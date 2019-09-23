#pragma once
#include"Child.h"

class btRigidBody;
namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Nyoibou {

class Fall : public Child  {
public:
	Fall( Parent* );
	virtual ~Fall();

	virtual Base* update( Parent*, float elapsedTime );

};

} } } }//GameObject::PlayerUtils::Updater::Nyoibou
