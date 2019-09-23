#pragma once

#include"GameObject/OldPlayer/Updater/IUpdater.h"
class btVector3;
namespace GameObject{
	namespace OldPlayer{
		class Player;
		namespace Updater{
			namespace QuarterView{

class SwingUpdater : public IUpdater {
public:
	static IUpdaterSharedPtr create( Player* player ){
		IUpdaterSharedPtr swing( new SwingUpdater( player ) );
		return swing;
	}
	virtual State getState()const{
		return QV_SWING;
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