#ifndef __FSM_PLAYER_EVENTANDENUM_H__
#define __FSM_PLAYER_EVENTANDENUM_H__
namespace FSM {

namespace Player {

struct EvClickedNearEnemy{};
struct EvClickedFarEnemy{};
struct EvApproachedEnemy{};
struct EvAttackEnd{};
struct EvAnimationEnd{};
struct EvClickedEmptyPos{};
struct EvArrivedAtTargetPos{};
//struct EvStand{};
struct EvOveredStaggerValue{};
struct EvOveredDownValue{};
//struct EvUpdate{};
struct EvCollided{};
struct EvSwing{};
struct EvShot{};
struct EvPunch{};

enum State {
	Standing=0,
	Running,
	Chasing,
	AttackingShortRange,
	AttackingLongRange,
	Staggering,
	Lying,
	NUM,
};

}
}

#endif//__FSM_PLAYER_EVENTANDENUM_H__