#ifndef __PHYSiCS_EVENT_LISTENER_H__
#define __PHYSiCS_EVENT_LISTENER_H__
#include "Event/MyEvent.h"

class PhysicsEventListener : public IEventListener {
public:
	PhysicsEventListener(){};
	virtual ~PhysicsEventListener(){};

	virtual char const * getName(void){
		return "PhysicsEventListener";
	}
	virtual bool handleEvent( IEventData const & ev );

	//ƒCƒxƒ“ƒg‚ª‘Î‰‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©ŒŸØ³‚µ‚¯‚ê‚Îtrue
	virtual bool validateEventType( EventType const &ev ) const;

};

#endif