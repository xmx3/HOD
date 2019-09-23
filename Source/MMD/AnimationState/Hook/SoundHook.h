#pragma once

#include"IHook.h"


namespace boost {
	template<class T> class shared_ptr;
}
namespace GameLib{
	namespace Sound {
		class Wave;
		class Player;
	}
}

namespace MMD{
namespace AnimationState{

	class BaseAnimationState;


namespace Hook {
	class SoundHook;
	typedef std::shared_ptr<SoundHook> SoundHookSharedPtr;

class SoundHook : public IHook {
public:
	static IHookSharedPtr create()
	{
		IHookSharedPtr spHook( new SoundHook() );
		return spHook;
	}
	virtual ~SoundHook();
	virtual void hookUpdate( float currentFrame );
	virtual void hookStart();
	virtual void hookChangeState();
	virtual void hookAnimationOver();
private:
	// use create(). can use only shared_ptr.
	SoundHook();
	//disallow assign
	SoundHook( const SoundHook & );
	//disallow copy
	void operator=( const SoundHook & );
};

}//MMD
}//AnimationState
}//Hook

