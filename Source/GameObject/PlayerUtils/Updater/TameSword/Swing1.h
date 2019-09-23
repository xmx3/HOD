#pragma once
#include"Child.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace TameSword {

class Swing1 : public Child  {
public:
	Swing1( Parent*, float pushingButtonTime );
	~Swing1();

	Base* update( Parent*, float elapsedTime );
private:
	float mPushingButtonTime;
	float mOriginalScale;
};

} } } }//GameObject::PlayerUtils::Updater::TameSword
