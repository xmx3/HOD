#include"Stand.h"
#include"Run.h"
#include"Parent.h"
#include"Swing.h"
#include"Fall.h"
#include<GameLib/Input/Mouse.h>
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"GameObject/Player.h"


namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Sword2 {

Stand::Stand( Parent* p  )
	:mModel(p->mModel),
	mMouse(p->mMouse)
{
	mModel->changeAnimation("stand");
	//mModel->init( toDxMatrix( p->mRigidBody->getWorldTransform() ), "stand" );
}
Stand::~Stand(){}

Base* Stand::update( Parent *parent, float elapsedTime ){
	if( !parent->mPlayer->onGround() ){
		return new Fall(parent);
	}
	
	GameLib::Input::Mouse m;

	if( m.isOn(m.BUTTON_LEFT) ){
		return new Sword2::Run( parent );
	} else if( m.isOn(m.BUTTON_RIGHT) ){
		return new Swing(parent);
	}
	return this;
}


} } } }//GameObject::PlayerUtils::Updater::Sword2