#include"StandUpdater.h"
#include"GameObject/OldPlayer/Updater/Car/StandUpdater.h"

#include"GameObject/OldPlayer/Player.h"

#include<GameLib/Input/Mouse.h>
#include<GameLib/Input/Keyboard.h>
#include"Input/PlayerMouse.h"
#include<GameLib/GameLib.h>
#include"Camera/PlayerCamera.h"
#include"GameObjectData/Status.h"

#include<GameLib/DebugScreen.h>

namespace GameObject{
	namespace OldPlayer{
		class Player;
		namespace Updater{
			namespace Car{

StandUpdater::StandUpdater(Player* player)
	:IUpdater(player),
	mCoolTime(2.f)
{
	//Šµ«“­‚©‚¹‚½‚¢ê‡‚à‚ ‚é‚¾‚ë‚¤‚©‚ç
	//mPlayer->stop();
	mPlayer->changeAnimation( ANIM_STAND );
	mPlayer->getCamera()->changeQuarterView();
	mPlayer->setMaxSpeedLow();
}

StandUpdater::~StandUpdater(){
}
void StandUpdater::update( float elapsedTime ){
	GameLib::Input::Mouse m;

	if( m.isTriggered(m.BUTTON_LEFT) ){
		mPlayer->changeUpdater( CAR_RUN );
		return;
		
	}

	if(mPlayer->onGround() && mPlayer->isStopping() ){
		if(mCoolTime < 0.f){
			mPlayer->healStamina( );			
		} else {
			mCoolTime -= mPlayer->getElapsedTime();
		}
	}

	GameLib::DebugScreen ds;
	ds << "Car::StandUpdate" <<GameLib::endl;
}


} } } }//GameObject::Player::Updater::Car
