#ifndef __GAMEOBJECT_OLDPLAYER_UPDATER_TPS_SWINGUPDATER_H__
#define __GAMEOBJECT_OLDPLAYER_UPDATER_TPS_SWINGUPDATER_H__
#include"GameObject/OldPlayer/Updater/IUpdater.h"
class btVector3;
namespace GameObject{
	namespace OldPlayer{
		class Player;
		namespace Updater{
			namespace TPS{

class SwingUpdater : public IUpdater {
public:
	static IUpdaterSharedPtr create( Player* player ){
		IUpdaterSharedPtr swing( new SwingUpdater( player ) );
		return swing;
	}
	virtual State getState()const{
		return TPS_SWING;
	}
	virtual ~SwingUpdater();
	virtual void update( float elapsedTime );
private:
	SwingUpdater(Player*);
	int mNumClicked;
	int mCurrentAnimIdx;
};
			}
		}
	}
}

#endif
