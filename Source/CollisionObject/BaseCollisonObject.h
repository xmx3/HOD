#pragma once
#include"ICollisionObject.h"
#include"GameObjectData/fwd.h"
#include<LinearMath/btTransform.h>

class btRigidBody;
//typedef std::shared_ptr<btRigidBody> BtRigidBodySharedPtr;
typedef std::unique_ptr<btRigidBody> BtRigidBodyUniquePtr;



namespace CollisionObject {
	class BaseCollisionObject {
	public:
		BaseCollisionObject();
		virtual ~BaseCollisionObject();

		//一回だけしか衝突しない場合
		bool canCollideOnlyOnce();

		void attack(GameObjectData::Status*) const;

		const btTransform & getWorldTransform() const;

		btTransform & getWorldTransform();
		
		void setWeaponStatus(GameObjectData::WeaponStatusSharedPtr weaponStatus)
		{
			mWeaponStatus = weaponStatus;
		}

		GameObjectData::WeaponStatusSharedPtr getWeaponStatus()const {
			return mWeaponStatus;
		}

		GameObjectData::StatusSharedPtr	getStatus()const {
			return mStatus;
		}

		void copyWeaponStatus(const GameObjectData::WeaponStatusSharedPtr &src);
		void copyWeaponStatus(const GameObjectData::WeaponStatus &src);


		//一回だけしか衝突しない場合
		bool canCollideOnlyOnce()const;

		bool isInWorld()const;

		btCollisionObject* getBtCollisionObject();

		//mIsInWorldがtrueなら、物理世界から削除してmIsInWorldをtrueにセットする
		void defalut_removeFromWorld();

		//mIsInWorldがfalseなら、
		//物理世界に追加して(mFilterGroup, mFilterMaskを考慮して)、
		//mIsInWorldをfalseにセットする
		void defalut_addToWorld();

		void hitback(const btVector3 &dir, float hitbackValue);

		virtual void onCollisionEnter(btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj);

		float getMass() const {
			return mMass;
		}

	protected:
		GameObjectData::StatusSharedPtr		mStatus;
		GameObjectData::WeaponStatusSharedPtr	mWeaponStatus;

		bool mIsInWorld;
		BtRigidBodyUniquePtr mRigidBody;
		float mMass;

		unsigned short	mFilterGroup;
		unsigned short	mFilterMask;

	};

}
