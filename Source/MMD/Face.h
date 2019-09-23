#ifndef __FACE_H__
#define __FACE_H__

#include <vector>
#include <d3dx9.h>
#include <set>
#include <assert.h>
#include "MMDMacro.h"

namespace MMD {
	class Face;
	class Animation;
	class VertexData;
	class VertexDataUsingVertexBlendShader;
	class FaceKey;

	class CFaceVertex
	{
	public:
		CFaceVertex()
			:index_(), vec3_(D3DXVECTOR3(0.f, 0.f, 0.f)), replacedIndices_(NULL), numReplacedIndices_(0)
		{}
		explicit CFaceVertex(const DWORD &index, const D3DXVECTOR3 &vec3)
			:index_(index), vec3_(vec3), replacedIndices_(NULL), numReplacedIndices_(0)
		{};
		virtual ~CFaceVertex()
		{
			SAFE_DELETE_ARRAY(replacedIndices_);
		};
		//vertexBlendのための拡張
		void initVertexBlendIndices(const std::set<unsigned long> &indices) {
			numReplacedIndices_ = indices.size();
			assert(numReplacedIndices_ != 0);
			replacedIndices_ = new unsigned long[numReplacedIndices_];
			int i = 0;
			for (
				std::set<unsigned long>::iterator it = indices.begin(), end = indices.end();
				it != end;
				++it, ++i
				)
			{
				replacedIndices_[i] = *it;
			}
		}

		//vertexBlendのための拡張
		void initVertexBlendIndices(const std::vector<unsigned long> &indices) {
			numReplacedIndices_ = indices.size();
			assert(numReplacedIndices_ != 0);
			replacedIndices_ = new unsigned long[numReplacedIndices_];
			int i = 0;
			for (
				std::vector<unsigned long>::const_iterator it = indices.cbegin(), end = indices.cend();
				it != end;
				++it, ++i
				)
			{
				replacedIndices_[i] = *it;
			}
		}

	private:
		DISALLOW_COPY_AND_ASSIGN(CFaceVertex);
		void init(const DWORD &index, const D3DXVECTOR3 &vec3)
		{
			index_ = index;
			vec3_ = vec3;
		};
		DWORD index_;
		D3DXVECTOR3 vec3_;
		//vertexBlendのために拡張
		DWORD *replacedIndices_;
		int numReplacedIndices_;
		friend class Face;
		friend class VertexData;
		friend class CFastVertexData;
		friend class VertexDataUsingVertexBlendShader;
	};

	class Face
	{
	public:
		explicit Face();
		virtual ~Face();

		const char* load(const char *pData);

		const char* getName() const { return name_; }
		//相対座標を絶対座標に変換
		//相対インデックスも絶対インデックスに変換
		void initalize(const Face &base);
	private:
		DISALLOW_COPY_AND_ASSIGN(Face);

	private:
		char name_[21];		// 表情名 (0x00 終端，余白は 0xFD)

		unsigned long numVertices_;	// 表情頂点数
		unsigned char type_;			// 分類

		float weight_;
		std::vector<CFaceVertex*> vertices_;	// 表情頂点データ
		friend class Animation;
		friend class VertexData;
		friend class CFastVertexData;
		friend class VertexDataUsingVertexBlendShader;
		friend class FaceKey;
	};
}
#endif //__FACE_H__