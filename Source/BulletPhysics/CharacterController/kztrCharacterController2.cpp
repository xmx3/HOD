/**
 * Orginal licence:
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2008 Erwin Coumans  http://bulletphysics.com

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "kztrCharacterController2.h"

#include <LinearMath/btIDebugDraw.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/CollisionShapes/btMultiSphereShape.h>
#include <BulletCollision/BroadphaseCollision/btOverlappingPairCache.h>
#include <BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <LinearMath/btDefaultMotionState.h>

#include <iostream>

#include"helper/PrintBtVector3.h"
#include"helper/MyOutputDebugString.h"

#include"GameObject/CharacterControllerGhostObject.h"

#include <boost/timer.hpp>
#include <boost/lexical_cast.hpp>


namespace kztr{

//---------------------------------------------------------------------------------------
// static helper method
static btVector3 getNormalizedVector(const btVector3& v)
{
   btVector3 n = v.normalized();
   if (n.length() < SIMD_EPSILON) {
      n.setValue(0, 0, 0);
   }
   return n;
}
//---------------------------------------------------------------------------------------
///@todo Interact with dynamic objects,
///Ride kinematicly animated platforms properly
///More realistic (or maybe just a config option) falling
/// -> Should integrate falling velocity manually and use that in stepDown()
///Support jumping
///Support ducking
class btKinematicClosestNotMeRayResultCallback : public btCollisionWorld::ClosestRayResultCallback
{
public:
   btKinematicClosestNotMeRayResultCallback (btCollisionObject* me) : btCollisionWorld::ClosestRayResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0))
   {
      m_me = me;
   }

   virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace)
   {
      if (rayResult.m_collisionObject == m_me)
         return 1.0;

      return ClosestRayResultCallback::addSingleResult (rayResult, normalInWorldSpace);
   }
protected:
   btCollisionObject* m_me;
};
//---------------------------------------------------------------------------------------
class btKinematicClosestNotMeConvexResultCallback : public btCollisionWorld::ClosestConvexResultCallback
{
public:
   btKinematicClosestNotMeConvexResultCallback (btCollisionObject* me, const btVector3& up, btScalar minSlopeDot)
   : btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0))
   , m_me(me)
   , m_up(up)
   , m_minSlopeDot(minSlopeDot)
   {
   }

   virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult,bool normalInWorldSpace)
   {
      if (convexResult.m_hitCollisionObject == m_me)
         return btScalar(1.0);
   
      //for trigger filtering
      if (!convexResult.m_hitCollisionObject->hasContactResponse())
         return btScalar(1.0);

      btVector3 hitNormalWorld;
      if (normalInWorldSpace)
      {
         hitNormalWorld = convexResult.m_hitNormalLocal;
      } else
      {
         ///need to transform normal into worldspace
         hitNormalWorld = convexResult.m_hitCollisionObject->getWorldTransform().getBasis()*convexResult.m_hitNormalLocal;
      }

      btScalar dotUp = m_up.dot(hitNormalWorld);
      if (dotUp < m_minSlopeDot) {
         return btScalar(1.0);
      }

      return ClosestConvexResultCallback::addSingleResult (convexResult, normalInWorldSpace);
   }
protected:
   btCollisionObject* m_me;
   const btVector3 m_up;
   btScalar m_minSlopeDot;
};
//---------------------------------------------------------------------------------------
/*
 * Returns the reflection direction of a ray going 'direction' hitting a surface with normal 'normal'
 *
 * from: http://www-cs-students.stanford.edu/~adityagp/final/node3.html
 */
btVector3 CharacterController2::computeReflectionDirection (const btVector3& direction, const btVector3& normal)
{
   return direction - (btScalar(2.0) * direction.dot(normal)) * normal;
}
//---------------------------------------------------------------------------------------
/*
 * Returns the portion of 'direction' that is parallel to 'normal'
 */
btVector3 CharacterController2::parallelComponent (const btVector3& direction, const btVector3& normal)
{
   btScalar magnitude = direction.dot(normal);
   return normal * magnitude;
}
//---------------------------------------------------------------------------------------
/*
 * Returns the portion of 'direction' that is perpindicular to 'normal'
 */
btVector3 CharacterController2::perpindicularComponent (const btVector3& direction, const btVector3& normal)
{
   return direction - parallelComponent(direction, normal);
}
//---------------------------------------------------------------------------------------
CharacterController2::CharacterController2 (btPairCachingGhostObject* ghostObject,btConvexShape* convexShape,btScalar stepHeight, int upAxis)
{
	m_upAxis = upAxis;
	m_addedMargin = 0.02f;
	m_walkDirection.setValue(0,0,0);
	m_useGhostObjectSweepTest = true;
	m_ghostObject = ghostObject;
	m_stepHeight = stepHeight;
	m_turnAngle = btScalar(0.0);
	m_convexShape=convexShape;   
	m_useWalkDirection = true;   // use walk direction by default, legacy behavior
	m_verticalVelocity = 0.0;
	m_verticalOffset = 0.0;
	m_gravity = 9.8f * 3.0f ; // 3G acceleration.
	m_fallSpeed = 55.0f; // Terminal velocity of a sky diver in m/s.
	m_jumpSpeed = 10.0f; // ?
	m_wasOnGround = false;
	m_wasJumping = false;
	setMaxSlope(btRadians(45.0f));
	
	m_mass=1.f;
	
	m_maxSpeed=100000.0f;
	m_minSpeed=1.0f;
	m_airResistance=0.01f;//‹ó‹C’ïRŒW”
	m_coefficientOfFriction=0.05f;//0.1//–€ŽCŒW”@“®–€ŽCŒW”‚Æ‚©ÃŽ~–€ŽCŒW”ì‚éH
	resetAllAccelVelocity();
}
//---------------------------------------------------------------------------------------
CharacterController2::~CharacterController2 ()
{
}
//---------------------------------------------------------------------------------------
bool CharacterController2::recoverFromPenetration ( btCollisionWorld* collisionWorld)
{

   bool penetration = false;

   collisionWorld->getDispatcher()->dispatchAllCollisionPairs(m_ghostObject->getOverlappingPairCache(), collisionWorld->getDispatchInfo(), collisionWorld->getDispatcher());

   m_currentPosition = m_ghostObject->getWorldTransform().getOrigin();
   
   btScalar maxPen = btScalar(0.0);
   for (int i = 0; i < m_ghostObject->getOverlappingPairCache()->getNumOverlappingPairs(); i++)
   {
      m_manifoldArray.resize(0);

      btBroadphasePair* collisionPair = &m_ghostObject->getOverlappingPairCache()->getOverlappingPairArray()[i];

      //for trigger filtering
	  //ignore when collision flag is CF_NO_CONTACT_RESPONSE
      if (!static_cast<btCollisionObject*>(collisionPair->m_pProxy0->m_clientObject)->hasContactResponse()
         || !static_cast<btCollisionObject*>(collisionPair->m_pProxy1->m_clientObject)->hasContactResponse())
         continue;
      
      if (collisionPair->m_algorithm)
         collisionPair->m_algorithm->getAllContactManifolds(m_manifoldArray);
      
      for (int j=0;j<m_manifoldArray.size();j++)
      {
         btPersistentManifold* manifold = m_manifoldArray[j];
         btScalar directionSign = manifold->getBody0() == m_ghostObject ? btScalar(-1.0) : btScalar(1.0);
         for (int p=0;p<manifold->getNumContacts();p++)
         {
            const btManifoldPoint&pt = manifold->getContactPoint(p);

            btScalar dist = pt.getDistance();

            if (dist < 0.0)
            {
               if (dist < maxPen)
               {
                  maxPen = dist;
                  m_touchingNormal = pt.m_normalWorldOnB * directionSign;//??

               }
               m_currentPosition += pt.m_normalWorldOnB * directionSign * dist * btScalar(0.2);
               penetration = true;
            } else {
               //printf("touching %f\n", dist);
            }
         }
         
         //manifold->clearManifold();
      }
   }
   btTransform newTrans = m_ghostObject->getWorldTransform();
   newTrans.setOrigin(m_currentPosition);
   m_ghostObject->setWorldTransform(newTrans);
//   printf("m_touchingNormal = %f,%f,%f\n",m_touchingNormal[0],m_touchingNormal[1],m_touchingNormal[2]);
   return penetration;
}
//---------------------------------------------------------------------------------------
void CharacterController2::stepUp ( btCollisionWorld* world)
{
   // phase 1: up
   btTransform start, end;
   m_targetPosition = m_currentPosition + getUpAxisDirections()[m_upAxis] * (m_stepHeight + (m_verticalOffset > 0.f?m_verticalOffset:0.f));

   start.setIdentity ();
   end.setIdentity ();

   /* FIXME: Handle penetration properly */
   start.setOrigin (m_currentPosition + getUpAxisDirections()[m_upAxis] * (m_convexShape->getMargin() + m_addedMargin));
   end.setOrigin (m_targetPosition);

   btKinematicClosestNotMeConvexResultCallback callback (m_ghostObject, -getUpAxisDirections()[m_upAxis], btScalar(0.7071));
   callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
   callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;
   
   if (m_useGhostObjectSweepTest)
   {
      m_ghostObject->convexSweepTest (m_convexShape, start, end, callback, world->getDispatchInfo().m_allowedCcdPenetration);
   }
   else
   {
      world->convexSweepTest (m_convexShape, start, end, callback);
   }
   
   if (callback.hasHit())
   {
      // Only modify the position if the hit was a slope and not a wall or ceiling.
      if(callback.m_hitNormalWorld.dot(getUpAxisDirections()[m_upAxis]) > 0.0)
      {
         // we moved up only a fraction of the step height
         m_currentStepOffset = m_stepHeight * callback.m_closestHitFraction;
         m_currentPosition.setInterpolate3 (m_currentPosition, m_targetPosition, callback.m_closestHitFraction);
      }
      m_verticalVelocity = 0.0;
      m_verticalOffset = 0.0;
   } else {
      m_currentStepOffset = m_stepHeight;
      m_currentPosition = m_targetPosition;
   }
}
//---------------------------------------------------------------------------------------
void CharacterController2::updateTargetPositionBasedOnCollision (const btVector3& hitNormal, btScalar tangentMag, btScalar normalMag)
{
   btVector3 movementDirection = m_targetPosition - m_currentPosition;
   btScalar movementLength = movementDirection.length();
   if (movementLength>SIMD_EPSILON)
   {
      movementDirection.normalize();

      btVector3 reflectDir = computeReflectionDirection (movementDirection, hitNormal);
      reflectDir.normalize();

      btVector3 parallelDir, perpindicularDir;

      parallelDir = parallelComponent (reflectDir, hitNormal);
      perpindicularDir = perpindicularComponent (reflectDir, hitNormal);

      m_targetPosition = m_currentPosition;
      if (0)//tangentMag != 0.0)
      {
         btVector3 parComponent = parallelDir * btScalar (tangentMag*movementLength);
//         printf("parComponent=%f,%f,%f\n",parComponent[0],parComponent[1],parComponent[2]);
         m_targetPosition +=  parComponent;
      }

      if (normalMag != 0.0)
      {
         btVector3 perpComponent = perpindicularDir * btScalar (normalMag*movementLength);
//         printf("perpComponent=%f,%f,%f\n",perpComponent[0],perpComponent[1],perpComponent[2]);
         m_targetPosition += perpComponent;
      }
   } else
   {
//      printf("movementLength don't normalize a zero vector\n");
   }
}
//---------------------------------------------------------------------------------------
void CharacterController2::stepForwardAndStrafe ( btCollisionWorld* collisionWorld, const btVector3& walkMove)
{
   // phase 2: forward and strafe
   btTransform start, end;
   m_targetPosition = m_currentPosition + walkMove;

   start.setIdentity ();
   end.setIdentity ();
   
   btScalar fraction = 1.0;
   btScalar distance2 = (m_currentPosition-m_targetPosition).length2();
//   printf("distance2=%f\n",distance2);

   btVector3 normalizedDirection = getNormalizedVector(m_walkDirection);

   if (m_touchingContact)
   {
      if (normalizedDirection.dot(m_touchingNormal) > btScalar(0.0))
      {
         updateTargetPositionBasedOnCollision (m_touchingNormal);
      }
   }

   int maxIter = 10;

   while (fraction > btScalar(0.01) && maxIter-- > 0)
   {
      start.setOrigin (m_currentPosition);
      end.setOrigin (m_targetPosition);
      btVector3 sweepDirNegative(m_currentPosition - m_targetPosition);

      btKinematicClosestNotMeConvexResultCallback callback (m_ghostObject, sweepDirNegative, btScalar(0.0));
      callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
      callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;


      btScalar margin = m_convexShape->getMargin();
      m_convexShape->setMargin(margin + m_addedMargin);


      if (m_useGhostObjectSweepTest)
      {
         m_ghostObject->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
      } else
      {
         collisionWorld->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
      }
      
      m_convexShape->setMargin(margin);

      
      fraction -= callback.m_closestHitFraction;

      if (callback.hasHit())
      {   
         // we moved only a fraction
         btScalar hitDistance;
         hitDistance = (callback.m_hitPointWorld - m_currentPosition).length();

//         m_currentPosition.setInterpolate3 (m_currentPosition, m_targetPosition, callback.m_closestHitFraction);

         updateTargetPositionBasedOnCollision (callback.m_hitNormalWorld);
         btVector3 currentDir = m_targetPosition - m_currentPosition;
         distance2 = currentDir.length2();
         if (distance2 > SIMD_EPSILON)
         {
            currentDir.normalize();
            /* See Quake2: "If velocity is against original velocity, stop ead to avoid tiny oscilations in sloping corners." */
            if (currentDir.dot( normalizedDirection ) <= btScalar(0.0))
            {
               break;
            }
         } else
         {
//            printf("currentDir: don't normalize a zero vector\n");
            break;
         }

      } else {
         // we moved whole way
         m_currentPosition = m_targetPosition;
      }

   //   if (callback.m_closestHitFraction == 0.f)
   //      break;

   }
}
//---------------------------------------------------------------------------------------
void CharacterController2::stepDown ( btCollisionWorld* collisionWorld, btScalar dt)
{
   btTransform start, end;

   // phase 3: down
   /*btScalar additionalDownStep = (m_wasOnGround && !onGround()) ? m_stepHeight : 0.0;
   btVector3 step_drop = getUpAxisDirections()[m_upAxis] * (m_currentStepOffset + additionalDownStep);
   btScalar downVelocity = (additionalDownStep == 0.0 && m_verticalVelocity<0.0?-m_verticalVelocity:0.0) * dt;
   btVector3 gravity_drop = getUpAxisDirections()[m_upAxis] * downVelocity;
   m_targetPosition -= (step_drop + gravity_drop);*/

   btScalar downVelocity = (m_verticalVelocity<0.f?-m_verticalVelocity:0.f) * dt;
   if(downVelocity > 0.0// && downVelocity < m_stepHeight //TEST
      && (m_wasOnGround || !m_wasJumping))
   {
      //if (downVelocity < m_stepHeight) //TODO to jak do ziemi <m_stepHeight
      //   downVelocity = m_stepHeight;
      ////TEST for better falling
         if(downVelocity > m_fallSpeed)
            downVelocity = m_fallSpeed;
      ////TEST END

      //downVelocity = m_stepHeight;
   }


   //onGround()‚ªãŽè‚­‚¢‚©‚È‚¢‚Ì‚ÅA‰º•ûŒü‚É‘½‚ß‚ÉˆÚ“®‚³‚¹,
   //‚Ô‚Â‚©‚ç‚È‚©‚Á‚½ê‡‚Ì‚ÝA³‚µ‚¢’l‚ð“ü‚ê‚é‚·‚éB
   //‚Ô‚Â‚©‚éê‡‚ÍA‘½‚ß‚ÉˆÚ“®‚³‚¹‚Ä‚é‚¾‚¯‚È‚Ì‚ÅA‚Ô‚Â‚©‚Á‚½ˆÊ’u‚ª•Ï‚í‚é‚í‚¯‚Å‚Í‚È‚¢‚¾‚ë‚¤‚Æ‚¢‚¤l‚¦•û
   btVector3 step_drop = getUpAxisDirections()[m_upAxis] * ( m_currentStepOffset + downVelocity + 0.05f );
   btVector3 target = m_targetPosition;
   target -= step_drop;

   step_drop = getUpAxisDirections()[m_upAxis] * ( m_currentStepOffset + downVelocity );
   m_targetPosition -= step_drop;

   start.setIdentity ();
   end.setIdentity ();

   start.setOrigin (m_currentPosition);
   end.setOrigin (target);
   //end.setOrigin (m_targetPosition);

   btKinematicClosestNotMeConvexResultCallback callback (m_ghostObject, getUpAxisDirections()[m_upAxis], m_maxSlopeCosine);
   callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
   callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;
   
   if (m_useGhostObjectSweepTest)
   {
      m_ghostObject->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
   } else
   {
      collisionWorld->convexSweepTest (m_convexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
   }

   if (callback.hasHit())
   {
      // we dropped a fraction of the height -> hit floor
      m_currentPosition.setInterpolate3 (m_currentPosition, target, callback.m_closestHitFraction);
      //m_currentPosition.setInterpolate3 (m_currentPosition, m_targetPosition, callback.m_closestHitFraction);
      m_verticalVelocity = 0.0;
      m_verticalOffset = 0.0;
      m_wasJumping = false;
   } else {
	   // we dropped the full height
	   m_currentPosition = m_targetPosition;

	   //TRACE1( "m_verticalVelocity : %f\n", m_verticalVelocity );
	   //TRACE1( "m_verticalOffset : %f\n", m_verticalOffset );
	   //TRACE1( "m_currentStepOffset + downVelocity : %f\n", m_currentStepOffset + downVelocity  );
   }
   //TRACE1( "m_verticalVelocity : %f\n", m_verticalVelocity );
   //TRACE1( "m_verticalOffset : %f\n", m_verticalOffset );
}
//---------------------------------------------------------------------------------------
// set walkDirection.
// in this method, walkDirection means move value per 1/60 sec. 
void CharacterController2::setWalkDirection(const btVector3& walkDirection)
{
   m_useWalkDirection = true;
   m_walkDirection = walkDirection;
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void CharacterController2::reset ()
{
}
//---------------------------------------------------------------------------------------
void CharacterController2::warp (const btVector3& origin)
{
   btTransform xform;
   xform.setIdentity();
   xform.setOrigin (origin);
   m_ghostObject->setWorldTransform (xform);
}
//---------------------------------------------------------------------------------------
void CharacterController2::preStep (  btCollisionWorld* collisionWorld)
{
   
   int numPenetrationLoops = 0;
   m_touchingContact = false;
   while (recoverFromPenetration (collisionWorld))
   {
      numPenetrationLoops++;
      m_touchingContact = true;
      if (numPenetrationLoops > 4)
      {
         //printf("character could not recover from penetration = %d\n", numPenetrationLoops);
         break;
      }
   }

   m_currentPosition = m_ghostObject->getWorldTransform().getOrigin();
   m_targetPosition = m_currentPosition;
//   printf("m_targetPosition=%f,%f,%f\n",m_targetPosition[0],m_targetPosition[1],m_targetPosition[2]);
}
//---------------------------------------------------------------------------------------
//#include <stdio.h>

void CharacterController2::playerStep (  btCollisionWorld* collisionWorld, btScalar dt)
{
	//using namespace boost;
	//boost::timer t; // ƒ^ƒCƒ}[‚ÌŠJŽn

	//PrintBtVector3::toDebugScreen ( m_walkDirection, 0, 2 );

//   printf("playerStep(): ");
//   printf("  dt = %f", dt);
	m_wasOnGround = onGround();	
   // quick check...
	if (!m_useWalkDirection  && m_wasOnGround && m_accelDatasUsedList.empty() && m_walkDirection.length2()==0.0 ) {
//      printf("\n");
		return;      // no motion
	}

   // Update fall velocity.
   m_verticalVelocity -= m_gravity * dt;
   if(m_verticalVelocity > 0.0 && m_verticalVelocity > m_jumpSpeed)
   {
      m_verticalVelocity = m_jumpSpeed;
   }
   if(m_verticalVelocity < 0.0 && btFabs(m_verticalVelocity) > m_fallSpeed)
   {
      m_verticalVelocity = -m_fallSpeed;
   }
   m_verticalOffset = m_verticalVelocity * dt;


   btTransform xform;
   xform = m_ghostObject->getWorldTransform ();

//   printf("walkDirection(%f,%f,%f)\n",walkDirection[0],walkDirection[1],walkDirection[2]);
//   printf("walkSpeed=%f\n",walkSpeed);

   stepUp (collisionWorld);
   //TRACE1( "CharacterController2::stepup() : %f\n: ", t.elapsed() );
	//t.restart();

   if (m_useWalkDirection) {
	   stepForwardAndStrafe (collisionWorld, m_walkDirection);
	   //TRACE1( "CharacterController2::stepForwardAndStrafe() : %f\n: ", t.elapsed() );
		//t.restart();
   } else {
	   assert( dt==1.f/60.f && "look getVelocity(). the method is wrong too. because i think that dt is always same(1.f/60.f). " );
	   // how far will we move while we are moving?
	   updateWalkeDirection(dt);
	   btVector3 move = m_walkDirection * dt;
	   //printf("  dtMoving: %f", dtMoving);
	   
	   // okay, step
	   stepForwardAndStrafe(collisionWorld, move);
	   	//TRACE1( "CharacterController2::stepForwardAndStrafe() : %f\n: ", t.elapsed() );
		//t.restart();
   }
   stepDown (collisionWorld, dt);
   //assert( dt==0.016666668f );
   // printf("\n");
   	  
   //TRACE1( "CharacterController2::stepDown() : %f\n: ", t.elapsed() );
   //t.restart();


   xform.setOrigin (m_currentPosition);
   m_ghostObject->setWorldTransform (xform);
  
   if (m_useWalkDirection) {
		static_cast<GameObject::CharacterControllerGhostObject*>( m_ghostObject->getUserPointer() )->checkArrivalInNexTime();
   } else {
		static_cast<GameObject::CharacterControllerGhostObject*>( m_ghostObject->getUserPointer() )->checkArrivalInNexTime( dt );
   }
}
//---------------------------------------------------------------------------------------
void CharacterController2::jump ()
{
   if (!canJump())
      return;

   m_verticalVelocity = m_jumpSpeed;
   m_wasJumping = true;

#if 0
   currently no jumping.
   btTransform xform;
   m_rigidBody->getMotionState()->getWorldTransform (xform);
   btVector3 up = xform.getBasis()[1];
   up.normalize ();
   btScalar magnitude = (btScalar(1.0)/m_rigidBody->getInvMass()) * btScalar(8.0);
   m_rigidBody->applyCentralImpulse (up * magnitude);
#endif
}

void CharacterController2::forceJump()
{
   m_verticalVelocity = m_jumpSpeed;
   m_wasJumping = true;
}
//---------------------------------------------------------------------------------------
btVector3* CharacterController2::getUpAxisDirections()
{
   static btVector3 sUpAxisDirection[3] = { btVector3(1.0f, 0.0f, 0.0f), btVector3(0.0f, 1.0f, 0.0f), btVector3(0.0f, 0.0f, 1.0f) };
   
   return sUpAxisDirection;
}
//---------------------------------------------------------------------------------------
void CharacterController2::debugDraw(btIDebugDraw* debugDrawer)
{
   debugDrawer;
}

bool CharacterController2::onGround () const {
	return m_verticalVelocity == 0.0 && m_verticalOffset == 0.0;
}


//---------------------------------------------------------------------------------------
}//end namespace kztr;
// kztr_charactercontroller2.cpp - End of file