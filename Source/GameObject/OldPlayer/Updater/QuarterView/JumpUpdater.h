#ifndef __GAMEOBJECT_OLDPLAYER_UPDATER_QUARTERVIEW_JUMPUPDATER_H__
#define __GAMEOBJECT_OLDPLAYER_UPDATER_QUARTERVIEW_JUMPUPDATER_H__
#include"GameObject/OldPlayer/Updater/IUpdater.h"
namespace GameObject{
	namespace OldPlayer{
		namespace Updater{
			namespace QuarterView{

class JumpUpdater : public IUpdater {
public:
	static IUpdaterSharedPtr create( Player* player ){
		IUpdaterSharedPtr jump( new JumpUpdater( player ) );
		return jump;
	}
	virtual ~JumpUpdater();
	virtual State getState()const{
		return QV_JUMP;
	}
	virtual void update( float elapsedTime );
private:
	JumpUpdater(Player* player);
};

}
}
}
}

#endif
