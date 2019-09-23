#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>
#include <GameLib/DebugScreen.h>
#include <GameLib/Input/Keyboard.h>

#include "helper/Image.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Judge.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Parent.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Ready.h"
#include "Sequence/Title.h"

#include <assert.h>

namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{

Judge::Judge() : mImage( 0 ), mCursorPosistion( 0 ){
	mImage = new Image( "Data/GUI/image/dummy.dds" ); 
}

Judge::~Judge(){
	SAFE_DELETE( mImage );
}

Base* Judge::update( Parent* parent ){
	Base* next = this;
	if(!isReady()){
		return next;
	}
	
	GameLib::Input::Keyboard k;

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
		if ( mCursorPosistion == 0 ){
			//続けて勝負
			assert(false);//TODO
			//本来はStateをリセットして送りたいがとりあえず
			next = new Ready(nullptr);
		}else if ( mCursorPosistion == 1 ){
			//タイトルへ
			next = new Title;
		}
	}
	//描画
	//まずゲーム画面
	parent->drawState();
	//上に重ねる
	mImage->draw();

	//まずどっちが勝ったのか表示
	GameLib::DebugScreen sc;
	sc.draw( 0, 0, "[ｼｮｳﾊｲｹｯﾃｲ]" );

	//Parent::PlayerID winner = parent->winner();
	//if ( winner == Parent::PLAYER_1 ){
	//	sc.draw( 0, 1, "1Pﾉ ｶﾁ!" );
	//}else if ( winner == Parent::PLAYER_2 ){
	//	sc.draw( 0, 1, "2Pﾉ ｶﾁ!" );
	//}else{
	//	sc.draw( 0, 1, "ｼｮｳｼｬﾅｼ! ﾋｷﾜｹ!" );
	//}
	//めぬー
	sc.draw( 1, 3, "ﾏﾀﾞ ｺﾛｼｱｳ" );
	sc.draw( 1, 4, "ﾔﾒﾃ ﾀｲﾄﾙ ｶﾞﾒﾝ ﾍ" );
	//カーソルを書く
	sc.draw( 0, mCursorPosistion + 3, ">" );

	return next;
}

bool Judge::isReady(){
	return mImage->isReady();
}

}}} //namespace Sequence::HatuneOfTheDead::CppImpl
