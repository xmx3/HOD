#include"Accessory.h"
#include<btBulletDynamicsCommon.h>
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"MMD/Bone.h"
#include"AccessoryUtils/MME/Model.h"
#include"SegaTypeHelper.h"
#include<assert.h>
#include"BulletPhysics/Manager.h"
#include"GameObjectData/WeaponStatus.h"
#include"helper/MyOutputDebugString.h"
#include"MME/Manager.h"
#include"MME/Drawer/GameDrawer.h"
#include"MME/Enums.h"

#include"Component/RigidBodyComponent.h"

namespace GameObject{
	RTTI_IMPL(Accessory, BaseObject);

struct Accessory::KinematicMotionState : public btMotionState
{
	MMD::Bone	*mBone;

	KinematicMotionState(MMD::Bone *pBone )
		: mBone( pBone )
	{}
	virtual ~KinematicMotionState(){}

	///synchronizes world transform from user to physics
	virtual void getWorldTransform(btTransform& centerOfMassWorldTrans ) const
	{
		//tofix　うーんいろいろ無駄あるなーboneクラス自体も書き直したい
		centerOfMassWorldTrans=toBtTransform( mBone->getSkinningMatrix() );
		centerOfMassWorldTrans.setOrigin( toBtVector3(mBone->getPos()) );
	}

	///synchronizes world transform from physics to user
	///Bullet only calls the update of worldtransform for active objects
	virtual void setWorldTransform( const btTransform& centerOfMassWorldTrans )
	{}
};

//Accessory::Accessory( 
//	std::shared_ptr<btCollisionShape> shape,
//	std::shared_ptr<AccessoryUtils::MME::Model> model,
//	float mass,
//	btCollisionObject *owner,
//	Bone *bone
//)
//	:mRigidBody(NULL),
//	mOwner(owner),
//	mBone(bone),
//	mIsInWorld(false),
//	mKinematicMotion(NULL),
//	mDefaultMotion(NULL)
//{
//	mShape=shape;
//	mModel=model;
//
//	if(mModel){
//		mModel->setAccessory(this);
//	}
//
//	if( owner ){
//		ignoreCollision( owner );
//	}
//
//	if(mShape){
//		btTransform bttr;
//		if(bone){
//			bttr= toBtTransform( bone->getSkinningMatrix() );
//		} else {
//			bttr = btTransform::getIdentity();
//		}
//
//		// 慣性テンソルの計算
//		btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
//		if( mass != 0.0f ) mShape->calculateLocalInertia( mass, btv3LocalInertia );
//
//		// MotionStateを作成する。剛体の姿勢制御をするもの	
//		mKinematicMotion = new KinematicMotionState( bone );
//		//切り替えるためにもう一つ作っておく
//		mDefaultMotion = new btDefaultMotionState();
//	
//		// 剛体を作成する
//		// 質量 0.0、慣性テンソル 0.0 ならこの剛体は動かない
//		btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, mKinematicMotion, mShape.get(), btv3LocalInertia );
//		mRigidBody = new btRigidBody( rbInfo );
//
//		//静的オブジェクトを動かす必要がある場合は、Kinematicフラグを立てて使ってください。
//		mRigidBody->setCollisionFlags( btCollisionObject::CF_KINEMATIC_OBJECT );
//		//mRigidBody->setCollisionFlags( btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE );
//		
//		//kinematicな場合　DISABLE_DEACTIVATION　をセット
//		//またアニメーションしている間はsleeping/deactivationを無効にしてください。
//		//これは、Bulletの力学ワールドが毎フレームbtMotionStateから新しいワールド変換行列を取得するためです。
//		mRigidBody->setActivationState( DISABLE_DEACTIVATION );
//	
//		mRigidBody->setUserPointer( this );
//	}
//}

Accessory::Accessory(
	BtCollisionShapeAndBtTriangleMesh shapeAndMesh,
	std::shared_ptr<AccessoryUtils::MME::Model> model,
	float mass,
	btCollisionObject *owner,
	const btTransform &startTrans
)	
	:mRigidBody(),
	mOwner(owner),
	mBone(nullptr),
	mIsInWorld(false),
	mKinematicMotion(),
	mDefaultMotion(),
	mCanCollideCallback(nullptr)
{
	mShape	= shapeAndMesh.first;
	mMesh	= shapeAndMesh.second;
	mModel	= model;

	//TRACE3("shape: %d\nmodel: %d\nmesh: %d\n",
	//	mShape.use_count(),
	//	mModel.use_count(),
	//	mMesh.use_count() );
	
	if(mModel){
		mModel->setAccessory(this);
		MME::Drawer::GameDrawer::instance()->add( mModel );
	}

	if(mShape){
		// 慣性テンソルの計算
		btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
		if( mass != 0.0f ) mShape->calculateLocalInertia( mass, btv3LocalInertia );

		// MotionStateを作成する。剛体の姿勢制御をするもの	
		mKinematicMotion = std::make_shared<KinematicMotionState>( nullptr );
		//切り替えるためにもう一つ作っておく
		mDefaultMotion = std::make_shared<btDefaultMotionState>( startTrans );

		// 剛体を作成する
		// 質量 0.0、慣性テンソル 0.0 ならこの剛体は動かない
		btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, mDefaultMotion.get(), mShape.get(), btv3LocalInertia );
		mRigidBody = std::make_shared<btRigidBody>( rbInfo );
		mRigidBodyComponent = Component::RigidBodyComponent::create(
			this,
			mShape,
			mDefaultMotion,
			mRigidBody);
		//mRigidBodyComponent->setParent(this);

		mCanCollideCallback = new Component::CanCollideExceptIgnoredObjectsCallback();

		mRigidBodyComponent->setCanCollideCallback(mCanCollideCallback);
		mRigidBodyComponent->getOnEnterCallback().addRaw(this, &Accessory::onCollisionEnter);
	}
}

Accessory::~Accessory(){
	removeFromWorld();
	MME::Drawer::GameDrawer::instance()->remove(mModel);

	SAFE_DELETE(mCanCollideCallback);

	//TRACE3("shape: %d\nmodel: %d\nmesh: %d\n",
	//	mShape.use_count(),
	//	mModel.use_count(),
	//	mMesh.use_count() );
	
}

void Accessory::draw() const{
	//こっちのほうがHookでコントロールしやすい
	//if(mIsInWorld){
		
		if(mModel){
			mModel->drawUsingGameLib();
		}
	//}
}

void Accessory::debug_draw() const{
	if(mIsInWorld){
		BulletPhysics::Manager::drawObject( mRigidBody.get() );
	}
}

void Accessory::enableContactResponse( bool enable ){
	if(enable){
		int f = mRigidBody->getCollisionFlags();
		mRigidBody->setCollisionFlags( f & ~btCollisionObject::CF_NO_CONTACT_RESPONSE );
	} else {
		int f = mRigidBody->getCollisionFlags();
		mRigidBody->setCollisionFlags( f | btCollisionObject::CF_NO_CONTACT_RESPONSE );
	}
}

void Accessory::addToWorld(){
	if(!mIsInWorld){
		mCanCollideCallback->clearIgnoredObjects();
		if (mOwner) {
			mCanCollideCallback->addIgnoredObject(mOwner);
		}
		//初期位置をしっかり入れておく
		mRigidBody->getMotionState()->getWorldTransform( mRigidBody->getWorldTransform() );
		mRigidBodyComponent->addToWorld( BulletPhysics::DefaultFilter, BulletPhysics::AllFilterExceptMMDObject );
		mIsInWorld=true;
		//TRACE1( "Accessory::addToWorld()\n", 0 );
	}
}
void Accessory::removeFromWorld(){
	if(mIsInWorld){
		mRigidBodyComponent->removeFromWorld();
		mIsInWorld=false;
		//TRACE1( "Accessory::removeFromWorld()\n", 0 );
	}
}

//void Accessory::setIsKinematic( bool isKinematic ){
//	if(!isKinematic){
//		int f = mRigidBody->getCollisionFlags();
//		mRigidBody->setCollisionFlags( f & ~btCollisionObject::CF_KINEMATIC_OBJECT );
//		mRigidBody->forceActivationState( ACTIVE_TAG );
//	} else {
//		int f = mRigidBody->getCollisionFlags();
//		mRigidBody->setCollisionFlags( f | btCollisionObject::CF_KINEMATIC_OBJECT );
//		mRigidBody->setActivationState( DISABLE_DEACTIVATION );
//	}
//}

void Accessory::attachBone(MMD::Bone* bone){
	if(bone){
		mBone=bone;
		mKinematicMotion->mBone=bone;
	} else {
		if(!mBone){
			assert(false);
			return;
		}
	}
	mRigidBodyComponent->setMotionState( mKinematicMotion );
	mRigidBodyComponent->setIsKinematic(true);
}

void Accessory::separeteFromBone(){
	btTransform w;
	mRigidBody->getMotionState()->getWorldTransform(w);
	mDefaultMotion->setWorldTransform( w );
	mRigidBodyComponent->setMotionState( mDefaultMotion );
	mRigidBodyComponent->setIsKinematic(false);
}

void Accessory::setVelocity( const btVector3 &velocity ){
	mRigidBody->setLinearVelocity( velocity );
}

btCollisionObject* Accessory::getBtCollisionObject(){
	return mRigidBody.get();
}

//void Accessory::onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ){
//	TRACE1("Accessory::onCollisionStay()\n", 0);
//}

void Accessory::onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ){
	if( canCollideOnlyOnce() ){
		mCanCollideCallback->addIgnoredObject(obj);
	}
}

bool Accessory::isReady(){
	return mModel->isFinished();
}

bool Accessory::canDraw()const{
	return mModel && mModel->canDraw();
}

void Accessory::setCanDraw( bool canDraw ){
	if(mModel){
		mModel->setCanDraw( canDraw );
	}
}


void Accessory::setCanDraw( MME::MMDPass pass, bool canDraw ){
	mModel->setCanDraw( pass, canDraw );
}

const std::string& Accessory::getModelFileName()const{
	return mModel->getModelFileName();
}

void Accessory::preDrawMMD(){
	mModel->fitTransformToBone();
}


float Accessory::getScale()const{
	
	
	//assert( TRIANGLE_MESH_SHAPE_PROXYTYPE!=mShape->getShapeType()
		//&& "メッシュは共有して使っているので一つでもサイズを変えると全て変わってしまう");
	//assert( 
	//	mModel->getScale()==mShape->getLocalScaling().x() &&
	//	mModel->getScale()==mShape->getLocalScaling().y() &&
	//	mModel->getScale()==mShape->getLocalScaling().z() );
	return mModel->getScale();

}
void Accessory::setScale(float scale){

	
	//assert( TRIANGLE_MESH_SHAPE_PROXYTYPE!=mShape->getShapeType()
		//&& "メッシュは共有して使っているので一つでもサイズを変えると全て変わってしまう");

	mModel->setScale(scale);
	mShape->setLocalScaling( btVector3( scale, scale, scale ) );
}

void Accessory::setWeaponStatus(GameObjectData::WeaponStatusSharedPtr weapon)
{
	mWeapon = weapon;
}

bool Accessory::canCollideOnlyOnce() const
{
	return mWeapon && mWeapon->canCollideOnlyOnce;
}

int Accessory::calculateDamage()
{
	return mWeapon ? mWeapon->caluculateDamage() : 0;
}

bool Accessory::canDamage()
{
	return true;//変数で動的に制御もあり
}

const GameObjectData::WeaponStatus * Accessory::getWeaponStatus()
{
	return mWeapon.get();
}


}//end namespace GameObject