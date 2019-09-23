#ifndef __SHADER_H__
#define __SHADER_H__
#include<d3dx9.h>
#include<GameLib/GameLib.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Graphics/Vertex.h>
#include<GameLib/Graphics/Texture.h>
#include<assert.h>
#include<GameLib/Math/Matrix34.h>

#include "shader/FireParticleSystemVsGenerated.h"
#include "shader/simple.h"

#include<tchar.h>
#include"helper/MyOutputDebugString.h"

#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/IndexBuffer.h>
#include<GameLib/Scene/Container.h>
#include<GameLib/Scene/Model.h>

#include"shader/convertXFileFormat.h"
 
#include<GameLib/Framework.h>

#include<string>
using namespace GameLib::Math;
using namespace GameLib::Graphics;
using namespace GameLib::Scene;

extern int gCount;
extern Texture gTexture;

static void drawCube( D3DXVECTOR3 const &pos, float const radius=10.f, float const r=1.f, float const g=0.f, float const b=0.f, float const a=1.f ) {
	GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
	
	//shadertest------------------------------------
	HRESULT hr;
	IDirect3DDevice9 *pDevice = m.dxDevice();

	LPD3DXBUFFER pCompilationErrors;
	ID3DXEffect *g_pEffect;
	//hr=D3DXCreateEffect( m.dxDevice(), gSimpleFx, sizeof(gSimpleFx), NULL, NULL, 0, NULL, &g_pEffect, NULL);
	D3DXCreateEffectFromFile(
		pDevice,
		_T("shader/simple.fx"),
		NULL,
		NULL,
		0,
		NULL,
		&g_pEffect,
		&pCompilationErrors
	);
	if(pCompilationErrors){
		const char* p= (const char*)pCompilationErrors->GetBufferPointer();
		OutputDebugStringA( p );
		//OutputDebugString( p );
		pCompilationErrors->Release();
		return;
	} 
	D3DXHANDLE handle = g_pEffect->GetAnnotation( "Town_Tex", 0 );
	//handle = g_pEffect->GetAnnotationByName( "Town_Tex", "ResourceName" );//ok
	const char *pName;
	std::string filename("shader/");
	g_pEffect->GetString( handle, &pName );
	filename.append(pName);

	Texture texture = Texture::create( filename.c_str() );
	while( !texture.isReady() ){}
	g_pEffect->SetTexture( "Town_Tex", texture.dxTeture() ); 
	hr=g_pEffect->SetTechnique( "textured");
	UINT numPass;
	hr=g_pEffect->Begin( &numPass, 0 );
	hr=g_pEffect->BeginPass( 0 );
	{	
		
		IDirect3DVertexBuffer9* dxObj;

		using GameLib::Graphics::Vertex;
		const int vertexCount = 8;
		const DWORD fvf = (D3DFVF_XYZW | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		//--------------頂点バッファを作る-----------------------
		// 頂点配列をコピー
		pDevice->CreateVertexBuffer(
			sizeof(Vertex)*vertexCount, 0, 
			fvf, D3DPOOL_SYSTEMMEM,
			&dxObj, NULL);
		void* vb;
		dxObj->Lock( 0, 0, &vb, 0 );
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
	/*	v[ 0 ].mNormal.set( 0.f, 0.f, 0.f );
		v[ 1 ].mNormal.set( 0.f, 0.f, 0.f );
		v[ 2 ].mNormal.set( 0.f, 0.f, 0.f );
		v[ 3 ].mNormal.set( 0.f, 0.f, 0.f );
		v[ 4 ].mNormal.set( 0.f, 0.f, 0.f );
		v[ 5 ].mNormal.set( 0.f, 0.f, 0.f );
		v[ 6 ].mNormal.set( 0.f, 0.f, 0.f );
		v[ 7 ].mNormal.set( 0.f, 0.f, 0.f );
	*/
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
		dxObj->Unlock();;

		//-------------インデクスバッファを作る--------------------
		//3インデクスで三角形一つなので、インデクスバッファのサイズは普通3の倍数になる
		IDirect3DIndexBuffer9* dxIndecies;
		pDevice->CreateIndexBuffer(
				sizeof(unsigned short)*36, 0, 
				D3DFMT_INDEX16, D3DPOOL_MANAGED, 
				&dxIndecies, NULL);
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
		dxIndecies->Lock( 0, 0, &ib, 0 );
		iBuffer = reinterpret_cast<unsigned short*>(ib);
		for ( int i = 0; i < 36; ++i ){
			iBuffer[ i ] = indices[ i ];
		}
		dxIndecies->Unlock();

		HRESULT hr;
	
	
		//空Texture作成
		//GameLib::Graphics::Texture texture=0;
		//m.setTexture(gTexture);
		//アンビエントは地味に0.3くらいで
		Vector3 ambient( 0.3f, 0.3f, 0.3f );
		//後は物体側の特性。あまりじっても仕方ないので固定値で。いろいろいじって結果がどうなるか見てやろう
		Vector3 diffuseColor( 1.f, 1.f, 1.f );
		Vector3 specularColor( 1.f, 1.f, 1.f );
		//これを変えるとハイライトの鋭さが変わる。小さいほどざらざらした表面というイメージ
		float specularSharpness = 100.f;
		
		//ではライトの情報をセットしてやろう
		m.setAmbientColor( ambient );
		m.setDiffuseColor( diffuseColor );
		m.setSpecularColor( specularColor );
		m.setSpecularSharpness( specularSharpness );
		//ワールドトランスフォーム		
		Matrix34 w;
		w.setIdentity();
		w.setTranslation( pos.x, pos.y, pos.z );
		m.setWorldMatrix( w );
		m.setVertexBuffer( GameLib::Graphics::VertexBuffer::create(1) );
		m.draw(0, 0);

		//頂点、インデックス、テクスチャセット
		hr = pDevice->SetStreamSource( 0, dxObj, 0, sizeof(Vertex) ); //Strideきめうち
		hr = pDevice->SetIndices( dxIndecies );
		hr = pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 36, 0, 12 ); 
		SAFE_RELEASE(dxObj);
		SAFE_RELEASE(dxIndecies);
	}
	hr=g_pEffect->EndPass();
	hr=g_pEffect->End();
}
ID3DXEffect *g_pEffect=NULL;
static void drawFire( const D3DXMATRIX &world, const D3DXMATRIX &view, const D3DXMATRIX &projection ){
	GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
	
	//shadertest------------------------------------
	HRESULT hr;
	IDirect3DDevice9 *pDevice = m.dxDevice();
	if(!g_pEffect){
		LPD3DXBUFFER pCompilationErrors;
		//hr=D3DXCreateEffect( m.dxDevice(), gSimpleFx, sizeof(gSimpleFx), NULL, NULL, 0, NULL, &g_pEffect, NULL);
		hr=D3DXCreateEffectFromFile(
			pDevice,
			_T("shader/FireParticleSystem.fx"),
			NULL,
			NULL,
			0,
			NULL,
			&g_pEffect,
			&pCompilationErrors
		);
		if(pCompilationErrors){
			const char* p= (const char*)pCompilationErrors->GetBufferPointer();
			OutputDebugStringA( p );
			//OutputDebugString( p );
			pCompilationErrors->Release();
			return;
		}
		D3DXHANDLE handle = g_pEffect->GetAnnotation( "Flame_Tex", 0 );
		//handle = g_pEffect->GetAnnotationByName( "Town_Tex", "ResourceName" );//ok
		const char *pName;

		g_pEffect->GetString( handle, &pName );
		Texture texture = Texture::create( pName );
		while( !texture.isReady() ){}
		g_pEffect->SetTexture( "Flame_Tex", texture.dxTeture() ); 
		hr=g_pEffect->SetTechnique( "FireParticleSystem" );

	}
	
	D3DXMATRIX v,p;
	D3DXVECTOR3 eye( 
			0.f,
			0.f,
			-50.f);
	D3DXVECTOR3 at( 0.f, 5.f, 0.f );
	D3DXVECTOR3 up( 0.f, 1.f, 0.f ); //「上」を指定するベクタ。これをいじって横に傾ける。
		
	D3DXMatrixLookAtLH( &v, &eye, &at, &up );
	
			
	//D3DXMatrixPerspectiveRH( 
	//	&p,
	//	static_cast< float >( GameLib::Framework::instance().width() ),
	//	static_cast< float >( GameLib::Framework::instance().height() ),
	//	1.f,
	//	1000.f );

	D3DXMatrixPerspectiveFovLH( 
		&p,
		3.14f/4.f,
		static_cast< float >( GameLib::Framework::instance().width() ) / static_cast< float >( GameLib::Framework::instance().height() ),
		1.f,
		1000.f );
	D3DXMATRIX wv,wvp;
	//isRightHand?
	if(true){
		 wv = world * view;
		 wvp = wv*projection;
	}else{
		 wv = world * v;//lh
		 wvp = wv*p;//lh
	}
	hr=g_pEffect->SetMatrixTranspose("world_view_trans_matrix", &wv );
	hr=g_pEffect->SetMatrix( "world_view_proj_matrix", &wvp );
	hr=g_pEffect->SetFloat( "time_0_X", static_cast<float>(gCount) );


	
	
	UINT numPass;
	
	hr=g_pEffect->Begin( &numPass, 0 );
	hr=g_pEffect->BeginPass( 0 );
	{	
		//xFile 作成
		Dix::CNormalAllocHierarchy NAH;
		D3DXFRAME *pFrame = NULL;
		ID3DXAnimationController *pAnim = NULL;
		D3DXLoadMeshHierarchyFromX( _T("shader/FireParticleSystem.x"), D3DXMESH_MANAGED, pDevice, &NAH, NULL, &pFrame, &pAnim);
		
		DWORD size = pFrame->pFrameFirstChild->pMeshContainer->MeshData.pMesh->GetNumBytesPerVertex();
		LPDIRECT3DVERTEXBUFFER9 dxVertecies;
		pFrame->pFrameFirstChild->pMeshContainer->MeshData.pMesh->GetVertexBuffer( &dxVertecies );
		DWORD num = pFrame->pFrameFirstChild->pMeshContainer->MeshData.pMesh->GetNumVertices();
		//頂点、インデックス、テクスチャセット
		hr = pDevice->SetStreamSource( 0, dxVertecies, 0, size ); //Strideきめうち
		//hr = pDevice->SetIndices( dxIndecies );
		hr = pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, num/3 ); 
		SAFE_RELEASE(pAnim);
		//SAFE_RELEASE(dxIndecies);
	}
	hr=g_pEffect->EndPass();
	hr=g_pEffect->End();

}

void convert(){
	GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
	
	IDirect3DDevice9 *pDevice = m.dxDevice();

	bool result = Dix::convertXFileFormat( pDevice, _T("shader/FireParticleSystem.x"), _T("shader/FireParticleSystem.x.txt"), D3DXF_FILEFORMAT_TEXT  );

}

#endif