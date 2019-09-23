#pragma once
#include"BulletPhysics/Manager.h"

class btRigidBody;

namespace BulletPhysics {


	//うーん、これダメっぽい
	//接地判定にcontactTestを使っているのだが、
	//どうしてもギリギリの所で接地してないと判定するようで(たぶん、物理エンジンにとってはそのほうが都合がよいのだろう)
	//このcontactTestを使う方法はだめ

	//10フレーム間接地判定を保持し、接地判定をするクラス
	//接地してるとkFilterSize以上接地していれば設置しているとみなす
	//マイフレームupdate()すること
	class OnGroundCheckerVerContactTest {
	public:
		OnGroundCheckerVerContactTest(
			btRigidBody* rb,
			short filterGroup = BulletPhysics::Manager::DefaultFilter,
			short filterMask = BulletPhysics::Manager::StaticFilter);
		virtual ~OnGroundCheckerVerContactTest();
		void update();
		bool isOnGroundAll()const;
		bool isOnGround()const;
	private:
		//disallow assign
		OnGroundCheckerVerContactTest(const OnGroundCheckerVerContactTest &);
		//disallow copy
		void operator =(const OnGroundCheckerVerContactTest &);

		enum {
			kArraySize = 10,
			kFilterSize=1
		};
		
		btRigidBody *mRigidbody;
		bool mIsOnGrounds[kArraySize];
		const short mGroup;
		const short mMask;
	};


}
