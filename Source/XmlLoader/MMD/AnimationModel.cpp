#include"AnimationModel.h"
#include"XmlLoader/MMD/TemplatePmd.h"
#include"XmlLoader/Shape.h"
#include"XmlLoader/MMD/AnimationState/IAnimationState.h"

#include<GameLib/GameLib.h>

#include<GameLib/FileIO/InFile.h>
#include<GameLib/PseudoXml/Document.h>
#include<GameLib/PseudoXml/Attribute.h>
#include<GameLib/PseudoXml/Element.h>

#include"helper/XmlHelperFuncs.h"
#include<boost/optional.hpp>

#include"MME/Object/Model.h"
#include"MMD/AnimationState/IAnimationState.h"

#include"MMD/AnimationModel.h"

#include"helper/BoostSerializationMacros.h"

namespace XmlLoader { namespace MMD{

AnimationModel::AnimationModel()
	:mHeightOffset(0.f),
	mNumAnimations(0),
	mFile(0),
	mIsFileFinished(false)
{
	mFile = new GameLib::FileIO::InFile();
	mModel = std::make_shared<MMD::TemplatePMD>();
	mShape = std::make_shared<Shape>();
	
}
AnimationModel::~AnimationModel(){
	delete mFile;
	mFile=0;
}
//
bool AnimationModel::loadStart( const std::string &fileName ){
	using namespace GameLib::PseudoXml;
	using namespace XmlHelperFuncs;

	using GameLib::RefString;
	*mFile = GameLib::FileIO::InFile::create( fileName.c_str() );
	if( mFile->isError() ){
		STRONG_ASSERT(false && "file not found");
		return false;
	}
	return true;
}

bool AnimationModel::isReady(){
	if(mFile){
		if( mFile->isFinished() ){
			if(mIsFileFinished){
				return isModelReady() && isAnimationsReady();
			}else {
				mIsFileFinished=true;
				std::istringstream in_file( 
					std::string(mFile->data(), mFile->size()),
					std::ios::binary || std::ios::in );
				boost::archive::text_iarchive in_archive(in_file, boost::archive::no_header );
				in_archive >> *this;
				return false;
			}
		}
	}
	return false;
}

bool AnimationModel::isModelReady(){
	if(!mModel->isReady()){
		return false;
	}
	return true;
}
bool AnimationModel::isAnimationsReady(){
	for( unsigned int i=0, size=mAnimations.size(); i<size; ++i ){
		if(!mAnimations[i]->isReady()){
			return false;
		}
	}
	return true;
}


::MMD::AnimationModelSharedPtr AnimationModel::instance(){
	while( !mModel->isReady() ){}
	::MMD::TemplatePMDSharedPtr pmd = mModel->instance();
	using ::MMD::AnimationState::IAnimationStateSharedPtr;
	
	::MMD::AnimationModelSharedPtr obj(
		new ::MMD::AnimationModel(pmd, true )
	);

	for( unsigned int i=0; i<mNumAnimations; ++i ){
		IAnimationStateSharedPtr anim = mAnimations[i]->instance( obj.get() );
		obj->addAnimState( mAnimations[i]->getName(), anim );
	}

	return obj;
}

template<class Archive>
void AnimationModel::load(Archive& ar, const unsigned int version){
	using boost::serialization::make_nvp;
	ar & make_nvp( "PmdModel", *mModel );

	ar & make_nvp( "Shape", *mShape );

	ar & make_nvp( "heightOffset", mHeightOffset );
	
	ar & make_nvp( "numAnimations", mNumAnimations );
	mAnimations.clear();
	mAnimations.reserve(mNumAnimations);
	for( unsigned int i=0; i<mNumAnimations; ++i ){
		MMD::AnimationState::IAnimationStateSharedPtr anim=std::make_shared<MMD::AnimationState::IAnimationState>();
		ar & make_nvp( "Animation", *anim );
		mAnimations.push_back(anim);
	}
	mAnimations.shrink_to_fit();
}


template<class Archive>
void AnimationModel::save(Archive& ar, const unsigned int version)const{
	using boost::serialization::make_nvp;
	ar & make_nvp( "PmdModel", *mModel );

	ar & make_nvp( "Shape", *mShape );

	ar & make_nvp( "heightOffset", mHeightOffset );
	
	ar & make_nvp( "numAnimations", mNumAnimations );
	for( unsigned int i=0; i<mNumAnimations; ++i ){
		ar & make_nvp( "Animation", *mAnimations[i] );
	}
}

SPLIT_SERIALIZE_IMPL( AnimationModel );


EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(AnimationModel);

} }//end namespace XmlLoader::MMD

BOOST_CLASS_IMPLEMENTATION(XmlLoader::MMD::AnimationModel, boost::serialization::object_serializable);
