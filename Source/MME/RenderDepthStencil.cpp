#include"RenderDepthStencil.h"
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Framework.h>
#include<assert.h>
#include"helper/MyOutputDebugString.h"
#include"TextureHelper.h"
#include"helper/ContainerHelper/findByName.h"

namespace MME {

typedef RenderDepthStencil Type;
std::vector< std::weak_ptr<Type> > Type::sCache;
typedef std::vector< std::weak_ptr<Type> >::iterator ItType;

RenderDepthStencilSharedPtr RenderDepthStencil::create(  ID3DXEffect *effect, D3DXHANDLE hTex ){
	using namespace ContainerHelper;

	HRESULT hr;

	D3DXPARAMETER_DESC texDesc;
	hr=effect->GetParameterDesc( hTex, &texDesc );
		
	bool isShared = 0 != (texDesc.Flags & D3DX_PARAMETER_SHARED);

	if( isShared){
		ItType it = sCache|findByName( texDesc.Name );

		//found!
		if( it !=sCache.end() ){
			//not expired
			if(std::shared_ptr<Type> shared = it->lock() ){
				std::shared_ptr<Type> p( new Type( *shared.get(), effect, hTex ) );
				return p;
			} else{
				assert(false && "タイミングによってはバグりそうな気がする念のため");
				std::shared_ptr<Type> p( new Type( effect, hTex ) );
				//更新
				*it=p;
				return p;
			}
		}
		//not found! create and push_back to Cache.
		else {
			std::shared_ptr<Type> p( new Type( effect, hTex ) );
			sCache.push_back(p);
			return p;
		}
	}
	

	std::shared_ptr<Type> p( new Type( effect, hTex ) );
	return p;
}

void RenderDepthStencil::clearCache(){
	sCache.clear();
	sCache.shrink_to_fit();
}
void RenderDepthStencil::shrinkToFitCache(){
	sCache.shrink_to_fit();

}
RenderDepthStencil::~RenderDepthStencil(){
}
bool RenderDepthStencil::isError()const{
	return mZBuffer==NULL;
}
	
//IDirect3DSurface9* RenderDepthStencil::getZBuffer(){
//	return mZBuffer;
//}

void RenderDepthStencil::setDepthStencilSurface(){
	HRESULT hr;
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();

	hr=pDevice->SetDepthStencilSurface( mZBuffer.get() );				
	assert(SUCCEEDED(hr));
}

const std::string & RenderDepthStencil::getName()const{
	return mName;
}

void RenderDepthStencil::send(ID3DXEffect *effect){
	HRESULT hr;
	hr=effect->SetTexture( mHandle, mTexture.get() );
	assert(SUCCEEDED(hr));
}

//デバイスロスト時のための開放処理
void RenderDepthStencil::backup(){
	mZBuffer.reset();
	mTexture.reset();
}
//デバイスロスト時のためのリソース再確保
void RenderDepthStencil::recover(){
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	
	HRESULT hr;
	//1を指定すると、ミップマップは生成されない。
	int miplevels=1;
	IDirect3DTexture9 *pTexture=NULL;

	//RENDERCOLORTARGETで生成したテクスチャとは違い、このセマンティクスで生成したテクスチャは、
	//レンダリング後も、内容を参照することはできない。
	//となっているので、サーフェイス入らないかもね
	if( FAILED(
			D3DXCreateTexture(
			pDevice,
			mWidth, mHeight,
			miplevels,
			D3DUSAGE_DEPTHSTENCIL,
			mFormat,
			D3DPOOL_DEFAULT,
			&pTexture )
		)
	){
		assert( false && "テクスチャの作成に失敗しました");
		return;
	}
	mTexture.reset( pTexture, TextureReleaser );

	IDirect3DSurface9 *pSurface=NULL;
	hr=mTexture->GetSurfaceLevel(0, &pSurface);		 
	assert(SUCCEEDED(hr));
	mZBuffer.reset( pSurface, SurfaceReleaser );
}


RenderDepthStencil::RenderDepthStencil( ID3DXEffect *effect, D3DXHANDLE hTex) :
	mTexture(NULL),
	mZBuffer(NULL),
	mHandle(NULL),
	mWidth(0),
	mHeight(0),
	mFormat(D3DFMT_D24S8)

{
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	GameLib::Framework fw = GameLib::Framework::instance();
	HRESULT hr;

	D3DXPARAMETER_DESC texDesc;
	hr=effect->GetParameterDesc( hTex, &texDesc );
	//●RENDERDEPTHSTENCILTARGET
	assert( _strcmpi( texDesc.Semantic, "RENDERDEPTHSTENCILTARGET" )==0 );
	//型はtexture, texture2Dのうちいずれか。
	if(
		texDesc.Type==D3DXPT_TEXTURE ||
		//texDesc.Type==D3DXPT_TEXTURE1D ||
		texDesc.Type==D3DXPT_TEXTURE2D ){
	} else{
		assert( false && "type must be texture or texture2D." ); 
		return;
	}
		
	//・int Width, int　Height, int Depth
	//	テクスチャの幅、高さ、深さをピクセル単位で指定する。
	//	
	//	Dimensions, ViewportRatio とは同時に指定できない。
	//	省略した場合、"float2 ViewportRatio = {1.0, 1.0};" という設定が使用される。
	int width=fw.width(), height=fw.height();

	D3DXHANDLE hWidth=0, hHeight=0;
	hWidth  = getWidth(	 effect, hTex, &width );
	hHeight = getHeight( effect, hTex, &height );

	//・int2 Dimensions
	//	テクスチャの幅、高さ、深さをピクセル単位で指定する。
	//	深さを指定するのはボリュームテクスチャの場合のみである。
	//	
	//	ViewportRatio, Width, Height, Depthとは同時に指定できない。
	D3DXHANDLE hDimensions=0;
	int dummy;
	hDimensions = getDimensions( effect, hTex, &height, &width, &dummy );

	//・float2 ViewportRatio
	//	テクスチャの幅、高さを、レンダリングターゲットのスクリーンのサイズとの比で指定する。
	//	スクリーンと同じサイズのテクスチャを生成するには、"float2 ViewportRatio = {1.0, 1.0};" と指定する。
	//	スクリーンの縦横2倍のサイズのテクスチャを生成するには、"float2 ViewportRatio = {2.0, 2.0};" と指定する。
	//	Dimensions, Width, Height, Depthとは同時に指定できない。
	//	"●通常テクスチャ"を参照。
	//	省略した場合、"float2 ViewportRatio = {1.0, 1.0};" という設定が使用される。
	D3DXHANDLE hViewPortRatio = 0;
	float xRate=1.f;
	float yRate=1.f;
	hViewPortRatio = getViewPortRatio( effect, hTex, &xRate, &yRate );
	
	if( hWidth && hHeight ){
		mWidth=width;
		mHeight=height;
	}else if( hDimensions ){
		mWidth=width;
		mHeight=height;
	}else if( hViewPortRatio ){
		mWidth = static_cast<unsigned int>(static_cast<float>(fw.width())*xRate);
		mHeight = static_cast<unsigned int>(static_cast<float>(fw.height())*yRate);
	}else {
		mWidth=fw.width();
		mHeight=fw.height();
	}	

	if( hViewPortRatio && hDimensions ){
		assert( false && "ViewportRatio, hDimensionsとは同時に指定できない。" );
		return;
	} else if( hViewPortRatio && (hWidth || hHeight ) ){
		assert( false && "ViewportRatio, Width, Height, Depthとは同時に指定できない。" );
		return;
	} else if( hDimensions && (hWidth || hHeight ) ){
		assert( false && "hDimensions, Width, Height, Depthとは同時に指定できない。" );
		return;
	}

	//・string Format
	//	テクスチャのフォーマットを指定する。
	//	省略した場合、"D24S8"が使用される。
	mFormat = getFormatRenderStencil( effect, hTex );
	
	//1を指定すると、ミップマップは生成されない。
	int miplevels=1;

	recover();

	mName.assign(texDesc.Name);
	mHandle=hTex;
}

RenderDepthStencil::RenderDepthStencil( const RenderDepthStencil &src, ID3DXEffect *effect, D3DXHANDLE hTex)
	:mTexture(src.mTexture),
	mZBuffer(src.mZBuffer),
	mHandle(hTex),
	mWidth(src.mWidth),
	mHeight(src.mHeight),
	mFormat(src.mFormat),
	mName(src.mName)
{
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	GameLib::Framework fw = GameLib::Framework::instance();
	HRESULT hr;

	D3DXPARAMETER_DESC texDesc;
	hr=effect->GetParameterDesc( hTex, &texDesc );
	//●RENDERDEPTHSTENCILTARGET
	assert( _strcmpi( texDesc.Semantic, "RENDERDEPTHSTENCILTARGET" )==0 );
	//型はtexture, texture2Dのうちいずれか。
	if(
		texDesc.Type==D3DXPT_TEXTURE ||
		//texDesc.Type==D3DXPT_TEXTURE1D ||
		texDesc.Type==D3DXPT_TEXTURE2D ){
	} else{
		assert( false && "type must be texture or texture2D." ); 
		return;
	}
		
	//・int Width, int　Height, int Depth
	//	テクスチャの幅、高さ、深さをピクセル単位で指定する。
	//	
	//	Dimensions, ViewportRatio とは同時に指定できない。
	//	省略した場合、"float2 ViewportRatio = {1.0, 1.0};" という設定が使用される。
	int width=fw.width(), height=fw.height();

	D3DXHANDLE hWidth=0, hHeight=0;
	hWidth  = getWidth(	 effect, hTex, &width );
	hHeight = getHeight( effect, hTex, &height );

	//・int2 Dimensions
	//	テクスチャの幅、高さ、深さをピクセル単位で指定する。
	//	深さを指定するのはボリュームテクスチャの場合のみである。
	//	
	//	ViewportRatio, Width, Height, Depthとは同時に指定できない。
	D3DXHANDLE hDimensions=0;
	int dummy;
	hDimensions = getDimensions( effect, hTex, &height, &width, &dummy );

	//・float2 ViewportRatio
	//	テクスチャの幅、高さを、レンダリングターゲットのスクリーンのサイズとの比で指定する。
	//	スクリーンと同じサイズのテクスチャを生成するには、"float2 ViewportRatio = {1.0, 1.0};" と指定する。
	//	スクリーンの縦横2倍のサイズのテクスチャを生成するには、"float2 ViewportRatio = {2.0, 2.0};" と指定する。
	//	Dimensions, Width, Height, Depthとは同時に指定できない。
	//	"●通常テクスチャ"を参照。
	//	省略した場合、"float2 ViewportRatio = {1.0, 1.0};" という設定が使用される。
	D3DXHANDLE hViewPortRatio = 0;
	float xRate=1.f;
	float yRate=1.f;
	hViewPortRatio = getViewPortRatio( effect, hTex, &xRate, &yRate );
	
	if( hWidth && hHeight ){
	}else if( hDimensions ){
	}else if( hViewPortRatio ){
		width = static_cast<unsigned int>(static_cast<float>(fw.width())*xRate);
		height = static_cast<unsigned int>(static_cast<float>(fw.height())*yRate);
	}else {
		width=fw.width();
		height=fw.height();
	}
	assert( mHeight == height );
	assert( mWidth == width );

	if( hViewPortRatio && hDimensions ){
		assert( false && "ViewportRatio, hDimensionsとは同時に指定できない。" );
		return;
	} else if( hViewPortRatio && (hWidth || hHeight ) ){
		assert( false && "ViewportRatio, Width, Height, Depthとは同時に指定できない。" );
		return;
	} else if( hDimensions && (hWidth || hHeight ) ){
		assert( false && "hDimensions, Width, Height, Depthとは同時に指定できない。" );
		return;
	}

	//・string Format
	//	テクスチャのフォーマットを指定する。
	//	省略した場合、"D24S8"が使用される。
	assert( mFormat == getFormatRenderStencil( effect, hTex ) );
	
	//1を指定すると、ミップマップは生成されない。
	int miplevels=1;

	assert( mName == texDesc.Name );
}


}// end namespace MME