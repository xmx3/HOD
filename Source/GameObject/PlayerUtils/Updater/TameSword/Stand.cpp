#include"Stand.h"
#include"Run.h"
#include"Parent.h"
#include"Swing0.h"
#include"Fall.h"
#include<GameLib/Input/Mouse.h>
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"BulletPhysics/OnGround.h"
#include"GameObject/Player.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace TameSword {

Stand::Stand( Parent* p  )
	:Child(p)
{
	mModel->changeAnimation("stand");
	//mModel->init( toDxMatrix( p->mRigidBody->getWorldTransform() ), "stand" );
}
Stand::~Stand(){}

Base* Stand::update( Parent *parent, float elapsedTime ){
	if(	!parent->mPlayer->onGround() ){
		return new Fall(parent);
	}
	
	GameLib::Input::Mouse m;

	if( m.isOn(m.BUTTON_LEFT) ){
		return new TameSword::Run( parent );
	} else if( m.isOn(m.BUTTON_RIGHT) ){
		return new Swing0(parent);
	}
	return this;
}


} } } }//GameObject::PlayerUtils::Updater::TameSword
