#include"TemplateAccessory.h"
#include"MME/Model.h"
#include"GameObject/Accessory.h"
#include"MME/TemplateModel.h"

namespace GameObject {
namespace AccessoryUtils {
TemplateAccessory::TemplateAccessory(
		SptrShape shape,
		MME::SptrTemplateModel model,
		float mass,
		float scale )
		:mMass(mass),
		mScale(scale),
		mTemplateModel( model ),
		mShape( shape )
{}
TemplateAccessory::~TemplateAccessory(){}



std::shared_ptr<Accessory> TemplateAccessory::createAccessory(  btCollisionObject *owner,  const btTransform &startTrans ){
	MME::ModelSharedPtr model;
	if( mTemplateModel ){
		model = mTemplateModel->createModel(mScale);
	}
	return std::make_shared<Accessory>( mShape, model, mMass,  owner, startTrans );
}


} //end namespace AccessoryUtils
} //end namespace GameObject