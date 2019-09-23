#include "Manager.h"
#include"GameObject/IGameObject.h"

#include"helper/MyOutputDebugString.h"
#include<tchar.h>

#include <algorithm>

#include<BulletCollision/CollisionDispatch/btGhostObject.h>


namespace MMD {
namespace MMDBulletPhysics {

Manager::UptrManager Manager::pThis_;

Manager::Manager() :
	pBtCollisionConfig_(NULL),
	pBtCollisionDispatcher_(NULL),
	pBtOverlappingPairCache_(NULL),
	pBtSolver_(NULL),
	pGhostPairCallback_(NULL)
{};

Manager::~Manager() {
	assert( pBtWorld_->getNumConstraints()==0 &&
		"ワールドを破壊する前にconstraintを取りのぞき、メモリを開放すること。 \
		再利用するならメモリは開放しないでいい");
	assert( pBtWorld_->getNumCollisionObjects()==0 &&
		"ワールドを破壊する前にcollisionObjectを取りのぞき、メモリを開放すること。 \
		再利用するならメモリは開放しないでいい");
	using GameObject::IGameObject;
	//debug用開放忘れの可能性のあるオブジェクトを表示
	for( int i = pBtWorld_->getNumConstraints()-1 ; i>-1 ; --i ){
		btTypedConstraint	*pObj = pBtWorld_->getConstraint(i);
		IGameObject *gameobj = static_cast<IGameObject*>(pObj->getUserConstraintPtr());
	
		if(gameobj){
			TRACE1("not removed object: %s\n", gameobj->getRTTI().getClassName().c_str() );
		} else {
			TRACE1("not removed object: NULL\n", 0 );
		}
	}

	for( int i = pBtWorld_->getNumCollisionObjects()-1 ; i >= 0 ; --i )
	{
		btCollisionObject	*pObj = pBtWorld_->getCollisionObjectArray()[i];
		IGameObject *gameobj = static_cast<IGameObject*>(pObj->getUserPointer());
	
		if(gameobj){
			TRACE1("not removed object: %s\n", gameobj->getRTTI().getClassName().c_str() );
		} else {
			TRACE1("not removed object: NULL\n", 0 );
		}
	}

	
	SAFE_DELETE(pGhostPairCallback_);
	SAFE_DELETE( pBtCollisionConfig_ );
	SAFE_DELETE( pBtCollisionDispatcher_ );
	SAFE_DELETE( pBtOverlappingPairCache_ );
	SAFE_DELETE( pBtSolver_ );
	SAFE_DELETE( pBtWorld_ );
};

Manager* Manager::instance() {
	if( !pThis_ )
	{
		pThis_.reset( new Manager );
		pThis_->initialize();
	}
	return pThis_.get();
}
//========
// 初期化
//========
bool Manager::initialize( void )
{
	// コリジョンコンフィグを作成する
	pBtCollisionConfig_ = new btDefaultCollisionConfiguration();

	// コリジョンディスパッチャを作成する
	pBtCollisionDispatcher_ = new btCollisionDispatcher( pBtCollisionConfig_ );

	// コリジョンワールドの最大サイズを指定する
	btVector3 btv3WorldAabbMin( -1000.0f, -1000.0f, -1000.0f );
	btVector3 btv3WorldAabbMax(  1000.0f,  1000.0f,  1000.0f );
	unsigned short iMaxProxies = 1024;
	pBtOverlappingPairCache_ = new btAxisSweep3( btv3WorldAabbMin, btv3WorldAabbMax, iMaxProxies );
	
	// Its insert/add and remove of objects is generally faster than the sweep and prune broadphases btAxisSweep3 and bt32BitAxisSweep3
	//btDbvtBroadphase *pBtDbvtBrodphase_ = new btDbvtBroadphase();
	
	// の拘束計算ソルバを作成する
	pBtSolver_ = new btSequentialImpulseConstraintSolver();

	// ワールドの作成
	pBtWorld_ = new btDiscreteDynamicsWorld( pBtCollisionDispatcher_, pBtOverlappingPairCache_, pBtSolver_, pBtCollisionConfig_ );
	//pBtWorld_ = new btDiscreteDynamicsWorld( pBtCollisionDispatcher_, pBtDbvtBrodphase_, pBtSolver_, pBtCollisionConfig_ );

	pGhostPairCallback_ = new btGhostPairCallback();
	btAxisSweep3* sweepBP = dynamic_cast<btAxisSweep3*>(pBtWorld_->getBroadphase());
	assert( sweepBP && "" );
	sweepBP->getOverlappingPairCache()->setInternalGhostPairCallback(pGhostPairCallback_);


	// 重力設定
	//pBtWorld_->setGravity( btVector3( 0.0f, -9.8f * 2.0f, 0.0f ) );	// ネクタイなどがふわふわするのでなんとなく2倍しておく
	pBtWorld_->setGravity( btVector3( 0.0f, -9.8f, 0.0f ) );

	return true;
}


void Manager::addToWorld( btCollisionObject *pbtCo ){
	pBtWorld_->addCollisionObject(pbtCo);
}
void Manager::addToWorld( btCollisionObject *pbtCo, unsigned short unGroupId, unsigned short unGroupMask ){
	pBtWorld_->addCollisionObject( pbtCo, unGroupId, unGroupMask );
}
	

//======================
// 剛体をワールドに追加
//======================
void Manager::addToWorld( btRigidBody *pbtRB, unsigned short unGroupId, unsigned short unGroupMask )
{
	pBtWorld_->addRigidBody( pbtRB, unGroupId, unGroupMask );
}

void Manager::addToWorld( btRigidBody *pbtRB )
{
	pBtWorld_->addRigidBody( pbtRB );
}


//==================================
// コンストレイントをワールドに追加
//==================================
void Manager::addToWorld( btTypedConstraint *pctConstraint )
{
	pBtWorld_->addConstraint( pctConstraint );
}

//当たり判定をワールドから削除
void Manager::removeFromWorld( btCollisionObject *pbtCo ){
	pBtWorld_->removeCollisionObject( pbtCo );
}


//========================
// 剛体をワールドから削除
//========================
void Manager::removeFromWorld( btRigidBody *pbtRB )
{
	pBtWorld_->removeCollisionObject( pbtRB );
}

//====================================
// コンストレイントをワールドから削除
//====================================
void Manager::removeFromWorld( btTypedConstraint *pctConstraint )
{
	pBtWorld_->removeConstraint( pctConstraint );
}

//======
// 更新
//======
void Manager::update( float fElapsedTime )
{
//	pBtWorld_->stepSimulation( fMilliSec, 1 * (int)fSubStep );
	//pBtWorld_->stepSimulation( fMilliSec, 1, fElapsedFlame / 30.0f );
	pBtWorld_->stepSimulation( fElapsedTime, 15 );
}

//======
// 解放
//======
void Manager::release( void )
{
	pThis_.reset(NULL);
}

}//end namespace MMDBulletPhysics
}//end namespace MMD
