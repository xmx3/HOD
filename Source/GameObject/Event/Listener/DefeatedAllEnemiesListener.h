#ifndef __GAMEOBJECT_EVENT_LISTENER_DEFEATDALLENEMIESLISTENER_H__
#define __GAMEOBJECT_EVENT_LISTENER_DEFEATDALLENEMIESLISTENER_H__

#include"Event/MyEvent.h"
#include"GameObject/Event/Manager.h"
#include"GameObject/Stage.h"
#include"GameObject/Event/EventData/DefeatedAllEnemy.h"
#include"GameObject/BaseObject.h"
#include<assert.h>

namespace GameObject{
namespace Event{
namespace Listener{
	
class DefeatedAllEnemiesListener : public IEventListener {
public:
	static IEventListenerPtr create(StageSharedPtr stage){
		IEventListenerPtr listener( new DefeatedAllEnemiesListener(stage) );
		return listener;
	}
	DefeatedAllEnemiesListener( StageSharedPtr obj )
		:mStage(obj)
	{}

	virtual ~DefeatedAllEnemiesListener(){}

	virtual char const * getName(void){
		return "GameObject::DefeatedAllEnemiesListener";
	}

	virtual bool handleEvent( IEventData const & ev )
	{
		std::shared_ptr<GameObject::Stage> stage = mStage.lock();
		if(stage){
			stage->handleEventThatDefeatedAllEnemies();
			return true;
		} else{
			assert(false);
		}
		return false;
	}


	//ƒCƒxƒ“ƒg‚ª‘Î‰‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©ŒŸØ³‚µ‚¯‚ê‚Îtrue
	virtual bool validateEventType( EventType const &ev ) const{
		return ev.isExactly( EventData::DefeatedAllEnemies::rtti() );
	}

private:
	DefeatedAllEnemiesListener( const DefeatedAllEnemiesListener & )=delete;
	void operator=( const DefeatedAllEnemiesListener & )=delete;

	std::weak_ptr<GameObject::Stage> mStage;
};
}//end namespace Listener
}//end namespace Event
}//end namespace GameObject
#endif 

