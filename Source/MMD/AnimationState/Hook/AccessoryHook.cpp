#include"AccessoryHook.h"
#include"MMD/AnimationState/BaseAnimationState.h"
#include"GameObject/Accessory.h"
#include"GameObjectData/WeaponStatus.h"
#include<assert.h>

namespace MMD{
namespace AnimationState{
namespace Hook {
namespace {
enum{
	DISABLE_DRAW_CONTOROL=-1,
};
}

IHookSharedPtr AccessoryHook::create( GameObject::AccessorySharedPtr accessory,
	float hitStartFrame, float hitEndFrame,
	float drawStartFrame, float drawEndFrame,
	Bone* bone,
	bool enableContactResponse,//•¨—“I‚È”½‰ž‚ð‚·‚é‚©
	GameObjectData::WeaponStatusSharedPtr weapon )
{

	assert( 
		drawStartFrame >= 0 &&
		drawEndFrame >= 0 &&
		drawStartFrame <= drawEndFrame &&
		hitStartFrame >= 0 &&
		hitEndFrame >= 0 &&
		hitStartFrame <= hitEndFrame );
	IHookSharedPtr spHook( new AccessoryHook(
		accessory,
		hitStartFrame, hitEndFrame,
		drawStartFrame, drawEndFrame,
		bone,
		enableContactResponse,
		weapon ) );
	return spHook;
}
IHookSharedPtr AccessoryHook::create( GameObject::AccessorySharedPtr accessory,
	float hitStartFrame, float hitEndFrame,
	Bone* bone,
	GameObjectData::WeaponStatusSharedPtr weapon )
{
	assert( 
		hitStartFrame >= 0 &&
		hitEndFrame >= 0 &&
		hitStartFrame <= hitEndFrame );

	IHookSharedPtr spHook( new AccessoryHook(
		accessory,
		hitStartFrame, hitEndFrame,
		DISABLE_DRAW_CONTOROL, DISABLE_DRAW_CONTOROL,
		bone,
		false,
		weapon ) );
	return spHook;
}

AccessoryHook::AccessoryHook(
	GameObject::AccessorySharedPtr accessory,
	float hitStartFrame, float hitEndFrame,
	float drawStartFrame, float drawEndFrame,
	Bone* bone,
	bool enableContactResponse,//•¨—“I‚È”½‰ž‚ð‚·‚é‚©
	GameObjectData::WeaponStatusSharedPtr weapon )
:mAccessory(accessory),
mWeaponStatus(weapon),
mHitStartFrame(hitStartFrame),
mHitEndFrame(hitEndFrame),
mDrawStartFrame(drawStartFrame),
mDrawEndFrame(drawEndFrame),
mBone(bone),
mEnableContactResponse(enableContactResponse)
{}
AccessoryHook::~AccessoryHook(){}

void AccessoryHook::hookUpdate(float currentFrame ){
	if( mHitStartFrame < currentFrame && currentFrame < mHitEndFrame ){
		mAccessory->addToWorld();
	} else {
		mAccessory->removeFromWorld();
	}

	if( mDrawStartFrame!=DISABLE_DRAW_CONTOROL ){
		if( mDrawStartFrame < currentFrame && currentFrame < mDrawEndFrame ){
			mAccessory->setCanDraw(true);
		} else {
			mAccessory->setCanDraw(false);
		}
	}
}
void AccessoryHook::hookStart(){
	mAccessory->setWeaponStatus( mWeaponStatus );
	mAccessory->attachBone(mBone);
	mAccessory->enableContactResponse(mEnableContactResponse);
}
void AccessoryHook::hookChangeState(){
	mAccessory->removeFromWorld();
	if( mDrawStartFrame!=DISABLE_DRAW_CONTOROL ){
		mAccessory->setCanDraw(false);
	}
}	
void AccessoryHook::hookAnimationOver(){}	

}//MMD
}//AnimationState
}//Hook
