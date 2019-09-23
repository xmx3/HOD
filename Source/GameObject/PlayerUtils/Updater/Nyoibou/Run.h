#pragma once
#include"Child.h"
#include"../PointMover.h"

namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Nyoibou {

class Run : public Child , protected PointMover {
public:
	Run( Parent* );
	virtual ~Run();

	virtual Base* update( Parent*, float elapsedTime );

	float mTime;
};

} } } } //GameObject::PlayerUtils::Updater::Nyoibou
