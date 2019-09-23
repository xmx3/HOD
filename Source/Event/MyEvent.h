#ifndef __MY_EVENT_H__
#define __MY_EVENT_H__
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "RTTI/RTTI.h"

typedef RTTI EventType;

class IEventData;
typedef std::shared_ptr<IEventData> IEventDataPtr;

class IEventData
{
public:
	explicit IEventData(){}
	virtual ~IEventData(){}
	virtual const RTTI & getRTTI() const = 0;
	//{ 
	//	return rtti;
	//}
    //static const RTTI rtti;

	const EventType& getEventType( void ) const
	{
		return getRTTI();
	}
};



class IEventListener
{
public:

	explicit IEventListener()
	{}

	virtual ~IEventListener()
	{}

	// Returns ascii-text name for this listener, used mostly for
	// debugging
	virtual char const * getName(void) = 0;

	// Return 'false' to indicate that this listener did NOT
	// consume the event, ( and it should continue to be
	// propogated )
	// 					
	// return 'true' to indicate that this listener consumed the
	//event, ( and it should NOT continue to be propgated )
	//
	virtual bool handleEvent( IEventData const & ev ) = 0;


	//ÉCÉxÉìÉgÇ™ëŒâûÇµÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©åüèÿê≥ÇµÇØÇÍÇŒtrue
	virtual bool validateEventType( EventType const &str ) const = 0;
private:
	
};


// IEventManager Description
//
// This is the object which maintains the list of registered
// events and their listeners
//
// This is a many-to-many relationship, as both one listener can
// be configured to process multiple event types and of course
// multiple listeners can be registered to each event type.
//
// The interface to this contruct uses smart pointer wrapped
// objects, the purpose being to ensure that no object that the
// registry is referring to is destoyed before it is removed from
// the registry AND to allow for the registry to be the only
// place where this list is kept ... the application code does
// not need to maintain a second list.
//
// Simply tearing down the registry (e.g.: destroying it) will
// automatically clean up all pointed-to objects ( so long as
// there are no other oustanding references, of course ).

typedef std::shared_ptr<IEventListener>   IEventListenerPtr;

class IEventManager
{
public:

	enum eConstants
	{
		kINFINITE = 0xffffffff
	};

	explicit IEventManager( char const * const pName )
	{}
	
	virtual ~IEventManager()
	{}

	// Register a handler for a specific event type, implicitly
	// the event type will be added to the known event types if
	// not already known.
	//
	// The function will return false on failure for any
	// reason. The only really anticipated failure reason is if
	// the input event type is bad ( e.g.: known-ident number
	// with different signature text, or signature text is empty
	// )
	
	virtual bool addListener ( IEventListenerPtr const & inHandler,
							   EventType const & inType ) = 0;

	// Remove a listener/type pairing from the internal tables
	//
	// Returns false if the pairing was not found.
	
	virtual bool deleteListener ( IEventListenerPtr const & inHandler,
							   EventType const & inType ) = 0;

	// Fire off event - synchronous - do it NOW kind of thing -
	// analogous to Win32 SendMessage() API.
	//
	// returns true if the event was consumed, false if not. Note
	// that it is acceptable for all event listeners to act on an
	// event and not consume it, this return signature exists to
	// allow complete propogation of that shred of information
	// from the internals of this system to outside uesrs.

	virtual bool trigger ( IEventData const & inEvent ) const = 0;

	// Fire off event - asynchronous - do it WHEN the event
	// system tick() method is called, normally at a judicious
	// time during game-loop processing.
	//
	// returns true if the message was added to the processing
	// queue, false otherwise.

	virtual bool queueEvent ( IEventDataPtr const & inEvent ) = 0;

	// Find the next-available instance of the named event type
	// and remove it from the processing queue.
	//
	// This may be done up to the point that it is actively being
	// processed ...  e.g.: is safe to happen during event
	// processing itself.
	//
	// if 'allOfType' is input true, then all events of that type
	// are cleared from the input queue.
	//
	// returns true if the event was found and removed, false
	// otherwise

	virtual bool abortEvent ( EventType const & inType,
							  bool allOfType = false ) = 0;

	// Allow for processing of any queued messages, optionally
	// specify a processing time limit so that the event
	// processing does not take too long. Note the danger of
	// using this artificial limiter is that all messages may not
	// in fact get processed.
	//
	// returns true if all messages ready for processing were
	// completed, false otherwise (e.g. timeout )

	virtual bool tick ( unsigned long maxMillis = kINFINITE ) = 0;

	// --- information lookup functions ---
	
	// Validate an event type, this does NOT add it to the
	// internal registry, only verifies that it is legal (
	// e.g. either the ident number is not yet assigned, or it is
	// assigned to matching signature text, and the signature
	// text is not empty ).

	virtual bool validateType( EventType const & inType ) const = 0;

};


class EventManager : public IEventManager
{
public:

	explicit EventManager( char const * const pName );

	virtual ~EventManager();

	// --- primary use functions --- make it work ---
	
	// Register a listener for a specific event type, implicitly
	// the event type will be added to the known event types if
	// not already known.
	//
	// The function will return false on failure for any
	// reason. The only really anticipated failure reason is if
	// the input event type is bad ( e.g.: known-ident number
	// with different signature text, or signature text is empty
	// )
	
	virtual bool addListener ( IEventListenerPtr const & inListener,
					   EventType const & inType );

	// Remove a listener/type pairing from the internal tables
	//
	// Returns false if the pairing was not found.
	
	virtual bool deleteListener ( IEventListenerPtr const & inListener,
					   EventType const & inType );

	// Fire off event - synchronous - do it NOW kind of thing -
	// analogous to Win32 SendMessage() API.
	//
	// returns true if the event was consumed, false if not. Note
	// that it is acceptable for all event listeners to act on an
	// event and not consume it, this return signature exists to
	// allow complete propogation of that shred of information
	// from the internals of this system to outside uesrs.

	virtual bool trigger ( IEventData const & inEvent ) const;

	// Fire off event - asynchronous - do it WHEN the event
	// system tick() method is called, normally at a judicious
	// time during game-loop processing.
	//
	// returns true if the message was added to the processing
	// queue, false otherwise.

	virtual bool queueEvent ( IEventDataPtr const & inEvent );

	// This was added to allow real time events to be sent into the 
	// event manager.
	
	virtual bool abortEvent ( EventType const & inType,
					  bool allOfType );

	// Allow for processing of any queued messages, optionally
	// specify a processing time limit so that the event
	// processing does not take too long. Note the danger of
	// using this artificial limiter is that all messages may not
	// in fact get processed.
	//
	// returns true if all messages ready for processing were
	// completed, false otherwise (e.g. timeout )

	virtual bool tick ( unsigned long maxMillis );

	// --- information lookup functions ---
	
	// Validate an event type, this does NOT add it to the
	// internal registry, only verifies that it is legal (
	// e.g. either the ident number is not yet assigned, or it is
	// assigned to matching signature text, and the signature
	// text is not empty ).

	virtual bool validateType( EventType const & inType ) const;

private:
	typedef std::multimap< const EventType*, IEventListenerPtr >	EventListenerMap;
	typedef std::pair< const EventType*, IEventListenerPtr  >		EventListenerMapElement;
	typedef std::pair< EventListenerMap::const_iterator , EventListenerMap::const_iterator > EventListenerMapIteratorPair;

	//// queue of pending- or processing-events
	typedef std::list< IEventDataPtr >						EventQueue;

	enum eConstants
	{
		kNumQueues = 2
	};
	
	EventListenerMap m_registry;           // mapping of event types
											// to listeners

	EventQueue       m_queues[kNumQueues]; // event processing queue,
											// double buffered to
											// prevent infinite cycles

	int               m_activeQueue;        // valid denoting which
											// queue is actively
											// processing, en-queing
											// events goes to the
											// opposing queue
};

#endif//__MY_EVENT_H__
