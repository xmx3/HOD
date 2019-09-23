#pragma once
#include"Child.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Nyoibou {

class Stand : public Child  {
public:
	Stand( Parent* );
	virtual ~Stand();

	virtual Base* update( Parent*, float elapsedTime );
};

} } } }//GameObject::PlayerUtils::Updater::Nyoibou
