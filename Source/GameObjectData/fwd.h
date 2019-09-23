#pragma once
#include<memory>

namespace GameObjectData{

enum Group{
	GroupPlayer=0,
	GroupEnemy=1,
};

enum DamageType{
	NOTHING		= 0x0000,
	CUT		= 0x0001,//slash//斬
	STRIKE	= 0x0002,//HIT、打
	THURUST	= 0x0004,//STAB、突
	FIRE	= 0x0008,
	ICE		= 0x0010,
	ENERGY	= 0x0020,//光、エネルギー属性
	MITEI1	= 0x0040,
	MITEI2	= 0x0080,
};
	
class Status;
typedef std::shared_ptr<Status> StatusSharedPtr;
typedef std::weak_ptr<Status> StatusWeakPtr;

class WeaponStatus;
typedef std::shared_ptr<WeaponStatus> WeaponStatusSharedPtr;

class IWeaponStatus;
typedef std::shared_ptr<IWeaponStatus> IWeaponStatusSharedPtr;

}
