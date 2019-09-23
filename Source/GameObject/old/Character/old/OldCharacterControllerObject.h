#ifndef __OLDCHARACTERCONTOROLEROBJECT_H__
#define __OLDCHARACTERCONTOROLEROBJECT_H__
#include<btBulletDynamicsCommon.h>
namespace kztr{
	class CharacterController2;
}

class btCharacterControllerInterface;
class btKinematicCharacterController;
class btPairCachingGhostObject;
class btCollisionShape;
class btGhostPairCallback;
namespace Old {
//カプセル型のキャラクターを操作するオブジェクト
class CharacterControllerObject {
public:
	//カプセル形状の当たり判定を作る
	CharacterControllerObject(
		const btTransform &startTransform,
		float characterHeight,
		float characterWidth,
		float velocity,
		float angularVelocity ); // 2.f*3.14f * 0.01 * 30.f  2PI * (1回転/秒) * (frame/sec) 1回転で100frameかかる

	virtual ~CharacterControllerObject();

	void update(
		float elapsedTime,
		bool isForward,
		bool isBackforward,
		bool isLeft,
		bool isRight );

	void update(
		float elapsedTime,
		float deltaPitch,
		float deltaYaw,
		bool isDash,
		bool isJump,
		bool isAprochTarget,
		const btVector3 &targetPos );

	void update2(
		float elapsedTime,
		float deltaPitch,
		float deltaYaw,
		bool isDash,
		bool isJump,
		bool isAprochTarget,
		const btVector3 &targetPos );

	void draw()const;

	const btTransform & getWorldTransform() const;

	void warp( const btVector3 &pos );
	
	const btVector3& getVelocity() const;

	void setVelocity( const float &v ){
		mVelocity=v;
	}
	float getAngularVelocity(){
		return mAngularVelocity;
	}
	void setAngularVelocity( const float &v ){
		mAngularVelocity=v;
	}

	void setUserPtr( void *ptr );

	btCollisionObject* getBtCollisionObject();

	bool onGround() const;
	bool onGroundPerhaps() const;

	//bool checkCollisions();

	//btPairCachingGhostObject* getGhostObjPtr(){
	//	return m_ghostObject;
	//}
private:
	kztr::CharacterController2		*m_character;//btKinematicCharacterController	*m_character;
	btPairCachingGhostObject		*m_ghostObject;
	float							mVelocity;
	float							mAngularVelocity;
	float							mMaxVelocity;
	float							mMaxAngularVelocity;
	
	//timeをframeにすべき？
	//クラスにしたほうがいい
	float							mDashVel;
	float							mDashMaxVel;
	float							mDashAccel;
	float							mDashDeltaTime;//経過時間
	float							mDashEnableTime;//有効期間
	float							mDashMaxEnableTime;//最大有効期間
	float							mDashAddTime;//増える量
	
	float							mAirResistance;//空気抵抗係数
	float							mCoefficientOfFriction;//摩擦係数　動摩擦係数とか静止摩擦係数作る？

	float							mJumpVel;
	float							mJumpMaxVel;
	float							mJumpAccel;
	float							mJumpDeltaTime;//経過時間
	float							mJumpEnableTime;//有効期間
	float							mJumpMaxEnableTime;//最大有効期間
	float							mJumpAddTime;//増える量
};

}//end namespace Old
#endif //__OLDCHARACTERCONTOROLEROBJECT_H__