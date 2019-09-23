#include"OnGroundCheckerVerHeight.h"
#include"OnGround.h"

namespace BulletPhysics {


OnGroundCheckerVerHeight::OnGroundCheckerVerHeight(
	btRigidBody* rb,
	short filterGroup,
	short filterMask )
	:mRigidbody(rb),
	mGroup(filterGroup),
	mMask(filterMask),
	mIsOnGround(true)
{
	for (float &h : mHeights) {
		h=mRigidbody->getWorldTransform().getOrigin().y();
	}
}

OnGroundCheckerVerHeight::~OnGroundCheckerVerHeight() {}

void OnGroundCheckerVerHeight::update() {
	for (int i = kArraySize-1; i > 0; --i) {
		mHeights[i] = mHeights[i - 1];
	}

	mHeights[0] = mRigidbody->getWorldTransform().getOrigin().getY();

	float total = 0.f;
	for (float h : mHeights) {
		total += h;
	}
	float average = total / kArraySize;

	static const float threshold = 0.1f;//しきい値

	if (std::fabsf(average - mHeights[0]) > threshold) {
		mIsOnGround = false;
	}
	else {
		mIsOnGround = true;
	}
}

bool OnGroundCheckerVerHeight::isOnGround()const {
	return mIsOnGround;
}

}//end namespace BulletPhysics