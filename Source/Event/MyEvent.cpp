#include"MyEvent.h"

#include<Windows.h>
#include<assert.h>
//RTTI_ROOT_IMPL( IEventData );

// EventManager

//
// EventManager::EventManager		 - Chapter 10, page 290
//
EventManager::EventManager(	char const * const pName )
: IEventManager(pName),m_activeQueue(0)
{}


//
// EventManager::~EventManager		 - Chapter 10, page 290
//
EventManager::~EventManager()
{
	m_activeQueue = 0;
}

//
// EventManager::addListener		 - Chapter 10, page 290
//
// Register a listener for a specific event type, implicitly the
// event type will be added to the known event types if not
// already known.
//
// The function will return false on failure for any reason. The
// only really anticipated failure reason is if the input event
// type is bad ( e.g.: known-ident number with different
// signature text, or signature text is empty )
	
bool EventManager::addListener (
	IEventListenerPtr const & inListener,
	EventType const & inType )
{
	if ( ! validateType( inType ) ){ return false; }
	if ( ! inListener->validateEventType( inType ) ){ return false; }

	//Eventを探す。範囲(pair)で返す。boostのRange使うともっとわかりやすく書きやすいかも
	EventListenerMapIteratorPair FirstEndPair = m_registry.equal_range(&inType);
	EventListenerMap::const_iterator itFirst = FirstEndPair.first;
	EventListenerMap::const_iterator itEnd = FirstEndPair.second;
	
	for( EventListenerMap::const_iterator it = itFirst ; it!=itEnd ; ++it )
	{
		//２重登録を防ぐため
		//同じものを登録しようとしたらfalse
		if( inListener==(*it).second ){ return false; }
	}
	
	//イベント名被ってないからオッケ。
	//for内部を回ってきた場合、イベント名は被っているけど、ListenerPtrは違うからok。
	EventListenerMapElement el( &inType, inListener );
	m_registry.insert( el );
	return true;
}


//
// EventManager::deleteListener		- Chapter 10, page 292
//
// Remove a listener/type pairing from the internal tables
//
// Returns false if the pairing was not found.
//
bool EventManager::deleteListener (
	IEventListenerPtr const & inListener, EventType const & inType )
{
	if ( ! validateType( inType ) ){ return false; }

	//Eventを探す。範囲(pair)で返す。boostのRange使うともっとわかりやすく書きやすいかも
	EventListenerMapIteratorPair FirstEndPair = m_registry.equal_range( &inType );
	EventListenerMap::const_iterator itFirst = FirstEndPair.first;
	EventListenerMap::const_iterator itEnd = FirstEndPair.second;
	
	//ソースコード見てconstを除外する必要性がないと思ったので、コメントアウト
	//EffectiveSTL27項　const_iterator を　iteratorにするには
	//EventListenerMap::iterator it( m_registry.begin() );
	//advance( it , std::distance<EventListenerMap::const_iterator>( it , itFirst ) );
	EventListenerMap::const_iterator it( itFirst );	
	for(;it!=itEnd ; ++it )
	{
		//イベントとlistenerPtrが一致したので消去
		if( inListener==(*it).second )
		{	
			m_registry.erase(it);
			return true;
		}
	}

	//イベントはあったけどListenerPtrがありませんでした
	return false;
}


//
// EventManager::trigger		- Chapter 10, page 293
//
// Fire off event - synchronous - do it NOW kind of thing -
// analogous to Win32 SendMessage() API.
//
// returns true if the event was consumed, false if not. Note
// that it is acceptable for all event listeners to act on an
// event and not consume it, this return signature exists to
// allow complete propogation of that shred of information from
// the internals of this system to outside uesrs.
//
bool EventManager::trigger (
	IEventData const & inEvent ) const
{
	if ( ! validateType( inEvent.getEventType() ) ){ return false; }

	//Eventを探す。範囲(pair)で返す。boostのRange使うともっとわかりやすく書きやすいかも
	EventListenerMapIteratorPair FirstEndPair =
		m_registry.equal_range( &(inEvent.getEventType()) );

	EventListenerMap::const_iterator itFirst = FirstEndPair.first;
	EventListenerMap::const_iterator itEnd = FirstEndPair.second;

	bool result = false;
	
	for( EventListenerMap::const_iterator it = itFirst ; it!=itEnd ; ++it )
	{
		IEventListenerPtr listener = (*it).second;
		if ( listener->handleEvent( inEvent ) )
		{
			result = true;
		}
	}
	//そんなイベントに対応するlistenerありません、
	//for内部を通ってきた場合、イベントに対応するlistenerはあったんだけど,
	//listener->handleEvent( inEvent )ないでうまくいきませんでしたという場合もある
	return result;
}

//
// EventManager::queueEvent			- Chapter 10, page 294
//
// Fire off event - asynchronous - do it WHEN the event system
// tick() method is called, normally at a judicious time during
// game-loop processing.
//
// returns true if the message was added to the processing queue,
// false otherwise.
//
bool EventManager::queueEvent ( IEventDataPtr const & inEvent )
{
	assert ( m_activeQueue >= 0 );
	assert ( m_activeQueue < kNumQueues );

	if ( ! validateType( inEvent->getEventType() ) ){ return false; }

	//Eventを探す。
	EventListenerMap::const_iterator it = m_registry.find( &inEvent->getEventType() );
	//そんなイベントありませんのでキューに入れません
	if( it==m_registry.end() )
	{
		return false;
	}

	m_queues[m_activeQueue].push_back( inEvent );
	
	return true;
}


// EventManager::abortEvent			- Chapter 10, page 295
//
// Find the next-available instance of the named event type and
// remove it from the processing queue.
//
// This may be done up to the point that it is actively being
// processed ...  e.g.: is safe to happen during event processing
// itself.
//
// returns true if the event was found and removed, false
// otherwise
//
bool EventManager::abortEvent ( EventType const & inType,
											bool allOfType )
{
	assert ( m_activeQueue >= 0 );
	assert ( m_activeQueue < kNumQueues );

	if ( ! validateType( inType ) )
		return false;
	
	EventQueue &evtQueue = m_queues[m_activeQueue];

	bool result=false;

	for ( EventQueue::iterator it = evtQueue.begin(),
			  itEnd = evtQueue.end(); it != itEnd; )
	{
		if ( (*it)->getEventType().isExactly( inType ) )
		{
			it = evtQueue.erase(it);
			result = true;
			if ( !allOfType )
				break;
		}
		else
		{
			++it;
		}
	}

	return result;
}

//
// EventManager::tick			- Chapter 10, page 296
// EventManager::tick			- Chapter 18, page 671  (for the threadsafe stuff)								
//
// Allow for processing of any queued messages, optionally
// specify a processing time limit so that the event processing
// does not take too long. Note the danger of using this
// artificial limiter is that all messages may not in fact get
// processed.
//
// returns true if all messages ready for processing were
// completed, false otherwise (e.g. timeout )
//
bool EventManager::tick ( unsigned long maxMillis )
{
	unsigned long curMs = GetTickCount();
	unsigned long maxMs =
		maxMillis == IEventManager::kINFINITE
		? IEventManager::kINFINITE
		: (curMs + maxMillis );
	
	// swap active queues, make sure new queue is empty after the
	// swap ...
	
	int queueToProcess = m_activeQueue;

	m_activeQueue = ( m_activeQueue + 1 ) % kNumQueues;

	assert( m_queues[m_activeQueue].empty() );
	m_queues[m_activeQueue].clear();//空だと思うが一応クリア

	// now process as many events as we can ( possibly time
	// limited ) ... always do AT LEAST one event, if ANY are
	// available ...

	while ( m_queues[queueToProcess].size() > 0 )
	{
		IEventDataPtr ev = m_queues[queueToProcess].front();

		m_queues[queueToProcess].pop_front();
		
		EventType const & eventType = ev->getEventType();

		//Eventを探す。範囲(pair)で返す。boostのRange使うともっとわかりやすく書きやすいかも
		EventListenerMapIteratorPair FirstEndPair = m_registry.equal_range( &eventType );
		EventListenerMap::const_iterator itFirst = FirstEndPair.first;
		EventListenerMap::const_iterator itEnd = FirstEndPair.second;

		for( EventListenerMap::const_iterator it = itFirst ; it!=itEnd ; ++it )
		{
			IEventListenerPtr listener = (*it).second;
			listener->handleEvent(*ev);
		}

		curMs = GetTickCount();

		if ( maxMillis != IEventManager::kINFINITE )
		{

			if ( curMs >= maxMs )
			{
				// time ran about, abort processing loop
				break;
			}
		}
	}
	
	// if any events left to process, push them onto the active
	// queue.
	//
	// Note: to preserver sequencing, go bottom-up on the
	// raminder, inserting them at the head of the active
	// queue...

	bool queueFlushed = ( m_queues[queueToProcess].size() == 0 );

	if ( !queueFlushed )
	{
		while ( m_queues[queueToProcess].size() > 0 )
		{
			IEventDataPtr spEv = m_queues[queueToProcess].back();

			m_queues[queueToProcess].pop_back();

			m_queues[m_activeQueue].push_front( spEv );
		}
	}
	
	// all done, this pass
	
	return queueFlushed;
}

// --- information lookup functions ---

//
// EventManager::validateType			- Chapter 10, page 299
//
// Validate an event type, this does NOT add it to the internal
// registry, only verifies that it is legal ( e.g. either the
// ident number is not yet assigned, or it is assigned to
// matching signature text, and the signature text is not empty
// ).
//
bool EventManager::validateType(
	EventType const & inType ) const
{
	if( 0 == inType.getClassName().length() )
	{
		return false;
	}

	//if( inType.isExactly(IEventData::rtti) ){
	//	assert( false && "overwrite getRTTI()!" );
	//	return false;
	//}

	return true;
}