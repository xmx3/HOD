#pragma once
#include<boost/serialization/serialization.hpp>
#include<boost/serialization/string.hpp>
#include<string>
#include<boost/flyweight/flyweight_fwd.hpp>
#include<boost/flyweight/key_value.hpp>
#include"GameObject/AccessoryUtils/MME/TemplateModel.h"
#include"GameObject/AccessoryUtils/MME/Model.h"


namespace GameObject{
	namespace AccessoryUtils{
		namespace MME{
			class TemplateModel;
			class Model;
			typedef std::shared_ptr<Model> ModelSharedPtr;
		}
	}
}


namespace Serialization {  namespace GameObject { namespace AccessoryUtils{
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
	void serialize(Archive& ar, const unsigned int version){
		ar & boost::serialization::make_nvp("xFileName", mFileName );
		ar & boost::serialization::make_nvp("scale", mScale );
	}
	std::string mFileName; 
	float mScale;

	//isReady();
	//mesh shapeÇçÏÇÈÇ∆Ç´Ç‡égÇ§
	boost::flyweights::flyweight<
		boost::flyweights::key_value<std::string, ::GameObject::AccessoryUtils::MME::TemplateModel >
	> *mModel;
};

} } }// end Serialization::GameObject::AccessoryUtils