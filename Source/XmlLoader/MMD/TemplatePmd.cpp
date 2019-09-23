#include"TemplatePMD.h"
#include"MMD/TemplatePMD.h"
#include"MMD/MMDDataBase.h"


#include<assert.h>
#include"helper/BoostSerializationMacros.h"

namespace XmlLoader{ namespace MMD{

TemplatePMD::TemplatePMD(){
}
TemplatePMD::~TemplatePMD(){}
	
bool TemplatePMD::isReady(){
	assert(mModel);
	return mModel->isReady();
}

const std::string & TemplatePMD::getFileName()const{
	return mPmdFileName;
}

::MMD::TemplatePMDSharedPtr TemplatePMD::instance(){
	return mModel;
}

SPLIT_SERIALIZE_IMPL( TemplatePMD );

template<class Archive>
void TemplatePMD::save(Archive& ar, const unsigned int version) const {
	ar & boost::serialization::make_nvp("pmdFile", mPmdFileName );
}
template<class Archive>
void TemplatePMD::load(Archive& ar, const unsigned int version) {
	ar & boost::serialization::make_nvp("pmdFile", mPmdFileName );
	mModel=::MMD::MMDDataBase::loadPMD( mPmdFileName.c_str() );
}


EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(TemplatePMD);

}}// namespace XmlLoader::MMD