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
#include"GameObject/Bullet.h"
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
#include"GameObject/Event/Manager.h"

#include"XmlFiles.h"

#include"HelperFunc.h"
#include"GUI/Label.h"
#include"GUI/Manager.h"

#include"SegaTypeHelper.h"
#include<BulletCollision/CollisionShapes/btBoxShape.h>


namespace GameObject{

RTTI_IMPL( Enemy, IRigidBody );
std::shared_ptr<GameObjectData::Status> Enemy::sspStatus;
std::shared_ptr<GameObjectData::WeaponStatus> Enemy::sBulletWeaponStatus;
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
		const IColliderSharedPtr &player,
		MME::Object::ModelKaiSharedPtr model,
		std::shared_ptr<btBoxShape> box,
		const GameObjectData::Status &status,
		const GameObjectData::WeaponStatus &weaponStatus)
{
	btVector3 pos = player->getConstBtCollisionObject()->getWorldTransform().getOrigin();
	GameLib::Framework f;
	static GameLib::Math::Random r=GameLib::Math::Random::create( f.time() );
	float x = r.getFloat( -30.f, 30.f );
	float y = 30.f;
	float z = r.getFloat( -30.f, 30.f );
	pos += btVector3( x, y, z );
	btMatrix3x3 matR = btMatrix3x3::getIdentity();
	btQuaternion q;
	q.setRotation( btVector3( 0.f, 1.0, 0.f ), r.getFloat( 0.f, D3DX_PI ) );
	matR.setRotation(q);


	EnemySharedPtr ptr( 
		NEW Enemy( 
			btTransform( matR, pos ),
			model,
			box,
			status,
			weaponStatus
		) 
	);
	ptr->setPlayer( player );
	ptr->initBullet();

	return ptr;
}


Enemy::Enemy(
		const btTransform &world,
		MME::Object::ModelKaiSharedPtr model,
		std::shared_ptr<btBoxShape> box,
		const GameObjectData::Status &status,
		const GameObjectData::WeaponStatus &weaponStatus
	)
	:mPlayer(NULL),
	mElapsedTime(0.f),
	mElapsedTimeSinceDeath(0.f),
	mModel(model),
	mShape(box),
	mElapsedTimeAfterLunch(0.f),
	mHpBar(NULL),
	mHpBackGroundBar(NULL)
{
	mFilterGroup = BulletPhysics::Manager::EnemyFilter;
	mFilterMask = btBroadphaseProxy::AllFilter & ~BulletPhysics::Manager::MMDObjectFilter;

	mMass=status.mass;

	mStatus = GameObjectData::Status::create();
	*mStatus = status;
	mStatus->group=GameObjectData::GroupEnemy;

	mWeaponStatus = std::make_shared<GameObjectData::WeaponStatus>();
	*mWeaponStatus=weaponStatus;
	mWeaponStatus->me=mStatus;

	// 慣性テンソルの計算
	btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
	//回転しないように
	//mShape->calculateLocalInertia( mMass, btv3LocalInertia );

	// MotionStateを作成する。剛体の姿勢制御をするもの	
	btMotionState *pMotionState = new btDefaultMotionState( world );

	// 剛体を作成する
	btRigidBody::btRigidBodyConstructionInfo rbInfo( mMass, pMotionState, mShape.get(), btv3LocalInertia );
	//rbInfo.m_friction = 0.5f;//通常0.5
	mRigidBody.reset( new btRigidBody( rbInfo ) );

	mRigidBody->setUserPointer(this);
	
	mModel->init( toDxMatrix(mRigidBody->getWorldTransform()), "stand" );
	MME::Drawer::GameDrawer::instance()->add(mModel);

	mHpBackGroundBar = NEW GUI::Label( 0, 0, 0, 0 );
	mHpBar = NEW GUI::Label( 0, 0, 0, 0 );
}

Enemy::~Enemy(){
	SAFE_DELETE( mHpBar );
	SAFE_DELETE( mHpBackGroundBar );
	
	//イベントを起こしたくないのでremoveFromWorld()は使わない
	//removeFromWorld();
	IRigidBody::defalut_removeFromWorld();
	
	//bug起こしたので戒めに残しておく
	//if(mIsInWorld){
	//	BulletPhysics::Manager::instance()->removeFromWorld( mRigidBody.get() );
	//	mIsInWorld=false;
	//	//消すものをsharedFromThisしてどうするんだ
	//	//Event::Manager::instance()->queueEvent( Event::EventData::RemoveFromWorld::create( shared_from_this() ) );
	//}
	
	btMotionState* pM = mRigidBody->getMotionState();
	SAFE_DELETE( pM );
	mRigidBody.reset();
}

void Enemy::addToWorld(){
	if(!mIsInWorld){
		mModel->addToWorld();
		mModel->init( toDxMatrix(mRigidBody->getWorldTransform()), "stand" );
		Event::Manager::instance()->queueEvent( Event::EventData::AddToWorld::create( getIColliderSharedPtr() ) );
		GUI::Manager *m = GUI::Manager::instance();
		m->add( mHpBackGroundBar );
		m->add( mHpBar );
		defalut_addToWorld();
	}
}

void Enemy::removeFromWorld(){
	if(mIsInWorld){
		mModel->removeFromWorld();
		Event::Manager::instance()->queueEvent( Event::EventData::RemoveFromWorld::create( getIColliderSharedPtr() ) );
		defalut_removeFromWorld();
		GUI::Manager *m = GUI::Manager::instance();
		m->remove( mHpBackGroundBar );
		m->remove( mHpBar );
	}
}

void Enemy::postdraw() const {
	if(mIsInWorld){
		mModel->update( toDxMatrix(mRigidBody->getWorldTransform()), mElapsedTime );
		
		if( isDied() ){
			const float transparency = 1.f - (mElapsedTimeSinceDeath / skMaxTimeThatRemoveObjectFromWorld);
			
			unsigned int color = static_cast<int>(transparency * 255) << 24 ;
			unsigned int yellow = 0x00ffff00;
			color = color | yellow;
			PrimitiveDrawer::draw( mRigidBody.get(), color, false );		
		} else {
			PrimitiveDrawer::draw( mRigidBody.get(), 0x88ffff00, true );	
		}

		if(  mPlayer ){
			const btTransform &trans = mRigidBody->getWorldTransform();

			btVector3 dir = mPlayer->getWorldTransform().getOrigin() - trans.getOrigin() ;
			float length = dir.length();
			if( length!=0 ){
				dir /= length;
			}

			assert( length!=0 );
			//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
			btVector3 backward = trans.getBasis()[2];
			backward.setX(-backward.x());
			backward.normalize ();

			btVector3 forward = -backward;

			float dot = forward.dot( dir );

			//角度が60度以内で近いなら射線表示
			if( length <skAttakingRange && dot > skCos60  ){
				dir.setY(0.f);
				//黄色から赤に色が変わる、危険度
				D3DXCOLOR from=0xff00ff00, to=0xffff0000;
				float t = mElapsedTimeAfterLunch/skCoolTime;
				t*=t;
				D3DXCOLOR c;
				D3DXColorLerp( &c, &from, &to, t ); 

				PrimitiveDrawer::drawLine(toVector3(trans.getOrigin()), toVector3(skBulletSpeed*dir+trans.getOrigin()), c );
			}
		}

		using namespace GameLib::Graphics;
		GameLib::Graphics::Manager gm;
		gm.setLightingMode(LIGHTING_NONE);
		//mModel->();

		
			
		unsigned int hpColor = 0xffff0000;
		unsigned int hpBgColor = 0xff806040;
		
		GameLib::Vector4 pos( mRigidBody->getWorldTransform().getOrigin() );

		drawHpBar( 
			mHpBar, mHpBackGroundBar,
			pos,
			mStatus->hp/mStatus->maxHp,
			hpColor,
			hpBgColor );
	}

	for( int i=0; i< NumberBullets; ++i ){
		mBullets[i]->draw();
	}


}

void Enemy::update( float elapsedTime ) {
	mElapsedTime = elapsedTime;
	for( int i=0; i< NumberBullets; ++i ){
		mBullets[i]->update(elapsedTime);
	}
	if( mIsInWorld ){
		if( isDied() ){
			updateWhenDied(elapsedTime);
			return;
		}

		
		if(  mPlayer ){
			const btTransform &trans = mRigidBody->getWorldTransform();

			btVector3 dir = mPlayer->getWorldTransform().getOrigin() - trans.getOrigin() ;
			float length = dir.length();
			if( length!=0 ){
				dir /= length;
			}

			assert( length!=0 );
			//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
			btVector3 backward = trans.getBasis()[2];
			backward.setX(-backward.x());
			backward.normalize ();

			btVector3 forward = -backward;

			float dot = forward.dot( dir );

			//射角
			//角度が60度以内で近く、狙いが定まったらなら弾発射
			if( length < skAttakingRange && dot > skCos60 ){
				mElapsedTimeAfterLunch+=elapsedTime;		
				if( mElapsedTimeAfterLunch > skCoolTime ){
					for( int i=0; i< NumberBullets; ++i ){
						if(!mBullets[i]->isInWorld()){
							dir.setY(0.f);
							mBullets[i]->lunch( trans,  skBulletSpeed*dir );
							mElapsedTimeAfterLunch = 0.f;
							break;
						}
					}
				}
			} else {
				mElapsedTimeAfterLunch = 0.f;
			}

			float accelSpeed = 50.f;
			//mRigidBody->applyCentralImpulse( dir*mMass*accelSpeed );
		}

		btVector3 velocity = mRigidBody->getLinearVelocity();
		btScalar speed = velocity.length();
		float maxSpeed = 200.f;
		if(speed > maxSpeed) {
			velocity *= maxSpeed/speed;
			mRigidBody->setLinearVelocity(velocity);
		}
	}
}
void Enemy::onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ) {
	IRigidBody::onCollisionEnter( manifold, me, obj );		
	if( isDied() )
	{
		if(mElapsedTimeSinceDeath==0.f){
			//sendEvent
			mElapsedTimeSinceDeath = (std::numeric_limits<float>::min)();
			
			//死んだら回転するようにする
			btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
			mShape->calculateLocalInertia( mMass, btv3LocalInertia );
			mRigidBody->setMassProps( mMass, btv3LocalInertia );
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
		mModel->setCanDraw(false);
	}
}

//shared_from_this()を使いたいので
void Enemy::initBullet(){
	for( int i=0; i<NumberBullets; ++i ){
		IColliderSharedPtr me = std::dynamic_pointer_cast<ICollider>(shared_from_this());
		assert(me);
		mBullets[i] = Bullet::createForEnemy( btTransform::getIdentity(), btVector3(0.f,0.f,0.f), 5.f, me );
		mBullets[i]->copyWeaponStatus( mWeaponStatus );
	}
}


}