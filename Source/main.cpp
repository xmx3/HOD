#include"main.h"
#include<GameLib/DebugScreen.h>
#include"GUI/Manager.h"
#include"Sequence/Parent.h"
//#include"GameObject/AccessoryUtils/Manager.h"
#include"MME/Manager.h"
#include"SoundManager.h"
#include"MMD/MMDDataBase.h"
#include<memory>
#include<GameLib/GameLib.h>
#include"MME/Object/PointLight.h"

#include<GameLib/FileIO/Manager.h>
namespace {

const int kLightsNum = 1;

GameLib::Vector3 gAmbient( 0.2f, 0.3f, 0.4f );
GameLib::Scene::PrimitiveRenderer gPrimitiveRenderer;


//void drawUserPtrOverLappingObjects( btGhostObject *go, DebugScreen ds ){
//	int num=go->getNumOverlappingObjects();
//	for( int i=0; i<num; ++i ){
//		btCollisionObject *p = go->getOverlappingObject( i );
//		ds << (int)p << endl;
//	}
//
//	btAlignedObjectArray<btCollisionObject*> &refArray = go->getOverlappingPairs();
//	int size=refArray.size();
//	for( int i=0; i<size; ++i ){
//		btCollisionObject *p = refArray[i];
//		ds << (int)p << endl;
//	}
//}

} // end namespace anonymous


//ユーザ実装関数。中身はmainLoop()に
namespace GameLib{
	void Framework::configure( Configuration* c ){
		//c->enableVSync( true );
		c->setArchiveNumber( 1 );
		c->setArchiveName( 0, "data.bin" );
		c->setLoadMode( LOAD_DIRECT_FIRST );
		c->setExtraThreadNumber( 1 );
		//c->enableAntiAlias(false);
		//c->setWidth(1200);
		//c->setHeight(700);
		//c->enableFullScreen();
		
	}
	void Framework::update(){
		static bool hasInitiated = false;
		if ( !hasInitiated ){
			Sequence::Parent::create();
			GUI::Manager *mngr=GUI::Manager::instance();
			while(!mngr->isReady()){}
			MME::Manager *mme = MME::Manager::instance();
			while(!mme->isReady()){}
			hasInitiated=true;
			setFrameRate(60);
			return;
		}
		Sequence::Parent::instance()->update();
/*
		unsigned int deltaMilliSec = time()-gPreTime;
		float deltaTime = static_cast<float>(deltaMilliSec)*0.001f;
		gPreTime=time();
		if ( gPlaying ){
			++gTime;
		}

		//カメラ行列ゲット
		Matrix44 pvm,pm;
		pm.setPerspectiveTransform( 45.f, 
			static_cast< float >( width() ),
			static_cast< float >( height() ),
			1.f,
			10000.f );
		
		Matrix34 vm;
		Vector3 eyePosition;
		
		vm.setViewTransform( Vector3( 0, 10, -100 ), Vector3(0,20,0), Vector3(0,1,0) );
		//if(false)	
		if(gPlaying){
			Vector3 eyePos, target;
			eyePos=pPlayer->getCameraPos();
			target=pPlayer->getCameraTargetPos();
			//g_pCharacter->getView2( &target, &eyePos );
			vm.setViewTransform( eyePos, target, Vector3(0,1,0) );
			eyePosition = eyePos;
			g_pSniperCamera->setInitialTargetPos( target );
			g_pSniperCamera->setPos( eyePos );
			g_pSniperCamera->resetYawPitch();
		} else {
			Vector3 target;
			g_pSniperCamera->update();
			g_pSniperCamera->getView( &eyePosition, &target );
			vm.setViewTransform( eyePosition, target, Vector3(0,1,0) );
		}

		pvm.setMul( pm, vm );

		//描画
		//グローバルなライティング設定
		Graphics::Manager gm = Graphics::Manager::instance();
		//gm.set
		gm.setProjectionViewMatrix( pvm );
		gm.setEyePosition( eyePosition );

		gm.setLightingMode( Graphics::LIGHTING_PER_PIXEL );
		gm.setAmbientColor( gAmbient );
		gm.setLightColor( 0, Vector3( 0.7f, 0.4f, 0.2f ) );
		gm.enableDepthTest( true );
		gm.enableDepthWrite( true );

		Vector3 lightPos[ 4 ];
		lightPos[ 0 ].set( 0.f, 100000.f, 0.f );
		float lightIntensities[ 4 ];
		lightIntensities[ 0 ] = lightPos[ 0 ].length(); //長さを強度にすれば、だいたいその距離で1になる

		gm.setCullMode( Graphics::CULL_BACK );
		
		//ライト設定
		for ( int i = 0; i < kLightsNum; ++i ){
			gm.setLightPosition( i, lightPos[ i ] );
			gm.setLightIntensity( i, lightIntensities[ i ] );
		}

		D3DXVECTOR3 start,end;
		//マウスの線をもらう
		ClickPos::getLine( &start, &end, toDxMatrix(pvm));
		using BulletPhysicsHelper::toDxVec3;
		
		//g_pCharacter->update( deltaTime, BulletPhysicsHelper::toBtVector3(start), BulletPhysicsHelper::toBtVector3(end) );
		//g_pCharacter->update( deltaTime );
		
		pPlayer->update(deltaTime);

			
		BOOST_FOREACH( GameObject::SptrEnemy e, gEnemies ){
			e->update(deltaTime);
		}

		if(gPlaying)
		{
			BulletPhysics::Manager::instance()->update(deltaTime);
			gStage->draw();
		}
		else
		{
			//gStage->draw();
			//BulletPhysics::Manager::instance()->drawWorld();
			//int framerate = frameRate();
			//std::string str = boost::lexical_cast<std::string>(framerate);
			//DebugScreen::instance().draw( 0, 0, str.c_str() );
		}


		Matrix34 wm;
		D3DXMATRIX w;
		D3DXMatrixIdentity(&w);
		wm.setIdentity();
		gm.setWorldMatrix(wm);


		//g_pCharacter->draw();
		pPlayer->draw();


		
		if ( Input::Manager().keyboard().isTriggered( 'a' ) ){
			//for( int i=0; i<10 ; ++i ){
				gEnemies.push_back( GameObject::SptrEnemy( NEW GameObject::Enemy(pPlayer) ) );
			//}
		}

		if(gExplosion==NULL)
		{
			if ( Input::Manager().keyboard().isTriggered( 'e' ) )
			{
				gExplosion = new ExplosionGhostObject();
				gExplosion->setPos( btVector3( 0, 50, 0 ) );
			}
			
		} else {
			gExplosion->update(deltaTime);
			gExplosion->draw();
			if ( Input::Manager().keyboard().isTriggered( 'e' ) )
			{
				gExplosion->setScale(0.f);
			}
			
			if ( Input::Manager().keyboard().isTriggered( '1' ) )
			{
				gExplosion->setEnable( !gExplosion->isEnable() );
			}
		}

		
		BOOST_FOREACH( GameObject::SptrEnemy e, gEnemies ){
			e->draw();
		}
		
		//以下フロントエンド描画
		//モデル描x画でいじられたものを元に戻す
		gm.setDiffuseColor( Vector3( 1.f, 1.f, 1.f ) );
		gm.setTransparency( 1.f );
		gm.setLightingMode( Graphics::LIGHTING_NONE );
		
		if ( Input::Manager().keyboard().isTriggered( ' ' ) ){
			gPlaying = !gPlaying;
		}
		//PrintBtVector3::toDebugScreen( g_pCharacter->getWorldTransform() );
		typedef DebugScreen::Color C;
		DebugScreen sc;
		sc.setPosition( 0, 20 );
		sc.precision( 3 );
		sc << C(0xff000000) << "framerate:"<< frameRate() << endl;
		sc << "num enemies: " << gEnemies.size() << endl;
*/		
		//終了判定(マウスで×ボタンが叩かれたか)
		if ( isEndRequested() ){
			//グローバルにあるものは勝手には消えないので開放
			Sequence::Parent::destroy();
			GUI::Manager::destory();
			//GameObject::AccessoryUtils::Manager::destroy();
			MME::Manager::instance()->destroy();
			SoundManager::destroy();
			//MME::Object::PointLight::destroy();
			MMD::MMDDataBase::destroy();
		}
	}
}
