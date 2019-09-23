#ifndef __GAMEOBJECT_EVENT_EVENTDATA_REMOVEFROMWORLD_H__
#define __GAMEOBJECT_EVENT_EVENTDATA_REMOVEFROMWORLD_H__
#include"Event/MyEvent.h"
#include"RTTI/RTTI.h"
#include"GameObject/BaseObject.h"
#include<memory>
namespace GameObject{
namespace Event {
namespace EventData {
	class RemoveFromWorld;
	typedef std::shared_ptr<RemoveFromWorld> RemoveFromWorldSharedPtr;
class RemoveFromWorld : public IEventData {
public:
	static IEventDataPtr create(GameObject::BaseObjectObjectSharedPtr obj ){
		IEventDataPtr ev( new RemoveFromWorld(obj) );
		return ev;
	}
	RemoveFromWorld(GameObject::BaseObjectObjectSharedPtr o)
		:mObj(o)
	{}
	virtual ~RemoveFromWorld(){}
	RTTI_HEADER_IMPL(RemoveFromWorld);

	GameObject::BaseObjectObjectSharedPtr mObj;

	RemoveFromWorld(const RemoveFromWorld &) = delete;
	void operator=(const RemoveFromWorld &) = delete;

};

}// end namespace EventData
}//end namespace Event
}//end namespace GameObject


#endif//__GAMEOBJECT_EVENT_EVENTDATA_REMOVEFROMWORLD_H__