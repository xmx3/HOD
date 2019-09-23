#pragma once
#include<string>
#include<memory>
#include<vector>

namespace boost{ namespace serialization{
	class access;
} } //boost::serialization

namespace GameLib{ namespace FileIO {
		class InFile;
} }

namespace MMD{
	class AnimationModel;
	typedef std::shared_ptr<AnimationModel> AnimationModelSharedPtr;
}

namespace XmlLoader {
	class Shape;
	typedef std::shared_ptr<Shape> ShapeSharedPtr;

	namespace MMD{
	class AnimationModel;

		class TemplatePMD;
		typedef std::shared_ptr<TemplatePMD> TemplatePMDSharedPtr;
		namespace AnimationState {
			class IAnimationState;
			typedef std::shared_ptr<IAnimationState> IAnimationStateSharedPtr;
		}
	

class AnimationModel {
public:
	AnimationModel();
	~AnimationModel();

	bool loadStart( const std::string &fileName );
	//bool loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	//bool saveXML( const std::string &fileName )const;

	bool isReady();

	//ShapeSharedPtr getShape()const{
	//	return mShape;
	//}

	::MMD::AnimationModelSharedPtr instance();
	
private:
	friend class boost::serialization::access;	
	//serialze関数を直接呼び出さないこと！！
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);
	template<class Archive>
	void save(Archive& ar, const unsigned int version)const;
	template<class Archive>
	void load(Archive& ar, const unsigned int version);

	//disallow
	AnimationModel(const AnimationModel& );
	//disallow
	void operator=(const AnimationModel& );

	bool isModelReady();
	bool isAnimationsReady();

	GameLib::FileIO::InFile *mFile;
	bool mIsFileFinished;

	MMD::TemplatePMDSharedPtr mModel;

	float mHeightOffset;
	//Characterのメンバーにするべきか？
	//タイプがmeshのときのことを考慮してここにおいてある
	ShapeSharedPtr mShape;


	unsigned int mNumAnimations;
	std::vector<MMD::AnimationState::IAnimationStateSharedPtr> mAnimations;
};

} }//end namespace XmlLoader::MMD