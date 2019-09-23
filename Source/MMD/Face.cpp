#include "Face.h"
#include "Pmd.h"
#include "ContainerHelper.h"
#include <algorithm>

namespace MMD {
	Face::Face()
		:numVertices_(0),
		type_(0),
		weight_(0.f) {}

	Face::~Face() {
		if (!vertices_.empty()) {
			SAFE_DELETE_ARRAY(vertices_[0]);
			vertices_.clear();
			vertices_.shrink_to_fit();
		}
	}

	const char* Face::load(const char *pData) {
		const PMD_FACE *pFace = reinterpret_cast<const PMD_FACE *>(pData);

		strncpy(name_, pFace->name, 20);
		name_[20] = '\0';

		numVertices_ = pFace->nVertices;
		type_ = pFace->type;

		pData += sizeof(char) * 20 + sizeof(unsigned long) + sizeof(unsigned char);

		CFaceVertex *pArray = new CFaceVertex[numVertices_];
		vertices_.reserve(numVertices_);
		for (unsigned long i = 0; i < numVertices_; ++i) {
			const PMD_FACE_VERTEX* pPMD = reinterpret_cast<const PMD_FACE_VERTEX*>(pData);
			pArray[i].init(pPMD->index, D3DXVECTOR3(pPMD->x, pPMD->y, pPMD->z));
			CFaceVertex *pFv = &pArray[i];
			vertices_.push_back(pFv);
			pData += sizeof(PMD_FACE_VERTEX);
		}
		return pData;
	}

	//相対座標を絶対座標に変換
	//相対インデックスも絶対インデックスに変換
	void Face::initalize(const Face &base)
	{
		for (unsigned long i = 0; i < numVertices_; ++i)
		{
			vertices_[i]->vec3_ += base.vertices_[vertices_[i]->index_]->vec3_;
			vertices_[i]->index_ = base.vertices_[vertices_[i]->index_]->index_;
		}
	}
}