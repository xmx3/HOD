#pragma once
#include<btBulletDynamicsCommon.h>
#include"Manager.h"
#include<assert.h>
#include"helper/MyOutputDebugString.h"

namespace BulletPhysics {

static bool onGroundVerRayTest( const btCollisionObject *obj, short filterGroup, short filterMask ){
	const btTransform &xform = obj->getWorldTransform ();
	
	btVector3 from=xform.getOrigin(), to=xform.getOrigin();
	const btCollisionShape *col = obj->getCollisionShape();
	btVector3 center;
	float radius;
	col->getBoundingSphere( center, radius );
	to[1] -= radius;

	class ClosestNotMeRayResultCallback : public btCollisionWorld::ClosestRayResultCallback
	{
	public:
		ClosestNotMeRayResultCallback (const btCollisionObject* me)
			: btCollisionWorld::ClosestRayResultCallback(
				btVector3(0.0, 0.0, 0.0),
				btVector3(0.0, 0.0, 0.0) )
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
		const btCollisionObject* m_me;
	};
	ClosestNotMeRayResultCallback callback( obj );
	callback.m_collisionFilterGroup = filterGroup;
	callback.m_collisionFilterMask = filterMask;
	BulletPhysics::Manager::instance()->getWorldPtr()->rayTest( from, to, callback );

	if( callback.hasHit() ){
		//btVector3 groundPos;
		//groundPos.setInterpolate3( from, to, callback.m_closestHitFraction );
		return true;
	} else {
		return false;
	}

}
//これいまいち
// 接地判定にcontactTestを使っているのだが、
// どうしてもギリギリの所で接地してないと判定するようで(たぶん、物理エンジンにとってはそのほうが都合がよいのだろう)
//このcontactTestを使う方法はだめ

static bool onGroundVerContactTest( btCollisionObject *obj, short filterGroup, short filterMask )
{
	struct   MyContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
		bool m_connected;
		MyContactResultCallback() 
			:m_connected(false)
		{
		}
		virtual   btScalar   addSingleResult(btManifoldPoint& cp,   const btCollisionObjectWrapper* colObj0,int partId0,int index0,const btCollisionObjectWrapper* colObj1,int partId1,int index1)
		{
			m_connected = true;

			return 1.f;
		}
	};
	
	MyContactResultCallback cb;
	cb.m_collisionFilterGroup = filterGroup;
	cb.m_collisionFilterMask = filterMask;	
	
	//コンタクトテストよりレイを飛ばしたほうがいい
	BulletPhysics::Manager::instance()->getWorldPtr()->contactTest( obj, cb );

	return cb.m_connected;
}


}