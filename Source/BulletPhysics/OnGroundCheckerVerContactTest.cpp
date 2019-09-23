#include"OnGroundCheckerVerContactTest.h"
#include"OnGround.h"

namespace BulletPhysics {


OnGroundCheckerVerContactTest::OnGroundCheckerVerContactTest(
	btRigidBody* rb,
	short filterGroup,
	short filterMask )
	:mRigidbody(rb),
	mGroup(filterGroup),
	mMask(filterMask)
{
	for (bool &b : mIsOnGrounds) {
		b = true;
	}
}

OnGroundCheckerVerContactTest::~OnGroundCheckerVerContactTest() {}

void OnGroundCheckerVerContactTest::update() {
	for (int i = kArraySize-1; i > 0; --i) {
		mIsOnGrounds[i] = mIsOnGrounds[i - 1];
	}

	mIsOnGrounds[0] = OnGroundCheckerVerContactTest(mRigidbody,
		mGroup,
		mMask);
}

bool OnGroundCheckerVerContactTest::isOnGroundAll()const {
	for (bool b : mIsOnGrounds) {
		if (!b) {
			return false;
		}
	}
	return true;
}

bool OnGroundCheckerVerContactTest::isOnGround()const {
	int count = 0;
	for (bool b : mIsOnGrounds) {
		if (b) {
			++count;
		}
	}
	if (count > kFilterSize) {
		return true;
	}
	return false;
}

}//end namespace BulletPhysics
