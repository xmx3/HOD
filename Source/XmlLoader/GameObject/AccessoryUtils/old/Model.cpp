#include"Model.h"
#include<boost/flyweight.hpp>
#include"helper/BoostSerializationMacros.h"

namespace Serialization { namespace GameObject { namespace AccessoryUtils{
Model::Model()
	:mModel(NULL)
{}
Model::~Model(){
	delete mModel;
	mModel=0;
}
void Model::loadModel(){
	delete mModel;
	mModel=0;
	mModel = new boost::flyweights::flyweight<
		boost::flyweights::key_value<std::string, ::GameObject::AccessoryUtils::MME::TemplateModel >
	>( mFileName );
}
bool Model::isReady(){
	assert( !mFileName.empty() );
	
	if( mModel ){
		return mModel->get().isFinished();
	} else {
		loadModel();
		return false;
	}
}

::GameObject::AccessoryUtils::MME::ModelSharedPtr 
Model::instance(){
	while(!isReady()){}
	return mModel->get().createModel( mScale );
}

EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(Model);


} } }// end Serialization::GameObject::AccessoryUtils
BOOST_CLASS_IMPLEMENTATION(Serialization::GameObject::AccessoryUtils::Model, boost::serialization::object_serializable);
