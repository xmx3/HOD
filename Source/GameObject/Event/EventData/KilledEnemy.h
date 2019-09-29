#pragma once

#include"Event/MyEvent.h"
#include"RTTI/RTTI.h"
#include"GameObject/Enemy.h"


namespace GameObject{
namespace Event {
namespace EventData {
	class KilledEnemy;
	typedef std::shared_ptr<KilledEnemy> KilledEnemySharedPtr;


class KilledEnemy : public IEventData {
public:
	
	static IEventDataPtr create( EnemySharedPtr enemy ){
		IEventDataPtr ev( new KilledEnemy(enemy) );
		return ev;
	}

	KilledEnemy(EnemySharedPtr obj)
		:mObj(obj)
	{}
	virtual ~KilledEnemy(){}
	RTTI_HEADER_IMPL(KilledEnemy);

	EnemySharedPtr mObj;
};

}// end namespace EventData
}//end namespace Event
}//end namespace GameObject