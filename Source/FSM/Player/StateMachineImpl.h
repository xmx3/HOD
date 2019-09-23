#ifndef __FSM_PLAYER_STATEMACHINEIMPL_H__
#define __FSM_PLAYER_STATEMACHINEIMPL_H__

#include"EventAndEnum.h"

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50

#include <boost/msm/back/state_machine.hpp>

#include <iostream>
#include <string>
#include <boost/msm/front/state_machine_def.hpp>
//#include "helper/MyOutputDebugString.h"

namespace FSM {

namespace Player {



namespace {

struct Standing_t : public boost::msm::front::state<> {
};

struct Running_t : public boost::msm::front::state<> {
};

struct Chasing_t : public boost::msm::front::state<> {
};

struct AttackingShortRange_t : public boost::msm::front::state<> {
};

struct AttackingLongRange_t : public boost::msm::front::state<> {
};

struct Staggering_t : public boost::msm::front::state<> {
};

struct Lying_t : public boost::msm::front::state<> {};

} // end anonymous namespace
 
struct Impl_t : public boost::msm::front::state_machine_def<Impl_t> {
	//void updateStanding(const EvUpdate & ev){
	//}

	//void updateRunning(const EvUpdate & ev){
	//}

	//void updateChasing(const EvUpdate & ev){
	//}

	//void updateAttackingShortRange(const EvUpdate & ev){
	//}

	//void updateAttackingLongRange(const EvUpdate & ev){
	//}

	//void updateStumbling(const EvUpdate & ev){
	//}	

	struct transition_table : public boost::mpl::vector<
		//		Start       Event					Next         Action                Guard
        //		+-----------+----------------------+---------------+---------------------+----------------------+
		//a_row<	Standing,	EvUpdate,			Standing,		&updateStanding								>,
		_row<	Standing_t,	EvClickedNearEnemy,		Chasing_t													>,
		_row<	Standing_t,	EvClickedFarEnemy,		AttackingLongRange_t										>,
		_row<	Standing_t,	EvClickedEmptyPos,		Running_t													>,
		_row<	Standing_t,	EvOveredStaggerValue,	Staggering_t												>,
		_row<	Standing_t,	EvOveredDownValue,		Lying_t														>,
		
		//a_row<	Running,	EvUpdate,			Running,		&updateRunning								>,
		_row<	Running_t,	EvArrivedAtTargetPos,	Standing_t													>,
		_row<	Running_t,	EvClickedNearEnemy,		Chasing_t													>,
		_row<	Running_t,	EvClickedFarEnemy,		AttackingLongRange_t										>,
		_row<	Running_t,	EvClickedEmptyPos,		Running_t													>,
		_row<	Running_t,	EvOveredStaggerValue,	Staggering_t												>,
		_row<	Running_t,	EvOveredDownValue,		Lying_t														>,
		_row<	Running_t,	EvCollided,				Standing_t													>,
		
		//a_row<	Chasing,	EvUpdate,			Chasing,		&updateChasing								>,
		_row<	Chasing_t,	EvClickedNearEnemy,		Chasing_t													>,//キャンセルあり？//ゲームバランス変わる
		_row<	Chasing_t,	EvClickedEmptyPos,		Running_t													>,//キャンセルあり？
		_row<	Chasing_t,	EvApproachedEnemy,		AttackingShortRange_t										>,
		_row<	Chasing_t,	EvOveredStaggerValue,	Staggering_t												>,
		_row<	Chasing_t,	EvOveredDownValue,		Lying_t														>,
		_row<	Chasing_t,	EvCollided,				Standing_t													>,
		
		//		Start					Event					Next					Action		                Guard
        //		+----------------------+------------------------+-----------------------+--------------------------+----------------------+
		//a_row<	AttackingShortRange,	EvUpdate,			AttackingShortRange,	&updateAttackingShortRange						>,
		_row<	AttackingShortRange_t,	EvAttackEnd,			Standing_t																>,
		_row<	AttackingShortRange_t,	EvOveredStaggerValue,	Staggering_t															>,
		_row<	AttackingShortRange_t,	EvOveredDownValue,		Lying_t																	>,
		
		//a_row<	AttackingLongRange,		EvUpdate,			AttackingLongRange,		&updateAttackingLongRange						>,
		_row<	AttackingLongRange_t,	EvAttackEnd,			Standing_t																>,
		_row<	AttackingLongRange_t,	EvOveredStaggerValue,	Staggering_t															>,
		_row<	AttackingLongRange_t,	EvOveredDownValue,		Lying_t																	>,
		
		//a_row<	Staggering,	EvUpdate,		Staggering,	&updateStumbling							>,
		_row<	Staggering_t,			EvAnimationEnd,			Standing_t								>,
		_row<	Staggering_t,			EvOveredDownValue,		Lying_t									>,
		
		_row<	Lying_t,				EvAnimationEnd,			Standing_t								>
        //		+----------------------+------------------------+-----------------------+--------------------------+----------------------+

	> {};
	typedef Standing_t initial_state;

	// イベントが見つからなかった時に呼ばれる
    template <class FSM,class Event>
    void no_transition(Event const& e, FSM&,int state)
    {
		//TRACE2( "no transition from state %d on event %s\n", state, typeid(e).name() );
    }
};

struct Impl{
	Impl(){}
	~Impl(){}
	void start()
	{
		mStateMachine.start();
	}
	//コンパイル時間長いので強制的にテンプレートかさせるために型を確定
	//template<class T>
	//void process_event( const T& t){
	//	mStateMachine.process_event(t);
	//}

	void process_event( const EvClickedNearEnemy& t ){
		mStateMachine.process_event(t);
	}
	void process_event( const EvClickedFarEnemy& t ){
		mStateMachine.process_event(t);
	}

	void process_event( const EvApproachedEnemy& t ){
		mStateMachine.process_event(t);
	}
	void process_event( const EvAttackEnd& t ){
		mStateMachine.process_event(t);
	}
	void process_event( const EvAnimationEnd& t ){
		mStateMachine.process_event(t);
	}
	void process_event( const EvClickedEmptyPos& t ){
		mStateMachine.process_event(t);
	}
	void process_event( const EvArrivedAtTargetPos& t ){
		mStateMachine.process_event(t);
	}
	//void process_event( const EvStand& t ){
	//	mStateMachine.process_event(t);
	//}
	void process_event( const EvOveredStaggerValue& t ){
		mStateMachine.process_event(t);
	}
	void process_event( const EvOveredDownValue& t ){
		mStateMachine.process_event(t);
	}
	void process_event( const EvCollided& t ){
		mStateMachine.process_event(t);
	}

	State current_state(){
		State s = static_cast<State>( *(mStateMachine.current_state()) );
		assert( 0<=s && s<NUM );
		return s;
	}
	boost::msm::back::state_machine<Impl_t> mStateMachine;
};


}// end namespace Player
}// end namespace FSM

#endif