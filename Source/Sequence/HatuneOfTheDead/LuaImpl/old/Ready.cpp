#include <GameLib/GameLib.h>
#include <GameLib/DebugScreen.h>
#include <GameLib/Framework.h>

#include "Sequence/HatuneOfTheDead/LuaImpl/Ready.h"
#include "Sequence/HatuneOfTheDead/LuaImpl/Parent.h"
#include "Sequence/HatuneOfTheDead/LuaImpl/Play.h"
#include "Sequence/HatuneOfTheDead/LuaImpl/State.h"
#include "helper/Image.h"

//#include"helper/FileLoader.h"
#include"GameObject/XmlFiles.h"

#include"GameObject/Stage.h"


#include<GameLib/Threading/Thread.h>
#include"MMD/Model.h"
#include"SoundManager.h"

#include"MMD/CameraAnimation.h"

#include"XmlLoader/GameObject/Player.h"
#include"XmlLoader/GameObject/Enemy.h"

namespace {
	void display( int count ){
		using namespace GameLib;

		GameLib::Framework fw = GameLib::Framework::instance();

		typedef DebugScreen::Color C;
		DebugScreen sc;
		sc.setPosition( 0, 20 );
		sc.precision( 3 );
		sc << C(0xff000000) << "framerate:"<< fw.frameRate() << endl;
		sc<< "previousFrameInterval:" << fw.previousFrameInterval() << endl;
		sc << "count: " << count << endl;
		
		//字を出す
		DebugScreen::instance().draw( count%fw.width(), 0,  "..." );
		DebugScreen::instance().draw( 0, 1, "[READY] : " );
		DebugScreen::instance().draw( 0, 2, "Ready..." );

	}
}


namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{

Ready::Ready(State* state) : 
mState(state),
mImage(nullptr),
mCount( 0 ),
mPlayer(nullptr),
mEnemy(nullptr),
mStage(nullptr)
{
	mImage = new Image( "Data/GUI/image/loading.png" ); 
	while( !mImage->isReady() ){}
	mCameraAnimation = std::make_shared<MMD::CameraAnimation>();
	mCameraAnimation->load("Data/MMDData/vmd/camera_simple.vmd");
	//mCameraAnimation->load("Data/MMDData/vmd/camera_test.vmd");
	mPlayer = new XmlLoader::GameObject::Player();
	mPlayer->loadXml("Data/XmlLoader/GameObject/Player/miku.xml");

	mEnemy = std::make_shared<XmlLoader::GameObject::Enemy>();
	mEnemy->loadXml("Data/XmlLoader/GameObject/Enemy/bou.xml");

	mStage = GameObject::Stage::create("Data/XmlLoader/GameObject/Stage/stage01.xml");
	//mStage = GameObject::Stage::create("Data/XmlLoader/GameObject/Stage/stage02.xml");
}

Ready::~Ready(){
	mStage.reset();
	mEnemy.reset();
	SAFE_DELETE(mPlayer);
	mCameraAnimation.reset();
	SAFE_DELETE(mImage);
	mState = nullptr;//削除はほかのクラスにお任せ、基本的に自分(自クラス内)で作ったもの以外はメモリ管理しない
}

Base* Ready::update( Parent* parent ){
	Base* next = this;

	++mCount;
	mImage->isReady();
	mImage->draw();
	
	using namespace GameLib;

	//wait for SoundManager to Ready.
	bool ok = SoundManager::instance()->isReady();
	if (!ok) {
		display(mCount);;
		return next;
	}

	ok = mPlayer->isReady();
	if (!ok) {
		DebugScreen::instance().draw(0, 0, "loading player...");
		display(mCount);
		return next;
	}


	ok = mStage->isReady();
	if (!ok) {
		DebugScreen::instance().draw(0, 0, "loading stage...");
		display(mCount);
		return next;
	}

	
	ok = mEnemy->isReady();
	if (!ok) {
		DebugScreen::instance().draw(0, 0, "loading enemy...");
		display(mCount);
		return next;
	}

	ok = mCameraAnimation->isReady();
	if (!ok) {
		DebugScreen::instance().draw(0, 0, "loading camera animation...");
		display(mCount);
		return next;
	}

	//wait for Parent to Ready.
	ok = parent->isReady();
	if (!ok) {
		display(mCount);;
		return next;
	}

	ok = wait30Frame();
	//display scene changing.  
	if (!ok) {
		DebugScreen::instance().draw(0, 0, "[READY] : ");
		DebugScreen::instance().draw(0, 1, "Ready...");
		return this;
	}

	ok = wait10Frame();
	//display scene changing.  
	if (!ok) {
		DebugScreen::instance().draw(0, 0, "[READY] : ");
		DebugScreen::instance().draw(0, 1, "GO!");
		return this;
	}

	mState->setCameraAnimation(mCameraAnimation);
	//mState->setEnemy(mEnemy);
	mState->setPlayer(mPlayer->instance());
	mState->setStage(mStage);

	assert(next == this);
	next = new Play();

	return next;
}

}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
