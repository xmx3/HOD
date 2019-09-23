#ifndef __GAMEOBJECT_ENEMY_H__
#define __GAMEOBJECT_ENEMY_H__
#include"GameObject/IRigidBody.h"
#include<memory>
#include"GameObject/SharedPtrs.h"

class btRigidBody;
class btSphereShape;
class btBoxShape;
class btTransform;


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
namespace GameObject {

	class Enemy;

typedef std::shared_ptr<Enemy> EnemySharedPtr;

class Enemy : public IRigidBody {
public:
	static EnemySharedPtr create(
		const IColliderSharedPtr &player,
		MME::Object::ModelKaiSharedPtr model,
		std::shared_ptr<btBoxShape> box,
		const GameObjectData::Status &status,
		const GameObjectData::WeaponStatus &weaponStatus
	);
	virtual ~Enemy();
	
	RTTI_DECL;

	void postdraw() const;

	void update(float elapsedTime);

	virtual void removeFromWorld();
	virtual void addToWorld();

	virtual void onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );
	
	bool isDied()const;
	void setPlayer(IColliderSharedPtr player){
		mPlayer=player;
	}

	void updateWhenDied( float );

private:
	//èâä˙âªÇ…shared_from_this()ÇégÇ¢ÇΩÇ¢ÇÃÇ≈ã÷é~
	//óvÇÕíxâÑèâä˙âªÇÇµÇΩÇ¢
	Enemy(
		const btTransform &world,
		MME::Object::ModelKaiSharedPtr model,
		std::shared_ptr<btBoxShape> box,
		const GameObjectData::Status &status,
		const GameObjectData::WeaponStatus &weaponStatus
	);
	
	//disallow copy
	void operator=( const Enemy & );
	//disallow assign
	Enemy(const Enemy & );
	
	void initBullet();

	std::shared_ptr<btBoxShape> mShape;

	MME::Object::ModelKaiSharedPtr mModel;
	
	float			mElapsedTime;
	float			mElapsedTimeSinceDeath;

	IColliderSharedPtr	mPlayer;


	enum {
		NumberBullets=5
	};

	BulletSharedPtr mBullets[NumberBullets];

	static std::shared_ptr<GameObjectData::Status>		sspStatus;
	static std::shared_ptr<GameObjectData::WeaponStatus>	sBulletWeaponStatus;
	
	float mElapsedTimeAfterLunch;
	
	GUI::Label *mHpBar;
	GUI::Label *mHpBackGroundBar;

};
}//end namespace GameObject
#endif