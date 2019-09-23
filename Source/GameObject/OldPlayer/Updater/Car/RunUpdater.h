#pragma once
#include"GameObject/OldPlayer/Updater/IUpdater.h"

class btVector3;
namespace GameObject{ namespace OldPlayer{
		class Player;
namespace Updater{ namespace Car{

class RunUpdater : public IUpdater {
public:
	static IUpdaterSharedPtr create( Player* player ){
		IUpdaterSharedPtr run( new RunUpdater( player ) );
		return run;
	}
	virtual State getState()const{
		return CAR_RUN;
	}
	virtual ~RunUpdater();
	void update( float elapsedTime );
	void onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );
private:
	RunUpdater(Player*);

};
} } } }

