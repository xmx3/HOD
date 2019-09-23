#include"StandUpdater.h"
#include"GameObject/OldPlayer/Updater/QuarterView/StandUpdater.h"

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
			namespace TPS{

StandUpdater::StandUpdater(Player* player)
	:IUpdater(player),
	mCoolTime(1.f)

{
	//慣性働かせたい場合もあるだろうから
	//mPlayer->stop();
	mPlayer->changeAnimation( ANIM_STAND );
	mPlayer->getCamera()->changeTPS();
	mPlayer->setMaxSpeedLow();
}

StandUpdater::~StandUpdater(){
}
void StandUpdater::update( float elapsedTime ){
	GameLib::Input::Mouse m;
	GameLib::Input::Keyboard k;
	int x,y;

	if( mPlayer->getMouse()->isFlickedPlayer( &x, &y ) && mPlayer->onGround() ){
		//if( mPlayer->mStatus->canRunHighSpeed() ){
			mPlayer->changeUpdater( TPS_STEP );
		//}
		return;

	} else if( m.isTriggered(m.BUTTON_LEFT) ){
		//クリックした位置にオブジェクトがあった場合
		if( mPlayer->getMouse()->onObject() ){
			IColliderSharedPtr obj = mPlayer->getMouse()->getOnObject();
			const RTTI &rtti = obj->getRTTI();
			if( rtti.isExactly( Rttis::Enemy() ) ){
				//IUpdater* attack = new AttackUpdater();
				//mPlayer->changeUpdater( attack );
				mPlayer->getCamera()->lockOn( obj );
			}
			//else if( rtti.isExactly( Rttis::Item() ){
			//}
		}
		//クリックした位置に何もない場合
		else {
			mPlayer->changeUpdater( TPS_RUN );
			return;
		}
		return;
	}else if( m.isTriggered( m.BUTTON_RIGHT ) ){
		mPlayer->changeUpdater( TPS_SWING );
		
		//Weapontype wp= mPlayer->hasWeaponType();
		//if( wp==SWORD ){
		//} else if( wp==GUN ){
		//} else {}
		//
		//IUpdaterSharedPtr attack( NEW attack( mPlayer ) );
		//mPlayer->changeUpdater( attack );
		return;
	} else if( k.isTriggered('c') ){
		if( mPlayer->onGround() ){
			mPlayer->changeUpdater( QV_STAND );
			return;
		}
	} else {
		if(mPlayer->onGround() && mPlayer->isStopping() ){
			if(mCoolTime < 0.f){
				mPlayer->healStamina( );			
			} else {
				mCoolTime -= mPlayer->getElapsedTime();
			}
		}
	}
}


}//end namespaces
}
}
}
