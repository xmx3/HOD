#include"Player.h"
#include"CharacterControllerRigidBody.h"


#include<d3dx9.h>
#include<boost/lexical_cast.hpp>
#include<tchar.h>
#include<new>


#include"MME/Object/ModelKai.h"
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"BulletPhysics/Manager.h"

#include<GameLib/GameLib.h>

#include<GameLib/Math/Vector3.h>

#include<GameLib/Framework.h>

#include<GameLib/FileIO/InFile.h>
#include<GameLib/FileIO/Manager.h>

#include<GameLib/Input/Keyboard.h>
#include<GameLib/Input/Mouse.h>

#include<GameLib/PseudoXml/Document.h>
#include<GameLib/PseudoXml/Element.h>
#include<GameLib/PseudoXml/Attribute.h>
#include<GameLib/Base/RefString.h>

#include"GameObject/Bullet.h"
#include"GameObject/Accessory.h"
#include"Camera/PlayerCamera.h"
//#include"Camera/SpringCameraWithoutYAxisEx.h"
#include"Input/PlayerMouse.h"

#include"GameObject/OldPlayer/Updater/IUpdater.h"
#include"GameObject/OldPlayer/Updater/QuarterView/StandUpdater.h"
#include"GameObject/OldPlayer/Updater/QuarterView/RunUpdater.h"
#include"GameObject/OldPlayer/Updater/QuarterView/JumpUpdater.h"
#include"GameObject/OldPlayer/Updater/QuarterView/SwingUpdater.h"
#include"GameObject/OldPlayer/Updater/TPS/StandUpdater.h"
#include"GameObject/OldPlayer/Updater/TPS/RunUpdater.h"
#include"GameObject/OldPlayer/Updater/TPS/StepUpdater.h"
#include"GameObject/OldPlayer/Updater/TPS/SwingUpdater.h"
#include"GameObject/OldPlayer/Updater/Car/StandUpdater.h"
#include"GameObject/OldPlayer/Updater/Car/RunUpdater.h"


#include"GameObject/HelperFunc.h"
#include"GameObject/XmlFiles.h"


#include"GameObjectData/Status.h"
#include"GameObjectData/WeaponStatus.h"


#include"GUI/Manager.h"
#include"GUI/Label.h"

#include"Serialization/MME/Object/ModelKai.h"
#include"Serialization/Actions.h"

#include"helper/ClickPos.h"
#include"helper/PrimitiveDrawer.h"
#include"helper/PrintBtVector3.h"
#include"SegaTypeHelper.h"

//#include<string>
//extern std::vector<GameObject::SptrEnemy> gEnemies;



namespace {
//敵から近い距離
static const float kCloseDistanceFromEnemy = 20.f;

struct   MyContactResultCallback : public btCollisionWorld::ContactResultCallback
{
	bool m_connected;
	MyContactResultCallback() :m_connected(false)
	{
	}
	virtual   btScalar   addSingleResult(btManifoldPoint& cp,   const btCollisionObject* colObj0,int partId0,int index0,const btCollisionObject* colObj1,int partId1,int index1)
	{
		if (cp.getDistance()<=0)
			m_connected = true;
		return 1.f;
	}
};


bool isThereEnemy( const btVector3 &pos, float radius=0.1f ){
	//Enemyがいるか
	bool isThereEnemy = false;
	
	//実装方法いろいろある
	//vector<Enemy*>をどこかで管理しといて、線形探索もあり
	//rayを世界に飛ばす
	//今回はcontactTest

	btSphereShape sphere(radius);
	btCollisionObject col;
	col.setCollisionShape( &sphere );
	col.setWorldTransform( btTransform( btMatrix3x3::getIdentity(), pos ) );
	 
	MyContactResultCallback cb;
	//Enemyのみ当たり判定ありのmask
	cb.m_collisionFilterMask = BulletPhysics::Manager::EnemyFilter;
		
	BulletPhysics::Manager::instance()->getWorldPtr()->contactTest( &col, cb );

	if (cb.m_connected)
	{
		isThereEnemy= true;
	}
	return isThereEnemy;

}

bool isThereEnemy( const btVector3 &start, const btVector3 &end, float radius=0.1f ){
	//Enemyがいるか
	bool isThereEnemy = false;
	
	//実装方法いろいろある
	//vector<Enemy*>をどこかで管理しといて、線形探索もあり
	//今夏はrayを世界に飛ばす

	btSphereShape sphere(radius);
	

	//始点と終点
	btTransform bttr( btMatrix3x3::getIdentity(), start );
	btTransform bttr1( btMatrix3x3::getIdentity(), end );
	 
	btCollisionWorld::ClosestConvexResultCallback cb( start,  end );
	//Enemyのみ当たり判定ありのmask
	cb.m_collisionFilterMask = BulletPhysics::Manager::EnemyFilter;
		
	BulletPhysics::Manager::instance()->getWorldPtr()->convexSweepTest( &sphere, bttr, bttr1, cb );

	if (cb.hasHit())
	{
		isThereEnemy= true;
	}
	return isThereEnemy;

}





//vector<Enemy*> gEnemiesを利用、線形探索だから遅いかも
//bool isThereEnemy1( const btVector3 &pos , float radius=0.1f ){
//	
//	btSphereShape sphere(radius);
//
//	btCollisionObject obj;
//	obj.setWorldTransform( btTransform( btMatrix3x3::getIdentity(), pos ) );
//	obj.setCollisionShape( &sphere );
//	
//	//実験
//	//btSphereShape sphere1(radius);
//
//	//btCollisionObject obj1;
//	//btVector3 pos1(pos);
//	//pos1.setY( 10000 );
//	//obj1.setWorldTransform( btTransform( btMatrix3x3::getIdentity(), pos1 ) );
//	//obj1.setCollisionShape( &sphere1 );
//
//	MyContactResultCallback cb;
//	//Enemyのみ当たり判定ありのmask
//	//contactPairTestこのパラメータ使ってない
//	cb.m_collisionFilterMask = BulletPhysics::Manager::EnemyFilter;
//
//	BOOST_FOREACH( GameObject::SptrEnemy e, gEnemies ){
//		BulletPhysics::Manager::instance()->getWorldPtr()->contactPairTest( &obj, e->getBtCollisionObject(), cb );
//		if ( cb.m_connected )
//		{
//			return true;
//		}
//	}
//
//	return false;
//}

bool onSphere( btCollisionObject* miku, const btVector3 &spherePos , float radius=0.1f){
	
	btSphereShape sphere(radius);

	btCollisionObject obj;
	obj.setWorldTransform( btTransform( btMatrix3x3::getIdentity(), spherePos ) );
	obj.setCollisionShape( &sphere );
	
	MyContactResultCallback cb;
	//cb.m_collisionFilterMask = BulletPhysics::Manager::EnemyFilter;

	BulletPhysics::Manager::instance()->getWorldPtr()->contactPairTest( &obj, miku, cb );
	if ( cb.m_connected )
	{
		return true;
	}

	return false;
}

static const btVector3 kDefalutInitPos( 0.f, 60.f, 0.f );
static const int kMaxPhase=10;
static const float kBulletRadius=5.f;
using namespace GameLib::PseudoXml;
ConstElement findElement( const Document &d, const char *findElementName ){
	const ConstElement &root = d.root();
	int numChild = root.childNumber();
	for( int i=0; i<numChild; ++i ){
		if( GameLib::RefString(root.child(i).name()) == findElementName ){
			return root.child(i);
		}
	}
	std::string message(findElementName);
	message.append( " didn't found!" );
	STRONG_ASSERT( false && message.c_str() );

	//空っぽを返す
	return ConstElement(); 
}

const char* getVMDFileName( ConstElement &elem ){
	int num=elem.attributeNumber();
	for( int i=0; i<num; ++i ){
		if( GameLib::RefString("vmdFile") == elem.attribute(i).name() ){
			return elem.attribute(i).value();
		}

	}
	STRONG_ASSERT( false && "vmdFile Attribute didn't find!" );

	return NULL;
}

//エラーが起きたらfalseを返す
bool setBool(bool *out, const ConstAttribute &a ){
	GameLib::RefString str( a.value() );
	if( str == "true" ){
		*out=true;
		return true;
	} else if( str == "false" ){
		*out=false;
		return true;
	} else {
		return false;
	}
}

}//end namespace anonymous

namespace GameObject{
namespace OldPlayer {


void Player::load(){
	if(mModel){
		assert(false && "it has already allocated.");
		return;
	}
	using GameLib::Math::Vector3;
	using namespace GameLib::FileIO;
	using namespace GameLib::PseudoXml;
	using GameLib::RefString;

	GameLib::FileIO::InFile xmlFile;
	xmlFile= GameLib::FileIO::InFile::create( "Data/GameObjectSetting/OldPlayer/init.xml" );
	if( xmlFile.isError() ){
		STRONG_ASSERT(false);
		return;
	}
	while( !xmlFile.isFinished() ){}

	Document mikuXml = Document::create( xmlFile.data(), xmlFile.size() );
	if( mikuXml.isError() ){
		STRONG_ASSERT(false);
		return;
	}

	float	speed=50.f,
			angSpeed=3.14f,
			cameraBackLength=50.f,
			cameraUpLength=100.f,
			cameraTargetForwardLength=10.f;
		
	RefString	statusFileName,
				pmdFile;

	float width=0.f;

	int numChild=mikuXml.childNumber();
	for( int ic=0; ic<numChild; ++ic )
	{
		ConstElement e = mikuXml.child(ic);
		if(RefString("Miku") == e.name() )
		{
			int numAttributes = e.attributeNumber();
			assert( numAttributes==9 );
			for( int ia=0; ia<numAttributes; ++ia )
			{
				ConstAttribute & a = e.attribute(ia);
				const char *attributeName = a.name();
				if( RefString("height") == attributeName ){
					mHeight = a.getFloatValue();
				} else if( RefString("width") == attributeName ){
					width = a.getFloatValue();
				} else if( RefString("speed") == attributeName ){
					speed = a.getFloatValue();
				} else if( RefString("angleSpeed") == attributeName ){
					angSpeed = a.getFloatValue();
				} else if( RefString("cameraBackLength") == attributeName ){
					cameraBackLength = a.getFloatValue();
				} else if( RefString("cameraUpLength") == attributeName ){
					cameraUpLength = a.getFloatValue();
				} else if( RefString("cameraTargetForwardLength") == attributeName ){
					cameraTargetForwardLength = a.getFloatValue();
				} else if( RefString("statusFile") == attributeName ){
					statusFileName = a.value();
				} else if( RefString("mass") == attributeName ){
					mMass = a.getFloatValue();
				} else {
					TRACE1( "this attribute name is wrong! %s\n", attributeName ); 
					STRONG_ASSERT( false );
				}
			}
		}
		else{
			TRACE1( "this element name is wrong! %s", e.name() ); 
			STRONG_ASSERT( false );
		}	
	}

	assert( mHeight>0.f );
	assert( width>0.f );
	mCylinder = std::make_shared<btCylinderShape>( btVector3( width/2.f, mHeight/2.f, width/2.f ) );
	
	assert(mMass!=0.f);
	
	//rigidbodyの作成
	// 慣性テンソルの計算
	//回転しない
	btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
	//mShape->calculateLocalInertia( mMass, btv3LocalInertia );
	
	// MotionStateを作成する。剛体の姿勢制御をするもの	
	btMotionState *pMotionState =
		//new btDefaultMotionState( btTransform::getIdentity() );
		new btDefaultMotionState( btTransform( btMatrix3x3::getIdentity(), kDefalutInitPos ) );

	// 剛体を作成する
	btRigidBody::btRigidBodyConstructionInfo rbInfo( mMass, pMotionState, mCylinder.get(), btv3LocalInertia );
	//mRigidBody = std::make_shared<btRigidBody>( rbInfo );//bugります,原因はたぶんalign
	mRigidBody.reset( new btRigidBody(rbInfo) );
	mRigidBody->setUserPointer( this );

	mController = CharacterControllerRigidBody::create(
		mRigidBody,
		speed,
		angSpeed,
		mMass
	);

	mStatus = GameObjectData::Status::create();
	mBulletWeaponStatus = std::make_shared<GameObjectData::WeaponStatus>( mStatus );
	GameLib::FileIO::InFile statusFile = GameLib::FileIO::InFile::create( statusFileName.get() );
	mStatus->loadTextFromArchive( statusFile );

	mTargetPos = mRigidBody->getWorldTransform().getOrigin();

	mMouse = NEW Input::PlayerMouse( mRigidBody.get(), mHeight*0.5f );

	const btTransform &world = mRigidBody->getWorldTransform();

	mCamera = NEW Camera::PlayerCamera(
		mRigidBody.get(),
		mMouse,
		cameraUpLength,
		cameraBackLength,
		cameraTargetForwardLength,
		mHeight,
		4.f*mHeight,
		mHeight );

	for( int i=0; i<BULLET_SIZE; ++i){
		mBullets[i] = Bullet::create( btTransform::getIdentity(), btVector3( 0.f, 0.f, 0.f ), kBulletRadius, getIColliderSharedPtr() );
		mBullets[i]->setWeaponStatus( mBulletWeaponStatus );
	}

	Serialization::MME::Object::ModelKai model;
	//model.loadStart( "Data/Serialization/Model/metal_miku.xml" );
	model.loadStart( "Data/Serialization/Model/bou.xml" );
	while(!model.isReady());
	
	//modelの作成
	mModel = model.instance();

	GameLib::FileIO::Manager m;
	//std::string str = m.createListString();
	//TRACE1("%s\n", str.c_str() );
	Serialization::Actions actions;
	actions.loadStart("Data/Serialization/Actions/doubleNegis.xml");
	while(!actions.isReady()){}
	actions.instance( mModel.get(), mRigidBody.get(), mStatus );
	//std::string str2 = m.createListString();
	//TRACE1("%s\n", str2.c_str() );
	
	//boost::timer t; // タイマーの開始
	//using boost::lexical_cast;
	//mModel->loadXML( XmlFiles::gskPlayer, getBtCollisionObject(), mStatus );

	//OutputDebugStringA( "model load: " );
	//OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
	//OutputDebugStringA( "\n" );
	//t.restart();

	//modelの初期位置
	mModel->init( toDxMatrix(world), "stand" );
				
	mUpdater = Updater::QuarterView::StandUpdater::create( this );
	mOldUpdater = mUpdater;
}

RTTI_IMPL( Player, ICollider );

std::shared_ptr<Player> create(){
	return Player::create();
}


Player::Player()
	:mModel(NULL),
	mHeight(0.f),
	mMass(0.f),
	mCamera(NULL),
	mElapsedTime(0.f),
	mBulletWeaponStatus(NULL),
	mIsAttacking(false),
	//mFileLoader(NULL),
	mUpdater(NULL),
	mMouse(NULL),
	mHpBar(NULL),
	mHpBackGroundBar(NULL)
{
	mHpBar = new GUI::Label( 0, 0, 0, 0, 0 );
	mHpBackGroundBar = new GUI::Label( 0, 0, 0, 0, 0 );
	GUI::Manager::instance()->add( mHpBackGroundBar );
	GUI::Manager::instance()->add( mHpBar );
	//assert( Rttis::Player().isExactly( Player::rtti ) );

}

void Player::release(){
	SAFE_DELETE( mHpBackGroundBar );
	SAFE_DELETE( mHpBar );
	SAFE_DELETE( mCamera );
	SAFE_DELETE( mMouse );
	removeFromWorld();
	mController.reset();
	btMotionState *m = mRigidBody->getMotionState();
	SAFE_DELETE(m);
	mRigidBody.reset();

}

Player::~Player(){
	release();
}



void Player::drawHUD() const {
	
	using namespace GameLib::Graphics;

	//透明度関係あるから描画順序考えたほうがいい
	//gm.setCullMode(CULL_NONE);
	if( mMouse->onPlayer() ){
		mMouse->drawMousePos( 0x8800ff00 );
	} else if( mMouse->onObject() ){
		mMouse->drawMousePos( 0x88ff0000 );
	}
	else {
		mMouse->drawMousePos( 0x88ffffff );
	}

	if( mIsAttacking ){
		PrimitiveDrawer::drawSphere( mTargetPos, 1.f, 0x88ff0000 );
	} else {
		PrimitiveDrawer::drawSphere( mTargetPos, 1.0f, 0x880000ff );	
	}


	
	//hpbar
	{
		unsigned int hpColor = 0xff88ccff;
		unsigned int hpBgColor = 0xff406080;
		
		GameLib::Vector4 pos( mRigidBody->getWorldTransform().getOrigin() );
		
		drawHpBar( 
			mHpBar, mHpBackGroundBar,
			pos,
			mStatus->hp/mStatus->maxHp,
			hpColor,
			hpBgColor );

	}


	GameLib::DebugScreen ds;
	ds.setPosition( 0, 0);
	ds.precision( 5 );
	ds << "HP: " << mStatus->hp <<GameLib::endl;
	ds << "stamina: " << mStatus->stamina << GameLib::endl; 
	ds << "onGround : " << mController->onGround() <<  GameLib::endl;
	ds << "chang camera when pushing c." <<GameLib::endl;

}

void Player::preDraw() const {
	
	//ここでmodelをアップデートするのはbulletPhysicsをアップデートしたあと(物理更新後)のmControlllerのworldが欲しいため
	//だけど、ボーンを使用するオブジェクトの表示は一つ遅れるんだよね
	//物理更新 この時点のボーンを参照する mController更新
	//↓
	//modelとbone update()
	//↓
	//boneObject.draw();//一つ遅れる
	//でも,この仕様でいい
	//modelとcontrollerが一致表示するのが重要
	//当たり判定は表示としては遅れるが、物理世界では遅れてない
	const btTransform &world = mRigidBody->getWorldTransform();

	mModel->update( toDxMatrix(world), mElapsedTime );//表示を物理適用後にするためここでupdate
	
	using namespace GameLib::Graphics;
	//GameLib::Graphics::Manager gm;
	//gm.setLightingMode(LIGHTING_NONE);
	//mModel->debugDraw();
	//BulletPhysics::Manager::drawObject( mRigidBody.get() );

	int numInWorld=0;
	for(int i=0; i<BULLET_SIZE; ++i ){
		if(mBullets[i]->isInWorld()){
			++numInWorld;
		}
		mBullets[i]->draw();
	}
}



void Player::update( float elapsedTime ){
	
	//GraphicManagerにパラメター送りたいから一番最初に更新
	mCamera->update( elapsedTime );

	mMouse->update(elapsedTime);
	mElapsedTime=elapsedTime;
	//GameLib::Input::Keyboard k;
	
	mUpdater->update( elapsedTime );

	GameLib::Input::Mouse mouse;
	if( mouse.isTriggered( mouse.BUTTON_LEFT ) ) {
		mTargetPos = mMouse->getPos();
	}

	for(int i=0; i<BULLET_SIZE; ++i ){
		mBullets[i]->update(elapsedTime);
	}


	mController->update( elapsedTime );
	
}

void Player::fire() {
	for(int i=0; i<BULLET_SIZE; ++i ){
		if( !mBullets[i]->isInWorld() ){
			const btTransform &world = mRigidBody->getWorldTransform();
			mBullets[i]->setWorldTransform( world );
			
			//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
			btVector3 backward = world.getBasis()[2];
			backward.setX(-backward.x());
			backward.normalize ();

			btVector3 forward = -backward;
			
			//btVector3 vel = mTargetPos - world.getOrigin();
			//vel.safeNormalize();
			
			float activeTime = 30.f/30.f;
			mBullets[i]->setActivationTime(activeTime);

			float bulletSpeed=150.f;
			//mBullets[i]->setLinerVelocity( vel*bulletSpeed );
			mBullets[i]->setLinerVelocity( forward*bulletSpeed );
			mBullets[i]->addToWorld();
			return;
		}
	}
}

void Player::checkLeftClick(){
	using GameLib::Input::Mouse;
	GameLib::Input::Mouse mouse;
	if( mouse.isTriggered( Mouse::BUTTON_RIGHT ) ) {
		mController->forceJump();
		fire();
		mModel->changeAnimation( "punch" );
	}
	int x,y;
	const float moveValue = mHeight*2;

	if( mMouse->isFlickedPlayer( &x, &y ) ){
		if(x>0){
			const btTransform &world = mRigidBody->getWorldTransform();
			
			//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
			btVector3 backward = world.getBasis()[2];
			backward.setX(-backward.x());
			backward.normalize ();

			btVector3 forward = -backward;
			//btVector3 upDir = world.getBasis()[1];
			btVector3 strafeDir = world.getBasis()[0];

			//upDir.normalize();
			strafeDir.normalize();

			mController->strafe( world.getOrigin()+strafeDir*moveValue );
			mTargetPos = world.getOrigin()+strafeDir*mHeight;
//#ifndef NOT_LOAD_MMD
//			mModel->changeAnimation( mRunAnim );
//#endif
		} else if( x<0 ){
			const btTransform &world = mRigidBody->getWorldTransform();
			
			//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
			btVector3 backward = world.getBasis()[2];
			backward.setX(-backward.x());
			backward.normalize ();

			btVector3 forward = -backward;
			//btVector3 upDir = world.getBasis()[1];
			btVector3 strafeDir = world.getBasis()[0];

			//upDir.normalize();
			strafeDir.normalize();

			mController->strafe( world.getOrigin()-strafeDir*moveValue );
			mTargetPos = world.getOrigin()-strafeDir*mHeight;
//#ifndef NOT_LOAD_MMD
//			mModel->changeAnimation( mRunAnim );
//#endif
		}
		
		return;
	}

	if( mouse.isTriggered( Mouse::BUTTON_LEFT ) ) {
		//クリックした場所にEnemyがいるか
		if( mMouse->onObject() ) {
			IColliderSharedPtr obj = mMouse->getOnObject();
			if( obj->getRTTI().isExactly( Rttis::Enemy() ) ){

				TRACE( _T("click enemy!\n") );
				//mController->look( mMouse->getPos() );
				//mTargetPos = mMouse->getPos();
				//mIsAttacking = true;

				btVector3 vel = mMouse->getPos() - getWorldTransform().getOrigin();
				float distance = vel.length();
				float nearRange = 50.f;
				float longRange = 100.f;
			
#ifndef NOT_LOAD_MMD
					//mModel->changeAnimation( mRunAnim );
#endif

				//近距離
				if( distance < nearRange ){
					mController->move( mMouse->getPos() );
					mTargetPos = mMouse->getPos();
#ifndef NOT_LOAD_MMD
					mModel->changeAnimation( "run" );
#endif
					//十分近い場合はもう振る
					if( distance < kCloseDistanceFromEnemy ){
						mController->look( mTargetPos );
#ifndef NOT_LOAD_MMD
						mModel->changeAnimation( "punch" );
#endif
					} 
				}
				//遠距離
				else if( distance < longRange ){
					mController->look( mMouse->getPos() );
					mTargetPos = mMouse->getPos();
					mIsAttacking = true;
#ifndef NOT_LOAD_MMD
					mModel->changeAnimation( "stand" );
#endif
				}
				//レンジ外
				else {
				}
			}
		}
		//敵がいない場合は移動
		else {
			mController->move( mMouse->getPos() );
			mTargetPos = mMouse->getPos();
#ifndef NOT_LOAD_MMD
			if( mController->onGround() ){
				mModel->changeAnimation( "run" );
			}
#endif
		}
	}
}


void Player::onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ){
	ICollider *gameObj = static_cast<ICollider*>( obj->getUserPointer() );

	mUpdater->onCollisionEnter( manifold, me, obj );
}

btCollisionObject* Player::getBtCollisionObject(){
	return mRigidBody.get();
}

void Player::removeFromWorld(){
	mController->removeFromWorld();
}

void Player::addToWorld(){
	mController->addToWorld();
}

void Player::hitback( const btVector3 & dir ){
	mController->stop();
	static const float hitbackLength = 3.f;
	mController->strafe( getWorldTransform().getOrigin()+dir );
	//mController->hitback(impulse);
}

bool Player::changeUpdater( const Updater::State &state ){
	switch(state){
	case Updater::QV_STAND :
		mOldUpdater=mUpdater;
		mUpdater = Updater::QuarterView::StandUpdater::create( this );
		return true;
	case Updater::QV_RUN :
		if( mStatus->canRun( mElapsedTime ) ){
			mOldUpdater=mUpdater;
			mUpdater = Updater::QuarterView::RunUpdater::create( this );
			return true;
		} else {
			return false;
		}
	case Updater::QV_JUMP :
		if( mStatus->canJump() ){
			mOldUpdater=mUpdater;
			mUpdater = Updater::QuarterView::JumpUpdater::create( this );
			return true;
		} else {
			return false;
		}
	case Updater::QV_SWING :
		if(true){ //if( mStatus->canSwing() ){
			mOldUpdater=mUpdater;
			mUpdater = Updater::QuarterView::SwingUpdater::create( this );
			return true;
		} else {
			return false;
		}
	case Updater::TPS_STAND :
		mOldUpdater=mUpdater;
		mUpdater = Updater::TPS::StandUpdater::create( this );
		return true;
	case Updater::TPS_RUN :
		if( mStatus->canWalk( mElapsedTime ) ){
			mOldUpdater=mUpdater;
			mUpdater = Updater::TPS::RunUpdater::create( this );
			return true;
		} else {
			return false;
		}
	case Updater::TPS_STEP :
		if( mStatus->canRunHighSpeed( mElapsedTime ) ){
			mOldUpdater=mUpdater;
			mUpdater = Updater::TPS::StepUpdater::create( this );
			return true;
		} else {
			return false;
		}
	case Updater::TPS_SWING :
		if( true ){ //if( mStatus->canSwing() ){
			mOldUpdater=mUpdater;
			mUpdater = Updater::TPS::SwingUpdater::create( this );
			return true;
		} else {
			return false;
		}
	case Updater::TPS_SHOT :
		assert(false);
		//mOldUpdater=mUpdater;
		//mUpdater = Updater::TPS::ShotUpdater::create( this );
		return true;
	case Updater::CAR_STAND :
		mOldUpdater=mUpdater;
		mUpdater = Updater::Car::StandUpdater::create( this );
		return true;
	case Updater::CAR_RUN :
		mOldUpdater=mUpdater;
		mUpdater = Updater::Car::RunUpdater::create( this );
		return true;
	
	}
	return false;
}

void Player::move( const btVector3 &pos ){
	mController->move(pos);
}

void Player::moveForward( const float &moveValue ){
	const btTransform &world = mRigidBody->getWorldTransform();

	//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
	btVector3 backward = world.getBasis()[2];
	backward.setX(-backward.x());
	backward.normalize ();

	btVector3 forward = -backward;

	move( world.getOrigin() + moveValue*forward );
}

bool Player::jumpIfHaveEnoughStamina(){
	if( mStatus->canJump() ){
		mController->jump();
		mStatus->jump();
		return true;
	}
	return false;
}

bool Player::forceJumpIfHaveEnoughStamina(){
	if( mStatus->canJump() ){
		mStatus->jump();
		mController->forceJump();
		return true;
	}
	return false;
}

void Player::jump(){
	if( mStatus->canJump() ){
		mController->jump();
	}
}

void Player::jumpLow(){
	mController->jumpLow();
}
void Player::jumpHi(){
	mController->jumpHi();
}
void Player::forceJump(){
	mController->forceJump();
}

void Player::jump(const float &speed){
	mController->jump(speed);
}

void Player::forceJump(const float &speed){
	mController->forceJump(speed);
}

void Player::stop(){
	mController->stop();
}

void Player::cut(){
	mController->cut();
}
void Player::look( const btVector3 & pos ){
	mController->look( pos );
}
void Player::strafe( const btVector3 & pos  ){
	mController->strafe( pos );
}

bool Player::isStopping() const{
	return mController->isStopping();
}
bool Player::isTurning() const{
	return mController->isTurning();
}
bool Player::isMoving() const{
	return mController->isMoving();
}
bool Player::onGround() const{
	return mController->onGround();
}

void Player::changeAnimation( Animation anim ){
	switch(anim){
	case ANIM_STAND :
		mModel->changeAnimation( "stand" );
		break;
	case ANIM_RUN :
		mModel->changeAnimation( "run" );
		break;
	case ANIM_PUNCH :
		mModel->changeAnimation( "punch" );
		break;
	case ANIM_LIE:
		mModel->changeAnimation( "lie" );
		break;
	case ANIM_SWING :
		mModel->changeAnimation( "swing0" );
		break;
	case ANIM_STUMBLE :
		mModel->changeAnimation( "stumble" );
		break;
	}
}

btVector3 Player::getMousePos()const{
	return mMouse->getPos();
}


//
//void Player::StandingUpdater::operator()( Player* player ){
//	player->checkLeftClick();
//}
//
//void Player::RunningUpdater::operator()( Player* player ){
//	if( player->mController->isMoving() ){
//		player->checkLeftClick();
//	} else {
//		player->mStateMachine->process_event( EvArrivedAtTargetPos() );
//#ifndef NOT_LOAD_MMD
//		player->mModel->changeAnimation( player->mStandAnim );
//#endif
//	}
//}
//void Player::ChasingUpdater::operator()( Player* player ){
//	btVector3 dir = player->getWorldTransform().getOrigin() - player->mTargetPos;
//	if( dir.length() < kCloseDistanceFromEnemy ){
//		player->mStateMachine->process_event( EvApproachedEnemy() );
//		player->mController->look( player->mTargetPos );
//#ifndef NOT_LOAD_MMD
//		player->mModel->changeAnimation( player->mPunchAnim );
//#endif
//	} else {
//		player->checkLeftClick();
//	}
//
//}
//void Player::AttackingShortRangeUpdater::operator()( Player* player ){
//	switch( mState ) {
//	case COMBO1 :
//		update1(player);
//		break;
//	case COMBO2 :
//		update2(player);
//		break;
//	case COMBO3 :
//		update3(player);
//		break;
//	default :
//		assert(false);
//		break;
//	}
//#ifndef NOT_LOAD_MMD
//	if( player->mModel->isAnimOver() ){
//		player->mModel->changeAnimation( player->mStandAnim );
//		player->mStateMachine->process_event( EvAttackEnd() );
//	}
//#else
//	TRACE( _T( "updateAttackingShortRange()\n" ) );
//	player->mStateMachine->process_event( EvAttackEnd() );
//#endif
//}
//
//void Player::AttackingShortRangeUpdater::update1( Player* player ){
//	const float kFirstFrame = 15.f;	
//	mEndFrame = kFirstFrame;
//	if( player->mModel->getFrame() > mEndFrame ){
//		if( mIsNext ){		 
//			mState = COMBO2;
//			mIsNext=false;
//			//player->mController->jumpLow();
//		}
//		//終了
//		else {
//			player->mModel->changeAnimation( player->mStandAnim );
//			player->mStateMachine->process_event( EvAttackEnd() );
//		}
//	}	
//	else {
//		GameLib::Input::Mouse m;
//		if( m.isTriggered( m.BUTTON_LEFT ) ){
//			mIsNext=true;
//		}
//	}
//}
//void Player::AttackingShortRangeUpdater::update2( Player* player ){
//	const float kSecondFrame = 55.f;	
//	mEndFrame = kSecondFrame;
//	if( player->mModel->getFrame() > mEndFrame ){
//		if( mIsNext ){		 
//			mState = COMBO3;
//			mIsNext=false;
//			player->mController->jump();
//
//		}
//		//終了
//		else {
//			player->mModel->changeAnimation( player->mStandAnim );
//			player->mStateMachine->process_event( EvAttackEnd() );
//		}
//	}	
//	else {
//		GameLib::Input::Mouse m;
//		if( m.isTriggered( m.BUTTON_LEFT ) ){
//			mIsNext=true;
//		}
//	}
//}
//void Player::AttackingShortRangeUpdater::update3( Player* player ){
//}
//
//
//void Player::AttackingLongRangeUpdater::operator()( Player* player ){
//	if( player->mController->isTurning() ){
//		return;
//	} else {
//		player->fire();
//		player->mIsAttacking=false;
//		player->mStateMachine->process_event( EvAttackEnd() );
//	}
//
//}
//void Player::StumblingUpdater::operator()( Player* player ){
//}
//void Player::LyingUpdater::operator()( Player* player ){
//}
//
//Player::SwingUpdater::SwingUpdater()
//	:mClickedNum(0),
//	mCurrentIdx(0)
//{}
//void Player::SwingUpdater::operator()(Player* p){
//	GameLib::Input::Mouse m;
//
//	if( m.isTriggered( m.BUTTON_LEFT ) ) {
//		++mClickedNum;
//	}
//
//	if( p->mModel->isAnimOver() ){
//		if( mCurrentIdx+1 < mClickedNum && mCurrentIdx+1 < p->mSwingAnims.size() ){
//			++mCurrentIdx;
//			p->mModel->changeAnimation( p->mSwingAnims[mCurrentIdx] );
//		} else {
//			//終了
//			//ここで硬直入れたい
//			p->mModel->changeAnimation( p->mStandAnim );
//			p->mStateMachine->process_event( EvAttackEnd() );
//		}
//	}
//}

std::shared_ptr<Player> Player::create(){
	std::shared_ptr<Player> plyr= std::make_shared<Player>();
	return plyr;
}

//std::shared_ptr<Player> Player::create(
//		MME::Object::ModelKaiSharedPtr model,
//		BtCollisionShapeSharedPtr shape,
//		GameObjectData::StatusSharedPtr status )
//{
//	std::shared_ptr<Player> plyr= std::make_shared<Player>();
//	plyr->mModel = model;
//	BtCylinderShapeSharedPtr cylinder = std::dynamic_pointer_cast<btCylinderShape>(shape);
//	float height = cylinder->getHalfExtentsWithMargin().getY()*2.f;
//	plyr->mHeight=height;
//	plyr->mController = CharacterControllerRigidBody::create(
//		plyr.get(),
//		btTransform(
//			btMatrix3x3::getIdentity(),
//			kDefalutInitPos 
//		) ,
//		cylinder,
//		status->speedWalking,
//		status->angleSpeed
//	);
//
//	plyr->mStatus = status;
//	plyr->mBulletWeaponStatus = std::make_shared<GameObjectData::WeaponStatus>( status );
//
//	plyr->mTargetPos = plyr->mRigidBody->getWorldTransform().getOrigin();
//
//	plyr->mMouse = NEW Input::PlayerMouse( plyr->mRigidBody.get(), height*0.5f );
//
//	const btTransform &world = plyr->mRigidBody->getWorldTransform();
//
//	float	cameraBackLength=50.f,
//			cameraUpLength=100.f,
//			cameraTargetForwardLength=10.f;
//	
//
//	plyr->mCamera = NEW Camera::PlayerCamera(
//		plyr->mRigidBody.get(),
//		plyr->mMouse,
//		cameraUpLength,
//		cameraBackLength,
//		cameraTargetForwardLength,
//		height,
//		4.f*height,
//		height );
//
//	for( int i=0; i<BULLET_SIZE; ++i){
//		plyr->mBullets[i] = Bullet::create( btTransform::getIdentity(), btVector3( 0.f, 0.f, 0.f ), kBulletRadius, plyr->getIColliderSharedPtr() );
//		plyr->mBullets[i]->setWeaponStatus( plyr->mBulletWeaponStatus );
//	}
//
//	//modelの初期位置
//	plyr->mModel->init( world );
//				
//	plyr->mUpdater = Updater::QuarterView::StandUpdater::create( plyr.get() );
//	plyr->mOldUpdater = plyr->mUpdater;	
//	return plyr;
//}


bool Player::useStaminaIfCanRunHigh(){
	if( mStatus->canRunHighSpeed( mElapsedTime ) ){
		mStatus->runHighSpeed( mElapsedTime );
		return true;
	} else {
		return false;
	}
}
bool Player::useStaminaIfCanRun(){
	if( mStatus->canRun( mElapsedTime ) ){
		mStatus->run( mElapsedTime );
		return true;
	} else {
		return false;
	}
}
bool Player::useStaminaIfCanWalk(){
	if( mStatus->canWalk( mElapsedTime ) ){
		mStatus->walk( mElapsedTime );
		return true;
	} else {
		return false;
	}
}

void Player::setMaxSpeed( float speed ){
	mController->setMaxSpeed( speed );
}

void Player::setMaxSpeedLow(){
	mController->setMaxSpeed( mStatus->getSpeedLow() );
}

void Player::setMaxSpeedNormal(){
	mController->setMaxSpeed( mStatus->getSpeed() );
	
}
void Player::setMaxSpeedHigh(){
	mController->setMaxSpeed( mStatus->getSpeedHigh() );
}
void Player::healStamina(){
	mStatus->healStamina( mElapsedTime );
}

	

} //end namespace OldPlayer
} //end namespace GameObject
