#include"Character.h"
#include"MME/Object/ModelKai.h"
#include"GameObjectData/Status.h"

#include"helper/BoostSerializationMacros.h"

#include<fstream>
#include<sstream>

#include<GameLib/FileIO/InFile.h>

#include<time.h>
#include<GameLib/FileIO/InFile.h>

namespace XmlLoader {
	namespace {
		static const std::string skInitModelXmlFileName = "Data/XmlLoader/Model/bou.xml";
		static const std::string skInitName = "ñ_êlä‘";
	}


Character::Character()
	:mName(),
	mModel(NULL)
{
	mModel = new MME::Object::ModelKai(); 
	mStatus = GameObjectData::Status::create();
}
Character::~Character()
{
	delete mModel;
	mModel=0;
}


template<class Archive>
void Character::serialize(Archive& ar, const unsigned int version){
	using boost::serialization::make_nvp;
	using namespace GameObjectData;
		        
	ar & make_nvp("Status",				*mStatus );
	ar & make_nvp("name",				mName );
	ar & make_nvp("weaponFile",			mWeaponFile );
}

EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(Character);

void Character::loadModel( const std::string &xmlFileName ){
	//assert(false);
	mModel->loadStart( xmlFileName );
}

}//end namespace XmlLoader