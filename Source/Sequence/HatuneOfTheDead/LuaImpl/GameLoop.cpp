#include <assert.h>
#include <GameLib/GameLib.h>
#include <GameLib/Input/Manager.h>
#include <GameLib/Input/Keyboard.h>
#include <GameLib/DebugScreen.h>
#include <GameLib/Framework.h>

#include "GUI/Manager.h"
#include "Sequence/HatuneOfTheDead/LuaImpl/GameLoop.h"
#include "Sequence/HatuneOfTheDead/LuaImpl/Parent.h"
#include "Lua/LuaHelper.h"
#include "State.h"
#include "Resource.h"
#include "helper/MyOutputDebugString.h"


namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{

GameLoop::GameLoop(){
}

GameLoop::~GameLoop(){
}

//ゲーム本体
Base* GameLoop::update( Parent* parent ){
	auto state = State::instance();
	state->setNextSequence(this);

	using namespace Lua;
	LuaFuncParam result;
	while (!CallLuaFunc("framefunc", &result, 1)) {
		WaitInputOnError(GetLuaError(), "Reload OK?");
		//assert(false && "現状こことおる気ない");//いやとおることあると思うけどf
		//全初期化
		state->resetBulletPhysics();
		State::instance()->release();
		GUI::Manager::instance()->destory();
		Resource::instance()->release();
		state = State::instance();//バグ対策、開放した奴そのまま使ってしまうから。新しいのを作って登録
		state->setNextSequence(this);
		parent->reloadLua();
		//HatneOfDead/gameinit.luaで指定された状態にに戻る
	}

	if ( state->needDrawCall()) {
		state->draw();
	}


	GameLib::Input::Keyboard k;
	if (k.isTriggered('1')) {
		//リソース以外は全開放
		//ロードする時間短くするため
		TRACE("reload lua in GameLoop.cpp\n");
		GUI::Manager::instance()->destory();

		state->resetBulletPhysics();
		//resourceは開放しない
		state->release();
		parent->reloadLua();
		//ロビーに戻る
		while (!CallLuaFunc("framefunc", &result, 1)) {
			WaitInputOnError(GetLuaError(), "Reload OK?");
			//assert(false && "現状こことおる気ない");//luaでのコンパイルエラー何度でもするでしょ
			state = State::instance();
			state->resetBulletPhysics();
			state->release();
			parent->reloadLua();
			//ロビーに戻る
		}
		state = State::instance();//バグ対策、開放した奴そのまま使ってしまうから。新しいのを作るって登録
		state->setNextSequence(this);
	}

	return state->getNextSequence();
}


}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
