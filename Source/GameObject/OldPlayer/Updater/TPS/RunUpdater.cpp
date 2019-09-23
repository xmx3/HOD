#include"RunUpdater.h"
#include"GameObject/OldPlayer/Player.h"
#include<GameLib/Input/Mouse.h>
#include"Input/PlayerMouse.h"
#include<GameLib/GameLib.h>
#include"Camera/PlayerCamera.h"
#include"GameObjectData/Status.h"
//#include<LinearMath/btVector3.h>

namespace GameObject{
	namespace OldPlayer{
		namespace Updater{
			namespace TPS{

RunUpdater::RunUpdater( Player* player )
	:IUpdater(player)
{
	mPlayer->move( mPlayer->getMousePos() );
	mPlayer->changeAnimation( ANIM_RUN );
}
RunUpdater::~RunUpdater(){}
void RunUpdater::update( float elapsedTime ){
	GameLib::Input::Mouse m;
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
			mPlayer->move( mPlayer->getMousePos() );
		}
	} else if( m.isTriggered( m.BUTTON_RIGHT ) ){
		if( mPlayer->onGround() ){
			//Weapontype wp= mPlayer->hasWeaponType();
			//if( wp==SWORD ){
			//} else if( wp==GUN ){
			//} else {}
			//
			//IUpdaterSharedPtr attack( NEW attack( mPlayer ) );
			//mPlayer->changeUpdater( attack );
			return;
		}
	}

	//空中にいる場合
	//if( !mPlayer->onGround() ){}


	if( mPlayer->isStopping() ){
		mPlayer->changeUpdater( TPS_STAND );
		return;
	}

}




			}//end namespaces
		}
	}
}


