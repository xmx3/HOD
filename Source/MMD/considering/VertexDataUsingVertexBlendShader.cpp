#include"VertexDataUsingVertexBlendShader.h"
#include"Pmd.h"
#include"Model.h"
#include"Face.h"
#include"Bone.h"
#include <GameLib/Graphics/Manager.h>
#include <assert.h>
#include <boost/lexical_cast.hpp>
#include <GameLib/Graphics/Vertex.h>
#include <string>
#include <GameLib/GameLib.h>
#include <GameLib/Graphics/Enum.h>
#include <GameLib/Math/Vector4.h>
#include <GameLib/Graphics/IndexBuffer.h>
#include <GameLib/Graphics/VertexBuffer.h>
#include <GameLib/Graphics/Texture.h>
#include "helper/MyOutputDebugString.h"
#include <tchar.h>
#include <set>


using namespace GameLib::Graphics;
using namespace GameLib::Math;
#define MODEL_BLEND_COUNT 2

struct ORIGINAL_VERTEX {
	D3DXVECTOR4 pos;
	D3DXVECTOR3 normal;
	unsigned color; //頂点色
	D3DXVECTOR2 uv;
	float weight[MODEL_BLEND_COUNT];
	unsigned short index[MODEL_BLEND_COUNT];//影響するボーンのインデックス

};
#define ORIGINAL_FVF (D3DFVF_XYZB5|D3DFVF_LASTBETA_UBYTE4|D3DFVF_NORMAL|D3DFVF_TEX1)

VertexDataUsingVertexBlendShader::VertexDataUsingVertexBlendShader() 
	:originalVertexBuffer_(0), 
	vertexCount_(0),
	indexBuffer_(0)
{
}

VertexDataUsingVertexBlendShader::~VertexDataUsingVertexBlendShader() {
	SAFE_RELEASE(originalVertexBuffer_);
	SAFE_RELEASE(indexBuffer_);
}

const char* VertexDataUsingVertexBlendShader::load(const char *pData) {
	Manager m = Manager::instance();
	IDirect3DDevice9 *pDevice=m.dxDevice();
	//-----------------------------------------------------
	// 頂点数取得
	vertexCount_ = *( reinterpret_cast<const unsigned long *>(pData) );
	pData += sizeof( unsigned long );

	// 頂点配列をコピー
	pDevice->CreateVertexBuffer(
		sizeof(ORIGINAL_VERTEX)*vertexCount_, 0, 
		ORIGINAL_FVF, D3DPOOL_SYSTEMMEM,
		&originalVertexBuffer_, NULL);

	if (!originalVertexBuffer_ ) {
		assert(false && "頂点バッファの作成に失敗");
		return false;
	}
		
	void* vb;
	void* avb;
	originalVertexBuffer_->Lock(0, 0, &vb, 0);
	ORIGINAL_VERTEX* v=(ORIGINAL_VERTEX*)vb;
				
	for (unsigned long i=0; i<vertexCount_; ++i) {
		const PMD_VERTEX *pVertex = reinterpret_cast<const PMD_VERTEX *>(pData);
	
		v[i].pos.x=pVertex->x;
		v[i].pos.y=pVertex->y;
		v[i].pos.z=pVertex->z;
		v[i].pos.w=0.f;

		v[i].normal.x=pVertex->nx;
		v[i].normal.y=pVertex->ny;
		v[i].normal.z=pVertex->nz;
		//頂点カラーを入れる(ライティングの効果を見たいので真っ白
		//マテリアルで調整するので白で平気のはず
		v[i].color= 0xffffffff;
				

		for (unsigned long j=0; j<MODEL_BLEND_COUNT; j++) {
			v[i].index[j]=0;
			v[i].weight[j]=0.f;
		}
		v[i].weight[0]=static_cast<float>(pVertex->weight)/100.f;
		v[i].weight[1]=1.f-v[i].weight[0];

		v[i].index[0]=pVertex->bone[0];
		v[i].index[1]=pVertex->bone[1];

		v[i].uv.x=pVertex->u;
		v[i].uv.y=pVertex->v;
					
		pData += sizeof( PMD_VERTEX );
	}
	originalVertexBuffer_->Unlock();

	// 頂点インデックス数取得
	numIndices_ = *( reinterpret_cast<const unsigned long *>(pData) );
	pData += sizeof( unsigned long );
	
	pDevice->CreateIndexBuffer(
			sizeof(unsigned short)*numIndices_, 0, 
			D3DFMT_INDEX16, D3DPOOL_MANAGED, 
			&indexBuffer_, NULL);
		if (!indexBuffer_) {
			assert( false && "インデックスバッファの作成に失敗");
			return false;
		}

	void* ib;
	indexBuffer_->Lock(0, 0, &ib, 0);
	unsigned short *pIndeces=reinterpret_cast<unsigned short*>(ib);
	for( unsigned int i=0; i<numIndices_; ++i) {
		pIndeces[i]=*( reinterpret_cast<const unsigned short *>(pData) );
		pData += sizeof(unsigned short);
	}
	indexBuffer_->Unlock();

	return pData;
}

void VertexDataUsingVertexBlendShader::draw(
	const std::vector<CBone*> &bones,
	const std::vector<CModel::Subset*> &subsets,
	const std::vector<CModel::Material*> &materials )
{
	HRESULT hr;
	Manager m = Manager::instance();
	//ダミーのvertex(index)Bufferを送らないと更新されない可能性があるので送る
	
	//・理由
	//描画してるのが一個だけの場合や
	//obj1->draw();
	//VertexDataUsingVertexBlendShader.draw();
	//obj1->draw
	//のように同じオブジェクト(同じVertexBufferが使われている)間にこの関数が入っていると上手くいかない。
	//理由はmanagerImpl内でこのように処理されてるので上手く処理されない
	//void setVertexBuffer( VertexBuffer::Impl* o ){
	//	if ( mCurrentVertexBuffer == o ){
	//		return;
	//	}
	//HRESULT hr;
	//	IDirect3DVertexBuffer9* dxObj = ( o ) ? o->mDxObject : 0;
	//	hr = mDevice->SetStreamSource( 0, dxObj, 0, sizeof( Vertex ) ); //Strideきめうち
	//
	//indexBufferやtetureも同様

	static VertexBuffer dummyVertices = VertexBuffer::create(1);
	static IndexBuffer dummyIndecies = IndexBuffer::create(1);
	static Texture dummyTexture = Texture::create(1, 1, false);
	m.setVertexBuffer(dummyVertices);
	m.setIndexBuffer(dummyIndecies);
	m.setTexture(dummyTexture);

	//ここで送ってもらえないデータをシェーダに送ってもらうために何も描画しないがdraw()を呼ぶ
	m.draw(0, 0);
	IDirect3DDevice9 *pDevice=m.dxDevice();
	// バッファ、FVF
	//pDevice->SetStreamSource(0, animatedVertexBuffer_, 0, sizeof(ANIMATED_VERTEX));
	pDevice->SetIndices(indexBuffer_);
	//pDevice->SetFVF(ANIMATED_FVF);
	// サブセットの描画
	for (unsigned int i=0; i<subsets.size(); ++i) {
		CModel::Subset* subset=subsets[i];
		// 色、テクスチャ
		unsigned long mi=subset->materialIndex_;
		CModel::Material *pMaterial = materials[mi];
		//GameLib::Graphics::ManagerImplのsendLightingParametersをコピペ
		//設計悪い。updateVertexが0.021s->0.017sぐらいまで高速化できるから妥協。
		//dxDevice()を作ったときにやりそうだと思ったが
		//ライト色は毎回強度と色を掛け合わせる。
		//Vector4 lc[ 4 ];
		//for ( int i = 0; i < 4; ++i ){
		//	lc[ i ].x = mLightColors[ i ].x * mLightIntensities[ i ];
		//	lc[ i ].y = mLightColors[ i ].y * mLightIntensities[ i ];
		//	lc[ i ].z = mLightColors[ i ].z * mLightIntensities[ i ];
		//	lc[ i ].w = 0.f;
		//}
		hr = pDevice->SetVertexShaderConstantF( 10, &pMaterial->material_.Diffuse.r, 1 );
		LightingMode lm=m.getLightingMode();
		STRONG_ASSERT( SUCCEEDED( hr ) && "SetVertexShaderConstantF : INVALID CALL" );
		if ( lm == LIGHTING_PER_PIXEL ){
			hr = pDevice->SetPixelShaderConstantF( 0, &pMaterial->material_.Ambient.r, 1 );
			STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetPixelShaderConstantF( 1, &mLightPositionXs.x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetPixelShaderConstantF( 2, &mLightPositionYs.x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetPixelShaderConstantF( 3, &mLightPositionZs.x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetPixelShaderConstantF( 4, &mEyePosition.x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
			//スペキュラ色は強度を調整2+e/2pi
			Vector4 sc;
			const float rcpPi2 = 1.f / ( 3.1415926535897932384626433832795f * 2.f );
			float f = ( 2.f + pMaterial->material_.Power ) * rcpPi2;
			sc.x = pMaterial->material_.Specular.r * f;
			sc.y = pMaterial->material_.Specular.g * f;
			sc.z = pMaterial->material_.Specular.b * f;
			//sc.w = pMaterial->material_.Specular.a;
			sc.w = pMaterial->material_.Power;

			hr = pDevice->SetPixelShaderConstantF( 5, &sc.x, 1 );
//			hr = pDevice->SetPixelShaderConstantF( 5, &pMaterial->material_.Specular.r, 1 );
			STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetPixelShaderConstantF( 6, &lc[ 0 ].x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetPixelShaderConstantF( 7, &lc[ 1 ].x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetPixelShaderConstantF( 8, &lc[ 2 ].x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetPixelShaderConstantF( 9, &lc[ 3 ].x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
			hr = pDevice->SetPixelShaderConstantF( 10, &pMaterial->material_.Emissive.r, 1 );
			STRONG_ASSERT( SUCCEEDED( hr ) && "SetPixelShaderConstantF : INVALID CALL" );
		}else if ( lm == LIGHTING_PER_VERTEX ){
			hr = pDevice->SetVertexShaderConstantF( 11, &pMaterial->material_.Ambient.r, 1 );
			STRONG_ASSERT( SUCCEEDED( hr ) && "SetVertexShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetVertexShaderConstantF( 12, &mLightPositionXs.x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetVertexShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetVertexShaderConstantF( 13, &mLightPositionYs.x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetVertexShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetVertexShaderConstantF( 14, &mLightPositionZs.x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetVertexShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetVertexShaderConstantF( 15, &lc[ 0 ].x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetVertexShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetVertexShaderConstantF( 16, &lc[ 1 ].x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetVertexShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetVertexShaderConstantF( 17, &lc[ 2 ].x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetVertexShaderConstantF : INVALID CALL" );
			//hr = pDevice->SetVertexShaderConstantF( 18, &lc[ 3 ].x, 1 );
			//STRONG_ASSERT( SUCCEEDED( hr ) && "SetVertexShaderConstantF : INVALID CALL" );
		}
		//pDevice->SetMaterial(&pMaterial->material_);
		if(pMaterial->texture_.isReady() ){
			pDevice->SetTexture(0, pMaterial->texture_.dxTeture() );
		}
		
		// 描画
		hr=pDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST, 0, 0, vertexCount_, 
			subset->faceIndex_*3, subset->faceCount_);
	}
}

void VertexDataUsingVertexBlendShader::updateFaceVertex(const std::vector<CFace*> &faces) {
	void* ovb;
	originalVertexBuffer_->Lock(0, 0, &ovb, 0);			
	ORIGINAL_VERTEX* ov=(ORIGINAL_VERTEX*)ovb;
	const CFace *pBase = faces[0];
	
	//baseで初期化
	for(unsigned int i=0, imax=pBase->vertices_.size(); i<imax; ++i) {
		ov[pBase->vertices_[i]->index_].pos.x=pBase->vertices_[i]->vec3_.x;
		ov[pBase->vertices_[i]->index_].pos.y=pBase->vertices_[i]->vec3_.y;
		ov[pBase->vertices_[i]->index_].pos.z=pBase->vertices_[i]->vec3_.z;
	}

	for( unsigned int i=1, imax=faces.size(); i<imax; ++i ) {
		const CFace *pFace = faces[i];
		if(pFace->weight_==0) continue;
		for( unsigned int j=0, jmax=pFace->vertices_.size(); j<jmax; ++j) {
			D3DXVECTOR3 vOut;
			D3DXVec3Lerp(
				&vOut,
				&( static_cast<D3DXVECTOR3>(ov[pFace->vertices_[j]->index_].pos) ) ,
				&(pFace->vertices_[j]->vec3_) ,
				pFace->weight_
			);
			ov[pFace->vertices_[j]->index_].pos.x=vOut.x;
			ov[pFace->vertices_[j]->index_].pos.y=vOut.y;
			ov[pFace->vertices_[j]->index_].pos.z=vOut.z;
		}
	}
	originalVertexBuffer_->Unlock();
}

