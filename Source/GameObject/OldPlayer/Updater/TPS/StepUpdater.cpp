#include"StepUpdater.h"

#include"GameObject/OldPlayer/Player.h"

#include<GameLib/Input/Mouse.h>
#include<GameLib/Input/Keyboard.h>
#include"Input/PlayerMouse.h"
#include<GameLib/GameLib.h>
#include"Camera/PlayerCamera.h"
#include"GameObjectData/Status.h"

#include<algorithm>

#include"helper/MyOutputDebugString.h"

namespace GameObject{
	namespace OldPlayer{
		class Player;
		namespace Updater{
			namespace TPS{

StepUpdater::StepUpdater(Player* player )
	:IUpdater(player)
{
	if( !mPlayer->useStaminaIfCanRunHigh() ){
		return;
	}
	int x, y;
	bool canStep=mPlayer->getMouse()->isFlickedPlayer( &x, &y );
	assert( canStep );

	//step
	const btTransform &world = mPlayer->getWorldTransform();
	//ƒJƒƒ‰‚ðŠî€‚É‚µ‚½‚Ù‚¤‚ª•ûŒü‚ª•ª‚©‚è‚â‚·‚¢
	Camera::PlayerCamera *camera = mPlayer->getCamera();
	//camera->getIdealPos();
	btVector3 target = camera->getTargetPos();
	//camera->getIdealPos();
	//camera->getIdealPos();
	btVector3 forward = target - world.getOrigin();
	forward.setY(0.f);
	forward.normalize();

	btVector3 strafeDir = forward.cross( btVector3( 0.f,1.f,0.f ) );

	strafeDir.normalize();
	float length = static_cast<float>( abs(x)+abs(y) );
	if( length==0.f ){
		return;
	}

	//TRACE1( "length:%f\n", length );
	float h = mPlayer->getHeight();
	const float moveValue = (std::min)( h*2.f, h*2.f*length/300.f );

	float rateX = static_cast<float>(x)/length;
	float rateY = static_cast<float>(y)/length;

	btVector3 stepDir = -rateY*forward+rateX*strafeDir;

	mPlayer->jump( 6.f );
	mPlayer->setMaxSpeedHigh();	
	mPlayer->strafe( world.getOrigin()+stepDir*moveValue );
}
StepUpdater::~StepUpdater(){}

void StepUpdater::update( float elapsedTime ){
	
	if( mPlayer->onGround() ){
		//mPlayer->mController->setMaxSpeed( mPlayer->mStatus->getSpeedWalking() );	
		mPlayer->cut();
		mPlayer->changeUpdater( TPS_STAND );
		return;
	}

}

			}
		}
	}
}