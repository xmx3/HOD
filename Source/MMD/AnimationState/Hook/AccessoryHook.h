#ifndef __MMD_ANIMATIONSTATE_HOOK_ACCESSORYHOOK_H__
#define __MMD_ANIMATIONSTATE_HOOK_ACCESSORYHOOK_H__

#include"IHook.h"
#include"GameObjectData/fwd.h"


namespace boost {
	template<class T> class shared_ptr;
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
	class AccessoryHook;
	typedef std::shared_ptr<AccessoryHook> AccessoryHookSharedPtr;

//当たり判定と表示をコントロールするためのクラス
//引数多すぎ、分割するべきか
class AccessoryHook : public IHook {
public:
	//引数多すぎないか　間違えそう
	static IHookSharedPtr create( GameObject::AccessorySharedPtr accessory,
		float hitStartFrame, float hitEndFrame,
		float drawStartFrame, float drawEndFrame,
		Bone* bone,
		bool enableContactResponse,//物理的な反応をするか
		GameObjectData::WeaponStatusSharedPtr weapon );
	static IHookSharedPtr create( GameObject::AccessorySharedPtr accessory,
		float hitStartFrame, float hitEndFrame,
		Bone* bone,
		GameObjectData::WeaponStatusSharedPtr weapon );

	virtual ~AccessoryHook();
	virtual void hookUpdate( float currentFrame );
	virtual void hookStart();
	virtual void hookChangeState();
	virtual void hookAnimationOver();
private:
	// use create(). can use only shared_ptr.
	AccessoryHook(
		GameObject::AccessorySharedPtr accessory,
		float hitStartFrame, float hitEndFrame,
		float drawStartFrame, float drawEndFrame,
		Bone* bone,
		bool enableContactResponse,//物理的な反応をするか
		GameObjectData::WeaponStatusSharedPtr weapon );
	//disallow assign
	AccessoryHook( const AccessoryHook & )=delete;
	//disallow copy
	void operator=( const AccessoryHook & )=delete;

	GameObject::AccessorySharedPtr mAccessory;
	float mHitStartFrame;
	float mHitEndFrame;
	float mDrawStartFrame;
	float mDrawEndFrame;
	Bone* mBone;
	bool mEnableContactResponse;//bulletPhysics
	GameObjectData::WeaponStatusSharedPtr mWeaponStatus; 
};

}//MMD
}//AnimationState
}//Hook

#endif