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
			namespace TPS{

SwingUpdater::SwingUpdater(Player* player)
	:IUpdater(player),
	mCurrentAnimIdx(0),
	mNumClicked(0)
{
	mPlayer->changeAnimation( ANIM_SWING );
	if( IColliderSharedPtr lockOnObject = mPlayer->getCamera()->getLockOnObject() ){
		mPlayer->move( lockOnObject->getWorldTransform().getOrigin() );
	}
}

SwingUpdater::~SwingUpdater(){
}

void SwingUpdater::update( float elapsedTime ){
	if( mPlayer->getModel()->isAnimOver() ){
		mPlayer->changeUpdater( TPS_STAND );
		
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
		//		mPlayer->cut();
		//		mPlayer->changeUpdater( TPS_STAND );
		//		return;
		//	}
		//} else {
		//	mPlayer->cut();
		//	mPlayer->changeUpdater( TPS_STAND );
		//	return;
		//}
	}

	GameLib::Input::Mouse m;
	if( m.isTriggered( m.BUTTON_RIGHT ) ){
		++mNumClicked;
	}
}
			}
		}
	}
}