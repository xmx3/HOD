#ifndef __GAMEOBJECT_OLDPLAYER_UPDATER_TPS_STANDUPDATER_H__
#define __GAMEOBJECT_OLDPLAYER_UPDATER_TPS_STANDUPDATER_H__
#include"GameObject/OldPlayer/Updater/IUpdater.h"
namespace GameObject{
	namespace OldPlayer{
		class Player;
		namespace Updater{
			namespace TPS{

class StandUpdater : public IUpdater {
public:
	static IUpdaterSharedPtr create( Player* player ){
		IUpdaterSharedPtr stand( new StandUpdater( player ) );
		return stand;
	}
	virtual ~StandUpdater();
	virtual State getState()const{
		return TPS_STAND;
	}

	virtual void update( float elapsedTime );
private:
	StandUpdater(Player* player);
	float mCoolTime;
};

}//end namespaces
}
}
}


#endif
