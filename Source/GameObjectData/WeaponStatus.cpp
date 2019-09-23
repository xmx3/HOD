#include"WeaponStatus.h"
#include"Status.h"
#include<fstream>
#include<iostream>
#include<sstream>

#include"helper/BoostSerializationMacros.h"
//#pragma warning (push)
//#pragma warning( disable : 4244 )
//
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
//
//#pragma warning (pop) 
//
//#include<boost/archive/text_iarchive.hpp>
//#include<boost/archive/text_oarchive.hpp>
//
//#include<boost/archive/xml_iarchive.hpp>
//#include<boost/archive/xml_oarchive.hpp>
//
//
//#include<boost/serialization/serialization.hpp>

#include<GameLib/FileIO/InFile.h>

namespace GameObjectData{

WeaponStatus::WeaponStatus( StatusSharedPtr status )
	:damageTypes(0),
	atkHp(4000),
	atkMp(0),
	atkLp(0),
	atkStamina(0),
	damageCorrectedRate(0),
	downValue(0),
	staggerValue(0),
	unControlableTime(0),
	upDownwardOffset(0),
	canCollideOnlyOnce(false),
	hitbackValue(0.f),
	//blowValue(0.f),
	staminaPerAttack(0),
	me(status)
{
	// knockBackNormalVel[0]=0.f;
	// knockBackNormalVel[1]=0.f;
	// knockBackNormalVel[2]=0.f;
	// knockBackVelSpeed[0]=0.f;
	// knockBackVelSpeed[1]=0.f;
	// knockBackVelSpeed[2]=0.f;
}


WeaponStatus::WeaponStatus()
	:damageTypes(0),
	atkHp(4000),
	atkMp(0),
	atkLp(0),
	atkStamina(0),
	damageCorrectedRate(0),
	downValue(0),
	staggerValue(0),
	unControlableTime(0),
	upDownwardOffset(0),
	canCollideOnlyOnce(false),
	hitbackValue(0.f),
	//blowValue(0.f),
	staminaPerAttack(0),
	me()
{
	//knockBackNormalVel[0]=0.f;
	//knockBackNormalVel[1]=0.f;
	//knockBackNormalVel[2]=0.f;
	//knockBackVelSpeed[0]=0.f;
	//knockBackVelSpeed[1]=0.f;
	//knockBackVelSpeed[2]=0.f;
}

bool WeaponStatus::loadBinary( const char *fileName ){
	std::ifstream in_file( fileName, std::ios::binary );
	boost::archive::binary_iarchive in_archive(in_file, boost::archive::no_header);
	in_archive >> *this;
	return true;
}
bool WeaponStatus::loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	// .data() doesn't have a terminal \0. It's not a c-string(char*).
	//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
	std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
	boost::archive::binary_iarchive in_archive( in_file, boost::archive::no_header );
	in_archive >> *this;
	return true;
}

bool WeaponStatus::saveBinary( const char *fileName ){
	std::ofstream out_file( fileName, std::ios::binary );
	boost::archive::binary_oarchive out_archive(out_file, boost::archive::no_header);
	out_archive << static_cast<const WeaponStatus &>(*this);
	return true;
}

bool WeaponStatus::loadText( const char *fileName ){
	std::ifstream in_file( fileName );
	boost::archive::text_iarchive in_archive(in_file, boost::archive::no_header);
	in_archive >> *this;
	return true;
}

bool WeaponStatus::loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	std::istringstream in_file( infileInArchive.data() );
	boost::archive::text_iarchive in_archive(in_file, boost::archive::no_header);
	in_archive >> *this;
	return true;
}

bool WeaponStatus::saveText( const char *fileName ){
	std::ofstream out_file( fileName );
	boost::archive::text_oarchive out_archive(out_file, boost::archive::no_header);
	out_archive << static_cast<const WeaponStatus &>(*this);
	return true;
}


bool WeaponStatus::loadXML( const char *fileName ){
	std::ifstream in_file( fileName );
	boost::archive::xml_iarchive in_archive(in_file, boost::archive::no_header);
	in_archive >>  boost::serialization::make_nvp("WeaponStatus", *this );
	return true;
}
bool WeaponStatus::loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	// .data() doesn't have a terminal \0. It's not a c-string(char*).
	//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
	std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
	boost::archive::xml_iarchive in_archive( in_file, boost::archive::no_header );
	in_archive >>  boost::serialization::make_nvp("WeaponStatus", *this );
	return true;
}
bool WeaponStatus::saveXML( const char *fileName ){
	std::ofstream out_file( fileName );
	boost::archive::xml_oarchive out_archive(out_file, boost::archive::no_header);
	out_archive << boost::serialization::make_nvp( "WeaponStatus", static_cast<const WeaponStatus &>(*this) );
	return true;
}


void WeaponStatus::print() const {
	std::cout << int(atkHp) << std::endl;
	std::cout << int(atkLp) << std::endl;
	std::cout << int(atkMp) << std::endl;
	std::cout << int(atkStamina) << std::endl;
	std::cout << int(damageCorrectedRate) << std::endl;
	std::cout << int(damageTypes) << std::endl;
	std::cout << int(downValue) << std::endl;
	//std::cout << int(knockBackNormalVel[0]) << std::endl;
	//std::cout << int(knockBackNormalVel[1]) << std::endl;
	//std::cout << int(knockBackNormalVel[2]) << std::endl;
	//std::cout << int(knockBackVelSpeed[0]) << std::endl;
	//std::cout << int(knockBackVelSpeed[1]) << std::endl;
	//std::cout << int(knockBackVelSpeed[2]) << std::endl;
	std::cout << int(staggerValue) << std::endl;
	std::cout << int(unControlableTime) << std::endl;
	std::cout << int(upDownwardOffset) << std::endl;

}


int WeaponStatus::caluculateDamage( ) const
{
	if (StatusSharedPtr myStatus = me.lock()) {
		int atk = (atkHp * (myStatus->str)) / 100;
		assert(atk >= 0);
		
		return atk;

	}
	else {
		assert(false);
		return 0;
	}
}

template <typename Archive>
void WeaponStatus::serialize(Archive &ar, const unsigned int ver) {
	ar & boost::serialization::make_nvp("damageTypes", damageTypes );
	ar & boost::serialization::make_nvp("atkHp", atkHp );
	ar & boost::serialization::make_nvp("atkMp", atkMp );
	ar & boost::serialization::make_nvp("atkLp", atkLp );
	ar & boost::serialization::make_nvp("atkStamina", atkStamina );
	ar & boost::serialization::make_nvp("damageCorrectedRate", damageCorrectedRate );
	ar & boost::serialization::make_nvp("downValue", downValue ); 
	ar & boost::serialization::make_nvp("staggerValue", staggerValue );
	ar & boost::serialization::make_nvp("unControlableTime", unControlableTime );
	//ar & boost::serialization::make_nvp("knockBackNormalVel", knockBackNormalVel );
	ar & boost::serialization::make_nvp("upDownwardOffset", upDownwardOffset );
	//ar & boost::serialization::make_nvp("knockBackVelSpeed", knockBackVelSpeed );
	ar & boost::serialization::make_nvp("canCollideOnlyOnce", canCollideOnlyOnce );
	ar & boost::serialization::make_nvp("hitbackValue", hitbackValue );
	//ar & boost::serialization::make_nvp("blowValue", blowValue );
	ar & boost::serialization::make_nvp("staminaPerAttack", staminaPerAttack );
}
EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(WeaponStatus);
}//end namespace GameObjectData;

BOOST_CLASS_IMPLEMENTATION(GameObjectData::WeaponStatus, boost::serialization::object_serializable);
