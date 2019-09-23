#ifndef __ANIMATIONSTATE_DEFAULT_H__
#define __ANIMATIONSTATE_DEFAULT_H__
#include"BaseAnimationState.h"
#include"IAnimationState.h"
#include<assert.h>
#include"../AnimationModel.h"
class CModel;
struct D3DXMATRIX;

namespace MMD {
namespace AnimationState {

//次の状態が立ち状態ならば、移行する。移行条件がかなりぬるいので、アニメーションに破綻をきたすかも
class Default : public BaseAnimationState {
public:
	
	//こっちのほうがわかりやすいか？
	//Default* animationState = model->loadVmd( vmdFileName, isWeightBlend, isRepeat, isStand );
	Default( AnimationModel *model, const char *vmdFileName, bool isWeightBlend, bool isRepeat, bool isStand, IAnimationState *nextState=NULL )
		:BaseAnimationState( model->loadVMD( vmdFileName ), vmdFileName ),
		mIsRepeat(isRepeat),
		mIsWeightBlend(isWeightBlend),
		mIsStand(isStand)
	{
		assert( !(isRepeat && nextState) && "繰り返しありと次のアニメーションは両立しません" );

		mNextState=nextState;
	}


	virtual ~Default(){}

	//変わらないならthisを返す。
	virtual IAnimationState* stepTime( float elapsedTime, CModel *model ){
		return defalut_stepTime( elapsedTime, model );
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

	virtual bool isOver( CModel *model ){
		return default_isOver(model);
	}

	virtual bool isWeightBlend() const {
		return mIsWeightBlend;
	}
	
	virtual bool isRepeat() const {
		return mIsRepeat;
	}

	bool mIsWeightBlend;
	bool mIsRepeat;
	bool mIsStand;
};

}
}
#endif //__ANIMATIONSTATE_DEFAULT_H__