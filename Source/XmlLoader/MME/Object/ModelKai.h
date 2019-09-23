#pragma once
#include<string>
#include<memory>
#include<vector>
namespace boost{ namespace serialization{
	class access;
} } //boost::serialization

namespace MME{ namespace Object {
	class ModelKai;
	typedef std::shared_ptr<ModelKai> ModelKaiSharedPtr;
}}

namespace GameLib{ namespace FileIO {
		class InFile;
} }


namespace XmlLoader{ 
	namespace MMD{ 
		class TemplatePMD;
		typedef std::shared_ptr<TemplatePMD> TemplatePMDSharedPtr;

		namespace AnimationState {
			class IAnimationState;
			typedef std::shared_ptr<IAnimationState> IAnimationStateSharedPtr;
		}
	}
	class Shape;
	typedef std::shared_ptr<Shape> ShapeSharedPtr;

	
namespace MME { namespace Object {

class ModelKai{
private:
	typedef ::MME::Object::ModelKaiSharedPtr InstanceModelKaiSharedPtr;
public:
	ModelKai();
	~ModelKai();

	bool loadStart( const std::string &fileName );

	bool isReady();
	
	//const std::string & getFileName()const;

	InstanceModelKaiSharedPtr instance();

private:
	friend class boost::serialization::access;	
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);
	template<class Archive>
	void save(Archive& ar, const unsigned int version) const;
	template<class Archive>
	void load(Archive& ar, const unsigned int version);

	bool isModelReady();
	bool isAnimationsReady();

	GameLib::FileIO::InFile *mFile;

	MMD::TemplatePMDSharedPtr mModel;

	float mHeightOffset;

	unsigned int mNumAnimations;
	MMD::AnimationState::IAnimationState *mAnimations;

};
} } }// namespace XmlLoader::MME::Object