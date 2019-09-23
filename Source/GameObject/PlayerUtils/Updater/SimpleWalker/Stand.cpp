#include"Stand.h"
#include"Run.h"
#include"Parent.h"
#include<GameLib/Input/Mouse.h>
#include"BulletPhysics/BulletPhysicsHelper.h"


namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace SimpleWalker {

Stand::Stand( Parent* p  )
	:mModel(p->mModel),
	mMouse(p->mMouse)
{
	mModel->changeAnimation("stand");
	//mModel->init( toDxMatrix( p->mRigidBody->getWorldTransform() ), "stand" );
}
Stand::~Stand(){}

Base* Stand::update( Parent *parent, float elapsedTime ){
	GameLib::Input::Mouse m;

	if( m.isOn(m.BUTTON_LEFT) ){
		return new SimpleWalker::Run( parent );
	}
	return this;
}


} } } }//GameObject::PlayerUtils::Updater::SimpleWalker