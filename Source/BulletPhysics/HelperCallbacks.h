#pragma once

#include<btBulletDynamicsCommon.h>



namespace BulletPhysics{

//ぶつかっているかどうかだけを確かめる
//exsample
//	MyContactResultCallback cb; 
//	BulletPhysics::Manager::instance()->getWorldPtr()->contactPairTest( &col, obj, cb );
struct SimpleContactResultCallback : public btCollisionWorld::ContactResultCallback
{
	bool mConnected;
	SimpleContactResultCallback() :mConnected(false)
	{}
	virtual ~SimpleContactResultCallback()
	{}

	virtual   btScalar   addSingleResult(btManifoldPoint& cp,   const btCollisionObjectWrapper* colObj0,int partId0,int index0,const btCollisionObjectWrapper* colObj1,int partId1,int index1)
	{
		if (cp.getDistance()<=0)
			mConnected = true;
		return 1.f;
	}
};

//指定オブジェクトを除いた一番近いオブジェクトを求める
//exsample
//	ClosestRayResultCallbackToIgnoreObject callback(mRigidBody.get());
//	callback.m_collisionFilterGroup = mFilterGroup;
//	callback.m_collisionFilterMask = mFilterMask;
//	BulletPhysics::Manager::instance()->getWorldPtr()->rayTest( from, to, callback );
class ClosestRayResultCallbackToIgnoreObject : public btCollisionWorld::ClosestRayResultCallback
{
public:
	ClosestRayResultCallbackToIgnoreObject (btCollisionObject* ignoredObj)
		: btCollisionWorld::ClosestRayResultCallback(
			btVector3(0.0, 0.0, 0.0),
			btVector3(0.0, 0.0, 0.0) ),
		mIgnoredObje(ignoredObj)
	{}
	virtual ~ClosestRayResultCallbackToIgnoreObject(){}

	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace)
	{
		if (rayResult.m_collisionObject == mIgnoredObje)
		{
			return 1.0;
		}

		return ClosestRayResultCallback::addSingleResult (rayResult, normalInWorldSpace);
	}
protected:
	const btCollisionObject * const mIgnoredObje;
};

//指定オブジェクトを除いた一番近いオブジェクトを求める
//exsample
//	btSphereShape sphere(radius);
//	ClosestConvexResultCallbackToIgnoreObject cb( ignoreobj, start,  end );
//	cb.m_collisionFilterMask = btBroadphaseProxy::AllFilter & ~BulletPhysics::Manager::MMDObjectFilter;
//		
//	BulletPhysics::Manager::instance()->getWorldPtr()->convexSweepTest( &sphere, start, end, cb );
//
struct ClosestConvexResultCallbackToIgnoreObject : public btCollisionWorld::ClosestConvexResultCallback
{
	btCollisionObject const *m_ignoredObj;

	ClosestConvexResultCallbackToIgnoreObject(
		const btCollisionObject *ignoredObj,
		const btVector3& convexFromWorld,
		const btVector3& convexToWorld )
		:ClosestConvexResultCallback( convexFromWorld, convexToWorld ),
		m_ignoredObj(ignoredObj)
	{}
	virtual ~ClosestConvexResultCallbackToIgnoreObject(){}

	virtual btScalar addSingleResult( btCollisionWorld::LocalConvexResult& convexResult,bool normalInWorldSpace)
	{
		//指定オブジェクトがぶつかってない場合
		if( convexResult.m_hitCollisionObject == m_ignoredObj ){
			return 1.0;
		}
		return ClosestConvexResultCallback::addSingleResult( convexResult, normalInWorldSpace );
	}
};


//contactTestObjから最も近いcollisionObjectを保存
//exsample
//	btSphereShape sphere(radius);
//	btCollisionObject col;
//	col.setCollisionShape( &sphere );
//	col.setWorldTransform( btTransform( btMatrix3x3::getIdentity(), spherePos ) );
//	
//	BulletPhysics::ClosestObjectContactResultCallbackFromObjectA cb( &col ); 
//	BulletPhysics::Manager::instance()->getWorldPtr()->contactTest( &col, cb );
//
struct ClosestObjectContactResultCallbackFromObjectA : public btCollisionWorld::ContactResultCallback
{
	const btCollisionObject *mContactTestObj;
	const btCollisionObject *mClosestObj;
	float mMinLength2;
	ClosestObjectContactResultCallbackFromObjectA( const btCollisionObject *contactTestObj )
		:mClosestObj(NULL),
		mMinLength2( (std::numeric_limits<float>::max)() ),
		mContactTestObj( contactTestObj )
	{}

	virtual ~ClosestObjectContactResultCallbackFromObjectA(){}

	virtual   btScalar   addSingleResult(btManifoldPoint& cp,   const btCollisionObjectWrapper* colObj0,int partId0,int index0,const btCollisionObjectWrapper* colObj1,int partId1,int index1)
	{
		if (cp.getDistance()<=0){
			assert( (mContactTestObj == colObj0->getCollisionObject()) | (mContactTestObj == colObj1->getCollisionObject() ) );
			
			const btCollisionObject *anotherContactTestObj=NULL;
			if( mContactTestObj == colObj0->getCollisionObject() ){
				anotherContactTestObj = colObj1->getCollisionObject();
			} else if( mContactTestObj == colObj1->getCollisionObject()){
				anotherContactTestObj = colObj0->getCollisionObject();
			} else {
				//assert();
				return 1.f;
			}

			float length2 = (mContactTestObj->getWorldTransform().getOrigin() - anotherContactTestObj->getWorldTransform().getOrigin() ).length2();

			if( length2 < mMinLength2 ){
				mMinLength2 = length2;
				mClosestObj = anotherContactTestObj;
			}
		}
		return 1.f;
	}
};



//指定オブジェクトがぶつかったか?を調べる
//かつ一番近いオブジェクトも調べる
//exsample	 
//	BulletPhysics::ClosestConvexResultCallbackAndCheckToColllideWithObjA cb( contactTestObject, start,  end );
//	cb.m_collisionFilterMask = btBroadphaseProxy::AllFilter & ~BulletPhysics::Manager::MMDObjectFilter;
//		
//	BulletPhysics::Manager::instance()->getWorldPtr()->convexSweepTest( &sphere, bttr, bttr1, cb );
//
//
struct ClosestConvexResultCallbackAndCheckToColllideWithObjA : public btCollisionWorld::ClosestConvexResultCallback
{
	bool m_hasCollidedWithObjA;
	btCollisionObject const *m_objA;

	ClosestConvexResultCallbackAndCheckToColllideWithObjA(
		const btCollisionObject *objA,
		const btVector3& convexFromWorld,
		const btVector3& convexToWorld )
		:ClosestConvexResultCallback( convexFromWorld, convexToWorld ),
		m_objA(objA),
		m_hasCollidedWithObjA(false)
	{}
	virtual ~ClosestConvexResultCallbackAndCheckToColllideWithObjA(){}

	virtual btScalar addSingleResult( btCollisionWorld::LocalConvexResult& convexResult,bool normalInWorldSpace)
	{
		//指定オブジェクトがぶつかってない場合
		if(!m_hasCollidedWithObjA){
			m_hasCollidedWithObjA = convexResult.m_hitCollisionObject == m_objA;
		}
		return ClosestConvexResultCallback::addSingleResult( convexResult, normalInWorldSpace );
	}
};




}