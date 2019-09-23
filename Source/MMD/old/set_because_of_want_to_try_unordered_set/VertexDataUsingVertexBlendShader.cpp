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
#include <GameLib/Graphics/AnimatedVertexBoneBuffer.h>
#include <GameLib/Graphics/AnimatedVertexBone.h>
#include <GameLib/Graphics/Vertex.h>
#include <GameLib/Graphics/Texture.h>
#include "helper/MyOutputDebugString.h"
#include <tchar.h>
#include <numeric>

#include"SegaTypeHelper.h"
#include<GameLib/Framework.h>

#include"MME/Manager.h"

using namespace GameLib::Graphics;
using namespace GameLib::Math;
//
//ID3DXEffect*					VertexDataUsingVertexBlendShader::sEffect					=NULL;
//IDirect3DVertexShader9*			VertexDataUsingVertexBlendShader::sVertexShader				=NULL;
//IDirect3DPixelShader9*			VertexDataUsingVertexBlendShader::sPixelShader				=NULL;
//IDirect3DVertexDeclaration9*	VertexDataUsingVertexBlendShader::sVertexDeclaration		=NULL;
//LPD3DXCONSTANTTABLE             g_pConstantTable											= NULL;

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

void assign( std::vector<TypeBoneIndex> *dst, const std::set<TypeBoneIndex> &source ){
	dst->reserve( source.size() );
	for( std::set<TypeBoneIndex>::iterator it=source.begin(), end=source.end();
		it!=end;
		++it )
	{
		dst->push_back( *it );
	}
	dst->shrink_to_fit();//念のため
}

}// end no namespace

struct VertexDataUsingVertexBlendShader::Vertex {
	D3DXVECTOR4 mPosition;
	D3DXVECTOR3 mNormal;
	unsigned mColor; //頂点色
	D3DXVECTOR2 mUv;
};

struct VertexDataUsingVertexBlendShader::VertexBone {
	float mWeights[MODEL_BLEND_COUNT];
	TypeBoneIndex mIndices[MODEL_BLEND_COUNT];//影響するボーンのインデックス
	void operator=( const VertexBone &vbBone ){
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
	usingBoneIndexPatternOfGroupInSubset_(0),
	vbOfGroupInSubset_(0),
	ibOfGroupInSubset_(0),
	vbBoneOfGroupInSubset_(0)
{
	vertexBuffer_ = NEW GameLib::Graphics::VertexBuffer();
	indexBuffer_  = NEW GameLib::Graphics::IndexBuffer();
	vbBone_ = NEW GameLib::Graphics::AnimatedVertexBoneBuffer();
}

VertexDataUsingVertexBlendShader::~VertexDataUsingVertexBlendShader() {
	
	//後始末
	for ( unsigned int i=0; i<numSubsets_; ++i) 
	{
		
		SAFE_DELETE_ARRAY( vbBoneOfGroupInSubset_[i] );
		SAFE_DELETE_ARRAY( ibOfGroupInSubset_[i] );
		SAFE_DELETE_ARRAY( vbOfGroupInSubset_[i] );
		
		SAFE_DELETE_ARRAY( numIndeicesOfGroupInSubset_[i] );
		SAFE_DELETE_ARRAY( usingBoneIndexPatternOfGroupInSubset_[i] );
	}

	SAFE_DELETE_ARRAY( vbBoneOfGroupInSubset_ );
	SAFE_DELETE_ARRAY( ibOfGroupInSubset_ );
	SAFE_DELETE_ARRAY( vbOfGroupInSubset_ );

	SAFE_DELETE_ARRAY( numIndeicesOfGroupInSubset_ ); 
	SAFE_DELETE_ARRAY( numGroups_ );
	
	SAFE_DELETE_ARRAY( usingBoneIndexPatternOfGroupInSubset_ );

	SAFE_DELETE(vertexBuffer_);
	SAFE_DELETE(vbBone_);
	SAFE_DELETE(indexBuffer_);
	SAFE_DELETE_ARRAY( usingBoneIndicesMap_ );
}

const char* VertexDataUsingVertexBlendShader::load(const char *pData) {
	//Manager m = Manager::instance();
	//IDirect3DDevice9 *pDevice=m.dxDevice();
	//-----------------------------------------------------
	// 頂点数取得
	numVertices_ = *( reinterpret_cast<const unsigned long *>(pData) );
	pData += sizeof( unsigned long );

	// 頂点配列をコピー
	*vertexBuffer_ = GameLib::Graphics::VertexBuffer::create( numVertices_, true );

	*vbBone_ = GameLib::Graphics::AnimatedVertexBoneBuffer::create( numVertices_ );
		
	GameLib::Graphics::Vertex *v;
	GameLib::Graphics::AnimatedVertexBone* vBone;
	v = vertexBuffer_->lock();
	vBone = vbBone_->lock();
				
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
		//GameLib::Graphics::AnimatedVertexBone *pvbBone;
		//pvbBone=&vBone[i];
		//assert( vBone[i].mWeights[0]!=0.f );



		originalVertexBufferBone_.push_back( BoneIndex( vBone[i].mIndices ) );

		v[i].mUv.x=pVertex->u;
		v[i].mUv.y=pVertex->v;
					
		pData += sizeof( PMD_VERTEX );
	}
	vbBone_->unlock(&vBone);
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
	
	return pData;
}

void VertexDataUsingVertexBlendShader::draw(
	const CBone *bones, const unsigned short &boneSize,
	const CModel::Subset *subsets, const unsigned long &subsetSize,
	const CModel::Material *materials, const unsigned long &materialSize )
{
	//HRESULT hr;
	Manager m = Manager::instance();


	//IDirect3DDevice9 *pDevice=m.dxDevice();
	m.enableVertexBlend( true );
	//int isBool=1;
	//hr = pDevice->SetVertexShaderConstantB( 11, &isBool, 1 );
	//assert( SUCCEEDED( hr ) );

	//バッファをセット
	m.setVertexBuffer( *vertexBuffer_ );
	m.setIndexBuffer( *indexBuffer_ );
	////ボーンのバーテックスバッファセット
	m.setAnimatedVertexBoneBuffer( *vbBone_ );

	unsigned long numFinishedIndices = 0;//書き終わったindexの数

	// サブセットの描画
	for (unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx) {
		
		const CModel::Subset* subset=&subsets[subsetIdx];
		
		// 色、テクスチャ
		unsigned long mi=subset->materialIndex_;
		const CModel::Material *pMaterial = &materials[mi];
		
		m.setDiffuseColor( pMaterial->diffuse_ );
		m.setTransparency( pMaterial->diffuse_.w );
		m.setAmbientColor( pMaterial->ambient_ );
		m.setSpecularColor( pMaterial->specular_ );
		m.setSpecularSharpness( pMaterial->power_ );
		m.setEmissionColor( pMaterial->emissive_ );
		m.setTexture( pMaterial->texture_ );

		for( unsigned int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ++groupIdx ){

			const int &numDrawingIndices = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx];
			assert(numDrawingIndices%3==0);
			//assert( numDrawingIndices==ibOfGroupInSubset_[subsetIdx][groupIdx].indexNumber() );
			sendMatrixArrayToShader( bones, subsetIdx, groupIdx, numFinishedIndices );

			m.drawIndexed( numFinishedIndices, numDrawingIndices/3 );

			numFinishedIndices += numDrawingIndices;

		}
	}

	//ストリームを消しとく
	//pDevice->SetStreamSource(1, 0, 0, 0);
}

void VertexDataUsingVertexBlendShader::drawByMME(
	const CBone *bones, const unsigned short &boneSize,
	const CModel::Subset *subsets, const unsigned long &subsetSize,
	const CModel::Material *materials, const unsigned long &materialSize )
{

	//HRESULT hr;
	//Manager ggm = Manager::instance();//Gamelib Graphics Manager
	MME::Manager *mmem = MME::Manager::instance();// Miku Miku Effect Manager

	D3DXMATRIX matI;
	D3DXMatrixIdentity( &matI );
	MME::Manager::instance()->setWorldMatrix( matI );
	MME::Manager::instance()->setLightWorldMatrix( 0, matI );

	//IDirect3DDevice9 *pDevice=m.dxDevice();
	mmem->enableVertexBlend( true );
	//int isBool=1;
	//hr = pDevice->SetVertexShaderConstantB( 11, &isBool, 1 );
	//assert( SUCCEEDED( hr ) );

	//バッファをセット
	mmem->setVertexBuffer( *vertexBuffer_ );
	mmem->setIndexBuffer( *indexBuffer_ );
	////ボーンのバーテックスバッファセット
	mmem->setAnimatedVertexBoneBuffer( *vbBone_ );

	unsigned long numFinishedIndices = 0;//書き終わったindexの数

	// サブセットの描画
	for (unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx) {
		
		const CModel::Subset* subset=&subsets[subsetIdx];
		
		unsigned long mi=subset->materialIndex_;
		const CModel::Material *pMaterial = &materials[mi];
		using namespace MME;

		UseTexture useTexture = 
			static_cast<const GameLib::Graphics::Texture &>(pMaterial->texture_) ? ENABLE_TEXTURE : DISABLE_TEXTURE;
		//bool useToon = static_cast<bool>( (void*)pMaterial->toonTexture_ );
		UseToon useToon = pMaterial->toonIndex_ != 0xff ? ENABLE_TOON : DISABLE_TOON;
		UseSphereMap useSphereMap =
			static_cast<const GameLib::Graphics::Texture &>(pMaterial->sphereTexture_) ? ENABLE_SPHEREMAP : DISABLE_SPHEREMAP;
		
		//一致している場合のみ描画だが、
		//zplot時のみ、textureやマテリアルを全て無視して書きたい
		assert( mi < (std::numeric_limits< unsigned int >::max)() );
		if( mmem->canDraw( useTexture, useSphereMap, useToon, mi ) )
		{}
		else {
			for( unsigned int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ++groupIdx ){

				const int &numDrawingIndices = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx];
				assert(numDrawingIndices%3==0);

				//zplot時のみ、textureやマテリアルを全て無視して書きたい
				if( mmem->getCurrentPass() == MME::MP_ZPLOT ){
					sendMatrixArrayToMMEShader( bones, subsetIdx, groupIdx, numFinishedIndices );
					mmem->drawIndexed( numFinishedIndices, numDrawingIndices/3 );
				}
				//assert( numDrawingIndices==ibOfGroupInSubset_[subsetIdx][groupIdx].indexNumber() );

				numFinishedIndices += numDrawingIndices;
			}
			continue;
		}

		mmem->setDiffuseColor( pMaterial->diffuse_ );
		//m.setTransparency( pMaterial->diffuse_.a );
		mmem->setAmbientColor( pMaterial->ambient_ );
		mmem->setSpecularColor( pMaterial->specular_ );
		mmem->setSpecularSharpness( pMaterial->power_ );
		mmem->setEmissionColor( pMaterial->emissive_ );
		mmem->setTexture( pMaterial->texture_ );
		
		if( useSphereMap ){
			mmem->setSphereTextureAdditive( pMaterial->isSphereTextureAdditive_!=0 );
			mmem->setSphereTexture( pMaterial->sphereTexture_ );
		}

		if( useToon ){
			mmem->setToonTexture( pMaterial->toonTexture_ );
			mmem->setToonColor( pMaterial->toonColor_ );
		}

		for( unsigned int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ++groupIdx ){

			const int &numDrawingIndices = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx];
			assert(numDrawingIndices%3==0);
			//assert( numDrawingIndices==ibOfGroupInSubset_[subsetIdx][groupIdx].indexNumber() );
			sendMatrixArrayToMMEShader( bones, subsetIdx, groupIdx, numFinishedIndices );

			mmem->drawIndexed( numFinishedIndices, numDrawingIndices/3 );

			numFinishedIndices += numDrawingIndices;
		}
	}

	//ストリームを消しとく
	//pDevice->SetStreamSource(1, 0, 0, 0);
}

void VertexDataUsingVertexBlendShader::updateFaceVertex(const CFace *faces, const short& size ) {
	if( !faces ){
		return;
	}
	if(size==0){
		return;
	}
	GameLib::Graphics::Vertex *vb;
	vb = vertexBuffer_->lock();			
	const CFace *pBase = faces;

	//baseで初期化
	CFaceVertex *pBaseFaceVertexArray = pBase->vertices_[0];
	for(unsigned int i=0, imax=pBase->vertices_.size(); i<imax; ++i) {
		const D3DXVECTOR3 &baseVec3 = pBaseFaceVertexArray[i].vec3_;
		for(unsigned int k=0, kmax=pBaseFaceVertexArray[i].numReplacedIndices_; k<kmax; ++k) {
			const unsigned long & index=pBaseFaceVertexArray[i].replacedIndices_[k];
			vb[index].mPosition.set( baseVec3.x, baseVec3.y, baseVec3.z );
		}
	}

	const CFace *faceArray = faces;
	//i=0はベース。だから抜かす
	for( unsigned int i=1, imax=size; i<imax; ++i ) {
		const CFace *pFace = &faceArray[i];
		if(pFace->weight_==0) continue;
		for( unsigned int j=0, jmax=pFace->vertices_.size(); j<jmax; ++j) {
			const CFaceVertex * pFaceVertex=pFace->vertices_[j];
			//線形補間 V1 + s(V2-V1)
			GameLib::Vector3 vOut( vb[pFaceVertex->replacedIndices_[0]].mPosition );
			GameLib::Vector3 v = toVector3(pFaceVertex->vec3_);

			v -= vOut;
			v *=pFace->weight_;
			vOut += v;

			for(unsigned int k=0, kmax=pFaceVertex->numReplacedIndices_; k<kmax; ++k) {
				const unsigned long & index=pFaceVertex->replacedIndices_[k];
				//vb[index].mPosition.set( vOut.x, vOut.y, vOut.z, 1.0f );
				vb[index].mPosition = vOut;
				break;
			}
		}
	}
	vertexBuffer_->unlock(&vb);
}

void VertexDataUsingVertexBlendShader::init(
		const CModel::Subset *subsets,	const unsigned long &subsetSize,
		CFace* faces, const unsigned long &faceSize )
{
	//IndexBufferの並び替え

	GameLib::Graphics::IndexBuffer tempIndexBuffer;
	tempIndexBuffer = GameLib::Graphics::IndexBuffer::create(numIndices_);
	
	GameLib::Graphics::AnimatedVertexBone *vbBone;
	vbBone = vbBone_->lock();

	unsigned short* ib;
	ib = indexBuffer_->lock();
	
	unsigned short* tib;//tempIndexBuffer
	tib = tempIndexBuffer.lock();

	memcpy( tib, ib, sizeof(unsigned short)*numIndices_ );
//#ifdef _DEBUG	
//	for(unsigned int i=0; i<numIndices_; ++i ){
//		assert( tib[i]==ib[i] );
//	}
//#endif//DEBUG
	
	numSubsets_ = subsetSize;
	//subset iにおけるグループの数
	numGroups_ = NEW unsigned int[numSubsets_];
	//subset iにおけるグループｊのインデックスの数
	numIndeicesOfGroupInSubset_ = NEW unsigned int*[numSubsets_];

	//subset idx における　三角形単位での使っているボーンインデックスのパターン
	std::set<TypeBoneIndex>** usingBoneIndexPatternOfGroupInSubset = NEW std::set<TypeBoneIndex>*[numSubsets_];
	
	for (unsigned int i=0; i<numSubsets_; ++i) {
		const CModel::Subset* subset=&(subsets[i]);
		std::set< std::set<TypeBoneIndex> > patternsInSubset;
		for( unsigned int j=0; j<subset->faceCount_*3; j+=3){
			assert(j+subset->faceIndex_*3 + 2 < numIndices_ );
			std::set<TypeBoneIndex> pattern;

			for( unsigned int triangleIdx=0; triangleIdx<3; ++triangleIdx ){
				const unsigned short &index = ib[j+subset->faceIndex_*3+triangleIdx];
					
				//GameLib::Graphics::AnimatedVertexBone *vBone = &vbBone[index];	
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
		//BOOST_FOREACH( const std::set<TypeBoneIndex> & pattern, patternsInSubset )
		//{
		//	TRACE1( "  ( ", 0 );	
		//	BOOST_FOREACH( TypeBoneIndex bi, pattern ){
		//		TRACE1( "%d, ", bi );	
		//	}
		//	TRACE1( ")\n", 0 );	

		//}

		//重複を取り除く
		removeContainedDuplicateElement( &patternsInSubset );
		//メンバー変数にコピー
		usingBoneIndexPatternOfGroupInSubset[i] = NEW std::set<TypeBoneIndex>[ patternsInSubset.size() ];
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
				usingBoneIndexPatternOfGroupInSubset[i][groupIdx] = pattern;
			}
		}

		//{
		//	unsigned int groupIdx=0;
		//	TRACE1( "material%dでの三角形単位の使用ボーン\n", i );	
		//	BOOST_FOREACH( const std::set<TypeBoneIndex> & pattern, patternsInSubset )
		//	{
		//		TRACE1( "group%d  ( ", groupIdx );	
		//		BOOST_FOREACH( TypeBoneIndex bi, pattern ){
		//			TRACE1( "%d, ", bi );	
		//		}
		//		TRACE1( ")\n", 0 );	
		//		++groupIdx;
		//	}
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
		//BOOST_FOREACH( pair, group_indexMap ){
		//	TRACE2( "  index %d: %d\n", pair.first, pair.second );	
		//}

		//subset iにおけるグループの数
		numGroups_[i] = group_indexMap.rbegin()->first+1;
		//subset iにおけるグループｊのインデックスの数
		numIndeicesOfGroupInSubset_[i] = NEW unsigned int[ numGroups_[i] ];
		int total = 0;
		for( unsigned int groupidx=0; groupidx<numGroups_[i]; ++groupidx ){
			numIndeicesOfGroupInSubset_[i][groupidx] = group_indexMap.count(groupidx)*3; 
			total += numIndeicesOfGroupInSubset_[i][groupidx];
		}
		assert( group_indexMap.size() == subset->faceCount_ );
		assert( total == subset->faceCount_*3 );

		//indexBufferを並び替え
		int j=0; 
		BOOST_FOREACH( pair, group_indexMap ){
			ib[j+subset->faceIndex_*3]		= tib[ pair.second ];
			ib[j+subset->faceIndex_*3 + 1]	= tib[ pair.second+1 ];
			ib[j+subset->faceIndex_*3 + 2]	= tib[ pair.second+2 ];
			j+=3;

		}
	}

//#ifdef _DEBUG	
//	long int total = 0;
//	for (unsigned int i=0; i<subsets.size(); ++i) {
//		for( int groupidx=0; groupidx<numGroups_[i]; ++groupidx ){
//			total += numIndeicesOfGroupInSubset_[i][groupidx];				
//		}
//	}
//	assert( numIndices_ == total );
//#endif//_DEBUG
	

	//シェーダのレジスタに入る最適な値に分割統合するため、どこで分けるか決定する。
	//現在は最小の値でグループ分けしてある。
	//最大でも、3頂点*4(MODEL_BLEND_COUNT)=12
	//サブセットを超えては統合しない
	//int **numIndeicesOfGroupInSubset_;
	//std::set<TypeBoneIndex>** newUsingBoneIndexPatternsOfGroupInSubset;
	//を作るのが目的

	unsigned int* newNumsGroups;
	newNumsGroups = NEW unsigned int [subsetSize];

	unsigned int **newNumIndeicesOfGroupInSubset;
	newNumIndeicesOfGroupInSubset = NEW unsigned int*[subsetSize];

	std::set<TypeBoneIndex>** newUsingBoneIndexPatternsOfGroupInSubset;
	newUsingBoneIndexPatternsOfGroupInSubset = NEW std::set<TypeBoneIndex>* [subsetSize];



	//新しいグループの分割数を知る(vector使えばいいんだけど、メンバー変数を簡単に入れ替えるために型を合わせておく)
	for(unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx) {
		unsigned int newNumGroups=0;
		std::set<TypeBoneIndex> newBoneIndexPattern;

		//group単位で統合したいのでgroupIdxは自分でインクリメント
		for( unsigned int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ){
			std::vector<TypeBoneIndex> tempBoneIndices;
			
			//新しく追加するものとそのサイズを知りたい
			for(
				std::set<TypeBoneIndex>::iterator it = usingBoneIndexPatternOfGroupInSubset[subsetIdx][groupIdx].begin(),
				end = usingBoneIndexPatternOfGroupInSubset[subsetIdx][groupIdx].end();
				it!=end;
				++it
			){ 
				//中にない場合
				if( newBoneIndexPattern.find( *it ) == newBoneIndexPattern.end() ){
					tempBoneIndices.push_back( *it );
				}
			}

			//容量があるのでnewBoneIndexPatternに入れる			
			if( SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE > tempBoneIndices.size()+newBoneIndexPattern.size()  ) {
				for( int i=0, size=tempBoneIndices.size(); i<size; ++i ){
					newBoneIndexPattern.insert( tempBoneIndices[i] );
				}
				++groupIdx;
			}
			else {
				//もう、入らないのでここで一区切り
				newBoneIndexPattern.clear();
				++newNumGroups;
				continue;
			}
		}
		//最後の奴は入っていないので足す
		++newNumGroups;
		newNumsGroups[subsetIdx] = newNumGroups;
		newNumIndeicesOfGroupInSubset[subsetIdx] = NEW unsigned int[newNumGroups];
		//初期化
		for( unsigned int i=0; i<newNumGroups; ++i){
			newNumIndeicesOfGroupInSubset[subsetIdx][i]=0;
		}
		newUsingBoneIndexPatternsOfGroupInSubset[subsetIdx] = NEW std::set<TypeBoneIndex>[newNumGroups];
	}
	//シェーダのレジスタに入る最適な値に分割統合するため、新しいグーループわけをする
	for(unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx) {
		unsigned int newGroupIdx=0;
		std::set<TypeBoneIndex> newBoneIndexPattern;
		unsigned int groupIdx=0;
		//group単位で統合したいのでgroupIdxは自分でインクリメント
		for( ; groupIdx<numGroups_[subsetIdx]; ){
			
			std::vector<TypeBoneIndex> tempBoneIndices;
			
			//新しく追加するものとそのサイズを知りたい
			for(
				std::set<TypeBoneIndex>::iterator it = usingBoneIndexPatternOfGroupInSubset[subsetIdx][groupIdx].begin(),
				end = usingBoneIndexPatternOfGroupInSubset[subsetIdx][groupIdx].end();
				it!=end;
				++it
			){ 
				//group単位でサイズを決めたいので、新しく入れるものの大きさを知りたい
				//中にない場合
				if( newBoneIndexPattern.find( *it ) == newBoneIndexPattern.end() ){
					tempBoneIndices.push_back( *it );
				}
			}
			//容量があるのでnewBoneIndexPatternに入れる			
			if( SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE > tempBoneIndices.size()+newBoneIndexPattern.size()  ) {
				for( int i=0, size=tempBoneIndices.size(); i<size; ++i ){
					newBoneIndexPattern.insert( tempBoneIndices[i] );
				}
				const int &newNumIdx = newNumIndeicesOfGroupInSubset[subsetIdx][newGroupIdx];
				const int &oldNumIdx = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx];

				newNumIndeicesOfGroupInSubset[subsetIdx][newGroupIdx] += numIndeicesOfGroupInSubset_[subsetIdx][groupIdx];
				++groupIdx;
			}
			else {
				//入らないのでここで保存
				newUsingBoneIndexPatternsOfGroupInSubset[subsetIdx][newGroupIdx] = newBoneIndexPattern;
				newBoneIndexPattern.clear();
				++newGroupIdx;
				continue;
			}
		}
		//最後の奴は入っていないので保存
		newUsingBoneIndexPatternsOfGroupInSubset[subsetIdx][newGroupIdx] = newBoneIndexPattern;
		newBoneIndexPattern.clear();
		++newGroupIdx;
		assert(newGroupIdx==newNumsGroups[subsetIdx]);
	}

//#ifdef _DEBUG	
//	total = 0;
//	for (unsigned int i=0; i<subsets.size(); ++i) {
//		for( int groupidx=0; groupidx<newNumsGroups[i]; ++groupidx ){
//			total += newNumIndeicesOfGroupInSubset[i][groupidx];				
//		}
//	}
//	assert( numIndices_ == total );
//#endif//_DEBUG

	//{
	//	TRACE1( "新しい統合したやつ\n", 0 );	

	//	for(unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx) {
	//		TRACE1( "material%dでの三角形単位の使用ボーン\n", subsetIdx );	
	//		for( unsigned int groupIdx=0; groupIdx<newNumsGroups[subsetIdx]; ++groupIdx ){
	//			TRACE1( "group%d  ( ", groupIdx );	
	//			BOOST_FOREACH( TypeBoneIndex bi, newUsingBoneIndexPatternsOfGroupInSubset[subsetIdx][groupIdx] )
	//			{
	//				TRACE1( "%d, ", bi );	
	//			}
	//			TRACE1( ")\n", 0 );	
	//		}
	//	}
	//}

	//新しいほうにメンバー関数を更新
	//古いほうを開放
	for ( unsigned int i=0; i<numSubsets_; ++i) {
		SAFE_DELETE_ARRAY( numIndeicesOfGroupInSubset_[i] );
		SAFE_DELETE_ARRAY( usingBoneIndexPatternOfGroupInSubset[i] );
	}

	SAFE_DELETE_ARRAY( numIndeicesOfGroupInSubset_ ); 
	SAFE_DELETE_ARRAY( numGroups_ );
	SAFE_DELETE_ARRAY( usingBoneIndexPatternOfGroupInSubset );

	//新しい値にポインタを付け替え
	numIndeicesOfGroupInSubset_ = newNumIndeicesOfGroupInSubset;
	numGroups_ = newNumsGroups;
	//usingBoneIndexPatternOfGroupInSubset_ = newUsingBoneIndexPatternsOfGroupInSubset;
	
	assert( usingBoneIndexPatternOfGroupInSubset_==0 );
	usingBoneIndexPatternOfGroupInSubset_ = NEW std::vector<TypeBoneIndex>*[subsetSize];
	for( unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx ){ 
		usingBoneIndexPatternOfGroupInSubset_[subsetIdx] = NEW std::vector<TypeBoneIndex>[ numGroups_[subsetIdx] ];
	}

	//setからvectorに変換　メンバー変数に入れる
	for ( unsigned int i=0; i<numSubsets_; ++i) {
		for ( unsigned int j=0; j<numGroups_[i]; ++j) {	
			assign( &usingBoneIndexPatternOfGroupInSubset_[i][j], newUsingBoneIndexPatternsOfGroupInSubset[i][j] );
		}
		SAFE_DELETE_ARRAY( newUsingBoneIndexPatternsOfGroupInSubset[i] );
	}
	SAFE_DELETE_ARRAY( newUsingBoneIndexPatternsOfGroupInSubset );

	//BoneIndexの置換、パーツの分割
	//サブセットグループごとにindexBufferとvertexBufferを分割して、新たに作る

	//faceIndexを置換するためのTable
	//key: oldVertexBufferIndex, value: newVertexBufferIndex
	std::map< unsigned long, std::set<unsigned long> > replacedFaceVertexIndexTable;

	GameLib::Graphics::Vertex *vb;
	vb=vertexBuffer_->lock();
	vbOfGroupInSubset_ = NEW GameLib::Graphics::VertexBuffer* [subsetSize];
	ibOfGroupInSubset_ = NEW GameLib::Graphics::IndexBuffer* [subsetSize];
	vbBoneOfGroupInSubset_ = NEW  GameLib::Graphics::AnimatedVertexBoneBuffer* [subsetSize];
	
	typedef std::set<unsigned long> UniqueIndices;
	//indexBufferの置換テーブル
	typedef std::map<unsigned long, unsigned long> ReplacementTable; // key oldIndexBufferIdx, value newIndexBufferIdx;

	unsigned long ibStartIndex=0;//indexbuffer
	unsigned long vbStartIndex=0;
	for (unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx) {
		
		const int &numGroup = numGroups_[subsetIdx];
		vbOfGroupInSubset_[subsetIdx] = NEW GameLib::Graphics::VertexBuffer [numGroup];
		ibOfGroupInSubset_[subsetIdx] = NEW GameLib::Graphics::IndexBuffer [numGroup];
		vbBoneOfGroupInSubset_[subsetIdx] = NEW GameLib::Graphics::AnimatedVertexBoneBuffer [numGroup];
		

		for( int groupIdx=0; groupIdx<numGroup; ++groupIdx ){

			const unsigned int numIndices = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx]; 
			
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
			//ユニークなインデックスのテーブルを作る
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
			const unsigned int  numVertex = uniqueIndices.size(); 

			//グループのインデックスの数分新しいのを作る
			ibOfGroupInSubset_[subsetIdx][groupIdx] = GameLib::Graphics::IndexBuffer::create(numIndices);

			//ユニークなインデックスの数　イコール　新しく作る頂点数
			vbOfGroupInSubset_[subsetIdx][groupIdx] = GameLib::Graphics::VertexBuffer::create( numVertex, true );
			
			vbBoneOfGroupInSubset_[subsetIdx][groupIdx] = GameLib::Graphics::AnimatedVertexBoneBuffer::create( numVertex );
			

			unsigned short *newIb = ibOfGroupInSubset_[subsetIdx][groupIdx] .lock();
			GameLib::Graphics::Vertex *newVb = vbOfGroupInSubset_[subsetIdx][groupIdx].lock(); 			
			GameLib::Graphics::AnimatedVertexBone *newVbBone = 
				vbBoneOfGroupInSubset_[subsetIdx][groupIdx].lock();

			// create new VertexBuffer
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
					
					//faceのモーフのためにここで置換テーブルに挿入
					std::map< unsigned long, std::set<unsigned long> >::iterator rfvitIt = 
						replacedFaceVertexIndexTable.find(oldIndex);
					//入っていない場合
					if( rfvitIt==replacedFaceVertexIndexTable.end() ){
						std::set<unsigned long> indices;
						indices.insert( newIndex+vbStartIndex );
						replacedFaceVertexIndexTable.insert( std::make_pair( oldIndex, indices) ); 
					}
					else{
						(*rfvitIt).second.insert( newIndex+vbStartIndex );//vbStartIndexはオフセット。後でひとつにするので
					}
					
					for( int iBone=0; iBone<MODEL_BLEND_COUNT; ++iBone ){
						const std::vector<TypeBoneIndex> &pattern = usingBoneIndexPatternOfGroupInSubset_[subsetIdx][groupIdx];
						unsigned int patternIdx=0;
						//置換
						for(
							std::vector<TypeBoneIndex>::const_iterator itPattern=pattern.begin(), endPattern = pattern.end();  
							itPattern!=endPattern;
							++itPattern, ++patternIdx )
						{
							if( newVbBone[newIndex].mIndices[iBone] == (std::numeric_limits< TypeBoneIndex >::max)() ){
								continue;
							}

							if( newVbBone[newIndex].mIndices[iBone] == *itPattern )
							{
								newVbBone[newIndex].mIndices[iBone] = patternIdx;
								break;
							}
						}
						const GameLib::Graphics::AnimatedVertexBone &boneA=newVbBone[newIndex];
						const GameLib::Graphics::AnimatedVertexBone &boneB=vbBone[oldIndex];
						assert(
							patternIdx<pattern.size() ||
							newVbBone[newIndex].mIndices[iBone] == (std::numeric_limits< TypeBoneIndex >::max)() &&
							"必ず置換するはず");
					}
				}
				assert( newIndex==numVertex );
				//create new indexBuffer
				unsigned long offset = ibStartIndex;
				for( unsigned long i=0;
					i<numIndices;
					++i )
				{
					const unsigned short &oldIndex = ib[i+offset];
					//置換
					const unsigned long &newIndex = rpcmtTbl[oldIndex];
					assert( newIndex <= (std::numeric_limits<unsigned short>::max)() );
					assert( newIndex <= oldIndex );
					newIb[i] = static_cast<unsigned short>(newIndex); 
				}
			}
			vbBoneOfGroupInSubset_[subsetIdx][groupIdx].unlock(&newVbBone);
			vbOfGroupInSubset_[subsetIdx][groupIdx].unlock(&newVb);
			ibOfGroupInSubset_[subsetIdx][groupIdx].unlock(&newIb);
			ibStartIndex += numIndices;
			vbStartIndex += vbOfGroupInSubset_[subsetIdx][groupIdx].vertexNumber();
			//TRACE3( "Subset %d, groupIdx %d, numBoneIndcies %d\n", subsetIdx, groupIdx, usingBoneIndexPatternOfGroupInSubset_[subsetIdx][groupIdx].size() );
		}	
	}

	vertexBuffer_->unlock(&vb);
	vbBone_->unlock(&vbBone);
	tempIndexBuffer.unlock(&tib);
	indexBuffer_->unlock(&ib);

	//メンバー関数(バッファ系)を一つに統合する
	//古いの開放
	*vertexBuffer_=0;
	//indexBuffer_は大きさ変わらないのでそのまま使う。
	//*indexBuffer_=0;
	*vbBone_ = 0;
	
	//新しいバッファを作成
	numVertices_ = 0;
	for (unsigned int i=0; i<numSubsets_; ++i) {
		for( unsigned int groupidx=0; groupidx<numGroups_[i]; ++groupidx ){
			numVertices_ += vbOfGroupInSubset_[i][groupidx].vertexNumber();				
		}
	}
	*vertexBuffer_ = GameLib::Graphics::VertexBuffer::create( numVertices_, true );
	*vbBone_ = GameLib::Graphics::AnimatedVertexBoneBuffer::create( numVertices_ );

	//indexBuffer_を新しいのに代入する
	ib = indexBuffer_->lock();
	unsigned long ibTotalIndex=0;
	unsigned short offset = 0;
	for (unsigned int subsetIdx=0; subsetIdx<numSubsets_; ++subsetIdx) {
		for( unsigned int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ++groupIdx ){
			
			unsigned short * oldIb = ibOfGroupInSubset_[subsetIdx][groupIdx].lock();
			for( int i=0, iMax=ibOfGroupInSubset_[subsetIdx][groupIdx].indexNumber(); i<iMax; ++i, ++ibTotalIndex ){
				ib[ibTotalIndex] = oldIb[i]+offset;
			}
			ibOfGroupInSubset_[subsetIdx][groupIdx].unlock(&oldIb);
			offset += vbOfGroupInSubset_[subsetIdx][groupIdx].vertexNumber();
		}
	}
	indexBuffer_->unlock(&ib);
	
	//vertexBuffer_,vbBone_を新しいのに代入する
	vbBone = vbBone_->lock();
	vb = vertexBuffer_->lock();	
	unsigned long vbTotalIndex=0;
	for (unsigned int subsetIdx=0; subsetIdx<numSubsets_; ++subsetIdx) {
		for( unsigned int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ++groupIdx ){
			GameLib::Graphics::Vertex *oldVb = vbOfGroupInSubset_[subsetIdx][groupIdx].lock();
			GameLib::Graphics::AnimatedVertexBone *oldVbBone =
				vbBoneOfGroupInSubset_[subsetIdx][groupIdx].lock();

			for( int i=0, iMax=vbOfGroupInSubset_[subsetIdx][groupIdx].vertexNumber(); i<iMax; ++i, ++vbTotalIndex ){
				vb[vbTotalIndex] = oldVb[i];
				vbBone[vbTotalIndex] = oldVbBone[i]; 
			}
			vbBoneOfGroupInSubset_[subsetIdx][groupIdx].unlock(&oldVbBone);
			vbOfGroupInSubset_[subsetIdx][groupIdx].unlock(&oldVb);
		}
	}
	vertexBuffer_->unlock(&vb);
	vbBone_->unlock(&vbBone);

	//faceを初期化
	if(faceSize==0){
		return;
	}
	CFace *pFaceArray = &faces[0];
	for( int i=0, imax=faceSize; i<imax; ++i )
	{
		CFaceVertex *pFaceVertexArray = pFaceArray[i].vertices_[0];
		for( int j=0, jmax=pFaceArray[i].vertices_.size(); j<jmax; ++j )
		{
			std::map< unsigned long, std::set<unsigned long> >::iterator rfvitIt = 
				replacedFaceVertexIndexTable.find( pFaceVertexArray[j].index_ );
			pFaceVertexArray[j].initVertexBlendIndices( rfvitIt->second );
		}
	}
}



void VertexDataUsingVertexBlendShader::sendMatrixArrayToShader(
	const CBone *bones,
	unsigned int subsetIndex,
	unsigned int groupIndex,
	unsigned int startIndexBufferIdx )
{
	Matrix34 matArray[SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE];
	const CBone *boneArray = bones;
	
	unsigned int i=0;
	//for( 
	//	std::set<TypeBoneIndex>::iterator it=usingBoneIndexPatternOfGroupInSubset_[subsetIndex][groupIndex].begin(),
	//	end = usingBoneIndexPatternOfGroupInSubset_[subsetIndex][groupIndex].end();
	//	it!=end;
	//	++it, ++i )
	//{
	//	assert(i<SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE);

	//	if( *it!=(std::numeric_limits<TypeBoneIndex >::max)() ){
	//		matArray[i] = toMatrix34( boneArray[ *it ].getSkinningMatrix() );
	//	} else {
	//		assert(false);
	//		//matArray[i]=matZero;
	//	}
	//}
	unsigned int size = usingBoneIndexPatternOfGroupInSubset_[subsetIndex][groupIndex].size();
	for( ; i<size; ++i ){
		const std::vector<TypeBoneIndex> &indexes = usingBoneIndexPatternOfGroupInSubset_[subsetIndex][groupIndex];
		assert(i<SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE);

		if( indexes[i]!=(std::numeric_limits<TypeBoneIndex >::max)() ){
			matArray[i] = toMatrix34( boneArray[ indexes[i] ].getSkinningMatrix() );
		} else {
			assert(false);
			//matArray[i]=matZero;
		}
	}
	assert( i==size );

	Manager m = Manager::instance();
	
	m.sendWorldMatrixArray(matArray, i );
	
	//HRESULT hr;
	//IDirect3DDevice9 *pDevice=m.dxDevice();
	//hr = pDevice->SetVertexShaderConstantF( 20, &matArray->m00, 3*SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE ); 
	//assert( SUCCEEDED( hr ) );
	//TRACE4( "sended mIndicesTable : %d, %d, %d, %d, ", boneIndicesTable[0], boneIndicesTable[1], boneIndicesTable[2], boneIndicesTable[3] );
	//TRACE4( "%d, %d, %d, %d, ", boneIndicesTable[4], boneIndicesTable[5], boneIndicesTable[6], boneIndicesTable[7] );
	//TRACE4( "%d, %d, %d, %d\n", boneIndicesTable[8], boneIndicesTable[9], boneIndicesTable[10], boneIndicesTable[11] );
}

//MMEは左手座標
void VertexDataUsingVertexBlendShader::sendMatrixArrayToMMEShader(
	const CBone *bones,
	unsigned int subsetIndex,
	unsigned int groupIndex,
	unsigned int startIndexBufferIdx )
{
	D3DXMATRIX matArray[SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE];
	const CBone *boneArray = bones;
	
	unsigned int i=0;
	//for( 
	//	std::set<TypeBoneIndex>::iterator it=usingBoneIndexPatternOfGroupInSubset_[subsetIndex][groupIndex].begin(),
	//	end = usingBoneIndexPatternOfGroupInSubset_[subsetIndex][groupIndex].end();
	//	it!=end;
	//	++it, ++i )
	//{
	//	assert(i<SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE);

	//	if( *it!=(std::numeric_limits<TypeBoneIndex >::max)() ){
	//		matArray[i] = boneArray[ *it ].getSkinningMatrix();
	//	} else {
	//		assert(false);
	//		//matArray[i]=matZero;
	//	}
	//}
	unsigned int size = usingBoneIndexPatternOfGroupInSubset_[subsetIndex][groupIndex].size();
	for( ; i<size; ++i ){
		const std::vector<TypeBoneIndex> &indexes = usingBoneIndexPatternOfGroupInSubset_[subsetIndex][groupIndex];
		assert(i<SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE);

		if( indexes[i]!=(std::numeric_limits<TypeBoneIndex >::max)() ){
			matArray[i] = boneArray[ indexes[i] ].getSkinningMatrix();
		} else {
			assert(false);
			//matArray[i]=matZero;
		}
	}
	assert( i==size );

	MME::Manager *mmem = MME::Manager::instance();//Miku Miku Effect Manager
	
	mmem->sendWorldMatrixArray(matArray, i );
	
	//HRESULT hr;
	//IDirect3DDevice9 *pDevice=m.dxDevice();
	//hr = pDevice->SetVertexShaderConstantF( 20, &matArray->m00, 3*SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE ); 
	//assert( SUCCEEDED( hr ) );
	//TRACE4( "sended mIndicesTable : %d, %d, %d, %d, ", boneIndicesTable[0], boneIndicesTable[1], boneIndicesTable[2], boneIndicesTable[3] );
	//TRACE4( "%d, %d, %d, %d, ", boneIndicesTable[4], boneIndicesTable[5], boneIndicesTable[6], boneIndicesTable[7] );
	//TRACE4( "%d, %d, %d, %d\n", boneIndicesTable[8], boneIndicesTable[9], boneIndicesTable[10], boneIndicesTable[11] );
}

/*
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
			_T("shader/VertexLightingVertexBlendVs.fx"), NULL, NULL, "main",
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
*/

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
	BOOST_FOREACH( TypeBoneIndex i, b ){
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
	BOOST_FOREACH( const std::set<TypeBoneIndex> &elementPatterns, patterns ){
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