#include"Swing0.h"
#include"Stand.h"
#include"Parent.h"
#include"Swing1.h"

#include<GameLib/Input/Mouse.h>
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"GameObject/Accessory.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace TameSword {

Swing0::Swing0( Parent* p  )
	:Child(p),
	mPushingButtonTime(0.f)
{
	mModel->changeAnimation("swing0");
}
Swing0::~Swing0(){}

Base* Swing0::update( Parent *parent, float elapsedTime ){
	GameLib::Input::Mouse m;

	if( m.isOn(m.BUTTON_RIGHT) ){
		mPushingButtonTime+=elapsedTime;
		return this;
	} else {
		if( mModel->isAnimOver() ){
			return new Swing1( parent, mPushingButtonTime );
		} else {
			return new Stand(parent);
		}
	}

	return this;
}


} } } }//GameObject::PlayerUtils::Updater::TameSword
