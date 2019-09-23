#include"JumpUpdater.h"

#include"GameObject/OldPlayer/Player.h"
#include<GameLib/Input/Mouse.h>
#include"Input/PlayerMouse.h"
#include<GameLib/GameLib.h>
//#include<LinearMath/btVector3.h>
#include"GameObjectData/Status.h"

namespace GameObject{
	namespace OldPlayer{
		namespace Updater{
			namespace QuarterView{
JumpUpdater::JumpUpdater(Player* player)
	:IUpdater(player)
{
	mPlayer->jumpIfHaveEnoughStamina();
	mPlayer->changeAnimation(ANIM_PUNCH);
}
JumpUpdater::~JumpUpdater(){

}
void JumpUpdater::update( float elapsedTime ){
	//GameObjectData::Status *st=mPlayer->mStatus;

	if( mPlayer->isMoving() ){
		if( mPlayer->useStaminaIfCanRun() ){
		} else {
			//完成をありにするか
			//mPlayer->stop();
			mPlayer->cut();
			return;
		}
	}

	GameLib::Input::Mouse m;
	if( m.isTriggered(m.BUTTON_LEFT) ){
		//クリックした位置にオブジェクトがあった場合
		if( mPlayer->getMouse()->onObject() ){
			IColliderSharedPtr obj = mPlayer->getMouse()->getOnObject();
			const RTTI &rtti = obj->getRTTI();
			if( rtti.isExactly( Rttis::Enemy() ) ){
				//IUpdater* attack = new AttackUpdater();
				//mPlayer->changeUpdater( attack );
			}
			//else if( rtti.isExactly( Rttis::Item() ){
			//}
		}
		//クリックした位置に何もない場合
		else {
			mPlayer->move( mPlayer->getMousePos() );
		}
	} else if( m.isTriggered( m.BUTTON_RIGHT ) ){
		mPlayer->forceJumpIfHaveEnoughStamina();
	}

	//空中にいる場合
	//if( !mPlayer->onGround() ){
	//}


	if( mPlayer->isStopping() && mPlayer->onGround() ){
		mPlayer->changeUpdater( QV_STAND );
	}
}


			}//end namespace
		}
	}
}