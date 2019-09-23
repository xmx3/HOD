#include"Model.h"
#include<boost/flyweight.hpp>
#include<boost/flyweight/key_value.hpp>

#include"helper/BoostSerializationMacros.h"
#include"XFile/Model.h"

#include"GameObject/AccessoryUtils/MME/Model.h"


namespace XmlLoader { namespace GameObject { namespace AccessoryUtils{
Model::Model()
	:mModel(NULL),mScale(1.f)
{}

Model::~Model(){
	delete mModel;
	mModel=0;
}
void Model::loadModel(){
	delete mModel;
	mModel=0;
	mModel = new boost::flyweights::flyweight<
		boost::flyweights::key_value<std::string, XFile::Model >
	>( mFileName );
}
bool Model::isReady(){
	assert( !mFileName.empty() );
	
	if( mModel ){
		return const_cast<XFile::Model&>(mModel->get()).isFinished();
	} else {
		loadModel();
		return false;
	}
}

::GameObject::AccessoryUtils::MME::ModelSharedPtr 
Model::instance(){
	while(!isReady()){}
	return ::GameObject::AccessoryUtils::MME::Model::create( *mModel, mScale );
	
}
template<class Archive>
void Model::serialize(Archive& ar, const unsigned int version){
	ar & boost::serialization::make_nvp("xFile", mFileName );
	ar & boost::serialization::make_nvp("scale", mScale );
}


EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(Model);

} } }// end XmlLoader::GameObject::AccessoryUtils
BOOST_CLASS_IMPLEMENTATION(XmlLoader::GameObject::AccessoryUtils::Model, boost::serialization::object_serializable);
