#ifndef __GAMEOBJECT_BONE_COLLISIONOBJECT_H__
#define __GAMEOBJECT_BONE_COLLISIONOBJECT_H__
#include"GameObject/ICollider.h"
#include"RTTI/RTTI.h"
#include<vector>
#include<memory>
class btPairCachingGhostObject;
class btGhostObject;
class btCollisionShape;
class btVector3;
class btCollisionObject;
class CBone;
namespace MMD{
	namespace AnimationState {
		class BaseAnimationState;
	}
}

namespace GameLib {
	namespace Scene {
		class Model;
		class Batch;
		class Container;
	}
}

namespace GameObjectData{
	class Status;
	class WeaponStatus;
}

namespace GameObject {
class Enemy;

//パンチとかキックのボーンが必要な当たり判定
//kinematic collision object with bone
//無理に訳すと ボーンに追従するキネマティック当たり判定
//kinematic object とは押すことは出来るけど、自分は押されないオブジェクト
//mRigidBody->setCollisionFlags( btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE );
//mRigidBody->setActivationState( DISABLE_DEACTIVATION );
// 上の設定で現在は押さなくなっている
class BoneCollisionObject : public ICollider {
public:
	friend class MMD::AnimationState::BaseAnimationState;
	//shapeになぜshared_ptrを使っているか？
	//deleteの責任があいまいになるから
	//自分のコーディングルールは、newしたクラスでdeleteするだが、
	//ここでその設計にするとshapeをもたなくて良いクラスで持つことになるし、
	//deleteの所在があいまいになる。
	//shapeはここでdeleteしたい。
	//shared_ptrとナマポが混ざることになるがそこは見逃せ
	BoneCollisionObject(
		float mass,
		float start, float end,
		std::shared_ptr<btCollisionShape> shape,
		btCollisionObject *owner,
		CBone *bone,
		GameObjectData::WeaponStatus *weaponStatus );
	virtual ~BoneCollisionObject();
	
	virtual void addToWorld();
	virtual void removeFromWorld();
	
	void draw() const;

	RTTI_DECL;
	
	//なければNULL返す
	virtual btCollisionObject* getBtCollisionObject();
	
	//virtual void onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );
	virtual void onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );
	//virtual void onCollisionExit(  btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );

	//float getMass() const ;

	//void loadAccessory( const char *fileName );
	//bool isReady();

	void createModel( unsigned int numBatchs, float scale );
	void setBatch( unsigned int index, GameLib::Scene::Batch b );

	//void calcDamage( GameObjectData::Status *st ){
	//	mWeaponStatus->attack(st);
	//}
	//
	//void attack( Enemy* e ){
	//	attack( e->getStatus() );
	//	e->hitback();
	//}
	//void attack( Enemy* e, GameObjectData::Status *enemySt, btRigidBody *enemyBody );
	//void attack( Player* p, GameObjectData::Status *playerSt );


	void attack( Enemy *enemy, GameObjectData::Status *enemyStatus );

	//void setWeaponStatus( GameObjectData::WeaponStatus *weaponStatus );


private:
	//float はたいていの場合　elapsedTime=1.f/30.f sec
	//だが、BoneCollisionObjectの場合のみ currentFrame
	//発生フレームと終了フレームで当たり判定を出すため現在のフレームが欲しい
	//privateなのはfrendでアクセスコントロールしてるため
	virtual void update( float currentFrame );
	
	// Kinematic用モーションステート
	struct KinematicMotionState;
	
	//disallow assingn
	BoneCollisionObject( const BoneCollisionObject& );
	//disallow copy
	void operator=( const BoneCollisionObject& );

	void calcDamage( GameObjectData::Status *st );


	//btPairCachingGhostObject	*mGhost;
	btRigidBody							*mRigidBody;
	std::shared_ptr<btCollisionShape> mShape;
	btCollisionObject					*mBtObjOfOwner;
	CBone								*mBone;
	bool								mIsInWorld;

	float mStart;
	float mEnd;

	
	struct Model;
	Model *mModel;
	//GameLib::Scene::Container *mContainer;

	GameObjectData::WeaponStatus *mWeaponStatus;
};
}//end namespace GameObject
#endif//__GAMEOBJECT_BONE_COLLISIONOBJECT_H__
