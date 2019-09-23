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
	static IEventDataPtr create(GameObject::BaseObjectObjectSharedPtr obj ){
		IEventDataPtr ev( new AddToWorld(obj) );
		return ev;
	}

	AddToWorld(GameObject::BaseObjectObjectSharedPtr obj)
		:mObj(obj)
	{}
	virtual ~AddToWorld(){}
	RTTI_HEADER_IMPL(AddToWorld);
	GameObject::BaseObjectObjectSharedPtr mObj;
};

}// end namespace EventData
}//end namespace Event
}//end namespace GameObject

