#pragma once
#include<string>
#include<memory>
#include<boost/serialization/serialization.hpp>
#include<boost/serialization/split_member.hpp>

namespace GameLib{
	namespace FileIO {
		class InFile;
	}
	namespace PseudoXml{
		class ConstElement;
	}
}
namespace MMD{
	namespace AnimationState{
		class IAnimationState;
		typedef std::shared_ptr<IAnimationState> IAnimationStateSharedPtr;
	}
	class AnimationModel;
}

namespace XmlLoader { namespace MMD { namespace AnimationState {
	//namespace Instance = ::MMD;

	class IAnimationState;
	typedef std::shared_ptr<IAnimationState> IAnimationStateSharedPtr;
class IAnimationState {
private:
	typedef ::MMD::AnimationModel InstanceAnimationModel;
	typedef ::MMD::AnimationState::IAnimationStateSharedPtr InstanceAnimationStateSharedPtr;
public:
	class Impl;
	IAnimationState(){}
	//static AnimationSharedPtr create( const GameLib::PseudoXml::ConstElement &animatinElement );
	~IAnimationState(){}

	bool isReady();

	InstanceAnimationStateSharedPtr instance( InstanceAnimationModel* );
	const std::string& getName()const{
		return mName;
	}
private:	
	//disallow
	IAnimationState(const IAnimationState& )=delete;
	//disallow
	void operator=(const IAnimationState& )=delete;

	void loadImpl();

	friend boost::serialization::access;
	//基底クラスのselialize, save, load関数を直接呼び出さないこと！！
	BOOST_SERIALIZATION_SPLIT_MEMBER();
	template<class Archive>
	void save(Archive& ar, const unsigned int version) const {
		using boost::serialization::make_nvp;
		ar & make_nvp("name",			mName );			
		ar & make_nvp("vmdFile",		mVmdFileName );			
		ar & make_nvp("type",			mType );			
		ar & make_nvp("arguments",		mArguments );
	}
	template<class Archive>
	void load(Archive& ar, const unsigned int version){
		using boost::serialization::make_nvp;
		ar & make_nvp("name",			mName );			
		ar & make_nvp("vmdFile",		mVmdFileName );			
		ar & make_nvp("type",			mType );			
		ar & make_nvp("arguments",		mArguments );
		loadImpl();

	}

	std::string mName;
	std::string mType;
	std::string mVmdFileName;
	std::string mArguments;
	std::shared_ptr<Impl> mImpl;

};

} } }//end namespace XmlLoader::MMD::AnimationState
