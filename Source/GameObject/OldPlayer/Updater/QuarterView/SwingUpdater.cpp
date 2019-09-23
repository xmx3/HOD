#include"SwingUpdater.h"
#include"GameObject/OldPlayer/Player.h"
#include<GameLib/Input/Mouse.h>
#include"Input/PlayerMouse.h"
#include<GameLib/GameLib.h>
#include"Camera/PlayerCamera.h"
#include"GameObjectData/Status.h"
#include"GameObject/Accessory.h"

#include"MME/Object/ModelKai.h"

namespace GameObject{
	namespace OldPlayer{
		class Player;
		namespace Updater{
			namespace QuarterView{

SwingUpdater::SwingUpdater(Player* player)
	:IUpdater(player),
	mCurrentAnimIdx(0),
	mNumClicked(0)
{
	IColliderSharedPtr obj = mPlayer->getMouse()->getOnObject();
	if( obj ){
		mPlayer->getCamera()->lockOn( obj );
		mPlayer->move( obj->getWorldTransform().getOrigin() );
	}
	mPlayer->changeAnimation( ANIM_SWING );
	mPlayer->setMaxSpeedLow();
}

SwingUpdater::~SwingUpdater(){
}

void SwingUpdater::update( float elapsedTime ){
	if( mPlayer->getModel()->isAnimOver() ){
		mPlayer->changeUpdater( QV_STAND );
		
		//++mCurrentAnimIdx;
		//if( mCurrentAnimIdx <= mNumClicked ){
		//	if( mCurrentAnimIdx < mPlayer->getModel()->getNumSwingAnims() )
		//	{
		//		if( mCurrentAnimIdx==1){
		//			mPlayer->jumpLow();
		//			mPlayer->moveForward( 20.f );
		//		}
		//		//mPlayer->cut();
		//		mPlayer->changeAnimation( ANIM_SWING );
		//		return;
		//	} else {
		//		mPlayer->getCamera()->lockOff();
		//		mPlayer->cut();
		//		mPlayer->changeUpdater( QV_STAND );
		//		return;
		//	}
		//} else {
		//	mPlayer->stop();
		//	mPlayer->getCamera()->lockOff();
		//	mPlayer->changeUpdater( QV_STAND );
		//	return;
		//}
	}

	GameLib::Input::Mouse m;
	if( m.isReleased( m.BUTTON_RIGHT ) ){
		++mNumClicked;
	}
}
			}
		}
	}
}