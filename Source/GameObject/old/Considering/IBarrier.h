#ifndef __GAMEOBJECT_IWEAPON_H__
#define __GAMEOBJECT_IWEAPON_H__

#include"IGameObject.h"
#include"RTTI/RTTI.h"
class RTTI;
class Status;
namespace GameObject {
	class IAttackAble {
	public:
		
		virtual ~IAttackAble(){}
		virtual void attack( Status* ) = 0; 
		RTTI_DECL;
	};

};

}//end namespace GameObject

#endif//__GAMEOBJECT_IWEAPON_H__