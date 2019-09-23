#include"TestWeaponStatus.h"
#include"Status.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<boost/archive/binary_iarchive.hpp>
#include<boost/archive/binary_oarchive.hpp>

#include<boost/archive/text_iarchive.hpp>
#include<boost/archive/text_oarchive.hpp>

#include<boost/archive/xml_iarchive.hpp>
#include<boost/archive/xml_oarchive.hpp>


#include<boost/serialization/serialization.hpp>

#include<GameLib/FileIO/InFile.h>

namespace GameObjectData{


SwordWeaponStatus::SwordWeaponStatus()
	:		
damageTypes_(0),
atk_(4000),	
damageCorrectedRate_(0.f),
downValue_(0),	
staggerValue_(0),	 	
unControlableTime_(0),
stamina_(0),
accessoryName_(),
hitStartFrame_(0),
hitEndFrame_(0),
equipBoneName_()
{
}

SwordWeaponStatus::SwordWeaponStatus( StatusSharedPtr status )
	:		
damageTypes_(0),
atk_(4000),	
damageCorrectedRate_(0.f),
downValue_(0),	
staggerValue_(0),	 	
unControlableTime_(0),
stamina_(0),
accessoryName_(),
hitStartFrame_(0),
hitEndFrame_(0),
equipBoneName_(),
me_(status)
{
}


bool SwordWeaponStatus::loadBinary( const char *fileName ){
	std::ifstream in_file( fileName, std::ios::binary );
	boost::archive::binary_iarchive in_archive(in_file);
	in_archive >> *this;
	return true;
}
bool SwordWeaponStatus::loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	// .data() doesn't have a terminal \0. It's not a c-string(char*).
	//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
	std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
	boost::archive::binary_iarchive in_archive( in_file );
	in_archive >> *this;
	return true;
}

bool SwordWeaponStatus::saveBinary( const char *fileName )const{
	std::ofstream out_file( fileName, std::ios::binary );
	boost::archive::binary_oarchive out_archive(out_file);
	out_archive << static_cast<const SwordWeaponStatus &>(*this);
	return true;
}

bool SwordWeaponStatus::loadText( const char *fileName ){
	std::ifstream in_file( fileName );
	boost::archive::text_iarchive in_archive(in_file);
	in_archive >> *this;
	return true;
}

bool SwordWeaponStatus::loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	std::istringstream in_file( infileInArchive.data() );
	boost::archive::text_iarchive in_archive(in_file);
	in_archive >> *this;
	return true;
}

bool SwordWeaponStatus::saveText( const char *fileName )const{
	std::ofstream out_file( fileName );
	boost::archive::text_oarchive out_archive(out_file);
	out_archive << static_cast<const SwordWeaponStatus &>(*this);
	return true;
}


bool SwordWeaponStatus::loadXML( const char *fileName ){
	std::ifstream in_file( fileName );
	boost::archive::xml_iarchive in_archive(in_file);
	in_archive >>  boost::serialization::make_nvp("SwordWeaponStatus", *this );
	return true;
}
bool SwordWeaponStatus::loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	// .data() doesn't have a terminal \0. It's not a c-string(char*).
	//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
	std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
	boost::archive::xml_iarchive in_archive( in_file );
	in_archive >>  boost::serialization::make_nvp("SwordWeaponStatus", *this );
	return true;
}
bool SwordWeaponStatus::saveXML( const char *fileName )const{
	std::ofstream out_file( fileName );
	boost::archive::xml_oarchive out_archive(out_file);
	out_archive << boost::serialization::make_nvp( "SwordWeaponStatus", static_cast<const SwordWeaponStatus &>(*this) );
	return true;
}

void SwordWeaponStatus::attack( Status *enemy )
{
	if( StatusSharedPtr myStatus = me_.lock()){
		if( enemy->group != myStatus->group  ){
			unsigned int atk = atk_ * ( myStatus->str * (100+myStatus->strRate)/100 ) * (100 - enemy->damageCorrectedRate) / 10000;
			unsigned int def = enemy->calcDef( damageTypes_ );
			static const int ushrtMax = std::numeric_limits<unsigned short>::max();
		
			if( atk > def ){
				enemy->hp = enemy->hp > (atk-def) ? enemy->hp - (atk-def) : 0;
				enemy->damageCorrectedRate += static_cast<unsigned char>(damageCorrectedRate_*100);
				if( enemy->damageCorrectedRate>99 ){
					enemy->damageCorrectedRate=99;
				}
				enemy->downValue += downValue_;
				enemy->staggerValue += staggerValue_;
				//check over flow;
				enemy->elapsedTimeAfterDamaged = 0.f;
				if( enemy->canStagger ){
					if( enemy->staggerValue > 99 ){
						//mStateMacine->process_event( EvOveredStaggerValue );
					}
				}
				if( enemy->downValue > 99 ){
						//mStateMacine->process_event( EvOveredDownValue );
				}
			}

			//for( unsigned int i=0, size=additionalEffects.size(); i<size; ++i ){
			//	additionalEffects[i]->exec( enemy );
			//}
		}
	}else{
		assert(false && "me must not be NULL.");
	}
}

void SwordWeaponStatus::print( std::ostringstream &ss ) const{
	ss <<
		"hitbackValue_				= "<<	hitbackValue_ 			<< std::endl <<
		"canCollideOnlyOnce_		= "<<	canCollideOnlyOnce_		<< std::endl <<
		"damageTypes_				= "<<	(int)damageTypes_		<< std::endl <<
		"atk_						= "<<	atk_ 					<< std::endl <<
		"damageCorrectedRate_		= "<<	damageCorrectedRate_	<< std::endl << 
		"downValue_					= "<<	(int)downValue_			<< std::endl <<
		"staggerValue_				= "<<	(int)staggerValue_		<< std::endl <<
		"unControlableTime_			= "<<	unControlableTime_		<< std::endl <<
		"stamina_					= "<<	stamina_				<< std::endl <<
		"accessoryName_				= "<<	accessoryName_			<< std::endl <<
		"hitStartFrame_				= "<<	hitStartFrame_			<< std::endl <<
		"hitEndFrame_				= "<<	hitEndFrame_			<< std::endl <<
		"equipBoneName_				= "<<	equipBoneName_			<< std::endl ;
}

}//end namespace GameObjectData