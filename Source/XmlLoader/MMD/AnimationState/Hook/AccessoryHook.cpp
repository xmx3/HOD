#include"AccessoryHook.h"
#include"../../../../MMD/AnimationState/Hook/AccessoryHook.h"
#include"../../../../GameObject/Accessory.h"
#include"helper/BoostSerializationMacros.h"


namespace XmlLoader{ namespace MMD { namespace AnimationState { namespace Hook {

	AccessoryHook::AccessoryHook()
		:mHitStartFrame(0.f),
		mHitEndFrame(0.f),
		mDrawStartFrame(0.f),
		mDrawEndFrame(0.f),
		mEnableContactResponse(false),
		mWeaponStatus(0)
	{
		mWeaponStatus = std::make_shared<GameObjectData::WeaponStatus>();
	}

	AccessoryHook::~AccessoryHook(){}

	::MMD::AnimationState::Hook::IHookSharedPtr AccessoryHook::instance( 
		GameObject::AccessorySharedPtr accessory,
		::MMD::Bone* bone,
		::GameObjectData::StatusSharedPtr status/*•Ší‚ªUŒ‚—Í‚ð‹‚ß‚é‚½‚ß‚É•K—v*/ ) 
	{
		mWeaponStatus->me = status;
		::MMD::AnimationState::Hook::IHookSharedPtr p = ::MMD::AnimationState::Hook::AccessoryHook::create(
			accessory, 
			mHitStartFrame, mHitEndFrame,
			mDrawStartFrame, mDrawEndFrame,
			bone,
			mEnableContactResponse,
			mWeaponStatus );
		return p;
		//MMD::AnimationState::Hook::AccessoryHookSharedPtr r = std::dynamic_pointer_cast<MMD::AnimationState::Hook::AccessoryHook>(p);
		//assert(r);
		//return r;
	}
EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(AccessoryHook);

} } } }//end namespace XmlLoader::MMD::AnimationState::Hook


BOOST_CLASS_IMPLEMENTATION(XmlLoader::MMD::AnimationState::Hook::AccessoryHook, boost::serialization::object_serializable);
