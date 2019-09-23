#pragma once
#include"Child.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Sword2 {

class Swing : public Child  {
public:
	Swing( Parent* );
	~Swing();

	Base* update( Parent*, float elapsedTime );
private:
	MME::Object::ModelKai *mModel;
	Input::PlayerMouse *mMouse;
	int mNumPushedButton;
	int mCurrentActionIndex;
};

} } } }//GameObject::PlayerUtils::Updater::Sword2