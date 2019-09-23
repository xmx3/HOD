#ifndef __MMDMIKUMODEL_H__
#define __MMDMIKUMODEL_H__

#include"Model.h"
#include<assert.h>

class CMMD_MikuModel{
public:
	enum AnimationState{
		ANIM_STAND=0,
		ANIM_WALK,
		ANIM_RUN,
		ANIM_IJIME_PUNCH,
		ANIM_DOUBLE_LARIAT,
		ANIM_DAMAGED,
		ANIM_DOWN,
		ANIM_WAKE,


		ANIM_NUM
	};
	CMMD_MikuModel();
	~CMMD_MikuModel();

	//初期位置をセット
	void init( const D3DXMATRIX &world );
	void draw();
	
	
	void update( const D3DXMATRIX &world, float elapsedTime );
	//IKBoneを指定の高さにする
	//example
	//if( mObj.onGround() ){
	//	mModle.update( world, elapsedTime );
	//} else {
	//	//現在地から下に向かってrayCastを地面に当ててgroundHeight求める
	//	//mObj.getPos().y()-obj.height*2.f //単純にこれでもいいね
	//	//mModle.update( world, elapsedTime, groundHeight );
	//}
	void update( const D3DXMATRIX &world, float elapsedTime, float groundHeight);

	bool isAnimOver();

	AnimationState getCurrentAnimation();
	void changeAnimation(AnimationState state);
	float getFrame(){
		return mModel.getFrame( mState );
	}

private:
	//キーボードのzxcvで操作
	void debugControll( const D3DXMATRIX &w, float elapsedTime );
	AnimationState mState;
	AnimationState mOldState;
	float mWeight;

	CModel mModel;
	class IAnimationStrategy;
	class CBaseAnimationStrategy;
	class CStandAnimation;
	class CWalkAnimation;
	class CRunAnimation;
	class CIjimePunchAnimation;
	class CDoubleLariatAnimation;
	class CDamagedAnimation;
	class CDownAnimation;
	class CWakeAnimation;

	IAnimationStrategy *m_pStrategy;
//以下は本当はMMDMikuModelAnimationStrategy.cppに定義したいがvcのバグでエラーが出てウザイので
//仕方なくここに置く

//CMMD_MikuModelを引数としたStrategyパターンっぽいな
//毎回new, deleteするのがダルイ。使いまわしたい。
//クラスメンバ変数なしの実装にした。
//読みにくい。せめて、mState,mOldState,mWeightはメンバ変数として持ってもよかったか？
//しかし、CMMD_MikuModelをポインタで渡していて、そこでそれらの変数を共通して持っていれば、いいんだから上の実装はなんか無駄がある。
class IAnimationStrategy{
public:
	virtual ~IAnimationStrategy(){}
	virtual void update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )=0;
	
	//virtual bool load()=0;

	//ホワイトリスト的に実装すること
	//そっちのほうがバグが少ない
	//ホワイトリスト的というのは、確実に信頼できる値のみtrueを返すこと
	//遷移できるものをtrueを返し、その他全部はfalseを返す実装
	//新しい状態を追加した場合、自動的にfalseを返すように
	//でも、この実装めんどいな。
	//立ち状態から遷移できるのは、ブラックリスト的に書くか？
	//とりあえず、出来るだけ、falseを返す実装で
	virtual bool isChangeAble( IAnimationStrategy *pS, CMMD_MikuModel *pMiku ) = 0;
	//立ち状態のアニメか？
	virtual bool isStand() = 0;

	//接地しているか？
	//実装はik使えそう足の長さのやつ
	//virtual bool isGround();
	
	//この関数を呼ぶ前に、isChangeAble関数を呼び検証すること
	virtual IAnimationStrategy* changeState( IAnimationStrategy* pS, CMMD_MikuModel *pMiku ) = 0;
	virtual AnimationState getType() = 0;
protected:
	virtual bool isOver( CMMD_MikuModel *pMiku ) =0;
};

#define INCREASED_WEIGHT_VALUE 0.05f;

//default動作実装
//weightBelndあり、リピートする。
class CBaseAnimationStrategy : public IAnimationStrategy {
public:
	CBaseAnimationStrategy(){}
	virtual ~CBaseAnimationStrategy(){}
	
protected:
	//再生が終わったら繰り返し0から再生
	void default_update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )
	{
		pMiku->mModel.update( world, true );
		float elapsedFrame = elapsedTime*30;

		if( pMiku->mWeight >= 1.f ) {
			pMiku->mModel.stepFrame( pMiku->mState, elapsedFrame );
		} else {
			pMiku->mModel.setWeight( pMiku->mState, pMiku->mWeight );
			pMiku->mModel.setWeight( pMiku->mOldState, 1.f-pMiku->mWeight );
			pMiku->mModel.stepFrame( pMiku->mState, elapsedFrame );
			pMiku->mWeight += INCREASED_WEIGHT_VALUE;
			if( pMiku->mWeight >= 1.f ) {
				pMiku->mModel.setWeight( pMiku->mOldState, 0.f );
				pMiku->mModel.setWeight( pMiku->mState, 1.f );
			}
		}

		if( isOver( pMiku ) ){
				pMiku->mModel.setFrame( pMiku->mState, 0.f );
		}
	}
	//ここでは、weightBlendの後始末とあとのモーションををきれいに動かす準備。
	//一つ上の階層で適切な値poiterを返すこと。
	void default_changeState( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		assert( pS->getType()<ANIM_NUM );
		assert( isChangeAble( pS, pMiku ) && "この関数を呼ぶ前に、isChangeAble関数を呼び検証すること" );
		
		//後始末
		//現在の重さを1に
		pMiku->mModel.setWeight( pMiku->mState, 1.0f );
		//古いものをリセット
		pMiku->mModel.setFrame( pMiku->mOldState, 0.f );
		pMiku->mModel.setWeight( pMiku->mOldState, 0.f );
		
		pMiku->mOldState=pMiku->mState;
		pMiku->mState=pS->getType();
		
		//次の準備//初期化されてないといけないので念のためリセット
		pMiku->mWeight=0.f;
		pMiku->mModel.setWeight( pMiku->mState, 0.f );
		pMiku->mModel.setFrame( pMiku->mState, 0.f );
	}

	bool default_isOver( CMMD_MikuModel *pMiku )
	{
		return pMiku->mModel.isFrameOver( pMiku->mState );
	}

private:
};

class CStandAnimation : public CBaseAnimationStrategy {
public:
	CStandAnimation(){}
	virtual ~CStandAnimation(){}
	
	void update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )
	{
		default_update( world, elapsedTime, pMiku );
	}
	IAnimationStrategy* changeState( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		default_changeState( pS, pMiku );
		return pS;
	}

	bool isChangeAble( IAnimationStrategy *pS , CMMD_MikuModel *pMiku )
	{
		AnimationState state=pS->getType();

		if( state==ANIM_WAKE ||
			state==ANIM_STAND ){
			return false;
		}
		if( pS->isStand() ) {
			return true;
		}
		return false;
	}

	AnimationState getType(){
		return ANIM_STAND;
	}

	bool isStand(){
		return true;
	}
protected:
	bool isOver( CMMD_MikuModel *pMiku ){
		return default_isOver( pMiku );
	}
};

class CWalkAnimation : public CBaseAnimationStrategy {
public:
	CWalkAnimation(){}
	virtual ~CWalkAnimation(){};

	void update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )
	{
		default_update( world, elapsedTime, pMiku );
	}
	IAnimationStrategy* changeState( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		default_changeState( pS, pMiku );
		return pS; 
	}
	AnimationState getType()
	{
		return ANIM_WALK;
	}
	bool isStand() {
		return true;
	}
	bool isChangeAble( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		AnimationState s=pS->getType();
		if(s==ANIM_WALK){
			return false;
		}
		if( pS->isStand() )
		{
			return true;
		}
		return false;
	}
protected:
	bool isOver( CMMD_MikuModel *pMiku ){
		return pMiku->mModel.getFrame( pMiku->mState ) > 32;
	}
};

class CRunAnimation : public CBaseAnimationStrategy {
	public:
	CRunAnimation(){}
	virtual ~CRunAnimation(){};

	void update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )
	{
		default_update( world, elapsedTime, pMiku );
	}
	IAnimationStrategy* changeState( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		default_changeState( pS, pMiku );
		return pS; 
	}
	AnimationState getType()
	{
		return ANIM_RUN;
	}
	bool isStand() {
		return true;
	}
	bool isChangeAble( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		AnimationState s=pS->getType();
		if(s==ANIM_RUN){
			return false;
		}
		if( pS->isStand() )
		{
			return true;
		}
		return false;
	}
protected:
	bool isOver( CMMD_MikuModel *pMiku ){
		return pMiku->mModel.getFrame( pMiku->mState ) > 20;
	}
};

class CIjimePunchAnimation : public CBaseAnimationStrategy {
public:
	CIjimePunchAnimation(){}
	virtual ~CIjimePunchAnimation(){};

	void update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )
	{
		default_update( world, elapsedTime, pMiku );
	}
	IAnimationStrategy* changeState( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		default_changeState( pS, pMiku );
		return pS; 
	}
	AnimationState getType()
	{
		return ANIM_IJIME_PUNCH;
	}
	bool isStand() {
		return true;
	}
	bool isChangeAble( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		AnimationState s=pS->getType();
		if(s==ANIM_IJIME_PUNCH){
			return false;
		}
		if( pS->isStand() )
		{
			return true;
		}
		return false;
	}
protected:
	bool isOver( CMMD_MikuModel *pMiku ){
		return default_isOver(pMiku);
	}
};

class CDamagedAnimation : public CBaseAnimationStrategy {
public:
	CDamagedAnimation(){}
	virtual ~CDamagedAnimation(){};
	//repeatなし standに遷移
	void update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )
	{
			pMiku->mModel.update( world, true );
		float elapsedFrame = elapsedTime*30;

		if( pMiku->mWeight >= 1.f ) {
			pMiku->mModel.stepFrame( pMiku->mState, elapsedFrame );
		} else {
			pMiku->mModel.setWeight( pMiku->mState, pMiku->mWeight );
			pMiku->mModel.setWeight( pMiku->mOldState, 1.f-pMiku->mWeight );
			pMiku->mModel.stepFrame( pMiku->mState, elapsedFrame );
			pMiku->mWeight += INCREASED_WEIGHT_VALUE;
			if( pMiku->mWeight >= 1.f ) {
				pMiku->mModel.setWeight( pMiku->mOldState, 0.f );
				pMiku->mModel.setWeight( pMiku->mState, 1.f );
			}
		}

		if( isOver( pMiku ) ){
			pMiku->m_pStrategy=changeState( &(pMiku->mStand), pMiku );
		}
	}
	IAnimationStrategy* changeState( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		default_changeState( pS, pMiku );
		return pS; 
	}
	AnimationState getType()
	{
		return ANIM_DAMAGED;
	}
	bool isStand() {
		return true;
	}
	bool isChangeAble( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		AnimationState s=pS->getType();
		if(s==ANIM_DAMAGED){
			return false;
		}
		if( pS->isStand() )
		{
			return true;
		}
		return false;
	}
protected:
	bool isOver( CMMD_MikuModel *pMiku ){
		return default_isOver(pMiku);
	}
};

class CDoubleLariatAnimation : public CBaseAnimationStrategy {
public:
	CDoubleLariatAnimation(){}
	virtual ~CDoubleLariatAnimation(){};
	//特殊ループ　リピートは途中から
	void update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )
	{
		pMiku->mModel.update( world, true );
		float elapsedFrame = elapsedTime*30;

		if( pMiku->mWeight >= 1.f ) {
			pMiku->mModel.stepFrame( pMiku->mState, elapsedFrame );
		} else {
			pMiku->mModel.setWeight( pMiku->mState, pMiku->mWeight );
			pMiku->mModel.setWeight( pMiku->mOldState, 1.f-pMiku->mWeight );
			pMiku->mModel.stepFrame( pMiku->mState, elapsedFrame );
			pMiku->mWeight += INCREASED_WEIGHT_VALUE;
			if( pMiku->mWeight >= 1.f ) {
				pMiku->mModel.setWeight( pMiku->mOldState, 0.f );
				pMiku->mModel.setWeight( pMiku->mState, 1.f );
			}
		}

		if( isOver( pMiku ) ){
				pMiku->mModel.setFrame( pMiku->mState, 30.f );
		}
	}
	IAnimationStrategy* changeState( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		default_changeState( pS, pMiku );
		return pS; 
	}
	AnimationState getType()
	{
		return ANIM_DOUBLE_LARIAT;
	}
	bool isStand() {
		return true;
	}
	bool isChangeAble( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		AnimationState s=pS->getType();
		if(s==ANIM_DOUBLE_LARIAT){
			return false;
		}
		if( pS->isStand() )
		{
			return true;
		}
		return false;
	}
protected:
	bool isOver( CMMD_MikuModel *pMiku ){
		return default_isOver(pMiku);
	}
};

class CDownAnimation : public CBaseAnimationStrategy {
public:
	CDownAnimation(){}
	virtual ~CDownAnimation(){};
	//weight blend あり。リピートなし
	void update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )
	{
		pMiku->mModel.update( world, true );
		float elapsedFrame = elapsedTime*30;
		
		if( pMiku->mWeight >= 1.f ) {
			pMiku->mModel.stepFrame( pMiku->mState, elapsedFrame );
		} else {
			pMiku->mModel.setWeight( pMiku->mState, pMiku->mWeight );
			pMiku->mModel.setWeight( pMiku->mOldState, 1.f-pMiku->mWeight );
			pMiku->mModel.stepFrame( pMiku->mState, elapsedFrame );
			pMiku->mWeight += INCREASED_WEIGHT_VALUE;
			if( pMiku->mWeight >= 1.f ) {
				pMiku->mModel.setWeight( pMiku->mOldState, 0.f );
				pMiku->mModel.setWeight( pMiku->mState, 1.f );
			}
		}

		if( isOver( pMiku ) ){
			pMiku->m_pStrategy=changeState( &(pMiku->mWake), pMiku );
		}
	}
	IAnimationStrategy* changeState( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		assert( isChangeAble( pS, pMiku ) && "この関数を呼ぶ前に、isChangeAble関数を呼び検証すること" );
		
		pMiku->mModel.setFrame( pMiku->mState, 0.f );
		pMiku->mModel.setWeight( pMiku->mState, 0.f );
		pMiku->mModel.setFrame( pMiku->mOldState, 0.f );
		pMiku->mModel.setWeight( pMiku->mOldState, 0.f );
		pMiku->mOldState=pMiku->mState;
		pMiku->mState=pS->getType();
		pMiku->mWeight = 1.f;
		pMiku->mModel.setWeight( pMiku->mState, 1.f );
		pMiku->mModel.setFrame( pMiku->mState, 0.f );
		return pS;
	}
	AnimationState getType()
	{
		return ANIM_DOWN;
	}
	bool isStand() {
		return true;
	}
	bool isChangeAble( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{	
		if( isOver(pMiku) ){
			AnimationState s=pS->getType();
			if(s==ANIM_WAKE){
				return true;
			}
		}
		return false;
	}
protected:
	bool isOver( CMMD_MikuModel *pMiku ){
		return default_isOver(pMiku);
	}
};


class CWakeAnimation : public CBaseAnimationStrategy {
public:
	CWakeAnimation(){}
	virtual ~CWakeAnimation(){};
	//blendなし、リピートなし
	void update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )
	{
		
		pMiku->mModel.update( world, true );
		float elapsedFrame = elapsedTime*30;

		assert( pMiku->mModel.getWeight(pMiku->mState)==1.0f );
		//pMiku->mModel.setWeight( pMiku->mState, 1.f );
		pMiku->mModel.stepFrame( pMiku->mState, elapsedFrame );

		if( isOver( pMiku ) ){
			pMiku->m_pStrategy=changeState( &(pMiku->mStand), pMiku );
		}
	}
	IAnimationStrategy* changeState( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		assert( isChangeAble( pS, pMiku ) && "この関数を呼ぶ前に、isChangeAble関数を呼び検証すること" );
		
		pMiku->mModel.setFrame( pMiku->mState, 0.f );
		pMiku->mModel.setWeight( pMiku->mState, 0.f );
		pMiku->mModel.setFrame( pMiku->mOldState, 0.f );
		pMiku->mModel.setWeight( pMiku->mOldState, 0.f );
		pMiku->mOldState=pMiku->mState;
		pMiku->mState=pS->getType();
		pMiku->mWeight = 1.f;
		pMiku->mModel.setWeight( pMiku->mState, 1.f );
		pMiku->mModel.setFrame( pMiku->mState, 0.f );
		return pS;
	}
	AnimationState getType()
	{
		return ANIM_WAKE;
	}
	bool isStand() {
		return false;
	}
	bool isChangeAble( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		if( isOver(pMiku) ){
			AnimationState s=pS->getType();
			if(s==ANIM_STAND){
				return true;
			}
		}
		return false;
	}
protected:
	bool isOver( CMMD_MikuModel *pMiku ){
		return default_isOver(pMiku);
	}
};

	CStandAnimation mStand;
	CWalkAnimation mWalk;
	CRunAnimation mRun;
	CIjimePunchAnimation mIjimePunch;
	CDoubleLariatAnimation mDoubleLariat;
	CDamagedAnimation mDamaged;
	CDownAnimation mDown;
	CWakeAnimation mWake;

}; //class CMMD_MikuModel
#endif//__MMDMIKUMODEL_H__