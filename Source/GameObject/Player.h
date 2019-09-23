#pragma once
#include"BaseObject.h"
#include<memory>
//#include"RTTI/RTTI.h"
#include<LinearMath/btVector3.h>

namespace Input {
	class PlayerMouse;
	typedef std::shared_ptr<PlayerMouse> PlayerMouseSharedPtr;
}

namespace GameLib {
	namespace Math {
		class Vector3;
	}
	namespace FileIO {
		class InFile;
	}
	namespace PseudoXml {
		class Document;
	}
}


namespace Camera {
	class ICamera;
	class PlayerCamera;
	class Simple;
	typedef std::shared_ptr<ICamera> ICameraSharedPtr;
	typedef std::shared_ptr<PlayerCamera> PlayerCameraSharedPtr;
}

namespace  GUI {
	class Button;
	class Label;
}

namespace XmlLoader {
	class Actions;
}

namespace GameObjectData {
	class Status;
	typedef std::shared_ptr<Status> StatusSharedPtr;
	class WeaponStatus;
}

class btCollisionObject;
class btRigidBody;
typedef std::shared_ptr<btRigidBody> BtRigidBodySharedPtr;
class btCollisionShape;
typedef std::shared_ptr<btCollisionShape> BtCollisionShapeSharedPtr;
class btCylinderShape;
typedef std::shared_ptr<btCylinderShape> BtCylinderShapeSharedPtr;
class btMotionState;
typedef std::shared_ptr<btMotionState> BtMotionStateSharedPtr;

namespace BulletPhysics {
	class OnGroundChecker;
}


namespace MME {
	namespace Object {
		class ModelKai;
		typedef std::shared_ptr<ModelKai> ModelKaiSharedPtr;
	}
}

namespace Component {
	class RigidBodyComponent;
	typedef std::shared_ptr<RigidBodyComponent> RigidBodyComponentSharedPtr;
}


namespace GameObject {
	namespace Utils {
		class  Character;
		typedef std::shared_ptr<Character> CharacterSharedPtr;
	}

	namespace PlayerUtils {
		namespace Updater {
			class Parent;
		}
	}//PlayerUtils::Updater



	class Player : public BaseObject
	{
	public:

		static std::shared_ptr<Player> create(
			float height,
			MME::Object::ModelKaiSharedPtr model,
			BtCylinderShapeSharedPtr shape,
			BtMotionStateSharedPtr motionState,
			BtRigidBodySharedPtr rigidbody,
			Camera::ICameraSharedPtr camera,
			Input::PlayerMouseSharedPtr mouse,
			GameObjectData::StatusSharedPtr status);

		static std::shared_ptr<Player> create(
			Utils::CharacterSharedPtr character,
			GameObjectData::StatusSharedPtr status);


		virtual ~Player();


		void release();

		void update(float elapsedTime);
		void preDraw()const;
		void drawHUD() const;

		RTTI_DECL;


		void removeFromWorld();

		void addToWorld();

		virtual void onCollisionEnter(btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj);
		virtual void onCollisionStay(btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj);
		virtual void onCollisionExit(btCollisionObject *me, btCollisionObject *obj);

		float getElapsedTime()const {
			return mElapsedTime;
		}

		Input::PlayerMouse* getMouse() {
			return mMouse.get();
		}
		btVector3 getMousePos()const;

		//Camera::PlayerCamera* getCamera(){
		//	return mCamera;
		//}

		MME::Object::ModelKai* getModel() {
			return mModel.get();
		}

		float getHeight()const {
			return mHeight;
		}

		GameObjectData::Status* getStatus() {
			return mStatus.get();
		}

		Utils::CharacterSharedPtr getCharacter() {
			return mCharacter;
		}


		bool onGround()const;

		void addActions(XmlLoader::Actions* actions);

		btCollisionObject* getBtCollisionObject();

		virtual void takeDamage(
			BaseObject* DamageCauser
		);

		virtual int calculateDamage()override;

		virtual bool canDamage()override;

		virtual const GameObjectData::WeaponStatus* getWeaponStatus()override;

		void setCamera(Camera::ICameraSharedPtr camera)
		{
			mCamera = camera;
		}
		

	private:
		//make_sharedがprivate　コンストラクタ呼ぶのに必要
		friend class std::_Ref_count_obj<Player>;
		//shared_ptrで管理しろ
		Player();
		void init(
			float height,
			MME::Object::ModelKaiSharedPtr model,
			BtCylinderShapeSharedPtr shape,
			BtMotionStateSharedPtr motionState,
			BtRigidBodySharedPtr rigidbody,
			Camera::ICameraSharedPtr camera,
			Input::PlayerMouseSharedPtr mouse,
			GameObjectData::StatusSharedPtr status
		);


		//disallow assign
		Player(const Player &) = delete;
		//disallow copy
		void operator =(const Player &) = delete;

		GameObjectData::StatusSharedPtr mStatus;

		float	mHeight;


		MME::Object::ModelKaiSharedPtr mModel;
		Utils::CharacterSharedPtr mCharacter;

		//Camera::PlayerCamera *mCamera;
		//Camera::Simple *mCamera;
		Camera::ICameraSharedPtr mCamera;

		std::shared_ptr<Input::PlayerMouse> mMouse;

		PlayerUtils::Updater::Parent *mUpdater;

		float						mElapsedTime;

		GUI::Label *mHpBar;
		GUI::Label *mHpBackGroundBar;

		BulletPhysics::OnGroundChecker *mOnGroundChecker;
		Component::RigidBodyComponentSharedPtr mRigidBodyComponent;

		unsigned short	mFilterGroup;
		unsigned short	mFilterMask;
	};


}