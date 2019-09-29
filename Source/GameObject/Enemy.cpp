#include"Enemy.h"

//#include"MMD/HumanModel.h"
#include"MME/Object/ModelKai.h"
#include"MME/Drawer/GameDrawer.h"
#include"XmlLoader/MME/Object/ModelKai.h"

#include"BulletPhysics/Manager.h"
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"helper/PrimitiveDrawer.h"
#include<GameLib/Math/Random.h>
#include"GameObjectData/Status.h"
#include"GameObjectData/WeaponStatus.h"
#include<assert.h>
#include<GameLib/GameLib.h>
#include<GameLib/Framework.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/FileIO/InFile.h>
#include"Accessory.h"
#include"helper/MyOutputDebugString.h"
#include<limits>

#include"GameObject/Event/EventData/AddToWorld.h"
#include"GameObject/Event/EventData/RemoveFromWorld.h"
#include"GameObject/Event/EventData/KilledEnemy.h"
#include"GameObject/Event/Manager.h"

#include"XmlFiles.h"

#include"HelperFunc.h"
#include"GUI/Label.h"
#include"GUI/Manager.h"

#include"SegaTypeHelper.h"
#include<BulletCollision/CollisionShapes/btBoxShape.h>


namespace GameObject{

RTTI_IMPL( Enemy, BaseObject );




namespace {
	static const float skMaxTimeThatRemoveObjectFromWorld=5.f;
	//射角
	static const float skCos30 = (float)0.70710678118654752440084436210485;
	static const float skCos60 = 0.5;
	static const float skCoolTime = 1.f;
	static const float skBulletSpeed = 14.f*6.f;//miku身長
	static const float skAttakingRange=50.f;

}
EnemySharedPtr Enemy::create(
	float mass,
	MME::Object::ModelKaiSharedPtr model,
	BtBoxShapeSharedPtr shape,
	BtMotionStateSharedPtr motionState,
	BtRigidBodySharedPtr rigidbody,
	GameObjectData::StatusSharedPtr status)
{
	//btVector3 pos = player->getConstBtCollisionObject()->getWorldTransform().getOrigin();
	//GameLib::Framework f;
	//static GameLib::Math::Random r=GameLib::Math::Random::create( f.time() );
	//float x = r.getFloat( -30.f, 30.f );
	//float y = 30.f;
	//float z = r.getFloat( -30.f, 30.f );
	//pos += btVector3( x, y, z );
	//btMatrix3x3 matR = btMatrix3x3::getIdentity();
	//btQuaternion q;
	//q.setRotation( btVector3( 0.f, 1.0, 0.f ), r.getFloat( 0.f, D3DX_PI ) );
	//matR.setRotation(q);


	EnemySharedPtr ptr( NEW Enemy());

	ptr->init(
		mass,
		model,
		shape,
		motionState,
		rigidbody,
		status
	);

	return ptr;
}


Enemy::Enemy()
	:mElapsedTime(0.f),
	mElapsedTimeSinceDeath(0.f),
	mModel(),
	mElapsedTimeAfterLunch(0.f),
	mHpBar(NULL),
	mHpBackGroundBar(NULL),
	mDamageValueForChain(0),
	mChain(0)

{
	mFilterGroup = BulletPhysics::EnemyFilter;
	mFilterMask = BulletPhysics::AllFilter & ~BulletPhysics::MMDObjectFilter;

	mHpBackGroundBar = NEW GUI::Label( 0, 0, 0, 0 );
	mHpBar = NEW GUI::Label( 0, 0, 0, 0 );
}

Enemy::~Enemy(){
	SAFE_DELETE( mHpBar );
	SAFE_DELETE( mHpBackGroundBar );
	MME::Drawer::GameDrawer::instance()->remove(mModel);

	removeFromWorld();
	
	//bug起こしたので戒めに残しておく
	//if(mIsInWorld){
	//	BulletPhysics::Manager::instance()->removeFromWorld( mRigidBody.get() );
	//	mIsInWorld=false;
	//	//消すものをsharedFromThisしてどうするんだ
	//	//Event::Manager::instance()->queueEvent( Event::EventData::RemoveFromWorld::create( shared_from_this() ) );
	//}
}

void Enemy::init(
	float mass,
	MME::Object::ModelKaiSharedPtr model,
	BtBoxShapeSharedPtr shape,
	BtMotionStateSharedPtr motionState,
	BtRigidBodySharedPtr rigidbody,
	GameObjectData::StatusSharedPtr status)
{

	if (
		mModel ||
		mRigidBodyComponent ||
		mStatus)
	{
		assert(false && "it has already allocated.");
		return;
	}

	mModel = model;


	mRigidBodyComponent =
		Component::RigidBodyComponent::create(
			this,
			shape,
			motionState,
			rigidbody);
	//modelの初期位置
	const btTransform &world = mRigidBodyComponent->getWorldTransform();

	mModel->init(toDxMatrix(world), "stand");

	auto func = std::bind(&Enemy::onCollisionEnter, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 );

	mRigidBodyComponent->getOnEnterCallback().add( func );

	mMass = mass;

	mStatus = status;

}

void Enemy::addToWorld(){
	if(!mRigidBodyComponent->isInWorld()){
		const btTransform &trans = mRigidBodyComponent->getWorldTransform();

		
		mModel->init(toDxMatrix(trans), "stand");
		
	
		//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
		btVector3 backward = trans.getBasis()[2];
		backward.setX(-backward.x());
		backward.normalize();
		btVector3 forward = -backward;

		mRigidBodyComponent->getRigidBody()->setLinearVelocity(forward * mStatus->speed);


		mModel->addToWorld();


		//HUDの設定
		GUI::Manager *m = GUI::Manager::instance();
		m->add( mHpBackGroundBar );
		m->add( mHpBar );

		bool b = mRigidBodyComponent->addToWorld( mFilterGroup, mFilterMask);
		assert(b);

		MME::Drawer::GameDrawer::instance()->add(mModel);
	}
}

void Enemy::removeFromWorld(){
	if (mRigidBodyComponent->isInWorld()) {
		mModel->removeFromWorld();

		bool b = mRigidBodyComponent->removeFromWorld();
		assert(b);
		
		GUI::Manager *m = GUI::Manager::instance();
		m->remove( mHpBackGroundBar );
		m->remove( mHpBar );
		
		mModel->setCanRemove(true);
	}
}

void Enemy::postdraw() const {
	if(mRigidBodyComponent->isInWorld()){
		const btTransform &w =mRigidBodyComponent->getWorldTransform();

		mModel->update( toDxMatrix(w), mElapsedTime );
		
		if( isDied() ){
			const float transparency = 1.f - (mElapsedTimeSinceDeath / skMaxTimeThatRemoveObjectFromWorld);
			
			unsigned int color = static_cast<int>(transparency * 255) << 24 ;
			unsigned int yellow = 0x00ffff00;
			color = color | yellow;
			btRigidBody *rb = mRigidBodyComponent->getRigidBody().get();
			PrimitiveDrawer::draw( rb, color, false );		
		} else {
			btRigidBody *rb = mRigidBodyComponent->getRigidBody().get();
			PrimitiveDrawer::draw( rb, 0x88ffff00, true );
		}


		//if(  mPlayer ){
		//	const btTransform &trans = mRigidBody->getWorldTransform();

		//	btVector3 dir = mPlayer->getWorldTransform().getOrigin() - trans.getOrigin() ;
		//	float length = dir.length();
		//	if( length!=0 ){
		//		dir /= length;
		//	}

		//	assert( length!=0 );
		//	//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
		//	btVector3 backward = trans.getBasis()[2];
		//	backward.setX(-backward.x());
		//	backward.normalize ();

		//	btVector3 forward = -backward;

		//	float dot = forward.dot( dir );

		//	//角度が60度以内で近いなら射線表示
		//	if( length <skAttakingRange && dot > skCos60  ){
		//		dir.setY(0.f);
		//		//黄色から赤に色が変わる、危険度
		//		D3DXCOLOR from=0xff00ff00, to=0xffff0000;
		//		float t = mElapsedTimeAfterLunch/skCoolTime;
		//		t*=t;
		//		D3DXCOLOR c;
		//		D3DXColorLerp( &c, &from, &to, t ); 

		//		PrimitiveDrawer::drawLine(toVector3(trans.getOrigin()), toVector3(skBulletSpeed*dir+trans.getOrigin()), c );
		//	}
		//}
			
		unsigned int hpColor = 0xffff0000;
		unsigned int hpBgColor = 0xff806040;

		GameLib::Vector4 pos( toVector3(w.getOrigin()) );

		//drawHpBar( 
		//	mHpBar, mHpBackGroundBar,
		//	pos,
		//	mStatus->hp.rate(),
		//	hpColor,
		//	hpBgColor );
	}
}

void Enemy::update( float elapsedTime ) {
	mElapsedTime = elapsedTime;
	if( mRigidBodyComponent->isInWorld() ){
		if( isDied() ){
			updateWhenDied(elapsedTime);
			return;
		}
		


		//if(  mPlayer ){
		//	const btTransform &trans = mRigidBody->getWorldTransform();

		//	btVector3 dir = mPlayer->getWorldTransform().getOrigin() - trans.getOrigin() ;
		//	float length = dir.length();
		//	if( length!=0 ){
		//		dir /= length;
		//	}

		//	assert( length!=0 );
		//	//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
		//	btVector3 backward = trans.getBasis()[2];
		//	backward.setX(-backward.x());
		//	backward.normalize ();

		//	btVector3 forward = -backward;

		//	float dot = forward.dot( dir );

		//	//射角
		//	//角度が60度以内で近く、狙いが定まったらなら弾発射
		//	if( length < skAttakingRange && dot > skCos60 ){
		//		mElapsedTimeAfterLunch+=elapsedTime;		
		//		if( mElapsedTimeAfterLunch > skCoolTime ){
		//			for( int i=0; i< NumberBullets; ++i ){
		//				if(!mBullets[i]->isInWorld()){
		//					dir.setY(0.f);
		//					mBullets[i]->lunch( trans,  skBulletSpeed*dir );
		//					mElapsedTimeAfterLunch = 0.f;
		//					break;
		//				}
		//			}
		//		}
		//	} else {
		//		mElapsedTimeAfterLunch = 0.f;
		//	}

		//	float accelSpeed = 50.f;
		//	//mRigidBody->applyCentralImpulse( dir*mMass*accelSpeed );
		//}

		//btVector3 velocity = mRigidBody->getLinearVelocity();
		//btScalar speed = velocity.length();
		//float maxSpeed = 200.f;
		//if(speed > maxSpeed) {
		//	velocity *= maxSpeed/speed;
		//	mRigidBody->setLinearVelocity(velocity);
		//}
	}
}
void Enemy::onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ) {
	
	auto rb = static_cast<Component::RigidBodyComponent*>(obj->getUserPointer());
	const RTTI &rtti = rb->getOwner()->getRTTI();
	//TRACE1("Enemy::onCollisionEnter: %s\n", rtti.getClassName().c_str());

	auto *collide = rb->getOwner();
	auto *weapon = collide->getWeaponStatus();

	if (collide->canDamage()) {
		takeDamage(collide);
	}
	else if ( rtti.isExactly(Enemy::rtti) ){
		if (Enemy *enemy = dynamic_cast<Enemy*>(collide)) {
			if (enemy->isDied()) {
				mStatus->hp.add(-enemy->mDamageValueForChain);
				mChain = std::max( mChain, enemy->mChain);
				mDamageValueForChain =  std::max(mDamageValueForChain, static_cast<int>(enemy->mDamageValueForChain*0.4f));
			}
		}

	}

	//weapon->damageTypes;//ダメージタイプによる場合分け
	//アニメーション
	//hitback
	//吹っ飛び等


	if( isDied() )
	{
		//はじめて死んだとき
		if(mElapsedTimeSinceDeath==0.f){
			//もう一回こことおらないようにちょっと足しておく
			mElapsedTimeSinceDeath = (std::numeric_limits<float>::min)();
			
			++mChain;

			//send event maneger
			auto evmngr = Event::Manager::instance();
			auto enemy = std::dynamic_pointer_cast<Enemy>(shared_from_this());
			evmngr->queueEvent(Event::EventData::KilledEnemy::create(enemy) );
			
			//死んだら回転するようにする
			btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
			mRigidBodyComponent->getShape()->calculateLocalInertia( mMass, btv3LocalInertia );
			mRigidBodyComponent->getRigidBody()->setMassProps( mMass, btv3LocalInertia );
		}

		if (weapon && weapon->hitbackValue != 0.f) {
			//btTransform xform = mRigidBodyComponent->getRigidBody()->getWorldTransform();
			////軸を求める
			////xform*z0
			//btVector3 backDir = xform.getBasis()[2];
			//backDir.setX(-backDir.x());
			//backDir.normalize();
			//mRigidBodyComponent->getRigidBody()->applyCentralImpulse(backDir*mMass*weapon->hitbackValue);

			const auto &pos0 = mRigidBodyComponent->getRigidBody()->getWorldTransform().getOrigin();
			const auto &pos1 = obj->getWorldTransform().getOrigin();

			auto dir = pos0 - pos1;
			dir.safeNormalize();
			mRigidBodyComponent->getRigidBody()->applyCentralImpulse(dir*mMass*weapon->hitbackValue);


		}

	}
}

//void Enemy::attack( GameObjectData::Status *obj ){
	//mWeaponStatus->attack( obj );
//}

//void Enemy::applyCentralForce( const btVector3 &force ){
//	mRigidBody->applyCentralForce( force );
//}

bool Enemy::isDied()const {
	return mStatus->isDied();
}


void Enemy::updateWhenDied( float elapsedTime )
{
	mElapsedTimeSinceDeath += elapsedTime;
	if( mElapsedTimeSinceDeath > skMaxTimeThatRemoveObjectFromWorld){
		removeFromWorld();
	}
}

btCollisionObject * Enemy::getBtCollisionObject()
{
	return mRigidBodyComponent->getBtCollisionObject();
}


const btCollisionObject * Enemy::getConstBtCollisionObject() const
{
	return mRigidBodyComponent->getConstBtCollisionObject();
}
const btTransform& Enemy::getWorldTransform()const {
	return mRigidBodyComponent->getWorldTransform();
}

btTransform& Enemy::getWorldTransform() {
	return mRigidBodyComponent->getWorldTransform();
}

bool Enemy::isInWorld()const {
	return mRigidBodyComponent->isInWorld();
}

void Enemy::takeDamage(BaseObject * DamageCauser)
{
	//TRACE("Enemy::takeDamage()\n");

	auto *weapon = DamageCauser->getWeaponStatus();
	int d = weapon->caluculateDamage();
	mStatus->hp.add(-d);
	mDamageValueForChain = std::max(mDamageValueForChain, d);
}

int Enemy::calculateDamage()
{
	assert(false);
	return 0;
}

bool Enemy::canDamage()
{
	return false;
}

const GameObjectData::WeaponStatus * Enemy::getWeaponStatus()
{
	return nullptr;
}

}
