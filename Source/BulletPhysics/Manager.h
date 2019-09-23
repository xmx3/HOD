#ifndef		__BULLETPHYSICS_MANAGER_H__
#define		__BULLETPHYSICS_MANAGER_H__

#include<btBulletDynamicsCommon.h>
#include"MMD/MMDMacro.h"

#include"GameLib/Graphics/VertexBuffer.h"
#include"GameLib/Graphics/IndexBuffer.h"

//#include "DxBulletDebugDrawer.h"
#include"DebugDrawer/SegaBulletDebugDrawer.h"
#include<set>
#include<list>
#include<memory>
#include<vector>

class btGhostPairCallback;
class btBroadphaseInterface;

class EventManager;

namespace BulletPhysics {
	namespace FilterCallback {
		class FilterCallbackUsingCollisionComponent;
	}
class CDxBulletDebugDrawer;
class CDxBulletDebugDrawerEx;
class CSegaBulletDebugDrawer;


enum WorldIndex{
	GameWorldIndex=0,
	CutSceneWorldIndex=1
};

//there were btBroadphaseProxy class.
//maybe Kinematic, Debris, DebrisFilter didn't use.
//i think that it is possible to delete these.
//so when need to delete, i will delete.
///optional filtering to cull potential collisions
enum CollisionFilterGroups
{
	DefaultFilter = 1,
	StaticFilter = 2,
	KinematicFilter = 4,
	DebrisFilter = 8,
	SensorTrigger = 16,
	CharacterFilter = 32,
	MMDObjectFilter = 64,
	PlayerFilter = 128,
	EnemyFilter = 256,
	BulletFilter = 512,
	AllFilter = -1, //all bits sets: DefaultFilter | StaticFilter | KinematicFilter | DebrisFilter | SensorTrigger
	AllFilterExceptMMDObject = AllFilter  & ~MMDObjectFilter,
	DynamicFilter = AllFilterExceptMMDObject & StaticFilter
};


class Manager
{
public :
	static Manager* instance( int index = GameWorldIndex );
	//インデックス指定しなくて大丈夫な実装にした
	//そのため静的メンバ関数にしなかった
	void release();
	
	void addToWorld( btCollisionObject *pbtCo );
	void addToWorld( btCollisionObject *pbtCo, unsigned short unGroupIdx, unsigned short unGroupMask );
	void addToWorld( btRigidBody *pbtRB, unsigned short unGroupIdx, unsigned short unGroupMask );
	void addToWorld( btRigidBody *pbtRB );
	void addToWorld( btTypedConstraint *pctConstraint );
	void removeFromWorld( btCollisionObject *pbtCo );
	void removeFromWorld( btRigidBody *pbtRB );
	void removeFromWorld( btTypedConstraint *pctConstraint );
	
	//void addHeightfieldTerrainShape();

	void update( float fElapsedTime );
	//debug用。遅い使うのやめたほうがいい
	void drawWorld();
	//debug用。遅い。使うのやめたほうがいい
	static void drawObject( const btCollisionObject *pObj, unsigned int color = 0xff000000 );
	//debug用。遅い。使うのやめたほうがいい
	void drawConstraint(btTypedConstraint* pConstraint);
	void clearForces();

	void abortEventAll();

	


	btDiscreteDynamicsWorld* getWorldPtr(){
		return pBtWorld_;
	}

	btIDebugDraw* getDebugDrawerPtr(){
		return pDebugDrawer_;
	}

	void checkAllContactPoints();

	int getNumberCollisionObjects()const;

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
	static std::vector<UptrManager> pThese_;

	btDefaultCollisionConfiguration			*pBtCollisionConfig_;
	btCollisionDispatcher					*pBtCollisionDispatcher_;
	btBroadphaseInterface					*pBtBroadPhase_;
	btSequentialImpulseConstraintSolver		*pBtSolver_;
	btDiscreteDynamicsWorld					*pBtWorld_;
	btGhostPairCallback						*pGhostPairCallback_;

	FilterCallback::FilterCallbackUsingCollisionComponent 	*pFilterCallback_;

	CSegaBulletDebugDrawer *pDebugDrawer_;//くそ遅い
	//CDxBulletDebugDrawer *pDebugDrawer_;//実装がシンプル
	//CDxBulletDebugDrawerEx *pDebugDrawer_;//安定しない

	typedef std::pair< btCollisionObject*, btCollisionObject* > CollisionPair;
	typedef std::set< CollisionPair > CollisionPairs;
	CollisionPairs							previousCollisionPairs_;

	EventManager							*eventManager_;
};
}
#endif
