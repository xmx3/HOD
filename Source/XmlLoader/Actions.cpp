#include"Actions.h"
#include"XmlLoader/GameObject/Accessory.h"
#include"XmlLoader/MMD/AnimationState/IAnimationState.h"
#include"XmlLoader/MMD/AnimationState/Hook/AccessoryHook.h"

#include"../GameObject/Accessory.h"
#include"../MME/Object/ModelKai.h"
#include"../MMD/AnimationState/IAnimationState.h"

#include<GameLib/GameLib.h>
#include<GameLib/FileIO/InFile.h>
#include<sstream>


#include"helper/BoostSerializationMacros.h"
#include<LinearMath/btTransform.h>

namespace XmlLoader{

Actions::Actions()
	:mIsXmlFileFinished(false),
	mFile(nullptr),
	mNumAccessories(0),
	mAccessories(nullptr),
	mNumAnimations(0),
	mAnimations(nullptr),
	mNumAccessoryHooks(0),
	mAccessoryHooks(nullptr)
{
}

Actions::~Actions(){
	SAFE_DELETE( mFile );
	SAFE_DELETE_ARRAY(mAccessories);
	SAFE_DELETE_ARRAY(mAnimations);
	SAFE_DELETE_ARRAY(mAccessoryHooks);
}

bool Actions::isReady(){
	//ここバグる気がする
	//<parent>
	//	<Actions/>
	//</parent>
	//のようなデータ構造あったら
	//ここのプログラムは自信がloadStartされるのが前提
	//今直すきはないのでちょっとassertかましておく
	if(mFile){
		if( mFile->isFinished() ){
			if(mIsXmlFileFinished){
				return areAccessoriesReady() && areAnimationsReady();
			}else {
				mIsXmlFileFinished=true;
				std::istringstream in_file( 
					std::string(mFile->data(), mFile->size()),
					std::ios::binary || std::ios::in );
				boost::archive::xml_iarchive in_archive(in_file, boost::archive::no_header );
				in_archive >> boost::serialization::make_nvp("Actions", *this );
				return false;
			}
		}
	}
	return false;

}

bool Actions::areAccessoriesReady(){
	for( int i=0; i<mNumAccessories; ++i ){
		if(!mAccessories[i].isReady())
		{
			return false;
		}
	}
	return true;
}

bool Actions::areAnimationsReady(){
	for( int i=0; i<mNumAnimations; ++i ){
		if( !mAnimations[i].isReady() ){
			return false;
		}
	}
	return true;
}

void Actions::instance(
	::MME::Object::ModelKai *model,
	btCollisionObject* owner,//accessoryが親を無視するために必要
	::GameObjectData::StatusSharedPtr status//武器が攻撃力を求めるために必要 
) {
	typedef ::GameObject::AccessorySharedPtr InstanceAccessory;
	//std::map< std::string,  InstanceAccessory> accessories;
	for( int i=0; i<mNumAccessories; ++i ){
		while(!mAccessories[i].isReady()){}
		InstanceAccessory ac = mAccessories[i].instance( owner, btTransform::getIdentity() );
		
		//std::map< std::string,  InstanceAccessory>::_Pairib ib =
		//	accessories.insert( 
		//		std::make_pair( mAccessories[i].getName(), ac ) );
		//assert(ib.second && "accessory name is doubled!" );
		model->addAccessory( mAccessories[i].getName(), ac );
	}

	typedef ::MMD::AnimationState::IAnimationStateSharedPtr InstanceAnim;
	std::map< std::string, InstanceAnim > animations;
	for( int i=0; i<mNumAnimations; ++i ){
		InstanceAnim anim = mAnimations[i].instance( model->getAnimationModel() );
		animations.insert( std::make_pair(mAnimations[i].getName(), anim) );
		model->addAnimState( mAnimations[i].getName(), anim );
	}

	typedef ::MMD::AnimationState::Hook::IHookSharedPtr InstanceHook;
	for( int i=0; i<mNumAccessoryHooks; ++i ){
		InstanceAccessory ac = 
			model->getAccessory( mAccessoryHooks[i].getAccessoryName() );
		//InstanceAccessory ac =
			//accessories.at( mAccessoryHooks[i].getAccessoryName() );

		::MMD::Bone *bone = model->getBone( mAccessoryHooks[i].getBoneName().c_str() );

		InstanceHook hook = mAccessoryHooks[i].instance( ac, bone, status );
		InstanceAnim anim = animations.at( mAccessoryHooks[i].getTargetAnimation() );
		anim->addHook( hook );
	}
}

bool Actions::loadStart( const std::string & xmlFileName ){
	SAFE_DELETE(mFile);

	mFile = new GameLib::FileIO::InFile();

	*mFile = GameLib::FileIO::InFile::create( xmlFileName.c_str() );
	if( mFile->isError() ){
		STRONG_ASSERT(false && "file not found");
		return false;
	}
	return true;
}


template<class Archive>
void Actions::load(Archive& ar, const unsigned int version){
	using boost::serialization::make_nvp;
	ar & make_nvp( "name", mName );

	ar & make_nvp( "numAccessories", mNumAccessories );
	SAFE_DELETE_ARRAY( mAccessories );
	mAccessories = new GameObject::Accessory[mNumAccessories];

	for( int i=0; i<mNumAccessories; ++i ){
		std::stringstream name;
		name << "Accessory" <<i;
		ar & make_nvp( name.str().c_str(), mAccessories[i] );
	}
	
	ar & make_nvp( "numAnimations", mNumAnimations );
	SAFE_DELETE_ARRAY( mAnimations );
	mAnimations = new MMD::AnimationState::IAnimationState[mNumAnimations];

	for( int i=0; i<mNumAnimations; ++i ){
		std::stringstream name;
		name << "Animation" <<i;
		ar & make_nvp( name.str().c_str(), mAnimations[i] );
	}
	
	ar & make_nvp( "numAccessoryHooks", mNumAccessoryHooks );
	SAFE_DELETE_ARRAY( mAccessoryHooks );
	mAccessoryHooks = new MMD::AnimationState::Hook::AccessoryHook[mNumAccessoryHooks];

	for( int i=0; i<mNumAccessoryHooks; ++i ){
		std::stringstream name;
		name << "AccessoryHook" <<i;
		ar & make_nvp( name.str().c_str(), mAccessoryHooks[i] );
	}
}


template<class Archive>
void Actions::save(Archive& ar, const unsigned int version)const{
	using boost::serialization::make_nvp;
	ar & make_nvp( "name", mName );

	ar & make_nvp( "numAccessories", mNumAccessories );
	for( int i=0; i<mNumAccessories; ++i ){
		std::stringstream name;
		name << "Accessory" <<i;
		ar & make_nvp( name.str().c_str(), mAccessories[i] );
	}
	
	ar & make_nvp( "numAnimations", mNumAnimations );
	for( int i=0; i<mNumAnimations; ++i ){
		std::stringstream name;
		name << "Animation" <<i;
		ar & make_nvp( name.str().c_str(), mAnimations[i] );
	}
	
	ar & make_nvp( "numAccessoryHooks", mNumAccessoryHooks );
	for( int i=0; i<mNumAccessoryHooks; ++i ){
		std::stringstream name;
		name << "AccessoryHook" <<i;
		ar & make_nvp( name.str().c_str(), mAccessoryHooks[i] );
	}
}

SPLIT_SERIALIZE_IMPL( Actions );
EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(Actions);

}//XmlLoader


BOOST_CLASS_IMPLEMENTATION(XmlLoader::Actions, boost::serialization::object_serializable);
