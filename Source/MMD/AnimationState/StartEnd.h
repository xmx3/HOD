#ifndef __ANIMATIONSTATE_STARTEND_H__
#define __ANIMATIONSTATE_STARTEND_H__
#include"BaseAnimationState.h"
#include"IAnimationState.h"
#include<assert.h>
#include"../AnimationModel.h"

class CModel;
struct D3DXMATRIX;

namespace MMD {
namespace AnimationState {

//アニメーションが破綻を防ぐためため終わりと開始のフレームを設定出来るアニメーション
class StartEnd : public BaseAnimationState {
public:
	//
	explicit StartEnd( AnimationModel *model, const char *vmdName, float restartFrame, float endFrame, bool isWeightBlend=true, bool isRepeat=true, bool isStand=true, IAnimationState *nextState=NULL )
		:BaseAnimationState( model->loadVMD(vmdName), vmdName ),
		mIsRepeat(isRepeat),
		mRestartFrame( restartFrame ),
		mEndFrame( endFrame ),
		mIsWeightBlend(isWeightBlend),
		mIsStand(isStand)
	{
		assert( !(isRepeat && nextState) && "繰り返しありと次のアニメーションは両立しません" );

		mNextState=nextState;
	}
	virtual ~StartEnd(){}

	//変わらないならthisを返す。
	virtual IAnimationState* stepTime( float elapsedTime, CModel *model ){
		return defalut_stepTime( elapsedTime, model, mRestartFrame );
	}
	
	//ホワイトリスト的に実装すること
	//そっちのほうがバグが少ない
	//ホワイトリスト的というのは、確実に信頼できる値のみtrueを返すこと
	//遷移できるものをtrueを返し、その他全部はfalseを返す実装
	//新しい状態を追加した場合、自動的にfalseを返すように
	//でも、この実装めんどいな。
	//立ち状態から遷移できるのは、ブラックリスト的に書くか？
	//とりあえず、出来るだけ、falseを返す実装で
	virtual bool isChangeAble( IAnimationState *nextState, CModel *model ) const {
		if(this==nextState)
		{
			return false;
		}

		if( nextState->isStand() ){
			return true;
		} else {
			return false;
		}
	}
	
	//立ち状態のアニメか？
	virtual bool isStand() const {
		return mIsStand;
	}

	//移行できない場合はthis
	virtual IAnimationState* changeState( IAnimationState* nextState, CModel *model ){
		IAnimationState* next=this;
		if( isChangeAble( nextState, model ) ){
			next=defalut_changeState( nextState, model );
		}
		return next;
	}

	virtual bool isOver( CModel *model );

	virtual bool isWeightBlend() const {
		return mIsWeightBlend;
	}
	
	virtual bool isRepeat() const {
		return mIsRepeat;
	}
private:
	bool mIsWeightBlend;
	bool mIsRepeat;
	bool mIsStand;
	float mRestartFrame;
	float mEndFrame;
};

}
}
#endif //__ANIMATIONSTATE_STARTEND_H__