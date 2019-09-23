#include"Model.h"
#include"MME/Object/Model.h"

#include<assert.h>
#include"helper/BoostSerializationMacros.h"

namespace XmlLoader{ namespace MME { namespace Object {

Model::Model(){
	typedef ::MME::Object::Model InstanceModel;
	mModel = InstanceModel::create();
}
Model::~Model(){}
	
bool Model::isReady(){
	assert(mModel);
	return mModel->isReady();
}

const std::string & Model::getFileName()const{
	return mPmdFileName;
}

Model::InstanceModelSharedPtr Model::instance(){
	return mModel;
}

SPLIT_SERIALIZE_IMPL( Model );

template<class Archive>
void Model::save(Archive& ar, const unsigned int version) const {
	ar & boost::serialization::make_nvp("pmdFile", mPmdFileName );
}
template<class Archive>
void Model::load(Archive& ar, const unsigned int version) {
	ar & boost::serialization::make_nvp("pmdFile", mPmdFileName );
	mModel->loadPMDFromDB( mPmdFileName.c_str(), true );
}


EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(Model);

} } }// namespace XmlLoader::MME::Object