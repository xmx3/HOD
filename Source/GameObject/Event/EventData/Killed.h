#pragma once

#include"Event/MyEvent.h"
#include"RTTI/RTTI.h"
#include"GameObject/ICollider.h"


namespace GameObject{
namespace Event {
namespace EventData {
	class Killed;
	typedef std::shared_ptr<Killed> KilledSharedPtr;


class Killed : public IEventData {
public:
	
	static IEventDataPtr create( IColliderSharedPtr obj ){
		IEventDataPtr ev( new Killed(obj) );
		return ev;
	}

	Killed(IColliderSharedPtr obj)
		:mObj(obj)
	{}
	virtual ~Killed(){}
	RTTI_HEADER_IMPL(Killed);

	IColliderSharedPtr mObj;
};

}// end namespace EventData
}//end namespace Event
}//end namespace GameObject