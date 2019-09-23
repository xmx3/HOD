#include"IGameObject.h"
#include<numeric>

namespace GameObject{
	unsigned int IGameObject::sNum = 0;

	RTTI_ROOT_IMPL(IGameObject);

IGameObject::IGameObject()
	:mId(++sNum)
{
	assert(sNum!=(std::numeric_limits<GameObjectId>::max)());
}

void IGameObject::attack( GameObjectData::Status* st ){
	if( mWeaponStatus && st ){
		mWeaponStatus->attack( st );
	}
}

//ƒƒ“ƒo•Ï”‚ÅŠÇ—‚·‚é‚×‚«‚©
bool IGameObject::canCollideOnlyOnce(){
	return mWeaponStatus && mWeaponStatus->canCollideOnlyOnce;
}

void IGameObject::copyWeaponStatus(const GameObjectData::WeaponStatusSharedPtr &src){
	if( !mWeaponStatus ){
		mWeaponStatus = std::make_shared<GameObjectData::WeaponStatus>();
	}
	*mWeaponStatus = *src;
}

void IGameObject::copyWeaponStatus(const GameObjectData::WeaponStatus &src){
	if( !mWeaponStatus ){
		mWeaponStatus = std::make_shared<GameObjectData::WeaponStatus>();
	}
	*mWeaponStatus = src;
}


}//end namespace GameObject
 