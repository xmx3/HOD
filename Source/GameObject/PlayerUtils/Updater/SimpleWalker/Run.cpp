#include"Run.h"
#include"Stand.h"
#include"Parent.h"
#include<GameLib/Input/Mouse.h>

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace SimpleWalker {

Run::Run( Parent* p  )
	:PointMover( p->mRigidBody, p->mStatus ), 
	mModel(p->mModel),
	mMouse(p->mMouse)
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
	GameLib::Input::Mouse m;
	const btVector3& pos = mMouse->getPos();

	look( pos );

	if( m.isOn(m.BUTTON_LEFT) ){
		strafe( pos );
	}

	updateStrafe(elapsedTime);
	updateLook(elapsedTime);

	if( !isMoving() ){
		return new Stand( parent );
	}

	return this;
}

} } } }//GameObject::PlayerUtils::Updater::SimpleWalker