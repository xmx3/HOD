#pragma once

#include<string>
#include<memory>
#include<boost/serialization/serialization.hpp>
#include<boost/serialization/split_member.hpp>

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
	class Enemy;
	typedef std::shared_ptr<Enemy> EnemySharedPtr;
	class ICollider;
	typedef std::shared_ptr<ICollider> IColliderSharedPtr;
}


namespace GameObjectData{
	class Status;
	typedef std::shared_ptr<Status> StatusSharedPtr;
	class WeaponStatus;
}

namespace XmlLoader{
	class Shape;
	namespace MME{ namespace Object{
		class ModelKai;
	}}

namespace GameObject{

class Enemy;
typedef std::shared_ptr<Enemy> EnemySharedPtr;

class Enemy{
public:
	Enemy();
	~Enemy();

	static EnemySharedPtr createSP();

	void loadXml( const std::string &file );

	bool isReady();
	
	::GameObject::EnemySharedPtr instance();

	const std::string & getName()const{
		return mName;
	}

private:
	//disallow
	Enemy(const Enemy&) = delete;
	//disalow
	void operator=(const Enemy&) = delete;

	friend boost::serialization::access;	
	//基底クラスのselialize, save, load関数を直接呼び出さないこと！！
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);

	GameLib::FileIO::InFile *mXmlFile;
	std::string mName;
	float mMass;
	Shape *mShape;
	MME::Object::ModelKai *mModel;
	GameObjectData::Status *mStatus;

};
} }//end namespace XmlLoader::GameObject