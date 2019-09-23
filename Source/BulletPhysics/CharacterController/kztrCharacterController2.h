#ifndef __KZTR_CHARACTER_CONTROLLER2_H__
#define __KZTR_CHARACTER_CONTROLLER2_H__

#include <LinearMath/btVector3.h>
//#include <BulletDynamics/Character/btCharacterControllerInterface.h>
#include <BulletDynamics/Dynamics/btActionInterface.h>

#include <BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h>
#include <list>


class btCollisionShape;
class btRigidBody;
class btCollisionWorld;
class btCollisionDispatcher;
class btPairCachingGhostObject;
class btConvexShape;

namespace kztr{
//---------------------------------------------------------------------------------------
///btKinematicCharacterController is an object that supports a sliding motion in a world.
///It uses a ghost object and convex sweep test to test for upcoming collisions. This is combined with discrete collision detection to recover from penetrations.
///Interaction between btKinematicCharacterController and dynamic rigid bodies needs to be explicity implemented by the user.

///加速度摩擦あり運動 あと　btGhostObject and btCollisionObject::CF_NO_CONTACT_RESPONSE work good well.
//<a href="http://www.bulletphysics.org/Bullet/phpBB3/viewtopic.php?f=9&t=5684">Physics Simulation Forum • View topic - Code Snippet: CharacterController + Ghost triggers</a>

class CharacterController2: public btActionInterface
{
protected:
	
	btScalar m_halfHeight;
	
	btPairCachingGhostObject* m_ghostObject;
	btConvexShape*   m_convexShape;//is also in m_ghostObject, but it needs to be convex, so we store it here to avoid upcast
	
	btScalar m_verticalVelocity;
	btScalar m_verticalOffset;
	btScalar m_fallSpeed;
	btScalar m_jumpSpeed;
	//btScalar m_maxJumpHeight;
	btScalar m_maxSlopeRadians; // Slope angle that is set (used for returning the exact value)
	btScalar m_maxSlopeCosine;  // Cosine equivalent of m_maxSlopeRadians (calculated once when set, for optimization)
	btScalar m_gravity;
	
	btScalar m_turnAngle;
	
	btScalar m_stepHeight;
	
	btScalar   m_addedMargin;//@todo: remove this and fix the code
	
	///this is the desired walk direction, set by the user
	btVector3   m_walkDirection;
	
	//some internal variables
	btVector3 m_currentPosition;
	btScalar  m_currentStepOffset;
	btVector3 m_targetPosition;
	
	///keep track of the contact manifolds
	btManifoldArray   m_manifoldArray;
	
	bool m_touchingContact;
	btVector3 m_touchingNormal;
	
	bool  m_wasOnGround;
	bool  m_wasJumping;
	bool   m_useGhostObjectSweepTest;
	bool   m_useWalkDirection;
	//	btScalar   m_velocityTimeInterval;
	int m_upAxis;

	btScalar m_mass;

	struct AccelData{
		bool isUsed;
		btScalar timeInterval;
		btVector3 accelVel;
		AccelData()
		:isUsed(false) {}

	};
	enum AccelDataArray{
		ACCEL_DATAS_NUM=20
	};
	AccelData m_accelDatas[ACCEL_DATAS_NUM];
	std::list<AccelData*> m_accelDatasUsedList;
	btScalar m_maxSpeed;
	btScalar m_minSpeed;
	btScalar m_airResistance;//空気抵抗係数
	btScalar m_coefficientOfFriction;//摩擦係数　動摩擦係数とか静止摩擦係数作る？
	
	static btVector3* getUpAxisDirections();
	
	btVector3 computeReflectionDirection (const btVector3& direction, const btVector3& normal);
	btVector3 parallelComponent (const btVector3& direction, const btVector3& normal);
	btVector3 perpindicularComponent (const btVector3& direction, const btVector3& normal);
	
	bool recoverFromPenetration ( btCollisionWorld* collisionWorld);
	void stepUp (btCollisionWorld* collisionWorld);
	void updateTargetPositionBasedOnCollision (const btVector3& hit_normal, btScalar tangentMag = btScalar(0.0), btScalar normalMag = btScalar(1.0));
	void stepForwardAndStrafe (btCollisionWorld* collisionWorld, const btVector3& walkMove);
	void stepDown (btCollisionWorld* collisionWorld, btScalar dt);
	

	//見つからなかったらfalseを返す、pOutはNULL;
	bool findNoUsedAccelData(AccelData** pOut){
		for( int i=0; i<ACCEL_DATAS_NUM; ++i ){
			if( m_accelDatas[i].isUsed==false ){
				*pOut=&m_accelDatas[i];
				return true;
			}
		}
		*pOut=NULL;
		return false;
	}

	void updateWalkeDirection(const btScalar &dt){
		for(
			std::list<AccelData*>::iterator it = m_accelDatasUsedList.begin(), end=m_accelDatasUsedList.end();
			it!=end; )
		{
			AccelData* a=*it;
			btScalar dtMoving = (dt < a->timeInterval ) ? dt : a->timeInterval;
			a->timeInterval -= dt;

			//加速度足す
			m_walkDirection += a->accelVel * dtMoving;
			
			//時間過ぎていたら
			if( a->timeInterval <=0 ){
				a->isUsed=false;
				it=m_accelDatasUsedList.erase( it );
			} else {
				++it;
			}
		}

		bool isBrake=false;
		btScalar resist =
			(isBrake) ? 0.4f : 0.0f ;
		resist +=
			( m_wasOnGround ) ? m_coefficientOfFriction : m_airResistance;
		
		btScalar speed0 = m_walkDirection.length();
		if( speed0==0.f ){
			return;
		}
		if( m_wasOnGround && speed0 < m_minSpeed ){
			m_walkDirection.setValue( 0.f, 0.f, 0.f );
			return;
		}
		btScalar speed = speed0 - resist*speed0;
		if( speed > m_maxSpeed ){
			speed=m_maxSpeed;
		}
		if( speed < resist ){
			speed=0.0;
		}
		
		m_walkDirection *= speed/speed0;
	}
public:
	CharacterController2(btPairCachingGhostObject* ghostObject,btConvexShape* convexShape,btScalar stepHeight, int upAxis = 1);
	~CharacterController2();
	
	///btActionInterface interface
	virtual void updateAction( btCollisionWorld* collisionWorld,btScalar deltaTime)
	{
	   preStep ( collisionWorld);
	   playerStep (collisionWorld, deltaTime);
	}
	
	///btActionInterface interface
	void   debugDraw(btIDebugDraw* debugDrawer);
	
	void setUpAxis (int axis)
	{
	   if (axis < 0)
	      axis = 0;
	   if (axis > 2)
	      axis = 2;
	   m_upAxis = axis;
	}
	
	/// This should probably be called setPositionIncrementPerSimulatorStep.
	/// This is neither a direction nor a velocity, but the amount to
	///   increment the position each simulation iteration, regardless
	///   of dt.
	/// This call will reset any velocity set by setVelocityForTimeInterval().
	void   setWalkDirection(const btVector3& walkDirection);
	
	/// Caller provides a velocity with which the character should move for
	///   the given time period.  After the time period,
	/// velocity is decreased by resistance(AirResistance or coefficient of friction).
	/// This call will reset any walk direction set by setWalkDirection().
	/// Negative time intervals will result in no motion.
	//virtual void setVelocityForTimeInterval(const btVector3& velocity, btScalar timeInterval);
	
	/// Caller set velocity.,
	/// velocity is decreased by resistance(AirResistance or coefficient of friction).
	/// This call will reset any walk direction set by setWalkDirection().
	/// Negative time intervals will result in no motion.
	void setVelocity( const btVector3& velocity ){
		m_walkDirection=velocity;
		m_useWalkDirection=false;
	}

	btVector3 getVelocity() const {
		if( m_useWalkDirection ){
			return m_walkDirection*60.f;
		}
		else{
			return m_walkDirection;
		}
	}



	/// Caller push back list as AccelData; accelData in list is added to Velosity for timeInterval.
	/// After the time period, accelData is removed from list.
	/// if list is full, retrun false;
	/// This call will reset any walk direction set by setWalkDirection().
	bool addAccelVelocityForTimeInterval(const btVector3& accel, btScalar timeInterval){
		if( timeInterval <= 0){ return false; }

		AccelData* pA=NULL;
		if( findNoUsedAccelData( &pA ) ){
			pA->accelVel=accel;
			pA->timeInterval = timeInterval;
			pA->isUsed = true;
			m_accelDatasUsedList.push_back( pA );
			m_useWalkDirection = false;

			return true;
		}
		else{
			return false;
		}
	}
	
	void resetAllAccelVelocity(){
		for( int i=0; i<ACCEL_DATAS_NUM; ++i ){
			m_accelDatas[i].isUsed=false;
		}
		m_accelDatasUsedList.clear();
	}

	void setTurnAngle(btScalar ang) { m_turnAngle = ang; };
	
	void reset ();
	void warp (const btVector3& origin);
	
	void preStep (  btCollisionWorld* collisionWorld);
	void playerStep ( btCollisionWorld* collisionWorld, btScalar dt);
	
	void setFallSpeed (btScalar fallSpeed)            { m_fallSpeed = btFabs(fallSpeed); }
	void setJumpSpeed (btScalar jumpSpeed)            { m_jumpSpeed = btFabs(jumpSpeed); }
	//void setMaxJumpHeight (btScalar maxJumpHeight)      { m_maxJumpHeight = maxJumpHeight; }
	
	///
	bool isJumping ()const                        { return m_wasJumping; }
	///
	bool canJump() const                        { return onGround(); }
	
	void jump ();
	void forceJump();
	
	void setGravity(btScalar gravity)               { m_gravity = gravity; }
	btScalar getGravity() const                     { return m_gravity; }
	
	/// The max slope determines the maximum angle that the controller can walk up.
	/// The slope angle is measured in radians.
	void setMaxSlope(btScalar slopeRadians)            { m_maxSlopeRadians = slopeRadians; m_maxSlopeCosine = btCos(slopeRadians); }
	btScalar getMaxSlope() const                  { return m_maxSlopeRadians; }
	
	btPairCachingGhostObject* getGhostObject()         { return m_ghostObject; }
	void setUseGhostSweepTest(bool use)               { m_useGhostObjectSweepTest = use; }
	
	bool onGround () const;
	
	//力積（りきせき、英語：impulse）は力の大きさと力が働く時間を掛けあわせたもの
	void applyCentralImpulse( const btVector3 & impulse ){
		btVector3 accel = impulse / m_mass;
		m_walkDirection += accel;
	}

	btScalar getMass() const {
		return m_mass;
	}
	void setMass( btScalar mass ){
		m_mass=mass;
	}
	
	btScalar getMaxSpeed() const {
		return m_maxSpeed;
	}

	void setMaxSpeed(btScalar maxSpeed){
		m_maxSpeed=maxSpeed;
	}


	btScalar getMinSpeed() const {
		return m_minSpeed;
	}

	void setMinSpeed(btScalar minSpeed){
		m_minSpeed=minSpeed;
	}

	btScalar getAirResistance() const {
		return m_airResistance;
	}
	void setAirResistance( btScalar ar ) {
		assert( ar <= 1.0 );
		assert( ar >= 0.0 );
		m_airResistance=ar;
	}

	btScalar getCoefficientOfFriction() const {
		return m_coefficientOfFriction;
	}
	void setCoefficientOfFriction( btScalar cf ) {
		assert( cf <= 1.0 );
		assert( cf >= 0.0 );
		m_coefficientOfFriction=cf;
	}
};
//---------------------------------------------------------------------------------------
} //namespace kztr
#endif // __KZTR_CHARACTER_CONTROLLER2_H__

// oije_charactercontroller.h - End of file