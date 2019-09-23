#include"StandUpdater.h"

#include"GameObject/OldPlayer/Player.h"
#include<GameLib/Input/Mouse.h>
#include<GameLib/Input/Keyboard.h>
#include"Input/PlayerMouse.h"
#include<GameLib/GameLib.h>
#include"Camera/PlayerCamera.h"
#include"GameObjectData/Status.h"
namespace GameObject{
	namespace OldPlayer{
		class Player;
		namespace Updater{
			namespace QuarterView{

StandUpdater::StandUpdater(Player* player)
	:IUpdater(player),
	mCoolTime(2.f)
{
	mPlayer->getCamera()->changeQuarterView();
	//慣性働かせたい場合もあるだろうから
	//mPlayer->stop();
	mPlayer->changeAnimation( ANIM_STAND );
	mPlayer->getCamera()->lockOff();
	mPlayer->setMaxSpeedHigh();

}
StandUpdater::~StandUpdater(){
}
void StandUpdater::update( float elapsedTime ){

	GameLib::Input::Mouse m;
	 GameLib::Input::Keyboard k;
	if( m.isTriggered(m.BUTTON_LEFT) ){
		//クリックした位置にオブジェクトがあった場合
		if( mPlayer->getMouse()->onObject() ){
			IColliderSharedPtr obj = mPlayer->getMouse()->getOnObject();
			const RTTI &rtti = obj->getRTTI();
			if( rtti.isExactly( Rttis::Enemy() ) ){
				//mPlayer->getCamera()->lockOn( obj );
				mPlayer->changeUpdater( QV_SWING );
				
				//IUpdater* attack = new AttackUpdater();
				//mPlayer->changeUpdater( attack );
			}
			//else if( rtti.isExactly( Rttis::Item() ){
			//}
		}
		//クリックした位置に何もない場合
		else {
			mPlayer->changeUpdater( QV_RUN );
			return;
		}
		return;
	}else if( m.isReleased( m.BUTTON_RIGHT ) ){
		if( mPlayer->onGround() ){
			mPlayer->changeUpdater( QV_SWING );
			return;
		}
	} else if( k.isTriggered('c') ){
		if( mPlayer->onGround() ){
			//mPlayer->changeUpdater( TPS_STAND );
			mPlayer->changeUpdater( CAR_STAND );
			return;
		}
	}

	if( mPlayer->onGround() ){
		if(mCoolTime < 0.f){
			mPlayer->healStamina();			
		} else {
			mCoolTime -= mPlayer->getElapsedTime();
		}
	}
}


}//end namespaces
}
}
}
