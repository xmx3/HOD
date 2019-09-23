#include"ModelKai.h"
#include"MMD/AnimationModel.h"
#include"MMD/AnimationState/IAnimationState.h"
#include"MMD/Bone.h"
#include<MME/Manager.h>

#include"XmlLoader/Actions.h"

namespace MME{
	namespace Object{
		

ModelKaiSharedPtr ModelKai::create( const MMD::TemplatePMDSharedPtr &pmd, bool enablePhysics, float heightOffset ){
	ModelKaiSharedPtr result( new ModelKai(pmd, enablePhysics, heightOffset) );
	return result;
}

ModelKai::ModelKai( const MMD::TemplatePMDSharedPtr &pmd, bool enablePhysics, float heightOffset )
	:mModel(0),
	mHeightOffset(heightOffset)
{
	mModel=new MMD::AnimationModel(pmd, enablePhysics);
}

ModelKai::~ModelKai(){
	delete mModel;
	mModel=0;
}


void ModelKai::draw()const{
	if(mCanDraw){
		mModel->drawByMME();
	}
}

float ModelKai::getScale()const{
	return 1.0;
}


	
float ModelKai::getFaceValue(const std::string &faceName )const
{
	assert(false);
	return 0;
}

const D3DXMATRIX & ModelKai::getBoneMatrix( const std::string &boneName )const
{
	MMD::Bone *bone = mModel->getBone( boneName.c_str() );
	if(bone){
		return bone->getSkinningMatrix();
	} else{
		static D3DXMATRIX matI( 
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
		);
		return matI;
	}

};

const std::string& ModelKai::getModelFileName()const{
	return mModel->getModelFileName();
}

void ModelKai::update( const D3DXMATRIX & world, float elapsed ){
	D3DXVECTOR3 offset;
	mTransform = world;

	D3DXVec3TransformNormal( &offset, &D3DXVECTOR3( 0.f, -mHeightOffset, 0.f ), &mTransform );
	mTransform._41 += offset.x;
	mTransform._42 += offset.y;
	mTransform._43 += offset.z;

	mModel->update( mTransform, elapsed );
}

//void ModelKai::loadPMDFromDB( const char *fileName, bool enablePhysics ){
//	mModel->loadPMDFromDB( fileName, enablePhysics );
//}

//‰ŠúˆÊ’u‚ðƒZƒbƒg(RigidBody‚Ì‚½‚ß).
void ModelKai::init( const D3DXMATRIX &world, const std::string &animName ){
	D3DXVECTOR3 offset;
	mTransform = world;

	D3DXVec3TransformNormal( &offset, &D3DXVECTOR3( 0.f, -mHeightOffset, 0.f ), &mTransform );
	mTransform._41 += offset.x;
	mTransform._42 += offset.y;
	mTransform._43 += offset.z;

	mModel->init( mTransform, animName );
}

bool ModelKai::isAnimOver() const{
	return mModel->isAnimOver();
}

void ModelKai::changeAnimation( const std::string &animName ){
	mModel->changeAnimation(animName);
}
float ModelKai::getFrame() const{
	return mModel->getFrame();
}

MMD::Bone* ModelKai::getBone( const char* boneName ){
	return mModel->getBone( boneName );
}

bool ModelKai::isReady(){
	return mModel->isReady();
}

//void ModelKai::addHookToAnim( const std::string &toAnimName, const MMD::AnimationState::Hook::IHookSharedPtr &hook ){
//	mModel->addHookToAnim( toAnimName, hook );
//}
void ModelKai::addAnimState( const std::string &animationName, const MMD::AnimationState::IAnimationStateSharedPtr &anim ){
	mModel->addAnimState( animationName, anim );
}

void ModelKai::addAccessory( const std::string &name, const GameObject::AccessorySharedPtr &accessory ){
	mModel->addAccessory( name, accessory );
}

//•¨—¢ŠE‚É’Ç‰Á
void ModelKai::addToWorld(){
	mModel->addToWorld();
}

//•¨—¢ŠE‚©‚çíœ
void ModelKai::removeFromWorld(){
	mModel->removeFromWorld();
}

GameObject::AccessorySharedPtr ModelKai::getAccessory( const std::string &name ){
	return mModel->getAccessory(name);
}

}// end namespace Object
}// end namespace MME

