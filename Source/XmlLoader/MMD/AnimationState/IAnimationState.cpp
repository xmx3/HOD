#include"IAnimationState.h"
#include"MMD/AnimationState/Default.h"
#include"MMD/AnimationState/StartEnd.h"

//#include<GameLib/GameLib.h>
//#include<GameLib/PseudoXml/Element.h>
//#include<GameLib/PseudoXml/Attribute.h>
//#include<GameLib/Base/RefString.h>
//#include"helper/XmlHelperFuncs.h"

#include<boost/optional.hpp>
#include<boost/lexical_cast.hpp>
#include"helper/parseEquals.h"

#include"MMD/MMDDataBase.h"
#include"MMD/TemplateVMD.h"

#include"helper/BoostSerializationMacros.h"


namespace {
	static const bool skIsRepeatDefalut=false;
	static const bool skIsBlendDefalut=false;
	static const bool skIsStandtDefalut=true;
	void setBool( bool *b, const std::string &str ){
		if( str=="true" ){
			*b=true;
		}else if( str=="false"){
			*b=false;
		} else {
			assert(false);
		}
	}
}

namespace XmlLoader { namespace MMD { namespace AnimationState {

typedef ::MMD::AnimationModel InstanceAnimationModel;
typedef ::MMD::AnimationState::IAnimationStateSharedPtr InstanceAnimationStateSharedPtr;

class IAnimationState::Impl{
public:
	Impl( const std::string &vmdFileName )
		:mVmdFileName(vmdFileName)
	{
		mVmd = ::MMD::MMDDataBase::loadVMD( mVmdFileName.c_str() );
	}
	virtual ~Impl(){}

	bool isReady(){
		return mVmd->isReady();
	}
	virtual InstanceAnimationStateSharedPtr createAnimationState( InstanceAnimationModel*  model )=0;
protected:
	std::string mVmdFileName;
	::MMD::TemplateVMDSharedPtr mVmd;
};

class DefalutAnimation : public IAnimationState::Impl {
public:
	DefalutAnimation( const std::string &vmdFileName, const std::string &arguments )
		:Impl(vmdFileName),
		mIsRepeat(skIsRepeatDefalut),
		mIsBlend(skIsBlendDefalut),
		mIsStand(skIsStandtDefalut),
		mPlaySpeed(1.f)
	{

		const char* pNext=arguments.c_str();
		while( pNext ){
			using boost::lexical_cast;
			std::string left,right;
			const char *pOld=pNext;
			pNext = parseEquals( pNext, &left, &right );
			if( left=="isRepeat"){
				setBool( &mIsRepeat, right );
			} else if( left=="isBlend"){
				setBool( &mIsBlend, right );
			} else if( left=="isStand"){
				setBool( &mIsStand, right );
			} else if( left=="playSpeed" ){
				mPlaySpeed = boost::lexical_cast<float>(right);
			} else {
				assert(left.empty());
			}
		}
	}
		
	~DefalutAnimation(){}

	
	InstanceAnimationStateSharedPtr createAnimationState( InstanceAnimationModel*  model ){
		std::shared_ptr<::MMD::AnimationState::Default> r =
			std::make_shared<::MMD::AnimationState::Default>(
				model,
				mVmdFileName.c_str(),
				mIsBlend, mIsRepeat, mIsStand );
		r->setPlaySpeed( mPlaySpeed );
		return r;
	}

private:
	bool mIsBlend, mIsRepeat, mIsStand;
	float mPlaySpeed;
};
class StartEndAnimation : public IAnimationState::Impl {
public:
	StartEndAnimation( const std::string &vmdFileName, const std::string &arguments )
		:Impl(vmdFileName),
		mIsRepeat(skIsRepeatDefalut),
		mIsBlend(skIsBlendDefalut),
		mIsStand(skIsStandtDefalut),
		mPlaySpeed(1.f),
		mRestartFrame(0.f),
		mEndFrame(0.f)
	{
		const char* pNext=arguments.c_str();
		while( pNext ){
			using boost::lexical_cast;
			std::string left,right;
			pNext = parseEquals( pNext, &left, &right );
			if( left=="isRepeat"){
				setBool( &mIsRepeat, right );
			} else if( left=="isBlend"){
				setBool( &mIsBlend, right );
			} else if( left=="isStand"){
				setBool( &mIsStand, right );
			} else if( left=="playSpeed" ){
				mPlaySpeed = boost::lexical_cast<float>(right);
			} else if( left=="restartFrame" ){
				mRestartFrame = boost::lexical_cast<float>(right);
			} else if( left=="endFrame" ){
				mEndFrame = boost::lexical_cast<float>(right);
			} else {
				assert(left.empty());
			}
		}
	}
	~StartEndAnimation(){}


	InstanceAnimationStateSharedPtr createAnimationState( InstanceAnimationModel*  model ){
		std::shared_ptr<::MMD::AnimationState::StartEnd> r =
			std::make_shared<::MMD::AnimationState::StartEnd>( 
			model,
			mVmdFileName.c_str(),
			mRestartFrame, mEndFrame,
			mIsBlend, mIsRepeat, mIsStand );

		r->setPlaySpeed( mPlaySpeed );
		return r;
	}
private:
	bool mIsBlend, mIsRepeat, mIsStand;
	float mPlaySpeed;
	float mRestartFrame, mEndFrame;
};

void IAnimationState::loadImpl(){
	if( mType == "default" ){
		mImpl=std::make_shared<DefalutAnimation>( mVmdFileName, mArguments );
	} else if( mType == "startEnd" ){
		mImpl=std::make_shared<StartEndAnimation>( mVmdFileName, mArguments );
	} else {
		assert( false && " type element of Animation is wrong!" );
	}	
}

InstanceAnimationStateSharedPtr 
IAnimationState::instance( InstanceAnimationModel* model )
{
	return mImpl->createAnimationState( model );
}

bool IAnimationState::isReady()
{
	return mImpl->isReady();
}


//IAnimationSharedPtr IAnimationState::create( const GameLib::PseudoXml::ConstElement &animationElement ){
//	using namespace GameLib::PseudoXml;
//	using namespace XmlHelperFuncs;

//	using GameLib::RefString;
//	
//	int num = animationElement.attributeNumber();
//	bool isBlend = false;
//	bool isRepeat = false;
//	bool isStand = true;
//	float restartFrame=0;
//	float endFrame=0;
//	float playSpeed=1.f;

//	std::string animationType, vmdFileName;

//	for( int i=0; i<num; ++i ){
//		ConstAttribute a = animationElement.attribute(i);

//		const char* attributeName = a.name();
//		if( RefString("type") == attributeName ){
//			animationType.assign( a.value() );
//		}
//		else if( RefString("isBlend") == attributeName ){
//			bool isOk = setBool( &isBlend, a );
//			STRONG_ASSERT( isOk && "isBlend is wrong!" );
//		}
//		else if( RefString("isRepeat") == attributeName ){
//			bool isOk = setBool( &isRepeat, a );
//			STRONG_ASSERT( isOk && "isRepeat is wrong!" );
//		}
//		else if( RefString("isStand") == attributeName ){
//			bool isOk = setBool( &isStand, a );
//			STRONG_ASSERT( isOk && "isStand is wrong!" );
//		}else if( RefString("restartFrame") == attributeName ){
//			restartFrame = a.getFloatValue();
//		}else if( RefString("endFrame") == attributeName ){
//			endFrame = a.getFloatValue();
//		}else if( RefString("vmdFile") == attributeName ){
//			vmdFileName.assign( a.value() );
//		}else if( RefString("playSpeed") == attributeName ){
//			playSpeed = a.getFloatValue();
//			assert( playSpeed != 0.f );
//		}else {
//			TRACE1("attribute name=%s\n", attributeName );
//			STRONG_ASSERT( false && "attribute name is wrong!" );
//		}
//	}

//	if( animationType == "default" ){
//		return std::make_shared<DefalutAnimation>( vmdFileName, isBlend, isRepeat, isStand, playSpeed );
//	} else if( animationType == "startEnd" ){
//		return std::make_shared<StartEndAnimation>( vmdFileName, restartFrame, endFrame, isBlend, isRepeat, isStand, playSpeed );
//	} else {
//		STRONG_ASSERT( false && " type attribute of Animation is wrong!" );
//		return 0;
//	}
//}
EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(IAnimationState);

} } }//end namespace XmlLoader::MMD::AnimationState




BOOST_CLASS_IMPLEMENTATION(XmlLoader::MMD::AnimationState::IAnimationState, boost::serialization::object_serializable);
