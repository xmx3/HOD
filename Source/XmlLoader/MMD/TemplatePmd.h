#pragma once
#include<string>
#include<memory>
namespace boost{ namespace serialization{
	class access;
} } //boost::serialization

namespace MMD{
class TemplatePMD;
typedef std::shared_ptr<TemplatePMD> TemplatePMDSharedPtr;
}

namespace XmlLoader{ namespace MMD{

class TemplatePMD{
public:
	TemplatePMD();
	~TemplatePMD();
	bool isReady();
	const std::string & getFileName()const;
	::MMD::TemplatePMDSharedPtr instance();

private:
	friend class boost::serialization::access;	
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);
	template<class Archive>
	void save(Archive& ar, const unsigned int version) const;
	template<class Archive>
	void load(Archive& ar, const unsigned int version);

	std::string mPmdFileName;
	::MMD::TemplatePMDSharedPtr mModel;
};
}}// namespace XmlLoader::MMD