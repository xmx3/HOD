#pragma once
#include"GameObject/OldPlayer/Updater/IUpdater.h"
namespace GameObject{ namespace OldPlayer{
		class Player;
namespace Updater{ namespace Car {

class StandUpdater : public IUpdater {
public:
	static IUpdaterSharedPtr create( Player* player ){
		IUpdaterSharedPtr stand( new StandUpdater( player ) );
		return stand;
	}
	virtual ~StandUpdater();
	virtual State getState()const{
		return CAR_STAND;
	}

	virtual void update( float elapsedTime );
private:
	StandUpdater(Player* player);
	float mCoolTime;
};

} } } } //GameObject::Player::Updater::Car




