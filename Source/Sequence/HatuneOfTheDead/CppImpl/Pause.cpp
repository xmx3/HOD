#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>
#include <GameLib/Input/Keyboard.h>
#include <GameLib/DebugScreen.h>
using namespace GameLib;

#include "helper/Image.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Pause.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Parent.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Play.h"
#include "Sequence/Title.h"

namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{

Pause::Pause() : mImage( 0 ),mCursorPosistion( 0 ){
	mImage = new Image( "Data/GUI/image/dummy.dds" ); 
}

Pause::~Pause(){
	SAFE_DELETE( mImage );
}

Base* Pause::update( Parent* parent ){
	Base* next = this;
	if(!isReady()){
		return next;
	}
	//0:やりなおし
	//1:面セレへ
	//2:タイトル画面へ
	//3:戻る
	Input::Keyboard k;
	if ( k.isTriggered( k.KEY_DOWN ) ){
		--mCursorPosistion;
		if ( mCursorPosistion < 0 ){ //マイナスは最大値にループ
 			mCursorPosistion = 1;
		}
	}else if ( k.isTriggered( k.KEY_UP ) ){
		++mCursorPosistion;
		if ( mCursorPosistion > 1 ){ //1を越えたら0にループ
			mCursorPosistion = 0;
		}
	}else if ( k.isTriggered( k.KEY_RETURN ) ){
		if ( mCursorPosistion == 0 ){ //ゲームに戻る
			next = new Play;
		}else if ( mCursorPosistion == 1 ){ //タイトルへ戻る
			next = new Title;
		}
	}
	//描画
	//まずゲーム画面
	parent->drawState();
	//上に重ねる
	mImage->draw();
	//字を描く
	DebugScreen sc;
	sc.draw( 0, 0, "[ﾎﾟｰｽﾞ]" );
	sc.draw( 1, 2, "ｹﾞｰﾑｦﾂﾂﾞｹﾙ" );
	sc.draw( 1, 3, "ﾀｲﾄﾙﾆﾓﾄﾞﾙ" );
	//カーソルを書く
	sc.draw( 0, mCursorPosistion + 2, ">" );

	return next;
}

bool Pause::isReady(){
	return mImage->isReady();
}

}}} //namespace Sequence::HatuneOfTheDead::CppImpl
