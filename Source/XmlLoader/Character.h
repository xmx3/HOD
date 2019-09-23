#pragma once
#include<string>
#include"GameObjectData/fwd.h"

namespace boost{
	namespace serialization{
		class access;
	}
}

namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}
namespace XmlLoader {
	class Character;
	typedef std::shared_ptr<Character> CharacterSharedPtr;
	namespace MME{ namespace Object{
		class ModelKai;
	} }

class Character {
public:
	Character();
	~Character();
	
	void loadModel( const std::string &xmlFileName );

	const std::string& getName()const{
		return mName;
	}

	void setName( const std::string name ){
		mName = name;
	}
	
private:
	//disallow
	Character(const Character& );
	//disallow
	void operator=(const Character& );

	std::string						mName;// ex miku
	std::string						mModelFile;
	std::string						mWeaponFile;
	//Item::ItemSharedPtr				mItem;
	MME::Object::ModelKai					*mModel;
	GameObjectData::StatusSharedPtr	mStatus;

	friend boost::serialization::access;	
	
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);
};

}//end namespace XmlLoader