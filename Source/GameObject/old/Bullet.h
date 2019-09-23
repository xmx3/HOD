#ifndef __GAMEOBJECT_Bullet_H__
#define __GAMEOBJECT_Bullet_H__
#include"IRigidBody.h"
#include<memory>
#include<vector>
class btRigidBody;
class btSphereShape;
class btBoxShape;
class btTransform;
class btVector3;

namespace GameObjectData{
	class Status;
}

namespace GameObject {
	class Bullet;

typedef std::shared_ptr<Bullet> BulletSharedPtr;

class Bullet : public IRigidBody {
public:
	//make_sharedがprivate　コンストラクタ呼ぶのに必要
	friend class std::_Ref_count_obj<Bullet>;

	static BulletSharedPtr create( const btTransform & startTrans, const btVector3 &velocity, const float &radius, IColliderWeakPtr parent );
	
	static BulletSharedPtr createForEnemy( const btTransform & startTrans, const btVector3 &velocity, const float &radius, IColliderWeakPtr parent );
	static BulletSharedPtr createForPlayer( const btTransform & startTrans, const btVector3 &velocity, const float &radius, IColliderWeakPtr parent );


	virtual ~Bullet();
	
	RTTI_DECL;

	void draw() const;

	void update(float elapsedTime);

	virtual void removeFromWorld();
	virtual void addToWorld();

	virtual void onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );
	//virtual void onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );
	//virtual void onCollisionExit(  btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );

	IColliderWeakPtr getParent();

	void setWorldTransform(const btTransform &startTrans );
	void setLinerVelocity( const btVector3 &linerVelocity );

	
	void setActivationTime(float t){
		mActivationTime=t;
	}

	float getActivationTime()const{
		return mActivationTime;
	}
	
	void lunch(  const btTransform & startTrans, const btVector3 &velocity, float activeTime = 10.f );

private:
	//disallow raw pointer. use create
	Bullet();
	//disallow raw pointer. use create
	Bullet(  const btTransform & startTrans, const btVector3 &velocity, const float &radius, IColliderWeakPtr parent );

	//disallow copy and assign
	Bullet( const Bullet & );
	void operator =( const Bullet & );

	void calcDamage( GameObjectData::Status *objStatus ); 


	btSphereShape		*mShape;
	IColliderWeakPtr	mParent;
	
	float mActivationTime;
};
}
#endif
