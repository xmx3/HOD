#include"Item.h"
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


namespace{
/*
//スマートポインタで保存できないのでいったん別の入れ物に入れてから、シリアライズ
class ItemAdapter{
public:
	ItemAdapter(){}
	ItemAdapter( const Item& it )
		:name_(it.name_),
		explanation_(it.explanation_),
		action_(it.action_)
	{
		for( unsigned int i=0, size=it.statuses_.size(); i<size; ++i ){
			if( IWeaponStatus *ws = it.statuses_[i].get() ){
				statuses_.push_back( ws );
			}
		}
	};

	~ItemAdapter(){}

	void copyTo( Item* dst ){
		dst->name_			= name_;
		dst->explanation_	= explanation_;
		dst->action_		= action_;
		dst->statuses_.clear();
		dst->statuses_.reserve( statuses_.size() );
		for( unsigned int i=0, size=statuses_.size(); i<size;++i ){
			dst->statuses_.push_back( IWeaponStatusSharedPtr( statuses_[i] ) );
		}
		dst->statuses_.shrink_to_fit();
	}

	bool loadBinary( const char *fileName ){
		statuses_.clear();
		std::ifstream in_file( fileName, std::ios::binary );
		boost::archive::binary_iarchive in_archive(in_file);
		in_archive >> *this;
		return true;
	}
	bool loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
		statuses_.clear();
		while(!infileInArchive.isFinished()){}
		// .data() doesn't have a terminal \0. It's not a c-string(char*).
		//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
		std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
		boost::archive::binary_iarchive in_archive( in_file );
		in_archive >> *this;
		return true;
	}

	bool saveBinary( const char *fileName ){
		std::ofstream out_file( fileName, std::ios::binary );
		boost::archive::binary_oarchive out_archive(out_file);
		out_archive << *this;
		return true;
	}

	bool loadText( const char *fileName ){
		statuses_.clear();
		std::ifstream in_file( fileName );
		boost::archive::text_iarchive in_archive(in_file);
		in_archive >> *this;
		return true;
	}

	bool loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
		statuses_.clear();
		while(!infileInArchive.isFinished()){}
		std::istringstream in_file( infileInArchive.data() );
		boost::archive::text_iarchive in_archive(in_file);
		in_archive >> *this;
		return true;
	}

	bool saveText( const char *fileName ){
		std::ofstream out_file( fileName );
		boost::archive::text_oarchive out_archive(out_file);
		out_archive << *this;
		return true;
	}


	bool loadXML( const char *fileName ){
		statuses_.clear();
		std::ifstream in_file( fileName );
		boost::archive::xml_iarchive in_archive(in_file);
		in_archive >>  boost::serialization::make_nvp("Item", *this );
		return true;
	}
	bool loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive ){
		statuses_.clear();
		while(!infileInArchive.isFinished()){}
		// .data() doesn't have a terminal \0. It's not a c-string(char*).
		//I didn't even realize stringstream had a char* constructor (who in their right mind uses them anymore?) but apparently it does and I'd bet it expects \0.
		std::istringstream in_file( std::string( infileInArchive.data(), infileInArchive.size() ) , std::ios::binary | std::ios::in );
		boost::archive::xml_iarchive in_archive( in_file );
		in_archive >>  boost::serialization::make_nvp("Item", *this );
		return true;
	}
	bool saveXML( const char *fileName ){
		std::ofstream out_file( fileName );
		boost::archive::xml_oarchive out_archive(out_file);
		out_archive << boost::serialization::make_nvp( "Item", *this );
		return true;
	}

	std::string name_;
	std::string explanation_;

	ActionType action_;
	
	std::vector<IWeaponStatus*> statuses_;
private:
	//disallow assign
	ItemAdapter( const ItemAdapter & );
	//disallow copy
	void operator=( const ItemAdapter & );
	
	friend boost::serialization::access;	
	//基底クラスのserialize関数を直接呼び出さないこと！！
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		using boost::serialization::make_nvp;

		// in this program, these classes are never serialized directly but rather
        // through a pointer to the base class bus_stop. So we need a way to be
        // sure that the archive contains information about these derived classes.
        ar.register_type(static_cast<SwordWeaponStatus *>(NULL));
        //ar.register_type(static_cast< *>(NULL));
        // serialization of stl collections is already defined
        // in the header

		ar & make_nvp("name",					name_ );
		//ar & make_nvp("explanation",	explanation_ );
		ar & make_nvp("action",					action_ );
		ar & make_nvp("statuses",				statuses_ );
	}
};
*/
}//end unnamespace


