#pragma once
#include<d3dx9.h>
#include<GameLib/Graphics/Texture.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Graphics/Vertex.h>
#include<GameLib/Graphics/VertexBuffer.h>
#include<tchar.h>
#include<GameLib/GameLib.h>
#include<GameLib/Math/Matrix44.h>
#include<GameLib/Math/Matrix34.h>
#include"helper/MyOutputDebugString.h"
#include<assert.h>

#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/IndexBuffer.h>

#include<GameLib/Input/Keyboard.h>
#include<GameLib/Scene/PrimitiveRenderer.h>
#include<GameLib/Input/Manager.h>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#endif//SAFE_RELEASE


class DxCube{
public:
	DxCube()
		: mVb(0), mIb(0), mTexture(0)
	{
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();

		HRESULT hr=0;
		IDirect3DDevice9 *pDevice = m.dxDevice();

		using GameLib::Graphics::Vertex;
		const int vertexCount = 8;
		const DWORD fvf = (D3DFVF_XYZW | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		//--------------頂点バッファを作る-----------------------
		// 頂点配列をコピー
		pDevice->CreateVertexBuffer(
			sizeof(Vertex)*vertexCount, 0, 
			fvf, D3DPOOL_SYSTEMMEM,
			&mVb, NULL);
		void* vb;
		mVb->Lock( 0, 0, &vb, 0 );
		Vertex* v = reinterpret_cast<Vertex*>(vb); //書き込みポインタを得る
		//位置を入れる
		v[ 0 ].mPosition.set( -10.f, -10.f, -10.f );
		v[ 1 ].mPosition.set( -10.f, -10.f, 10.f );
		v[ 2 ].mPosition.set( -10.f, 10.f, -10.f );
		v[ 3 ].mPosition.set( -10.f, 10.f, 10.f );
		v[ 4 ].mPosition.set( 10.f, -10.f, -10.f );
		v[ 5 ].mPosition.set( 10.f, -10.f, 10.f );
		v[ 6 ].mPosition.set( 10.f, 10.f, -10.f );
		v[ 7 ].mPosition.set( 10.f, 10.f, 10.f );
		//法線を入れる。斜めに出ている法線にしてみる。長さはだいたい1
		v[ 0 ].mNormal.set( -0.57f, -0.57f, -0.57f );
		v[ 1 ].mNormal.set( -0.57f, -0.57f, 0.57f );
		v[ 2 ].mNormal.set( -0.57f, 0.57f, -0.57f );
		v[ 3 ].mNormal.set( -0.57f, 0.57f, 0.57f );
		v[ 4 ].mNormal.set( 0.57f, -0.57f, -0.57f );
		v[ 5 ].mNormal.set( 0.57f, -0.57f, 0.57f );
		v[ 6 ].mNormal.set( 0.57f, 0.57f, -0.57f );
		v[ 7 ].mNormal.set( 0.57f, 0.57f, 0.57f );

		//頂点カラーを入れる(ライティングの効果を見たいので真っ白
		for ( int i = 0; i < 8; ++i ){
			v[ i ].mColor = 0xffffffff;
		}
		//テクスチャ座標を入れる(適当)
		v[ 0 ].mUv.set( 0.f, 0.f );
		v[ 1 ].mUv.set( 0.f, 1.f );
		v[ 2 ].mUv.set( 1.f, 0.f );
		v[ 3 ].mUv.set( 1.f, 1.f );
		v[ 4 ].mUv.set( 0.f, 0.f );
		v[ 5 ].mUv.set( 0.f, 1.f );
		v[ 6 ].mUv.set( 1.f, 0.f );
		v[ 7 ].mUv.set( 1.f, 1.f );
		//書き終わったら閉じる
		mVb->Unlock();;

		//-------------インデクスバッファを作る--------------------
		//3インデクスで三角形一つなので、インデクスバッファのサイズは普通3の倍数になる
		pDevice->CreateIndexBuffer(
			sizeof(unsigned short)*36, 0, 
			D3DFMT_INDEX16, D3DPOOL_MANAGED, 
			&mIb, NULL);
		unsigned short indices[ 36 ] = {
			0, 1, 3, 3, 2, 0,
			4, 6, 7, 7, 5, 4,
			0, 4, 5, 5, 1, 0,
			2, 3, 7, 7, 6, 2,
			7, 3, 1, 1, 5, 7,
			2, 6, 4, 4, 0, 2,
		};
		unsigned short* iBuffer;
		void *ib;
		mIb->Lock( 0, 0, &ib, 0 );
		iBuffer = reinterpret_cast<unsigned short*>(ib);
		for ( int i = 0; i < 36; ++i ){
			iBuffer[ i ] = indices[ i ];
		}
		mIb->Unlock();

		//textur作成
		//D3DXHANDLE handle = pEffect->GetAnnotation( "Town_Tex", 0 );
		//handle = pEffect->GetAnnotationByName( "Town_Tex", "ResourceName" );//ok
		//const char *pName;
		//pEffect->GetString( handle, &pName );
		//mTexture = Texture::create( pName );
		//while( !gDrawCubeTexture.isReady() ){}

	}
	~DxCube(){
		SAFE_RELEASE(mVb);
		SAFE_RELEASE(mIb);
	}

	void draw(){
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
		GameLib::Graphics::VertexBuffer vb = GameLib::Graphics::VertexBuffer::create( 1 );
		m.setVertexBuffer(vb);
		//ダミーを送る
		m.draw( 0, 0 );
		
		HRESULT hr;
		IDirect3DDevice9 *pDevice = m.dxDevice();

		//頂点、インデックス、テクスチャセット
		hr = pDevice->SetStreamSource( 0, mVb, 0, sizeof(GameLib::Graphics::Vertex) ); //Strideきめうち
		assert(SUCCEEDED(hr));
		hr = pDevice->SetIndices( mIb );
		assert(SUCCEEDED(hr));
		hr = pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12 ); 
		assert(SUCCEEDED(hr));
	}

	IDirect3DVertexBuffer9* mVb;
	IDirect3DIndexBuffer9* mIb;
	GameLib::Graphics::Texture mTexture;

};

class DxRectangle {
public:
	
	DxRectangle()
		: mVb(0)
	{
		using namespace GameLib;
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();

		HRESULT hr=0;
		IDirect3DDevice9 *pDevice = m.dxDevice();

		using GameLib::Graphics::Vertex;
		const int vertexCount = 6;
		const DWORD fvf = (D3DFVF_XYZW | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		//--------------頂点バッファを作る-----------------------
		// 頂点配列をコピー
		pDevice->CreateVertexBuffer(
			sizeof(Vertex)*vertexCount, 0, 
			fvf, D3DPOOL_SYSTEMMEM,
			&mVb, NULL);
		void* vb;
		mVb->Lock( 0, 0, &vb, 0 );
		Vertex* v = reinterpret_cast<Vertex*>(vb); //書き込みポインタを得る
		
		unsigned int c=0xffffffff;
		float depth=0.f;
		int w,h;
		m.getViewport( 0, 0, &w, &h );
		Vector2 p0(0,0), p1(static_cast<float>(w), static_cast<float>(h));
		Vector2 t0(0,0), t1(1,1);

		for ( int i = 0; i < 6; ++i ){
			v[ i ].mColor = c;
			v[ i ].mNormal = 0.f;
		}

		//位置を入れる
		v[ 0 ].mPosition.set( p0.x, p0.y, depth );
		v[ 0 ].mUv.set( t0.x, t0.y );
		v[ 1 ].mPosition.set( p0.x, p1.y, depth );
		v[ 1 ].mUv.set( t0.x, t1.y );
		v[ 2 ].mPosition.set( p1.x, p0.y, depth );
		v[ 2 ].mUv.set( t1.x, t0.y );

		v[ 3 ].mPosition.set( p1.x, p0.y, depth );
		v[ 3 ].mUv.set( t1.x, t0.y );
		v[ 4 ].mPosition.set( p0.x, p1.y, depth );
		v[ 4 ].mUv.set( t0.x, t1.y );
		v[ 5 ].mPosition.set( p1.x, p1.y, depth );
		v[ 5 ].mUv.set( t1.x, t1.y );
		
		//書き終わったら閉じる
		mVb->Unlock();

	}
	~DxRectangle(){
		SAFE_RELEASE(mVb);

	}
	void draw(){
		using namespace GameLib::Graphics;
		using namespace GameLib;
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
		//初期値をセットして回る。
		//テクスチャは初期化しない
		Matrix44 transform;
		transform.setIdentity();
		Matrix34 wm;
		wm.setIdentity();
		bool depthWrite = true;
		bool depthTest = false;
		BlendMode blendMode = BLEND_OPAQUE;
		CullMode cullMode = CULL_NONE;
		m.setProjectionViewMatrix( transform );
		m.setWorldMatrix( wm );
		//m.setTexture( mTexture );
		m.enableDepthWrite( depthWrite );
		m.enableDepthTest( depthTest );
		m.setBlendMode( blendMode );
		m.setCullMode( cullMode );
		m.setDiffuseColor( Vector3( 1.f, 1.f, 1.f ) );
		m.setLightingMode( LIGHTING_NONE );
		m.enableVertexBlend(false);
		//スクリーン座標->クリップ空間変換行列
		Matrix44 screenToClipTransform;
		int width;
		int height;
		m.getViewport( 0, 0, &width, &height );
		screenToClipTransform.setOrthogonalTransform(
			0.f, static_cast< float >( width ), 
			static_cast< float >( height ), 0.f, //下、上の順で、下はheight,上は0であることに注意
			0.f, 1.f );
		m.setProjectionViewMatrix(screenToClipTransform);
		
		GameLib::Graphics::VertexBuffer vb = GameLib::Graphics::VertexBuffer::create( 1 );
		m.setVertexBuffer(vb);
		
		//デバイスに送るためのダミーのドロー
		m.draw( 0, 0 );

		HRESULT hr;
		IDirect3DDevice9 *pDevice = m.dxDevice();
		//頂点、インデックス、テクスチャセット
		hr = pDevice->SetStreamSource( 0, mVb, 0, sizeof(GameLib::Graphics::Vertex) ); //Strideきめうち
		assert(SUCCEEDED(hr));
		hr = pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );
		assert(SUCCEEDED(hr));
	}

	IDirect3DVertexBuffer9* mVb;
};

class DxAnimRectangle {
public:
	
	DxAnimRectangle()
		: mVb(0), mTexture(0)
	{
		using namespace GameLib;
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();

		HRESULT hr;
		IDirect3DDevice9 *pDevice = m.dxDevice();

		using GameLib::Graphics::Vertex;
		const int vertexCount = 6;
		const DWORD fvf = (D3DFVF_XYZW | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		//--------------頂点バッファを作る-----------------------
		// 頂点配列をコピー
		pDevice->CreateVertexBuffer(
			sizeof(Vertex)*vertexCount, 0, 
			fvf, D3DPOOL_SYSTEMMEM,
			&mVb, NULL);
		void* vb;
		mVb->Lock( 0, 0, &vb, 0 );
		Vertex* v = reinterpret_cast<Vertex*>(vb); //書き込みポインタを得る
		
		unsigned int c=0xffffffff;
		float depth=0.f;
		int w,h;
		m.getViewport( 0, 0, &w, &h );
		Vector2 p0(0,0), p1(static_cast<float>(w), static_cast<float>(h));
		Vector2 t0(0,0), t1(1,1);

		for ( int i = 0; i < 6; ++i ){
			v[ i ].mColor = c;
			v[ i ].mNormal = 0.f;
		}

		//位置を入れる
		v[ 0 ].mPosition.set( p0.x, p0.y, depth );
		v[ 0 ].mUv.set( t0.x, t0.y );
		v[ 1 ].mPosition.set( p0.x, p1.y, depth );
		v[ 1 ].mUv.set( t0.x, t1.y );
		v[ 2 ].mPosition.set( p1.x, p0.y, depth );
		v[ 2 ].mUv.set( t1.x, t0.y );

		v[ 3 ].mPosition.set( p1.x, p0.y, depth );
		v[ 3 ].mUv.set( t1.x, t0.y );
		v[ 4 ].mPosition.set( p0.x, p1.y, depth );
		v[ 4 ].mUv.set( t0.x, t1.y );
		v[ 5 ].mPosition.set( p1.x, p1.y, depth );
		v[ 5 ].mUv.set( t1.x, t1.y );
		
		//書き終わったら閉じる
		mVb->Unlock();

		hr=D3DXCreateTextureFromFileA( pDevice, "shader/movie7.png", &mTexture );
		assert(SUCCEEDED(hr));

		D3DSURFACE_DESC desc;

		mTexture->GetLevelDesc( 0, &desc );
		//TRACE1("", desc.Type);
		//desc.
		
	}
	~DxAnimRectangle(){
		SAFE_RELEASE(mVb);
		SAFE_RELEASE(mTexture);

	}
	void draw(){
		using namespace GameLib::Graphics;
		using namespace GameLib;
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
		//初期値をセットして回る。
		//テクスチャは初期化しない
		Matrix44 transform;
		transform.setIdentity();
		Matrix34 wm;
		wm.setIdentity();
		bool depthWrite = true;
		bool depthTest = false;
		BlendMode blendMode = BLEND_OPAQUE;
		CullMode cullMode = CULL_NONE;
		m.setProjectionViewMatrix( transform );
		m.setWorldMatrix( wm );
		//m.setTexture( mTexture );
		m.enableDepthWrite( depthWrite );
		m.enableDepthTest( depthTest );
		m.setBlendMode( blendMode );
		m.setCullMode( cullMode );
		m.setDiffuseColor( Vector3( 1.f, 1.f, 1.f ) );
		m.setLightingMode( LIGHTING_NONE );
		m.enableVertexBlend(false);
		//スクリーン座標->クリップ空間変換行列
		Matrix44 screenToClipTransform;
		int width;
		int height;
		m.getViewport( 0, 0, &width, &height );
		screenToClipTransform.setOrthogonalTransform(
			0.f, static_cast< float >( width ), 
			static_cast< float >( height ), 0.f, //下、上の順で、下はheight,上は0であることに注意
			0.f, 1.f );
		m.setProjectionViewMatrix(screenToClipTransform);
		
		GameLib::Graphics::VertexBuffer vb = GameLib::Graphics::VertexBuffer::create( 1 );
		m.setVertexBuffer(vb);
		
		//デバイスに送るためのダミーのドロー
		m.draw( 0, 0 );

		HRESULT hr;
		IDirect3DDevice9 *pDevice = m.dxDevice();
		pDevice->SetTexture( 0, mTexture );
		//頂点、インデックス、テクスチャセット
		hr = pDevice->SetStreamSource( 0, mVb, 0, sizeof(GameLib::Graphics::Vertex) ); //Strideきめうち
		assert(SUCCEEDED(hr));
		hr = pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );
		assert(SUCCEEDED(hr));
	}

	IDirect3DVertexBuffer9* mVb;
	LPDIRECT3DTEXTURE9 mTexture;	
};

class DxEffect {
public:
	DxEffect(LPCWSTR filename ) 
		: mEffect(0)
	{
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();

		HRESULT hr;
		IDirect3DDevice9 *pDevice = m.dxDevice();

		//バージョンいくつに対応してるか
		D3DCAPS9 caps;
		pDevice->GetDeviceCaps(&caps);

		if ( ( caps.VertexShaderVersion < D3DVS_VERSION(3,0) ) ||
			( caps.PixelShaderVersion < D3DPS_VERSION(3,0)  ) ) {
				::MessageBox(NULL,_T("プログラマブルシェーダの機能に対応していません。"),_T(""),MB_OK);
		}

		LPD3DXBUFFER pCompilationErrors;
		hr=D3DXCreateEffectFromFile(
			pDevice,
			filename,
			NULL,
			NULL,
			0,
			NULL,
			&mEffect,
			&pCompilationErrors );
		assert(SUCCEEDED(hr));
		if(pCompilationErrors){
			const char* p= (const char*)pCompilationErrors->GetBufferPointer();
			OutputDebugStringA( p );
			//OutputDebugString( p );
			pCompilationErrors->Release();
			return;
		}
	}
	~DxEffect(){
		SAFE_RELEASE(mEffect);
	}
	ID3DXEffect *mEffect;
};



namespace {
	using namespace GameLib::Graphics;
	using namespace GameLib::Scene;
	PrimitiveRenderer *gRender = NULL;
	VertexBuffer gVertexBuffer;
	IndexBuffer gIndexBuffer;
	class Dx{
	public:
		Dx() :
		mBackBuffer(NULL),
		mZBuffer(NULL),
		mTextureZBuffer(NULL),
		mTexture(NULL)
		{
			IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
			GameLib::Framework fw = GameLib::Framework::instance();
			
			//レンダリングターゲットになるテクスチャオブジェクトの作成
			if( FAILED(
					D3DXCreateTexture(
					pDevice,
					fw.width(), fw.height(),
					0,
					D3DUSAGE_RENDERTARGET,
					D3DFMT_A8R8G8B8,
					D3DPOOL_DEFAULT,
					&mTexture )
				)
			){
			
				assert( false && "テクスチャの作成に失敗しました");
			}

			//テクスチャをレンダリングターゲットにする際のZバッファを作成
			D3DSURFACE_DESC desc;
			mTexture->GetLevelDesc(0,&desc);
			if(
				FAILED(
					pDevice->CreateDepthStencilSurface(
						desc.Width,desc.Height,
						D3DFMT_D16,D3DMULTISAMPLE_NONE,
						0,
						TRUE,
						&mTextureZBuffer,
						NULL )
				)
			) {
				assert( false && "テクスチャ用のZバッファ作成に失敗しました");	
			}
		}
		~Dx(){
			SAFE_RELEASE( mBackBuffer );
			SAFE_RELEASE( mZBuffer );
			SAFE_RELEASE( mTextureZBuffer );
			mTexture = 0;
		}

		// シーンのレンダリング レンダリング先は”テクスチャに変更
		void preDraw(){
			HRESULT hr;
			IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();

			//通常時のバックバッファ、Ｚバッファを保存していく（後でもとのレンダリングターゲットに戻す際に必要）			
			hr=pDevice->GetRenderTarget(0, &mBackBuffer);			
			assert(SUCCEEDED(hr));
			hr=pDevice->GetDepthStencilSurface(&mZBuffer);
			assert(SUCCEEDED(hr));
			//レンダリングターゲットをテクスチャにセット
			LPDIRECT3DSURFACE9 pSurf = NULL;
			hr=mTexture->GetSurfaceLevel(0,&pSurf);		 
			assert(SUCCEEDED(hr));
			hr=pDevice->SetRenderTarget(0,pSurf );				
			assert(SUCCEEDED(hr));
			hr=pDevice->SetDepthStencilSurface(mTextureZBuffer);
			assert(SUCCEEDED(hr));
			SAFE_RELEASE(pSurf);

			hr=pDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,
				D3DCOLOR_XRGB(0,0,200), 1.0f, 0 );
			assert(SUCCEEDED(hr));
		}

		//テクスチャのレンダリング　レンダリング先は”バックバッファ”に変更		 
		void postDraw(){
			IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();

			HRESULT hr;

			//レンダリングターゲットを元に戻す（バックバッファに戻す）
			hr=pDevice->SetRenderTarget(0,mBackBuffer );
			assert(SUCCEEDED(hr));
			hr=pDevice->SetDepthStencilSurface(mZBuffer);		
			assert(SUCCEEDED(hr));
			SAFE_RELEASE(mBackBuffer);
			SAFE_RELEASE(mZBuffer);

			//pDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,
			//	D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
			
			//pDevice->SetTexture(0, mTexture.dxTeture());
		}
		

		LPDIRECT3DSURFACE9 mBackBuffer;
		LPDIRECT3DSURFACE9 mZBuffer;
		LPDIRECT3DSURFACE9 mTextureZBuffer;
		LPDIRECT3DTEXTURE9 mTexture;
	};

	void changeLightMode(){
		using namespace GameLib::Graphics;
		Manager m;
		static LightingMode sMode=LIGHTING_NONE;
		//以下はスペースキーでライティングを切り替えるコード。
		if ( GameLib::Input::Manager::instance().keyboard().isTriggered( ' ' ) ){
			if (  sMode== LIGHTING_NONE ){
				sMode=LIGHTING_PER_VERTEX;
			}else if ( sMode == LIGHTING_PER_VERTEX ){
				sMode=LIGHTING_PER_PIXEL;

			}else if ( sMode == LIGHTING_PER_PIXEL ){
				sMode=LIGHTING_NONE;
			}
		}
		m.setLightingMode( sMode );

	}

} // end namespace anonymous
