#ifndef __CHARACTERCONTOROLEROBJECT_H__
#define __CHARACTERCONTOROLEROBJECT_H__

#include<btBulletCollisionCommon.h>
#include"GameObject/IGameObject.h"
#include"RTTI/RTTI.h"

namespace kztr{
	class CharacterController2;
}

class btCharacterControllerInterface;
class btKinematicCharacterController;
class btPairCachingGhostObject;
class btCollisionShape;
class btGhostPairCallback;
class btTransform;
class btVector3;
namespace GameObject {
//カプセル型のキャラクターを操作するオブジェクト
class CharacterControllerObject : public IGameObject {
public:
	enum Mode {
		MODE_WALK,
		MODE_ACCEL,
		MODE_CLICK
	};

	//カプセル形状の当たり判定を作る
	CharacterControllerObject(
		const btTransform &startTransform,
		float characterHeight,
		float characterWidth,
		float velocity,
		float angularSpeed );

	virtual ~CharacterControllerObject();

	virtual btTransform const & getWorldTransform() const;
	virtual btTransform & getWorldTransgorm();

	virtual GameObjectType getGameObjectType() const {
		return CHARACTER_CONTROLLER;
	}

	virtual GameObjectId getID() const {
		return mId;
	}
	
	RTTI_DECL;

	virtual bool isTerrain() const{
		return false;
	}

	virtual bool isMMDObject() const{
		return false;
	}

		
	virtual bool enableCollidedMMDObject() const{
		return false;
	}
	
	//なければNULL返す
	virtual btCollisionObject* getBtCollisionObject();
	
	//BoneCollisionObjectの自分のパンチが自分に当たらないようにするため必要
	//当たり判定を2つ以上持つ場合持つ場合（地形用、その他）必要。
	//いらない場合はgetEmptyBtCollisionObjects()を使って実装。
	//virtual const std::vector< const btCollisionObject* > & getNotCollideBtCollisionObjects() const
	//{
	//	return getEmptyBtCollisionObjects();
	//}

	//virtual void applyForce( const btVector3 &force ){};

	virtual void removeFromWorld();
	virtual void addToWorld();
	

	void draw()const;

	void warp( const btVector3 &pos );
	
	const btVector3& getVelocity() const;
	//void setSpeed( const float &v );
	
	//float getAngularSpeed();
	//void setAngularSpeed( const float &v );

	void setUserPtr( void *ptr );

	bool onGround() const;
	bool onGroundPerhaps() const;

	void setControleFlags( 
		bool isDash,
		bool isJump,
		const btVector3 &target )
	{
		mIsDash = isDash;
		mIsJump = isJump;
		mTarget = target;
		mIsArrived = false;
	}

	//
	void setWalkControleFlags(
		bool up,
		bool down,
		bool left,
		bool right 	){
			mIsUp		= up;
			mIsDown	= down;
			mIsLeft	= left;
			mIsRight	= right;
	}

	//update3種類1フレーム間にどれか一つだけ呼び出すこと

	//右左で回転上下で前後進
	void walkControleUpdate( float elapsedTime );
	
	//ターゲットに向かって進むアクセル型
	void update(float elapsedTime);

	//ターゲットに向かって進む自動型
	void update2( float elapsedTime );

	//到着したか確認
	//次回に到着するならスピードを調整
	//到着していれば、スピードを0に
	void checkArrivalInNexTime();
private:
	const GameObjectId	mId;

	kztr::CharacterController2		*mCharacter;//btKinematicCharacterController	*m_character;
	btPairCachingGhostObject		*mGhostObject;
	
	float							mMaxSpeed;
	float							mMaxAngularSpeed;

	bool	mIsDash;
	bool	mIsJump;
	btVector3 mTarget;

	bool mIsArrived;//目的地に到着したか？

	bool mIsUp;
	bool mIsDown;
	bool mIsLeft;
	bool mIsRight;

	unsigned short mFilterGroup;
	unsigned short mFilterMask;


	bool mIsInWorld;

	Mode mMode;

	float mSpeed;
};

}//end namespace GameObject

#endif //__CHARACTERCONTOROLEROBJECT_H__