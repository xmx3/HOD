#ifndef __GAMEOBJECT_EVENT_LISTENER_REMOVEFROMWORLDLISTENER_H__
#define __GAMEOBJECT_EVENT_LISTENER_REMOVEFROMWORLDLISTENER_H__
#include"Event/MyEvent.h"
#include"GameObject/Event/EventData/RemoveFromWorld.h"
#include"GameObject/Event/Manager.h"
namespace GameObject{
namespace Event{
namespace Listener{
	
class RemoveFromWorldListener : public IEventListener {
public:
	static IEventListenerPtr create(){
		IEventListenerPtr listener(new RemoveFromWorldListener);
		return listener;
	}
	RemoveFromWorldListener(){}
	virtual ~RemoveFromWorldListener(){}

	virtual char const * getName(void){
		return "GameObject::RemoveFromWorldListener";
	}

	
	virtual bool handleEvent( IEventData const & ev )
	{
		using EventData::RemoveFromWorld;
		const RemoveFromWorld *rfw = dynamic_cast<const RemoveFromWorld *>(&ev);
		if(!rfw){
			return false;
		}
		Manager *m=Manager::instance();
		m->remove(rfw->mObj);
		return true;
	}


	//ƒCƒxƒ“ƒg‚ª‘Î‰‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©ŒŸØ³‚µ‚¯‚ê‚Îtrue
	virtual bool validateEventType( EventType const &ev ) const{
		return ev.isExactly( EventData::RemoveFromWorld::rtti() );
	}

private:
	RemoveFromWorldListener( const RemoveFromWorldListener & );
	void operator=( const RemoveFromWorldListener & );
};
}//end namespace Listener
}//end namespace Event
}//end namespace GameObject
#endif 

