#include"StateMachine.h"
#include"StateMachineImpl.h"
#include<assert.h>
#include"GameObject/Player.h"
namespace FSM {

namespace Player {


StateMachine::StateMachine( GameObject::Player* player )
	:mImpl( new Impl ),
	mPlayer(player)
{}

StateMachine::~StateMachine(){
	delete mImpl;
	mImpl=NULL;
}

void StateMachine::process_event( const EvClickedNearEnemy &ev ){
	const State temp = current_state();
	mImpl->process_event( ev );
	const State current  = current_state();

	if( temp != current ){
		informChangeState( current );
	}
}
void StateMachine::process_event( const EvClickedFarEnemy &ev ){
	const State temp = current_state();
	mImpl->process_event( ev );
	const State current  = current_state();

	if( temp != current ){
		informChangeState( current );
	}
}

void StateMachine::process_event( const EvApproachedEnemy &ev ){
	const State temp = current_state();
	mImpl->process_event( ev );
	const State current  = current_state();

	if( temp != current ){
		informChangeState( current );
	}
}

void StateMachine::process_event( const EvAttackEnd &ev ){
	const State temp = current_state();
	mImpl->process_event( ev );
	const State current  = current_state();

	if( temp != current ){
		informChangeState( current );
	}
}

void StateMachine::process_event( const EvAnimationEnd &ev ){
	const State temp = current_state();
	mImpl->process_event( ev );
	const State current  = current_state();

	if( temp != current ){
		informChangeState( current );
	}
}

void StateMachine::process_event( const EvClickedEmptyPos &ev ){
	const State temp = current_state();
	mImpl->process_event( ev );
	const State current  = current_state();

	if( temp != current ){
		informChangeState( current );
	}
}

void StateMachine::process_event( const EvArrivedAtTargetPos &ev ){
	const State temp = current_state();
	mImpl->process_event( ev );
	const State current  = current_state();

	if( temp != current ){
		informChangeState( current );
	}
}

//void StateMachine::process_event( const EvStand &ev ){
//	mImpl->process_event( ev );
//}

void StateMachine::process_event( const EvOveredStaggerValue &ev ){
	const State temp = current_state();
	mImpl->process_event( ev );
	const State current  = current_state();

	if( temp != current ){
		informChangeState( current );
	}
}

void StateMachine::process_event( const EvOveredDownValue &ev ){
	const State temp = current_state();
	mImpl->process_event( ev );
	const State current  = current_state();

	if( temp != current ){
		informChangeState( current );
	}
}

void StateMachine::process_event( const EvCollided &ev ){
	const State temp = current_state();
	mImpl->process_event( ev );
	const State current  = current_state();

	if( temp != current ){
		informChangeState( current );
	}
}

State StateMachine::current_state(){
	return mImpl->current_state();
}

void StateMachine::start(){
	mImpl->start();
}
//impl_tのactionでやったほうが良いんだろうけど、(現在と過去の状態を調べる必要ないし）
//なんとなく、playerをImpl_tに結び付けたくなかった；
void StateMachine::informChangeState( const State & state ){
	mPlayer->changeState( state );
}

}// end namespace Player
}// end namespace FSM