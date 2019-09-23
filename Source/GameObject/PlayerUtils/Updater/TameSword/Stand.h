#pragma once
#include"Child.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace TameSword {

class Stand : public Child  {
public:
	Stand( Parent* );
	~Stand();

	Base* update( Parent*, float elapsedTime );
};

} } } }//GameObject::PlayerUtils::Updater::TameSword
