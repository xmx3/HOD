#include"Run.h"
#include"Stand.h"
#include"Parent.h"
#include"Swing0.h"
#include"Fall.h"
#include<GameLib/Input/Mouse.h>
#include"BulletPhysics/Manager.h"
#include"GameObject/Player.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace TameSword {

Run::Run( Parent* p  )
	:PointMover( p->mRigidBody, p->mStatus ), 
	Child(p)
{
	mModel->changeAnimation("run");
	const btVector3& pos = mMouse->getPos();
	look( pos );
	strafe( pos );
}
Run::~Run(){
	stop();
}

Base* Run::update( Parent *parent, float elapsedTime ){
	if(	!parent->mPlayer->onGround() ){
		return new Fall(parent);
	}
	
	GameLib::Input::Mouse m;
	const btVector3& pos = mMouse->getPos();

	if(	!parent->mPlayer->onGround() ){
		return new Fall(parent);
	}

	look( pos );

	if( m.isOn(m.BUTTON_LEFT) ){
		strafe( pos );
	}

	updateStrafe(elapsedTime);
	updateLook(elapsedTime);

	if(m.isTriggered( m.BUTTON_RIGHT ) ){
		return new Swing0( parent );
	}

	if( !isMoving() ){
		return new Stand( parent );
	}

	return this;
}

} } } } //GameObject::PlayerUtils::Updater::TameSword
