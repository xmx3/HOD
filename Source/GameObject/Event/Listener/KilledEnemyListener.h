#pragma once
#include"Event/MyEvent.h"
#include"GameObject/Event/EventData/KilledEnemy.h"
#include"GameObject/Rttis.h"
#include"Sequence/HatuneOfTheDead/LuaImpl/State.h"

namespace GameObject{
namespace Event{
namespace Listener{
	
class KilledEnemyListener : public IEventListener {
public:
	static IEventListenerPtr create(){
		IEventListenerPtr listener(new KilledEnemyListener);
		return listener;
	} 
	KilledEnemyListener(){}
	virtual ~KilledEnemyListener(){}

	virtual char const * getName(void){
		return "GameObject::KilledEnemyListener";
	}

	
	virtual bool handleEvent( IEventData const & ev )
	{
		using EventData::KilledEnemy;
		const KilledEnemy *killed = dynamic_cast<const KilledEnemy *>(&ev);
		if(!killed){
			return false;
		}
		//Enemy *obj = killed->mObj.get();
		Sequence::HatuneOfTheDead::LuaImpl::State::instance()->addScore(100*killed->mObj->getChain());
		return true;
	}


	//ƒCƒxƒ“ƒg‚ª‘Î‰‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©ŒŸØ³‚µ‚¯‚ê‚Îtrue
	virtual bool validateEventType( EventType const &ev ) const{
		return ev.isExactly( EventData::KilledEnemy::rtti() );
	}

private:
	KilledEnemyListener( const KilledEnemyListener & );
	void operator=( const KilledEnemyListener & );
};
}//end namespace Listener
}//end namespace Event
}//end namespace GameObject

