#include"BoneCollisionObject.h"
#include"BulletPhysics/Manager.h"
#include<btBulletDynamicsCommon.h>
#include<BulletCollision/CollisionDispatch/btGhostObject.h>
#include"MMD/Bone.h"
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"helper/PrintBtVector3.h"
#include"GameObject/CharacterControllerGhostObject.h"
#include<GameLib/Scene/Container.h>
#include<GameLib/GameLib.h>
#include"SegaTypeHelper.h"
#include"helper/PrimitiveDrawer.h"
#include<GameLib/Scene/Batch.h>
#include"GameObjectData/Status.h"
#include"GameObjectData/WeaponStatus.h"
#include"Enemy.h"

using BulletPhysicsHelper::toBtTransform;
namespace GameObject {

RTTI_IMPL( BoneCollisionObject, ICollider );
//RTTI_IMPL( GameObject::BoneCollisionObject, GameObject::ICollider );


struct BoneCollisionObject::Model {
	Model()
		:mBatchs(NULL),
		mScale(1.f),
		mNumBatchs(0)
	{}
	~Model(){
		SAFE_DELETE_ARRAY( mBatchs );
		mScale=0.f;
		mNumBatchs=0;
	}
	void setScale( const float & s ){
		mScale=s;
	}
	void createBatchsArray( unsigned int numBatchs ){
		mNumBatchs=numBatchs;
		mBatchs = new GameLib::Scene::Batch[mNumBatchs];
	}
	void setBatch( unsigned int index, GameLib::Scene::Batch b ){
		assert( index < mNumBatchs );
		mBatchs[index]=b;
	}
	void draw( const btTransform &bttr ){
		using namespace GameLib::Graphics;

		GameLib::Math::Matrix34 w34= toMatrix34( bttr );
		w34.scale(mScale);
		Manager::instance().setWorldMatrix( w34 );
		Manager::instance().setAmbientColor( GameLib::Math::Vector3(1.f) ); 

		for( unsigned int i=0; i<mNumBatchs; ++i){
			mBatchs[i].draw();
		}
	}
	GameLib::Scene::Batch *mBatchs;
	unsigned int mNumBatchs;
	float mScale;
};

struct BoneCollisionObject::KinematicMotionState : public btMotionState
{
	CBone	*mBone;

	KinematicMotionState(CBone *pBone )
		: mBone( pBone )
	{}
	virtual ~KinematicMotionState(){}

	///synchronizes world transform from user to physics
	virtual void getWorldTransform(btTransform& centerOfMassWorldTrans ) const
	{
		//fix　うーんいろいろ無駄あるなーboneクラス自体も書き直したい
		centerOfMassWorldTrans=toBtTransform( mBone->getSkinningMatrix() );
		centerOfMassWorldTrans.setOrigin( toBtVector3(mBone->getPos()) );
	}

	///synchronizes world transform from physics to user
	///Bullet only calls the update of worldtransform for active objects
	virtual void setWorldTransform( const btTransform& centerOfMassWorldTrans )
	{}
};

BoneCollisionObject::BoneCollisionObject(
	float mass,
	float start, float end,
	std::shared_ptr<btCollisionShape> shape,
	btCollisionObject *owner,
	CBone *bone,
	GameObjectData::WeaponStatus *weaponStatus )
	:
	//mGhost(NULL),
	mRigidBody(NULL),
	mShape(shape),
	mBtObjOfOwner(owner),
	mBone(bone),
	mIsInWorld(false),
	mStart(start), mEnd(end),
	mModel(NULL),
	//mContainer(NULL),
	mWeaponStatus(weaponStatus)
{
	btTransform bttr= toBtTransform( bone->getSkinningMatrix() );

	// 慣性テンソルの計算
	btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
	if( mass != 0.0f ) mShape->calculateLocalInertia( mass, btv3LocalInertia );

	// MotionStateを作成する。剛体の姿勢制御をするもの	
	btMotionState *pMotionState = new KinematicMotionState( bone );

	// 剛体を作成する
	// 質量 0.0、慣性テンソル 0.0 ならこの剛体は動かない
	btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, pMotionState, mShape.get(), btv3LocalInertia );
	mRigidBody = new btRigidBody( rbInfo );

	//mRigidBody = BulletPhysicsHelper::createRigidBody( mass, bttr, mShape );
	
	//mRigidBody->setCollisionFlags( btCollisionObject::CF_KINEMATIC_OBJECT );
	mRigidBody->setCollisionFlags( btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE );
	mRigidBody->setActivationState( DISABLE_DEACTIVATION );
	if( owner ){
		ignoreCollision(owner);
	}
	mRigidBody->setUserPointer( this );
}
BoneCollisionObject::~BoneCollisionObject(){
	removeFromWorld();
	SAFE_DELETE(mModel);
	//SAFE_DELETE(mContainer);

	btMotionState* pM = mRigidBody->getMotionState();
	SAFE_DELETE( pM );
	SAFE_DELETE(mRigidBody);
	//mShape.reset( (void*)0 );
}

void BoneCollisionObject::addToWorld(){
	if(!mIsInWorld){
		//初期位置をしっかり入れておく
		mRigidBody->getMotionState()->getWorldTransform( mRigidBody->getWorldTransform() );
		//const int mmdFilter = 0x7fc0;
		//BulletPhysics::Manager::instance()->addToWorld( mRigidBody, btBroadphaseProxy::DefaultFilter, btBroadphaseProxy::AllFilter & ~mmdFilter );
		BulletPhysics::Manager::instance()->addToWorld( mRigidBody, btBroadphaseProxy::DefaultFilter, btBroadphaseProxy::AllFilter & ~BulletPhysics::Manager::MMDObjectFilter );
		mIsInWorld=true;
	}
}
void BoneCollisionObject::removeFromWorld(){
	if(mIsInWorld){
		BulletPhysics::Manager::instance()->removeFromWorld( mRigidBody );
		mIsInWorld=false;
	}
}
	
//float はたいていの場合　elapsedTime=1.f/30.f sec
//だが、BoneCollisionObjectの場合のみ currentFrame
//発生フレームと終了フレームで当たり判定を出すため現在のフレームが欲しい
void BoneCollisionObject::update( float currentFrame ){
	if( mStart <= currentFrame && currentFrame <= mEnd ){
		addToWorld();
	}
	else {
		removeFromWorld();
	}
}
	
void BoneCollisionObject::draw() const{
	using namespace GameLib::Math;
	using namespace GameLib::Graphics;
	
	if( mIsInWorld ){
//#ifdef _DEBUG
		//1フレーム遅れた表示
		//当たり判定の表示
		PrimitiveDrawer::draw( mRigidBody, 0xffff0000 );
//#endif
		//ボーン更新後で物理更新前なのでmRigidBody->getWorldTransform()では1フレーム遅れる
		//実際に表示するのはmodel(ミクさん)に一致して欲しいのでkinematicMotionStateから直接もらてくる
		if(mModel){
			btTransform w;
			mRigidBody->getMotionState()->getWorldTransform(w);
			
			mModel->draw(w);
		}
	}
		
	
}

//btTransform const & BoneCollisionObject::getWorldTransform() const{
//	return mRigidBody->getWorldTransform();
//}
//btTransform & BoneCollisionObject::getWorldTransgorm(){
//	return mRigidBody->getWorldTransform();
//}

btCollisionObject* BoneCollisionObject::getBtCollisionObject(){
	return mRigidBody;
}

void BoneCollisionObject::onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ) {
	assert(me==mRigidBody);
	
	ICollider *gameObj = static_cast<ICollider*>( obj->getUserPointer() );
	//if (gameObj->getRTTI().isExactly( BoneCollisionObject::rtti ) )
	//{
	//	//btVector3 vel = mBtObjOfOwner->getWorldTransform().getOrigin() - obj->getWorldTransform().getOrigin();
	//	btVector3 vel = me->getWorldTransform().getOrigin() - obj->getWorldTransform().getOrigin();
	//		
	//	float l = vel.length();
	//	if( l== 0.f ){
	//		return;
	//	}
	//	vel /= l;
	//	
	//	ICollider *gameOwnerObj = static_cast<ICollider*>( mBtObjOfOwner->getUserPointer() );

	//	float knocbackLength = 2.f;

	//	//親をノックバック
	//	if( gameOwnerObj->getRTTI().isExactly( CharacterControllerGhostObject::rtti ) ){
	//		//CharacterControllerGhostObject* cco = static_cast<CharacterControllerGhostObject*>(gameOwnerObj);
	//		//cco->strafe( mBtObjOfOwner->getWorldTransform().getOrigin() + knocbackLength*vel  );
	//		//アニメーション欲しい？
	//	} else if( mBtObjOfOwner->getInternalType() ==btCollisionObject::CO_RIGID_BODY ){
	//		//btRigidBody::upcast(mBtObjOfOwner)->applyCentralForce( vel );
	//	}
	//}
}

//float BoneCollisionObject::getMass() const {
//	return 1.f/mRigidBody->getInvMass();
//}

void BoneCollisionObject::calcDamage( GameObjectData::Status *st ){
	mWeaponStatus->attack( st );
}

//void BoneCollisionObject::setWeaponStatus( GameObjectData::WeaponStatus *weaponSt ){
//	mWeaponStatus=weaponSt;
//}

void BoneCollisionObject::attack( Enemy *enemy, GameObjectData::Status *enemyStatus ){
	calcDamage( enemyStatus );
	btVector3 vec2Enemy = enemy->getWorldTransform().getOrigin() - mRigidBody->getWorldTransform().getOrigin();
	float length = vec2Enemy.length();
	if(length > 0 ){
		vec2Enemy /= length;
	} else {
		length=1.f;
		vec2Enemy.setValue( 0.f, 1.f, 0.f );
	}
	//const float *normalVel = mWeaponStatus->knockBackNormalVel;
	//const float *velocity = mWeaponStatus->knockBackVelSpeed;
	//const float upDownWardOffset = mWeaponStatus->upDownwardOffset
	
	//距離が近いほど衝撃を大きくする。
	//length*=0.003f;
	//length*=length;
	//vec2Enemy/=length;

	float power = 10.f;
	enemy->hitback( vec2Enemy*enemy->getMass()*power );
}

void BoneCollisionObject::createModel( unsigned int numBatchs, float scale ){
	if(mModel){
		SAFE_DELETE(mModel);
	} 
	mModel=new Model;
	mModel->createBatchsArray( numBatchs );
	mModel->setScale( scale );
}

void BoneCollisionObject::setBatch( unsigned int index, GameLib::Scene::Batch b ){
	assert(mModel);
	mModel->setBatch( index, b );
}

}//end namespace GameObject