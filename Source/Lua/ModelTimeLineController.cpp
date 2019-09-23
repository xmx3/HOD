#include"ModelTimeLineController.h"
#include<boost/container/flat_set.hpp>
#include<d3dx9.h>
#include<algorithm>
#include<assert.h>
#include"MME/Object/ModelKai.h"

namespace Lua {

	D3DXMATRIX calcTransformMatrix(const D3DXVECTOR3 &p, const D3DXQUATERNION &q) {
		D3DXMATRIX out;
		D3DXMatrixRotationQuaternion(&out, &q);
		out._41 = p.x;
		out._42 = p.y;
		out._43 = p.z;
		return out;
	}


	//名前案
	//TimeTransform key-value的な感じ
	//Transform
	//Key animation的に考えて

	struct TimeTransform {
		TimeTransform(float time, const D3DXVECTOR3 &p, const D3DXQUATERNION &q, const std::string &animationName) 
			:mTime(time),
			mPos(p),
			mQuat(q),
			mAnimName(animationName)
		{}

		bool operator<(const TimeTransform & right)const {
			return mTime < right.mTime;
		}
		bool operator<(const float & rightTime)const {
			return mTime < rightTime;
		}


		float mTime;
		std::string mAnimName;
		D3DXVECTOR3 mPos;
		D3DXQUATERNION mQuat;

	};

	//オブジェクトの座標をを計算する
	class ModelTimeLineController::Impl {
	public:
		Impl(MME::Object::ModelKaiSharedPtr model)
			:mTime(0.f),
			mModel(model)
		{}

		~Impl() {}

		void setTime(float time) {
			mTime = time;
		}

		void update(float elapsedTime) {
			mTime += elapsedTime;

			boost::container::flat_set<TimeTransform>::const_iterator it =
				std::lower_bound(mTimeTransform.begin(), mTimeTransform.end(), mTime);


			std::lower_bound(mTimeTransform.begin(), mTimeTransform.end(), mTime);

			if (it == mTimeTransform.begin()) {
				mModel->changeAnimation(it->mAnimName);
				mModel->update(
					calcTransformMatrix(it->mPos, it->mQuat),
					elapsedTime) ;
				return;
			}
			else if (it == mTimeTransform.end()) {
				--it;
				mModel->changeAnimation(it->mAnimName);
				mModel->update(
					calcTransformMatrix(it->mPos, it->mQuat),
					elapsedTime);
				return;
			}
			else {
				const TimeTransform &data1 = *it;

				const float &time1 = data1.mTime;
				const D3DXVECTOR3 &pos1 = data1.mPos;
				const D3DXQUATERNION &q1 = data1.mQuat;

				--it;
				const TimeTransform & data0 = *it;

				float time0 = data0.mTime;
				D3DXVECTOR3 pos0 = data0.mPos;
				D3DXQUATERNION q0 = data0.mQuat;

				assert(time0 <= mTime && mTime <= time1);
				assert(time0 < time1);

				float rate = (time1 - mTime) / (time1 - time0);

				D3DXVECTOR3 pos;

				pos = pos0*rate + pos1*(1.f - rate);



				//回転部分の補間
				D3DXQUATERNION q;
				float qDot = D3DXQuaternionDot(&q0, &q1);

				if (qDot < 0) {
					q = q0*rate - q1*(1 - rate);
				}
				else {
					q = q0*rate + q1*(1 - rate);
				}


				mModel->changeAnimation(data0.mAnimName);
				mModel->update(
					calcTransformMatrix(pos, q),
					elapsedTime );
				return;

			}
		}

		void insert(float time, const D3DXVECTOR3 &p, const D3DXQUATERNION &q, const std::string &animationName) {
			auto it = mTimeTransform.insert(TimeTransform(time, p, q, animationName));
			assert(it.second);//2重追加はダメ
		}

		bool isOver()const {
			if (mTimeTransform.empty()) {
				return true;
			}
			else {
				auto it = mTimeTransform.end();
				--it;
				return mTime > it->mTime;
			}
		}

		void init() {
			mTime = 0.f;
			auto it = mTimeTransform.begin();
			mModel->init(
				calcTransformMatrix( it->mPos, it->mQuat ),
				it->mAnimName );
		}


		float mTime;
		boost::container::flat_set<TimeTransform> mTimeTransform;
		MME::Object::ModelKaiSharedPtr mModel;
	};

}


Lua::ModelTimeLineController::ModelTimeLineController(const MME::Object::ModelKaiSharedPtr & model)
	:mImpl(new Impl(model))
{
	
}

Lua::ModelTimeLineController::~ModelTimeLineController()
{
	delete mImpl;
	mImpl = nullptr;
}

void Lua::ModelTimeLineController::insert(float time,
	float x, float y, float z,
	float degreeX, float degreeY, float degreeZ,
	const std::string &animName )
{
	float pitch = D3DXToRadian(degreeX);
	float yaw = D3DXToRadian(degreeY);
	float roll = D3DXToRadian(degreeZ);

	D3DXQUATERNION q;

	D3DXQuaternionRotationYawPitchRoll(&q, yaw, pitch, roll);

	mImpl->insert(time, D3DXVECTOR3(x, y, z), q, animName);
}

void Lua::ModelTimeLineController::update(float elapsedTime)
{
	mImpl->update(elapsedTime);
}

void Lua::ModelTimeLineController::init()
{
	mImpl->init();
}

bool Lua::ModelTimeLineController::isAnimOver() const
{
	return mImpl->isOver();
}

MME::Object::ModelKaiSharedPtr Lua::ModelTimeLineController::getModel()
{
	return mImpl->mModel;
}
