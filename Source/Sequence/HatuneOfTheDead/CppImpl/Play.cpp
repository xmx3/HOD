#include <GameLib/GameLib.h>
#include <GameLib/Input/Manager.h>
#include <GameLib/Input/Keyboard.h>
#include <GameLib/DebugScreen.h>
#include <GameLib/Framework.h>


#include "Sequence/HatuneOfTheDead/CppImpl/Play.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Clear.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Failure.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Judge.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Pause.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Parent.h"
#include "Sequence/Title.h"
#include "Sequence/HatuneOfTheDead/CppImpl/BattleResult.h"
#include "Sequence/Test.h"

namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{

Play::Play(){ //何もしない
}

Play::~Play(){ //何もしない
}

//ゲーム本体
Base* Play::update( Parent* parent ){
	Base* next = this;
	GameLib::Input::Keyboard kb = GameLib::Input::Manager::instance().keyboard();

	//とりあえずデバグコマンドでテストする。
	if ( kb.isTriggered( '1' ) ) {
		next = new Clear;
	} else if ( kb.isTriggered( '2' ) ){
		next = new Judge;
	} else if ( kb.isTriggered( '3' ) ){
		next = new Failure;
	} else if ( kb.isTriggered( '4' ) ){
		next = new BattleResult();
	} else if ( kb.isTriggered( ' ' ) ){ //spaceボタンでポーズへ行く。ただしまだ移ってない時だけだ
		next = new Pause;
	}

	parent->updateState();
	parent->drawState();


	if(next==this){
		if( parent->isClear() ){
			next = new Clear;
		}
	}
	
	using GameLib::endl;
	GameLib::DebugScreen sc;
	sc << "1 clear" << endl;
	sc << "2 judge" << endl;
	sc << "3 failure" << endl;
	sc << "4 BattleResult" << endl;
	sc << "space pause" << endl;
	
	//GameLib::Framework f;
	//f.requestEnd();
	return next;
}


}}} //namespace Sequence::HatuneOfTheDead::CppImpl
