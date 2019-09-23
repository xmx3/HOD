#include"TemplateModel.h"
#include"XFile/Model.h"
#include<d3dx9.h>
#include"GameObject/Accessory.h"
#include"MME/Enums.h"
#include"MMD/Bone.h"
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"SegaTypeHelper.h"
#include"Model.h"


namespace GameObject {
namespace AccessoryUtils {
namespace MME {

TemplateModel::TemplateModel( const std::string &xFileName )
	:mModel(NULL)
{
	mModel= std::make_shared<XFile::Model>( xFileName );
}

TemplateModel::~TemplateModel(){
}

bool TemplateModel::isFinished()const{
	return mModel->isFinished();
}
bool TemplateModel::isError()const{
	return mModel->isError();
}

GameLib::Graphics::VertexBuffer TemplateModel::getVertexBuffer()const{
	return mModel->getVertexBuffer();
}
GameLib::Graphics::IndexBuffer TemplateModel::getIndexBuffer()const{
	return mModel->getIndexBuffer();
}

const std::string & TemplateModel::getModelFileName()const{
	return mModel->getFileName();
}

//std::shared_ptr<Model> TemplateModel::createModel(float scale)const{
//	std::shared_ptr<Model> model = std::make_shared<Model>( mModel, scale );
//	return model;
//}


}//end namespace MME

}//end namespace AccessoryUtils
}//end namespace GameObject
