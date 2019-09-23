#ifndef __KZTR_CHARACTER_CONTROLLER_H__
#define __KZTR_CHARACTER_CONTROLLER_H__

#include <LinearMath/btVector3.h>
#include <BulletDynamics/Character/btCharacterControllerInterface.h>
#include <BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h>


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
///加速度減衰摩擦あり運動
/// あと　btGhostObject and btCollisionObject::CF_NO_CONTACT_RESPONSE work good well.
//<a href="http://www.bulletphysics.org/Bullet/phpBB3/viewtopic.php?f=9&t=5684">Physics Simulation Forum • View topic - Code Snippet: CharacterController + Ghost triggers</a>

class CharacterController: public btCharacterControllerInterface
{
protected:
	
	btScalar m_halfHeight;
	
	btPairCachingGhostObject* m_ghostObject;
	btConvexShape*   m_convexShape;//is also in m_ghostObject, but it needs to be convex, so we store it here to avoid upcast
	
	btScalar m_verticalVelocity;
	btScalar m_verticalOffset;
	btScalar m_fallSpeed;
	btScalar m_jumpSpeed;
	btScalar m_maxJumpHeight;
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
	//btScalar   m_velocityTimeInterval;//摩擦で減衰するのでいらない
	int m_upAxis;

	btScalar m_mass;
	
	btScalar m_maxSpeed;
	btVector3 m_accelNormalVel;//加速度は向き欲しい
	btScalar m_accelSpeed;
	static const btScalar sk_minAccelSpeed;//m_accelSpeedがこれ以下になったら0
	static const btScalar sk_minSpeed;//m_walkDirectionがこれ以下になったら0

	btScalar m_coefficientOfAccelration;//加速度係数、減速(Deceleration)係数の方が名前いい？
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
	void updateWalkeDirection(btScalar dt){
		//加速度足す
		m_walkDirection += m_accelNormalVel*m_accelSpeed*dt;
		m_accelSpeed *= m_coefficientOfAccelration;
		if( m_accelSpeed < sk_minAccelSpeed ){
			m_accelSpeed=0.0;
		}

		bool isBrake=false;
		btScalar resist =
			(isBrake) ? 0.4f : 0.0f ;
		resist +=
			( onGround() ) ? m_coefficientOfFriction : m_airResistance;
		
		btScalar speed0 = m_walkDirection.length();
		if( speed0 < sk_minSpeed ){
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
	CharacterController(btPairCachingGhostObject* ghostObject,btConvexShape* convexShape,btScalar stepHeight, int upAxis = 1);
	~CharacterController();
	
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
	virtual void   setWalkDirection(const btVector3& walkDirection);
	
	/// Caller provides a velocity with which the character should move for
	///   the given time period.  After the time period, velocity is reset
	///   to zero.
	/// This call will reset any walk direction set by setWalkDirection().
	/// Negative time intervals will result in no motion.
	virtual void setVelocityForTimeInterval(const btVector3& velocity,
	         btScalar timeInterval);
	
	
	void setTurnAngle(btScalar ang) { m_turnAngle = ang; };
	
	void reset ();
	void warp (const btVector3& origin);
	
	void preStep (  btCollisionWorld* collisionWorld);
	void playerStep ( btCollisionWorld* collisionWorld, btScalar dt);
	
	void setFallSpeed (btScalar fallSpeed)            { m_fallSpeed = btFabs(fallSpeed); }
	void setJumpSpeed (btScalar jumpSpeed)            { m_jumpSpeed = btFabs(jumpSpeed); }
	void setMaxJumpHeight (btScalar maxJumpHeight)      { m_maxJumpHeight = maxJumpHeight; }
	
	///
	bool isJumping ()const                        { return m_wasJumping; }
	///
	bool canJump() const                        { return onGround(); }
	
	void jump ();
	
	void setGravity(btScalar gravity)               { m_gravity = gravity; }
	btScalar getGravity() const                     { return m_gravity; }
	
	/// The max slope determines the maximum angle that the controller can walk up.
	/// The slope angle is measured in radians.
	void setMaxSlope(btScalar slopeRadians)            { m_maxSlopeRadians = slopeRadians; m_maxSlopeCosine = btCos(slopeRadians); }
	btScalar getMaxSlope() const                  { return m_maxSlopeRadians; }
	
	btPairCachingGhostObject* getGhostObject()         { return m_ghostObject; }
	void setUseGhostSweepTest(bool use)               { m_useGhostObjectSweepTest = use; }
	
	bool onGround () const                        { return m_verticalVelocity == 0.0 && m_verticalOffset == 0.0; }
	
	
	

	void applyCentralImpulse( const btVector3 & impulse ){
		btVector3 accel = impulse / m_mass;
		accel += m_accelNormalVel*m_accelSpeed;
		m_accelSpeed=accel.length();
		m_accelNormalVel=accel/m_accelSpeed;
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
	
	btScalar getCoefficientOfAccelration() const {
		return m_coefficientOfAccelration;
	}
	void setCoefficientOfAccelration( btScalar ka ) {
		assert( ka <= 1.0 );
		assert( ka >= 0.0 );
		m_coefficientOfAccelration=ka;
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
#endif // __KZTR_CHARACTER_CONTROLLER_H__

// oije_charactercontroller.h - End of file