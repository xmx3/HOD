#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>
#include <GameLib/DebugScreen.h>

#include "Sequence/HatuneOfTheDead/CppImpl/Failure.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Parent.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Ready.h"
#include "Sequence/GameOver.h"
#include "helper/Image.h"

namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{

Failure::Failure() : mImage( 0 ), mCount( 0 ){
	mImage = new Image( "Data/GUI/image/dummy.dds" ); 
}

Failure::~Failure(){
	SAFE_DELETE( mImage );
}

Base* Failure::update( Parent* parent ){
	Base* next = this;
	if(!isReady()){
		return next;
	}
	
	if ( mCount == 60 ){ //1秒待つ 
		next = new GameOver;
	}
	//描画
	//まずゲーム画面を描画
	parent->drawState();
	//上に祝いのメッセージを描画
	mImage->draw();
	//クリアーと字を描く
	GameLib::DebugScreen sc;
	sc.draw( 0, 0, "ｱｰｯ!" );

	++mCount;

	return next;
}

bool Failure::isReady(){
	return mImage->isReady();
}

}}} //namespace Sequence::HatuneOfTheDead::CppImpl
