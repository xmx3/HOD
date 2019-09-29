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

#include<unordered_set>
#include<unordered_map>
#include<boost/container/flat_set.hpp>

#include <boost/timer.hpp>



#include"SegaTypeHelper.h"
#include<GameLib/Framework.h>

#include"MME/Manager.h"

namespace MMD{
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

typedef std::vector<TypeBoneIndex> Pattern;
//typedef std::set<TypeBoneIndex> Pattern;

//sorted unique vectorとして使う
typedef std::vector<Pattern> Patterns;
//typedef std::set<Pattern> Patterns;

//typedef std::unordered_set<TypeBoneIndex> Pattern;
//template< class T>
//void insert( std::vector<T> &v, const T &val ){
//	std::vector<T>::iterator it=std::lower_bound(v.begin(), v.end(), val);
//	if(it==v.end() || *it!=val){
//		v.insert( it, val );
//	}
//}

void insertionSort( std::vector<TypeBoneIndex> &v, const TypeBoneIndex &val ){
	std::vector<TypeBoneIndex>::iterator it=std::lower_bound(v.begin(), v.end(), val);
	if(it==v.end() || *it!=val){
		v.insert( it, val );
	}
}

bool do_a_have_b( 
	const std::vector<TypeBoneIndex> &a,
	const std::vector<TypeBoneIndex> &b );

//2分探索のため
//(1,2,3,4), というのがあったとしたら
//(1,3) だったらtrueを返す
//(1,2,3,4,5) だったら falseを返す
//(6)　はないので　falseを返す
bool do_a_have_b( 
	const std::set<TypeBoneIndex> &a,
	const std::set<TypeBoneIndex> &b );

//(1,2,3,4), というのがあったとしたら
//(1,3) だったらtrueを返す
//(1,2,3,4,5) だったら falseを返す
//(6)　はないので　falseを返す
bool do_a_have_b( 
	const std::vector<TypeBoneIndex> &a,
	const std::vector<TypeBoneIndex> &b )
{
	std::vector<TypeBoneIndex>::const_iterator 
		begin = a.cbegin(),
		end = a.cend();
	for( unsigned int i=0, size=b.size(); i<size; ++i)
	{
		//aの中にiがない場合
		if( !std::binary_search(begin, end, b[i]) ){
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
	const std::set<TypeBoneIndex> &pattern );

//含まれている重複した要素を取り除く
//{ (1,2,3,4),(1,3) } というのがあったとしたら (1,3) は　(1,2,3,4)　に含まれているので消す
void removeContainedDuplicateElement( std::set< std::set<TypeBoneIndex> > *elements );

//void copy( std::vector<TypeBoneIndex> *dst, const std::set<TypeBoneIndex> &source ){
//	dst->reserve( source.size() );
//	for( std::set<TypeBoneIndex>::iterator it=source.begin(), end=source.end();
//		it!=end;
//		++it )
//	{
//		dst->push_back( *it );
//	}
//	dst->shrink_to_fit();//念のため
//}
//template<class T>
//void copy( std::vector<TypeBoneIndex> *dst, const T &source ){
//	dst->reserve( source.size() );
//	for( T::iterator it=source.begin(), end=source.end();
//		it!=end;
//		++it )
//	{
//		dst->push_back( *it );
//	}
//	dst->shrink_to_fit();//念のため
//}



//(1,2,3,4), というのがあったとしたら
//(1,3) だったらtrueを返す
//(1,2,3,4,5) だったら falseを返す
//(6)　はないので　falseを返す
//template< class T >
//bool do_a_have_b( 
//	const T &a,
//	const T &b )
//{
//	T::const_iterator end = a.cend();
//	BOOST_FOREACH( TypeBoneIndex i, b ){
//		//aの中にiがない場合
//		if( end == a.find(i) ){
//			return false;
//		}
//	}
//	return true;
//}

//遅い　2分探索したい
//(1,2,3,4), というのがあったとしたら
//(1,3) だったらtrueを返す
//(1,2,3,4,5) だったら falseを返す
//(6)　はないので　falseを返す
//template< class T >
//bool do_a_have_b( 
//	const T &a,
//	const T &b )
//{
//	return std::includes(
//		a.begin(), a.end(),
//		b.begin(), b.end() );
//}


//{ (1,2,3,4), (1,5), (6,7,9) } というのがあったとしたら
//(1,3)だったら0を返す
//(5,)だったら 1を返す
//((4,6,7)　はないので　-1を返す
template< class T >
int whichGroup(
	const std::set< T > &patterns,
	const T &pattern )
{
	int num = patterns.size();
	int group=0;
	BOOST_FOREACH( const T &elementPatterns, patterns ){
		if( do_a_have_b( elementPatterns, pattern ) ){
			return group;
		}
		++group;
	}
	return -1;
}

template< class T >
int whichGroup(
	const std::vector< T > &patterns,
	const T &pattern )
{
	for( unsigned i=0, size=patterns.size(); i<size; ++i ){
		if( do_a_have_b( patterns[i], pattern ) ){
			return i;
		}
	}
	return -1;
}

//新しいパターンを追加か代入
//返す値は追加(代入)したグループ
template< class T >
int pushBack_or_assign(
	std::vector< T > *patterns,
	const T &newPattern )
{
	for( unsigned iGroup=0, groupSize=patterns->size(); iGroup<groupSize; ++iGroup ){
		T &p = (*patterns)[iGroup];
		std::vector<TypeBoneIndex>::const_iterator 
			begin =p.cbegin(),
			end = p.cend();

		unsigned int numFound=0;
		unsigned int i=0, newPatternSize=newPattern.size();
		for(; i<newPatternSize; ++i)
		{
			if( std::binary_search(begin, end, newPattern[i]) ){
				++numFound;
				if(numFound==newPatternSize){
					return iGroup;
				}
			}
		}
		
		//あたらしいのが古いパターンも含んでいるので更新;
		unsigned int oldSize=p.size();
		if( numFound==oldSize ){
			if( newPatternSize>oldSize ){
				p=newPattern;
			}
			return iGroup;
		}
	}

	patterns->push_back( newPattern );

	return patterns->size()-1;
}



//含まれている重複した要素を取り除く
//{ (1,2,3,4),(1,3) } というのがあったとしたら (1,3) は　(1,2,3,4)　に含まれているので消す
template< class T >
void removeContainedDuplicateElement( std::set< T > *elements ) {
 
	typedef std::set< T > Elements;
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

//含まれている重複した要素を取り除く
//{ (1,2,3,4),(1,3) } というのがあったとしたら (1,3) は　(1,2,3,4)　に含まれているので消す
template< class T >
void removeContainedDuplicateElement( std::unordered_set< T > *elements ) {
 
	typedef std::unordered_set< T > Elements;
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

//含まれている重複した要素を取り除く
//{ (1,2,3,4),(1,3) } というのがあったとしたら (1,3) は　(1,2,3,4)　に含まれているので消す
template< class T >
void removeContainedDuplicateElement( std::vector< T > *elements ) {
	typedef std::vector< T > Elements;
	std::sort( elements->begin(), elements->end() );
	
	Elements::iterator it;
	it = std::unique( elements->begin(), elements->end() );
	elements->resize( std::distance(elements->begin(),it) );

	bool* isErased = new bool[elements->size()];
	for(int i=0, size=elements->size(); i<size; ++i){
		isErased[i] = false;
	}

	for(int i=0, size=elements->size(); i<size; ++i){
		if(isErased[i]){
			continue;
		}
		
		for(int j=0; j<size; ++j){
			const Elements &e = *elements;
			if(
				!isErased[j] &&
				&e[i]!=&e[j] &&
				do_a_have_b( e[i], e[j] ) )
			{
				isErased[j]=true;
			}
		}
	}

	int resize=0;
	for(int i=0, size=elements->size(); i<size; ++i){
		if(!isErased[i]){
			(*elements)[resize++] = (*elements)[i];
		}
	}
	elements->resize(resize);


	


	/*
	Elements::reverse_iterator	it  = elements->rbegin();

	while(it!=elements->rend()){
		for( Elements::reverse_iterator	jt  = elements->rbegin();
				jt!=elements->rend();
			)
		{
			if( it==jt ){
				++jt;
				continue;
			}
			if( do_a_have_b( *it, *jt ) ){
				jt = Elements::reverse_iterator(
					elements->erase( jt.base() ) );
			} else {
				++jt;
			}
		}
		++it;
	}
	*/
	SAFE_DELETE_ARRAY( isErased );
}

//bool compare_pair(const std::pair<int, unsigned long>& x, const std::pair<int, unsigned long>& y)
//{
//	return x.first < y.first || (!(y.first < x.first) && x.second < y.second)
//}

void sort_unique( std::vector<TypeBoneIndex> *pattern ){
	std::sort( pattern->begin(), pattern->end() );
	std::vector<TypeBoneIndex>::iterator it;
	it=std::unique(pattern->begin(), pattern->end());
	pattern->resize( std::distance(pattern->begin(),it) );
}

template<class T>
void sort_unique( std::vector<T> *v ){
	std::sort( v->begin(), v->end() );
	std::vector<T>::iterator it;
	it=std::unique(v->begin(), v->end());
	v->resize( std::distance(v->begin(),it) );
}

//見つからなかった場合挿入位置を返す
template<class T0, class T1 >
typename std::pair< typename std::vector< std::pair<T0, T1> >::iterator, bool >
binary_serach( std::vector< std::pair<T0, T1> > *v, const T0 &val ){
	
	struct KeyLess{
		bool operator() (const std::pair<T0, T1>& x, const T0 & y) const
		{
			return x.first<y;
		}
	};
	KeyLess less;

	std::vector< std::pair<T0, T1> >::iterator it=std::lower_bound(v->begin(), v->end(), val, less );

	//見つかった場合
	if( it!=v->end() && (*it).first==val ){
		return std::make_pair( it, true );
	}
	return std::make_pair( it, false );
}

void sendParamToMME(
	const CModel::Material *pMaterial,
	MME::UseTexture useTexture,
	MME::UseToon useToon,
	MME::UseSphereMap useSphereMap )
{
	MME::Manager *mmem = MME::Manager::instance();// Miku Miku Effect Manager

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
	const Bone *bones, const unsigned short &boneSize,
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
	const Bone *bones, const unsigned short &boneSize,
	const CModel::Subset *subsets, const unsigned long &subsetSize,
	const CModel::Material *materials, const unsigned long &materialSize )
{
	//HRESULT hr;
	//Manager ggm = Manager::instance();//Gamelib Graphics Manager
	MME::Manager *mmem = MME::Manager::instance();// Miku Miku Effect Manager
	
	MME::MMDPass pass = mmem->getCurrentPass();
	if( pass==MME::MP_OBJECT ||
		pass==MME::MP_OBJECT_SS ){
		using namespace MME;

		if( !mmem->canDraw( ENABLE_TEXTURE, ENABLE_SPHEREMAP, ENABLE_TOON, 0 )){
			return;
		}
	}


	D3DXMATRIX matI;
	D3DXMatrixIdentity( &matI );
	mmem->setWorldMatrix( matI );
	mmem->setLightWorldMatrix( 0, matI );

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
		assert( mi < (std::numeric_limits< unsigned int >::max)() );

		const CModel::Material *pMaterial = &materials[mi];
		using namespace MME;

		
		UseTexture useTexture = 
			static_cast<const GameLib::Graphics::Texture &>(pMaterial->texture_) ? ENABLE_TEXTURE : DISABLE_TEXTURE;
		//bool useToon = static_cast<bool>( (void*)pMaterial->toonTexture_ );
		//UseToon useToon = pMaterial->toonIndex_ != 0xff ? ENABLE_TOON : DISABLE_TOON;
		UseToon useToon = ENABLE_TOON;
		UseSphereMap useSphereMap =
			static_cast<const GameLib::Graphics::Texture &>(pMaterial->sphereTexture_) ? ENABLE_SPHEREMAP : DISABLE_SPHEREMAP;
		
		assert( 
			useTexture == ENABLE_TEXTURE &&
			useToon == ENABLE_TOON &&
			useSphereMap == ENABLE_SPHEREMAP &&
			"描画高速化のため VertexDataUsingVertexBlendShader::drawByMMEを改造したため,テクスチャがない場合は許さない。" );

		if(pass==MME::MP_EDGE){
			//このマテリアルは描画しない
			if( pMaterial->edgeFlag_!=1 ){
				//次回はどこから書くのか欲しいのでループ回す
				for( unsigned int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ++groupIdx ){

					const int &numDrawingIndices = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx];
					assert(numDrawingIndices%3==0);
					numFinishedIndices += numDrawingIndices;
				}
				continue;
			}
			useTexture = DISABLE_TEXTURE;
			useToon = DISABLE_TOON;
			useSphereMap = DISABLE_SPHEREMAP;
		} else if( pass == MME::MP_ZPLOT || pass == MME::MP_ZPREPASS){
			useTexture = DISABLE_TEXTURE;
			useToon = DISABLE_TOON;
			useSphereMap = DISABLE_SPHEREMAP;
		}

		//一致している場合のみ描画だが、
		//zplot時のみ、textureやマテリアルを全て無視して書きたい
		if( mmem->canDraw( useTexture, useSphereMap, useToon, mi ) )
		{
			//zplot時のみ、textureやマテリアルを全て無視
			if( pass!=MME::MP_ZPLOT){
				sendParamToMME(
					pMaterial,
					useTexture,
					useToon,
					useSphereMap );
			}	
		
			//描画
			for( unsigned int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ++groupIdx ){

				const int &numDrawingIndices = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx];
				assert(numDrawingIndices%3==0);
				//assert( numDrawingIndices==ibOfGroupInSubset_[subsetIdx][groupIdx].indexNumber() );
				sendMatrixArrayToMMEShader( bones, subsetIdx, groupIdx, numFinishedIndices );

				mmem->drawIndexed( numFinishedIndices, numDrawingIndices/3 );

				numFinishedIndices += numDrawingIndices;
			}
		}
		else {
			//次回はどこから書くのか欲しいのでループ回す
			for( unsigned int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ++groupIdx ){
				
				const int &numDrawingIndices = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx];
				assert(numDrawingIndices%3==0);
				numFinishedIndices += numDrawingIndices;
			}
			continue;
		}
	}

	//ストリームを消しとく
	//pDevice->SetStreamSource(1, 0, 0, 0);
}

void VertexDataUsingVertexBlendShader::updateFaceVertex(const Face *faces, const short& size ) {
	if( !faces ){
		return;
	}
	if(size==0){
		return;
	}
	GameLib::Graphics::Vertex *vb;
	vb = vertexBuffer_->lock();			
	const Face *pBase = faces;

	//baseで初期化
	CFaceVertex *pBaseFaceVertexArray = pBase->vertices_[0];
	for(unsigned int i=0, imax=pBase->vertices_.size(); i<imax; ++i) {
		const D3DXVECTOR3 &baseVec3 = pBaseFaceVertexArray[i].vec3_;
		for(unsigned int k=0, kmax=pBaseFaceVertexArray[i].numReplacedIndices_; k<kmax; ++k) {
			const unsigned long & index=pBaseFaceVertexArray[i].replacedIndices_[k];
			vb[index].mPosition.set( baseVec3.x, baseVec3.y, baseVec3.z );
		}
	}

	const Face *faceArray = faces;
	//i=0はベース。だから抜かす
	for( unsigned int i=1, imax=size; i<imax; ++i ) {
		const Face *pFace = &faceArray[i];
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
		Face* faces, const unsigned long &faceSize )
{
	//VertexDataUsingVertexBlendShader::init() : 8.75
	//VertexDataUsingVertexBlendShader::init() : 8.6960000991821289
	//boost::timer t; // タイマーの開始
	//boost::timer t0;
	//double total_t[5]={0.0};
	
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
	Pattern** usingBoneIndexPatternOfGroupInSubset = NEW Pattern*[numSubsets_];
	
	//グループとパターン似ているな　どっちかに統一したほうがいいか
	//group ユニークなボーンインデックスの集まり　patterns
	//pattern　ユニークなボーンインデックス

	for (unsigned int i=0; i<numSubsets_; ++i) {
		//boost::timer t;
		
		const CModel::Subset* subset=&(subsets[i]);
		Patterns patterns;
		
		typedef std::vector<unsigned long> IndexesBucket;//頂点インデックスを突っ込んでおくバケツ
		std::vector< IndexesBucket > indexesBuckets;//indexesBuckets[group]//グループ毎に分ける
		std::vector<unsigned int> numIndeicesOfGroup;
		
		//indexesBuckets.reserve(SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE);//値は適当だいたいこんなもんだろ
		//numIndeicesOfGroup.reserve(SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE);


		for( unsigned int j=0; j<subset->faceCount_*3; j+=3){
			assert(j+subset->faceIndex_*3 + 2 < numIndices_ );
			Pattern pattern;
			pattern.reserve(MODEL_BLEND_COUNT*3);

			//三角形毎の使用するボーンのパターンを調査
			for( unsigned int triangleIdx=0; triangleIdx<3; ++triangleIdx ){
				const unsigned short &index = ib[j+subset->faceIndex_*3+triangleIdx];
					
				for( unsigned int blendCount=0; blendCount<MODEL_BLEND_COUNT; ++blendCount ){
					const TypeBoneIndex &boneIndex = originalVertexBufferBone_[index][blendCount];
					if( boneIndex==(std::numeric_limits<TypeBoneIndex >::max)() ){
					} else {
						pattern.push_back( boneIndex );
					}
				}
			}
			//最後にまとめて整理
			sort_unique( &pattern );

			int group=whichGroup( patterns, pattern );
			//not found
			static const int not_found=-1;
			if( group==not_found ){
				//新しいパターンを追加か代入
				//返す値は追加(代入)したグループ
				group = pushBack_or_assign( &patterns, pattern );
				
				//追加した場合
				if(numIndeicesOfGroup.size() == group){
					numIndeicesOfGroup.push_back(0);
					indexesBuckets.push_back( IndexesBucket() );
				}
			}
			indexesBuckets[group].push_back( j+subset->faceIndex_*3);
			numIndeicesOfGroup[group] += 3;
		}
		//TRACE1("bukect size%d\n", indexesBuckets.size());

		//total_t[0]+=t.elapsed();
		//t.restart();
		
		std::vector< std::pair<int, int> > replaceTable;
		
		//0  [ 3, 43, 44, 45, ]
		//4  [ 43, 44, 45, ]
		//5  [ 3, 11, 12, 13, ]
		//9  [ 11, 12, 13, ]
		//上のようなパターンでは
		//4 を 0
		//9 を 5
		//に置換できるので、
		//置換のため表を作る。
		//無駄があるがたいした数を回すわけではないのでok
		//GroupIndex
		for(int gi0=0,size=patterns.size(); gi0<size; ++gi0 ){
			for(int gi1=0; gi1<size; ++gi1 ){
				if(gi0==gi1){
					continue;
				}
				if( do_a_have_b( patterns[gi1], patterns[gi0] ) ){
					replaceTable.push_back( std::make_pair(gi0, gi1) );
				}
			}
		}

		//置換
		for(
			std::vector< std::pair<int, int> >::iterator
				it = replaceTable.begin(),
				end = replaceTable.end();
			it!=end;
			++it )
		{
			const std::pair<int, int> &replace = *it;
			/*KeyLess less;
			std::pair< 
				std::vector< std::pair<int, int> >::iterator,
				std::vector< std::pair<int, int> >::iterator > 
			itPair = std::equal_range( group_indexVector0.begin(), group_indexVector0.end(), replace.first, less );

			while( itPair.first!=itPair.second ){
				(*itPair.first).first = replace.second;
			}

			if(itPair.first!=itPair.second){
			}*/
			
			IndexesBucket & a = indexesBuckets[replace.first];
			IndexesBucket & b = indexesBuckets[replace.second];
			b.insert(b.end(),a.begin(),a.end()); 
			a.clear();
			
			numIndeicesOfGroup[replace.second] += numIndeicesOfGroup[replace.first];
			numIndeicesOfGroup[replace.first]=0;

			patterns[replace.first].clear();

		}
		struct IsNotZero{
			bool operator() (const unsigned int &val) const
			{
				return val!=0;
			}
		};

		IsNotZero isNotZero;
		
		int numberOfGroup = std::count_if( numIndeicesOfGroup.begin(), numIndeicesOfGroup.end(), isNotZero );;
		//コピーするため確保
		usingBoneIndexPatternOfGroupInSubset[i] = NEW Pattern[ numberOfGroup ];
		//subset iにおけるグループの数
		numGroups_[i] = numberOfGroup;
		//subset iにおけるグループｊのインデックスの数
		numIndeicesOfGroupInSubset_[i] = NEW unsigned int[ numGroups_[i] ];
		//+3ずつ足していくので0に初期化
		//ZeroMemory( numIndeicesOfGroupInSubset_[i], sizeof(unsigned long)*numGroups_[i] );


		//{
		//	TRACE0( "replaceTable\n" );
		//	std::pair<int, int> replace;
		//	BOOST_FOREACH( replace, replaceTable ){
		//		TRACE2( "%d -> %d\n", replace.first, replace.second );	
		//		
		//	}

		//	TRACE1( "material%dでの三角形単位の使用ボーン\n", i );
		//	int group=0; 
		//	BOOST_FOREACH( const Pattern & pattern, patterns )
		//	{
		//		TRACE1( "%d  [ ", group++ );	
		//		BOOST_FOREACH( TypeBoneIndex bi, pattern ){
		//			TRACE1( "%d, ", bi );	
		//		}
		//		TRACE( "]\n" );	
		//	}
		//}

		//group毎の使うボーンパターンをコピーする
		{
			unsigned int newGroupIdx=0;
			for(
				int groupId=0, size=patterns.size();
				groupId<size;
				++groupId )
			{
				assert(newGroupIdx<patterns.size());
				const Pattern & pattern = patterns[groupId];
				if( pattern.empty() ){
					assert( numIndeicesOfGroup[groupId]==0 );
					continue;
				}
				assert( pattern.size() <= MODEL_BLEND_COUNT*3 );//1つの頂点が持てる最大のボーン数*3(三角形)
				usingBoneIndexPatternOfGroupInSubset[i][newGroupIdx] = pattern;
				numIndeicesOfGroupInSubset_[i][newGroupIdx] = numIndeicesOfGroup[groupId];
				++newGroupIdx;
			}
		}
			
		//グループ毎に固めるため
		//indexBufferを並び替え
		int j=0;
		for(int groupId=0,size=indexesBuckets.size(); groupId<size; ++groupId ){
		
			for( IndexesBucket::iterator it=indexesBuckets[groupId].begin(), end=indexesBuckets[groupId].end();
				it!=end;
				++it )
			{
				ib[j+subset->faceIndex_*3]		= tib[ *it ];
				ib[j+subset->faceIndex_*3 + 1]	= tib[ *it+1 ];
				ib[j+subset->faceIndex_*3 + 2]	= tib[ *it+2 ];
				j+=3;
			}
		}



		//int oldsize= patterns.size();
		//重複を取り除く
		//removeContainedDuplicateElement( &patterns );
		//assert( oldsize==patterns.size() );

		//TRACE1( "material%dでの三角形単位の使用ボーン\n", i );	
		//BOOST_FOREACH( const Pattern & pattern, patterns )
		//{
		//	TRACE( "  ( " );	
		//	BOOST_FOREACH( TypeBoneIndex bi, pattern ){
		//		TRACE1( "%d, ", bi );	
		//	}
		//	TRACE( ")\n" );	

		//}
		
		/*
		//コピーするため確保
		usingBoneIndexPatternOfGroupInSubset[i] = NEW Pattern[ patterns.size() ];
		//subset iにおけるグループの数
		numGroups_[i] = patterns.size();
		//subset iにおけるグループｊのインデックスの数
		numIndeicesOfGroupInSubset_[i] = NEW unsigned int[ numGroups_[i] ];
		//+3ずつ足していくので0に初期化
		ZeroMemory( numIndeicesOfGroupInSubset_[i], sizeof(unsigned long)*numGroups_[i] );

		
		total_t[1]+=t.elapsed();
		t.restart();


		//group毎の使うボーンパターンをコピーする
		{
			unsigned int groupIdx=0;
			for(
				Patterns::iterator it=patterns.begin(),
				end = patterns.end();
				it!=end;
				++it, ++groupIdx )
			{
				assert(groupIdx<patterns.size());
				const Pattern & pattern = *it; 
				assert( pattern.size() <= MODEL_BLEND_COUNT*3 );//1つの頂点が持てる最大のボーン数*3(三角形)
				usingBoneIndexPatternOfGroupInSubset[i][groupIdx] = pattern;
			}
		}

		total_t[2]+=t.elapsed();
		t.restart();

		//{
		//	unsigned int groupIdx=0;
		//	TRACE1( "material%dでの三角形単位の使用ボーン\n", i );	
		//	BOOST_FOREACH( const Pattern & pattern, patterns )
		//	{
		//		TRACE1( "group%d  ( ", groupIdx );	
		//		BOOST_FOREACH( TypeBoneIndex bi, pattern ){
		//			TRACE1( "%d, ", bi );	
		//		}
		//		TRACE( ")\n");	
		//		++groupIdx;
		//	}
		//}

		//TRACE1( "material%dでのグループ分け開始\n", i );	
		//TRACE1( "indexBufferのindex : groupId \n", i );	

		//key groupId, value count
		//group分けしてグループ毎に固めておきたい
		//(1、6、8ボーンを使う三角形を一度にまとめて書きたいので
		//散らばっているとシェーダでレジスタにセットしなおさなければいけないので一箇所にまとめるため
		//三角形はどのグループに所属してるか調べる
		std::vector< std::pair<int, unsigned long> > group_indexVector;//key groupId, value indexBufferのindex
		
		int totalVertex=0;//サブセット毎のトータルの頂点数//assertしたいので

		//jは面番号
		//subset->faceIndex_　開始面番号
		for( unsigned int j=0; j<subset->faceCount_*3; j+=3){
			assert(j+subset->faceIndex_*3 + 2 < numIndices_ );
			boost::timer t2;
			Pattern pattern;
			pattern.reserve(MODEL_BLEND_COUNT*3);

			for( unsigned int triangleIdx=0; triangleIdx<3; ++triangleIdx ){
				//並べ替えで値が変わるのでtempIndexBufferを使う
				const unsigned short &index = tib[j+subset->faceIndex_*3+triangleIdx];
				for( unsigned int blendCount=0; blendCount<MODEL_BLEND_COUNT; ++blendCount ){
					const TypeBoneIndex &boneIndex = originalVertexBufferBone_[index][blendCount];
					if( boneIndex==(std::numeric_limits<TypeBoneIndex >::max)() ){
					} else {
						insert( pattern, boneIndex );
					}
				}
			}
			//unique( &pattern );
			total_t2[0]+=t2.elapsed();
			t2.restart();

			//この三角形はどのグループ(ボーンインデックスのパターン)に入るか?
			int group = whichGroup( patterns, pattern );
			total_t2[1]+=t2.elapsed();
			t2.restart();

			assert( group!=-1 );//アサートするようならバグあり
			//TRACE2( "  index %d: %d\n", j+subset->faceIndex_*3, group );	

			//group_indexMap.insert( std::pair<int, unsigned long>(group, j+subset->faceIndex_*3) );
			group_indexVector.push_back( std::pair<int, unsigned long>(group, j+subset->faceIndex_*3) );
			numIndeicesOfGroupInSubset_[i][group] += 3;
			totalVertex+=3;
		}

		std::sort( group_indexVector.begin(), group_indexVector.end() );
		
		total_t[3]+=t.elapsed();
		t.restart();

		//並べ替え後の値
		//TRACE1( "並べ替え後", 1 );	
		//TRACE1( "indexBufferのindex : groupId \n", 1 );	
		//std::pair<int, unsigned long> pair;
		//BOOST_FOREACH( pair, group_indexMap ){
		//	TRACE2( "  index %d: %d\n", pair.first, pair.second );	
		//}

		
		
		//int total = 0;
		//for( unsigned int groupidx=0; groupidx<numGroups_[i]; ++groupidx ){ 
		//	total += numIndeicesOfGroupInSubset_[i][groupidx];
		//}
		//assert( group_indexMap.size() == subset->faceCount_ );
		//assert( total == subset->faceCount_*3 );
		assert( totalVertex == subset->faceCount_*3 );
		
		//グループ毎に固めるため
		//indexBufferを並び替え
		int j=0; 
		for( std::vector< std::pair<int, unsigned long> >::iterator it=group_indexVector.begin(), end=group_indexVector.end();
			it!=end;
			++it )
		{
			ib[j+subset->faceIndex_*3]		= tib[ it->second ];
			ib[j+subset->faceIndex_*3 + 1]	= tib[ it->second+1 ];
			ib[j+subset->faceIndex_*3 + 2]	= tib[ it->second+2 ];
			j+=3;
		}
		total_t[4]+=t.elapsed();
		t.restart();
		*/
	}
	//TRACE1( "total0 : %s.\n", boost::lexical_cast<std::string>(total_t[0]).c_str() );
	//TRACE1( "total1 : %s.\n", boost::lexical_cast<std::string>(total_t[1]).c_str() );
	//TRACE1( "total2 : %s.\n", boost::lexical_cast<std::string>(total_t[2]).c_str() );
	//TRACE1( "total3 : %s.\n", boost::lexical_cast<std::string>(total_t[3]).c_str() );
	//TRACE1( "total4 : %s.\n", boost::lexical_cast<std::string>(total_t[4]).c_str() );
	
	//シェーダのレジスタに入る最適な値に分割統合するため、どこで分けるか決定する。
	//現在は最小の値でグループ分けしてある。
	//最大でも、3頂点*4(MODEL_BLEND_COUNT)=12
	//サブセットを超えては統合しない
	
	//unsigned int* newNumsGroups;
	//newNumsGroups = NEW unsigned int [subsetSize];

	//unsigned int **newNumIndeicesOfGroupInSubset;
	//newNumIndeicesOfGroupInSubset = NEW unsigned int*[subsetSize];

	//Pattern** newUsingBoneIndexPatternsOfGroupInSubset;
	//newUsingBoneIndexPatternsOfGroupInSubset = NEW Pattern* [subsetSize];



	////新しいグループの分割数を知る
	//for(unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx) {
	//	unsigned int newNumGroups=0;
	//	Pattern newBoneIndexPattern;

	//	//group単位で統合したいのでgroupIdxは自分でインクリメント
	//	for( unsigned int groupIdx=0; groupIdx<numGroups_[subsetIdx]; ){
	//		Pattern newPattern;
	//		
	//		//新しく追加するものとそのサイズを知りたい
	//		for(
	//			Pattern::iterator it = usingBoneIndexPatternOfGroupInSubset[subsetIdx][groupIdx].begin(),
	//			end = usingBoneIndexPatternOfGroupInSubset[subsetIdx][groupIdx].end();
	//			it!=end;
	//			++it
	//		){ 
	//			//中にない場合
	//			if( std::find( newBoneIndexPattern.begin(), newBoneIndexPattern.end(), *it ) == newBoneIndexPattern.end() ){
	//				newPattern.push_back( *it );
	//			}
	//		}
	//		//ソートと重複なくし
	//		//unique( &newPattern );


	//		//容量があるのでnewBoneIndexPatternに入れる			
	//		if( SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE > newPattern.size()+newBoneIndexPattern.size()  ) {
	//			for( int i=0, size=newPattern.size(); i<size; ++i ){
	//				newBoneIndexPattern.push_back( newPattern[i] );
	//			}
	//			++groupIdx;
	//		}
	//		else {
	//			//もう、入らないのでここで一区切り
	//			newBoneIndexPattern.clear();
	//			++newNumGroups;
	//			continue;
	//		}
	//	}
	//	//最後の奴は入っていないので足す
	//	++newNumGroups;
	//	newNumsGroups[subsetIdx] = newNumGroups;
	//	newNumIndeicesOfGroupInSubset[subsetIdx] = NEW unsigned int[newNumGroups];
	//	//初期化
	//	for( unsigned int i=0; i<newNumGroups; ++i){
	//		newNumIndeicesOfGroupInSubset[subsetIdx][i]=0;
	//	}
	//	newUsingBoneIndexPatternsOfGroupInSubset[subsetIdx] = NEW Pattern[newNumGroups];
	//}

	//TRACE1( "VertexDataUsingVertexBlendShader00 : %s.\n", boost::lexical_cast<std::string>(t0.elapsed()).c_str() );
	//t0.restart();

	std::vector<unsigned int> nGroupInSubset(subsetSize);
	std::vector< std::vector<unsigned int> > nIndeciesOfGroupInSubset(subsetSize);
	std::vector< std::vector<Pattern> > patternsOfGroupInSubset(subsetSize);
	


	//シェーダのレジスタに入る最適な値に統合するため、新しいグーループわけをする
	for(unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx) {
		nIndeciesOfGroupInSubset[subsetIdx].reserve( numGroups_[subsetIdx] );
		nIndeciesOfGroupInSubset[subsetIdx].push_back(0);
		patternsOfGroupInSubset[subsetIdx].reserve( numGroups_[subsetIdx] );

		unsigned int newGroupIdx=0;
		Pattern newPattern;
		unsigned int groupIdx=0;
		
		//group単位で統合したいのでグループごとのユニークなボーンを求める
		//groupIdxはやり直ししたい場面があるので、自分でインクリメント
		for( ; groupIdx<numGroups_[subsetIdx]; ){
			
			const Pattern &pattern = usingBoneIndexPatternOfGroupInSubset[subsetIdx][groupIdx];
			
			//容量があるのでグループを統合し、頂点数を足す			
			if( SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE > pattern.size()+newPattern.size()  ) {
				//新しいボーンパターンを追加
				for( int i=0, size=pattern.size(); i<size; ++i ){
					insertionSort( newPattern, pattern[i] );
				}

				nIndeciesOfGroupInSubset[subsetIdx][newGroupIdx] += numIndeicesOfGroupInSubset_[subsetIdx][groupIdx];
				++groupIdx;
			}
			else {
				//入らないのでここで保存
				//sortだけで良いと思うが重複も取っておく
				patternsOfGroupInSubset[subsetIdx].push_back( newPattern );
				newPattern.clear();
				++newGroupIdx;
				nIndeciesOfGroupInSubset[subsetIdx].push_back(0);
				
				continue;
			}
		}
		//最後の奴は入っていないので保存
		patternsOfGroupInSubset[subsetIdx].push_back( newPattern );
		
		newPattern.clear();
		++newGroupIdx;
		nGroupInSubset[subsetIdx]=newGroupIdx;
	}

	//for(unsigned int si=0; si<subsetSize; ++si) {
	//	assert( newNumsGroups[si]==nGroupInSubset[si] );
	//	for( unsigned int gi=0; gi<newNumsGroups[si]; ++gi ){
	//		assert(
	//			newUsingBoneIndexPatternsOfGroupInSubset[si][gi] ==
	//			patternsOfGroupInSubset[si][gi] );
	//		assert(
	//			newNumIndeicesOfGroupInSubset[si][gi] == 
	//			newNumIndeicesOfGroupInSubset[si][gi] );

	//	}
	//}



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

	assert( usingBoneIndexPatternOfGroupInSubset_==0 );
	usingBoneIndexPatternOfGroupInSubset_ = NEW std::vector<TypeBoneIndex>*[subsetSize];
	
	for ( unsigned int si=0; si<numSubsets_; ++si) {
		//再利用
		numGroups_[si]=nGroupInSubset[si];
		
		SAFE_DELETE_ARRAY( numIndeicesOfGroupInSubset_[si] );
		numIndeicesOfGroupInSubset_[si] = NEW unsigned int[ numGroups_[si] ];
		
		SAFE_DELETE_ARRAY( usingBoneIndexPatternOfGroupInSubset[si] );

		usingBoneIndexPatternOfGroupInSubset_[si] = NEW std::vector<TypeBoneIndex>[ numGroups_[si] ];

		for( unsigned int gi=0; gi<nGroupInSubset[si]; ++gi ){
			numIndeicesOfGroupInSubset_[si][gi] = nIndeciesOfGroupInSubset[si][gi];

			usingBoneIndexPatternOfGroupInSubset_[si][gi].resize(patternsOfGroupInSubset[si][gi].size() );
			std::copy(
				patternsOfGroupInSubset[si][gi].begin(), patternsOfGroupInSubset[si][gi].end(),
				usingBoneIndexPatternOfGroupInSubset_[si][gi].begin() );
		}
	}

	//SAFE_DELETE_ARRAY( numIndeicesOfGroupInSubset_ ); 
	//SAFE_DELETE_ARRAY( numGroups_ );

	SAFE_DELETE_ARRAY( usingBoneIndexPatternOfGroupInSubset );

	//新しい値にポインタを付け替え
	//numIndeicesOfGroupInSubset_ = newNumIndeicesOfGroupInSubset;
	//numGroups_ = newNumsGroups;
	//usingBoneIndexPatternOfGroupInSubset_ = newUsingBoneIndexPatternsOfGroupInSubset;
	
	//assert( usingBoneIndexPatternOfGroupInSubset_==0 );
	//usingBoneIndexPatternOfGroupInSubset_ = NEW std::vector<TypeBoneIndex>*[subsetSize];
	//for( unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx ){ 
	//	usingBoneIndexPatternOfGroupInSubset_[subsetIdx] = NEW std::vector<TypeBoneIndex>[ numGroups_[subsetIdx] ];
	//}

	//メンバー変数に入れる
	//for ( unsigned int i=0; i<numSubsets_; ++i) {
	//	for ( unsigned int j=0; j<numGroups_[i]; ++j) {	
	//		usingBoneIndexPatternOfGroupInSubset_[i][j].resize(newUsingBoneIndexPatternsOfGroupInSubset[i][j].size() );
	//		std::copy(
	//			newUsingBoneIndexPatternsOfGroupInSubset[i][j].begin(), newUsingBoneIndexPatternsOfGroupInSubset[i][j].end(),
	//			usingBoneIndexPatternOfGroupInSubset_[i][j].begin() );
	//	}
	//	SAFE_DELETE_ARRAY( newUsingBoneIndexPatternsOfGroupInSubset[i] );
	//}
	//SAFE_DELETE_ARRAY( newUsingBoneIndexPatternsOfGroupInSubset );


	//TRACE1( "VertexDataUsingVertexBlendShader0 : %s.\n", boost::lexical_cast<std::string>(t0.elapsed()).c_str() );
	//t0.restart();

	//BoneIndexの置換、パーツの分割

	//今のVertexBufferではグループを越えて使う頂点があり、
	//頂点が指定するボーンは実際に使っているボーンとなっている
	
	//新しい頂点では指定するボーンはシェーダで実際に使うindexに変更する。
	//そのため、グループを越えて使う頂点をグループごとに新しく追加する

	//サブセットグループごとにindexBufferとvertexBufferを分割して、新たに作る

	//faceIndexを置換するためのTable
	//key: oldVertexBufferIndex, value: newVertexBufferIndex
	//std::map< unsigned long, std::set<unsigned long> > replacedFaceVertexIndexTable;
	typedef std::vector< std::vector<unsigned long> > ReplacementFaceVertexIndexTable;
	//typedef std::vector< std::pair< unsigned long, std::vector<unsigned long> > > ReplacementFaceVertexIndexTable;
	//typedef std::map< unsigned long, std::set<unsigned long> > ReplacementFaceVertexIndexTable;
	ReplacementFaceVertexIndexTable replacementFaceVertexIndexTable( numVertices_ );

	GameLib::Graphics::Vertex *vb;
	vb=vertexBuffer_->lock();
	vbOfGroupInSubset_ = NEW GameLib::Graphics::VertexBuffer* [subsetSize];
	ibOfGroupInSubset_ = NEW GameLib::Graphics::IndexBuffer* [subsetSize];
	vbBoneOfGroupInSubset_ = NEW  GameLib::Graphics::AnimatedVertexBoneBuffer* [subsetSize];
	
	typedef std::vector<unsigned short> UniqueIndices;
	//indexBufferの置換テーブル
	//typedef std::vector< std::pair<unsigned short, unsigned short> > ReplacementTable; // key oldIndexBufferIdx, value newIndexBufferIdx;
	typedef std::vector< unsigned short> ReplacementTable; // newIndexBufferIdx;
	ReplacementTable rpcmtTbl( numVertices_ );

	//double total_t1[6] = {0.0};

	unsigned long ibStartIndex=0;//indexbuffer
	unsigned long vbStartIndex=0;
	for (unsigned int subsetIdx=0; subsetIdx<subsetSize; ++subsetIdx) {
		//boost::timer t1;
		
		const int &numGroup = numGroups_[subsetIdx];
		vbOfGroupInSubset_[subsetIdx] = NEW GameLib::Graphics::VertexBuffer [numGroup];
		ibOfGroupInSubset_[subsetIdx] = NEW GameLib::Graphics::IndexBuffer [numGroup];
		vbBoneOfGroupInSubset_[subsetIdx] = NEW GameLib::Graphics::AnimatedVertexBoneBuffer [numGroup];
		

		for( int groupIdx=0; groupIdx<numGroup; ++groupIdx ){

			const unsigned int numIndices = numIndeicesOfGroupInSubset_[subsetIdx][groupIdx]; 
			
			//create replacement table
			//ReplacementTable rpcmtTbl;
			UniqueIndices uniqueIndices;
			//グループで使う頂点番号が欲しい
			//並べ替えと重複を省く
			//VertexBufferの元の並び順は維持したい
			//-------------------------------------------
			//	VertexBuffer
			//	0 : a 使わない
			//	1 :	b 使う
			//	2 :	c 使う
			//	3 :	d 使わない
			//	4 :	e 使う
			//	
			//	IndexBuffer
			//	0 : 4
			//	1 :	1
			//	2 :	2
			//	
			//	new VertexBuffer
			//	0 : b 使う
			//	1 :	c 使う
			//	2 :	e 使う
			//	
			//	new IndexBuffer
			//	0 : 2
			//	1 :	0
			//	2 :	1
			//-------------------------------------------
			//まずこれを作る
			//vectorではなくsetなのは並び順、重複を省くため
			//並び順が412だと三角形の最適化がなくなるかもしれないから(vertexBufferのため)
			//	
			//	uniqueIndices
			//	1
			//	2
			//	4
			//			
			//ユニークなインデックスのテーブルを作る
			for( unsigned long ibIndex=ibStartIndex, ibEndIndex = ibStartIndex + numIndices;
				ibIndex<ibEndIndex;
				++ibIndex )
			{
				uniqueIndices.push_back(ib[ibIndex]);
			}
			sort_unique(&uniqueIndices);

			//total_t1[0]+=t1.elapsed();
			//t1.restart();

			//置換テーブルを作る
			{
				unsigned short newIndex = 0;
				for( UniqueIndices::iterator it=uniqueIndices.begin(), end=uniqueIndices.end();
					it!=end;
					++it )
				{
					//順番はソートしてあるから大丈夫　2番目の値のソートはどーでもいい(一番目の要素がユニークなので)
					//rpcmtTbl.push_back( std::make_pair( *it, newIndex ) );
					rpcmtTbl[*it] = newIndex;
					++newIndex;
				}
			}

			const unsigned int  numVertex = uniqueIndices.size(); 

			//グループのインデックスの数分新しいのを作る
			ibOfGroupInSubset_[subsetIdx][groupIdx] = GameLib::Graphics::IndexBuffer::create(numIndices);

			//ユニークなインデックスの数　イコール　新しく作る頂点数
			vbOfGroupInSubset_[subsetIdx][groupIdx] = GameLib::Graphics::VertexBuffer::create( numVertex, true );
			
			vbBoneOfGroupInSubset_[subsetIdx][groupIdx] = GameLib::Graphics::AnimatedVertexBoneBuffer::create( numVertex );

			//total_t1[1]+=t1.elapsed();
			//t1.restart();

			
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
					replacementFaceVertexIndexTable[oldIndex].push_back( newIndex+vbStartIndex );

					/*
					//faceのモーフのためにここで置換テーブルに挿入
					std::map< unsigned long, std::set<unsigned long> >::iterator rfvitIt = 
						replacementFaceVertexIndexTable.find(oldIndex);
					//入っていない場合
					if( rfvitIt==replacementFaceVertexIndexTable.end() ){
						std::set<unsigned long> indices;
						indices.insert( newIndex+vbStartIndex );
						replacementFaceVertexIndexTable.insert( std::make_pair( oldIndex, indices) ); 
					}
					else{
						(*rfvitIt).second.insert( newIndex+vbStartIndex );//vbStartIndexはオフセット。後でひとつにするので
					}
					*/

					/*
					//faceのモーフのためにここで置換テーブルに挿入
					std::pair<ReplacementFaceVertexIndexTable::iterator, bool> pairIb =
						binary_serach( &replacementFaceVertexIndexTable, oldIndex );
					
					if( pairIb.second ){
						pairIb.first->second.push_back( newIndex+vbStartIndex );//vbStartIndexはオフセット。後でひとつにするので
					}
					//新規に作る
					else{
						std::vector<unsigned long> indices;
						indices.push_back( newIndex+vbStartIndex );
						replacementFaceVertexIndexTable.insert( pairIb.first, std::make_pair( oldIndex, indices) ); 
					}
					*/
					
					//total_t1[2]+=t1.elapsed();
					//t1.restart();
				
					
					for( int iBone=0; iBone<MODEL_BLEND_COUNT; ++iBone ){
						const std::vector<TypeBoneIndex> &pattern = usingBoneIndexPatternOfGroupInSubset_[subsetIdx][groupIdx];
						
						const TypeBoneIndex &bone=newVbBone[newIndex].mIndices[iBone];
						if( bone == (std::numeric_limits< TypeBoneIndex >::max)() ){
							continue;
						}
						
						//2分探索　大して早くならん、なぜ？要素数少ないから
						//const std::vector<TypeBoneIndex>::const_iterator &begin = pattern.begin();
						//std::vector<TypeBoneIndex>::const_iterator it=std::lower_bound( begin, pattern.end(), bone );
						////assert(*it==bone);
						////int len = std::distance( pattern.begin(), it );
						////assert( len==(&*it - &*pattern.begin()) );						
						//newVbBone[newIndex].mIndices[iBone] = (&*it - &*begin);

						unsigned int patternIdx=0;
						//置換//ここ早くできるかも線形探索を2分探索に
						for(
							std::vector<TypeBoneIndex>::const_iterator itPattern=pattern.begin(), endPattern = pattern.end();  
							itPattern!=endPattern;
							++itPattern, ++patternIdx )
						{
							if( newVbBone[newIndex].mIndices[iBone] == *itPattern )
							{
								newVbBone[newIndex].mIndices[iBone] = patternIdx;
								//assert(len==patternIdx);
								break;
							}
						}
						//const GameLib::Graphics::AnimatedVertexBone &boneA=newVbBone[newIndex];
						//const GameLib::Graphics::AnimatedVertexBone &boneB=vbBone[oldIndex];
						//assert(
						//	patternIdx<pattern.size() ||
						//	newVbBone[newIndex].mIndices[iBone] == (std::numeric_limits< TypeBoneIndex >::max)() &&
						//	"必ず置換するはず");
					}
					//total_t1[3]+=t1.elapsed();
					//t1.restart();
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
					//std::pair< ReplacementTable::const_iterator, bool > pairIb =binary_serach( &rpcmtTbl, oldIndex );
					//assert(pairIb.second);
					//const unsigned short newIndex = pairIb.first->second;
					const unsigned short newIndex = rpcmtTbl[oldIndex];
					assert( newIndex < (std::numeric_limits<unsigned short>::max)() );
					assert( newIndex <= oldIndex );
					newIb[i] = static_cast<unsigned short>(newIndex); 
				}
				//total_t1[4]+=t1.elapsed();
				//t1.restart();
				
			}

			vbBoneOfGroupInSubset_[subsetIdx][groupIdx].unlock(&newVbBone);
			vbOfGroupInSubset_[subsetIdx][groupIdx].unlock(&newVb);
			ibOfGroupInSubset_[subsetIdx][groupIdx].unlock(&newIb);
			ibStartIndex += numIndices;
			vbStartIndex += vbOfGroupInSubset_[subsetIdx][groupIdx].vertexNumber();
			//TRACE3( "Subset %d, groupIdx %d, numBoneIndcies %d\n", subsetIdx, groupIdx, usingBoneIndexPatternOfGroupInSubset_[subsetIdx][groupIdx].size() );
			
		}	
	}

	//TRACE1( "0 : %s.\n", boost::lexical_cast<std::string>(total_t1[0]).c_str() );
	//TRACE1( "1 : %s.\n", boost::lexical_cast<std::string>(total_t1[1]).c_str() );
	//TRACE1( "2 : %s.\n", boost::lexical_cast<std::string>(total_t1[2]).c_str() );
	//TRACE1( "3 : %s.\n", boost::lexical_cast<std::string>(total_t1[3]).c_str() );
	//TRACE1( "4 : %s.\n", boost::lexical_cast<std::string>(total_t1[4]).c_str() );
	//TRACE1( "5 : %s.\n", boost::lexical_cast<std::string>(total_t1[5]).c_str() );



	//TRACE1( "VertexDataUsingVertexBlendShader1 : %s.\n", boost::lexical_cast<std::string>(t0.elapsed()).c_str() );
	//t0.restart();


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

	//TRACE1( "VertexDataUsingVertexBlendShader2 : %s.\n", boost::lexical_cast<std::string>(t0.elapsed()).c_str() );
	//t0.restart();


	//OutputDebugStringA( "VertexDataUsingVertexBlendShader::init() : " );
	//OutputDebugStringA( boost::lexical_cast<std::string>(t.elapsed()).c_str() );
	//OutputDebugStringA( "\n" );
	//t.restart();

	/*
	//faceを初期化
	if(faceSize==0){
		return;
	}
	Face *pFaceArray = &faces[0];
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
	*/
	//faceを初期化
	if(faceSize==0){
		return;
	}
	Face *pFaceArray = &faces[0];
	for( int i=0, imax=faceSize; i<imax; ++i )
	{
		CFaceVertex *pFaceVertexArray = pFaceArray[i].vertices_[0];
		for( int j=0, jmax=pFaceArray[i].vertices_.size(); j<jmax; ++j )
		{
			pFaceVertexArray[j].initVertexBlendIndices( replacementFaceVertexIndexTable[pFaceVertexArray[j].index_] );
		}
	}
}



void VertexDataUsingVertexBlendShader::sendMatrixArrayToShader(
	const Bone *bones,
	unsigned int subsetIndex,
	unsigned int groupIndex,
	unsigned int startIndexBufferIdx )
{
	Matrix34 matArray[SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE];
	const Bone *boneArray = bones;
	
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
	const Bone *bones,
	unsigned int subsetIndex,
	unsigned int groupIndex,
	unsigned int startIndexBufferIdx )
{
	D3DXMATRIX matArray[SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE];
	const Bone *boneArray = bones;
	
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
}// namespace MMD