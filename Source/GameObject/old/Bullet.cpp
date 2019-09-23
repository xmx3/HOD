#include"Bullet.h"
#include"BulletPhysics/Manager.h"
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"helper/PrimitiveDrawer.h"
#include"Player.h"
#include"Enemy.h"
#include<GameLib/Math/Random.h>
#include"GameObjectData/WeaponStatus.h"
#include<GameLib/GameLib.h>
#include"helper/MyOutputDebugString.h"
#include"Accessory.h"
namespace GameObject{

RTTI_IMPL( Bullet, IRigidBody );
	
BulletSharedPtr Bullet::create( const btTransform & startTrans, const btVector3 &velocity, const float &radius, IColliderWeakPtr parent ){
	BulletSharedPtr sp = std::make_shared<Bullet>( startTrans, velocity, radius, parent ); 
	return sp;
}

BulletSharedPtr Bullet::createForEnemy( const btTransform & startTrans, const btVector3 &velocity, const float &radius, IColliderWeakPtr parent ){
	BulletSharedPtr sp = std::make_shared<Bullet>( startTrans, velocity, radius, parent ); 
	//sp->mFilterMask = btBroadphaseProxy::AllFilter & ~BulletPhysics::Manager::EnemyFilter;
	sp->mFilterMask = btBroadphaseProxy::AllFilter;
	return sp;
}

BulletSharedPtr Bullet::createForPlayer( const btTransform & startTrans, const btVector3 &velocity, const float &radius, IColliderWeakPtr parent ){
	BulletSharedPtr sp = std::make_shared<Bullet>( startTrans, velocity, radius, parent ); 
	sp->mFilterMask = btBroadphaseProxy::AllFilter & ~BulletPhysics::Manager::PlayerFilter;
	return sp;
}

Bullet::Bullet()
	:mShape(NULL),
	mActivationTime(0.f)	
{
	mFilterGroup = BulletPhysics::Manager::BulletFilter;
	mFilterMask = btBroadphaseProxy::AllFilter & ~BulletPhysics::Manager::MMDObjectFilter;
}


Bullet::Bullet( const btTransform & startTrans, const btVector3 &velocity, const float &radius, IColliderWeakPtr parent )
	:mShape(NULL),
	mParent(parent),
	mActivationTime(0.f)	
{
	mFilterGroup = BulletPhysics::Manager::BulletFilter;
	mFilterMask = btBroadphaseProxy::AllFilter & ~BulletPhysics::Manager::MMDObjectFilter;

	mMass = radius*radius*3.141715f;
	mShape = new btSphereShape( radius );

	if( IColliderSharedPtr sptr = mParent.lock() ){
		assert(sptr->getBtCollisionObject());
		ignoreCollision( sptr->getBtCollisionObject() );
	}
	
	// Šµ«ƒeƒ“ƒ\ƒ‹‚ÌŒvŽZ
	btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
	mShape->calculateLocalInertia( mMass, btv3LocalInertia );

	// MotionState‚ðì¬‚·‚éB„‘Ì‚ÌŽp¨§Œä‚ð‚·‚é‚à‚Ì	
	btMotionState *pMotionState = new btDefaultMotionState( startTrans );
	
	// „‘Ì‚ðì¬‚·‚é
	btRigidBody::btRigidBodyConstructionInfo rbInfo( mMass, pMotionState, mShape, btv3LocalInertia );
	rbInfo.m_friction = 0.5f;//’Êí0.5
	
	mRigidBody.reset( new btRigidBody( rbInfo ) );
	mRigidBody->setLinearVelocity( velocity );
	mRigidBody->setUserPointer(this);
}

Bullet::~Bullet(){
	removeFromWorld();
	if(mRigidBody){
		btMotionState* pM = mRigidBody->getMotionState();
		SAFE_DELETE( pM );
		mRigidBody.reset();
	}
	SAFE_DELETE(mShape);
}

void Bullet::addToWorld(){
	defalut_addToWorld();
}

void Bullet::removeFromWorld(){
	defalut_removeFromWorld();
}

void Bullet::draw() const {
	if(mIsInWorld){
		PrimitiveDrawer::draw( mRigidBody.get(), 0xffffffff, false );
	}
}

void Bullet::update( float elapsedTime ) {
	if( mIsInWorld ){
		if( mActivationTime>0 ) {
			mActivationTime -= elapsedTime;
		} else {
			removeFromWorld();
		}
	}
}

IColliderWeakPtr Bullet::getParent() {
	return mParent;
}


void Bullet::setWorldTransform(const btTransform &startTrans ){
	mRigidBody->setWorldTransform( startTrans );
}
void Bullet::setLinerVelocity( const btVector3 &linerVelocity ){
	mRigidBody->setLinearVelocity( linerVelocity );
}

void Bullet::lunch(  const btTransform & startTrans, const btVector3 &velocity, float activeTime ){
	mRigidBody->setWorldTransform( startTrans );
	mRigidBody->setLinearVelocity( velocity );
	mActivationTime = activeTime;
	if(ICollider *ptr = mParent.lock().get() ){
		mWeaponStatus->me = ptr->getStatus();
		assert(ptr->getBtCollisionObject());
		ignoreCollision( ptr->getBtCollisionObject() );
		addToWorld();
	}else{
		assert(false);
	}

}

void Bullet::onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ){
	ICollider *colObj = static_cast<ICollider*>(obj->getUserPointer());
	IRigidBody::onCollisionEnter( manifold, me, obj );

	//’µ‚Ë•Ô‚µ//Ž©g‚Ì’e‚É
	if( colObj->getRTTI().isExactly( Rttis::Accessory() ) ){
		Accessory *ac=static_cast<Accessory*>(colObj);
		assert(ac);
		if( btCollisionObject *owner=ac->getOwner() ){
			clearNotCollideObjects();
			mWeaponStatus->me = static_cast<ICollider*>(owner->getUserPointer())->getStatus();
		}
	}
}
}
