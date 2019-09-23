#pragma once
#include"Event/MyEvent.h"
#include"GameObject/Event/EventData/AddToWorld.h"
#include"GameObject/Event/Manager.h"
namespace GameObject{
namespace Event{
namespace Listener{
	
class AddToWorldListener : public IEventListener {
public:
	static IEventListenerPtr create(){
		IEventListenerPtr listener(new AddToWorldListener);
		return listener;
	} 
	AddToWorldListener(){}
	virtual ~AddToWorldListener(){}

	virtual char const * getName(void){
		return "GameObject::AddToWorldListener";
	}

	
	virtual bool handleEvent( IEventData const & ev )
	{
		using EventData::AddToWorld;
		const AddToWorld *a = dynamic_cast<const AddToWorld *>(&ev);
		if(!a){
			return false;
		}
		Manager *m=Manager::instance();
		m->add(a->mObj);
		return true;
	}


	//ƒCƒxƒ“ƒg‚ª‘Î‰‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©ŒŸØ³‚µ‚¯‚ê‚Îtrue
	virtual bool validateEventType( EventType const &ev ) const{
		return ev.isExactly( EventData::AddToWorld::rtti() );
	}

private:
	AddToWorldListener( const AddToWorldListener & );
	void operator=( const AddToWorldListener & );
};
}//end namespace Listener
}//end namespace Event
}//end namespace GameObject

