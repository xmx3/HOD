#pragma once
#include"Child.h"

class btRigidBody;
namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace TameSword {

class Fall : public Child  {
public:
	Fall( Parent* );
	~Fall();

	Base* update( Parent*, float elapsedTime );

};

} } } }//GameObject::PlayerUtils::Updater::TameSword
