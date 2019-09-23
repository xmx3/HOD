#pragma once
#include<boost/serialization/serialization.hpp>
#include<boost/serialization/string.hpp>
#include<string>
#include<boost/flyweight/flyweight_fwd.hpp>
#include<boost/flyweight/key_value_fwd.hpp>
#include<memory>

namespace XFile{
	class Model;
}
namespace GameObject { namespace AccessoryUtils { namespace MME {
	class Model;
	typedef std::shared_ptr<Model> ModelSharedPtr;
} } }


namespace XmlLoader {  namespace GameObject { namespace AccessoryUtils{
class Model{
public:
	Model();
	~Model();
	bool isReady();

	::GameObject::AccessoryUtils::MME::ModelSharedPtr instance();

	const std::string& fileName()const{
		return mFileName;
	}
private:
	void loadModel();
	friend boost::serialization::access;	
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);
	std::string mFileName; 
	float mScale;

	//isReady();
	//mesh shapeÇçÏÇÈÇ∆Ç´Ç‡égÇ§
	boost::flyweights::flyweight<
		boost::flyweights::key_value<std::string, XFile::Model >
	> *mModel;
};

} } }// end XmlLoader::GameObject::AccessoryUtils