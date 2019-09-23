#pragma once
#include"Child.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Nyoibou {

class Swing1 : public Child  {
public:
	Swing1( Parent*, float pushingButtonTime );
	virtual ~Swing1();

	virtual Base* update( Parent*, float elapsedTime );
private:
};

} } } }//GameObject::PlayerUtils::Updater::Nyoibou
