#include "BulletPhysics/Manager.h"
#include "DebugDrawer/DxBulletDebugDrawer.h"
#include "DebugDrawer/DxBulletDebugDrawerEx.h"
#include "DebugDrawer/SegaBulletDebugDrawer.h"
#include "MMD/MMDMacro.h"

#include <GameLib/Graphics/Vertex.h>

#include <Windows.h>

#include"helper/MyOutputDebugString.h"
#include<tchar.h>

#include<BulletCollision/CollisionDispatch/btGhostObject.h>
#include"DebugDrawer/BtCollisionObjectDrawer.h"
#include<BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>

#include<algorithm>
#include<assert.h>
#include<vector>

#include"FilterCallback/FilterCallbackUsingCollisionComponent.h"

#include"Event/MyEvent.h"
#include"Event/Physics/PhysicsEventListener.h"
#include"Event/Physics/PhysicsEventData.h"

namespace BulletPhysics {

std::vector<Manager::UptrManager> Manager::pThese_;

Manager::Manager() :
	pBtCollisionConfig_(NULL),
	pBtCollisionDispatcher_(NULL),
	pBtBroadPhase_(NULL),
	pBtSolver_(NULL),
	pDebugDrawer_(NULL),
	pFilterCallback_(NULL),
	pGhostPairCallback_(NULL),
	eventManager_(NULL)
{};

Manager::~Manager() {
	assert( pBtWorld_->getNumConstraints()==0 &&
		"ワールドを破壊する前にconstraintを取りのぞき、メモリを開放すること。 \
		再利用するならメモリは開放しないでいい");
	assert( pBtWorld_->getNumCollisionObjects()==0 &&
		"ワールドを破壊する前にcollisionObjectを取りのぞき、メモリを開放すること。 \
		再利用するならメモリは開放しないでいい");
	//debug用開放忘れの可能性のあるオブジェクトを表示
	for( int i = pBtWorld_->getNumConstraints()-1 ; i>-1 ; --i ){
		btTypedConstraint	*pObj = pBtWorld_->getConstraint(i);
		Component::RigidBodyComponent *pCol = static_cast<Component::RigidBodyComponent*>(pObj->getUserConstraintPtr());
	
		if(pCol){
			TRACE0("not removed object: RigidBodyComponent\n" );
		} else {
			TRACE1("not removed object: NULL\n", 0 );
		}
	}

	for( int i = pBtWorld_->getNumCollisionObjects()-1 ; i >= 0 ; --i )
	{
		btCollisionObject	*pObj = pBtWorld_->getCollisionObjectArray()[i];
		Component::RigidBodyComponent *pCol = static_cast<Component::RigidBodyComponent*>(pObj->getUserPointer());
	
		if(pCol){
			TRACE0("not removed object: RigidBodyComponent\n");
		} else {
			TRACE1("not removed object: NULL\n", 0 );
		}
	}

	SAFE_DELETE( eventManager_ );
	SAFE_DELETE( pDebugDrawer_ );
	SAFE_DELETE( pBtWorld_ );
	SAFE_DELETE( pGhostPairCallback_ );
	SAFE_DELETE( pFilterCallback_ );
	SAFE_DELETE( pBtSolver_ );
	SAFE_DELETE( pBtBroadPhase_ );
	SAFE_DELETE( pBtCollisionDispatcher_ );
	SAFE_DELETE( pBtCollisionConfig_ );
};

Manager* Manager::instance( int index ) {
	assert(index == 0);//もう使う気はないので一応assert()
	//MMDのために世界分けようかとも思ったけどgroupの工夫で何とかしたし
	//CutScenenで分けようかと思ったけどもアニメーションの状態を維持しておくのに結構な改造がいるとわかったので

	assert( index <= 1 );

	if( ! (static_cast<unsigned int>(index) < pThese_.size()) ){
		pThese_.resize( index+1 );
	}

	if( !pThese_[index] )
	{
		pThese_.emplace( pThese_.begin()+index, new Manager );
		pThese_[index]->initialize();
	}
	return pThese_[index].get();
}

// 解放
void Manager::release()
{
	for( int i=0, size=pThese_.size(); i<size; ++i ){
		if(this==pThese_[i].get()){
			pThese_[i].reset();
			//やっていることは delete this;に近い
			return;
		}
	}
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
	//btVector3 btv3WorldAabbMin( -1000.0f, -1000.0f, -1000.0f );
	//btVector3 btv3WorldAabbMax(  1000.0f,  1000.0f,  1000.0f );
	//unsigned short iMaxProxies = 1024;
	//pBtBroadPhase_ = new btAxisSweep3( btv3WorldAabbMin, btv3WorldAabbMax, iMaxProxies );
	
	// Its insert/add and remove of objects is generally faster than the sweep and prune broadphases btAxisSweep3 and bt32BitAxisSweep3
	pBtBroadPhase_ = new btDbvtBroadphase();
	
	// の拘束計算ソルバを作成する
	pBtSolver_ = new btSequentialImpulseConstraintSolver();

	// ワールドの作成
	pBtWorld_ = new btDiscreteDynamicsWorld( pBtCollisionDispatcher_, pBtBroadPhase_, pBtSolver_, pBtCollisionConfig_ );

	// 重力設定
	pBtWorld_->setGravity( btVector3( 0.0f, -9.8f, 0.0f ) );

	//カスタムコールバックの設定
	pFilterCallback_ = new FilterCallback::FilterCallbackUsingCollisionComponent();
	pBtWorld_->getPairCache()->setOverlapFilterCallback( pFilterCallback_ );

	//characterControllerGhostObjectで使っているはず
	//playerをcharacterControllerRigidbodyにしたのでいらない
	//pGhostPairCallback_ = new btGhostPairCallback();
	//btAxisSweep3* sweepBP = dynamic_cast<btAxisSweep3*>(pBtWorld_->getBroadphase());
	//assert( sweepBP && "" );
	//sweepBP->getOverlappingPairCache()->setInternalGhostPairCallback(pGhostPairCallback_);

	//pDebugDrawer_ = new CDxBulletDebugDrawer();
	//pDebugDrawer_ = new CDxBulletDebugDrawerEx();
	pDebugDrawer_ = new CSegaBulletDebugDrawer();
	pBtWorld_->setDebugDrawer(pDebugDrawer_);

	//gContactAddedCallback;
	//gContactProcessedCallback;
	//gContactDestroyedCallback;

	eventManager_ = new EventManager( "PhysicsEventManager" );
	IEventListenerPtr evListenner( new PhysicsEventListener() );
	eventManager_->addListener( evListenner, OnCollisionStayEventData::rtti );
	eventManager_->addListener( evListenner, OnCollisionEnterEventData::rtti );
	eventManager_->addListener( evListenner, OnCollisionExitEventData::rtti );
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
	pBtWorld_->addConstraint( pctConstraint, true );
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
	checkAllContactPoints();
}

void Manager::drawWorld() {
	pBtWorld_->debugDrawWorld();
	//pDebugDrawer_->drawWorld(pBtWorld_);
}
void Manager::drawObject( const btCollisionObject *pObj, unsigned int color ) {
	BtCollisionObjectDrawer::draw( pObj, color );
}

void Manager::drawConstraint(btTypedConstraint* pConstraint) {
	pBtWorld_->debugDrawConstraint( pConstraint );
}

void Manager::clearForces() {
	pBtWorld_->clearForces();
}

void Manager::abortEventAll()
{
	eventManager_->abortEvent( OnCollisionEnterEventData::rtti, true);
	eventManager_->abortEvent( OnCollisionStayEventData::rtti, true);
	eventManager_->abortEvent( OnCollisionExitEventData::rtti, true );
}

int Manager::getNumberCollisionObjects()const{
	return pBtWorld_->getCollisionObjectArray().size();
}


//sendEventManager
void Manager::checkAllContactPoints(){

	//TRACE1("checkAllContactPoints start!\n",0);

	CollisionPairs currentCollisionPairs;
	//TRACE0( _T("checkAllContactPoints start!\n") );
	//TRACE0( _T(" class name : id \n") );
	//Assume world->stepSimulation or world->performDiscreteCollisionDetection has been called
	int numManifolds = pBtWorld_->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold =  pBtWorld_->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obj0 = const_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obj1 = const_cast<btCollisionObject*>(contactManifold->getBody1());
		
		if( !obj0->getUserPointer() ||
			!obj1->getUserPointer() ) {
			continue;
		}

		//enterとexistイベントの他実装案について
		//btGhostObjectを使ったほうがいいかも（rigidBodyでは当たった物体を覚えておけない）
		//btGhostObject内で当たっているオブジェクトとか覚えておく、
		//そうすると、出たのとか、triggeredとかが実装できる（onCollisionStay()からEnter,Exitを発行）
		//enter, exit使いたいのは当たり判定なしの部屋(ビーム)みたいなのが多いんだしonCollisionStayイベントでroomクラスに送って
		//enterとexitを発生させる。
		//ここではstayのみ
		
		//do Swapp? 
		if( obj0 > obj1 ){
			btCollisionObject *temp = obj0; 
			obj0 = obj1;
			obj1 = temp;
		}


		
		Component::RigidBodyComponent *user0 = static_cast<Component::RigidBodyComponent*>( obj0->getUserPointer() );
		Component::RigidBodyComponent *user1 = static_cast<Component::RigidBodyComponent*>( obj1->getUserPointer() );

		if( user0->canCollide( obj1 ) &&  user1->canCollide( obj0 ) ){}
		else {
			//衝突しない場合イベントは作らない
			continue;
		}

		CollisionPair pair(obj0, obj1);
		CollisionPairs::iterator itPair = previousCollisionPairs_.find( pair );
		currentCollisionPairs.insert( pair );

		if( itPair==previousCollisionPairs_.end() ){
			//createEnterEvent
			//sendEnterEvent
			//createStayEvent
			//sendEnterEvent
			IEventDataPtr enter( new OnCollisionEnterEventData( contactManifold, obj0, obj1 ) );
			eventManager_->queueEvent(enter);
			IEventDataPtr stay( new OnCollisionStayEventData( contactManifold, obj0, obj1 ) );
			eventManager_->queueEvent(stay);
//#ifdef _DEBUG
//			if( obj0->getUserPointer() && obj1->getUserPointer() ){
//				GameObject::ICollider *userPtr0 = static_cast<GameObject::ICollider*>( obj0->getUserPointer() );
//				GameObject::ICollider *userPtr1 = static_cast<GameObject::ICollider*>( obj1->getUserPointer() );
//				
//				TRACE2( "%d, %d enter\n", obj0, obj1 );
//
//				TRACE4("%s : %d, %s : %d Enter!\n",
//					userPtr0->getRTTI().getClassName().c_str(),
//					userPtr0->getID(),
//					userPtr1->getRTTI().getClassName().c_str(),
//					userPtr1->getID()  );
//			}
//#endif//_DEBUG
		} else {
			//createStayEvent
			//sendEnterEvent
			IEventDataPtr stay( new OnCollisionStayEventData( contactManifold, obj0, obj1 ) );
			eventManager_->queueEvent(stay);
//#ifdef _DEBUG
//			if( obj0->getUserPointer() && obj1->getUserPointer() ){
//				GameObject::ICollider *userPtr0 = static_cast<GameObject::ICollider*>( obj0->getUserPointer() );
//				GameObject::ICollider *userPtr1 = static_cast<GameObject::ICollider*>( obj1->getUserPointer() );
//				
//				TRACE4("%s : %d, %s : %d Stay!\n",
//					userPtr0->getRTTI().getClassName().c_str(),
//					userPtr0->getID(),
//					userPtr1->getRTTI().getClassName().c_str(),
//					userPtr1->getID()  );
//			}
//#endif//_DEBUG

		}
	}
	CollisionPairs removedCollisionPairs;
	
	// use the STL set difference function to find collision pairs that existed during the previous tick but not any more
	std::set_difference( previousCollisionPairs_.begin(), previousCollisionPairs_.end(),
		currentCollisionPairs.begin(), currentCollisionPairs.end(),
		std::inserter( removedCollisionPairs, removedCollisionPairs.begin() ) );

	for ( CollisionPairs::const_iterator it = removedCollisionPairs.begin(), 
		end = removedCollisionPairs.end(); it != end; ++it )
	{
		btCollisionObject  *obj0 = it->first;
		btCollisionObject  *obj1 = it->second;

		//create ExitEvent
		IEventDataPtr exit( new OnCollisionExitEventData( obj0, obj1 ) );
		eventManager_->queueEvent(exit);
//#ifdef _DEBUG
//		if( obj0->getUserPointer() && obj1->getUserPointer() ){
//			GameObject::ICollider *userPtr0 = static_cast<GameObject::ICollider*>( obj0->getUserPointer() );
//			GameObject::ICollider *userPtr1 = static_cast<GameObject::ICollider*>( obj1->getUserPointer() );
			//TRACE2( "%d, %d remove\n", obj0, obj1 );
//				
//			TRACE4("%s : %d, %s : %d Exit!\n",
//				userPtr0->getRTTI().getClassName().c_str(),
//				userPtr0->getID(),
//				userPtr1->getRTTI().getClassName().c_str(),
//				userPtr1->getID()  );
//		}
//#endif//_DEBUG
	}

	// the current tick becomes the previous tick.  this is the way of all things.
	previousCollisionPairs_ = currentCollisionPairs;

	eventManager_->tick( EventManager::kINFINITE );
}
		//if(vp1 && vp2 ){
		//	TRACE2( "vp1:%d, vp2:%d hit\n", ob1, ob2 );
		//}
		//else if(vp1){
		//	TRACE1( "vp1 %d hit\n", *vp1 );
		//}
		//else if(vp2){
		//	TRACE1( "vp2 %d hit\n", *vp2 );
		//}
		/*
		bool isMMD = MMDFILTER , ob1->getBroadphaseHandle()->m_collisionFilterMask;

		if( vp1 && vp2 ){
			eventMngr->send( IEvent( contactManifold );
		}
		//null case
		else {
			if(vp1){
				ob2->isStaticObject();
				eventMngr->send( IEvent(vp1) );
			}
			if(vp2){
				ob2->isStaticObject()
				eventMngr->send( IEvent(vp1) );
			}
			return;
		}
		
		
		if( ob1->isStaticObject() ){}
		if( ob2->isStaticObject() ){}
		
		if( ob1->isKinematicObject() ){}
		if( ob2->isKinematicObject() ){}
		
		int flag = ob1->getCollisionFlags();
		//btCollisionObject::CollisionFlags;
		
		if( !ob1->isStaticOrKinematicObject() ){
			isMMD();
			ob1->getBroadphaseHandle();

			btRigidBody* rb1 = btRigidBody::upcast(ob1);
			//rb1->getCompanionId();
		}



		//mmdは 体は　static kinematic,　紙とかネクタイはdefault


		

		class IActor{
		public:
			int getType(){
				return 0;
			}
		};

		typedef int type;
		IActor *actor1 = static_cast<IActor*>(vp1);
		type type1 = actor1->getType();
		const int player=0;
		const int bullet=0;
		const int enemy=0;
		const int item=0;

		switch(type1){
		case player :  
		}

		
		//eventManager->send();

		//接触点の数
		//int numContacts = contactManifold->getNumContacts();
		//for (int j=0;j<numContacts;j++)
		//{
		//	btManifoldPoint& pt = contactManifold->getContactPoint(j);
		//	if (pt.getDistance()<0.f)
		//	{
		//		const btVector3& ptA = pt.getPositionWorldOnA();
		//		const btVector3& ptB = pt.getPositionWorldOnB();
		//		const btVector3& normalOnB = pt.m_normalWorldOnB;
		//	}
		//}
		*/

//#include"GameObject/ICollider.h"
//void hitAction( btPersistentManifold* contactManifold ){
//	btCollisionObject *obj1, *obj2;
//	//型変換
//	GameObject::ICollider* go1 = static_cast<GameObject::ICollider*>(obj1->getUserPointer());
//	GameObject::ICollider* go2 = static_cast<GameObject::ICollider*>(obj2->getUserPointer());
//	if(go1->getRootBtCollisionObject() == obj2) {
//		return;
//	}
//	if(go2->getRootBtCollisionObject() == obj1) {
//		return;
//	}
//
//	//hpの処理とノックバックをどう処理するか？
//	//せっかく物理エンジン使ってるからノックバックは自動でやらせたいが上記のが絡んでくる
//	//だから、BoneCollisionObjectはghostobjectにして爆弾処理みたいにしてやる
//	//boneGhostObjectか
//	//hpの処理はまとめてここでやってevent送信？
//	//それとも,BoneCollisionObject書いてしまうべきか?
//	//でも銃の弾みたいな、rigidBodyの場合、どうやって当たったの検出するの？
//	//btRigidBodyにそういう機能ついてたっけ
//}

//namespace {
//	struct ContactPointData{
//		btPersistentManifold* parent;
//		const btManifoldPoint& pt;
//		btCollisionObject* colObj0;
//		btCollisionObject* colObj1;
//	};
//
//	bool contactAddedCallback(
//		btManifoldPoint& cp,
//		const btCollisionObject* colObj0,
//		int partId0,
//		int index0,
//		const btCollisionObject* colObj1,
//		int partId1,
//		int index1
//	){
//		Manager::instance()->getWorldPtr()->getDispatcher()->getInternalManifoldPointer();
//		//cp.m_userPersistentData = &cp;
//	}
//
//	bool contactProcessedCallback(
//		btManifoldPoint& cp,
//		void* body0,
//		void* body1
//	){}
//
//	bool contactDestroyedCallback( void* userPersistentData ){
//		ContactPointData cpd;
//		//cpd.parent->getNumContacts()==1 or 0;
//	}
//}
}