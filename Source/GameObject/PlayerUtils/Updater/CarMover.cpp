#include"CarMover.h"
#include<btBulletDynamicsCommon.h>
//#include<btBulletCollisionCommon.h>
//#include<BulletDynamics/Dynamics/btRigidBody.h>
#include"GameObjectData/Status.h"
#include"BulletPhysics/HelperCallbacks.h"
#include"BulletPhysics/Manager.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { 
CarMover::CarMover(btRigidBody* rb, GameObjectData::Status *s)
	:mRigidBody(rb),
	mStatus(s)
{}
CarMover::~CarMover(){
	mRigidBody=0;
	mStatus=0;
}

void CarMover::applyImpulseTowardTarget(const btVector3& targetPos, float elapsedTime ){
	
	const float &accel = mStatus->accel;
	const float &maxSpeed = mStatus->speed;
	const float &angleSpeed = mStatus->angleSpeed;
	const float &mass = mStatus->mass;

	const float rateBeforeSpeed=0.1f;

	btTransform xform = mRigidBody->getWorldTransform();
	//軸を求める
	//xform*z0
	btVector3 forwardDir = xform.getBasis()[2];
	forwardDir.setX(-forwardDir.x());
	//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
	forwardDir = -forwardDir;
	forwardDir.normalize ();

	btVector3 upDir = xform.getBasis()[1];
	btVector3 strafeDir = xform.getBasis()[0];
	upDir.normalize ();
	strafeDir.normalize();


	//水平に落としたtargetDirとforwardDirの間の角度
	float angleBetweenForwardAndTarget=0.f;

	//targetの方向に向く
	{
		//回転する角度
		float theata = 0.f;

		//targetPosをオブジェクト"上平面状"に落とす。
		btVector3 targetDir = targetPos-xform.getOrigin();
		targetDir -= targetDir.dot( upDir ) * upDir;
		//0割対策
		if( targetDir.length2() == 0.f ){
			theata = 0.f;
		} else {
			targetDir.normalize();
			float dot;
			dot =  forwardDir.dot(targetDir);
			if( dot > 1.f ){
				dot=1.f;
			}
			theata = acosf( forwardDir.dot(targetDir) );
		}
		//非数の場合、(同じ方向の場合)
		if( theata!=theata ){
			theata = 0.f;
		}

		if(theata!=0.f){
			//回転させる量(一秒で45度回転)
			btScalar angularSpeed = angleSpeed * elapsedTime;
			//assert( theata>=0.f );
			angleBetweenForwardAndTarget = theata;
			if( theata > angularSpeed ){
				theata=angularSpeed;
			}
			//回転が右か左か。cosで+-が消えてるのですべて＋の回転になっているので
			btVector3 cross=forwardDir.cross(targetDir);
			if( cross.y() < 0.f){
				theata=-theata;
			}
			btMatrix3x3 orn = xform.getBasis();
			orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0), theata));
			mRigidBody->getWorldTransform ().setBasis(orn);
			btVector3 vel=mRigidBody->getLinearVelocity();
			float speed=vel.length();
			vel.normalize();
			targetDir;

			//移動向きののコントロール
			mRigidBody->setLinearVelocity( ( (1-rateBeforeSpeed)*vel+targetDir*rateBeforeSpeed ) * speed );
			//シンプルにこっちか？
			//mRigidBody->setLinearVelocity( ( (1-rateBeforeSpeed)*vel ) * speed );

		}
	}

	//移動
	{
		btVector3 walkDir = targetPos-xform.getOrigin();
		walkDir.setY(0.f);		
		const float distance = walkDir.length();

		if(distance < 0.001){

		}
		else
		{
			walkDir.normalize();

			//when theata=0;
			//	cos( theata*0.5f )=1.f;
			//when theata=PI/2;
			//	cos( theata*0.5f )=1.f/squrt(2.f);
			//when theata=PI;
			//	cos( theata*0.5f )=0.f;

			//向きが真正面じゃないときの遅くするためのもの
			float rate = cosf( 0.5f*angleBetweenForwardAndTarget );

			mRigidBody->applyCentralImpulse( walkDir*accel*mass*rate );
			limitSpeed( maxSpeed );			
		}
	}
}

void CarMover::limitSpeed( float maxSpeed ){
	const btVector3 &vel = mRigidBody->getLinearVelocity();
	float speed2=vel.length2();
	if( maxSpeed*maxSpeed < speed2 ){
		float speed = sqrt( speed2 );
		mRigidBody->setLinearVelocity(vel/speed*maxSpeed);
	}
}
void CarMover::applyImpulseTowardTargetIf(const btVector3& target, float elapsedTime ){
	if( mStatus->canRun( elapsedTime ) ){
		applyImpulseTowardTarget( target, elapsedTime );
	}
}

const btCollisionObject* CarMover::rayTest( const btVector3 &start, const btVector3 &end ){

	//始点と終点
	
	
	BulletPhysics::ClosestRayResultCallbackToIgnoreObject cb( mRigidBody );
	cb.m_collisionFilterMask = BulletPhysics::AllFilterExceptMMDObject;
		
	BulletPhysics::Manager::instance()->getWorldPtr()->rayTest( start, end, cb );

	if (cb.hasHit())
	{
		return cb.m_collisionObject;
	}

	
	return 0;
}

} } } //GameObject::PlayerUtils::Updater