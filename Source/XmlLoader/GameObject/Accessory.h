#pragma once
#include<string>
#include<memory>
#include<boost/serialization/serialization.hpp>
#include<boost/serialization/split_member.hpp>
#include"AccessoryUtils/Model.h"
#include"XmlLoader/Shape.h"


class btCollisionObject;
class btTransform;


namespace GameLib{
	namespace PseudoXml{
		class ConstElement;
	}
	namespace FileIO{
		class InFile;
	}
}

namespace GameObject{
	class Accessory;
	typedef std::shared_ptr<Accessory> AccessorySharedPtr;
	namespace AccessoryUtils{
		namespace MME{
			class TemplateModel;
			class Model;
			typedef std::shared_ptr<Model> ModelSharedPtr;
		}
	}
}

namespace GameObjectData{
	class Status;
	typedef std::shared_ptr<Status> StatusSharedPtr;
}

namespace XmlLoader{
	class Shape;
	typedef std::shared_ptr<Shape> ShapeSharedPtr;
namespace GameObject{
class Accessory{
public:
	Accessory();
	//Accessory( const GameLib::PseudoXml::ConstElement & modelElement );
	~Accessory();

	void loadXml( const std::string &filename );

	bool isReady();
	::GameObject::AccessorySharedPtr instance(
		btCollisionObject *owner,
		const btTransform &startTrans
	);
	const std::string & getName()const{
		return mName;
	}

private:
	//disallow
	Accessory( const Accessory& );
	//disalow
	void operator=( const Accessory& ); 

	BtCollisionShapeAndBtTriangleMesh instanceBtCollisionShape();
	::GameObject::AccessoryUtils::MME::ModelSharedPtr instanceModel();

	friend boost::serialization::access;	
	//基底クラスのselialize, save, load関数を直接呼び出さないこと！！
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);
	template<class Archive>
	void save(Archive& ar, const unsigned int version) const;
	template<class Archive>
	void load(Archive& ar, const unsigned int version);
	
	GameLib::FileIO::InFile *mXmlFile;
	std::string mName;
	AccessoryUtils::Model mModel;
	float mMass;
	Shape mShape;
};
} }//end namespace XmlLoader::GameObject