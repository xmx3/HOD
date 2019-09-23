#ifndef __GAMEOBJECT_EVENT_EVENTDATA_DEFEATEDALLENEMIES_H__
#define __GAMEOBJECT_EVENT_EVENTDATA_DEFEATEDALLENEMIES_H__
#include"Event/MyEvent.h"
#include"RTTI/RTTI.h"

namespace GameObject{
namespace Event {
namespace EventData {
	class DefeatedAllEnemies;
	typedef std::shared_ptr<DefeatedAllEnemies> DefeatedAllEnemiesSharedPtr;


class DefeatedAllEnemies : public IEventData {
public:
	static IEventDataPtr create(){
		IEventDataPtr ev(new DefeatedAllEnemies);
		return ev;
	}
	DefeatedAllEnemies(){}
	virtual ~DefeatedAllEnemies(){}
	RTTI_HEADER_IMPL(DefeatedAllEnemies);
};

}// end namespace EventData
}//end namespace Event
}//end namespace GameObject


#endif//__GAMEOBJECT_EVENT_EVENTDATA_DEFEATEDALLENEMIES_H__