#pragma once
#include"BulletPhysics/Manager.h"

class btRigidBody;

namespace BulletPhysics {


	//接地状態を保持するクラス
	//何回も衝突判定をしないようにするためのクラス
	//毎フレームupdate()すること
	class OnGroundChecker {
	public:
		OnGroundChecker(
			btRigidBody* rb,
			short filterGroup = BulletPhysics::DefaultFilter,
			short filterMask = BulletPhysics::StaticFilter);
		virtual ~OnGroundChecker();
		void update();
		bool isOnGround()const;
	private:
		//disallow assign
		OnGroundChecker(const OnGroundChecker &) = delete;
		//disallow copy
		void operator =(const OnGroundChecker &) = delete;

		
		btRigidBody *mRigidbody;
		const short mGroup;
		const short mMask;

		bool mIsOnGround;
	};


}