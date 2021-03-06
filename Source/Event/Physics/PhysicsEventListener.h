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

	//イベントが対応しているかどうか検証正しければtrue
	virtual bool validateEventType( EventType const &ev ) const;

};

#endif