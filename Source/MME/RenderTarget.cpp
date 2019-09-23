#include"RenderTarget.h"
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Framework.h>
#include<assert.h>
#include"helper/MyOutputDebugString.h"
#include<string>
#include"TextureHelper.h"
#include"BaseEffect.h"
#include"helper/ContainerHelper/findByName.h"



namespace MME{

typedef RenderTarget Type;
std::vector< std::weak_ptr<Type> > Type::sCache;
typedef std::vector< std::weak_ptr<Type> >::iterator ItType;

RenderTargetSharedPtr RenderTarget::create(  ID3DXEffect *effect, D3DXHANDLE hTex ){
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
				RenderTargetSharedPtr p( new Type( *shared.get(), effect, hTex ) );
				return p;
			} else{
				assert(false && "タイミングによってはバグりそうな気がする念のため");
				RenderTargetSharedPtr p( new Type( effect, hTex ) );
				//更新
				*it=p;
				return p;
			}
		}
		//not found! create and push_back to Cache.
		else {
			RenderTargetSharedPtr p( new Type( effect, hTex ) );
			sCache.push_back(p);
			return p;
		}
	}
	

	RenderTargetSharedPtr p( new RenderTarget(effect, hTex ) );
	return p;
}

RenderTarget::~RenderTarget(){
}
bool RenderTarget::isError()const{
	return mTexture==NULL;
}
void RenderTarget::send(ID3DXEffect *effect){
	HRESULT hr;
	hr=effect->SetTexture( mHandle, mTexture.get() );
	assert(SUCCEEDED(hr));
		
	//D3DXPARAMETER_DESC desc;
	//effect->GetParameterDesc( mHandle, &desc );

}

//IDirect3DSurface9* RenderTarget::getSurfLevel( UINT level ){
//	IDirect3DSurface9 *result=0;
//	HRESULT hr;
//	hr=mTexture->GetSurfaceLevel( level, &result );
//	assert(SUCCEEDED(hr));
//	return result;
//}


//名前が目的語と主語でかぶっているがわかりやすいからこの名前にした
//他候補としては
//	setToDevice
//	setSelf
void RenderTarget::setRenderTarget( int renderTargetIndex, BaseEffect* effect ){
	HRESULT hr;
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	
	//レンダリングターゲットをテクスチャにセット
	hr=pDevice->SetRenderTarget( renderTargetIndex, mSurface.get() );				
	assert(SUCCEEDED(hr));
	
	if( renderTargetIndex==0 )
	{
		D3DSURFACE_DESC desc;
		hr=mSurface->GetDesc( &desc );
		assert(SUCCEEDED(hr));
	
		//set viewport
		D3DVIEWPORT9 vp;
		vp.X = vp.Y = 0;
		vp.Width = desc.Width;
		vp.Height = desc.Height;
		vp.MinZ = 0.f;
		vp.MaxZ = 1.f;
		hr=pDevice->SetViewport( &vp );
		assert(SUCCEEDED(hr));
		
		//※この値は、MMDのスクリーンもしくはオフスクリーンレンダリングターゲットのサイズを指す。
		//Scriptsの"RenderColorTarget"コマンドで、レンダリングターゲットが変更しても、
		//この値は変化しない。
		//effect->setViewportPixelSize( static_cast<float>(vp.Width), static_cast<float>(vp.Height) );
	}
}

const std::string & RenderTarget::getName()const{
	return mName;
}

//デバイスロスト時のための開放処理
void RenderTarget::backup(){
	mTexture.reset();
	mSurface.reset();
}
//デバイスロスト時のためのリソース再確保
void RenderTarget::recover(){
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
		
	IDirect3DTexture9 *pTexture=NULL;
		
	HRESULT hr;
	//レンダリングターゲットになるテクスチャオブジェクトの作成
	if( FAILED(
			D3DXCreateTexture(
			pDevice,
			mWidth, mHeight,
			mMipLevels,
			D3DUSAGE_RENDERTARGET,
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
	mSurface.reset( pSurface, SurfaceReleaser );
}


RenderTarget::RenderTarget( ID3DXEffect *effect, D3DXHANDLE hTex) :
	mTexture(NULL, TextureReleaser ),
	mHandle(0),
	mSurface(NULL, SurfaceReleaser ),
	mWidth(0),
	mHeight(0),
	mMipLevels(1),
	mFormat(D3DFMT_A8R8G8B8),
	mIsShared(false)
{
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	GameLib::Framework fw = GameLib::Framework::instance();
	HRESULT hr;

	D3DXPARAMETER_DESC texDesc;
	hr=effect->GetParameterDesc( hTex, &texDesc );
	
	mName.assign(texDesc.Name);

	mIsShared = 0 != (texDesc.Flags & D3DX_PARAMETER_SHARED);
		
	//●RENDERCOLORTARGET
	assert( _strcmpi( texDesc.Semantic, "RENDERCOLORTARGET" )==0 );
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
	//	深さを指定するのはボリュームテクスチャの場合のみである。
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
	float xRate=1.f, yRate=1.f;
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
	//	
	//	省略した場合、"A8R8G8B8"が使用される。
	//	ResourceNameが指定されているならば、画像ファイルからフォーマットが取得され、
	//	このアノテーションの設定は無視される。
	//	
	//	指定可能なフォーマットは、D3DFORMAT（http://msdn.microsoft.com/ja-jp/library/bb172558(v=VS.85).aspx）
	//	を参照。
	//	
	//	"A8R8G8B8"、"FMT_A8R8G8B8"、"D3DFMT_A8R8G8B8"のいずれの書式でも指定できる。
	mFormat = getFormat( effect, hTex, D3DFMT_A8R8G8B8 );


	//・int Miplevels
	//・int Levels
	//　　"●通常テクスチャ"を参照。
	//　　1または0が指定できる。
	//　　0を指定した場合、完全なミップマップ チェーンが作成される。
	//　　1を指定すると、ミップマップは生成されない（デフォルト）。
	mMipLevels= getMiplevel( effect, hTex, 1 );

	recover();

	mHandle=hTex;
}

//共通の値か確かめる
RenderTarget::RenderTarget( const RenderTarget &src, ID3DXEffect *effect, D3DXHANDLE hTex )
	:mTexture(src.mTexture),
	mHandle(hTex),
	mSurface(src.mSurface ),
	mWidth(src.mWidth),
	mHeight(src.mHeight),
	mMipLevels(src.mMipLevels),
	mFormat(src.mFormat),
	mIsShared(src.mIsShared),
	mName( src.mName )
{
	GameLib::Framework fw = GameLib::Framework::instance();
	HRESULT hr;

	D3DXPARAMETER_DESC texDesc;
	hr=effect->GetParameterDesc( hTex, &texDesc );
		
	assert( mIsShared == 0 != (texDesc.Flags & D3DX_PARAMETER_SHARED) );
		
	//●RENDERCOLORTARGET
	assert( _strcmpi( texDesc.Semantic, "RENDERCOLORTARGET" )==0 );
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
	//	深さを指定するのはボリュームテクスチャの場合のみである。
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
	float xRate=1.f, yRate=1.f;
	hViewPortRatio = getViewPortRatio( effect, hTex, &xRate, &yRate );

	if( hWidth && hHeight ){
		assert(	mWidth	==	width);
		assert( mHeight	==	height );
	}else if( hDimensions ){
		assert(	mWidth	==	width);
		assert( mHeight	==	height );
	}else if( hViewPortRatio ){
		width = static_cast<unsigned int>(static_cast<float>(fw.width())*xRate);
		height = static_cast<unsigned int>(static_cast<float>(fw.height())*yRate);
		assert(	mWidth	==	width);
		assert( mHeight	==	height );
	}else {
		width=fw.width();
		height=fw.height();
		assert(	mWidth	==	width);
		assert( mHeight	==	height );
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
	//	
	//	省略した場合、"A8R8G8B8"が使用される。
	//	ResourceNameが指定されているならば、画像ファイルからフォーマットが取得され、
	//	このアノテーションの設定は無視される。
	//	
	//	指定可能なフォーマットは、D3DFORMAT（http://msdn.microsoft.com/ja-jp/library/bb172558(v=VS.85).aspx）
	//	を参照。
	//	
	//	"A8R8G8B8"、"FMT_A8R8G8B8"、"D3DFMT_A8R8G8B8"のいずれの書式でも指定できる。
	assert( mFormat == getFormat( effect, hTex, D3DFMT_A8R8G8B8 ) );

	//・int Miplevels
	//・int Levels
	//　　"●通常テクスチャ"を参照。
	//　　1または0が指定できる。
	//　　0を指定した場合、完全なミップマップ チェーンが作成される。
	//　　1を指定すると、ミップマップは生成されない（デフォルト）。
	assert( mMipLevels == getMiplevel( effect, hTex, 1 ) );

	assert(mName==texDesc.Name);
}

void RenderTarget::clearCache(){
	sCache.clear();
	sCache.shrink_to_fit();
}
void RenderTarget::shrinkToFitCache(){
	sCache.shrink_to_fit();
}

}// end namespace MME