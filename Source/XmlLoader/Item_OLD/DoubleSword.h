#pragma once
#include"Item.h"
#include"GameObjectData/fwd.h"
#include<string>
#include<vector>
#include<sstream>
#include<boost/serialization/base_object.hpp>

#include"Serialization/GameObject/AccessoryUtils/Hook.h"
#include"Serialization/GameObject/Accessory.h"


namespace Serialization {
	class Shape;
	typedef std::shared_ptr<Shape> ShapeSharedPtr;

	class Accessory;
	typedef std::shared_ptr<Accessory> AccessorySharedPtr;
	namespace AccessoryUtils{
		class Hook;
	}
namespace Item{
	
class DoubleSword;
typedef std::shared_ptr<DoubleSword> DoubleSwordSharedPtr;


class DoubleSword : public Item {
public:
	DoubleSword();
	virtual ~DoubleSword();

	bool loadBinary( const char *fileName );
	bool loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveBinary( const char *fileName )const;
	
	bool loadText( const char *fileName );
	bool loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveText( const char *fileName )const;
	
	bool loadXML( const char *fileName );
	bool loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveXML( const char *fileName )const;
	
	void print( std::ostringstream &ss )const;

	//別名実装案
	//model->equip( accessory );
	virtual void buildAccessories( MMD::HumanModel*, btCollisionObject* owner,  const GameObjectData::StatusSharedPtr &ownerSt  );	

	Accessory mAccessoryR;
	Accessory mAccessoryL;
	
	Serialization::AccessoryUtils::Hook mHooksR[3];
	Serialization::AccessoryUtils::Hook mHooksL[3];
private:
	//disallow assign
	DoubleSword( const DoubleSword & );
	//disallow copy
	void operator=( const DoubleSword & );

	friend boost::serialization::access;	
	//基底クラスのserialize関数を直接呼び出さないこと！！
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) 
	{
		using namespace boost::serialization;
		// save/load base class information
        ar & make_nvp( "Item", base_object<Item>(*this) );
		
		ar & make_nvp("AccessoryR", mAccessoryR );
		ar & make_nvp("AccessoryL", mAccessoryL );
	
		ar & make_nvp( "AccessoryHooksR[0]", mHooksR[0] );
		ar & make_nvp( "AccessoryHooksR[1]", mHooksR[1] );
		ar & make_nvp( "AccessoryHooksR[2]", mHooksR[2] );

		ar & make_nvp( "AccessoryHooksL[0]", mHooksL[0] );
		ar & make_nvp( "AccessoryHooksL[1]", mHooksL[1] );
		ar & make_nvp( "AccessoryHooksL[2]", mHooksL[2] );
	}
};
}//end namespace Item
}//end namespace Serialization