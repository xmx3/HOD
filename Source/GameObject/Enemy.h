#pragma once
#ifndef __GAMEOBJECT_ENEMY_H__
#define __GAMEOBJECT_ENEMY_H__
#include<memory>
#include"BaseObject.h"

class btRigidBody;
class btSphereShape;
class btBoxShape;
class btTransform;

typedef std::shared_ptr<btBoxShape> BtBoxShapeSharedPtr;


namespace GameObjectData{
	class Status;
	class WeaponStatus;
}

namespace GUI{
	class Label;
}

namespace MMD{
	class HumanModel;
}

namespace MME{ namespace Object {
	class ModelKai;
	typedef std::shared_ptr<ModelKai> ModelKaiSharedPtr;
} }

namespace Component {
	class RigidBodyComponent;
	typedef std::shared_ptr<RigidBodyComponent> RigidBodyComponentSharedPtr;
}

namespace GameObject {

class Enemy;
typedef std::shared_ptr<Enemy> EnemySharedPtr;

class Enemy : public  BaseObject {
public:
	static EnemySharedPtr create(
		float mass,
		MME::Object::ModelKaiSharedPtr model,
		BtBoxShapeSharedPtr shape,
		BtMotionStateSharedPtr motionState,
		BtRigidBodySharedPtr rigidbody,
		GameObjectData::StatusSharedPtr status );

	virtual ~Enemy();
	
	RTTI_DECL;

	void postdraw() const;

	void update(float elapsedTime);

	virtual void removeFromWorld();
	virtual void addToWorld();

	virtual void onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );
	
	bool isDied()const;

	//void setPlayer(IColliderSharedPtr player){
	//	mPlayer=player;
	//}

	void updateWhenDied( float );

	btCollisionObject* getBtCollisionObject();

	const btCollisionObject* getConstBtCollisionObject()const;

	const btTransform & getWorldTransform() const;

	btTransform & getWorldTransform();

	bool isInWorld()const;

	//ここでダメージ計算を行う、ヒットバック処理等はまた別の所で行う
	virtual void takeDamage(
		BaseObject* DamageCauser
	);

	virtual int calculateDamage()override;

	//ダメージを与えるオブジェクトかどうか？
	virtual bool canDamage()override;

	//ダメージを求めるのに使用
	//ダメージを与えるオブジェクトでなければnullを返すこともある
	virtual const GameObjectData::WeaponStatus* getWeaponStatus()override;

	int getChain() const {
		return mChain;
	}

private:
	//初期化に自分ののスマートポインタ使いたい場合がありそうなのでここでメンバーの初期化はしない
	//要は遅延初期化をしたい
	Enemy();
	void init(
		float mass,
		MME::Object::ModelKaiSharedPtr model,
		BtBoxShapeSharedPtr shape,
		BtMotionStateSharedPtr motionState,
		BtRigidBodySharedPtr rigidbody,
		GameObjectData::StatusSharedPtr status
	);

	
	//disallow copy
	void operator=( const Enemy & )=delete;
	//disallow assign
	Enemy(const Enemy & )=delete;
	
	void initBullet();

	float mMass;

	Component::RigidBodyComponentSharedPtr mRigidBodyComponent;

	MME::Object::ModelKaiSharedPtr mModel;

	GameObjectData::StatusSharedPtr mStatus;

	float			mElapsedTime;
	float			mElapsedTimeSinceDeath;

	float mElapsedTimeAfterLunch;
	
	GUI::Label *mHpBar;
	GUI::Label *mHpBackGroundBar;

	unsigned short	mFilterGroup;
	unsigned short	mFilterMask;

	int mDamageValueForChain;
	int mChain;


};
}//end namespace GameObject
#endif