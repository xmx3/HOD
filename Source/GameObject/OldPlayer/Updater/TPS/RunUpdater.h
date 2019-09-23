#ifndef __GAMEOBJECT_OLDPLAYER_UPDATER_TPS_RUNUPDATER_H__
#define __GAMEOBJECT_OLDPLAYER_UPDATER_TPS_RUNUPDATER_H__
#include"GameObject/OldPlayer/Updater/IUpdater.h"
class btVector3;
namespace GameObject{
	namespace OldPlayer{
		class Player;
		namespace Updater{
			namespace TPS{

class RunUpdater : public IUpdater {
public:
	static IUpdaterSharedPtr create( Player* player ){
		IUpdaterSharedPtr run( new RunUpdater( player ) );
		return run;
	}
	virtual State getState()const{
		return TPS_RUN;
	}
	virtual ~RunUpdater();
	virtual void update( float elapsedTime );
private:
	RunUpdater(Player*);

};

}//end namespaces
}
}
}

#endif
