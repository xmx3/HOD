#pragma once
#ifndef __GAMEOBJECT_ACCESSORY_H__
#define __GAMEOBJECT_ACCESSORY_H__
#include"GameObject/BaseObject.h"
#include"RTTI/RTTI.h"
#include<memory>
namespace MMD{
class Bone;
}// namespace MMD

namespace MME {
	enum MMDPass;
}

class btCollisionObject;
class btCollisionShape;
class btTransform;
class btVector3;
struct btDefaultMotionState;
typedef std::shared_ptr<btDefaultMotionState> BtDefaultMotionStateSharedPtr;

typedef std::shared_ptr<btCollisionShape> BtCollisionShapeSharedPtr;
class btTriangleMesh;
typedef std::shared_ptr<btTriangleMesh> BtTriangleMeshSharedPtr;
//if btCollisionShape don't use btTriangleMesh, pair.second returns NULL. 
//この型はbtTiangleMeshの削除の責任をGameObject::Accessoryに委譲するために必要
typedef std::pair<BtCollisionShapeSharedPtr, BtTriangleMeshSharedPtr> BtCollisionShapeAndBtTriangleMesh; 

class btRigidBody;
typedef std::shared_ptr<btRigidBody> BtRigidBodyShardPtr;


namespace GameLib {
	namespace Math {
		class Matrix34;
	}
}

namespace Component {
	class RigidBodyComponent;
	typedef std::shared_ptr<RigidBodyComponent> RigidBodyComponentSharedPtr;
	class CanCollideExceptIgnoredObjectsCallback;
}

namespace GameObjectData {
	class WeaponStatus;
	typedef std::shared_ptr<WeaponStatus> WeaponStatusSharedPtr;
}

namespace GameObject {

namespace AccessoryUtils {
	namespace MME{
		class Model;
	}
}

class Accessory;
typedef std::shared_ptr<Accessory> AccessorySharedPtr;


//表示と当たり判定を管理するクラス
//表示だけ、当たり判定だけで使うことも可能
//AccessoryHookと組み合わせて使う
class Accessory : public BaseObject {
public:
	//bone追従のキネマティック剛体オブジェクト
	//Accessory( 
	//	std::shared_ptr<btCollisionShape> shape,
	//	std::shared_ptr<AccessoryUtils::MME::Model> model,
	//	float mass,
	//	btCollisionObject *owner,
	//	Bone *bone=NULL
	//);

	//通常の剛体オブジェクト
	Accessory( 
		BtCollisionShapeAndBtTriangleMesh shapeAndMesh,
		std::shared_ptr<AccessoryUtils::MME::Model> model,
		float mass,
		btCollisionObject *owner,
		const btTransform &startTrans
	);

	virtual ~Accessory();

	RTTI_DECL;

	btCollisionObject* getBtCollisionObject();

	void removeFromWorld();
	void addToWorld();

	void draw() const;

	const std::string& getModelFileName()const;

	void debug_draw() const;
	
	void preDrawMMD();


	//めり込みを許すか？
	//貫通弾とか
	//剣を振るときヒットバックが発生して欲しくない場合,false
	//onCollisionEnter, onCollisionStay, onCollisionExit は発生する
	void enableContactResponse( bool enable );

	void attachBone(MMD::Bone* bone=NULL);
	void separeteFromBone();
	void setVelocity( const btVector3 &velocity );

	bool isInWorld()const{
		return mIsInWorld;
	}

	bool canDraw()const;

	void setCanDraw( bool canDraw );

	void setCanDraw( MME::MMDPass pass, bool canDraw );
	
	virtual void onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );
	//btCollisionObjectが接触している間、呼ばれ続ける
	virtual void onCollisionStay(btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj) 
	{}
	//btCollisionObjectが離れたとき呼ばれる
	virtual void onCollisionExit(btCollisionObject *me, btCollisionObject *obj)
	{}


	bool isReady();
	const MMD::Bone* getBone()const{
		return mBone;
	}

	btCollisionObject* getOwner(){
		return mOwner;
	}

	float getScale()const;
	void setScale(float scale);

	void setWeaponStatus(GameObjectData::WeaponStatusSharedPtr weapon);


	//一回のみのあたり判定
	bool canCollideOnlyOnce()const;

	virtual int calculateDamage();

	virtual bool canDamage();

	virtual const GameObjectData::WeaponStatus* getWeaponStatus();


private:
	Accessory(const Accessory &) = delete;
	void operator=(const Accessory &) = delete;
	
	// Kinematic用モーションステート
	struct KinematicMotionState;
	typedef std::shared_ptr<KinematicMotionState> KinematicMotionStateSharedPtr;
	//void setIsKinematic( bool isKinematic );


	BtRigidBodyShardPtr mRigidBody;
	BtCollisionShapeSharedPtr mShape;
	BtTriangleMeshSharedPtr mMesh;
	std::shared_ptr<AccessoryUtils::MME::Model> mModel;
	KinematicMotionStateSharedPtr mKinematicMotion;
	BtDefaultMotionStateSharedPtr mDefaultMotion;
	MMD::Bone		*mBone;

	bool mIsInWorld;

	btCollisionObject *mOwner;

	Component::RigidBodyComponentSharedPtr mRigidBodyComponent;
	Component::CanCollideExceptIgnoredObjectsCallback *mCanCollideCallback;


	GameObjectData::WeaponStatusSharedPtr mWeapon;
};
}//end namespace GameObject

#endif
