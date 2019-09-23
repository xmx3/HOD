#ifndef __GAMEOBJECT_IATTACKABLE_H__
#define __GAMEOBJECT_IATTACKABLE_H__

#include"IGameObject.h"
#include"RTTI/RTTI.h"
class RTTI;
namespace GameObjectData {
	class Status;
}
namespace GameObject {
	class IAttackAble {
	public:
		virtual ~IAttackAble(){}
		virtual void attack( GameObjectData::Status* ) = 0; 
		RTTI_DECL;
	};

}//end namespace GameObject

#endif//__GAMEOBJECT_IATTACKABLE_H__