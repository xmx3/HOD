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
#include <GameLib/Graphics/Vertex.h>
#include <GameLib/Graphics/Texture.h>
#include "helper/MyOutputDebugString.h"
#include <tchar.h>
#include <numeric>



#include"SegaTypeHelper.h"
#include<GameLib/Framework.h>

using namespace GameLib::Graphics;
using namespace GameLib::Math;

ID3DXEffect*					VertexDataUsingVertexBlendShader::sEffect					=NULL;
IDirect3DVertexShader9*			VertexDataUsingVertexBlendShader::sVertexShader				=NULL;
IDirect3DPixelShader9*			VertexDataUsingVertexBlendShader::sPixelShader				=NULL;
IDirect3DVertexDeclaration9*	VertexDataUsingVertexBlendShader::sVertexDeclaration		=NULL;
LPD3DXCONSTANTTABLE             g_pConstantTable											= NULL;

namespace {

typedef VertexDataUsingVertexBlendShader::TypeBoneIndex TypeBoneIndex;
//(1,2,3,4), というのがあったとしたら
//(1,3) だったらtrueを返す
//(1,2,3,4,5) だったら falseを返す
//(6)　はないので　falseを返す
bool do_a_have_b( 
	const std::set<TypeBoneIndex> &a,
	const std::set<TypeBoneIndex> &b );

//{ (1,2,3,4), (1,5), (6,7,9) } というのがあったとしたら
//(1,3)だったら0を返す
//(5,)だったら 1を返す
//((4,6,7)　はないので　-1を返す
int whichGroup(
	const std::set< std::set<TypeBoneIndex> > &patterns,
	const std::set<TypeBoneIndex> &pattern );

//含まれている重複した要素を取り除く
//{ (1,2,3,4),(1,3) } というのがあったとしたら (1,3) は　(1,2,3,4)　に含まれているので消す
void removeContainedDuplicateElement( std::set< std::set<TypeBoneIndex> > *elements );

}// end no namespace

struct VertexDataUsingVertexBlendShader::VERTEX {
	D3DXVECTOR4 mPosition;
	D3DXVECTOR3 mNormal;
	unsigned mColor; //頂点色
	D3DXVECTOR2 mUv;
};

struct VertexDataUsingVertexBlendShader::VERTEX_BONE {
	float mWeights[MODEL_BLEND_COUNT];
	TypeBoneIndex mIndices[MODEL_BLEND_COUNT];//影響するボーンのインデックス
	void operator=( const VERTEX_BONE &vbBone ){
		for( int i=0; i<MODEL_BLEND_COUNT; ++i ){
			mWeights[i] = vbBone.mWeights[i];
			mIndices[i] = vbBone.mIndices[i];
		}
	}
};



VertexDataUsingVertexBlendShader::VertexDataUsingVertexBlendShader() 
	:vertexBuffer_(0),
	vbBone_(0),
	numVertices_(0),
	indexBuffer_(0),
	usingBoneIndicesMap_(0),
	numGroups_(0),
	numIndeicesOfGroupInSubset_(0),
	numSubsets_(0),
	usingBoneIndexPatternOfGroupInSubset_(0)
{
	vertexBuffer_ = NEW GameLib::Graphics::VertexBuffer();
	indexBuffer_  = NEW GameLib::Graphics::IndexBuffer();
}

VertexDataUsingVertexBlendShader::~VertexDataUsingVertexBlendShader() {
	
	//後始末
	for ( int i=0; i<numSubsets_; ++i) {
		SAFE_DELETE_ARRAY( numIndeicesOfGroupInSubset_[i] );
		SAFE_DELETE_ARRAY( usingBoneIndexPatternOfGroupInSubset_[i] );
	}
	SAFE_DELETE_ARRAY( numIndeicesOfGroupInSubset_ ); 
	SAFE_DELETE_ARRAY( numGroups_ );
	
	SAFE_DELETE_ARRAY( usingBoneIndexPatternOfGroupInSubset_ );

	SAFE_DELETE(vertexBuffer_);
	SAFE_RELEASE(vbBone_);
	SAFE_DELETE(indexBuffer_);
	SAFE_DELETE_ARRAY( usingBoneIndicesMap_ );
}

const char* VertexDataUsingVertexBlendShader::load(const char *pData) {
	Manager m = Manager::instance();
	IDirect3DDevice9 *pDevice=m.dxDevice();
	//-----------------------------------------------------
	// 頂点数取得
	numVertices_ = *( reinterpret_cast<const unsigned long *>(pData) );
	pData += sizeof( unsigned long );

	// 頂点配列をコピー
	*vertexBuffer_ = GameLib::Graphics::VertexBuffer::create( numVertices_ );

	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_BONE)*numVertices_, 0, 
		0, D3DPOOL_SYSTEMMEM,
		&vbBone_, NULL);

	if (!vbBone_ ) {
		assert(false && "頂点バッファの作成に失敗");
		return false;
	}
		
	GameLib::Graphics::Vertex *v;
	VERTEX_BONE* vBone;
	v = vertexBuffer_->lock();
	vbBone_->Lock(0, 0, (void**)&vBone, 0);
				
	originalVertexBufferBone_.reserve(numVertices_);
	for (unsigned long i=0; i<numVertices_; ++i) {
		const PMD_VERTEX *pVertex = reinterpret_cast<const PMD_VERTEX *>(pData);
	
		v[i].mPosition.x=pVertex->x;
		v[i].mPosition.y=pVertex->y;
		v[i].mPosition.z=pVertex->z;
		v[i].mPosition.w=1.f;

		//TRACE3( "( %f, %f, %f )\n", v[i].mPosition.x, v[i].mPosition.y, v[i].mPosition.z );

		v[i].mNormal.x=pVertex->nx;
		v[i].mNormal.y=pVertex->ny;
		v[i].mNormal.z=pVertex->nz;
		//マテリアルで調整するので白で平気のはず
		v[i].mColor= 0xffffffff;
				

		for (unsigned long j=0; j<MODEL_BLEND_COUNT; j++) {
			vBone[i].mIndices[j]=(std::numeric_limits<TypeBoneIndex>::max)();
			vBone[i].mWeights[j]=0.f;
		}
		vBone[i].mWeights[0]=static_cast<float>(pVertex->weight)/100.f;
		vBone[i].mWeights[1]=1.f-vBone[i].mWeights[0];
		
		vBone[i].mIndices[0]=static_cast<TypeBoneIndex>(pVertex->bone[0]);
		vBone[i].mIndices[1]=static_cast<TypeBoneIndex>(pVertex->bone[1]);
		assert(pVertex->bone[0]<(std::numeric_limits<TypeBoneIndex>::max)() && "buffer over flow. charじゃ無理。");
		assert(pVertex->bone[1]<(std::numeric_limits<TypeBoneIndex>::max)() && "buffer over flow. charじゃ無理。");
		//TRACE2( "mWeights[2]: %f, %f\n", vBone[i].mWeights[0], vBone[i].mWeights[1] ); 
		//VERTEX_BONE *pvbBone;
		//pvbBone=&vBone[i];
		//assert( vBone[i].mWeights[0]!=0.f );



		originalVertexBufferBone_.push_back( BoneIndex( vBone[i].mIndices ) );

		v[i].mUv.x=pVertex->u;
		v[i].mUv.y=pVertex->v;
					
		pData += sizeof( PMD_VERTEX );
	}
	vbBone_->Unlock();
	vertexBuffer_->unlock(&v);

	// 頂点インデックス数取得
	numIndices_ = *( reinterpret_cast<const unsigned long *>(pData) );
	pData += sizeof( unsigned long );
	
	*indexBuffer_ = GameLib::Graphics::IndexBuffer::create( numIndices_ );

	unsigned short *ib;
	ib = indexBuffer_->lock();
	for( unsigned int i=0; i<numIndices_; ++i) {
		ib[i]=*( reinterpret_cast<const unsigned short *>(pData) );
		pData += sizeof(unsigned short);
	}
	indexBuffer_->unlock(&ib);

	initStaticObject();

	return pData;
}

void VertexDataUsingVertexBlendShader::draw(
	const std::vector<CBone*> &bones,
	const std::vector<CModel::Subset*> &subsets,
	const std::vector<CModel::Material*> &materials )
{
	HRESULT hr;
	Manager m = Manager::instance();
	IDirect3DDevice9 *pDevice=m.dxDevice();

	hr=pDevice->SetVertexShader( sVertexShader );
	assert( SUCCEEDED( hr ) );
	
	hr=pDevice->SetPixelShader( sPixelShader );
	assert( SUCCEEDED( hr ) );

	Matrix34 wm;
	wm.setIdentity();
	m.setWorldMatrix(wm);
	//カメラ行列ゲット
	Matrix44 pvm,pm;
	pm.setPerspectiveTransform( 45.f, 
		static_cast< float >( GameLib::Framework::instance().width() ),
		static_cast< float >( GameLib::Framework::instance().height() ),
		1.f,
		10000.f );
	Matrix34 vm;
		
	vm.setViewTransform( Vector3( 0, 0, -50 ), Vector3(0,0,0), Vector3(0,1,0) );
	pvm.setMul( pm, vm );
	m.setProjectionViewMatrix(pvm);
	m.setEyePosition( Vector3( 0, 0, -50 ) );
		

	//m.setCullMode(CULL_NONE);

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

	//static VertexBuffer dummyVertices = VertexBuffer::create(1);
	//static IndexBuffer dummyIndecies = IndexBuffer::create(1);
	//static Texture dummyTexture = Texture::create(1, 1, false);
	m.setVertexBuffer(*vertexBuffer_);
	m.setIndexBuffer(*indexBuffer_);
	m.setTexture(0);

	

	//ボーンのバーテックスバッファセット
	hr=pDevice->SetStreamSource(1, vbBone_, 0, sizeof(VERTEX_BONE));
	assert( SUCCEEDED( hr ) );

		
	D3DXMATRIX dxMat = toDxMatrix(pvm);
	hr=sEffect->SetMatrix("mViewProj", &dxMat );
	assert( SUCCEEDED( hr ) );
	//hr=g_pConstantTable->SetMatrix( pDevice, "mViewProj", &dxMat );
	hr=pDevice->SetVertexShaderConstantF( 50, &dxMat._11, 4 );  
	assert( SUCCEEDED( hr ) );

	


	unsigned long numFinishedIndices = 0;//書き終わったindexの数

	// サブセットの描画
	for (unsigned int subsetIdx=0; subsetIdx<subsets.size(); ++subsetIdx) {
		
		CModel::Subset* subset=subsets[subsetIdx];
		
		// 色、テクスチャ
		unsigned long mi=subset->materialIndex_;
		CModel::Material *pMaterial = materials[mi];
		
		pMaterial->material_.Diffuse;
		m.setDiffuseColor( Vector3( pMaterial->material_.Diffuse.r, pMaterial->material_.Diffuse.g, pMaterial->material_.Diffuse.b) );
		m.setTransparency( pMaterial->material_.Diffuse.a );
		LightingMode lm=m.getLightingMode();
		if ( lm == LIGHTING_PER_PIXEL ){
			m.setAmbientColor( Vector3( pMaterial->material_.Ambient.r, pMaterial->material_.Ambient.g, pMaterial->material_.Ambient.b) );
			m.setSpecularColor( Vector3( pMaterial->material_.Specular.r, pMaterial->material_.Specular.g, pMaterial->material_.Specular.b ) );
			m.setSpecularSharpness( pMaterial->material_.Power );
			m.setEmissionColor( Vector3( pMaterial->material_.Emissive.r, pMaterial->material_.Emissive.g, pMaterial->material_.Emissive.b) );
		}else if ( lm == LIGHTING_PER_VERTEX ){
			m.setAmbientColor( Vector3( pMaterial->material_.Ambient.r, pMaterial->material_.Ambient.g, pMaterial->material_.Ambient.b) );
		}
		m.setTexture( pMaterial->texture_ );

		for( int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ++groupIdx ){
			const int &numIndicesDrawn = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx];
			assert(numIndicesDrawn%3==0);
			
			// Set NumBones to select the correct vertex shader for the number of bones
			hr=sEffect->SetInt( "NumUsedBones", usingBoneIndexPatternOfGroupInSubset_[subsetIdx][groupIdx].size() );
			assert( SUCCEEDED( hr ) );
/*
            // Start the effect now all parameters have been updated
            UINT numPasses=1;
            hr=sEffect->Begin( &numPasses, 0 );
			assert( SUCCEEDED( hr ) );
			
			//if( FAILED(hr) ){
			//	if(hr==D3DERR_INVALIDCALL){
			//		TRACE0(_T("D3DERR_INVALIDCALL") );
			//	}
			//	else if(hr==D3DXERR_INVALIDDATA){
			//		TRACE0(_T("D3DXERR_INVALIDDATA") );
			//	}
			//}
			sendMatrixArrayToShader( bones, subsetIdx, groupIdx, numFinishedIndices );


			for( UINT iPass = 0; iPass < numPasses; iPass++ )
			{
				hr=sEffect->BeginPass( iPass );

				//ここでデータをシェーダに送ってもらうために何も描画しないがdraw()を呼ぶ
				//m.draw(0, 0);
				//m.sendLightingParameters()
				//m.sendMatrices();


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
					D3DPT_TRIANGLELIST, 0, 0, numVertices_, 
					numFinishedIndices, numIndicesDrawn/3 );
				assert( SUCCEEDED( hr ) );

				hr=sEffect->EndPass();
				assert( SUCCEEDED( hr ) );
			}
			hr=sEffect->End();
			assert( SUCCEEDED( hr ) );
*/
			hr = pDevice->SetVertexShaderConstantF( 10, &pMaterial->material_.Diffuse.r, 1 );

			//ここでデータをシェーダに送ってもらうために何も描画しないがdraw()を呼ぶ
			//m.draw(0, 0);
			//pDevice->SetVertexShaderConstantF( 0, &pvm.m00, 4 );
			pDevice->SetTexture(0, pMaterial->texture_.dxTeture() );
			sendMatrixArrayToShader( bones, subsetIdx, groupIdx, numFinishedIndices );

			D3DXMATRIX dxMatOut;
			hr=pDevice->GetVertexShaderConstantF( 50, &dxMatOut._11, 4 );  
			assert( SUCCEEDED( hr ) );
			assert( dxMat==dxMatOut );
			// 描画
			hr=pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST, 0, 0, numVertices_, 
				numFinishedIndices, numIndicesDrawn/3 );
			assert( SUCCEEDED( hr ) );

			numFinishedIndices += numIndicesDrawn;

		}
	}

	//ストリームを消しとく
	pDevice->SetStreamSource(1, 0, 0, 0);
}

void VertexDataUsingVertexBlendShader::updateFaceVertex(const std::vector<CFace*> &faces) {
	GameLib::Graphics::Vertex *vb;
	vb = vertexBuffer_->lock();			
	const CFace *pBase = faces[0];
	
	//baseで初期化
	for(unsigned int i=0, imax=pBase->vertices_.size(); i<imax; ++i) {
		vb[pBase->vertices_[i]->index_].mPosition.x=pBase->vertices_[i]->vec3_.x;
		vb[pBase->vertices_[i]->index_].mPosition.y=pBase->vertices_[i]->vec3_.y;
		vb[pBase->vertices_[i]->index_].mPosition.z=pBase->vertices_[i]->vec3_.z;
	}

	//i=0はベース。だから抜かす
	for( unsigned int i=1, imax=faces.size(); i<imax; ++i ) {
		const CFace *pFace = faces[i];
		if(pFace->weight_==0) continue;
		for( unsigned int j=0, jmax=pFace->vertices_.size(); j<jmax; ++j) {
			//D3DXVECTOR3 vOut;
			//D3DXVec3Lerp(
			//	&vOut,
			//	&( static_cast<D3DXVECTOR3>(vb[pFace->vertices_[j]->index_].mPosition) ) ,
			//	&(pFace->vertices_[j]->vec3_) ,
			//	pFace->weight_
			//);

			//線形補間 V1 + s(V2-V1)
			GameLib::Vector3 vOut;
			GameLib::Vector3 v = toVector3(pFace->vertices_[j]->vec3_);

			vOut.set(
				vb[pFace->vertices_[j]->index_].mPosition.x,
				vb[pFace->vertices_[j]->index_].mPosition.y,
				vb[pFace->vertices_[j]->index_].mPosition.z );
			v -= vOut;
			v *=pFace->weight_;
			vOut += v;

			vb[pFace->vertices_[j]->index_].mPosition.set( vOut.x, vOut.y, vOut.z, 1.0f );
		}
	}
	vertexBuffer_->unlock(&vb);
}

void VertexDataUsingVertexBlendShader::init( const std::vector<CModel::Subset*> &subsets ){
	//IndexBufferの並び替え
	Manager m = Manager::instance();
	IDirect3DDevice9 *pDevice=m.dxDevice();

	GameLib::Graphics::IndexBuffer tempIndexBuffer;
	tempIndexBuffer = GameLib::Graphics::IndexBuffer::create(numIndices_);
	
	VERTEX_BONE *vbBone;
	vbBone_->Lock(0, 0, (void**)&vbBone, D3DLOCK_READONLY);

	unsigned short* ib;
	ib = indexBuffer_->lock();
	
	unsigned short* tib;//tempIndexBuffer
	tib = tempIndexBuffer.lock();

	memcpy( tib, ib, sizeof(unsigned short)*numIndices_ );
#ifdef _DEBUG	
	for(unsigned int i=0; i<numIndices_; ++i ){
		assert( tib[i]==ib[i] );
	}
#endif//DEBUG
	
	numSubsets_ = subsets.size();
	//subset iにおけるグループの数
	numGroups_ = NEW int[subsets.size()];
	//subset iにおけるグループｊのインデックスの数
	numIndeicesOfGroupInSubset_ = NEW int*[subsets.size()];

	//subset idx における　三角形単位での使っているボーンインデックスのパターン
	usingBoneIndexPatternOfGroupInSubset_ = NEW std::set<TypeBoneIndex>*[numSubsets_];
	
	for (unsigned int i=0; i<subsets.size(); ++i) {
		CModel::Subset* subset=subsets[i];
		std::set< std::set<TypeBoneIndex> > patternsInSubset;
		for( unsigned int j=0; j<subset->faceCount_*3; j+=3){
			assert(j+subset->faceIndex_*3 + 2 < numIndices_ );
			std::set<TypeBoneIndex> pattern;

			for( unsigned int triangleIdx=0; triangleIdx<3; ++triangleIdx ){
				const unsigned short &index = ib[j+subset->faceIndex_*3+triangleIdx];
					
				//VERTEX_BONE *vBone = &vbBone[index];	
				//BoneIndex bi = originalVertexBufferBone_[index];
				//assert(vBone->index[0]==originalVertexBufferBone_[index][0]);
				
				for( unsigned int blendCount=0; blendCount<MODEL_BLEND_COUNT; ++blendCount ){
					const TypeBoneIndex &boneIndex = originalVertexBufferBone_[index][blendCount];
					if( boneIndex==(std::numeric_limits<TypeBoneIndex >::max)() ){
					} else {
						pattern.insert( boneIndex );
					}
				}
			}

			patternsInSubset.insert( pattern );
		}

		//TRACE1( "material%dでの三角形単位の使用ボーン\n", i );	
		//foreach( const std::set<TypeBoneIndex> & pattern, patternsInSubset )
		//{
		//	TRACE1( "  ( ", 0 );	
		//	foreach( TypeBoneIndex bi, pattern ){
		//		TRACE1( "%d, ", bi );	
		//	}
		//	TRACE1( ")\n", 0 );	

		//}

		//重複を取り除く
		removeContainedDuplicateElement( &patternsInSubset );
		//メンバー変数にコピー
		usingBoneIndexPatternOfGroupInSubset_[i] = NEW std::set<TypeBoneIndex>[ patternsInSubset.size() ];
		{
			unsigned int groupIdx=0;
			for(
				std::set< std::set<TypeBoneIndex> >::iterator it=patternsInSubset.begin(),
				end = patternsInSubset.end();
				it!=end;
				++it, ++groupIdx )
			{
				assert(groupIdx<patternsInSubset.size());
				const std::set<TypeBoneIndex> & pattern = *it; 
				assert( pattern.size() <= MODEL_BLEND_COUNT*3 );//1つの頂点が持てる最大のボーン数*3(三角形)
				usingBoneIndexPatternOfGroupInSubset_[i][groupIdx] = pattern;
			}
		}


		//TRACE1( "material%dでの三角形単位の使用ボーン\n", i );	
		//foreach( const std::set<TypeBoneIndex> & pattern, patternsInSubset )
		//{
		//	TRACE1( "  ( ", 0 );	
		//	foreach( TypeBoneIndex bi, pattern ){
		//		TRACE1( "%d, ", bi );	
		//	}
		//	TRACE1( ")\n", 0 );	
		//}

		//TRACE1( "material%dでのグループ分け開始\n", i );	
		//TRACE1( "indexBufferのindex : groupId \n", i );	
		//group分け
		std::multimap< int, unsigned long > group_indexMap;//key groupId, value indexBufferのindex
		for( unsigned int j=0; j<subset->faceCount_*3; j+=3){
			assert(j+subset->faceIndex_*3 + 2 < numIndices_ );
			std::set<TypeBoneIndex> pattern;

			
			for( unsigned int triangleIdx=0; triangleIdx<3; ++triangleIdx ){
				//並べ替えで値が変わるのでtempIndexBufferを使う
				const unsigned short &index = tib[j+subset->faceIndex_*3+triangleIdx];
				for( unsigned int blendCount=0; blendCount<MODEL_BLEND_COUNT; ++blendCount ){
					const TypeBoneIndex &boneIndex = originalVertexBufferBone_[index][blendCount];
					if( boneIndex==(std::numeric_limits<TypeBoneIndex >::max)() ){
					} else {
						pattern.insert( boneIndex );
					}
				}
			}

			//この三角形はどのグループ(ボーンインデックスのパターン)に入るか?
			int group = whichGroup( patternsInSubset, pattern );
			assert( group!=-1 );//アサートするようならバグあり
			//TRACE2( "  index %d: %d\n", j+subset->faceIndex_*3, group );	

			group_indexMap.insert( std::pair<int, unsigned long>(group, j+subset->faceIndex_*3) );
		}

		//並べ替え後の値
		//TRACE1( "並べ替え後", 1 );	
		//TRACE1( "indexBufferのindex : groupId \n", 1 );	
		std::pair<int, unsigned long> pair;
		//foreach( pair, group_indexMap ){
		//	TRACE2( "  index %d: %d\n", pair.first, pair.second );	
		//}

		//subset iにおけるグループの数
		numGroups_[i] = group_indexMap.rbegin()->first+1;
		//subset iにおけるグループｊのインデックスの数
		numIndeicesOfGroupInSubset_[i] = NEW int[ numGroups_[i] ];
		int total = 0;
		for( int groupidx=0; groupidx<numGroups_[i]; ++groupidx ){
			numIndeicesOfGroupInSubset_[i][groupidx] = group_indexMap.count(groupidx)*3; 
			total += numIndeicesOfGroupInSubset_[i][groupidx];
		}
		assert( group_indexMap.size() == subset->faceCount_ );
		assert( total == subset->faceCount_*3 );

		//indexBufferを並び替え
		int j=0; 
		foreach( pair, group_indexMap ){
			ib[j+subset->faceIndex_*3]		= tib[ pair.second ];
			ib[j+subset->faceIndex_*3 + 1]	= tib[ pair.second+1 ];
			ib[j+subset->faceIndex_*3 + 2]	= tib[ pair.second+2 ];
			j+=3;

		}
	}

#ifdef _DEBUG	
	long int total = 0;
	for (unsigned int i=0; i<subsets.size(); ++i) {
		for( int groupidx=0; groupidx<numGroups_[i]; ++groupidx ){
			total += numIndeicesOfGroupInSubset_[i][groupidx];				
		}
	}
	assert( numIndices_ == total );
#endif//_DEBUG
	
	
	//BoneIndexの置換
	//サブセットグループごとにindexBufferとvertexBufferを分割して、新たに作る
	GameLib::Graphics::Vertex *vb;
	vb=vertexBuffer_->lock();
	const unsigned int subsetSize=subsets.size();
	vbOfGroupInSubset_ = NEW GameLib::Graphics::VertexBuffer* [subsetSize];
	ibOfGroupInSubset_ = NEW GameLib::Graphics::IndexBuffer* [subsetSize];
	//抽象クラスは配列使えないのでvectorで
	vbBoneOfGroupInSubset_ = NEW std::vector<IDirect3DVertexBuffer9*> [subsetSize];
	
	typedef std::set<unsigned long> UniqueIndices;
	typedef std::map<unsigned long, unsigned long> ReplacementTable; // key oldIndexBufferIdx, value newIndexBufferIdx;

	unsigned long ibStartIndex=0;//indexbuffer
	for (unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx) {
		
		const int &numGroup = numGroups_[subsetIdx];
		vbOfGroupInSubset_[subsetIdx] = NEW GameLib::Graphics::VertexBuffer [numGroup];
		ibOfGroupInSubset_[subsetIdx] = NEW GameLib::Graphics::IndexBuffer [numGroup];
		vbBoneOfGroupInSubset_[subsetIdx].reserve(numGroup);
		
		for( int groupIdx=0; groupIdx<numGroup; ++groupIdx ){

			const unsigned int numIndices = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx]; 
			ibOfGroupInSubset_[subsetIdx][groupIdx] = GameLib::Graphics::IndexBuffer::create(numIndices);
			
			unsigned short *newIb = ibOfGroupInSubset_[subsetIdx][groupIdx] .lock();

			
			//create replacement table
			ReplacementTable rpcmtTbl;
			UniqueIndices uniqueIndices;
			//並べ替えと重複を省く
			//VertexBufferの元の並び順は維持したい
			/*-------------------------------------------
				VertexBuffer
				0 : a 使わない
				1 :	b 使う
				2 :	c 使う
				3 :	d 使わない
				4 :	e 使う

				IndexBuffer
				0 : 4
				1 :	1
				2 :	2

				new VertexBuffer
				0 : b 使う
				1 :	c 使う
				2 :	e 使う

				new IndexBuffer
				0 : 2
				1 :	0
				2 :	1
			-------------------------------------------*/
			//まずこれを作る
			//vectorではなくsetなのは並び順、重複を省くため
			//並び順が412だと三角形の最適化がなくなるかもしれないから(vertexBufferのため)
			/*
				uniqueIndices
				1
				2
				4
			*/			
			
			for( unsigned long ibIndex=ibStartIndex, ibEndIndex = ibStartIndex + numIndices;
				ibIndex<ibEndIndex;
				++ibIndex )
			{
				uniqueIndices.insert(ib[ibIndex]);
			}
			//置換テーブルを作る
			{
				unsigned long newIndex = 0;
				for( UniqueIndices::iterator it=uniqueIndices.begin(), end=uniqueIndices.end();
					it!=end;
					++it )
				{
					//keyがなかった場合入れる PairI(terator)B(ool)
					ReplacementTable::_Pairib pib = rpcmtTbl.insert( std::make_pair( *it, newIndex ) );
					if( pib.second ){
						++newIndex;
					}
					else{
						//set使っているのでないはず
						assert(	false && "キーが重複している" );
					}
				}
			}
			//ユニークなインデックスの数　イコール　新しく作る頂点数
			const unsigned int  numVertex = uniqueIndices.size(); 
			vbOfGroupInSubset_[subsetIdx][groupIdx] = GameLib::Graphics::VertexBuffer::create( numVertex );
			
			Manager m = Manager::instance();
			IDirect3DDevice9 *pDevice=m.dxDevice();
			pDevice->CreateVertexBuffer(
				sizeof(VERTEX_BONE)*numVertex, 0, 
				0, D3DPOOL_SYSTEMMEM,
				&vbBoneOfGroupInSubset_[subsetIdx][groupIdx], NULL);

			if (!vbBoneOfGroupInSubset_[subsetIdx][groupIdx] ) {
				assert(false && "頂点バッファの作成に失敗");
			}

			GameLib::Graphics::Vertex *newVb = vbOfGroupInSubset_[subsetIdx][groupIdx].lock(); 			
			VERTEX_BONE *newVbBone;
			vbBoneOfGroupInSubset_[subsetIdx][groupIdx]->Lock( 0, 0, (void**)&newVbBone, 0);
			// create new Buffer
			{
				unsigned long newIndex=0;
				for( 
					UniqueIndices::iterator it=uniqueIndices.begin(), end=uniqueIndices.end();
					it!=end;
					++it, ++newIndex )
				{
					const unsigned long &oldIndex = *it;
					//使う部分を代入
					newVb[newIndex] = vb[oldIndex];
					newVbBone[newIndex] = vbBone[oldIndex];
				}
				assert( newIndex==numVertex );
				//indexBufferは置換
				unsigned long offset = ibStartIndex;
				for( unsigned long i=0;
					i<numIndices;
					++i )
				{
					const unsigned short &oldIndex = ib[i+offset];
					//置換
					const unsigned long &newIndex = rpcmtTbl[oldIndex];
					newIb[i] = newIndex; 
				}
			}
			vbBoneOfGroupInSubset_[subsetIdx][groupIdx]->Unlock();
			vbOfGroupInSubset_[subsetIdx][groupIdx].unlock(&newVb);
			ibOfGroupInSubset_[subsetIdx][groupIdx].unlock(&newIb);


			//TRACE3( "Subset %d, groupIdx %d, numBoneIndcies %d\n", subsetIdx, groupIdx, usingBoneIndexPatternOfGroupInSubset_[subsetIdx][groupIdx].size() );
		}	
	}
	vertexBuffer_->unlock(&vb);
	vbBone_->Unlock();
	tempIndexBuffer.unlock(&tib);
	indexBuffer_->unlock(&ib);


}


//置換が必要なくするにはVertexBufferの建て直しが必要
//VertexBuffer[subsetIdx] or
//VertexBuffer[subsetIdx][groupIdx] 見たいな感じで作る。
//indexはすでに置換しとく
//subsetごとに必要なワールドマトリックス行列を送る関数は欲しい
void VertexDataUsingVertexBlendShader::sendMatrixArrayToShader(
	const std::vector<CBone*> &bones,
	int subsetIndex,
	int groupIndex,
	int startIndexBufferIdx )
{
	//const static D3DXMATRIX matZero( 
	//						0.f, 0.f, 0.f, 0.f,
	//						0.f, 0.f, 0.f, 0.f,
	//						0.f, 0.f, 0.f, 0.f,
	//						0.f, 0.f, 0.f, 0.f );
	//const static D3DXMATRIX matI( 
	//						1.f, 0.f, 0.f, 0.f,
	//						0.f, 1.f, 0.f, 0.f,
	//						0.f, 0.f, 1.f, 0.f,
	//						0.f, 0.f, 0.f, 1.f );

	//bonematrixArrayと対応する置換テーブル(表）をつくる
	int boneIndicesTable[MATRIX_ARRAY_MAX_SIZE];
	Matrix34 matArray[MATRIX_ARRAY_MAX_SIZE];
	const CBone *boneArray = bones[0];
	
	int i=0;
	for( 
		std::set<TypeBoneIndex>::iterator it=usingBoneIndexPatternOfGroupInSubset_[subsetIndex][groupIndex].begin(),
		end = usingBoneIndexPatternOfGroupInSubset_[subsetIndex][groupIndex].end();
		it!=end;
		++it, ++i )
	{
		assert(i<MATRIX_ARRAY_MAX_SIZE);

		if( *it!=(std::numeric_limits<TypeBoneIndex >::max)() ){
			boneIndicesTable[i]=*it;
			matArray[i] = toMatrix34( boneArray[ boneIndicesTable[i] ].getSkinningMatrix() );
		} else {
			boneIndicesTable[i]=*it;//255
			//matArray[i]=matZero;
		}
	}

	for(;i<MATRIX_ARRAY_MAX_SIZE; ++i){
		boneIndicesTable[i]=(std::numeric_limits<TypeBoneIndex >::max)();
	//	matArray[i]=matZero;
	}


	////描く数
	//const int &numIndicesDrawn = numIndeicesOfGroupInSubset_[subsetIndex][groupIndex];

	////CPU側で置換 くそ遅いので使わない
	//VERTEX_BONE *vBone;
	//unsigned short *ib = indexBuffer_->lock();
	//vbBone_->Lock( 0, 0, (void**)&vBone, 0);
	//for(int indexOfIndexBuffer=startIndexBufferIdx; indexOfIndexBuffer<startIndexBufferIdx+numIndicesDrawn; ++indexOfIndexBuffer ){
	//	int index = ib[indexOfIndexBuffer];
	//	for(int boneBlendIdx=0; boneBlendIdx<MODEL_BLEND_COUNT; ++boneBlendIdx ){ 
	//		for( int j=0; j<MATRIX_ARRAY_MAX_SIZE; ++j ){
	//			if( originalVertexBufferBone_[index][boneBlendIdx] == boneIndicesTable[j] ){
	//				vBone[index].mIndices[boneBlendIdx] = j;
	//				break;
	//			}
	//			assert( j!=11 );
	//		}
	//	}
	//}
	//vbBone_->Unlock();
	//indexBuffer_->unlock(&ib);


	//gm->sendWorldMatrixArrayToDevice();
	
	HRESULT hr;
	if(true){
		Manager m = Manager::instance();
		IDirect3DDevice9 *pDevice=m.dxDevice();
		
		//hr=g_pConstantTable->SetValue( pDevice, "mWorldMatrixArray", &matArray->m00, sizeof(float)*4*3*MATRIX_ARRAY_MAX_SIZE );
		//hr=g_pConstantTable->SetFloatArray( pDevice, "mWorldMatrixArray", &matArray->m00, 4*3*MATRIX_ARRAY_MAX_SIZE );
		//assert( SUCCEEDED( hr ) );
		//hr=g_pConstantTable->SetIntArray( pDevice, "mIndicesTable", boneIndicesTable, MATRIX_ARRAY_MAX_SIZE );
		//assert( SUCCEEDED( hr ) );

		hr = pDevice->SetVertexShaderConstantI( 11, boneIndicesTable, 3 ); 
		assert( SUCCEEDED( hr ) );
		hr = pDevice->SetVertexShaderConstantF( 14, &matArray->m00, 3*12 ); 
		assert( SUCCEEDED( hr ) );
		
		int shaderArray[12];
		Matrix34 debugMatArray[MATRIX_ARRAY_MAX_SIZE];

		hr = pDevice->GetVertexShaderConstantI( 11, shaderArray, 3 ); 
		assert( SUCCEEDED( hr ) );
		hr = pDevice->GetVertexShaderConstantF( 14, &debugMatArray->m00, 3*12 ); 
		assert( SUCCEEDED( hr ) );


	} else {
		hr=sEffect->SetRawValue( "mWorldMatrixArray", matArray, 0, sizeof(float)*4*3*MATRIX_ARRAY_MAX_SIZE );
		assert( SUCCEEDED( hr ) );
		hr=sEffect->SetIntArray( "mIndicesTable", boneIndicesTable, MATRIX_ARRAY_MAX_SIZE );
		assert( SUCCEEDED( hr ) );
	}

	//TRACE4( "sended mIndicesTable : %d, %d, %d, %d, ", boneIndicesTable[0], boneIndicesTable[1], boneIndicesTable[2], boneIndicesTable[3] );
	//TRACE4( "%d, %d, %d, %d, ", boneIndicesTable[4], boneIndicesTable[5], boneIndicesTable[6], boneIndicesTable[7] );
	//TRACE4( "%d, %d, %d, %d\n", boneIndicesTable[8], boneIndicesTable[9], boneIndicesTable[10], boneIndicesTable[11] );
}


void VertexDataUsingVertexBlendShader::initStaticObject(){
	

	if(!sVertexDeclaration)
	{
		HRESULT hr;
		Manager m = Manager::instance();
		IDirect3DDevice9 *pDevice=m.dxDevice();
	
		//複数ストリームを用いた描画のため新たに作る
		D3DVERTEXELEMENT9 vElements[] = {
			{ 0,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
			{ 0, 28, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
			{ 0, 32, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			{ 1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
			{ 1, 16, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
			D3DDECL_END(),
		};
		assert( sizeof(TypeBoneIndex)==sizeof(unsigned char) );
		assert( MODEL_BLEND_COUNT == 4 );


		hr = pDevice->CreateVertexDeclaration( vElements, &sVertexDeclaration );
		//LPVOID string;

		//FormatMessage(
		//	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		//	NULL,
		//	hr,
		//	0,//MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 既定の言語
		//	(LPTSTR)&string,
		//	0,
		//	NULL);

		//// エラーメッセージを表示する
		////MessageBox(NULL, (LPCTSTR)string, TEXT("Error"), MB_OK);
	
		////バッファを解放する	
		//LocalFree(string);

		STRONG_ASSERT( SUCCEEDED( hr ) && "CreateVertexDeclaration : INVALID CALL" );
	
		hr = pDevice->SetVertexDeclaration( sVertexDeclaration );
		STRONG_ASSERT( SUCCEEDED( hr ) && "setVertexDeclaration : INVALID CALL" );
	}

	if( !sEffect ){
		while(true){
			HRESULT hr;
			Manager m = Manager::instance();
			IDirect3DDevice9 *pDevice=m.dxDevice();
	
			LPD3DXBUFFER pCompilationErrors;	
			//hr=D3DXCreateEffect( m.dxDevice(), gSimpleFx, sizeof(gSimpleFx), NULL, NULL, 0, NULL, &sEffect, NULL);
			hr=D3DXCreateEffectFromFile(
				pDevice,
				_T("shader/test.fx"),
				NULL,
				NULL,
				0,
				NULL,
				&sEffect,
				&pCompilationErrors
			);
			if(pCompilationErrors){
				const char* p= (const char*)pCompilationErrors->GetBufferPointer();
				OutputDebugStringA( p );
				//OutputDebugString( p );
				pCompilationErrors->Release();
				if( SUCCEEDED( hr ) ) {
					break;
				}
			}
			else{
				STRONG_ASSERT( SUCCEEDED( hr ) && "setVertexDeclaration : INVALID CALL" );
				break;
			}
		}
	}

	if(!sVertexShader){
		HRESULT hr;
		Manager m = Manager::instance();
		IDirect3DDevice9 *pDevice=m.dxDevice();
		// Define DEBUG_VS and/or DEBUG_PS to debug vertex and/or pixel shaders with the 
		// shader debugger. Debugging vertex shaders requires either REF or software vertex 
		// processing, and debugging pixel shaders requires REF.  The 
		// D3DXSHADER_FORCE_*_SOFTWARE_NOOPT flag improves the debug experience in the 
		// shader debugger.  It enables source level debugging, prevents instruction 
		// reordering, prevents dead code elimination, and forces the compiler to compile 
		// against the next higher available software target, which ensures that the 
		// unoptimized shaders do not exceed the shader model limitations.  Setting these 
		// flags will cause slower rendering since the shaders will be unoptimized and 
		// forced into software.  See the DirectX documentation for more information about 
		// using the shader debugger.
		DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
		// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
			dwShaderFlags |= D3DXSHADER_SKIPOPTIMIZATION|D3DXSHADER_DEBUG;
		#endif
#ifdef DEBUG_PS
			dwShaderFlags |= D3DXSHADER_SKIPOPTIMIZATION|D3DXSHADER_DEBUG;
#endif

		LPD3DXBUFFER pCode;
		LPD3DXBUFFER pCompilationErrors;

		// Assemble the vertex shader from the file
		hr = D3DXCompileShaderFromFile( 
			_T("shader/testVs.fx"), NULL, NULL, "VS_main",
			"vs_3_0", dwShaderFlags, &pCode,
			&pCompilationErrors, &g_pConstantTable );
		if(pCompilationErrors){
			const char* p= (const char*)pCompilationErrors->GetBufferPointer();
			OutputDebugStringA( p );
			//OutputDebugString( p );
			pCompilationErrors->Release();
		}
		assert( SUCCEEDED( hr ) );



		// Create the vertex shader
		hr = pDevice->CreateVertexShader( 
			( DWORD* )pCode->GetBufferPointer(),
			&sVertexShader );
		assert( SUCCEEDED( hr ) );
		pCode->Release();
	
	}

	if(!sPixelShader) {
		HRESULT hr;
		Manager m = Manager::instance();
		IDirect3DDevice9 *pDevice=m.dxDevice();
		// Define DEBUG_VS and/or DEBUG_PS to debug vertex and/or pixel shaders with the 
		// shader debugger. Debugging vertex shaders requires either REF or software vertex 
		// processing, and debugging pixel shaders requires REF.  The 
		// D3DXSHADER_FORCE_*_SOFTWARE_NOOPT flag improves the debug experience in the 
		// shader debugger.  It enables source level debugging, prevents instruction 
		// reordering, prevents dead code elimination, and forces the compiler to compile 
		// against the next higher available software target, which ensures that the 
		// unoptimized shaders do not exceed the shader model limitations.  Setting these 
		// flags will cause slower rendering since the shaders will be unoptimized and 
		// forced into software.  See the DirectX documentation for more information about 
		// using the shader debugger.
		DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
		// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
			dwShaderFlags |= D3DXSHADER_SKIPOPTIMIZATION|D3DXSHADER_DEBUG;
		#endif
#ifdef DEBUG_PS
			dwShaderFlags |= D3DXSHADER_SKIPOPTIMIZATION|D3DXSHADER_DEBUG;
#endif

		LPD3DXBUFFER pCode;
		LPD3DXBUFFER pCompilationErrors;

		// Assemble the vertex shader from the file
		hr = D3DXCompileShaderFromFile( 
			_T("shader/testPs.fx"), NULL, NULL, "PS_main",
			"ps_3_0", dwShaderFlags, &pCode,
			&pCompilationErrors, NULL );
		if(pCompilationErrors){
			const char* p= (const char*)pCompilationErrors->GetBufferPointer();
			OutputDebugStringA( p );
			//OutputDebugString( p );
			pCompilationErrors->Release();
		}

		assert( SUCCEEDED( hr ) );

		// Create the vertex shader
		hr = pDevice->CreatePixelShader( 
			( DWORD* )pCode->GetBufferPointer(),
			&sPixelShader );
		assert( SUCCEEDED( hr ) );
		pCode->Release();
	
	}

	//HRESULT hr;
	//Manager m = Manager::instance();
	//IDirect3DDevice9 *pDevice=m.dxDevice();
	//pDevice->SetVertexShader( sVertexShader );
	//pDevice->SetPixelShader( sPixelShader );


}

void VertexDataUsingVertexBlendShader::releaseStaticObject(){
	SAFE_RELEASE(sVertexDeclaration);
	SAFE_RELEASE(sEffect);
	SAFE_RELEASE(sVertexShader);
	SAFE_RELEASE(sPixelShader);
}


void VertexDataUsingVertexBlendShader::update(const std::vector<CBone*> &bones) {
}

namespace {

//(1,2,3,4), というのがあったとしたら
//(1,3) だったらtrueを返す
//(1,2,3,4,5) だったら falseを返す
//(6)　はないので　falseを返す
bool do_a_have_b( 
	const std::set<TypeBoneIndex> &a,
	const std::set<TypeBoneIndex> &b )
{
	std::set<TypeBoneIndex>::const_iterator end = a.cend();
	foreach( TypeBoneIndex i, b ){
		//aの中にiがない場合
		if( end == a.find(i) ){
			return false;
		}
	}
	return true;
}

//{ (1,2,3,4), (1,5), (6,7,9) } というのがあったとしたら
//(1,3)だったら0を返す
//(5,)だったら 1を返す
//((4,6,7)　はないので　-1を返す
int whichGroup(
	const std::set< std::set<TypeBoneIndex> > &patterns,
	const std::set<TypeBoneIndex> &pattern )
{
	int num = patterns.size();
	int group=0;
	foreach( const std::set<TypeBoneIndex> &elementPatterns, patterns ){
		if( do_a_have_b( elementPatterns, pattern ) ){
			return group;
		}
		++group;
	}
	return -1;
}

//含まれている重複した要素を取り除く
//{ (1,2,3,4),(1,3) } というのがあったとしたら (1,3) は　(1,2,3,4)　に含まれているので消す
void removeContainedDuplicateElement( std::set< std::set<TypeBoneIndex> > *elements ) {
 
	typedef std::set< std::set<TypeBoneIndex> > Elements;
	Elements::iterator	it  = elements->begin();
		
	while(it!=elements->end()){
		
		for( Elements::iterator	jt  = elements->begin();
				jt!=elements->end();
			)
		{
			if( it==jt ){
				++jt;
				continue;
			}
			if( do_a_have_b( *it, *jt ) ){
				jt = elements->erase( jt );
			} else {
				++jt;
			}
		}
		++it;
	}
}

}// end no namespace