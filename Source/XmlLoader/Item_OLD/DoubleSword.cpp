#include"DoubleSword.h"
#include"Serialization/Accessory.h"
#include"Serialization/Shape.h"
#include"Serialization/AccessoryUtils/Hook.h"

#include"GameObject/Accessory.h"

#include"MMD/HumanModel.h"

#include<fstream>
#include<iostream>
#include<sstream>

#pragma warning (push)
#pragma warning( disable : 4244 )

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#pragma warning (pop) 


#include<boost/archive/text_iarchive.hpp>
#include<boost/archive/text_oarchive.hpp>

#include<boost/archive/xml_iarchive.hpp>
#include<boost/archive/xml_oarchive.hpp>


#include<boost/serialization/serialization.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>

#include<GameLib/FileIO/InFile.h>

//#include"Serialization/AccessoryHook.h"


#include<assert.h>
namespace Serialization {
namespace Item{
	namespace{
		namespace defalut{
			const std::string skAccessoryModelXmlFile="Data/Serialization/AccessoryModel/negi.xml";
		}
	}

DoubleSword::DoubleSword()
{
	using namespace GameObjectData;
	name_ = "‘oŒ•";
	action_ = SWING;
	explanation_ = "‘oŒ•";	
};

DoubleSword::~DoubleSword(){
}


bool DoubleSword::loadBinary( const char *fileName ){
	std::ifstream in_file( fileName, std::ios::binary );
	boost::archive::binary_iarchive in_archive(in_file);
	in_archive >> *this;
	return true;
}
bool DoubleSword::loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	// .data() doesn't have a terminal \0. It's not a c-string(char*).
	//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
	std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
	boost::archive::binary_iarchive in_archive( in_file );
	in_archive >> *this;
	return true;
}

bool DoubleSword::saveBinary( const char *fileName )const{
	std::ofstream out_file( fileName, std::ios::binary );
	boost::archive::binary_oarchive out_archive(out_file);
	out_archive << *this;
	return true;
}

bool DoubleSword::loadText( const char *fileName ){
	std::ifstream in_file( fileName );
	boost::archive::text_iarchive in_archive(in_file);
	in_archive >> *this;
	return true;
}

bool DoubleSword::loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	std::istringstream in_file( infileInArchive.data() );
	boost::archive::text_iarchive in_archive(in_file);
	in_archive >> *this;
	return true;
}

bool DoubleSword::saveText( const char *fileName )const{
	std::ofstream out_file( fileName );
	boost::archive::text_oarchive out_archive(out_file);
	out_archive << *this;
	return true;
}


bool DoubleSword::loadXML( const char *fileName ){
	std::ifstream in_file( fileName );
	boost::archive::xml_iarchive in_archive(in_file);
	in_archive >>  boost::serialization::make_nvp("DoubleSword", *this );
	return true;
}
bool DoubleSword::loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	// .data() doesn't have a terminal \0. It's not a c-string(char*).
	//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
	std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
	boost::archive::xml_iarchive in_archive( in_file );
	in_archive >>  boost::serialization::make_nvp("DoubleSword", *this );
	return true;
}
bool DoubleSword::saveXML( const char *fileName )const{
	std::ofstream out_file( fileName );
	boost::archive::xml_oarchive out_archive(out_file);
	out_archive << boost::serialization::make_nvp( "DoubleSword", *this );
	return true;
}

//void DoubleSword::print( std::ostringstream &ss )const{
//	ss <<
//		"name_				= " << name_			<< std::endl <<
//		"explanation_		= " << explanation_		<< std::endl <<
//		"action_			= " << action_			<< std::endl <<
//		"statuses_.size()	= " << statuses_.size()	<< std::endl ;
//
//	for( unsigned int i=0, size=statuses_.size(); i<size; ++i ){
//		ss << i << "-----------------------" <<std::endl;
//		statuses_[i]->print(ss);
//
//
//	}
//}

void DoubleSword::buildAccessories( MMD::HumanModel* model, btCollisionObject* owner,  const GameObjectData::StatusSharedPtr &ownerSt  ){
	
	GameObject::AccessoryUtils::MME::ModelSharedPtr accessoryModelR = mAccessoryR.createModel();
	std::shared_ptr<btCollisionShape> shapeR = mAccessoryR.createBtCollisionShape();

	float mass=0.f;
	GameObject::AccessorySharedPtr accessoryR = std::make_shared<GameObject::Accessory>( 
		shapeR,
		accessoryModelR,
		mass,
		owner,
		btTransform::getIdentity() );
	
	GameObject::AccessoryUtils::MME::ModelSharedPtr accessoryModelL = mAccessoryL.createModel();
	std::shared_ptr<btCollisionShape> shapeL = mAccessoryL.createBtCollisionShape();

	GameObject::AccessorySharedPtr accessoryL = std::make_shared<GameObject::Accessory>( 
		shapeL,
		accessoryModelL,
		mass,
		owner,
		btTransform::getIdentity() );

	assert(
		mHooksR[0].getBoneName()==mHooksR[1].getBoneName() &&
		mHooksR[0].getBoneName()==mHooksR[2].getBoneName() );
	CBone* rightHandBone = model->getBone( mHooksR[0].getBoneName().c_str() );
	model->addHookToSwingAnim( 0, mHooksR[0].createHook( accessoryR, rightHandBone ) );
	model->addHookToSwingAnim( 1, mHooksR[1].createHook( accessoryR, rightHandBone ) );
	model->addHookToSwingAnim( 2, mHooksR[2].createHook( accessoryR, rightHandBone ) );

	accessoryR->attachBone( rightHandBone );
	accessoryR->enableContactResponse( false );

	assert(
		mHooksL[0].getBoneName()==mHooksL[1].getBoneName() &&
		mHooksL[0].getBoneName()==mHooksL[2].getBoneName() );
	CBone* leftHandBone = model->getBone( mHooksL[0].getBoneName().c_str() );
	
	model->addHookToSwingAnim( 0, mHooksL[0].createHook( accessoryL, leftHandBone ) );
	model->addHookToSwingAnim( 1, mHooksL[1].createHook( accessoryL, leftHandBone ) );
	model->addHookToSwingAnim( 2, mHooksL[2].createHook( accessoryL, leftHandBone ) );

	accessoryL->attachBone( leftHandBone );
	accessoryL->enableContactResponse( false );
}

}//end namespace Item
}//end namespace Serialization

