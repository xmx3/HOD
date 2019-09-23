#ifndef __VERTEXDATA_USING_VERTEX_BLEND_SHADER_H__
#define __VERTEXDATA_USING_VERTEX_BLEND_SHADER_H__
#include <d3dx9.h>
#include <vector>
#include <map>
#include <assert.h>
#include "Model.h"
#include "MMDMacro.h"
#include <set>

namespace GameLib{
	namespace Graphics{
		class VertexBuffer;
		class IndexBuffer;
		class AnimatedVertexBoneBuffer;
	}
}

class CFace;
class CBone;

//どうせならハーフエッジ構造も組み込んでおくべきだったか？
//欲しくなったら作る
class VertexDataUsingVertexBlendShader {
public:
	enum{ SENDED_WORLD_MATRIX_ARRAY_MAX_SIZE = 32, };//deviceに送られる最大の配列長
	enum{ MODEL_BLEND_COUNT = 4, };
	VertexDataUsingVertexBlendShader();
	~VertexDataUsingVertexBlendShader();
	const char* load(const char *pData);
	void draw(
		const CBone *bones, const unsigned short &boneSize,
		const CModel::Subset *subsets, const unsigned long &subsetSize,
		const CModel::Material *materials, const unsigned long &materialSize );

	void drawByMME(
		const CBone *bones, const unsigned short &boneSize,
		const CModel::Subset *subsets, const unsigned long &subsetSize,
		const CModel::Material *materials, const unsigned long &materialSize );

	void updateFaceVertex(const CFace *faces, const short &size );

	//indexBufferを最適化する。
	//頂点ブレンドをするためにIndexBufferを最適化する
	//void sortIndexBuffer();
	void init(
		const CModel::Subset *subsets,	const unsigned long &subsetSize,
		CFace* faces, const unsigned long &faceSize );

	//static void initStaticObject();
	//static void releaseStaticObject();
	
	//shortかintかcharどれにするか迷ったので
	typedef unsigned char TypeBoneIndex;

private:
	DISALLOW_COPY_AND_ASSIGN(VertexDataUsingVertexBlendShader);
	
	//グループごとに頂点を更新するために使用するWorldMatrixTableを作成してシェーダに送る
	void sendMatrixArrayToShader( 
		const CBone *bones,
		unsigned int subsetIndex,
		unsigned int groupIndex,
		unsigned int startIndexBufferIdx );

	//MMEは左手座標
	void VertexDataUsingVertexBlendShader::sendMatrixArrayToMMEShader(
		const CBone *bones,
		unsigned int subsetIndex,
		unsigned int groupIndex,
		unsigned int startIndexBufferIdx );


	GameLib::Graphics::VertexBuffer *vertexBuffer_;
	GameLib::Graphics::AnimatedVertexBoneBuffer* vbBone_;
	unsigned long numVertices_;
	GameLib::Graphics::IndexBuffer *indexBuffer_;
	unsigned long numIndices_;


	//クラスにするべきかも PrimitevePart? ModelPart
	//動的にパーツを作れるクラス
	GameLib::Graphics::VertexBuffer **vbOfGroupInSubset_;
	GameLib::Graphics::IndexBuffer **ibOfGroupInSubset_;
	GameLib::Graphics::AnimatedVertexBoneBuffer **vbBoneOfGroupInSubset_;
	//std::vector<IDirect3DVertexBuffer9*> *vbBoneOfGroupInSubset_;

	//subsetsのindexと共通
	//本来はCModel::Subsetに持たせるほうが自然
	std::map<unsigned short, unsigned short> *usingBoneIndicesMap_;//key boneIndex, value boneindexInShader

	struct Vertex;
	struct VertexBone;
	class BoneIndex{
	public:
		explicit BoneIndex( const TypeBoneIndex bi_array[] ){
			for( int i=0; i<MODEL_BLEND_COUNT; ++i ){
				value[i]=bi_array[i];
			}
		}
		BoneIndex( const BoneIndex & bi ) {
			for( int i=0; i<MODEL_BLEND_COUNT; ++i ){
				value[i]=bi.value[i];
			}
		}
		void operator=( const BoneIndex & bi ) {
			for( int i=0; i<MODEL_BLEND_COUNT; ++i ){
				value[i]=bi.value[i];
			}
		}
		bool operator==( const BoneIndex & bi ) const {
			for( int i=0; i<MODEL_BLEND_COUNT; ++i ){
				if(value[i]!=bi.value[i]){
					return false;
				}
			}
			return true;
		}
		TypeBoneIndex operator[](int i) const {
			assert( i<MODEL_BLEND_COUNT );
			assert( i>=0 );
			return value[i];
		}
	private:
		TypeBoneIndex value[MODEL_BLEND_COUNT];
	};
	//本来のboneIndexを保存するための配列
	std::vector<BoneIndex> originalVertexBufferBone_;


	//subset(材質)の数
	unsigned int numSubsets_;

	//subset iにおけるグループの数
	//subsets[i]には　numGroups_[i]個グループがある。
	unsigned int *numGroups_;
	//subset iにおけるグループｊのインデックスの数
	//numIndeicesOfGroupInSubset[i][j]個インデックスがある。
	//どれだけ描けばいいか知るに使う
	unsigned int **numIndeicesOfGroupInSubset_;

	
	//typedef std::set<unsigned short> BoneIndexPattern;
	//subset i におけるグループｊの三角形単位での使っているボーンインデックスのパターン
	//for( int j=0; j<numGroups[i]; j++ ){
	//	BoneIndexPattern	it  = usingBoneIndexPatternOfGroupInSubset_[i][j].begin(),
	//						end = usingBoneIndexPatternOfGroupInSubset_[i][j].end;
	//}
	//setである必要なしコピーとユニークかどうか調べるのめんどくさいからset使ってる
	std::vector<TypeBoneIndex>** usingBoneIndexPatternOfGroupInSubset_;

	
	//static ID3DXEffect *sEffect;
	//static IDirect3DVertexDeclaration9 *sVertexDeclaration;
	//static IDirect3DVertexShader9 *sVertexShader;
	//static IDirect3DPixelShader9 *sPixelShader;


};


#endif//__VERTEXDATA_USING_VERTEX_BLEND_SHADER_H__