#pragma once
#include"Child.h"
#include"../PointMover.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace SimpleWalker {

class Run : public Child , protected PointMover {
public:
	Run( Parent* );
	~Run();

	Base* update( Parent*, float elapsedTime );
private:
	MME::Object::ModelKai *mModel;
	Input::PlayerMouse *mMouse;
};

} } } }//GameObject::PlayerUtils::Updater::SimpleWalker