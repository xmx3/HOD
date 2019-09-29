#include"Player.h"
#include"PlayerUtils/Updater/Parent.h"

#include"Enemy.h"

#include<d3dx9.h>


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

//#include"GameObject/Bullet.h"
#include"GameObject/Accessory.h"

//#include"Camera/PlayerCamera.h"
//#include"Camera/Simple.h"
#include"Camera/HodCamera.h"


#include"Input/PlayerMouse.h"

#include"GameObject/HelperFunc.h"
#include"GameObject/XmlFiles.h"

#include"GameObjectData/Status.h"

#include"GUI/Manager.h"
#include"GUI/Label.h"

#include"XmlLoader/MME/Object/ModelKai.h"
#include"XmlLoader/Actions.h"

#include"helper/ClickPos.h"
#include"helper/PrimitiveDrawer.h"
#include"helper/PrintBtVector3.h"
#include"SegaTypeHelper.h"

#include"MME/Drawer/GameDrawer.h"

#include"BulletPhysics/OnGroundChecker.h"

#include"limitMovableArea.h"

#include"Frustrum.h"

#include"GameObject/Utils/Character.h"
#include"MMD/CameraAnimation.h"

#include"Component/RigidBodyComponent.h"

#include"GameObjectData/WeaponStatus.h"

namespace {
//敵から近い距離
static const float kCloseDistanceFromEnemy = 20.f;

struct   MyContactResultCallback : public btCollisionWorld::ContactResultCallback
{
	bool m_connected;
	MyContactResultCallback() :m_connected(false)
	{
	}

	virtual   btScalar   addSingleResult(
		btManifoldPoint& cp,
		const btCollisionObjectWrapper* colObj0,
		int partId0,
		int index0,
		const btCollisionObjectWrapper* colObj1,
		int partId1,
		int index1 )
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
	cb.m_collisionFilterMask = BulletPhysics::EnemyFilter;
		
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
	cb.m_collisionFilterMask = BulletPhysics::EnemyFilter;
		
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

}//end namespace anonymous

namespace GameObject{

RTTI_IMPL( Player, BaseObject);

std::shared_ptr<Player> Player::create(
	float height,
	MME::Object::ModelKaiSharedPtr model,
	BtCylinderShapeSharedPtr shape,
	BtMotionStateSharedPtr motionState,
	BtRigidBodySharedPtr rigidbody,
	Camera::ICameraSharedPtr camera,
	Input::PlayerMouseSharedPtr mouse,
	GameObjectData::StatusSharedPtr status
) {
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->init(
		height,
		model,
		shape,
		motionState,
		std::move(rigidbody),
		camera,
		mouse,
		status);
	return player;
}

std::shared_ptr<Player> Player::create(
	Utils::CharacterSharedPtr character,
	GameObjectData::StatusSharedPtr status) {


	std::shared_ptr<btCylinderShape> cylinder = std::dynamic_pointer_cast<btCylinderShape>(character->getShape());
	assert(cylinder);

	//rigidbodyの作成
	// 慣性テンソルの計算
	//回転しない
	btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
	//mShape->calculateLocalInertia( mMass, btv3LocalInertia );

	//static const btVector3 kDefalutInitPos( 0.f, 20.f, 0.f );
	static const btVector3 kDefalutInitPos(-80.f, 55.f, 0.f);

	// MotionStateを作成する。剛体の姿勢制御をするもの	
	std::shared_ptr<btDefaultMotionState> pMotionState =
		std::make_shared<btDefaultMotionState>(btTransform(btMatrix3x3::getIdentity(), kDefalutInitPos));

	// 剛体を作成する
	btRigidBody::btRigidBodyConstructionInfo rbInfo(character->getMass(), pMotionState.get(), cylinder.get(), btv3LocalInertia);
	//mRigidBody = std::make_shared<btRigidBody>( rbInfo );//bugります,原因はたぶんalign
	std::unique_ptr<btRigidBody> pRigidBody(new btRigidBody(rbInfo));

	//Mouseの作成
	std::shared_ptr<Input::PlayerMouse> pMouse =
		std::make_shared<Input::PlayerMouse>(pRigidBody.get(), character->getHeight()*0.5f);

	//PlayerCameraの作成
	//std::shared_ptr<::Camera::PlayerCamera> pCamera =
	//	mCamera->instance(pRigidBody.get(), pMouse.get());
	//std::shared_ptr<::Camera::ICamera> pICamera =
	//	std::dynamic_pointer_cast<::Camera::ICamera, ::Camera::PlayerCamera>(pCamera);

	//とりあえずの処理
	//カメラをどこに置くかも考えなきゃ
	::MMD::CameraAnimationSharedPtr animCamera = std::make_shared<::MMD::CameraAnimation>();
	//animCamera->load("Data/MMDData/vmd/camera_simple.vmd");
	//animCamera->load("Data/MMDData/vmd/camera_test.vmd");

	while (!animCamera->isReady()) {}
	auto pCamera = std::make_shared<::Camera::HodCamera>(std::move(animCamera));
	std::shared_ptr<::Camera::ICamera> pICamera =
		std::dynamic_pointer_cast<::Camera::ICamera, ::Camera::HodCamera>(pCamera);

	assert(pICamera);



	//FixedCameraの作成
	//GameLib::Framework framework;
	//auto pCamera = std::make_shared<::Camera::FixedCamera>(
	//	D3DXVECTOR3(0.f, 70.f, 40.f),
	//	D3DXVECTOR3(0.f, 55.f, 0.f),
	//	D3DXVECTOR3(0.f, 1.f, 0.f),
	//	45.f,
	//	0.1f,
	//	30000.f);
	//std::shared_ptr<::Camera::ICamera> pICamera =
	//	std::dynamic_pointer_cast<::Camera::ICamera, ::Camera::FixedCamera>(pCamera);
	//
	//assert(pICamera);


	auto player = create(
		character->getHeight(),
		character->getModel(),
		cylinder,
		pMotionState,
		std::move(pRigidBody),
		pICamera,
		pMouse,
		status);
	player->mCharacter=character;
	return player;


}




Player::Player()
	:mModel(nullptr),
	mHeight(0.f),
	mCamera(nullptr),
	mElapsedTime(0.f),
	mMouse(nullptr),
	mHpBar(nullptr),
	mHpBackGroundBar(nullptr),
	mUpdater(nullptr),
	mOnGroundChecker(nullptr),
	mRigidBodyComponent(nullptr)
{
	mHpBar = new GUI::Label( 0, 0, 0, 0, 0 );
	mHpBackGroundBar = new GUI::Label( 0, 0, 0, 0, 0 );
	GUI::Manager::instance()->add( mHpBackGroundBar );
	GUI::Manager::instance()->add( mHpBar );

	mFilterGroup = BulletPhysics::DefaultFilter;
	mFilterMask = BulletPhysics::AllFilterExceptMMDObject;

}

void Player::release(){
	SAFE_DELETE( mOnGroundChecker );
	SAFE_DELETE( mUpdater );
	SAFE_DELETE( mHpBackGroundBar );
	SAFE_DELETE( mHpBar );
	mMouse.reset();
	removeFromWorld();
	mCamera.reset();
	mRigidBodyComponent.reset();
}

Player::~Player(){
	release();
}



void Player::drawHUD() const {
	
	//btVector3 p = mRigidBody->getWorldTransform().getOrigin();
	//btVector3 center;
	//float radius;
	//mCylinder->getBoundingSphere( center, radius );
	//PrimitiveDrawer::drawSphere( p+center, radius );

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

	//hpbar
	{
		unsigned int hpColor = 0xff88ccff;
		unsigned int hpBgColor = 0xff406080;
		
		GameLib::Vector4 pos( mRigidBodyComponent->getWorldTransform().getOrigin() );
		
		drawHpBar( 
			mHpBar, mHpBackGroundBar,
			pos,
			mStatus->hp.rate(),
			hpColor,
			hpBgColor );

	}

	
	GameLib::DebugScreen ds;
	ds.setPosition( 0, 0);
	ds.precision( 5 );
	ds << "HP: " << mStatus->hp <<GameLib::endl;
	//ds << "stamina: " << mStatus->stamina << GameLib::endl;
	//const btVector3 pos = mRigidBodyComponent->getWorldTransform().getOrigin();	
	//ds << "pos( " <<
		//pos.x() << ", " <<
		//pos.y() << ", " <<
		//pos.z() << " )" << GameLib::endl;;
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
	const btTransform &world = mRigidBodyComponent->getWorldTransform();

	mModel->update( toDxMatrix(world), mElapsedTime );//表示を物理適用後にするためここでupdate
	
	using namespace GameLib::Graphics;
	//GameLib::Graphics::Manager gm;
	//gm.setLightingMode(LIGHTING_NONE);
	//mModel->debugDraw();
	//BulletPhysics::Manager::drawObject( mRigidBody.get() );
}


void Player::update( float elapsedTime ){

	//GameLib::Input::Keyboard k;

	mCamera->update(elapsedTime);

	mOnGroundChecker->update();
	
	//視錐台の中で移動制限
	{
		auto camera = dynamic_cast<Camera::HodCamera*>(mCamera.get());
		assert(camera);

		const D3DXMATRIX &viewproj = camera->getViewProj();

		D3DXVECTOR3 closestPoint;
		auto &pos = mRigidBodyComponent->getWorldTransform().getOrigin();
		auto dxPos = toDxVec3(pos);

		Frustrum frustrum(viewproj);
		bool isInside = frustrum.calculateClosestPoint(&closestPoint, nullptr, dxPos);
		if (!isInside) {
			pos.setX(closestPoint.x);
			pos.setZ(closestPoint.z);
		}
	}

	mUpdater->update( elapsedTime );

	mMouse->update(elapsedTime);
	mElapsedTime=elapsedTime;

}

void Player::onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ){
	auto rb = static_cast<Component::RigidBodyComponent*>(obj->getUserPointer());
	const RTTI &rtti = rb->getOwner()->getRTTI();
	if (rtti.isExactly(Rttis::Enemy())) {
		Enemy* enemy = dynamic_cast<Enemy*>(rb->getOwner());
		if (enemy && !enemy->isDied()) {
			mStatus->hp.add(-1000);
		}
	}
}

void Player::onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ){
	auto rb = static_cast<Component::RigidBodyComponent*>(obj->getUserPointer());
	const RTTI &rtti = rb->getOwner()->getRTTI();
	if (rtti.isExactly(Rttis::Enemy())) {
		Enemy* enemy = dynamic_cast<Enemy*>(rb->getOwner());
		if (enemy && !enemy->isDied()) {
			mStatus->hp.add(-10);
		}
	}
	//ICollider *gameObj = static_cast<ICollider*>( obj->getUserPointer() );
	//mUpdater->onCollisionEnter( manifold, me, obj );
}

void Player::onCollisionExit(btCollisionObject *me, btCollisionObject *obj) {}


void Player::removeFromWorld(){
	mModel->removeFromWorld();
	mRigidBodyComponent->removeFromWorld();
	MME::Drawer::GameDrawer::instance()->remove(mModel);


}

void Player::addToWorld(){	
	mModel->addToWorld();
	mRigidBodyComponent->addToWorld(mFilterGroup, mFilterMask);
	MME::Drawer::GameDrawer::instance()->add(mModel);
}


btVector3 Player::getMousePos()const{
	return mMouse->getPos();
}


bool Player::onGround()const {
	return mOnGroundChecker->isOnGround();
}


void Player::init(
	float height,
	MME::Object::ModelKaiSharedPtr model,
	BtCylinderShapeSharedPtr shape,
	BtMotionStateSharedPtr motionState,
	BtRigidBodySharedPtr rigidbody,
	Camera::ICameraSharedPtr camera,
	Input::PlayerMouseSharedPtr mouse,
	GameObjectData::StatusSharedPtr status)
{
	if (
		mModel ||
		mRigidBodyComponent ||
		mMouse ||
		mStatus)
	{
		assert(false && "it has already allocated.");
		return;
	}

	
	mRigidBodyComponent =
		Component::RigidBodyComponent::create(
			this,
			shape,
			motionState,
			rigidbody );
	auto func = std::bind(&Player::onCollisionEnter, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	mRigidBodyComponent->getOnEnterCallback().add(func);

	auto func1 = std::bind(&Player::onCollisionStay, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	mRigidBodyComponent->getOnStayCallback().add(func1);


	mHeight = height;
	mModel = model;
	mCamera = camera;
	mMouse = mouse;
	mStatus = status;
	
	
	addToWorld();

	{
		XmlLoader::Actions actions;
		actions.loadStart("Data/XmlLoader/Actions/doubleNegis.xml");
		while (!actions.isReady()) {}
		actions.instance(mModel.get(), rigidbody.get(), mStatus);
	}
	{
		XmlLoader::Actions actions;
		actions.loadStart("Data/XmlLoader/Actions/nyoibou.xml");
		while (!actions.isReady()) {}
		actions.instance(mModel.get(), rigidbody.get(), mStatus);
	}

	//modelの初期位置
	const btTransform &world = mRigidBodyComponent->getWorldTransform();

	mModel->init(toDxMatrix(world), "stand");
	mUpdater = new PlayerUtils::Updater::Parent(this);

	GameObjectData::WeaponStatus weaponTemplate;
	GameLib::FileIO::InFile f = GameLib::FileIO::InFile::create("Data/GameObjectData/Weapon/baseWeapon.xml");
	while (!f.isFinished()) {}
	weaponTemplate.loadXMLFromArchive(f);
	weaponTemplate.me = mStatus;


	mOnGroundChecker = new BulletPhysics::OnGroundChecker(rigidbody.get());


}

void Player::addActions(XmlLoader::Actions* actions) {
	while (!actions->isReady()) {}
	actions->instance( mModel.get(), mRigidBodyComponent->getRigidBody().get(), mStatus);
}

btCollisionObject * Player::getBtCollisionObject()
{
	return mRigidBodyComponent->getBtCollisionObject();
}



void Player::takeDamage(BaseObject * DamageCauser)
{
	TRACE("Player::takeDamage()あとで実装\n");
}

int Player::calculateDamage()
{
	assert(false&& "ここをとおることはないはず");
	return 0;
}

bool Player::canDamage()
{
	return false;
}

const GameObjectData::WeaponStatus * Player::getWeaponStatus()
{
	return nullptr;
}


} //GameObject::Player
