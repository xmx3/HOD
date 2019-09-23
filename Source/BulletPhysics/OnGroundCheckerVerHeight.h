#pragma once
#include"BulletPhysics/Manager.h"

class btRigidBody;

namespace BulletPhysics {


	
	//10フレーム間位置情報の高さyを保持し、接地判定をするクラス
	//弱点 坂
	//マイフレームupdate()すること
	class OnGroundCheckerVerHeight {
	public:
		OnGroundCheckerVerHeight(
			btRigidBody* rb,
			short filterGroup = BulletPhysics::Manager::DefaultFilter,
			short filterMask = BulletPhysics::Manager::StaticFilter);
		virtual ~OnGroundCheckerVerHeight();
		void update();
		bool isOnGround()const;
	private:
		//disallow assign
		OnGroundCheckerVerHeight(const OnGroundCheckerVerHeight &);
		//disallow copy
		void operator =(const OnGroundCheckerVerHeight &);

		enum {
			kArraySize = 10,
		};
		
		btRigidBody *mRigidbody;
		float mHeights[kArraySize];
		const short mGroup;
		const short mMask;

		bool mIsOnGround;
	};


}