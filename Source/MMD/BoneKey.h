#ifndef __BONEKEY_H__
#define __BONEKEY_H__
#include<map>
#include<d3dx9.h>
#include"MMDMacro.h"
#include<assert.h>
#include<memory>
#include"Bone.h"
#include"BezierCurve.h"
#include"TemplateBoneKey.h"
#include<boost/container/flat_set.hpp>
#include"OneFrameData.h"

namespace MMD {

	class Animation;
	class BoneKey;
	typedef std::shared_ptr<BoneKey> BoneKeySharedPtr;
	//ボーンを探すとき文字列だと遅いので、文字列の代わりにボーンを持たせたもの,
	//同じモデルのときボーン配列の順番同じなのでボーンインデックス持たせたほうがいいね
	class BoneKey {
	public:
		BoneKey()
			:
			//bone_(NULL),
			boneIndex_(-1)//こうしとけば確実にエラー起こすだろ
		{}
		void init(Bone* bone, const TemplateBoneKey &tbk)
		{
			//bone_ = bone;
			boneIndex_ = bone->getIndex();
			frames_ = tbk.getFrames();
		}
		virtual ~BoneKey() {}

		void updateBone(const float &frame, Bone *bones) {

			Bone *bone = &bones[boneIndex_];
			assert(!empty());
			//MapType::iterator it = mapTimeTransform_->lower_bound(frame);
			boost::container::flat_set<OneFrameData>::iterator it =
				std::lower_bound(frames_->begin(), frames_->end(), frame);


			if (it == frames_->begin()) {
				bone->setPosAndQuat(it->pos_, it->rot_);
			}
			else if (it == frames_->end()) {
				--it;
				bone->setPosAndQuat(it->pos_, it->rot_);
			}
			else {
				const OneFrameData & data1 = *it;

				float time1 = data1.frame_;
				D3DXVECTOR3 pos1 = data1.pos_;
				D3DXQUATERNION q1 = data1.rot_;

				--it;
				const OneFrameData & data0 = *it;

				float time0 = data0.frame_;
				D3DXVECTOR3 pos0 = data0.pos_;
				D3DXQUATERNION q0 = data0.rot_;

				assert(time0 <= frame && frame <= time1);
				assert(time0 < time1);

				float r = (time1 - frame) / (time1 - time0);

				D3DXVECTOR3 vOut;

				float rate = data0.interpolationX_->getInterValue(r);
				float a = pos0.x;
				float b = pos1.x;
				vOut.x = a*rate + b*(1.f - rate);

				rate = data0.interpolationY_->getInterValue(r);
				a = pos0.y;
				b = pos1.y;
				vOut.y = a*rate + b*(1.f - rate);

				rate = data0.interpolationZ_->getInterValue(r);
				a = pos0.z;
				b = pos1.z;
				vOut.z = a*rate + b*(1.f - rate);


				//回転部分の補間
				D3DXQUATERNION qOut;
				rate = data0.interpolationQ_->getInterValue(r);
				float qDot = D3DXQuaternionDot(&q0, &q1);

				if (qDot < 0) {
					qOut = q0*rate - q1*(1 - rate);
					//回転部分は球面補間のほうがいい？
					//D3DXQuaternionSlerp(&qOut,&q1,&(-q2),r);
				}
				else {
					qOut = q0*rate + q1*(1 - rate);
					//回転部分は球面補間のほうがいい？
					//D3DXQuaternionSlerp(&qOut,&q1,&q2,r);
				}

				D3DXQuaternionNormalize(&qOut, &qOut);

				bone->setPosAndQuat(vOut, qOut);
			}
		}

		//デバッグ用に欲しいか？
		//const char* getName() const { return name_; }
		bool empty()const {
			return frames_->empty();
		}
		int boneIndex()const {
			return boneIndex_;
		}

		//Bone* bone(){
		//	return bone_;
		//}

		float maxFrame()const {
			if (frames_->empty()) {
				return 0.f;
			}
			else {
				return frames_->rbegin()->frame_;
			}
		}
	private:
		DISALLOW_COPY_AND_ASSIGN(BoneKey);

		std::shared_ptr< boost::container::flat_set<OneFrameData> > frames_;

		//const char* const name_;
		//Bone* bone_;
		int boneIndex_;
	};
}
#endif//__BONEKEY_H__
