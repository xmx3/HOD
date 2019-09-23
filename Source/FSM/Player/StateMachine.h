#ifndef __FSM_PLAYER_STATEMACHINE_H__
#define __FSM_PLAYER_STATEMACHINE_H__

#include"EventAndEnum.h"

namespace GameObject{
	class Player;
}

namespace FSM {

namespace Player {
struct Impl;

//boost::msmégÇ§Ç∆ìÆìIÇ…çÏÇÍÇ»Ç¢ÇÃÇ™Ç¢ÇΩÇ¢Ç»Å[
class StateMachine {
public:
	StateMachine( GameObject::Player* );
	~StateMachine();
	void start();
	void process_event( const EvClickedNearEnemy& );
	void process_event( const EvClickedFarEnemy& );
	void process_event( const EvApproachedEnemy& );
	void process_event( const EvAttackEnd& );
	void process_event( const EvAnimationEnd& );
	void process_event( const EvClickedEmptyPos& );
	void process_event( const EvArrivedAtTargetPos& );
	//void process_event( const EvStand& );
	void process_event( const EvOveredStaggerValue& );
	void process_event( const EvOveredDownValue& );
	void process_event( const EvCollided& );
	State current_state();
private:
	void informChangeState( const State & state );

	Impl *mImpl;
	GameObject::Player *mPlayer;
};


}// end namespace Player
}// end namespace FSM
#endif
