#pragma once
#include"GameObject/ICollider.h"
#include"GameObject/SharedPtrs.h"
#include<memory>
#include<map>
#include<array>

//#define NOT_LOAD_MMD

namespace Input{
	class PlayerMouse;
}

namespace GameLib {
	namespace Math {
		class Vector3;
	}
	namespace FileIO {
		class InFile;
	}
	namespace PseudoXml{
		class Document;
	}
}


namespace Camera {
	class SpringCameraWithoutYAxisEx;
	class PlayerCamera;
}

namespace  GUI{
	class Button;
	class Label;
}

namespace GameObjectData{
	class Status;
	class WeaponStatus;
}

class btPersistentManifold;
class btCollisionObject;
class btRigidBody;
typedef std::shared_ptr<btRigidBody> BtRigidBodySharedPtr;
class btCollisionShape;
typedef std::shared_ptr<btCollisionShape> BtCollisionShapeSharedPtr;
class btCylinderShape;
typedef std::shared_ptr<btCylinderShape> BtCylinderShapeSharedPtr;

namespace MME{ namespace Object{
	class ModelKai;
	typedef std::shared_ptr<ModelKai> ModelKaiSharedPtr;
} }

namespace GameObject {
	class Accessory;

	class CharacterControllerGhostObject;
	class BoneCollisionObject;
	class Bullet;

//#define TYPEDEF_SHARED_PTR( class_name ) \
//	typedef std::shared_ptr<class_name> class_name##SharedPtr;

namespace OldPlayer {
	class CharacterControllerRigidBody;

	namespace Updater {
		class IUpdater;
		enum State;
		//namespace QuarterView {
		//	class StandUpdater;
		//	class RunUpdater;
		//	class JumpUpdater;
		//	class LieUpdater;
		//	class StumbleUpdater;
		//}
		//namespace TPS {
		//	class StandUpdater;
		//	class RunUpdater;
		//	class JumpUpdater;
		//	class LieUpdater;
		//	class StumbleUpdater;
		//	class StepUpdater;
		//	class SwingUpdater;
		//	class ShotUpdater;
		//}

};

	//changeAnimationで使用
	enum Animation{
		ANIM_STAND,
		ANIM_RUN,
		ANIM_PUNCH,
		ANIM_SWING,
		ANIM_STUMBLE,
		ANIM_LIE,
	};

	std::shared_ptr<Player> create();

class Player : public ICollider  {
public:
	//make_sharedがprivate　コンストラクタ呼ぶのに必要
	friend class std::tr1::_Ref_count_obj<Player>;

	static std::shared_ptr<Player> create();
	static std::shared_ptr<Player> create(
		MME::Object::ModelKaiSharedPtr model,
		BtCollisionShapeSharedPtr,
		GameObjectData::StatusSharedPtr );

	virtual ~Player();

	void load();

	void release();

	void update( float elapsedTime );
	void preDraw()const;
	void drawHUD() const;

	RTTI_DECL;

	virtual btCollisionObject* getBtCollisionObject();

	virtual void removeFromWorld();

	virtual void addToWorld();

	virtual void onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj );

	
	//現在位置からmove分移動する
	//@parm
	//move ヒットバックする方向と大きさ
	void hitback( const btVector3 & dir );
	
	void checkLeftClick();

	void fire();
	void fire( const btVector3 &target );
	void move( const btVector3 &pos );
	void moveForward( const float &moveValue );
	//void setVelocity( const btVector3 &vel );
	void jump();
	//has or have
	bool jumpIfHaveEnoughStamina();
	void jumpLow();
	void jumpHi();
	void forceJump();
	void jump(const float &speed);
	void forceJump( const float &speed );

	bool forceJumpIfHaveEnoughStamina();

	//その場に停止
	void stop();
	//摩擦で自動にとまる(慣性あり)
	void cut();

	void look( const btVector3 & pos );
	void strafe( const btVector3 & pos  );

	bool isStopping() const;
	bool isTurning() const;
	bool isMoving() const;
	bool onGround() const;

	//スタミナ減少のみ状態移行
	bool useStaminaIfCanRunHigh();	
	bool useStaminaIfCanRun();
	bool useStaminaIfCanWalk();

	void setMaxSpeed( float speed );

	void setMaxSpeedLow();
	void setMaxSpeedNormal();
	void setMaxSpeedHigh();

	void healStamina();

	float getElapsedTime()const{
		return mElapsedTime;
	}

	void changeAnimation( Animation anim );

	btVector3 getMousePos()const;

	bool changeUpdater( const Updater::State &state );

	Camera::PlayerCamera* getCamera(){
		return mCamera;
	}

	MME::Object::ModelKai* getModel(){
		return mModel.get();
	}
	Input::PlayerMouse* getMouse(){
		return mMouse;
	}

	float getHeight()const{
		return mHeight;
	}

private:
	//shared_ptrで管理しろ
	Player();
	//disallow assign
	Player( const Player & );
	//disallow copy
	void operator =( const Player & );

	//CharacterControllerGhostObjectSharedPtr mController;
	CharacterControllerRigidBodySharedPtr mController;

	float	mHeight;
	float   mMass;
	BtRigidBodySharedPtr			mRigidBody;
	BtCylinderShapeSharedPtr		mCylinder;

	MME::Object::ModelKaiSharedPtr mModel;

	Camera::PlayerCamera *mCamera;

	Input::PlayerMouse *mMouse;

	float						mElapsedTime;

	btVector3					mTargetPos;

	enum { BULLET_SIZE=0, };
	//boost::shared_arrayを使うべきか
	std::array< BulletSharedPtr, BULLET_SIZE > mBullets;

	bool mIsAttacking;

	GameObjectData::WeaponStatusSharedPtr	mBulletWeaponStatus;

	Updater::IUpdaterSharedPtr			mUpdater;
	Updater::IUpdaterSharedPtr			mOldUpdater;

	GUI::Label *mHpBar;
	GUI::Label *mHpBackGroundBar;


};
} } //GameObject::OldPlayer
