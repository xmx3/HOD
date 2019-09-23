#pragma once
#include"Event/MyEvent.h"
#include"GameObject/Event/EventData/Killed.h"
#include"GameObject/ICollider.h"
#include"GameObject/Rttis.h"
namespace GameObject{
namespace Event{
namespace Listener{
	
class KilledListener : public IEventListener {
public:
	static IEventListenerPtr create(){
		IEventListenerPtr listener(new KilledListener);
		return listener;
	} 
	KilledListener(){}
	virtual ~KilledListener(){}

	virtual char const * getName(void){
		return "GameObject::KilledListener";
	}

	
	virtual bool handleEvent( IEventData const & ev )
	{
		using EventData::Killed;
		const Killed *killed = dynamic_cast<const Killed *>(&ev);
		if(!killed){
			return false;
		}
		ICollider *obj = killed->mObj.get();
		if(obj->getRTTI().isExactly( Rttis::Player() )){
			//gameover
		}else if(obj->getRTTI().isExactly( Rttis::Enemy() )){
			//createEffect();
		}else {
			assert(false);
			return false;
		}

		return true;
	}


	//ƒCƒxƒ“ƒg‚ª‘Î‰‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©ŒŸØ³‚µ‚¯‚ê‚Îtrue
	virtual bool validateEventType( EventType const &ev ) const{
		return ev.isExactly( EventData::Killed::rtti() );
	}

private:
	KilledListener( const KilledListener & );
	void operator=( const KilledListener & );
};
}//end namespace Listener
}//end namespace Event
}//end namespace GameObject

