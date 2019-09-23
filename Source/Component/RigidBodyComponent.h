#pragma once
#include"BaseComponent.h"
#include<memory>
#include<vector>
#include"helper/Delegate.h"


class btRigidBody;
class btCollisionObject;
class btCollisionShape;
class btTransform;
class btVector3;
class btMotionState;
class btPersistentManifold;


class btRigidBody;
typedef std::shared_ptr<btRigidBody> BtRigidBodySharedPtr;
class btCollisionShape;
typedef std::shared_ptr<btCollisionShape> BtCollisionShapeSharedPtr;
typedef std::shared_ptr<btMotionState> BtMotionStateSharedPtr;

namespace MMD {
	class PMDRigidBody;
}


namespace GameObject {
	class BaseObject;
	typedef std::weak_ptr<BaseObject> BaseObjectObjectWeakPtr;
}


namespace Component {
	class RigidBodyComponent;
	typedef std::shared_ptr<RigidBodyComponent> RigidBodyComponentSharedPtr;


	//namespaceここでいいのか？
	class ICanCollideCallback {
	public:
		ICanCollideCallback() = default;
		virtual ~ICanCollideCallback() = default;

		virtual bool needCollision(const btCollisionObject*) const = 0;
	};

	//
	class CanCollideExceptIgnoredObjectsCallback : public ICanCollideCallback {
	public:
		CanCollideExceptIgnoredObjectsCallback()= default;
		virtual ~CanCollideExceptIgnoredObjectsCallback() = default;

		virtual bool needCollision(const btCollisionObject *obj) const  {
			for (const btCollisionObject *ignoreObj : mIgnoredObjects) {
				if (ignoreObj == obj) {
					return false;
				}
			}
			return true;	
		}

		//add ignored list.
		void addIgnoredObject(const btCollisionObject *obj) {
			mIgnoredObjects.push_back(obj);
		}

		void clearIgnoredObjects() {
			mIgnoredObjects.clear();
		}

		//sorted_vectorにしたほうが探索するの早いだろうけど、
		//そこまで数がおおくないので線形探索でいいだろう
		std::vector<const btCollisionObject*> mIgnoredObjects;

	};

	//下の3つのコールバック
	//親クラスのshared_ptr持たせて循環参照にしないように

	class IOnCollisionEnterCallback {
	public:
		IOnCollisionEnterCallback() {}
		virtual ~IOnCollisionEnterCallback() {}
		virtual void operator()(btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj)=0;
	};

	class IOnCollisionStayCallback {
	public:
		IOnCollisionStayCallback() {}
		virtual ~IOnCollisionStayCallback() {}
		virtual void operator()(btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj) = 0;
	};

	class IOnCollisionExitCallback {
	public:
		IOnCollisionExitCallback() {}
		virtual ~IOnCollisionExitCallback() {}
		virtual void operator()(btCollisionObject *me, btCollisionObject *obj) = 0;
	};

	class RigidBodyComponent : public BaseComponent {
	public:
		static RigidBodyComponentSharedPtr create(
			GameObject::BaseObject* owner,
			BtCollisionShapeSharedPtr shape,
			BtMotionStateSharedPtr motionState,
			BtRigidBodySharedPtr rigidbody);

		RigidBodyComponent(
			GameObject::BaseObject* owner,
			BtCollisionShapeSharedPtr shape,
			BtMotionStateSharedPtr motionState,
			BtRigidBodySharedPtr rigidbody
		);

		virtual ~RigidBodyComponent();

		//mCanCollideCallbackが実装されてない場合trueを返す
		virtual bool canCollide(const btCollisionObject *obj) const
		{
			if (mCanCollideCallback) {
				return mCanCollideCallback->needCollision(obj);
			}
			else {
				return true;
			}
		}

		btCollisionObject* getBtCollisionObject();

		const btCollisionObject* getConstBtCollisionObject()const;

		const btTransform & getWorldTransform() const;

		btTransform & getWorldTransform();

		BtMotionStateSharedPtr getMotionState() {
			return mMotionState;
		}

		void setMotionState(const BtMotionStateSharedPtr motionstate);

		BtRigidBodySharedPtr getRigidBody() {
			return mRigidBody;
		}

		BtCollisionShapeSharedPtr getShape() {
			return mShape;
		}

		bool isInWorld()const;

		//追加できた場合trueを返す
		bool addToWorld(unsigned short filterGroup, unsigned short filterMask);
		//取り除けた場合trueを返す
		virtual bool removeFromWorld();

		void setCanCollideCallback(ICanCollideCallback *callback) {
			mCanCollideCallback = callback;
		}

		void setIsKinematic(bool isKinematic);

		//btCollisionObjectが接触している間、呼ばれ続ける
		virtual void onCollisionStay(btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj);

		//btCollisionObjectが衝突したとき呼ばれる
		virtual void onCollisionEnter(btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj);

		//btCollisionObjectが離れたとき呼ばれる
		virtual void onCollisionExit(btCollisionObject *me, btCollisionObject *obj);

		//void setOnCollisonEnterCallback(IOnCollisionEnterCallback* callback);
		//void setOnCollisonStayCallback(IOnCollisionStayCallback* callback);
		//void setOnCollisonExitCallback(IOnCollisionExitCallback* callback);

		DECLARE_MULTICAST_DELEGATE_PARAM_3(TCollisionEnterCallback, void, btPersistentManifold*, btCollisionObject*, btCollisionObject*);
		DECLARE_MULTICAST_DELEGATE_PARAM_3(TCollisionStayCallback, void, btPersistentManifold*, btCollisionObject*, btCollisionObject*);
		DECLARE_MULTICAST_DELEGATE_PARAM_2(TCollisionExitCallback, void, btCollisionObject*, btCollisionObject*);

		TCollisionEnterCallback& getOnEnterCallback() {
			return mOnEnterCallback;
		}
		TCollisionStayCallback& getOnStayCallback() {
			return mOnStayCallback;
		}
		TCollisionExitCallback& getOnExitCallback() {
			return mOnExitCallback;
		}




	protected:
		BtCollisionShapeSharedPtr mShape;
		BtMotionStateSharedPtr mMotionState;
		BtRigidBodySharedPtr mRigidBody;

		bool mIsInWorld;

		ICanCollideCallback* mCanCollideCallback;

		TCollisionEnterCallback mOnEnterCallback;
		TCollisionStayCallback mOnStayCallback;
		TCollisionExitCallback mOnExitCallback;

	};
}

