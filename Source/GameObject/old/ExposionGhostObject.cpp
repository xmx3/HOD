#include"ExplosionGhostObject.h"
#include<btBulletCollisionCommon.h>
#include<BulletCollision/CollisionDispatch/btGhostObject.h>
#include"BulletPhysics/Manager.h"
#include<GameLib/GameLib.h>
#include"helper/MyOutputDebugString.h"
#include<tchar.h>


ExplosionGhostObject::ExplosionGhostObject()
	:mGhost(NULL),
	mOwner(NULL),
	mScale(0.f),
	mPower(1.f),
	mIsEnable(true)
{
	static const float radius = 1.f; 
	mGhost = new btPairCachingGhostObject;
	mGhost->setCollisionFlags( mGhost->CF_NO_CONTACT_RESPONSE );
	mShape = new btSphereShape( radius );
	mGhost->setCollisionShape( mShape );
	BulletPhysics::Manager::instance()->addToWorld( mGhost, btBroadphaseProxy::DefaultFilter, btBroadphaseProxy::CharacterFilter | btBroadphaseProxy::DefaultFilter );
}

ExplosionGhostObject::~ExplosionGhostObject(){
	BulletPhysics::Manager::instance()->removeFromWorld( mGhost );	
	SAFE_DELETE(mGhost);
	SAFE_DELETE(mShape);
}

void ExplosionGhostObject::update( float elapsedTime ) {
	
	if( !isEnable() )
	{
		return;
	}
	
	mShape->setLocalScaling( btVector3( mScale, mScale, mScale ) );
	mScale += 0.3f;

	//   apply a force on all objects
	btManifoldArray   manifoldArray;
	btBroadphasePairArray& pairArray = mGhost->getOverlappingPairCache()->getOverlappingPairArray();
    int numPairs = pairArray.size();

    for (int i=0;i<numPairs;i++)
    {
        manifoldArray.clear();

        const btBroadphasePair& pair = pairArray[i];
         

        //unless we manually perform collision detection on this pair, the contacts are in the dynamics world paircache:
		btBroadphasePair* collisionPair = BulletPhysics::Manager::instance()->getWorldPtr()->getPairCache()->findPair(pair.m_pProxy0,pair.m_pProxy1);
		if (!collisionPair){ continue; }

        if (collisionPair->m_algorithm){
			collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);
		}
        for (int j=0;j<manifoldArray.size();j++)
        {
			btPersistentManifold* manifold = manifoldArray[j];
			for (int p=0;p<manifold->getNumContacts();p++)
			{
				const btManifoldPoint&pt = manifold->getContactPoint(p);
				const float &distance = pt.getDistance();
				if (distance<0.f)
				{
					btVector3 contactPos;
					btVector3 normal;
					btCollisionObject *other;//*me;
					if(manifold->getBody0() == mGhost){
						other=static_cast<btCollisionObject*>( manifold->getBody1() );
						contactPos = pt.getPositionWorldOnB();
						normal = -pt.m_normalWorldOnB;
					} else {
						other=static_cast<btCollisionObject*>( manifold->getBody0() );
						contactPos = pt.getPositionWorldOnA();
						normal = pt.m_normalWorldOnB;
					}
						
					if( other->getInternalType() ==  btCollisionObject::CO_GHOST_OBJECT ){
						//btGhostObject *go;
						//GameEntity* p=static_cast<GameEntity*>(other->getUserPointer());
						//p->HitDamage(this);
						TRACE1( "distance: %f\n", distance );
					} else if( other->getInternalType() ==  btCollisionObject::CO_RIGID_BODY ){
						btRigidBody* b = btRigidBody::upcast( other );
						assert(b);
						if(b){
							b->applyImpulse( normal*elapsedTime*distance*distance*mPower, contactPos );
						}
					}
				}
			}
        }
    }


	//for (int i=0, num=mGhost->getNumOverlappingObjects(); i<num; ++i )
 //  {
	//   btCollisionObject* c = mGhost->getOverlappingObject(i);
	//   if ( mOwner==NULL )
	//   {
 //          //Apply linear impulse on rigid bodies
	//	   btRigidBody* b = btRigidBody::upcast( c );
	//	   if(b){
	//		   b->applyImpulse();
	//	   }
	//   }
	//   else if( c->getUserPointer() == mOwner )
	//   {
	//	   //do nothing, or
	//	   //do somtthing when hitted myself.
	//	   TRACE( _T("Owner hitted Explosion\n") );

	//   }
	//   else
	//   {
 //          //Apply linear impulse on rigid bodies
	//	   TRACE( _T("Other hitted Explosion\n") );
	//   }
	//}
}

void ExplosionGhostObject::setPos( const btVector3 &p ){
	mGhost->getWorldTransform().setOrigin( p );
}

void ExplosionGhostObject::draw() const
{
	if( !isEnable() )
	{
		return;
	}
	BulletPhysics::Manager::drawObject( mGhost );
}

void ExplosionGhostObject::add(){
	BulletPhysics::Manager::instance()->addToWorld( mGhost, btBroadphaseProxy::DefaultFilter, btBroadphaseProxy::CharacterFilter | btBroadphaseProxy::DefaultFilter );
}

void ExplosionGhostObject::remove(){
	BulletPhysics::Manager::instance()->removeFromWorld( mGhost );
}