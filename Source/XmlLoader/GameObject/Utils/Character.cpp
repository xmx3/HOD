#include"Character.h"
#include"helper/BoostSerializationMacros.h"

#include"GameObject/Utils/Character.h"

#include"../../Shape.h"
#include"../../MME/Object/ModelKai.h"

#include<GameLib/GameLib.h>//SAFE_DELETE
#include<GameLib/FileIO/InFile.h>
#include<sstream>

namespace XmlLoader {
	namespace GameObject {
		namespace Utils {

Character::Character()
	:mFile(nullptr),
	mName(),
	mHeight(0.f),
	mMass(0.f),
	mShape( new Shape() ),
	mModel( new MME::Object::ModelKai() )
{}

Character::~Character() {
	SAFE_DELETE(mFile);
	SAFE_DELETE(mShape);
	SAFE_DELETE(mModel);
}

Character::InstancedCharacterSharedPtr Character::instance() {
	assert(isReady());
	while (!isReady()) {}


	return std::make_shared<::GameObject::Utils::Character>(
		mName,
		mHeight,
		mMass,
		mShape->instanceBtCollisionShape().first,
		mModel->instance() );
	
	
}

bool Character::isReady() {
	
	if ( mFile ) {//loadStart‚µ‚½‚Ì‚È‚ç

		if (mFile->isFinished()) {
			std::istringstream in_file(
				std::string(mFile->data(), mFile->size()),
				std::ios::binary || std::ios::in);
			boost::archive::xml_iarchive in_archive(in_file, boost::archive::no_header);
			in_archive >> boost::serialization::make_nvp("Character", *this);
			SAFE_DELETE(mFile);
		}
		return false;
	}
	else {
		return
			mModel->isReady() &&
			mShape->isReady();
	}
}

void Character::loadStart(const std::string &filename) {
	SAFE_DELETE(mFile);
	mFile = new GameLib::FileIO::InFile();
	*mFile = GameLib::FileIO::InFile::create(filename.c_str());
	if (mFile->isError()) {
		assert(false && "file not found");
	}

}

			
template<class Archive>
void Character::serialize(Archive& ar, const unsigned int version) {
	using boost::serialization::make_nvp;
	ar & make_nvp("Name", mName);
	ar & make_nvp("Height", mHeight);
	ar & make_nvp("Mass", mMass);
	ar & make_nvp("Shape", *mShape);
	ar & make_nvp("ModelKai", *mModel);
}

EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(Character);
}}}// end XmlLoader::GameObject::Utils

BOOST_CLASS_IMPLEMENTATION(XmlLoader::GameObject::Utils::Character, boost::serialization::object_serializable);
