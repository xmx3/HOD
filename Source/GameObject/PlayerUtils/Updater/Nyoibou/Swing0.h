#pragma once
#include"Child.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Nyoibou {

class Swing0 : public Child  {
public:
	Swing0( Parent* );
	virtual ~Swing0();

	virtual Base* update( Parent*, float elapsedTime );
private:
	float mPushingButtonTime;
};

} } } }//GameObject::PlayerUtils::Updater::Nyoibou
