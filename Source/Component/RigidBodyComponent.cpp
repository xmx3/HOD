#include "RigidBodyComponent.h"
#include<btBulletDynamicsCommon.h>

#include"BulletPhysics/Manager.h"


namespace Component{
RigidBodyComponentSharedPtr RigidBodyComponent::create(
	GameObject::BaseObject* owner,
	BtCollisionShapeSharedPtr shape,
	BtMotionStateSharedPtr motionState,
	BtRigidBodySharedPtr rigidbody)
{
	return std::make_shared<RigidBodyComponent>(
		owner,
		shape,
		motionState,
		rigidbody );
}

RigidBodyComponent::RigidBodyComponent(
	GameObject::BaseObject* owner,
	BtCollisionShapeSharedPtr shape,
	BtMotionStateSharedPtr motionState,
	BtRigidBodySharedPtr rigidbody )
	:mShape(shape),
	mRigidBody(rigidbody),
	mMotionState(motionState),
	mIsInWorld(false),
	mCanCollideCallback(nullptr),
	mOnEnterCallback(),
	mOnStayCallback(),
	mOnExitCallback()
{
	mOwner = owner;
	if (mRigidBody) {
		mRigidBody->setUserPointer(this);
	}
}

RigidBodyComponent::~RigidBodyComponent()
{
}


btCollisionObject * RigidBodyComponent::getBtCollisionObject()
{
	return mRigidBody.get();
}

const btCollisionObject * RigidBodyComponent::getConstBtCollisionObject() const
{
	return mRigidBody.get();
}

const btTransform & RigidBodyComponent::getWorldTransform() const
{
	return mRigidBody->getWorldTransform();
}

btTransform & RigidBodyComponent::getWorldTransform()
{
	return mRigidBody->getWorldTransform();
}


bool RigidBodyComponent::isInWorld()const {
	return mIsInWorld;
}

bool RigidBodyComponent::removeFromWorld() {
	if (mIsInWorld) {
		BulletPhysics::Manager::instance()->removeFromWorld(mRigidBody.get());
		mIsInWorld = false;
		return true;
	}
	return false;
}

bool RigidBodyComponent::addToWorld(unsigned short filterGroup, unsigned short filterMask) {
	if (!mIsInWorld) {
		BulletPhysics::Manager::instance()->addToWorld(
			mRigidBody.get(),
			filterGroup,
			filterMask);
		mIsInWorld = true;
		return true;
	}
	return false;
}

void RigidBodyComponent::setIsKinematic(bool isKinematic) {
	if (isKinematic) 
	{
		int f = mRigidBody->getCollisionFlags();
		mRigidBody->setCollisionFlags(f | btCollisionObject::CF_KINEMATIC_OBJECT);
		mRigidBody->setActivationState(DISABLE_DEACTIVATION);
	}
	else {
		int f = mRigidBody->getCollisionFlags();
		mRigidBody->setCollisionFlags(f & ~btCollisionObject::CF_KINEMATIC_OBJECT);
		mRigidBody->forceActivationState(ACTIVE_TAG);
	}
}

void RigidBodyComponent::onCollisionStay(btPersistentManifold * manifold, btCollisionObject * me, btCollisionObject * obj)
{
	mOnStayCallback.exec(manifold, me, obj);
}

void RigidBodyComponent::onCollisionEnter(btPersistentManifold * manifold, btCollisionObject * me, btCollisionObject * obj)
{
	mOnEnterCallback.exec(manifold, me, obj);
}

void RigidBodyComponent::onCollisionExit(btCollisionObject * me, btCollisionObject * obj)
{
	mOnExitCallback.exec(me, obj);
}

//void RigidBodyComponent::setOnCollisonEnterCallback(IOnCollisionEnterCallback * callback)
//{
//	mOnEnterCallback = callback;
//}
//
//void RigidBodyComponent::setOnCollisonStayCallback(IOnCollisionStayCallback * callback)
//{
//	mOnStayCallback = callback;
//}
//
//void RigidBodyComponent::setOnCollisonExitCallback(IOnCollisionExitCallback * callback)
//{
//	mOnExitCallback = callback;
//}


void RigidBodyComponent::setMotionState(const BtMotionStateSharedPtr motionstate) {
	mMotionState = motionstate;
	mRigidBody->setMotionState(mMotionState.get());
}


}