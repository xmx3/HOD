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
#include<GameLib/Math/Matrix33.h>
#include"helper/MyOutputDebugString.h"
#include<assert.h>
#include<GameLib/Graphics/AnimatedVertexBoneBuffer.h>
#include<GameLib/Graphics/AnimatedVertexBone.h>
#include<GameLib/Graphics/IndexBuffer.h>
#include<GameLib/Input/Manager.h>
#include<GameLib/Input/Keyboard.h>

#include <boost/timer.hpp>
#include <boost/lexical_cast.hpp>

#include<GameLib/Framework.h>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#endif//SAFE_RELEASE



class DxEffectCube{
public:
	DxEffectCube()
		: mDxVb(0), 
		mDxIb(0),
		mDxTexture(0),
		mEffect(0),
		mLightingMode(GameLib::Graphics::LIGHTING_NONE)
	{
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();

		HRESULT hr=0;
		IDirect3DDevice9 *pDevice = m.dxDevice();

		using GameLib::Graphics::Vertex;
		const int vertexCount = 8;
		{
			const DWORD fvf = (D3DFVF_XYZW | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
			//--------------頂点バッファを作る-----------------------
			// 頂点配列をコピー
			pDevice->CreateVertexBuffer(
				sizeof(Vertex)*vertexCount, 0, 
				fvf, D3DPOOL_SYSTEMMEM,
				&mDxVb, NULL);
			void* vb;
			mDxVb->Lock( 0, 0, &vb, 0 );
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
			mDxVb->Unlock();

			//-------------インデクスバッファを作る--------------------
			//3インデクスで三角形一つなので、インデクスバッファのサイズは普通3の倍数になる
			pDevice->CreateIndexBuffer(
				sizeof(unsigned short)*36, 0, 
				D3DFMT_INDEX16, D3DPOOL_MANAGED, 
				&mDxIb, NULL);
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
			mDxIb->Lock( 0, 0, &ib, 0 );
			iBuffer = reinterpret_cast<unsigned short*>(ib);
			for ( int i = 0; i < 36; ++i ){
				iBuffer[ i ] = indices[ i ];
			}
			mDxIb->Unlock();
		}
		mAvb = GameLib::Graphics::AnimatedVertexBoneBuffer::create( vertexCount );
		GameLib::Graphics::AnimatedVertexBone *av = mAvb.lock();
		//ModelBlend
		for( int i=0; i<vertexCount; ++i ){
			av[i].mIndices[0] = 1;
			av[i].mIndices[1] = 0;
			av[i].mIndices[2] = 1;
			av[i].mIndices[3] = 1;
			
			av[i].mWeights[0] = 1.f;
			av[i].mWeights[1] = 0.f;
			av[i].mWeights[2] = 0.f;
			av[i].mWeights[3] = 0.f;
		}
		mAvb.unlock(&av);
		
		{
			using namespace GameLib::Graphics;
			mVb = VertexBuffer::create( vertexCount );
			Vertex* v = mVb.lock();
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
			mVb.unlock(&v);

			mIb = IndexBuffer::create( 36 );
			unsigned short* iBuffer = mIb.lock();

			unsigned short indices[ 36 ] = {
				0, 1, 3, 3, 2, 0,
				4, 6, 7, 7, 5, 4,
				0, 4, 5, 5, 1, 0,
				2, 3, 7, 7, 6, 2,
				7, 3, 1, 1, 5, 7,
				2, 6, 4, 4, 0, 2,
			};
			for ( int i = 0; i < 36; ++i ){
				iBuffer[ i ] = indices[ i ];
			}
			mIb.unlock(&iBuffer);

		}



		hr=D3DXCreateTextureFromFileA( pDevice, "ShaderTest/town.dds", &mDxTexture );
		assert(SUCCEEDED(hr));
		mTex = GameLib::Graphics::Texture::create( "ShaderTest/town.dds" );
		while( !mTex.isReady() ){}
	}
	~DxEffectCube(){
		SAFE_RELEASE(mDxVb);
		SAFE_RELEASE(mDxIb);
		SAFE_RELEASE(mEffect);
	}

	void draw(){
		HRESULT hr;
		//hr=mEffect->SetTexture( 0, mTex.dxTeture() );
		//assert( SUCCEEDED( hr ) );

		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
		GameLib::Graphics::VertexBuffer vb = GameLib::Graphics::VertexBuffer::create( 1 );
		GameLib::Graphics::AnimatedVertexBoneBuffer avb = GameLib::Graphics::AnimatedVertexBoneBuffer::create( 3 );
		GameLib::Graphics::AnimatedVertexBone *av = avb.lock();		
		for( int i=0; i<3; ++i ){
			av[i].mIndices[0] = 1;
			av[i].mIndices[1] = 0;
			av[i].mIndices[2] = 1;
			av[i].mIndices[3] = 1;
			
			av[i].mWeights[0] = 1.f;
			av[i].mWeights[1] = 0.f;
			av[i].mWeights[2] = 0.f;
			av[i].mWeights[3] = 0.f;
		}
		avb.unlock(&av);
		GameLib::Graphics::IndexBuffer ib = GameLib::Graphics::IndexBuffer::create( 1 );
		GameLib::Matrix34 wa[2];
		GameLib::Matrix34 w;
		w.setIdentity();
		wa[0].setScaling(0);
		wa[1].setIdentity();
		//wa[1].setRotationZ(45);
		//wa[1].scale( 1.0, 0.5, 0.5 );

		m.setLightingMode( GameLib::Graphics::LIGHTING_PER_PIXEL );
		m.enableVertexBlend(true);
		
		hr=mEffect->Begin( 0, 0 );
		assert(SUCCEEDED(hr));
		hr=mEffect->BeginPass(0);
		assert(SUCCEEDED(hr));
		
		
		m.setVertexBuffer(vb);
		m.setAnimatedVertexBoneBuffer(mAvb);
		//m.setAnimatedVertexBoneBuffer(avb);
		m.setIndexBuffer(ib);
		//m.setTexture(0);
		unsigned int size=2;
		m.sendWorldMatrixArray( wa, size );
		//ダミーを送る
		m.drawIndexed( 0, 0 );
		
		IDirect3DDevice9 *pDevice = m.dxDevice();
		GameLib::Math::Matrix34 invTransposeMatArray[2];
		invTransposeMatArray[0] = wa[0];
		//invTransposeMatArray[0].setInverse(wa[0]);
		//invTransposeMatArray[0].transpose33();

		invTransposeMatArray[1].setInverse(wa[1]);
		invTransposeMatArray[1].transpose33();

		int invTransposeMatArraySize=2;
		//hr = pDevice->SetVertexShaderConstantF( 26, &invTransposeMatArray[0].m00, 3*invTransposeMatArraySize ); 

		//頂点、インデックス、テクスチャセット
		hr = pDevice->SetStreamSource( 0, mDxVb, 0, sizeof(GameLib::Graphics::Vertex) ); //Strideきめうち
		assert(SUCCEEDED(hr));
		//hr = pDevice->SetStreamSource( 1, 0, 0, sizeof(GameLib::Graphics::AnimatedVertexBoneBuffer) ); //Strideきめうち
		assert(SUCCEEDED(hr));
		hr = pDevice->SetIndices( mDxIb );
		assert(SUCCEEDED(hr));
		pDevice->SetTexture( 0, mDxTexture );
		hr = pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12 ); 
		assert(SUCCEEDED(hr));
		
		hr=mEffect->EndPass();
		assert(SUCCEEDED(hr));
		hr=mEffect->End();
		assert(SUCCEEDED(hr));
	}

	void drawNotUsingEffect(){
		HRESULT hr;
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
		GameLib::Graphics::VertexBuffer vb = GameLib::Graphics::VertexBuffer::create( 1 );
		GameLib::Graphics::AnimatedVertexBoneBuffer avb = GameLib::Graphics::AnimatedVertexBoneBuffer::create( 3 );
		GameLib::Graphics::AnimatedVertexBone *av = avb.lock();		
		for( int i=0; i<3; ++i ){
			av[i].mIndices[0] = 1;
			av[i].mIndices[1] = 0;
			av[i].mIndices[2] = 1;
			av[i].mIndices[3] = 1;
			
			av[i].mWeights[0] = 1.f;
			av[i].mWeights[1] = 0.f;
			av[i].mWeights[2] = 0.f;
			av[i].mWeights[3] = 0.f;
		}
		avb.unlock(&av);
		
		GameLib::Graphics::IndexBuffer ib = GameLib::Graphics::IndexBuffer::create( 1 );
		GameLib::Matrix34 wa[2];
		GameLib::Matrix34 w;
		w.setIdentity();
		wa[0].setScaling(0);
		wa[1].setIdentity();
		//wa[1].setRotationZ(45);
		w.setIdentity();
		m.setLightingMode( mLightingMode );
		m.enableVertexBlend(true);
		
		m.setVertexBuffer(vb);
		m.setAnimatedVertexBoneBuffer(mAvb);
		//m.setAnimatedVertexBoneBuffer(avb);
		m.setIndexBuffer(ib);
		//m.setTexture(0);
		unsigned int size=2;
		m.sendWorldMatrixArray( wa, size );
		//ダミーを送る
		m.drawIndexed( 0, 0 );
		
		IDirect3DDevice9 *pDevice = m.dxDevice();

		//頂点、インデックス、テクスチャセット
		hr = pDevice->SetStreamSource( 0, mDxVb, 0, sizeof(GameLib::Graphics::Vertex) ); //Strideきめうち
		assert(SUCCEEDED(hr));
		//hr = pDevice->SetStreamSource( 1, 0, 0, sizeof(GameLib::Graphics::AnimatedVertexBoneBuffer) ); //Strideきめうち
		assert(SUCCEEDED(hr));
		hr = pDevice->SetIndices( mDxIb );
		assert(SUCCEEDED(hr));
		pDevice->SetTexture( 0, mDxTexture );
		hr = pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12 ); 
		assert(SUCCEEDED(hr));
		using namespace GameLib::Graphics;
		//以下はスペースキーでライティングを切り替えるコード。
		if ( GameLib::Input::Manager::instance().keyboard().isTriggered( ' ' ) ){
			if ( mLightingMode == LIGHTING_NONE ){
				mLightingMode = LIGHTING_PER_VERTEX;
			}else if ( mLightingMode == LIGHTING_PER_VERTEX ){
				mLightingMode = LIGHTING_PER_PIXEL;
			}else if ( mLightingMode == LIGHTING_PER_PIXEL ){
				mLightingMode = LIGHTING_NONE;
			}
		}
	}

	void init(){
		//バージョンいくつに対応してるか
		
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();

		HRESULT hr=0;
		IDirect3DDevice9 *pDevice = m.dxDevice();

		D3DCAPS9 caps;
		pDevice->GetDeviceCaps(&caps);

		if ( ( caps.VertexShaderVersion < D3DVS_VERSION(3,0) ) ||
			( caps.PixelShaderVersion < D3DPS_VERSION(3,0)  ) ) {
				::MessageBox(NULL,_T("プログラマブルシェーダの機能に対応していません。"),_T(""),MB_OK);
		}
		{
			//const char *filename = "ShaderTest/redCube.fx";
			const char *filename = "ShaderTest/redCubeVertexBlendPs.fx";
			//const char *filename = "ShaderTest/redCubeLightingPs.fx";
			LPD3DXBUFFER pCompilationErrors;
			hr=D3DXCreateEffectFromFileA(
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


		{
			const char *filename = "ShaderTest/redCube.fx";
			LPD3DXBUFFER pCompilationErrors;
			hr=D3DXCreateEffectFromFileA(
				pDevice,
				filename,
				NULL,
				NULL,
				0,
				NULL,
				&mEffectNotVertexBlend,
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
		//D3DXHANDLE hTransform =  mEffect->GetParameterByName( 0, "gTransform" );
		//D3DXHANDLE hAmbient =  mEffect->GetParameterByName( 0, "gAmbient" );
		//assert( hTransform == hAmbient );
		
		return;
	}

	bool isError()const{
		return mEffect==0;
	}

	//切り替えにどのくらい時間がかかるか
	void test(){
		//HRESULT hr;
		using namespace boost;
		boost::timer t; // タイマーの開始
		for(int i=0; i<1000000; ++i ){
			mEffect->Begin( 0, 0 );
			mEffect->BeginPass(0);
			mEffect->EndPass();
			mEffect->End();
		}
		OutputDebugStringA( "1000000time : " );
		OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
		OutputDebugStringA( "\n" );
		t.restart();
		// 1000000time : 5.5460000038146973
		// 1000000time : 5.7420001029968262
		// 1000000time : 5.5960001945495605
		// 1000000time : 5.4489998817443848
		// 1000000time : 5.4510002136230469
		// 1000000time : 5.4580001831054687
		// 1000000time : 5.4429998397827148
		// 1000000time : 5.4539999961853027
		// 1000000time : 5.4169998168945313

	}

	//時間を計りたい
	void drawUsingVertexBlend(){
		using namespace boost;
		boost::timer t; // タイマーの開始
		
		HRESULT hr;
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
		IDirect3DDevice9 *pDevice = m.dxDevice();
		

		GameLib::Matrix34 wa[2];
		GameLib::Matrix34 w;
		w.setIdentity();
		//wa[0].scale(0);
		//wa[0].setIdentity();
		wa[1].setIdentity();
		wa[1].setScaling( 1.f/4.f );
		wa[0]=wa[1];
		//m.enableVertexBlend(false);
		
		hr=mEffect->Begin( 0, 0 );
		assert(SUCCEEDED(hr));
		hr=mEffect->BeginPass(0);
		assert(SUCCEEDED(hr));
		
		
		for(int i=0; i<100; ++i ){
			m.setVertexBuffer(mVb);
			m.setAnimatedVertexBoneBuffer(mAvb);
			m.setIndexBuffer(mIb);
			unsigned int size=2;
			m.sendWorldMatrixArray( wa, size );
			//ダミーを送る
			pDevice->SetTexture( 0, mDxTexture );
			//m.setTexture(mTex);

			m.drawIndexed( 0, 12 );
		
		}
		hr=mEffect->EndPass();
		assert(SUCCEEDED(hr));
		hr=mEffect->End();
		assert(SUCCEEDED(hr));
		OutputDebugStringA( "100time draw using Vertex blend : " );
		OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
		OutputDebugStringA( "\n" );
		t.restart();


	}

	//時間を計りたい
	void drawNotUsingVertexBlend(){
		using namespace boost;
		boost::timer t; // タイマーの開始
		
		HRESULT hr;
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
		IDirect3DDevice9 *pDevice = m.dxDevice();

		hr=mEffectNotVertexBlend->Begin( 0, 0 );
		assert(SUCCEEDED(hr));
		hr=mEffectNotVertexBlend->BeginPass(0);
		assert(SUCCEEDED(hr));
		
		
		for(int i=0; i<100; ++i ){
			m.setVertexBuffer(mVb);
			m.setAnimatedVertexBoneBuffer(mAvb);
			m.setIndexBuffer(mIb);
			//ダミーを送る
			pDevice->SetTexture( 0, mDxTexture );
			//m.setTexture(mTex);

			m.drawIndexed( 0, 12 );
		
		}
		
		hr=mEffectNotVertexBlend->EndPass();
		assert(SUCCEEDED(hr));
		hr=mEffectNotVertexBlend->End();
		assert(SUCCEEDED(hr));

		OutputDebugStringA( "100time draw not using Vertex blend : " );
		OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
		OutputDebugStringA( "\n" );
		t.restart();

	}

private:
	IDirect3DVertexBuffer9* mDxVb;
	IDirect3DIndexBuffer9* mDxIb;

	GameLib::Graphics::VertexBuffer mVb;
	GameLib::Graphics::IndexBuffer mIb;

	ID3DXEffect *mEffect;
	ID3DXEffect *mEffectNotVertexBlend;
	GameLib::Graphics::AnimatedVertexBoneBuffer mAvb;
	LPDIRECT3DTEXTURE9 mDxTexture;
	GameLib::Graphics::Texture mTex;
	GameLib::Graphics::LightingMode mLightingMode;
};