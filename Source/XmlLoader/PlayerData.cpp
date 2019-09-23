#include"PlayerData.h"
#include"Character.h"

#include<assert.h>
#include<fstream>
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

#include<GameLib/FileIO/InFile.h>

#include<time.h>

#include"helper/BoostSerializationMacros.h"

namespace XmlLoader {

PlayerDataSharedPtr PlayerData::create( const std::string &fileName ){
	if( fileName.empty() ){
		return std::make_shared<PlayerData>();
	} else{
		assert(false && "not impl" );
		return 0;
	
	}
}

PlayerData::PlayerData()
	:mClearedStage(0),
	mMiku( new Character )
{
}
PlayerData::~PlayerData()
{
	delete mMiku;
	mMiku=0;
}

bool PlayerData::loadBinary( const char *fileName ){
	std::ifstream in_file( fileName, std::ios::binary );
	boost::archive::binary_iarchive in_archive(in_file, boost::archive::no_header);
	in_archive >> *this;
	return true;
}
bool PlayerData::loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	// .data() doesn't have a terminal \0. It's not a c-string(char*).
	//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
	std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
	boost::archive::binary_iarchive in_archive( in_file, boost::archive::no_header );
	in_archive >> *this;
	return true;
}

bool PlayerData::saveBinary( const char *fileName )const{
	std::ofstream out_file( fileName, std::ios::binary );
	boost::archive::binary_oarchive out_archive(out_file, boost::archive::no_header );
	out_archive << *this;
	return true;
}

bool PlayerData::loadText( const char *fileName ){
	std::ifstream in_file( fileName );
	boost::archive::text_iarchive in_archive(in_file, boost::archive::no_header );
	in_archive >> *this;
	return true;
}

bool PlayerData::loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	std::istringstream in_file( infileInArchive.data() );
	boost::archive::text_iarchive in_archive(in_file, boost::archive::no_header );
	in_archive >> *this;
	return true;
}

bool PlayerData::saveText( const char *fileName )const{
	std::ofstream out_file( fileName );
	boost::archive::text_oarchive out_archive(out_file, boost::archive::no_header );
	out_archive << *this;
	return true;
}


bool PlayerData::loadXML( const char *fileName ){
	std::ifstream in_file( fileName );
	boost::archive::xml_iarchive in_archive(in_file, boost::archive::no_header );
	in_archive >>  boost::serialization::make_nvp("PlayerData", *this );
	return true;
}
bool PlayerData::loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
	while(!infileInArchive.isFinished()){}
	// .data() doesn't have a terminal \0. It's not a c-string(char*).
	//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
	std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
	boost::archive::xml_iarchive in_archive( in_file, boost::archive::no_header  );
	in_archive >>  boost::serialization::make_nvp("PlayerData", *this );
	return true;
}
bool PlayerData::saveXML( const char *fileName )const{
	std::ofstream out_file( fileName );
	boost::archive::xml_oarchive out_archive(out_file, boost::archive::no_header );
	out_archive << boost::serialization::make_nvp( "PlayerData", *this );
	return true;
}

template<class Archive>
void PlayerData::serialize(Archive& ar, const unsigned int version){
	using boost::serialization::make_nvp;
	ar & make_nvp("clearedStage", mClearedStage );
	ar & make_nvp("Miku", *mMiku );
}

/*
void PlayerData::addItem( Item::ItemSharedPtr item ){
	//2重に入らないようにチェックする
	for( std::vector<Item::ItemSharedPtr>::iterator it=mItems.begin(), end=mItems.end();
		it!=end; ++it ){
		assert( *it!=item && "item is doubled." );
	}
	mItems.push_back( item );
}
bool PlayerData::removeItem( const Item::ItemSharedPtr &item ){
	for( std::vector<Item::ItemSharedPtr>::iterator it=mItems.begin(), end=mItems.end();
		it!=end; ++it ){
		if( *it==item){
			mItems.erase( it );
			return true;
		}
	}
	return false;
}
void PlayerData::swapItem( unsigned int index0, unsigned int index1 ){
	assert( mItems.size() > index0 );
	assert( mItems.size() > index1 );
	
	std::swap(mItems[index0], mItems[index1]);
	//Item::ItemSharedPtr temp = mItems[index0];
	//mItems[index0] = mItems[index1]; 
	//mItems[index1] = temp; 
}



void PlayerData::setCurrentTime(){
	struct tm date;
	time_t now;

	time(&now);
	localtime_s( &date, &now);


	mYear	= date.tm_year + 1900;
	mMonth	= date.tm_mon + 1;
	mDay	= date.tm_mday;
	mHour	= date.tm_hour;
	mMinute	= date.tm_min;
	mSecond	= date.tm_sec;
}

//characterでcreateGameObjectPlayerDataやらないのはaccessoryのため
GameObject::PlayerDataSharedPtr PlayerData::createGameObjectPlayer(int index){
	assert( index < mCharacters.size() );
	Character& c = *mCharacters[index].get();
	
	//c.getModel()->isReady();

	MMD::HumanModelSharedPtr model = c.getModel()->createGameObjectModel();
	
	BtCollisionShapeSharedPtr shape = c.getShape()->createBtCollisionShape();
	c.getStatus();

	btCylinderShape *cylinder = dynamic_cast<btCylinderShape*>(shape.get());
	assert(cylinder);

	GameObject::Player::PlayerSharedPtr player = GameObject::Player::Player::create( model, shape, c.getStatus() );
	
	//hook and accessory
	c.getItem()->buildAccessories( player->getModel(), player->getBtCollisionObject(), player->getStatus() );

	return player;

}




*/


EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(PlayerData);

}//end namespace XmlLoader
BOOST_CLASS_IMPLEMENTATION(XmlLoader::PlayerData, boost::serialization::object_serializable );
