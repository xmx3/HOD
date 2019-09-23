#include"BaseAnimationState.h"
#include"MMD/Model.h"
#include<assert.h>
#include<d3dx9.h>
#include<GameLib/GameLib.h>
#include<GameLib/Framework.h>
#include"MMD/MMDConstants.h"
//#include"GameObject/BoneCollisionObject.h"

#define INCREASED_WEIGHT_VALUE 0.25f

namespace MMD {
namespace AnimationState {
BaseAnimationState::BaseAnimationState( const std::shared_ptr<Animation> &anim, const char *vmdName )
	:mAnimation(anim),
	mNextState(NULL),
	mVmdName(NULL),
	mPlaySpeed(1.f)
{
	if(vmdName!=NULL) {
		int size = strlen(vmdName);
		mVmdName = new char [size];
		for(int i=0; i<size; ++i ){
			mVmdName[i]=vmdName[i];
		}
	}
}
BaseAnimationState::~BaseAnimationState(){
	//mCollisionObjects.clear();
	//mCollisionObjects.shrink_to_fit();
	SAFE_DELETE_ARRAY( mVmdName );
}

IAnimationState* BaseAnimationState::defalut_stepTime( float elapsedTime, CModel *model, float restartFrame )
{
	IAnimationState *next=this;

	float elapsedFrame = elapsedTime*MMD_FramePerSecond*mPlaySpeed;
	//elapsedTime*static_cast<float>( GameLib::Framework::instance().frameRate() );
	
	//float elapsedFrame = elapsedTime*static_cast<float>( GameLib::Framework::instance().previousFrameInterval() ) * 0.001f;


	model->stepFrame( elapsedFrame );

	//for( int i=0, size=mCollisionObjects.size(); i<size; ++i ){
	//	mCollisionObjects[i]->update( model->getFrame() );
	//}

	informUpdate( model->getFrame() );

	if( isOver(model)){
		informAnimationOver();
		if( isRepeat() ){
			model->setFrame( restartFrame );
		} else if(mNextState){
			next = changeState( mNextState, model );
			assert( next == mNextState );
		}
	}
	return next;

}

//ここでは、weightBlendの後始末とあとのモーションををきれいに動かす準備。
IAnimationState* BaseAnimationState::defalut_changeState( IAnimationState *nextState, CModel *model )
{
	assert( isChangeAble( nextState, model ) && "この関数を呼ぶ前に、isChangeAble関数を呼び検証すること" );
		
	

	//次の準備
	const std::shared_ptr<Animation> &next  = nextState->getAnimation();
	//開始時刻を0に
	model->setFrame( 0.f );
	model->setCurrentAnimation( next );
	//weightBlend使う場合
	if( nextState->isWeightBlend() ){
		model->startWeightBlend();
	}

	//removeFromWorldAllCollisionObjects();
	informChangeState();
	nextState->informStart();
	
	return nextState;
}

bool BaseAnimationState::default_isOver(CModel *model)
{
	return model->isFrameOver();
}

//void BaseAnimationState::addCollisionObject( GameObject::BoneCollisionObject *obj ){
//	mCollisionObjects.push_back(obj);
//}
//
//void BaseAnimationState::removeFromWorldAllCollisionObjects() {
//	for( int i=0, size=mCollisionObjects.size(); i<size; ++i ){
//		mCollisionObjects[i]->removeFromWorld();
//	}
//}

void BaseAnimationState::informUpdate( float currentFrame ){
	for( int i=0, size=mHooks.size(); i<size; ++i ){
		mHooks[i]->hookUpdate( currentFrame );
	}
}
void BaseAnimationState::informStart(){
	for( int i=0, size=mHooks.size(); i<size; ++i ){
		mHooks[i]->hookStart();
	}
}

void BaseAnimationState::addHook( Hook::IHookSharedPtr hook ){
	mHooks.push_back( hook );
}
void BaseAnimationState::shrinkToFitAllHookContainers(){
	mHooks.shrink_to_fit();
	//mCollisionObjects.shrink_to_fit();
}

void BaseAnimationState::informChangeState(){
	for( int i=0, size=mHooks.size(); i<size; ++i ){
		mHooks[i]->hookChangeState();
	}
}
void BaseAnimationState::informAnimationOver(){
	for( int i=0, size=mHooks.size(); i<size; ++i ){
		mHooks[i]->hookAnimationOver();
	}
}

}
}