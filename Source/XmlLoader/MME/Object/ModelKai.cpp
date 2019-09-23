#include"ModelKai.h"
#include"XmlLoader/MMD/TemplatePmd.h"
#include"XmlLoader/Shape.h"
#include"XmlLoader/MMD/AnimationState/IAnimationState.h"


#include"MME/Object/ModelKai.h"

#include<GameLib/GameLib.h>

#include<GameLib/FileIO/InFile.h>
#include<assert.h>
#include"helper/XmlHelperFuncs.h"
#include<boost/optional.hpp>
#include"helper/BoostSerializationMacros.h"


namespace XmlLoader{ namespace MME { namespace Object {

ModelKai::ModelKai()
	:mHeightOffset(0.f),
	mNumAnimations(0),
	mAnimations(NULL),
	mFile(nullptr),
	mModel(nullptr)
{
	mModel = std::make_shared<MMD::TemplatePMD>();
}
ModelKai::~ModelKai(){
	delete mFile;
	mFile=0;
	delete [] mAnimations;
	mAnimations=0;
}
//
bool ModelKai::loadStart( const std::string &fileName ){
	mFile = new GameLib::FileIO::InFile();	
	*mFile = GameLib::FileIO::InFile::create( fileName.c_str() );
	if( mFile->isError() ){
		STRONG_ASSERT(false && "file not found");
		return false;
	}
	return true;
}

bool ModelKai::isReady(){
	if(mFile){
		if( mFile->isFinished() ){
			std::istringstream in_file( 
				std::string(mFile->data(), mFile->size()),
				std::ios::binary || std::ios::in );
			boost::archive::xml_iarchive in_archive(in_file, boost::archive::no_header );
			in_archive >> boost::serialization::make_nvp("ModelKai", *this );
			SAFE_DELETE(mFile);
			return false;
		}
	} else{
		return isModelReady() && isAnimationsReady();
	}
	return false;
}

bool ModelKai::isModelReady(){
	if(!mModel->isReady()){
		return false;
	}
	return true;
}
bool ModelKai::isAnimationsReady(){
	for( unsigned int i=0; i<mNumAnimations; ++i ){
		if(!mAnimations[i].isReady()){
			return false;
		}
	}
	return true;
}


ModelKai::InstanceModelKaiSharedPtr ModelKai::instance(){
	while( !mModel->isReady() ){}
	::MMD::TemplatePMDSharedPtr pmd = mModel->instance();
	using ::MMD::AnimationState::IAnimationStateSharedPtr;
	namespace Instance=::MME::Object;

	Instance::ModelKaiSharedPtr obj=
		Instance::ModelKai::create( pmd, true, mHeightOffset );

	for( unsigned int i=0; i<mNumAnimations; ++i ){
		IAnimationStateSharedPtr anim = mAnimations[i].instance( obj->getAnimationModel() );
		obj->addAnimState( mAnimations[i].getName(), anim );
	}

	return obj;
}

template<class Archive>
void ModelKai::load(Archive& ar, const unsigned int version){
	using boost::serialization::make_nvp;
	ar & make_nvp( "PmdModel", *mModel );

	ar & make_nvp( "heightOffset", mHeightOffset );
	
	ar & make_nvp( "numAnimations", mNumAnimations );
	delete [] mAnimations;
	mAnimations=NULL;

	mAnimations = new MMD::AnimationState::IAnimationState[mNumAnimations];

	for( unsigned int i=0; i<mNumAnimations; ++i ){
		ar & make_nvp( "Animation", mAnimations[i] );
	}
}


template<class Archive>
void ModelKai::save(Archive& ar, const unsigned int version)const{
	using boost::serialization::make_nvp;
	ar & make_nvp( "PmdModel", *mModel );

	ar & make_nvp( "heightOffset", mHeightOffset );
	
	ar & make_nvp( "numAnimations", mNumAnimations );
	for( unsigned int i=0; i<mNumAnimations; ++i ){
		ar & make_nvp( "Animation", mAnimations[i] );
	}
}

SPLIT_SERIALIZE_IMPL( ModelKai );


EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(ModelKai);

} } }// namespace XmlLoader::MME::Object
BOOST_CLASS_IMPLEMENTATION(XmlLoader::MME::Object::ModelKai, boost::serialization::object_serializable);
