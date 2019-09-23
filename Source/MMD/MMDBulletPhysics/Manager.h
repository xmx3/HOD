#ifndef		__MMDBULLETPHYSICS_MANAGER_H__
#define		__MMDBULLETPHYSICS_MANAGER_H__

#include<btBulletDynamicsCommon.h>
#include"MMD/MMDMacro.h"

#include<set>
#include<list>
#include<memory>

class btGhostPairCallback;

namespace MMD{
//ルート上にこの名前空間があるので少し余分な名前に
namespace MMDBulletPhysics {

class Manager
{
public :
	//there were btBroadphaseProxy class.
	//this is because of help understandable.
	///optional filtering to cull potential collisions
	enum CollisionFilterGroups
	{
	        //DefaultFilter = 1,
	        //StaticFilter = 2,
	        //KinematicFilter = 4,
	        //DebrisFilter = 8,
			//SensorTrigger = 16,
			//CharacterFilter = 32,
			MMDObjectFilter = 64,
			PlayerFilter = 128,
			EnemyFilter = 256,
			BulletFilter = 512
	        //AllFilter = -1 //all bits sets: DefaultFilter | StaticFilter | KinematicFilter | DebrisFilter | SensorTrigger
	};
	static Manager* instance();
	void addToWorld( btCollisionObject *pbtCo );
	void addToWorld( btCollisionObject *pbtCo, unsigned short unGroupIdx, unsigned short unGroupMask );
	void addToWorld( btRigidBody *pbtRB, unsigned short unGroupIdx, unsigned short unGroupMask );
	void addToWorld( btRigidBody *pbtRB );
	void addToWorld( btTypedConstraint *pctConstraint );
	void removeFromWorld( btCollisionObject *pbtCo );
	void removeFromWorld( btRigidBody *pbtRB );
	void removeFromWorld( btTypedConstraint *pctConstraint );
	
	void update( float fElapsedTime );

	void release( void );

	btDiscreteDynamicsWorld* getWorldPtr(){
		return pBtWorld_;
	}

private:
	DISALLOW_COPY_AND_ASSIGN(Manager);
	Manager( void );
	~Manager( void );
	
	bool initialize( void );
	static btRigidBody* createRigidBody(const float &mass, const btTransform &trans, btCollisionShape* pShape );

private :
	struct Deleter
	{
		void operator()( Manager const* const p ) const
		{
			delete p;
		}
	};
	typedef std::unique_ptr<Manager, Deleter > UptrManager;
	static UptrManager pThis_;

	btDefaultCollisionConfiguration			*pBtCollisionConfig_;
	btCollisionDispatcher					*pBtCollisionDispatcher_;
	btAxisSweep3							*pBtOverlappingPairCache_;
	btSequentialImpulseConstraintSolver		*pBtSolver_;
	btDiscreteDynamicsWorld					*pBtWorld_;
	btGhostPairCallback						*pGhostPairCallback_;

};
}// end namespace MMDBulletPhysics
}// end namespace MMD
#endif
