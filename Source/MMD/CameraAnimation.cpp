#include"CameraAnimation.h"
#include"CameraOneFrameData.h"
#include<algorithm>
#include<d3dx9.h>
#include<assert.h>
#include"BezierCurve.h"
#include"MMDConstants.h"
#include<GameLib/GameLib.h>
#include"TemplateVMD.h"
#include"MMDDataBase.h"

namespace MMD {

	CameraAnimation::CameraAnimation() {
	}
	CameraAnimation::~CameraAnimation() {
		keys_.clear();
		keys_.shrink_to_fit();
	}

	void CameraAnimation::insert(const CameraOneFrameData &framedata) {
		//auto pair = keys_.insert(framedata);
		//assert(pair.second && "key is doubled.");

		auto it = std::lower_bound(keys_.begin(), keys_.end(), framedata);
		if (it == keys_.end() || it->frame_ != framedata.frame_) {
			keys_.insert(it, framedata);
		}
	}

	void CameraAnimation::reserve(unsigned int size) {
		keys_.reserve(size);
	}
	void CameraAnimation::shrink_to_fit() {
		assert(keys_.size() == keys_.capacity());
		//この関数呼び出したくない、最初にメモリ確保しとけ
		keys_.shrink_to_fit();
	}
	//カメラに必要なパラメーターを計算
	void CameraAnimation::calc(
		float time,
		D3DXVECTOR3 *pCameraPos,
		D3DXVECTOR3 *pLookAt,
		D3DXVECTOR3 *pUp,
		float *pViewAngle
	) {
		float frame = time * MMD_FramePerSecond;
		//boost::container::flat_set<CameraOneFrameData>::iterator it = std::lower_bound( keys_.begin(), keys_.end() , frame );
		auto it = std::lower_bound(keys_.begin(), keys_.end(), frame);

		D3DXVECTOR3 target;
		D3DXQUATERNION q;
		float d;
		float v;
		if (it == keys_.begin()) {
			const CameraOneFrameData &ck = *it;
			target = ck.pos_;
			q = ck.rot_;
			d = ck.distance_;
			v = ck.viewAngle_;
		}
		else if (it == keys_.end()) {
			--it;
			const CameraOneFrameData &ck = *it;
			target = ck.pos_;
			q = ck.rot_;
			d = ck.distance_;
			v = ck.viewAngle_;
		}
		else {

			const CameraOneFrameData &ck1 = *it;

			const float &f1 = ck1.frame_;
			const D3DXVECTOR3 &p1 = ck1.pos_;
			const D3DXQUATERNION &q1 = ck1.rot_;
			const float &d1 = ck1.distance_;
			const float &v1 = ck1.viewAngle_;
			--it;
			const CameraOneFrameData &ck0 = *it;

			const float &f0 = ck0.frame_;
			const D3DXVECTOR3 &p0 = ck0.pos_;
			const D3DXQUATERNION &q0 = ck0.rot_;
			const float &d0 = ck0.distance_;
			const float &v0 = ck0.viewAngle_;


			assert(f0 <= frame && frame <= f1);

			float r = (f1 - frame) / (f1 - f0);

			//位置の補間
			float rate = ck0.interpolationX_->getInterValue(r);
			float a = p0.x;
			float b = p1.x;
			target.x = a*rate + b*(1.f - rate);

			rate = ck0.interpolationY_->getInterValue(r);
			a = p0.y;
			b = p1.y;
			target.y = a*rate + b*(1.f - rate);

			rate = ck0.interpolationZ_->getInterValue(r);
			a = p0.z;
			b = p1.z;
			target.z = a*rate + b*(1.f - rate);


			//回転部分の補間
			rate = ck0.interpolationQ_->getInterValue(r);
			float qDot = D3DXQuaternionDot(&q0, &q1);
			if (qDot < 0) {
				q = q0*rate - q1*(1 - rate);
				//回転部分は球面補間のほうがいい？
				//D3DXQuaternionSlerp(&q,&q0,&(-q1),r);
			}
			else {
				q = q0*rate + q1*(1 - rate);
				//回転部分は球面補間のほうがいい？
				//D3DXQuaternionSlerp(&q,&q0,&q1,r);
			}


			D3DXQuaternionNormalize(&q, &q);

			//距離の補間
			rate = ck0.interpolationD_->getInterValue(r);
			d = d0*rate + d1*(1.f - rate);

			//視野角の補間
			rate = ck0.interpolationV_->getInterValue(r);
			v = v0*rate + v1*(1.f - rate);
		}

		D3DXQUATERNION qDir(0.f, 0.f, d, 0);
		D3DXQUATERNION iq(-q.x, -q.y, -q.z, q.w);
		//D3DXQuaternionInverse( &iq, &q );
		D3DXQuaternionMultiply(&qDir, &iq, &qDir);
		D3DXQuaternionMultiply(&qDir, &qDir, &q);
		D3DXVECTOR3 cameraPos(
			qDir.x + target.x,
			qDir.y + target.y,
			qDir.z + target.z);

		D3DXVECTOR3 lookAt = target;



		/*
			D3DXVECTOR3 dir( 0.f, 0.f, d);
			D3DXMATRIX matR;
			D3DXMatrixRotationQuaternion( &matR, &q );
			D3DXVec3TransformNormal( &dir, &dir, &matR );

			D3DXVECTOR3 lookAt = target;
			D3DXVECTOR3 cameraPos = target + dir;

		*/

		D3DXQUATERNION qUp(0.f, 1.f, 0.f, 0.f);
		D3DXQuaternionMultiply(&qUp, &iq, &qUp);
		D3DXQuaternionMultiply(&qUp, &qUp, &q);
		D3DXVECTOR3 up(qUp.x, qUp.y, qUp.z);


		if (pViewAngle) {
			*pViewAngle = v;
		}

		if (pCameraPos) {
			*pCameraPos = cameraPos;
		}
		if (pLookAt) {
			*pLookAt = lookAt;
		}
		if (pUp) {
			*pUp = up;
		}
	}

	void MMD::CameraAnimation::load(const std::string & vmdFileName)
	{
		assert(keys_.empty() && "this is allocated.");//別に
		templateVmd_ = MMD::MMDDataBase::loadVMD(vmdFileName.c_str());
	}

	bool MMD::CameraAnimation::isReady()
	{
		if (templateVmd_ ){
			if (templateVmd_->isReady()) {
				auto ptr = templateVmd_->getCameraAnimation();
				keys_=ptr->keys_;
				templateVmd_.reset();
				
				return true;
			}
			else {
				return false;
			}
		}
		return true;
	}

	bool CameraAnimation::isOver(float time) const
	{
		float frame = time * MMD_FramePerSecond;

		const float &lastFrame = keys_.crbegin()->frame_;
		return frame >= lastFrame;
	}

}//namespace MMD