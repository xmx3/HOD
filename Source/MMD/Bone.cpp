#include "Bone.h"
#include "Pmd.h"
#include<assert.h>

namespace MMD {


	Bone::Bone()
		:index_(-1),
		pParent_(NULL)
	{
		D3DXMatrixIdentity(&weightBlendMatrix_);
		//name_[21]に何かしたほうがいいかも
	};

	void Bone::init(
		Bone* pBones,
		const PMD_BONE &pmd,
		const int &index)
	{
		index_ = index;

		strncpy(name_, pmd.name, 20);
		name_[20] = '\0';


		initPos_ = D3DXVECTOR3(pmd.x, pmd.y, pmd.z);
		pos_ = D3DXVECTOR3(0.f, 0.f, 0.f);
		D3DXQuaternionIdentity(&qRotation_);
		D3DXMatrixIdentity(&skinningMatrix_);
		// 自分が子供で親フレームがあれば
		if (pmd.parent != -1) {
			//親に自分を子供としてセット
			pBones[pmd.parent].children_.push_back(this);
			//親をセット
			pParent_ = &(pBones[pmd.parent]);
		}
		else {
			pParent_ = NULL;
		}

		//pmd.ikTarget;
		//pmd.kind;
		//pmd.to;
	}
	Bone::~Bone() {

	}

	void Bone::debug_draw() {
		//D3DXVECTOR3 v;
		//D3DXVec3TransformCoord( &v, &initPos_, &skinningMatrix_ ); 
		//DrawSphere(v, 1.f);

		/*for (unsigned int i=0, imax=children_.size(); i<imax; ++i) {
			children_[i]->debug_draw();
		}*/
	}

	void Bone::updateSkinningMatrix(const D3DXMATRIX& matParent) {
		D3DXMATRIX matInvInitialPosMatrix, InitialPosMatrix, TransformMatrix;
		D3DXMatrixTranslation(&InitialPosMatrix, initPos_.x, initPos_.y, initPos_.z);
		D3DXMatrixTranslation(&matInvInitialPosMatrix, -1 * InitialPosMatrix._41, -1 * InitialPosMatrix._42, -1 * InitialPosMatrix._43);

		D3DXMatrixRotationQuaternion(&TransformMatrix, &qRotation_);
		TransformMatrix._41 = pos_.x;
		TransformMatrix._42 = pos_.y;
		TransformMatrix._43 = pos_.z;

		//ボーンの初期位置を中心にして回転のため
		//平行移動して回転して平行移動で戻す
		skinningMatrix_ = matInvInitialPosMatrix*TransformMatrix*InitialPosMatrix*matParent;

		for (unsigned int i = 0, imax = children_.size(); i < imax; ++i) {
			children_[i]->updateSkinningMatrix(skinningMatrix_);
		}
	}

	void Bone::saveWeightBlendMatrix() {
		weightBlendMatrix_ = skinningMatrix_;
		for (unsigned int i = 0, imax = children_.size(); i < imax; ++i) {
			children_[i]->saveWeightBlendMatrix();
		}
	}

	// アニメーション切り替え補間
	void Bone::exeWeightBlend(float weight) {
		assert( 1.f>=weight && weight>=0.f );

		if (1.f>=weight && weight>0.f ) {
			skinningMatrix_ = (1.f - weight)*skinningMatrix_ + weight*weightBlendMatrix_;
			for (unsigned int i = 0, imax = children_.size(); i < imax; ++i) {
				children_[i]->exeWeightBlend(weight);
			}
		}

		
	}
}//end namespace MMD