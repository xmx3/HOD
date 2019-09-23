#pragma once

#include<btBulletCollisionCommon.h>
#include"GameObject/ICollider.h"
#include"RTTI/RTTI.h"
#include<memory>


class btCapsuleShape;
class btCylinderShape;
typedef std::shared_ptr<btCylinderShape> BtCylinderShapeSharedPtr;
typedef std::shared_ptr<btRigidBody> BtRigidBodySharedPtr;
class btCharacterControllerInterface;
class btKinematicCharacterController;
class btPairCachingGhostObject;
class btCollisionShape;
class btGhostPairCallback;
class btTransform;
class btVector3;
namespace GameObject { namespace OldPlayer {

class CharacterControllerRigidBody;
typedef std::shared_ptr<CharacterControllerRigidBody> CharacterControllerRigidBodySharedPtr;
//namespace Controllerにでもするべきかもしれない
//GameObjectというよりbtRigitBodyのラッパーに近い
//衝突検出が遅すぎるのでCharacterControllerRigidBodyを作る


//カプセル型のキャラクターを操作するオブジェクト
class CharacterControllerRigidBody {
public:

	//float maxSpeed,　:　最高速度
	//float maxAngularSpeed:最高角速度
	//float mass 重さ
	static CharacterControllerRigidBodySharedPtr create(
		BtRigidBodySharedPtr rb,
		float maxSpeed,
		float maxAngularSpeed,
		float mass
	);
	virtual ~CharacterControllerRigidBody();
	
	btCollisionObject* getBtCollisionObject();

	const btTransform & getWorldTransform() const;

	btTransform & getWorldTransform();
	
	void removeFromWorld();
	void addToWorld();
	
	void draw()const;

	void warp( const btVector3 &pos );
	
	btVector3 getVelocity() const;
	//void setSpeed( const float &v );
	
	//float getAngularSpeed();
	//void setAngularSpeed( const float &v );

	//void setUserPtr( void *ptr );

	bool onGround() const;

	void stop();
	//自動に摩擦でとまらせる
	void cut();
	
	void look( const btVector3 &pos );

	void move( const btVector3 &pos );
	
	//動いてる？
	//canMoveがfalseの場合false
	bool isMoving() const;
	//回転してる？
	//canTurnがfalseの場合false
	bool isTurning() const;
	//止まっている？
	//止まっていても慣性で動いてる場合があり
	bool isStopping() const;

	//平行移動する。（回転しないで移動）
	void strafe( const btVector3 & pos );

	//身長の2倍
	void jumpHi();
	//身長の半分
	void jumpLow();
	//身長分
	void jump();
	//接地していなくてもジャンプ
	void forceJump();
	//速度セット
	void jump(const float &impulseY );
	void forceJump( const float &impulseY );

	//void clearForce();

	//void hitback( const btVector3 & impulse );


	void update(float elapsedTime);

	void setMaxSpeed( float maxSpeed ){
		mMaxSpeed = maxSpeed;
	}

private:
	//disallow raw pointer. use create().
	//カプセル形状の当たり判定を作る
	CharacterControllerRigidBody(
		BtRigidBodySharedPtr rb,
		float maxSpeed,
		float maxAngularSpeed,
		float mass );
	//disallow assign
	CharacterControllerRigidBody( const CharacterControllerRigidBody & );
	//disallow copy
	void operator=( const CharacterControllerRigidBody & );

	ICollider *mParent;

	BtRigidBodySharedPtr			mRigidBody;
	btCylinderShape					*mShape;

	float							mMaxSpeed;
	float							mMaxAngularSpeed;

	btVector3 mTarget;

	bool mHasMoved;//目的地に着いた？
	bool mCanMove;//移動できる？lookを実装するのに使用
	bool mCanTurn;//回転できる？
	bool mHasTurned;//回転は終了した？

	unsigned short mFilterGroup;
	unsigned short mFilterMask;

	bool mIsInWorld;

	float mSpeed;
	float mMass;

	float mJumpSpeed;

	bool mIsOnGround;
};

} }//end namespace GameObject::OldPlayer

