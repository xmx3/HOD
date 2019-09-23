#include"Accessory.h"
#include"XmlLoader/Shape.h"

#include<GameLib/GameLib.h>

#include"../../GameObject/Accessory.h"
#include<GameLib/PseudoXml/Element.h>
#include<GameLib/PseudoXml/Attribute.h>
#include<GameLib/FileIO/InFile.h>
#include<assert.h>
#include<GameLib/Base/RefString.h>

#include<string>
#include<sstream>

#include"helper/BoostSerializationMacros.h"



namespace XmlLoader{ namespace GameObject {
Accessory::Accessory()
	:mMass(0.f),
	mXmlFile(nullptr)
{}

/*
Accessory::Accessory( const GameLib::PseudoXml::ConstElement & e )
	:mScale(0.f),
	mModel(NULL)
{
	using GameLib::RefString;
	using namespace GameLib::PseudoXml;
	assert( RefString(e.name())=="Accessory" );
	int n = e.childNumber();

	for( int i=0; i<n;++i ){
		const ConstElement &c = e.child(i);
		if(RefString(c.name())=="Model"){
			int attrN = c.attributeNumber();
			assert( attrN==2 );
			for( int ai=0; ai<attrN; ++ai ){
				const ConstAttribute &a = c.attribute(ai);
				if( RefString(a.name())=="file" ){
					mModelFileName.assign( a.value() );
				} else if( RefString(a.name())=="scale" ){
					mScale=a.getFloatValue();
				} else {
					assert(false);
				}
			}
		}
		else if(RefString(c.name())=="Shape"){
			assert( !mModelFileName.empty() );
			mShape = Shape::create( c, mModelFileName );
		}
		else{
			assert(false);
		}
	}

	assert( !mModelFileName.empty() );
	assert( mScale!=0.f );
	assert( mShape );
	mModel = new boost::flyweights::flyweight<
		boost::flyweights::key_value<std::string, GameObject::AccessoryUtils::MME::TemplateModel >
	>( mModelFileName );

}
*/

Accessory::~Accessory(){
	SAFE_DELETE(mXmlFile);
}
bool Accessory::isReady(){
	if(mXmlFile){
		//xmlファイルロード完了
		//モデル、シェイプ等のロードを開始
		if(mXmlFile->isFinished()){
			std::istringstream in_file( 
				std::string(mXmlFile->data(), mXmlFile->size()),
				std::ios::binary || std::ios::in );

			boost::archive::xml_iarchive in_archive(in_file, boost::archive::no_header );
			in_archive >> boost::serialization::make_nvp("Accessory", *this );
			SAFE_DELETE(mXmlFile);
		}
		return false;
	}else{
		return mModel.isReady();
	}

}

BtCollisionShapeAndBtTriangleMesh Accessory::instanceBtCollisionShape(){
	return mShape.instanceBtCollisionShape();
}
::GameObject::AccessoryUtils::MME::ModelSharedPtr Accessory::instanceModel(){
	return mModel.instance();
}

::GameObject::AccessorySharedPtr Accessory::instance(
	btCollisionObject *owner,
	const btTransform &startTrans )
{
	typedef ::GameObject::AccessoryUtils::MME::ModelSharedPtr InstanceModelSharedPtr;

	InstanceModelSharedPtr model = instanceModel();
	BtCollisionShapeAndBtTriangleMesh shapeAndMesh = instanceBtCollisionShape();
	::GameObject::AccessorySharedPtr accessory = std::make_shared<::GameObject::Accessory>( 
		shapeAndMesh,
		model,
		mMass,
		owner,
		startTrans );
	return accessory;
}

void Accessory::loadXml( const std::string &fileName ){
	assert(mXmlFile==nullptr);
	mXmlFile = new GameLib::FileIO::InFile();
	*mXmlFile = GameLib::FileIO::InFile::create( fileName.c_str() );
}


SPLIT_SERIALIZE_IMPL(Accessory);

template<class Archive>
void Accessory::save(Archive& ar, const unsigned int version) const {
	ar & boost::serialization::make_nvp("name", mName );
	ar & boost::serialization::make_nvp("mass", mMass );
	ar & boost::serialization::make_nvp("Model", mModel );
	ar & boost::serialization::make_nvp("Shape", mShape );		
}
template<class Archive>
void Accessory::load(Archive& ar, const unsigned int version){
	ar & boost::serialization::make_nvp("name", mName );
	ar & boost::serialization::make_nvp("mass", mMass );
	ar & boost::serialization::make_nvp("Model", mModel );

	mShape.setModelFile( mModel.fileName() );
	ar & boost::serialization::make_nvp("Shape", mShape );		
}
EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(Accessory);

} }//end namespace XmlLoader::GameObject
BOOST_CLASS_IMPLEMENTATION(XmlLoader::GameObject::Accessory, boost::serialization::object_serializable);
