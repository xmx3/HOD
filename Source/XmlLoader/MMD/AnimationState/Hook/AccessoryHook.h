#pragma once
#include<string>
#include<memory>
#include<boost/serialization/split_member.hpp>

#include<boost/serialization/serialization.hpp>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/string.hpp>

#include"GameObjectData/WeaponStatus.h"

namespace GameLib{
	namespace PseudoXml{
		class ConstElement;
	}
}

namespace GameObject {
	class Accessory;
	typedef std::shared_ptr<Accessory> AccessorySharedPtr;
}

namespace MMD{
	class Bone;
	namespace AnimationState{
		class BaseAnimationState;
		namespace Hook {
			class IHook;
			typedef std::shared_ptr<IHook> IHookSharedPtr;
		}
	}
}

namespace GameObject{
	namespace AccessoryUtils{
		namespace MME{
			class TemplateModel;
			class Model;
			typedef std::shared_ptr<Model> ModelSharedPtr;
		}
	}
}


namespace XmlLoader{ namespace MMD { namespace AnimationState { namespace Hook {

class AccessoryHook{
public:
	AccessoryHook();
	~AccessoryHook();
	const std::string & getBoneName()const{
		return mBoneName;
	}

	const std::string & getAccessoryName()const{
		return mAccessory;
	}
	
	const std::string & getTargetAnimation()const{
		return mToAnimation;
	}



	::MMD::AnimationState::Hook::IHookSharedPtr instance(
		::GameObject::AccessorySharedPtr mAccessory,
		::MMD::Bone* bone,
		::GameObjectData::StatusSharedPtr status/*武器が攻撃力を求めるために必要*/ );

private:
	friend boost::serialization::access;	
	//基底クラスのselialize, save, load関数を直接呼び出さないこと！！
	BOOST_SERIALIZATION_SPLIT_MEMBER();
	template<class Archive>
	void save(Archive& ar, const unsigned int version) const 
	{
		using namespace boost::serialization;
		ar & make_nvp("toAnimation",	mToAnimation );
		ar & make_nvp("accessory",		mAccessory );
		ar & make_nvp("hitStartFrame",	mHitStartFrame );
		ar & make_nvp("hitEndFrame",	mHitEndFrame );
		ar & make_nvp("drawStartFrame",	mDrawStartFrame );
		ar & make_nvp("drawEndFrame",	mDrawEndFrame );
		ar & make_nvp("boneName",		mBoneName );
		ar & make_nvp("enableContactResponse",	mEnableContactResponse );


		GameObjectData::WeaponStatus* temp = mWeaponStatus.get();
		ar & make_nvp("WeaponStatus",			*temp );
	}
	template<class Archive>
	void load(Archive& ar, const unsigned int version) 
	{
		using namespace boost::serialization;

		ar & make_nvp("toAnimation",	mToAnimation );
		ar & make_nvp("accessory",		mAccessory );
		ar & make_nvp("hitStartFrame",	mHitStartFrame );
		ar & make_nvp("hitEndFrame",	mHitEndFrame );
		ar & make_nvp("drawStartFrame",	mDrawStartFrame );
		ar & make_nvp("drawEndFrame",	mDrawEndFrame );
		ar & make_nvp("boneName",		mBoneName );

		ar & make_nvp("enableContactResponse",	mEnableContactResponse );

		mWeaponStatus = std::make_shared<GameObjectData::WeaponStatus>();
		GameObjectData::WeaponStatus* temp = mWeaponStatus.get();
		ar & make_nvp("WeaponStatus",			*temp );
	}

	std::string mToAnimation;//mWhichAnimation
	std::string mAccessory;
	float mHitStartFrame;
	float mHitEndFrame;
	float mDrawStartFrame;
	float mDrawEndFrame;
	bool mEnableContactResponse;
	std::string mBoneName;
	GameObjectData::WeaponStatusSharedPtr mWeaponStatus; 
};
} } } }//end namespace XmlLoader::MMD::AnimationState::Hook