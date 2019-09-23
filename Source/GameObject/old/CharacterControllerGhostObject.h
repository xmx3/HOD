#ifndef __GAMEOBJECT_CHARACTERCONTOROLERGHOSTOBJECT_H__
#define __GAMEOBJECT_CHARACTERCONTOROLERGHOSTOBJECT_H__

#include<btBulletCollisionCommon.h>
#include"GameObject/ICollider.h"
#include"RTTI/RTTI.h"
#include<memory>

namespace kztr{
	class CharacterController2;
}
class btCapsuleShape;
class btCharacterControllerInterface;
class btKinematicCharacterController;
class btPairCachingGhostObject;
class btCollisionShape;
class btGhostPairCallback;
class btTransform;
class btVector3;
namespace GameObject {

class CharacterControllerGhostObject;
typedef std::shared_ptr<CharacterControllerGhostObject> CharacterControllerGhostObjectSharedPtr;

//衝突検出が遅すぎるのでCharacterControllerRigidBodyを作る
//カプセル型のキャラクターを操作するオブジェクト
class CharacterControllerGhostObject : public ICollider {
public:
	static CharacterControllerGhostObjectSharedPtr create(
		ICollider* parent,
		const btTransform &startTransform,
		float characterHeight,
		float characterWidth,
		float velocity,
		float angularSpeed
	);
	virtual ~CharacterControllerGhostObject();

	//btTransform const & getWorldTransform() const;
	//btTransform & getWorldTransgorm();
	
	RTTI_DECL;
	
	//なければNULL返す
	virtual btCollisionObject* getBtCollisionObject();
	
	virtual void removeFromWorld();
	virtual void addToWorld();
	
	//btCollisionObjectが接触している間、呼ばれ続ける
	virtual void onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj){
		mParent->onCollisionStay( manifold, me, obj );
	}

	//btCollisionObjectが衝突したとき呼ばれる
	virtual void onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj){
		mParent->onCollisionEnter( manifold, me, obj );	
	}

	//btCollisionObjectが離れたとき呼ばれる
	virtual void onCollisionExit( btCollisionObject *me, btCollisionObject *obj ){
		mParent->onCollisionExit( me, obj );
	}

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
	void jump(const float &speed );
	void forceJump( const float &speed );

	//void clearForce();

	//void hitback( const btVector3 & impulse );


	void update(float elapsedTime);

	void setMaxSpeed( float maxSpeed ){
		mMaxSpeed = maxSpeed;
	}


	//到着したか確認
	//次回に到着するならスピードを調整
	//到着していれば、スピードを0に
	//setWalkDirection バージョン
	void checkArrivalInNexTime();
	//setVelocity バージョン
	void checkArrivalInNexTime( float dt );
private:
	//disallow raw pointer. use create().
	//カプセル形状の当たり判定を作る
	CharacterControllerGhostObject(
		ICollider* parent,
		const btTransform &startTransform,
		float characterHeight,
		float characterWidth,
		float velocity,
		float angularSpeed );
	//disallow assign
	CharacterControllerGhostObject( const CharacterControllerGhostObject & );
	//disallow copy
	void operator=( const CharacterControllerGhostObject & );

	ICollider *mParent;

	kztr::CharacterController2		*mCharacter;//btKinematicCharacterController	*m_character;
	btPairCachingGhostObject		*mGhostObject;
	btCapsuleShape					*mCapsule;

	float							mMaxSpeed;
	float							mMaxAngularSpeed;

	bool	mIsDash;
	bool	mIsJump;
	btVector3 mTarget;

	bool mHasMoved;//目的地に着いた？
	bool mCanMove;//移動できる？lookを実装するのに使用
	bool mCanTurn;//回転できる？
	bool mHasTurned;//回転は終了した？

	unsigned short mFilterGroup;
	unsigned short mFilterMask;

	bool mIsInWorld;

	float mSpeed;
	//float mMass;

	float mJumpSpeed;
	float mJumpHiSpeed;
	float mJumpLowSpeed;
};

}//end namespace GameObject

#endif //__GAMEOBJECT_CHARACTERCONTOROLERGHOSTOBJECT_H__