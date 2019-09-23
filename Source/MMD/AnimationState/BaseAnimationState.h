#ifndef __BASE_ANIMATION_STATE_H__
#define __BASE_ANIMATION_STATE_H__

#include"IAnimationState.h"
#include"Hook/IHook.h"
#include<vector>

//Effective C++ 34項 インターフェースの継承と実装の継承の区別をしよう

struct D3DXMATRIX;

//namespace GameObject{
//	class BoneCollisionObject;
//}

namespace MMD {
	class CModel;
	class Animation;

namespace AnimationState {
//default動作実装のお助けクラス
//mNextSceneがNULLか、isWeightBlend()、isRepeatの実装によって変化する。
class BaseAnimationState : public IAnimationState
{
public:
	BaseAnimationState( const std::shared_ptr<Animation> &anim, const char* vmdName );
	virtual ~BaseAnimationState();
	
	virtual std::shared_ptr<Animation> getAnimation() const{
		return mAnimation;
	}
	virtual const char* getVmdName() const {
		return mVmdName;
	};

	//virtual void addCollisionObject( GameObject::BoneCollisionObject *obj );

	virtual void addHook( Hook::IHookSharedPtr hook );
	void shrinkToFitAllHookContainers();
	void setPlaySpeed( const float & playSpeed ){
		mPlaySpeed=playSpeed;
	}
protected:
	//何も変化しない場合thisを返す
	//isBlendWeight()とisRepeat()の実装, mNextSceneがNULLかによって処理が変化
	//restartFrameはisOver()とisRepeat()がtrueの場合、再開始するフレーム位置
	IAnimationState* defalut_stepTime( float elapsedTime, CModel *model, float restartFrame=0.f );

	//isBlendWeight()とisRepeat()の実装によって処理が変化
	//ここでは、weightBlendの後始末と次のモーションををきれいに動かす準備。
	//移行できないならthisを返す。
	IAnimationState* defalut_changeState( IAnimationState *nextState, CModel *model  );

	bool default_isOver( CModel *model );
	
	//void removeFromWorldAllCollisionObjects();

	//defaultの実装を使わないなら自分で呼び出すこと
	//	default_stepTimeを使わないなら、informUpdateとinformAnimOverをただしく呼び出すこと
	//	default_changeStateを使わないなら、informChangeStateとinformStartを正しく呼び出すこと
	//
	//informAnimationOverの位置に気をつけること
	//	stepTime内で一回呼び出すのがお勧め
	//	呼び出すのはフレーム毎一回にすること。
	//	isOver()の中でtrueになるたび呼び出さないこと
	virtual void informUpdate( float currentFrame );
	virtual void informStart();
	virtual void informChangeState();
	virtual void informAnimationOver();


	
	char *mVmdName;
	std::shared_ptr<Animation> mAnimation;
	float mPlaySpeed;
	//std::vector<GameObject::BoneCollisionObject*> mCollisionObjects;
	IAnimationState *mNextState;

	std::vector<Hook::IHookSharedPtr> mHooks;

};
}
}
#endif//__BASE_ANIMATION_STATE_H__