#include "CutScene.h"
#include "MME/Manager.h"
#include "MME/Batch/StandardEffectBatch.h"
#include "MME/Batch/PostEffectBatch.h"
#include <GameLib/GameLib.h>//SAFE_DELETE
#include "helper/FileLoader.h"
#include "GameObject/AccessoryUtils/MME/Model.h"
#include "MME/Object/ModelKai.h"
#include "MME/Object/Accessory.h"
#include "MME/Object/PointLight.h"

#include <GameLib/Graphics/Manager.h>
#include "CutSceneImpl/Standard.h"
#include "CutSceneImpl/Light.h"


namespace MME {


namespace Drawer{ namespace CutScene {

//using MME::Drawer::CutSceneImpl::Standard::Impl;
using MME::Drawer::CutSceneImpl::Light::Impl;
void destroy(){
	Impl::instance()->destroy();
}

bool isReady(){
	return Impl::instance()->isReady();

}

void draw(){
	Impl::instance()->draw();
}


void add( const Object::ModelKaiSharedPtr &obj){
	Impl::instance()->add(obj);
}
void add( const Object::PointLightSharedPtr &obj){
	Impl::instance()->add(obj);
}
	
void add( const Object::AccessorySharedPtr &obj){
	Impl::instance()->add(obj);
}
void add( const GameObject::AccessoryUtils::MME::ModelSharedPtr &obj){
	Impl::instance()->add(obj);
}

} } }//end namespace MME::Drawer::CutScene
