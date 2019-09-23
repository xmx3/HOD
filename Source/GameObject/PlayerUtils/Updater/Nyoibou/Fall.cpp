#include"Fall.h"
#include"Stand.h"
#include"Parent.h"
#include"BulletPhysics/Manager.h"
#include<GameLib/Input/Mouse.h>
#include"GameObject/Player.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Nyoibou {

Fall::Fall( Parent* p  )
	:Child(p)
{
	mModel->changeAnimation("fall");
}
Fall::~Fall(){}

Base* Fall::update( Parent *parent, float elapsedTime ){
	
	if(	parent->mPlayer->onGround()	){
		return new Stand(parent);
	}
	
	GameLib::Input::Mouse m;
	if( m.isTriggered(m.BUTTON_LEFT) ){
		mRigidBody->setLinearVelocity( btVector3(0.f,0.f,0.f) );
	}

	return this;
}


} } } }//GameObject::PlayerUtils::Updater::Nyoibou
