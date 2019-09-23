#include"Texture .h"
#include<GameLib/Graphics/Manager.h>
#include<assert.h>
#include"helper/MyOutputDebugString.h"
#include"TextureHelper.h"
#include"helper/ContainerHelper/findByName.h"
namespace MME{


typedef Texture Type;
std::vector< std::weak_ptr<Type> > Type::sCache;
typedef std::vector< std::weak_ptr<Type> >::iterator ItType;

TextureSharedPtr Texture::create(  ID3DXEffect *effect, D3DXHANDLE hTex, const std::string &path ){
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
				std::shared_ptr<Type> p( new Type( *shared.get(), effect, hTex, path ) );
				return p;
			} else{
				assert(false && "タイミングによってはバグりそうな気がする念のため");
				std::shared_ptr<Type> p( new Type( effect, hTex, path ) );
				//更新
				*it=p;
				return p;
			}
		}
		//not found! create and push_back to Cache.
		else {
			std::shared_ptr<Type> p( new Type( effect, hTex, path ) );
			sCache.push_back(p);
			return p;
		}
	}
	

	std::shared_ptr<Type> p( new Type( effect, hTex, path ) );
	return p;
}

void Texture::clearCache(){
	sCache.clear();
	sCache.shrink_to_fit();
}
void Texture::shrinkToFitCache(){
	sCache.shrink_to_fit();

}

Texture::~Texture(){
	mTexture.reset();
}

const std::string & Texture::getName()const{
	return mName;
}

bool Texture::isError()const{
	return mTexture==NULL;
}
void Texture::send(ID3DXEffect *effect){
	HRESULT hr;
	hr=effect->SetTexture( mHandle, mTexture.get() );
	assert(SUCCEEDED(hr));
}

Texture::Texture( ID3DXEffect *effect, D3DXHANDLE hTex, const std::string &path ) :
	mTexture(NULL),
	mHandle(NULL)
{
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	HRESULT hr;
	D3DXPARAMETER_DESC texDesc;
	hr=effect->GetParameterDesc( hTex, &texDesc );
		
	//型はtexture, texture2D, texture3D, textureCUBEのうちいずれか。
	if(
		texDesc.Type==D3DXPT_TEXTURE ||
		//texDesc.Type==D3DXPT_TEXTURE1D ||
		texDesc.Type==D3DXPT_TEXTURE2D ){
		//texDesc.Type==D3DXPT_TEXTURE3D ||
		//texDesc.Type==D3DXPT_TEXTURECUBE ){
	} else{
		assert( false && "not impliment." );
		assert( false && "type must be texture or texture2D, texTure3D, textureCUBE." ); 
		return;
	}
		
	//・string ResourceType
	//テクスチャの種類を指定する。"2D", "3D", "CUBE"のうちいずれかを指定する。
	//型と矛盾した値は指定できない。
	//
	//型が"texture"であり、かつ"2D"以外のテクスチャを生成する場合には、
	//かならずこのアノテーションを指定しなければならない。それ以外では省略可能である。
	D3DXHANDLE hResourceType = effect->GetAnnotationByName( hTex, "ResourceType" );
	if( hResourceType ){
		const char *rt=NULL;
		effect->GetString( hResourceType, &rt );
		if( _strcmpi(rt, "2D")==0 ){}
		else if( _strcmpi(rt, "3D")==0 ){
			assert( false && "not impliment." );
			return;
		}
		else if( _strcmpi(rt, "CUBE")==0 ){
			assert( false && "not impliment." );			
			return;
		}
		else {
			assert( false && "ResourceType is wrong." );
			return;
		}
	}

	//・string ResourceName
	//テクスチャの元になる画像ファイルを指定する。
	//サポートしているファイルフォーマットは、bmp、.dds、.dib、.jpg、.png、および .tga である。
	//相対パスでファイル名を指定した場合、エフェクトファイルが格納されているフォルダが基準となる。
	D3DXHANDLE hResourceName = effect->GetAnnotationByName( hTex, "ResourceName" );
	if( hResourceName ){
		const char *rname=NULL;
		hr=effect->GetString( hResourceName, &rname );
		assert(SUCCEEDED(hr));
		std::string fileName(path);
		fileName.append(rname);
		IDirect3DTexture9 *pTexture=NULL;			
		if( 
			FAILED( D3DXCreateTextureFromFileA( pDevice, fileName.c_str(), &pTexture ) )
		){
			assert(false && "textureの作成に失敗しました。");
			return;
		}
		mTexture.reset( pTexture, TextureReleaser );
	} else {
		//・int Width, int　Height, int Depth
		//	テクスチャの幅、高さ、深さをピクセル単位で指定する。
		//	深さを指定するのはボリュームテクスチャの場合のみである。
		//	
		//	Dimensions, ViewportRatio とは同時に指定できない。
		//
		//	(Width,Height,Depth), Dimensions, ViewportRatioのいずれも指定されていない場合の、
		//	デフォルト値は、64ピクセルである。
		//	また、ResourceNameが指定されているならば、画像ファイルからサイズが自動的に取得される。
		int width=64, height=64, depth=64;

		D3DXHANDLE hWidth=0, hHeight=0, hDepth=0;
		hWidth  = getWidth(	 effect, hTex, &width );
		hHeight = getHeight( effect, hTex, &height );
		hDepth  = getDepth(	 effect, hTex, &depth );

		//・int2(or int3) Dimensions
		//	テクスチャの幅、高さ、深さをピクセル単位で指定する。
		//	深さを指定するのはボリュームテクスチャの場合のみである。
		//	
		//	ViewportRatio, Width, Height, Depthとは同時に指定できない。
		D3DXHANDLE hDimensions=0;
		hDimensions = getDimensions( effect, hTex, &height, &width, &depth );

		//・float2 ViewportRatio
		//	テクスチャの幅、高さを、レンダリングターゲットのスクリーンのサイズとの比で指定する。
		//	スクリーンと同じサイズのテクスチャを生成するには、"float2 ViewportRatio = {1.0, 1.0};" と指定する。
		//	スクリーンの縦横2倍のサイズのテクスチャを生成するには、"float2 ViewportRatio = {2.0, 2.0};" と指定する。
		//	Dimensions, Width, Height, Depthとは同時に指定できない。
		D3DXHANDLE hViewPortRatio = 0;
		float xRate=1.f, yRate=1.f;

		hViewPortRatio = getViewPortRatio( effect, hTex, &xRate, &yRate );

		if( hViewPortRatio ){
			GameLib::Framework fw = GameLib::Framework::instance();
			width = static_cast<int>(fw.width()*xRate);
			height = static_cast<int>(fw.height()*yRate);
		}

		if( hViewPortRatio && hDimensions ){
			assert( false && "ViewportRatio, hDimensionsとは同時に指定できない。" );
			return;
		} else if( hViewPortRatio && (hWidth || hHeight || hDepth) ){
			assert( false && "ViewportRatio, Width, Height, Depthとは同時に指定できない。" );
			return;
		} else if( hDimensions && (hWidth || hHeight || hDepth) ){
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
		D3DFORMAT format = getFormat( effect, hTex, D3DFMT_A8R8G8B8 );

		//・int Miplevels
		//	ミップマップを指定したレベルで生成する。
		//	省略するか0を指定した場合、完全なミップマップ チェーンが作成される。
		//	1を指定すると、ミップマップは生成されない。
		//・int Levels
		//	Miplevelsの別名である。
		int miplevels= getMiplevel( effect, hTex, 0 );

		IDirect3DTexture9 *pTexture=NULL;	
		//テクスチャオブジェクトの作成
		if( FAILED(
				D3DXCreateTexture(
				pDevice,
				width, height,
				miplevels,
				0,
				format,
				D3DPOOL_MANAGED,
				&pTexture )
			)
		){
			assert( false && "テクスチャの作成に失敗しました");
		}
		mTexture.reset( pTexture, TextureReleaser );
		assert(false&&"ここ来たら可笑しい気がする");
	}

	mName.assign(texDesc.Name);
	mHandle=hTex;

	//D3DSURFACE_DESC desc;

	//mTexture->GetLevelDesc( 0, &desc );
	//desc.
}

Texture::Texture( const Texture &src, ID3DXEffect *effect, D3DXHANDLE hTex, const std::string &path )
	:mTexture(src.mTexture),
	mHandle(hTex),
	mName(src.mName)
{
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	HRESULT hr;
	D3DXPARAMETER_DESC texDesc;
	hr=effect->GetParameterDesc( hTex, &texDesc );
		
	//型はtexture, texture2D, texture3D, textureCUBEのうちいずれか。
	if(
		texDesc.Type==D3DXPT_TEXTURE ||
		//texDesc.Type==D3DXPT_TEXTURE1D ||
		texDesc.Type==D3DXPT_TEXTURE2D ){
		//texDesc.Type==D3DXPT_TEXTURE3D ||
		//texDesc.Type==D3DXPT_TEXTURECUBE ){
	} else{
		assert( false && "not impliment." );
		assert( false && "type must be texture or texture2D, texTure3D, textureCUBE." ); 
		return;
	}
		
	//・string ResourceType
	//テクスチャの種類を指定する。"2D", "3D", "CUBE"のうちいずれかを指定する。
	//型と矛盾した値は指定できない。
	//
	//型が"texture"であり、かつ"2D"以外のテクスチャを生成する場合には、
	//かならずこのアノテーションを指定しなければならない。それ以外では省略可能である。
	D3DXHANDLE hResourceType = effect->GetAnnotationByName( hTex, "ResourceType" );
	if( hResourceType ){
		const char *rt=NULL;
		effect->GetString( hResourceType, &rt );
		if( _strcmpi(rt, "2D")==0 ){}
		else if( _strcmpi(rt, "3D")==0 ){
			assert( false && "not impliment." );
			return;
		}
		else if( _strcmpi(rt, "CUBE")==0 ){
			assert( false && "not impliment." );			
			return;
		}
		else {
			assert( false && "ResourceType is wrong." );
			return;
		}
	}

	//・string ResourceName
	//テクスチャの元になる画像ファイルを指定する。
	//サポートしているファイルフォーマットは、bmp、.dds、.dib、.jpg、.png、および .tga である。
	//相対パスでファイル名を指定した場合、エフェクトファイルが格納されているフォルダが基準となる。
	D3DXHANDLE hResourceName = effect->GetAnnotationByName( hTex, "ResourceName" );
	if( hResourceName ){
	} else {
		//・int Width, int　Height, int Depth
		//	テクスチャの幅、高さ、深さをピクセル単位で指定する。
		//	深さを指定するのはボリュームテクスチャの場合のみである。
		//	
		//	Dimensions, ViewportRatio とは同時に指定できない。
		//
		//	(Width,Height,Depth), Dimensions, ViewportRatioのいずれも指定されていない場合の、
		//	デフォルト値は、64ピクセルである。
		//	また、ResourceNameが指定されているならば、画像ファイルからサイズが自動的に取得される。
		int width=64, height=64, depth=64;

		D3DXHANDLE hWidth=0, hHeight=0, hDepth=0;
		hWidth  = getWidth(	 effect, hTex, &width );
		hHeight = getHeight( effect, hTex, &height );
		hDepth  = getDepth(	 effect, hTex, &depth );

		//・int2(or int3) Dimensions
		//	テクスチャの幅、高さ、深さをピクセル単位で指定する。
		//	深さを指定するのはボリュームテクスチャの場合のみである。
		//	
		//	ViewportRatio, Width, Height, Depthとは同時に指定できない。
		D3DXHANDLE hDimensions=0;
		hDimensions = getDimensions( effect, hTex, &height, &width, &depth );

		//・float2 ViewportRatio
		//	テクスチャの幅、高さを、レンダリングターゲットのスクリーンのサイズとの比で指定する。
		//	スクリーンと同じサイズのテクスチャを生成するには、"float2 ViewportRatio = {1.0, 1.0};" と指定する。
		//	スクリーンの縦横2倍のサイズのテクスチャを生成するには、"float2 ViewportRatio = {2.0, 2.0};" と指定する。
		//	Dimensions, Width, Height, Depthとは同時に指定できない。
		D3DXHANDLE hViewPortRatio = 0;
		float xRate=1.f, yRate=1.f;

		hViewPortRatio = getViewPortRatio( effect, hTex, &xRate, &yRate );

		if( hViewPortRatio ){
			GameLib::Framework fw = GameLib::Framework::instance();
			width = static_cast<int>(fw.width()*xRate);
			height = static_cast<int>(fw.height()*yRate);
		}

		if( hViewPortRatio && hDimensions ){
			assert( false && "ViewportRatio, hDimensionsとは同時に指定できない。" );
			return;
		} else if( hViewPortRatio && (hWidth || hHeight || hDepth) ){
			assert( false && "ViewportRatio, Width, Height, Depthとは同時に指定できない。" );
			return;
		} else if( hDimensions && (hWidth || hHeight || hDepth) ){
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
		D3DFORMAT format = getFormat( effect, hTex, D3DFMT_A8R8G8B8 );

		//・int Miplevels
		//	ミップマップを指定したレベルで生成する。
		//	省略するか0を指定した場合、完全なミップマップ チェーンが作成される。
		//	1を指定すると、ミップマップは生成されない。
		//・int Levels
		//	Miplevelsの別名である。
		int miplevels= getMiplevel( effect, hTex, 0 );

		IDirect3DTexture9 *pTexture=NULL;	
		//テクスチャオブジェクトの作成
		if( FAILED(
				D3DXCreateTexture(
				pDevice,
				width, height,
				miplevels,
				0,
				format,
				D3DPOOL_MANAGED,
				&pTexture )
			)
		){
			assert( false && "テクスチャの作成に失敗しました");
		}
		mTexture.reset( pTexture, TextureReleaser );
		assert(false&&"ここ来たら可笑しい気がする");
	}

	assert( mName == texDesc.Name );
}



} // end namespace
