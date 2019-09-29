#pragma once
#include"Event/MyEvent.h"
#include"GameObject/BaseObject.h"
#include<memory>
namespace GameObject{
namespace Event{
namespace EventData {
	class AddToWorld;
	typedef std::shared_ptr<AddToWorld> AddToWorldSharedPtr;
class AddToWorld : public IEventData {
public:
	static IEventDataPtr create(GameObject::BaseObjectSharedPtr obj ){
		IEventDataPtr ev( new AddToWorld(obj) );
		return ev;
	}

	AddToWorld(GameObject::BaseObjectSharedPtr obj)
		:mObj(obj)
	{}
	virtual ~AddToWorld(){}
	RTTI_HEADER_IMPL(AddToWorld);
	GameObject::BaseObjectSharedPtr mObj;
};

}// end namespace EventData
}//end namespace Event
}//end namespace GameObject

