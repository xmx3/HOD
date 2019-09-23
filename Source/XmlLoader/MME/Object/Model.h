#pragma once
#include<string>
#include<memory>
namespace boost{ namespace serialization{
	class access;
} } //boost::serialization

namespace MME{ namespace Object {
	class Model;
	typedef std::shared_ptr<Model> ModelSharedPtr;
}}

namespace XmlLoader{ namespace MME { namespace Object {

class Model{
private:
	typedef ::MME::Object::ModelSharedPtr InstanceModelSharedPtr;
public:
	Model();
	~Model();
	bool isReady();
	const std::string & getFileName()const;
	InstanceModelSharedPtr instance();

private:
	friend class boost::serialization::access;	
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);
	template<class Archive>
	void save(Archive& ar, const unsigned int version) const;
	template<class Archive>
	void load(Archive& ar, const unsigned int version);

	std::string mPmdFileName;
	InstanceModelSharedPtr mModel;
};
} } }// namespace XmlLoader::MME::Object