#pragma once
#include"ICollider.h"
#include<memory>
class btRigidBody;
//typedef std::shared_ptr<btRigidBody> BtRigidBodySharedPtr;
typedef std::unique_ptr<btRigidBody> BtRigidBodyUniquePtr;

namespace GameObject {
class IRigidBody : public ICollider {
public:
	IRigidBody();
	virtual ~IRigidBody();

	RTTI_DECL;

	bool isInWorld()const;

	virtual btCollisionObject* getBtCollisionObject();
	
	//mIsInWorldがtrueなら、物理世界から削除してmIsInWorldをtrueにセットする
	void defalut_removeFromWorld();

	//mIsInWorldがfalseなら、
	//物理世界に追加して(mFilterGroup, mFilterMaskを考慮して)、
	//mIsInWorldをfalseにセットする
	void defalut_addToWorld();

	void hitback( const btVector3 &dir, float hitbackValue );

	virtual void onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj);
	
	float getMass() const {
		return mMass;
	}

protected:
	bool mIsInWorld;
	BtRigidBodyUniquePtr mRigidBody;
	float mMass;

	unsigned short	mFilterGroup;
	unsigned short	mFilterMask;
};

}//end namespace GameObject