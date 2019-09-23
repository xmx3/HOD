#include"OffScreenRender.h"
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Framework.h>
#include<assert.h>
#include"helper/MyOutputDebugString.h"
#include"helper/ContainerHelper/findByName.h"
#include"helper/ContainerHelper/safeDeleteAll.h"
#include"BaseEffect.h"
#include"TextureHelper.h"
#include"Manager.h"
#include<boost/xpressive/xpressive.hpp>
#include"helper/parseEquals.h"
#include<assert.h>
#include"helper/ReplaceTxt.h"
#include"Object/IObject.h"

namespace MME {

struct OffScreenRender::DefalutEffect{
	DefalutEffect( const boost::xpressive::sregex &reg, const std::string &str )
		:mModelFile(reg),
		mFxFileName(str)
	{}
	boost::xpressive::sregex mModelFile;
	std::string mFxFileName;
};

typedef OffScreenRender Type;
std::vector< std::weak_ptr<Type> > Type::sCache;
typedef std::vector< std::weak_ptr<Type> >::iterator ItType;

OffScreenRenderSharedPtr OffScreenRender::create(
	ID3DXEffect *effect,
	D3DXHANDLE hTex,
	const std::string& currentPath,
	LPD3DXEFFECTPOOL pool )
{
	using namespace ContainerHelper;

	HRESULT hr;

	D3DXPARAMETER_DESC texDesc;
	hr=effect->GetParameterDesc( hTex, &texDesc );
		
	bool isShared = 0 != (texDesc.Flags & D3DX_PARAMETER_SHARED);

	if( isShared){
		assert( false && "動かしたことなし、バグの可能性多々あり" );
		//対応する
		ItType it = sCache|findByName( texDesc.Name );

		//found!
		if( it !=sCache.end() ){
			//not expired
			if(std::shared_ptr<Type> shared = it->lock() ){
				std::shared_ptr<Type> p( new Type( *shared.get(), effect, hTex, currentPath, pool ) );
				return p;
			} else{
				assert(false && "タイミングによってはバグりそうな気がする念のため");
				std::shared_ptr<Type> p( new Type( effect, hTex, currentPath, pool ) );
				//更新
				*it=p;
				return p;
			}
		}
		//not found! create and push_back to Cache.
		else {
			std::shared_ptr<Type> p( new Type( effect, hTex, currentPath, pool ) );
			sCache.push_back(p);
			return p;
		}
	}
	

	std::shared_ptr<Type> p( new Type( effect, hTex, currentPath, pool ) );
	return p;
}

void OffScreenRender::clearCache(){
	sCache.clear();
	sCache.shrink_to_fit();
}
void OffScreenRender::shrinkToFitCache(){
	sCache.shrink_to_fit();
}

OffScreenRender::~OffScreenRender(){
	mDefalutEffects|ContainerHelper::safeDeleteAll();
	SAFE_RELEASE(mTempBackbuffer);
	SAFE_RELEASE(mTempBackZ);
}

bool OffScreenRender::isError()const{
	return mTexture==NULL;
}
void OffScreenRender::send(ID3DXEffect *effect){
	HRESULT hr;
	hr=effect->SetTexture( mHandle, mTexture.get() );
	assert(SUCCEEDED(hr));
		
	//D3DXPARAMETER_DESC desc;
	//effect->GetParameterDesc( mHandle, &desc );

}

void OffScreenRender::draw(){
	//HRESULT hr;
	//GameLib::Graphics::Manager m;
	//LPDIRECT3DDEVICE9 pDevice = m.dxDevice();

	//// バックバッファーの退避用
	////LPDIRECT3DSURFACE9      backbuffer;	// バックバッファー
	////LPDIRECT3DSURFACE9		backZ;		// バックバッファー用の深度バッファー


	//// ビューポート情報の保持
	////D3DVIEWPORT9 viewport;
	//pDevice->GetViewport(&mTempViewport);

	//// バックバッファーへのインターフェースの保持
	//hr=pDevice->GetRenderTarget(0, &mTempBackbuffer);
	//assert( SUCCEEDED(hr) );

	//// 深度バッファーのインターフェースの保持
	//hr=pDevice->GetDepthStencilSurface( &mTempBackZ); 
	//assert( SUCCEEDED(hr) );

	//// テクスチャをレンダリングターゲットに設定
	//hr=pDevice->SetRenderTarget(0, mSurface.get());
	//assert( SUCCEEDED(hr) );

	//// テクスチャ用の深度バッファを設定
	//hr=pDevice->SetDepthStencilSurface(mZBuffer.get());
	//assert( SUCCEEDED(hr) );

	//// レンダリングターゲットを初期化
	//hr=pDevice->Clear(0,NULL, 
	//	D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 
	//	D3DXCOLOR(mClearColor.x, mClearColor.y, mClearColor.z, mClearColor.w),
	//	mClearDepth, 0);
	//assert( SUCCEEDED(hr) );

	//// ビューポートをテクスチャ画像のサイズに設定
	//D3DSURFACE_DESC desc;
	//mTexture->GetLevelDesc( 0, &desc );
	//D3DVIEWPORT9 viewport2 = { 0, 0, desc.Width, desc.Height, 0.0f, 1.0f };
	//pDevice->SetViewport(&viewport2);

	//	描画タイミングは、以下の通りです。
	//(1) セルフシャドウ用Zバッファ描写(zplot)
	//(2) OFFSCREENRENDERTARGET一式描画
	//(3) ポストエフェクトのScriptの、先頭から"ScriptExternal=Color"まで
	//(4) プリエフェクト
	//(5) モデルよりも先に描画されるアクセサリ一式描画（object, object_ss）
	//(6) 地面影一式描写（shadow） ※ただしアクセの描画順序は不定
	//(7) モデル一式描画（object, object_ss）
	//(8) エッジ一式描画（edge）
	//(9) モデルより後に描写されるアクセサリ一式描写（object, object_ss）
	//(10) ポストエフェクトのScriptの、"ScriptExternal=Color"から最後まで
	//※(5)～(9)については、MMD側の描画順序に由来します。

	begin();

	//オフスクリーン用のシャドウバッファが必要、実装してない
	//beginShadow();
	//for(unsigned int i=0, size=mEffects.size(); i<size; ++i ){
	//	mEffects[i]->drawZPlot(); 
	//}
	//endShadow();

	//offscreenのoffscrenは入らない気がする(速度的に)	
	for(unsigned int i=0, size=mEffects.size(); i<size; ++i ){
		mEffects[i]->drawOffScreen(); 
	}

	for(unsigned int i=0, size=mEffects.size(); i<size; ++i ){
		StandardEffect *e = mEffects[i].get();
		e->drawObject();
		//e->drawObjectSS();//影つき描画のほうがいい気もするが

	}

	//遅いのでコメントアウト
	//for(unsigned int i=0, size=mEffects.size(); i<size; ++i ){
	//	StandardEffect *e = mEffects[i].get();
	//	e->drawEdge();
	//}

	
	end();

	//// 保存しておいたバックバッファをレンダリングターゲットに設定
	//hr=pDevice->SetRenderTarget(0, mTempBackbuffer);
	//assert( SUCCEEDED(hr) );
	//SAFE_RELEASE(mTempBackbuffer);

	//// 保存しておいたバックバッファの深度バッファを設定
	//hr=pDevice->SetDepthStencilSurface(mTempBackZ);
	//assert( SUCCEEDED(hr) );
	//SAFE_RELEASE(mTempBackZ);


	//// 保存しておいたビューポートを元に戻す
	//hr=pDevice->SetViewport(&mTempViewport);
	//assert( SUCCEEDED(hr) );
}
LPDIRECT3DTEXTURE9 OffScreenRender::getDxTexture(){
	return mTexture.get();
}


const std::string & OffScreenRender::getName()const{
	return mName;
}

//void OffScreenRender::removeRemovableObjects(){
//	for(unsigned int i=0, size=mEffects.size(); i<size; ++i ){		
//		mEffects[i]->removeRemovableObjects();
//	}
//}

StandardEffectSharedPtr OffScreenRender::findStandardEffect( const std::string &name ){
	using namespace ContainerHelper;
	std::vector<StandardEffectSharedPtr>::iterator it = mEffects|findByName2( name.c_str() );
	if( it==mEffects.end() ) {
		return NULL;
	} else {
		return *it;
	}
}

//デバイスロスト時のための開放処理
void OffScreenRender::backup(){
	mTexture.reset();
	mSurface.reset();
	mZBuffer.reset();

	for(unsigned int i=0, size=mEffects.size(); i<size; ++i ){
		mEffects[i]->backup(); 
	}


}
//デバイスロスト時のためのリソース再確保
void OffScreenRender::recover(){
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();

	HRESULT hr;

	IDirect3DTexture9 *pTexture=NULL;

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
		assert( false && "offscreenテクスチャの作成に失敗しました");
		return;
	}
	mTexture.reset( pTexture, TextureReleaser );

	IDirect3DSurface9 *pZBuffer;
	if(
		FAILED(
			pDevice->CreateDepthStencilSurface(
				mWidth, mHeight,
				D3DFMT_D24S8,
				D3DMULTISAMPLE_NONE,
				0,
				TRUE,
				&pZBuffer,
				NULL )
		)
	)
	{
		assert( false && "offscreen用のZバッファ作成に失敗しました");	
	}
	mZBuffer.reset( pZBuffer, SurfaceReleaser );


	IDirect3DSurface9 *pSurface=NULL;
	hr=mTexture->GetSurfaceLevel(0, &pSurface);		 
	assert(SUCCEEDED(hr));
	mSurface.reset( pSurface, SurfaceReleaser );
	
	for(unsigned int i=0, size=mEffects.size(); i<size; ++i ){
		mEffects[i]->recover(); 
	}
		
}

OffScreenRender::OffScreenRender( ID3DXEffect *effect, D3DXHANDLE hTex, const std::string& currentPath, LPD3DXEFFECTPOOL pool ) :
	mTexture(NULL),
	mHandle(NULL),
	mSurface(NULL),
	mZBuffer(NULL),
	mTempBackbuffer(NULL),
	mTempBackZ(NULL),
	mWidth(0),
	mHeight(0),
	mMipLevels(1),
	mFormat(D3DFMT_A8R8G8B8)
{
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	GameLib::Framework fw = GameLib::Framework::instance();
	HRESULT hr;

	D3DXPARAMETER_DESC texDesc;
	hr=effect->GetParameterDesc( hTex, &texDesc );
	//●OFFSCREENRENDERTARGET
	assert( _strcmpi( texDesc.Semantic, "OFFSCREENRENDERTARGET" )==0 );
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

	//D3DFORMAT formatZ = getFormatRenderStencil( effect, hTex );


	//・int Miplevels
	//・int Levels
	//　　"●通常テクスチャ"を参照。
	//　　1または0が指定できる。
	//　　0を指定した場合、完全なミップマップ チェーンが作成される。
	//　　1を指定すると、ミップマップは生成されない（デフォルト）。
	mMipLevels= getMiplevel( effect, hTex, 1 );

	//	・float4 ClearColor
	//　　レンダリングターゲットをクリアする色を設定する。
	//　　ここで指定した色で、レンダリングターゲットは自動的にクリアされる。
	//
	D3DXHANDLE hClearColor = effect->GetAnnotationByName( hTex, "ClearColor" );
	mClearColor.set( 0.f, 0.f, 0.f, 0.f );
	if( hClearColor ){
		float c[4]={0};
		hr=effect->GetFloatArray( hClearColor, c, 4 );
		assert( SUCCEEDED(hr) );
		mClearColor.set( c[0], c[1], c[2], c[3] );
	}

	//・float ClearDepth
	//　　深度ステンシルサーフェイスをクリアするZ値を設定する。
	//　　ここで指定したZ値で、深度ステンシルサーフェイスは自動的にクリアされる。
	D3DXHANDLE hClearDepth = effect->GetAnnotationByName( hTex, "ClearDepth" );
	mClearDepth = 0.f;
	if( hClearDepth ){
		hr=effect->GetFloat( hClearDepth, &mClearDepth );
		assert( SUCCEEDED(hr) );
	}

	//・bool AntiAlias
	//　　レンダリングにアンチエイリアスを使用する。デフォルトはfalse。
	//　　※アンチエイリアスが有効の場合、ビデオメモリは多く消費されるため、
	//　　　テクスチャのサイズには注意すること
	D3DXHANDLE hAntiAilias = effect->GetAnnotationByName( hTex, "AntiAlias" );
	mIsAntiAilias = false;
	if( hAntiAilias ){
		TRACE( "not impl offscreen antiailias" );
		hr=effect->GetBool( hAntiAilias, &mIsAntiAilias );
		assert( SUCCEEDED(hr) );
	}

	//・string Description
	//　　オフスクリーンレンダリングターゲットの説明文を指定する。
	//　　ここで指定した文字列が、エフェクト割当のGUIダイアログ上で表示される。
	D3DXHANDLE hDescription = effect->GetAnnotationByName( hTex, "Description" );
		
	if( hDescription ){
		const char *string;
		hr=effect->GetString( hDescription, &string );
		mDescription.assign( string );
		assert( SUCCEEDED(hr) );
	}


	//・string DefaultEffect
	//　　オフスクリーンレンダリングで使用するエフェクトファイルの割り当て方法を指定する。
	//　　１つの割り当ては、以下の書式で記述する。
	//　　
	//　　　　"(オブジェクトファイル名)=(エフェクトファイル名);"
	//　　
	//　　オブジェクト毎に使用するエフェクトファイルを切り替えるには、この割り当てを複数回記述する。
	//　　複数回記述した場合、記述した順でオブジェクトファイル名が比較され、最初にマッチしたものが使用される。
	//　　
	//　　　例： string DefaultEffect = "self=hide; Mirror*.x=hide; *=MirrorObject.fx;";
	//　　
	//　　オブジェクトファイル名には"*"と"?"によるワイルドカードが指定できる。
	//　　特殊なオブジェクトファイル名として"self"が指定でき、これは、
	//　　このOFFSCREENRENDERTARGETを持つエフェクトが割り当てられたオブジェクト自身を表す。
	//　　
	//　　エフェクトファイル名に相対パスでファイル名を指定した場合、
	//　　参照元のエフェクトファイルが格納されているフォルダが基準となる。
	//　　
	//　　また、特殊なエフェクトファイル名として"none"と"hide"が指定でき、
	//　　これは、「エフェクトなし」と「非表示」を表す。
	//　　また、"main_default"を指定すると、メインスクリーンでのデフォルト動作と同様な、
	//　　オブジェクトファイルパスに基づくfxファイルやemdファイルの自動割当が行われる。
	//　　
	D3DXHANDLE hDefaultEffect = effect->GetAnnotationByName( hTex, "DefaultEffect" );
	if( hDefaultEffect ){
		const char *string;
		hr=effect->GetString( hDefaultEffect, &string );
		assert( SUCCEEDED(hr) );

		while ( string && *string ){
			std::string fxfile, model;
			string = parseEquals( string, &model, &fxfile );
				
			if( model == "self" ){
				assert( fxfile=="hide" );
				//読み込むときxfile読み込まないから入らないでしょ、大抵"self=hide"だし
				TRACE1( "offscreen %s: ignored 'self' in DeffalutEffect annotation.\n", mName.c_str() );
				continue;
			}else{
				assert(false);
			}

			if( fxfile == "main_defalt" ){
				assert( false && "not impl" );
			} else if( fxfile == "none" ){
				assert( false && "not impl" );
			} else if( fxfile == "hide" ){
			}else{
				assert(false && "実装はしたけどテストしてない");
			}


			std::string fxFullPath( currentPath );
			fxFullPath.append( fxfile );
			//ファイルが存在するか
			if( 
				fxfile == "main_defalt" ||
				fxfile == "none"		||
				fxfile == "hide" )
			{
				fxFullPath = fxfile;

			}
			else if( findStandardEffect( fxFullPath ) )
			{
			
			}
			else{
				GameLib::FileIO::InFile f = GameLib::FileIO::InFile::create( fxFullPath.c_str() );
				StandardEffectSharedPtr effect = std::make_shared<StandardEffect>( fxFullPath, f, pool );
				if( effect->isError() ){
					assert(false);
					return;
				}
				effect->setViewportPixelSize( static_cast<float>(width), static_cast<float>(height) );

				mEffects.push_back( effect );
			}
			
			using namespace boost::xpressive;
			model = replaceText( model, "*", ".*" );
			model = replaceText( model, "?", ".?" );


			mDefalutEffects.emplace_back(
				new DefalutEffect( sregex::compile( model ), fxFullPath )
			);			
		}
	}
	mEffects.shrink_to_fit();

	recover();
		
	mName.assign(texDesc.Name);
	mHandle=hTex;
}

OffScreenRender::OffScreenRender( const OffScreenRender & src, ID3DXEffect *effect, D3DXHANDLE hTex, const std::string& currentPath, LPD3DXEFFECTPOOL pool )
	:mTexture(src.mTexture),
	mHandle(hTex),
	mSurface(src.mSurface),
	mZBuffer(src.mZBuffer),
	mTempBackbuffer(NULL),
	mTempBackZ(NULL),
	mWidth(src.mWidth),
	mHeight(src.mHeight),
	mMipLevels(src.mMipLevels),
	mFormat(src.mFormat),
	mName(src.mName),
	mClearColor(src.mClearColor),
	mClearDepth(src.mClearDepth),
	mIsAntiAilias(src.mIsAntiAilias),
	mDescription(src.mDescription )
{
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	GameLib::Framework fw = GameLib::Framework::instance();
	HRESULT hr;

	D3DXPARAMETER_DESC texDesc;
	hr=effect->GetParameterDesc( hTex, &texDesc );
	//●OFFSCREENRENDERTARGET
	assert( _strcmpi( texDesc.Semantic, "OFFSCREENRENDERTARGET" )==0 );
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
	}else if( hDimensions ){
	}else if( hViewPortRatio ){
		width = static_cast<unsigned int>(static_cast<float>(fw.width())*xRate);
		height = static_cast<unsigned int>(static_cast<float>(fw.height())*yRate);
	}else {}

	assert( mWidth==width );
	assert( mHeight==height );


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

	//D3DFORMAT formatZ = getFormatRenderStencil( effect, hTex );


	//・int Miplevels
	//・int Levels
	//　　"●通常テクスチャ"を参照。
	//　　1または0が指定できる。
	//　　0を指定した場合、完全なミップマップ チェーンが作成される。
	//　　1を指定すると、ミップマップは生成されない（デフォルト）。
	assert( mMipLevels == getMiplevel( effect, hTex, 1 ) );

	//	・float4 ClearColor
	//　　レンダリングターゲットをクリアする色を設定する。
	//　　ここで指定した色で、レンダリングターゲットは自動的にクリアされる。
	//
	D3DXHANDLE hClearColor = effect->GetAnnotationByName( hTex, "ClearColor" );
	if( hClearColor ){
		float c[4]={0};
		hr=effect->GetFloatArray( hClearColor, c, 4 );
		assert( SUCCEEDED(hr) );
		assert(
			mClearColor.x == c[0] &&
			mClearColor.y == c[1] &&
			mClearColor.z == c[2] &&
			mClearColor.w == c[3] 
		);
	}

	//・float ClearDepth
	//　　深度ステンシルサーフェイスをクリアするZ値を設定する。
	//　　ここで指定したZ値で、深度ステンシルサーフェイスは自動的にクリアされる。
	D3DXHANDLE hClearDepth = effect->GetAnnotationByName( hTex, "ClearDepth" );
	if( hClearDepth ){
		float clearDepth;
		hr=effect->GetFloat( hClearDepth, &clearDepth );
		assert( SUCCEEDED(hr) );
		assert( clearDepth==mClearDepth );
	}

	//・bool AntiAlias
	//　　レンダリングにアンチエイリアスを使用する。デフォルトはfalse。
	//　　※アンチエイリアスが有効の場合、ビデオメモリは多く消費されるため、
	//　　　テクスチャのサイズには注意すること
	D3DXHANDLE hAntiAilias = effect->GetAnnotationByName( hTex, "AntiAlias" );
	if( hAntiAilias ){
		int isAntiAilias;
		TRACE( "not impl offscreen antiailias" );
		hr=effect->GetBool( hAntiAilias, &isAntiAilias );
		assert( SUCCEEDED(hr) );
		assert( isAntiAilias==mIsAntiAilias );
	}

	//・string Description
	//　　オフスクリーンレンダリングターゲットの説明文を指定する。
	//　　ここで指定した文字列が、エフェクト割当のGUIダイアログ上で表示される。
	D3DXHANDLE hDescription = effect->GetAnnotationByName( hTex, "Description" );
		
	if( hDescription ){
		const char *string;
		hr=effect->GetString( hDescription, &string );
		assert( SUCCEEDED(hr) );
		assert( mDescription== string );
	}


	//・string DefaultEffect
	//　　オフスクリーンレンダリングで使用するエフェクトファイルの割り当て方法を指定する。
	//　　１つの割り当ては、以下の書式で記述する。
	//　　
	//　　　　"(オブジェクトファイル名)=(エフェクトファイル名);"
	//　　
	//　　オブジェクト毎に使用するエフェクトファイルを切り替えるには、この割り当てを複数回記述する。
	//　　複数回記述した場合、記述した順でオブジェクトファイル名が比較され、最初にマッチしたものが使用される。
	//　　
	//　　　例： string DefaultEffect = "self=hide; Mirror*.x=hide; *=MirrorObject.fx;";
	//　　
	//　　オブジェクトファイル名には"*"と"?"によるワイルドカードが指定できる。
	//　　特殊なオブジェクトファイル名として"self"が指定でき、これは、
	//　　このOFFSCREENRENDERTARGETを持つエフェクトが割り当てられたオブジェクト自身を表す。
	//　　
	//　　エフェクトファイル名に相対パスでファイル名を指定した場合、
	//　　参照元のエフェクトファイルが格納されているフォルダが基準となる。
	//　　
	//　　また、特殊なエフェクトファイル名として"none"と"hide"が指定でき、
	//　　これは、「エフェクトなし」と「非表示」を表す。
	//　　また、"main_default"を指定すると、メインスクリーンでのデフォルト動作と同様な、
	//　　オブジェクトファイルパスに基づくfxファイルやemdファイルの自動割当が行われる。
	//　　
	D3DXHANDLE hDefaultEffect = effect->GetAnnotationByName( hTex, "DefaultEffect" );
	assert( false && "これで良いと思うけど自信ない" );
	mEffects.assign(src.mEffects.begin(), src.mEffects.end() );
	
	//	
	//if( hDefaultEffect ){
	//	const char *string;
	//	hr=effect->GetString( hDefaultEffect, &string );
	//	assert( SUCCEEDED(hr) );

	//	while ( string && *string ){
	//		std::string fxfile, model;
	//		string = parseEquals( string, &model, &fxfile );
	//			
	//		if( model == "self" ){
	//			TRACE1( "offscreen %s: ignored self in DeffalutEffect annotation.\n", mName.c_str() );
	//			continue;
	//		}else{
	//			assert(false);
	//		}

	//		if( fxfile == "main_defalt" ){
	//			assert( false && "not impl" );
	//			continue;
	//		} else if( fxfile == "none" ){
	//			assert( false && "not impl" );
	//			continue;
	//		} else if( fxfile == "hide" ){
	//			continue;
	//		}else{
	//			assert(false);
	//		}


	//		std::string fxFullPath( currentPath );
	//		fxFullPath.append( fxfile );
	//		//ファイルが存在するかを確かめたほうがいい
	//		GameLib::FileIO::InFile f = GameLib::FileIO::InFile::create( fxFullPath.c_str() );
	//		StandardEffectSharedPtr effect = std::make_shared<StandardEffect>( fxFullPath, f, pool );
	//		if( effect->isError() ){
	//			assert(false);
	//			return;
	//		}
	//		effect->setViewportPixelSize( static_cast<float>(width), static_cast<float>(height) );

	//		mEffects.push_back( effect );
	//			
	//		std::vector<Object::IObjectSharedPtr> objects;
	//		using namespace boost::xpressive;
	//		model = replaceText( model, "*", ".*" );
	//		sregex rexModel = sregex::compile( model );
	//			
	//		Manager *m = Manager::instance();
	//		m->matchByModelFileName( &objects, rexModel );

	//		for( unsigned int i=0, size=objects.size(); i<size; i++ ){
	//			effect->add( objects[i] );
	//		}
	//		
	//	}
	//}
	mEffects.shrink_to_fit();

	assert(mName==texDesc.Name);
}

//void OffScreenRender::add( const Object::IObjectSharedPtr &obj ){
//	for( int i=0,size=mDefalutEffects.size(); i<size; ++i ){
//		std::string effectName;
//		if( findProperEffectName( &effectName, obj ) ){
//			StandardEffectSharedPtr ef = findStandardEffect( effectName );
//			if(ef){
//				ef->add( obj );
//			}
//			else {
//				assert(
//					mDefalutEffects[i]->mFxFileName == "hide" ||
//					mDefalutEffects[i]->mFxFileName == "main_defalut" ||
//					mDefalutEffects[i]->mFxFileName == "none"  &&
//					"登録されてないエフェクトを探そうとしたかも？" );
//
//			}
//			return;
//		}
//		
//	}
//}

bool OffScreenRender::findProperEffectName( std::string* found, const Object::IObjectSharedPtr &obj ){
	for( int i=0,size=mDefalutEffects.size(); i<size; ++i ){
		using namespace boost::xpressive;
		smatch what;
		if (regex_match( obj->getModelFileName(), what, mDefalutEffects[i]->mModelFile)) {
			*found = mDefalutEffects[i]->mFxFileName;
			return true;
		}
	}
	return false;
}

void OffScreenRender::begin(){
	HRESULT hr;
	GameLib::Graphics::Manager m;
	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();

	// ビューポート情報の保持
	pDevice->GetViewport(&mTempViewport);

	// バックバッファーへのインターフェースの保持
	hr=pDevice->GetRenderTarget(0, &mTempBackbuffer);
	assert( SUCCEEDED(hr) );

	// 深度バッファーのインターフェースの保持
	hr=pDevice->GetDepthStencilSurface( &mTempBackZ); 
	assert( SUCCEEDED(hr) );

	// テクスチャをレンダリングターゲットに設定
	hr=pDevice->SetRenderTarget(0, mSurface.get());
	assert( SUCCEEDED(hr) );

	// テクスチャ用の深度バッファを設定
	hr=pDevice->SetDepthStencilSurface(mZBuffer.get());
	assert( SUCCEEDED(hr) );

	// レンダリングターゲットを初期化
	hr=pDevice->Clear(0,NULL, 
		D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 
		D3DXCOLOR(mClearColor.x, mClearColor.y, mClearColor.z, mClearColor.w),
		mClearDepth, 0);
	assert( SUCCEEDED(hr) );

	// ビューポートをテクスチャ画像のサイズに設定
	D3DSURFACE_DESC desc;
	mTexture->GetLevelDesc( 0, &desc );
	D3DVIEWPORT9 viewport2 = { 0, 0, desc.Width, desc.Height, 0.0f, 1.0f };
	pDevice->SetViewport(&viewport2);

}

void OffScreenRender::end(){
	GameLib::Graphics::Manager m;
	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();
	
	// 保存しておいたバックバッファをレンダリングターゲットに設定
	HRESULT hr=pDevice->SetRenderTarget(0, mTempBackbuffer);
	assert( SUCCEEDED(hr) );
	SAFE_RELEASE(mTempBackbuffer);

	// 保存しておいたバックバッファの深度バッファを設定
	hr=pDevice->SetDepthStencilSurface(mTempBackZ);
	assert( SUCCEEDED(hr) );
	SAFE_RELEASE(mTempBackZ);


	// 保存しておいたビューポートを元に戻す
	hr=pDevice->SetViewport(&mTempViewport);
	assert( SUCCEEDED(hr) );
}

unsigned int OffScreenRender::getNumberOfStandardEffects()const
{
	return mEffects.size();
}
StandardEffectSharedPtr OffScreenRender::getStandardEffectAt( unsigned int i){
	return mEffects[i];
}

//void OffScreenRender::clearAllObjects(){
//	for(unsigned int i=0, size=mEffects.size(); i<size; ++i ){		
//		mEffects[i]->clearAllObjects();
//	}
//}


}// end namespace MME