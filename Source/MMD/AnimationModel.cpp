#include"AnimationModel.h"
#include<assert.h>
#include"MMD/Model.h"
#include<GameLib/GameLib.h>
#include"AnimationState/IAnimationState.h"

#include"GameObject/Accessory.h"

namespace MMD {
AnimationModel::AnimationModel()
	:mModel(NULL),
	mState(NULL)
{
	mModel = NEW CModel();
}

AnimationModel::AnimationModel( const TemplatePMDSharedPtr &pmd, bool enablePhysics )
	:mModel(NULL),
	mState(NULL)
{
	mModel = NEW CModel();
	mModel->build(pmd, enablePhysics);
}

AnimationModel::~AnimationModel(){
	removeFromWorld();
	SAFE_DELETE(mModel);
}

void  AnimationModel::loadPMD( const char *pmdName ){
	assert(false && "use loadPMDFromDB" );
	bool b;
	b=mModel->loadPMD(pmdName, true);
	assert(b);
}

void  AnimationModel::loadPMD( const GameLib::FileIO::InFile &inFile ){
	assert(false && "use loadPMDFromDB" );
	bool b;
	b=mModel->loadPMD(inFile, true);
	assert(b);
}

void AnimationModel::loadPMDFromDB( const char *fileName, bool enablePhysics ){
	//2重ロードのことまったく考慮してない
	mModel->loadPMDFromDB( fileName, enablePhysics );
}


std::shared_ptr<Animation> AnimationModel::loadVMD( const char *vmdName ) {
	return mModel->loadVMD( vmdName );
}

//indexを返す。失敗したら-1を返す。
//int AnimationModel::loadVMD( const GameLib::FileIO::InFile &inFile ){
//	if(mModel->loadVMD( inFile )){
//		return mModel->getAnimationsNum()-1;
//	}else{
//		return -1;
//	}
//}


//見つからないならー1を返す
//int AnimationModel::getIndex( const char *vmdName ) const {}

//初期位置をセット(RigidBodyのため).
//warpの方が名前いい?setInitWorldTransform();reset
void AnimationModel::init( const D3DXMATRIX &world, AnimationState::IAnimationState *anim ){
	mState = anim;
	mModel->setCurrentAnimation( mState->getAnimation() );
	mModel->setFrame(0.f);
	mModel->fitRigidBodeisToBone(world);
	mModel->update(world, true);
}
void AnimationModel::draw() const {
	mModel->draw();
}

void AnimationModel::drawByMME() const {
	mModel->drawByMME();
}

void AnimationModel::update( const D3DXMATRIX &world, float elapsedTime ){
	mState=mState->stepTime( elapsedTime, mModel);
	mModel->update( world, true );
	updateAccessories();
}

bool AnimationModel:: isAnimOver() const{
	return mState->isOver(mModel);
}

std::shared_ptr<Animation> AnimationModel::getCurrentAnimation() const {
	return mState->getAnimation();
}

AnimationState::IAnimationState* AnimationModel::getCurrentAnimationState(){
	return mState;
}

void AnimationModel::changeAnimation(AnimationState::IAnimationState* state){
	if( mState->isChangeAble( state, mModel ) ){
		 mState = mState->changeState(state, mModel);
	}
}
float AnimationModel::getFrame() const {
	return mModel->getFrame();
}

Bone* AnimationModel::getBone( const char* boneName ){
	return mModel->getBone( boneName );
}

void AnimationModel::debugDraw() const{
	mModel->debugDraw();
}

const std::string& AnimationModel::getModelFileName()const{
	return mModel->getFileName();
}

bool AnimationModel::isReady(){
	assert(false);
	if( mModel->isReady() ){
		//for( 
		//	AnimationMap::iterator it=mAnimationMap.begin(), end=mAnimationMap.end();
		//	it!=end;
		//	++it )
		//{
		//	if(!it->second->isReady()){
		//		return false;
		//	}
		//}

		for( 
			AccessoryMap::iterator it=mAccessoryMap.begin(), end=mAccessoryMap.end();
			it!=end;
			++it )
		{
			if(!it->second->isReady()){
				return false;
			}
		}
		return true;
	}else{
		return false;
	}
	return false;
}

void AnimationModel::changeAnimation( const std::string& animName ){
	AnimationMap::iterator it = mAnimationMap.find(animName);
	assert( it!=mAnimationMap.end());
	changeAnimation( it->second.get() );
}

std::shared_ptr<GameObject::Accessory> AnimationModel::getAccessory( const std::string &name ){
	AccessoryMap::iterator it = mAccessoryMap.find(name);
	assert( it!=mAccessoryMap.end() );
	return it->second;
}

void AnimationModel::addHookToAnim( const std::string &toAnimName, const MMD::AnimationState::Hook::IHookSharedPtr &hook ){
	AnimationMap::iterator it = mAnimationMap.find(toAnimName);
	assert( it!=mAnimationMap.end());
	it->second->addHook( hook );
}

void AnimationModel::addAnimState( const std::string &animationName, const MMD::AnimationState::IAnimationStateSharedPtr &anim ){
	typedef std::pair<AnimationMap::iterator, bool> Pairib;

	Pairib pair = mAnimationMap.insert( 
		std::pair<std::string, MMD::AnimationState::IAnimationStateSharedPtr>(animationName, anim) 
	);
	assert( pair.second );
}

void AnimationModel::updateAccessories() const{
	for(
		AccessoryMap::const_iterator it= mAccessoryMap.begin(), end =mAccessoryMap.end();
		it!=end;
		++it )
	{
		//canDraw()
		if( it->second->canDraw() ){
			it->second->preDrawMMD();
		}
	}
}

void AnimationModel::init( const D3DXMATRIX &world, const std::string & animName ){
	AnimationMap::iterator it = mAnimationMap.find(animName);
	assert( it!=mAnimationMap.end());
	init( world, it->second.get() );
}

void AnimationModel::addAccessory( const std::string &name, const std::shared_ptr<GameObject::Accessory>& accessory  ){
	typedef std::pair<AccessoryMap::iterator, bool > Pairib;
	Pairib ib =	mAccessoryMap.insert( std::make_pair( name, accessory ) );
	assert( ib.second && "accessory name is doubled!" );
}

void AnimationModel::addToWorld(){
	mModel->addToWorld();
}
void AnimationModel::removeFromWorld(){
	mModel->removeFromWorld();
	for (
		AccessoryMap::const_iterator it = mAccessoryMap.begin(), end = mAccessoryMap.end();
		it != end;
		++it)
	{
		it->second->removeFromWorld();
	}
}




}// end namespace MMD