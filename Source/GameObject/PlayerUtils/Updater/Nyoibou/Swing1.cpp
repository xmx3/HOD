#include"Swing1.h"
#include"Stand.h"
#include"Parent.h"
#include<GameLib/Input/Mouse.h>
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"GameObject/Accessory.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Nyoibou {

namespace {
	static const float skPusingShortTime = 1.f/30.f * 3.f; 
	static const float skPusingMiddleTime = 1.f/30.f * 6.f; 
	static const float skPusingLongTime = 1.f/30.f * 9.f; 
	enum {
		kLong,
		kMiddle,
		kShort,
		kVeryShort
	};

	int howLongWasButtonPushed(float time){
		if( time > skPusingLongTime ){
			return kLong;
		} else if( time > skPusingMiddleTime ){
			return kMiddle;
		} else if( time > skPusingShortTime ){
			return kShort;
		} else {
			return kVeryShort;
		}
	}
	 

}//end unnamespace
Swing1::Swing1( Parent* p, float pushingButtonTime  )
	:Child(p)
{
	switch( howLongWasButtonPushed( pushingButtonTime) ){
	case kLong :
		mModel->changeAnimation("nyoibou::swingStrong");
		break;
	case kMiddle :
		mModel->changeAnimation("nyoibou::swingMiddle");
		break;
	case kShort :
		mModel->changeAnimation("nyoibou::swingLow" );
		break;
	case kVeryShort:
		mModel->changeAnimation("nyoibou::swingLow" );
	default :
		mModel->changeAnimation("nyoibou::swingLow" );		
	}
}
Swing1::~Swing1(){}

Base* Swing1::update( Parent *parent, float elapsedTime ){
	//GameLib::Input::Mouse m;

	if( mModel->isAnimOver() ){
		return new Stand(parent);
	}

	return this;

}


} } } }//GameObject::PlayerUtils::Updater::Nyoibou
