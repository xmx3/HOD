#pragma once
#include"Child.h"
#include"../PointMover.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace TameSword {

class Run : public Child , protected PointMover {
public:
	Run( Parent* );
	~Run();

	Base* update( Parent*, float elapsedTime );

};

} } } } //GameObject::PlayerUtils::Updater::TameSword
