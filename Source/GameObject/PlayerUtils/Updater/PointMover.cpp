#include"PointMover.h"
#include<btBulletDynamicsCommon.h>
#include"BulletPhysics/Manager.h"
#include"GameObjectData/Status.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { 
PointMover::PointMover(btRigidBody* rb, GameObjectData::Status *s)
	:mStatus(s),
	mRigidBody(rb),
	mFilterGroup(BulletPhysics::DefaultFilter),
	mFilterMask( ~BulletPhysics::AllFilterExceptMMDObject ),
	mMass(s->mass),
	mTargetPos( rb->getWorldTransform().getOrigin() ),
	mEyePos( rb->getWorldTransform().getOrigin() ),
	mAccel( s->accel ),
	mMaxSpeed(s->speed),
	mMaxAngularSpeed(s->angleSpeed),
	mAngle(0.1f),//0以外のにしといたほうがいいかも
	mOldPos(rb->getWorldTransform().getOrigin()),
	mIsLookingFinished(false)
{}

PointMover::~PointMover(){}

	
//void PointMover::move( const btVector3 &pos ){}
//void PointMover::moveForward( const float &moveValue ){}
	
//void PointMover::jump(){}

// jump If have enough stamina.
//bool PointMover::jumpIf(){}

//その場に停止
void PointMover::stop(){
	mRigidBody->clearForces();
	mRigidBody->setLinearVelocity( btVector3( 0.f, 0.f, 0.f ) );
	mEyePos=mTargetPos=mRigidBody->getWorldTransform().getOrigin();
	mIsLookingFinished = true;
}

////摩擦で自動にとまる(慣性あり)
//void PointMover:: cut(){
//	mRigidBody->setLinearVelocity( btVector3( 0.f, 0.f, 0.f ) );
//	mEyePos=mTargetPos=mRigidBody->getWorldTransform().getOrigin();
//}

void PointMover::look( const btVector3 & pos ){
	mEyePos=pos;
	mIsLookingFinished = false;
}
	
//回転なしの移動
void PointMover::strafe( const btVector3 & pos ){
	mTargetPos=pos;
	mOldPos=mRigidBody->getWorldTransform().getOrigin();
}

void PointMover::updateStrafe( float elapsedTime ){
	const btTransform &xform = mRigidBody->getWorldTransform ();
	const btVector3 &pos=xform.getOrigin();
	if(pos==mTargetPos){
		return;
	}
	
	//移動
	btVector3 targetDir = mTargetPos-pos;
	targetDir.setY(0.f);		
	const float distance = targetDir.length();

	btVector3 forceDir = targetDir - mRigidBody->getLinearVelocity();
	float forceLen = forceDir.length();
	assert(forceLen!=0);
	assert(distance!=0);

	//正規化
	forceDir / forceLen;
	targetDir /= distance;


	//90度以上の場合(ブレーキがかかる場合)
	if( forceDir.dot(targetDir) < 0.f ){
		forceDir=targetDir;
	}

	mRigidBody->applyCentralImpulse( forceDir*mAccel*mMass );

	btVector3 vel = mRigidBody->getLinearVelocity();
	float speed=vel.length();
	assert(speed!=0.f);
	vel /= speed;//正規化

	if( mMaxSpeed<speed ){
		mRigidBody->setLinearVelocity(vel*mMaxSpeed);
		speed=mMaxSpeed;
	}
	
	//前回の距離、方向を求める
	btVector3 targetDir0 = mTargetPos-mOldPos;
	//targetDir0.setY(0.f);		
	float distance0 = targetDir0.length();
	

	if( distance < speed*elapsedTime || distance < 1.f || distance0 < distance ){
		mTargetPos = pos;
		stop();
		vel.setZero();
	}

	mOldPos=pos;
}

void PointMover::updateLook( const float elapsedTime ){
	const btTransform &xform = mRigidBody->getWorldTransform ();
	
	if(mIsLookingFinished){
		return;
	}

	//軸を求める
	btVector3 forwardDir = xform.getBasis()[2];
	forwardDir.setX(-forwardDir.x());
	//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
	forwardDir = -forwardDir;
	forwardDir.normalize ();

	btVector3 upDir = xform.getBasis()[1];
	btVector3 strafeDir = xform.getBasis()[0];
	upDir.normalize ();
	strafeDir.normalize();
	
	//targetの方向に向く
	//回転する角度を求める
	mAngle = 0.f;

	//mEyeをオブジェクト"上平面状"に落とす。
	btVector3 targetDir = mEyePos-xform.getOrigin();
	targetDir -= targetDir.dot( upDir ) * upDir;
	//0割対策
	if( targetDir.fuzzyZero()  ){
		mAngle = 0.f;
	} else {
		targetDir.normalize();
		float dot;
		dot =  forwardDir.dot(targetDir);
		if( dot > 1.f ){
			dot=1.f;
		}
		mAngle = acosf( forwardDir.dot(targetDir) );
		//非数の場合、(同じ方向の場合)
		if( mAngle!=mAngle ){
			//mHasTurned = true;				
			mAngle = 0.f;
		}
	}
	
	//120度以上の場合 ブレーキかける
	//if(mAngle>3.14159265f*2.f/3.f){
	//	isBrake=true;
	//}

	//rigidbodyを回転させる
	if(mAngle!=0.f){
		//回転させる量
		btScalar angularSpeed = mMaxAngularSpeed * elapsedTime;
		if( mAngle > angularSpeed ){
			mAngle=angularSpeed;
		} else {
			mIsLookingFinished = true;
		}
		//回転が右か左か。cosで+-が消えてるのですべて＋の回転になっているので
		//外積のy軸を求めてねじの回転方向を調べる
		//btVector3 cross=forwardDir.cross(targetDir);
		//if( cross.y() < 0.f){
		if(	forwardDir[2] * targetDir[0] - forwardDir[0] * targetDir[2] < 0.f ){
			mAngle = -mAngle;
		}
		btMatrix3x3 orn = xform.getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0), mAngle));
		mRigidBody->getWorldTransform ().setBasis(orn);
	} else {
		mIsLookingFinished = true;
	}
}

bool PointMover::isStopped() const{
	return !isTurning() && !isMoving();
}

bool PointMover::isTurning() const{
	return mAngle!=0.f;
}
bool PointMover::isMoving() const{
	return mTargetPos!=mRigidBody->getWorldTransform().getOrigin();
}
//bool PointMover::onGround() const{}
//
//	//スタミナ減少のみ
//bool PointMover::useStaminaIfCanRunHigh(){}	
//bool PointMover::useStaminaIfCanRun(){}
//bool PointMover::useStaminaIfCanWalk(){}
//
//void PointMover::setMaxSpeed( float speed ){}
//
//void PointMover::setMaxSpeedToLow(){}
//void PointMover::setMaxSpeedToNormal(){}
//void PointMover::setMaxSpeedToHigh(){}
//
//void PointMover::healStamina(){}

} } } //GameObject::PlayerUtils::Updater