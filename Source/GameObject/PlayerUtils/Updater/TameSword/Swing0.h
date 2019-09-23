#pragma once
#include"Child.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace TameSword {

class Swing0 : public Child  {
public:
	Swing0( Parent* );
	~Swing0();

	Base* update( Parent*, float elapsedTime );
private:
	float mPushingButtonTime;
};

} } } }//GameObject::PlayerUtils::Updater::TameSword
