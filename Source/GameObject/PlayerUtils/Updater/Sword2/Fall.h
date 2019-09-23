#pragma once
#include"Child.h"

class btRigidBody;
namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Sword2 {

class Fall : public Child  {
public:
	Fall( Parent* );
	~Fall();

	Base* update( Parent*, float elapsedTime );
private:
	MME::Object::ModelKai *mModel;
	Input::PlayerMouse *mMouse;
	btRigidBody *mRigidBody;
};

} } } }//GameObject::PlayerUtils::Updater::Sword2