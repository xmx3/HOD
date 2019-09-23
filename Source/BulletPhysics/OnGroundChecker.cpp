#include"OnGroundChecker.h"
#include"OnGround.h"

namespace BulletPhysics {


OnGroundChecker::OnGroundChecker(
	btRigidBody* rb,
	short filterGroup,
	short filterMask )
	:mRigidbody(rb),
	mGroup(filterGroup),
	mMask(filterMask),
	mIsOnGround(true)
{
	update();
}

OnGroundChecker::~OnGroundChecker() {}

void OnGroundChecker::update() {
	mIsOnGround = onGroundVerRayTest(mRigidbody, mGroup, mMask);;
}

bool OnGroundChecker::isOnGround()const {
	return mIsOnGround;
}

}//end namespace BulletPhysics