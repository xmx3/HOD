#include"Model.h"
#include"MMD/AnimationModel.h"
#include"MMD/AnimationState/IAnimationState.h"
#include"MMD/Bone.h"
#include<MME/Manager.h>
namespace MME{
	namespace Object{
		

ModelSharedPtr Model::create(){
	ModelSharedPtr result = std::make_shared<Model>();
	//MME::Manager::instance()->addToStandardEfffect( result, NULL );
	assert(false && "implement now");
	return result;
}

Model::Model()
	:mModel(0)
{
	mModel=new MMD::AnimationModel();
}

Model::~Model(){
	delete mModel;
	mModel=0;
}


void Model::draw()const{
	if(mCanDraw){
		mModel->drawByMME();
	}
}

float Model::getScale()const{
	return 1.0;
}


	
float Model::getFaceValue(const std::string &faceName )const
{
	assert(false);
	return 0;
}

const D3DXMATRIX & Model::getBoneMatrix( const std::string &boneName )const
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

const std::string& Model::getModelFileName()const{
	return mModel->getModelFileName();
}

void Model::update( const D3DXMATRIX & world, float elapsed ){
	mModel->update( world, elapsed );
	mTransform = world;
}

void Model::loadPMDFromDB( const char *fileName, bool enablePhysics ){
	mModel->loadPMDFromDB( fileName, enablePhysics );
}

//初期位置をセット(RigidBodyのため).
//warpの方が名前いい?setInitWorldTransform();reset
void Model::init( const D3DXMATRIX &world, MMD::AnimationState::IAnimationState* anim ){
	mModel->init( world, anim );
}

bool Model::isAnimOver() const{
	return mModel->isAnimOver();
}

MMD::AnimationState::IAnimationState* Model::getCurrentAnimationState(){
	return mModel->getCurrentAnimationState();
}
void Model::changeAnimation( MMD::AnimationState::IAnimationState* state ){
	mModel->changeAnimation(state);
}
float Model::getFrame() const{
	return mModel->getFrame();
}

MMD::Bone* Model::getBone( const char* boneName ){
	return mModel->getBone( boneName );
}

bool Model::isReady(){
	return mModel->isReady();
}


}// end namespace Object
}// end namespace MME

