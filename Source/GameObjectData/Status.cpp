#include"Status.h"
#include<fstream>
#include<iostream>
#include<GameLib/FileIO/InFile.h>
#include<sstream>
#include<GameLib/GameLib.h>

#include"helper/BoostSerializationMacros.h"


namespace GameObjectData{

Status::Status()
	:hp(),
	mp(), 
	lp(), 
	stamina(), 
	str(),
	inte(),
	will(),
	dex(),
	qui(),
	vit(),
	psy(),
	luck(),
	elementalDefs(0),
	downValue(0),
	staggerValue(0),
	elapsedTimeAfterDamaged(0),
	group(0),
	damageCorrectedRate(0),
	canStagger(true),
	unContrableTime(0),
	mutekiTime(0),
	powerGauge(0),
	mass( 30.f),
	speed(50.f),
	speedLow(25.f),
	speedHigh(75.f),
	jumpSpeed( 14.f ),
	angleSpeed(3.14f),
	accel( 2.f ),
	usageStaminaPerSecSpeedHigh(30),
	usageStaminaPerSecSpeed(1),		
	usageStaminaPerSecSpeedLow(1),		
	usageStaminaPerJump(10),
	healingStaminaPerSec(15)
{}

bool Status::loadBinary( const char *fileName ){
	std::ifstream in_file( fileName, std::ios::binary );
	boost::archive::binary_iarchive in_archive(in_file);
	in_archive >> *this;
	return true;
}
bool Status::loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	// .data() doesn't have a terminal \0. It's not a c-string(char*).
	//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
	std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
	boost::archive::binary_iarchive in_archive( in_file );
	in_archive >> *this;
	return true;
}
bool Status::saveBinary( const char *fileName ){
	std::ofstream out_file( fileName, std::ios::binary );
	boost::archive::binary_oarchive out_archive(out_file);
	out_archive << static_cast<const Status &>(*this);
	return true;
}

bool Status::loadText( const char *fileName ){
	std::ifstream in_file( fileName );
	boost::archive::text_iarchive in_archive(in_file);
	in_archive >> *this;
	return true;
}

bool Status::loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	std::istringstream in_file( infileInArchive.data() );
	boost::archive::text_iarchive in_archive(in_file);
	in_archive >> *this;
	return true;
}
bool Status::saveText( const char *fileName ){
	std::ofstream out_file( fileName );
	boost::archive::text_oarchive out_archive(out_file);
	out_archive << static_cast<const Status &>(*this);
	return true;
}

bool Status::loadXML( const char *fileName ){
	std::ifstream in_file( fileName );
	boost::archive::xml_iarchive in_archive(in_file);
	in_archive >>  boost::serialization::make_nvp("Status", *this );
	return true;
}
bool Status::loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	// .data() doesn't have a terminal \0. It's not a c-string(char*).
	//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
	std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
	boost::archive::xml_iarchive in_archive( in_file );
	in_archive >>  boost::serialization::make_nvp("Status", *this );
	return true;
}
bool Status::saveXML( const char *fileName ){
	std::ofstream out_file( fileName );
	boost::archive::xml_oarchive out_archive(out_file);
	out_archive << boost::serialization::make_nvp( "Status", static_cast<const Status &>(*this) );
	return true;
}

void Status::reset(){
	hp.setValueToMax();
	mp.setValueToMax();
	lp.setValueToMax();
	stamina.setValueToMax();
	downValue=0;
	staggerValue=0;
	elapsedTimeAfterDamaged=0;
	group=0;
	damageCorrectedRate=0;
	canStagger=true;
	unContrableTime=0;
	mutekiTime=0;
	powerGauge=0;
}

void Status::update( float dt ){
	downValue;
	staggerValue;
	elapsedTimeAfterDamaged+=dt;
	damageCorrectedRate;
	unContrableTime-=dt;
	mutekiTime-=dt;
}

StatusSharedPtr Status::clone() const {
	return StatusSharedPtr(NEW Status(*this));
}


template<class Archive>
void Status::load(Archive& ar, const unsigned int version) {

	unsigned char read;
	ar & boost::serialization::make_nvp("str", read);
	str.init(0.f, 1.5f*read, read);
	ar & boost::serialization::make_nvp("inte", read);
	inte.init(0.f, 1.5f*read, read);
	ar & boost::serialization::make_nvp("will", read);
	will.init(0.f, 1.5f*read, read);
	ar & boost::serialization::make_nvp("dex", read);
	dex.init(0.f, 1.5f*read, read);
	ar & boost::serialization::make_nvp("qui", read);
	qui.init(0.f, 1.5f*read, read);
	ar & boost::serialization::make_nvp("vit", read);
	vit.init(0.f, 1.5f*read, read);
	ar & boost::serialization::make_nvp("psy", read);
	psy.init(0.f, 1.5f*read, read);
	ar & boost::serialization::make_nvp("luck", read);
	luck.init(0.f, 1.5f*read, read);

	float maxHp;
	float maxMp;
	float maxLp;
	float maxStamina;

	ar & boost::serialization::make_nvp("maxHp", maxHp);
	hp.init(0.f, maxHp, maxHp);
	ar & boost::serialization::make_nvp("maxMp", maxMp);
	mp.init(0.f, maxMp, maxMp);
	ar & boost::serialization::make_nvp("maxLp", maxLp);
	lp.init(0.f, maxLp, maxLp);
	ar & boost::serialization::make_nvp("maxStamina", maxStamina);
	stamina.init(0.f, maxStamina, maxStamina);


	ar & boost::serialization::make_nvp("elementalDefs", elementalDefs);

	ar & boost::serialization::make_nvp("mass", mass);

	ar & boost::serialization::make_nvp("speed", speed);
	ar & boost::serialization::make_nvp("speedLow", speedLow);
	ar & boost::serialization::make_nvp("speedHigh", speedHigh);
	ar & boost::serialization::make_nvp("angleSpeed", angleSpeed);
	ar & boost::serialization::make_nvp("jumpSpeed", jumpSpeed);

	ar & boost::serialization::make_nvp("accel", accel);


	ar & boost::serialization::make_nvp("usageStaminaPerSecSpeedHigh", usageStaminaPerSecSpeedHigh);
	ar & boost::serialization::make_nvp("usageStaminaPerSecSpeed", usageStaminaPerSecSpeed);
	ar & boost::serialization::make_nvp("usageStaminaPerSecSpeedLow", usageStaminaPerSecSpeedLow);
	ar & boost::serialization::make_nvp("usageStaminaPerJump", usageStaminaPerJump);
	ar & boost::serialization::make_nvp("healingStaminaPerSec", healingStaminaPerSec);

	ar & boost::serialization::make_nvp("group", group);
}


template<class Archive>
void Status::save(Archive& ar, const unsigned int version)const {
	using boost::serialization::make_nvp;
	assert(false && "一回もデバッグしてない");
	unsigned char read;
	read = static_cast<unsigned char>(str.getDefault());
	ar & boost::serialization::make_nvp("str", read);
	read = static_cast<unsigned char>(inte.getDefault());
	ar & boost::serialization::make_nvp("inte", read);
	read = static_cast<unsigned char>(will.getDefault());
	ar & boost::serialization::make_nvp("will", read);
	read = static_cast<unsigned char>(dex.getDefault());
	ar & boost::serialization::make_nvp("dex", read);
	read = static_cast<unsigned char>(qui.getDefault());
	ar & boost::serialization::make_nvp("qui", read);
	read = static_cast<unsigned char>(vit.getDefault());
	ar & boost::serialization::make_nvp("vit", read);
	read = static_cast<unsigned char>(psy.getDefault());
	ar & boost::serialization::make_nvp("psy", read);
	read = static_cast<unsigned char>(luck.getDefault());
	ar & boost::serialization::make_nvp("luck", read);

	float maxHp=hp.getMax();
	float maxMp=mp.getMax();
	float maxLp=lp.getMax();
	float maxStamina=stamina.getMax();

	ar & boost::serialization::make_nvp("maxHp", maxHp);
	ar & boost::serialization::make_nvp("maxMp", maxMp);
	ar & boost::serialization::make_nvp("maxLp", maxLp);
	ar & boost::serialization::make_nvp("maxStamina", maxStamina);

	ar & boost::serialization::make_nvp("elementalDefs", elementalDefs);

	ar & boost::serialization::make_nvp("mass", mass);

	ar & boost::serialization::make_nvp("speed", speed);
	ar & boost::serialization::make_nvp("speedLow", speedLow);
	ar & boost::serialization::make_nvp("speedHigh", speedHigh);
	ar & boost::serialization::make_nvp("angleSpeed", angleSpeed);
	ar & boost::serialization::make_nvp("jumpSpeed", jumpSpeed);

	ar & boost::serialization::make_nvp("accel", accel);


	ar & boost::serialization::make_nvp("usageStaminaPerSecSpeedHigh", usageStaminaPerSecSpeedHigh);
	ar & boost::serialization::make_nvp("usageStaminaPerSecSpeed", usageStaminaPerSecSpeed);
	ar & boost::serialization::make_nvp("usageStaminaPerSecSpeedLow", usageStaminaPerSecSpeedLow);
	ar & boost::serialization::make_nvp("usageStaminaPerJump", usageStaminaPerJump);
	ar & boost::serialization::make_nvp("healingStaminaPerSec", healingStaminaPerSec);

	ar & boost::serialization::make_nvp("group", group);

}

SPLIT_SERIALIZE_IMPL(Status);
EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION( Status );
}// GameObjectData

BOOST_CLASS_IMPLEMENTATION( GameObjectData::Status, boost::serialization::object_serializable );
