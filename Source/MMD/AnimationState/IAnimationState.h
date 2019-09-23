#ifndef __IANIMATION_STATE_H__
#define __IANIMATION_STATE_H__
struct D3DXMATRIX;
class BaseObject;

#include<memory>

namespace MMD {
	class CModel;
	class Animation;
namespace AnimationState {
namespace Hook{
	class IHook;
	typedef std::shared_ptr<IHook> IHookSharedPtr;
}//MMD::AnimationState::Hook

class IAnimationState{
public:
	virtual ~IAnimationState(){}
	//変わらないならthisを返す。
	virtual IAnimationState* stepTime( float elapsedTime, CModel *model )=0;
	
	//virtual bool load()=0;

	//ホワイトリスト的に実装すること
	//そっちのほうがバグが少ない
	//ホワイトリスト的というのは、確実に信頼できる値のみtrueを返すこと
	//遷移できるものをtrueを返し、その他全部はfalseを返す実装
	//新しい状態を追加した場合、自動的にfalseを返すように
	//でも、この実装めんどいな。
	//立ち状態から遷移できるのは、ブラックリスト的に書くか？
	//とりあえず、出来るだけ、falseを返す実装で
	virtual bool isChangeAble( IAnimationState *pS, CModel *model ) const = 0;
	//立ち状態のアニメか？
	virtual bool isStand() const = 0;

	virtual bool isOver( CModel *model ) =0;

	//接地しているか？
	//実装はik使えそう足の長さのやつ
	//virtual bool isGround();
	
	//この関数を呼ぶ前に、isChangeAble関数を呼び検証すること
	virtual IAnimationState* changeState( IAnimationState* nextState, CModel *model ) = 0;
	
	//virtual int getType() const = 0;
	virtual bool isWeightBlend() const = 0;
	virtual bool isRepeat() const = 0;


	//以下はBaseAnimationStateで実装されます

	virtual std::shared_ptr<Animation> getAnimation() const = 0;
	virtual const char* getVmdName() const = 0;
	
	virtual void addHook( Hook::IHookSharedPtr ) = 0;
	
	//virtual void addCollisionObject( BaseObject *obj )=0;
	
	virtual void informUpdate( float currentFrame )=0;
	virtual void informStart()=0;
	virtual void informChangeState()=0;
	virtual void informAnimationOver()=0;
};
}
}
#endif//__IANIMATION_STATE_H__