#ifndef __GAMEOBJECT_OLDPLAYER_UPDATER_TPS_STEP_H__
#define __GAMEOBJECT_OLDPLAYER_UPDATER_TPS_STEP_H__
#include"GameObject/OldPlayer/Updater/IUpdater.h"
class btVector3;
namespace GameObject{
	namespace OldPlayer{
		class Player;
		namespace Updater{
			namespace TPS{

class StepUpdater : public IUpdater {
public:
	static IUpdaterSharedPtr create( Player* player ){
		IUpdaterSharedPtr step( new StepUpdater( player ) );
		return step;
	}
	virtual State getState()const{
		return TPS_STEP;
	}
	virtual ~StepUpdater();
	virtual void update( float elapsedTime );
private:
	StepUpdater(Player*);
};
			}
		}
	}
}

#endif
