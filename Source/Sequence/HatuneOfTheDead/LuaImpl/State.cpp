#include"State.h"

#include<boost/timer.hpp>

#include<d3dx9.h>

#include<GameLib/DebugScreen.h>
#include<GameLib/Framework.h>
#include<GameLib/GameLib.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Math/Matrix34.h>
#include<GameLib/Math/Matrix44.h>
#include<GameLib/Input/Keyboard.h>
#include<GameLib/Input/Manager.h>

#include"BulletPhysics/Manager.h"

#include"Camera/HodCamera.h"

#include"GameObject/Stage.h"
#include"GameObject/Player.h"
#include"GameObject/Enemy.h"

#include"GameObject/Event/Manager.h"
#include"GameObject/Event/EventData/AddToWorld.h"
#include"GameObject/Event/EventData/DefeatedAllEnemy.h"
#include"GameObject/Event/EventData/RemoveFromWorld.h"
#include"GameObject/Event/Listener/AddToWorldListener.h"
#include"GameObject/Event/Listener/RemoveFromWorldListener.h"
#include"GameObject/Event/Listener/DefeatedAllEnemiesListener.h"
#include"GameObject/Event/Listener/KilledEnemyListener.h"

#include"GUI/Manager.h"

#include"HOD/EnemyManager.h"
#include"HOD/EnemySpawner.h"


#include"MME/Manager.h"
#include"MME/Drawer/GameDrawer.h"
#include"MME/Object/PointLight.h"
#include"MME/PostEffect.h"

#include"Lua/LuaHelper.h"

#include"Resource.h"

#include"SegaTypeHelper.h"

#include"XmlLoader/GameObject/Enemy.h"



namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{
namespace{
	void cameraInit(){
		GameLib::Framework fw = GameLib::Framework::instance();

		using namespace GameLib;

		GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
		{

			const GameLib::Vector3 zero( 0.f, 0.f, 0.f );
			const GameLib::Vector3 one( 1.f, 1.f, 1.f );
			gm.setAmbientColor( one );
			gm.setDiffuseColor( one );
			gm.setSpecularColor( one );
			gm.setEmissionColor( one );
			gm.setSpecularSharpness( 1.f );
			gm.setTransparency( 1.f );

			gm.setCullMode( Graphics::CULL_BACK );
			gm.enableDepthWrite( true );
			gm.enableDepthTest( true );

			Matrix34 wm;
			D3DXMATRIX w;
			D3DXMatrixIdentity(&w);
			wm.setIdentity();
			gm.setWorldMatrix(wm);

			gm.setLightingMode( Graphics::LIGHTING_PER_PIXEL );
		}

		//MMEの設定
		//適当に
		{
			MME::Manager *m = MME::Manager::instance();
			//ビュー行列を作ろう
			Vector3 eye( 15.f, 30.f, -30.f );
			//Matrix34 matR;
			//matR.setRotationY( gCount );
			//matR.mul33( &eye, eye );
			Vector3 target( 0.f, 0.f, 0.f );
			Vector3 up( 0.f, 1.f, 0.f );
			bool isRightHandCoordinate = false;
			Matrix34 vm;
			vm.setViewTransformLH(
				eye,
				target, 
				up );
			//透視変換行列
			Matrix44 pm;
			pm.setPerspectiveTransform( 
				30.f, 
				static_cast< float >( fw.width() ),
				static_cast< float >( fw.height() ),
				1.f, 500.f );
			m->setEyePosition( eye );
			Vector3 dir;
			dir.setSub( target, eye );
			dir.normalize();
			m->setEyeDirection( dir );
			Matrix34 world;
			world.setIdentity();
			m->setWorldMatrix( toDxMatrix(world) ); 
			m->setViewMatrix( toDxMatrix( vm ) );
			m->setProjectionMatrix( toDxMatrix( pm ) );

			//材質
			//アンビエントは地味に0.3くらいで
			//Vector4 ambient( 0.3f, 0.3f, 0.3f, 1.f );
			Vector4 ambient( 1.f, 1.f, 1.f, 1.f );
			//後は物体側の特性。あまりじっても仕方ないので固定値で。いろいろいじって結果がどうなるか見てやろう
			Vector4 diffuseColor( 1.f, 1.f, 1.f, 1.f );
			Vector4 specularColor( 1.f, 1.f, 1.f, 1.f );
			//これを変えるとハイライトの鋭さが変わる。小さいほどざらざらした表面というイメージ
			float specularSharpness = 100.f;

			m->setAmbientColor( ambient );
			m->setDiffuseColor( diffuseColor );
			m->setSpecularColor( specularColor );
			m->setSpecularSharpness( specularSharpness );

			//ライト
			using namespace GameLib::Graphics;
			//m->setLightIntensity( 0, 50.f );

			//ライティングの設定をする。
			Vector3 lightPositions[ 4 ];
			float lightIntensities[ 4 ];
			Vector3 lightPos( 20, 200, -20 );
			lightPositions[0] = lightPos ;

			lightIntensities[0] = 50.f;

			//光1光源のみ
			//実装なし
			for ( int i = 1; i < 4; ++i ){
				//まずは位置
				lightPositions[i] = lightPos ;
				//float phase = 90.f * static_cast< float >( i );
				//float t = gCount * 0.025f + phase;
				//lightPositions[ i ].x = 30.f * sin( t ) * sin( t );
				//lightPositions[ i ].y = 30.f * sin( t ) * cos( t );
				//lightPositions[ i ].z = 30.f * cos( t );
				lightIntensities[ i ] = 50.f;
			}
			//光の色は白、赤、緑、青、にしてやろう
			Vector4 lightColors[ 4 ];

			//lightColors[ 0 ].set( 0.8f, 0.8f, 0.8f, 1.f );
			lightColors[ 0 ].set( 1.f, 1.f, 1.f, 1.f );
			lightColors[ 1 ].set( 1.f, 0.f, 0.f, 1.f );
			lightColors[ 2 ].set( 0.f, 1.f, 0.f, 1.f );
			lightColors[ 3 ].set( 0.f, 0.f, 1.f, 1.f );


			//ではライトの情報をセットしてやろう
			for ( int i = 0; i < 4; ++i ){
				Vector4 vOne(1.f);
				Vector4 vZero(0.f);
				Vector4 v08(0.8f);
				Vector4 v05(0.5f);
				m->setLightColor( i, lightColors[ i ] );
				m->setLightPosition( i, lightPositions[i] );
				//dir.setSub( target, lightPositions[i] );
				//dir.normalize();
				//m->setLightDirection( i, dir );
				//m->setLightDirection( i, vZ8ero );
				Vector3 v333( -0.33333333333f );
				Vector3 lightDir;

				v333.normalize();
				static float angle=0;
				GameLib::Matrix33 Rot;
				
				if ( GameLib::Input::Manager().keyboard().isOn( 'q' ) ){
					angle += 0.5;
				}else if ( GameLib::Input::Manager().keyboard().isOn( 'w' ) ){
					angle -= 0.5;				
				}
				Rot.setRotationZ(angle);
				Rot.mul( &lightDir, v333 );

				m->setLightDirection( i, lightDir );

				//m->setLightDirection( i, Vector3( 0.1, -.99f, 0 ) );
				
				m->setLightDiffuse( i,  vOne );
				m->setLightAmbient( i,  v05 );
				m->setLightSpecular( i, vOne );
				//m->setLightIntensity( i, lightIntensities[ i ] );
			}

			Matrix34 lvm;
			lvm.setViewTransformLH( 
				lightPositions[0],
				target, 
				up );

			world.setIdentity();
			m->setLightWorldMatrix( 0, toDxMatrix(world) );
			m->setLightViewMatrix( 0, toDxMatrix(lvm) );


			Matrix44 lpm;
			lpm.setPerspectiveTransform( 
				90.f, 
				static_cast< float >( fw.width() ),
				static_cast< float >( fw.height() ),
				1.f, 500.f );
			m->setLightProjectionMatrix( 0, toDxMatrix( lpm ) );
		}
	
	}
	
}


State::UptrState State::mThis=nullptr;

State* State::instance() {

	if (!mThis) {
		mThis.reset(new State);
	}

	return mThis.get();
}

// 解放
void State::release()
{
	mThis.reset();
}

State::State()
	:mStage(nullptr),
	mPlayer(nullptr),
	mCameraAnimation(nullptr),
	mNextSequence(nullptr),
	mNeedDrawCall(false),
	mScore(0),
	mNumberKilledEnemy(0)
{
	cameraInit();
	resetAll();
	
	//listener の登録
	//using namespace GameObject::Event::EventData;
	//using namespace GameObject::Event::Listener;
	//GameObject::Event::Manager *gevmngr = GameObject::Event::Manager::instance();
	//gevmngr->addListener( AddToWorldListener::create(), AddToWorld::rtti() );
	//gevmngr->addListener( RemoveFromWorldListener::create(), RemoveFromWorld::rtti() );
	//gevmngr->addListener( DefeatedAllEnemiesListener::create(mStage), DefeatedAllEnemies::rtti() );	


}
State::~State(){
	GameObject::Event::Manager::instance()->destroy();

	mEnemyManager.reset();
	mEnemySpawner.reset();
	mCameraAnimation.reset();
	mStage.reset();
	mPlayer.reset();
	//MME::Manager::instance()->destroy();
	//BulletPhysics::Managerが最後(オブジェクトを世界から全てリムーブさせるため)
	//BulletPhysics::Manager::instance()->release();
	//GUI::Manager::destory();
}

void State::update(){
	GameLib::Framework fw = GameLib::Framework::instance();
	unsigned int deltaMilliSec = fw.previousFrameInterval();
	float deltaTime = static_cast<float>(deltaMilliSec)*0.001f;
	deltaTime=1.f/60.f;
	cameraInit();

	using namespace GameLib;

	GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();


	mPlayer->update(deltaTime);
	mEnemySpawner->update(deltaTime);
	mEnemyManager->update(deltaTime);

	BulletPhysics::Manager::instance()->update(deltaTime);


	GameObject::Event::Manager::instance()->tick(GameObject::Event::Manager::kINFINITE);
}

void State::draw(){
	using namespace GameLib;
	Framework fw = Framework::instance();

	GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
	
	static const int do_nothing = 0;
	
	mPlayer ? mPlayer->preDraw() : do_nothing;

	MME::Drawer::GameDrawer::instance()->draw();

	mEnemyManager ? mEnemyManager->postDraw() : do_nothing;

	mPlayer ? mPlayer->drawHUD() : do_nothing;


 	GUI::Manager::instance()->draw();



	//以下フロントエンド描画
	//モデル描x画でいじられたものを元に戻す
	gm.setDiffuseColor( Vector3( 1.f, 1.f, 1.f ) );
	gm.setTransparency( 1.f );
	gm.setLightingMode( Graphics::LIGHTING_NONE );
		
	//typedef DebugScreen::Color C;
	//DebugScreen sc;
	//sc.setPosition( 0, 20 );
	//sc.precision( 3 );
	//sc << C(0xff000000) << "framerate:"<< fw.frameRate() << endl;
	//sc<< "previousFrameInterval:" << fw.previousFrameInterval() << endl;
	//sc << "num bullet collision objects:" << BulletPhysics::Manager::instance()->getNumberCollisionObjects() << endl;
}

bool State::isReady(){

	static bool only=false;
	//初回だけのとりあえず
	if(MME::Object::PointLight::isReady() && !only){
		static MME::Object::PointLightSharedPtr a = MME::Object::PointLight::create( D3DXVECTOR3(  0,  0,  0 ), 30.f, D3DXVECTOR4( 1, 0, 0, 1 ) ); 
		static MME::Object::PointLightSharedPtr b = MME::Object::PointLight::create( D3DXVECTOR3( 30, 53,  0 ), 30.f, D3DXVECTOR4( 0, 1, 0, 1 ) ); 
		static MME::Object::PointLightSharedPtr c = MME::Object::PointLight::create( D3DXVECTOR3(  0, 53, 30 ), 30.f, D3DXVECTOR4( 0, 0, 1, 1 ) ); 
		static MME::Object::PointLightSharedPtr d = MME::Object::PointLight::create( D3DXVECTOR3( 30, 53, 30 ), 30.f, D3DXVECTOR4( 1, 1, 1, 1 ) ); 
		MME::Drawer::GameDrawer* drawer = MME::Drawer::GameDrawer::instance();
		drawer->add(a);
		drawer->add(b);
		drawer->add(c);
		drawer->add(d);
		only=true;
	}

	

	return 
		MME::Drawer::GameDrawer::instance()->isReady() &&
		only;
}

bool State::isClear()const{
	return mStage->isClear();	
}

//void State::setCameraAnimation(std::shared_ptr<MMD::CameraAnimation> cameraAnim) {
//	mCameraAnimation = cameraAnim;
//}
//
//void State::setPlayer(const GameObject::PlayerSharedPtr & player)
//{
//	mPlayer = player;
//}
//
//void State::setStage(const GameObject::StageSharedPtr & stage)
//{
//	mStage = stage;
//}

void State::setNextSequence(Base* next)
{
	mNextSequence = next;
}
Base* State::getNextSequence()
{
	return mNextSequence;
}


void State::reserveEnemySpawn(const std::string & enemyName, float spawnTime, const btTransform & trans)
{
	auto enemy = mEnemySpawner->reserve(enemyName, spawnTime, trans);
	assert(enemy);
	if (enemy)
	{
		mEnemyManager->add(enemy);
	}
}

void State::build(Resource *resource)
{
	if (!resource->isReady()) {
		TRACE("resource is not ready. it will be ready at this frame.");
		while (!resource->isReady()) {}
	}
	mPlayer = resource->instancePlayer();
	auto enemies = resource->getEnemies();
	for (const auto &e : enemies)
	{
		mEnemySpawner->registerEnemy(e.second);
	}
	mStage = resource->getStage();
	mStage->addToWorld();
	auto iCamera= resource->getCameraAnimation();
	auto hodCamera = std::dynamic_pointer_cast<Camera::HodCamera, Camera::ICamera>(iCamera);
	if (hodCamera) {
		mCameraAnimation = hodCamera;
		mPlayer->setCamera(mCameraAnimation);
	}
	else {
		assert(false && "カメラの実装方法考えろ");
	}
	mEnemySpawner->setTime(0.f);
	mCameraAnimation->setTime(0.f);

}

GameObject::Player * State::getPlayer()
{
	return mPlayer.get();
}

void State::removeFromWorldAll() {
	mPlayer ?mPlayer->removeFromWorld() : 0;
	mEnemyManager ?	mEnemyManager->removeFromWorldAll() : 0 ;
	mStage ? mStage->removeFromWorld() : 0;
}

void State::resetBulletPhysics()
{
	removeFromWorldAll();
	auto mngr = BulletPhysics::Manager::instance();
	mngr->abortEventAll();
	mngr->release();

}

bool State::needDrawCall()const {
	return mNeedDrawCall;
}
void State::setNeedDrawCall(bool b) {
	mNeedDrawCall = b;
}


void State::resetAll() {
	GameObject::Event::Manager::instance()->destroy();
	resetBulletPhysics();
	mEnemyManager.reset(new HOD::EnemyManager());
	mEnemySpawner.reset(new HOD::EnemySpawner());
	mCameraAnimation.reset();
	mStage.reset();
	mPlayer.reset();
	mScore=0;
	mNumberKilledEnemy = 0;

	//listener の登録
	using namespace GameObject::Event::EventData;
	using namespace GameObject::Event::Listener;
	GameObject::Event::Manager *evmngr = GameObject::Event::Manager::instance();
	//evmngr->addListener( AddToWorldListener::create(), AddToWorld::rtti() );
	//evmngr->addListener( RemoveFromWorldListener::create(), RemoveFromWorld::rtti() );
	//evmngr->addListener( DefeatedAllEnemiesListener::create(mStage), DefeatedAllEnemies::rtti() );	
	evmngr->addListener(KilledEnemyListener::create(), KilledEnemy::rtti() );
}

void State::addScore(int value) {
	mScore += value;
	++mNumberKilledEnemy;
}

int State::getScore() const {
	return mScore;
}

int State::getNumberKilledEnemy() const {
	return mNumberKilledEnemy;
}

int State::getPlayerHp() const {
	return static_cast<int>(mPlayer->getStatus()->hp);
}


}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
