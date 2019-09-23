#ifndef __GAMEOBJECT_OLDPLAYER_UPDATER_TPS_SHOTUPDATER_H__
#define __GAMEOBJECT_OLDPLAYER_UPDATER_TPS_SHOTUPDATER_H__
#include"GameObject/OldPlayer/Updater/IUpdater.h"
class btVector3;
namespace GameObject{
	namespace OldPlayer{
		class Player;
		namespace Updater{
			namespace TPS{

class ShotUpdater : public IUpdater {
public:
	static IUpdaterSharedPtr create( Player* player ){
		IUpdaterSharedPtr shot( new ShotUpdater( player ) );
		return shot;
	}
	virtual State getState()const{
		return TPS_SHOT;
	}
	virtual ~ShotUpdater();
	virtual void update( float elapsedTime );
private:
	ShotUpdater(Player*);
};
			}
		}
	}
}

#endif
