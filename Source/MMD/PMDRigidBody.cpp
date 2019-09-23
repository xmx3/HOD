#include <memory.h>
#include "PMDRigidBody.h"
#include "BulletPhysics/Manager.h"
#include <helper/MyOutputDebugString.h>
#include <tchar.h>
#include <btBulletCollisionCommon.h>
#include "Component/RigidBodyComponent.h"




namespace{
	const int kFollowUpBone=0; 
}

namespace MMD {
	RTTI_IMPL(PMDRigidBody, GameObject::BaseObject);

	class PMDRigidBody::CanCollideCallback : public Component::ICanCollideCallback {
	public:
		CanCollideCallback(
			unsigned short filterGroup,
			unsigned short filterMask)
			:mCollisionFilterGroup(filterGroup),
			mCollisionFilterMask(filterMask)
		{}
		virtual ~CanCollideCallback() = default;

		virtual bool needCollision(const btCollisionObject *obj) const override {
			auto c = static_cast<Component::RigidBodyComponent*>(obj->getUserPointer());
			assert(c);
			if (c) {
				GameObject::BaseObject *b = c->getOwner();
				auto pmd = dynamic_cast<PMDRigidBody*>(b);
				assert(pmd);

				return
					pmd &&
					((mCollisionFilterGroup & (pmd->getFilterMask())) != 0) &&
					((pmd->getFilterGroup() & mCollisionFilterMask) != 0);
			}
			return false;
		}

		unsigned short mCollisionFilterGroup;
		unsigned short mCollisionFilterMask;
	};

	// Kinematic用モーションステート
	class PMDRigidBody::btKinematicMotionState : public btMotionState
	{
	public:
		//btTransform bttrGraphicsWorldTrans_;
		btTransform	mBoneOffsetTransform;
		btTransform mStartWorldTransform;
		Bone	*mBone;

		btKinematicMotionState(const btTransform& startTrans, const btTransform& boneOffset, Bone *pBone)
			: mBoneOffsetTransform(boneOffset), mStartWorldTransform(startTrans), mBone(pBone)
		{}

		virtual ~btKinematicMotionState() {}

		///synchronizes world transform from user to physics
		virtual void getWorldTransform(btTransform& centerOfMassWorldTrans) const
		{
			btTransform		bttrBoneTransform;

			bttrBoneTransform = toBtTransform(mBone->getSkinningMatrix());
			//btVector3 v = bttrBoneTransform.getOrigin();
			//v += toBtVector3(mBone->initPos_);
			//bttrBoneTransform.setOrigin(v);

			centerOfMassWorldTrans = bttrBoneTransform * mStartWorldTransform;
		}

		///synchronizes world transform from physics to user
		///Bullet only calls the update of worldtransform for active objects
		virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans)
		{
			//mBone->skinningMatrix_ = toDXMatrix( centerOfMassWorldTrans );
			//bttrGraphicsWorldTrans_ = centerOfMassWorldTrans;
		}
	};


	PMDRigidBody::PMDRigidBody()
		:mRigidBodyComponent(nullptr),
		mCanCollideCallback(nullptr),
		mBone(NULL),
		mCollisionFilterGroup(0),
		mCollisionFilterMask(0)
	{

	}


	PMDRigidBody::~PMDRigidBody()
	{
		release();
	}

	bool PMDRigidBody::initialize(const PMD_RigidBody *pPMDRigidBody, Bone *pBone)
	{
		assert(
			!mRigidBodyComponent &&
			!mCanCollideCallback );

		if (mRigidBodyComponent ||
			mCanCollideCallback )
		{
			release();
		}


		BtCollisionShapeSharedPtr shape;
		BtMotionStateSharedPtr motionState;
		BtRigidBodySharedPtr rigidBody;


		// シェイプの作成
		switch (pPMDRigidBody->cbShapeType)
		{
		case 0:	// 球
			shape.reset( new btSphereShape(pPMDRigidBody->fWidth) );
			break;

		case 1:	// 箱
			shape.reset( new btBoxShape(btVector3(pPMDRigidBody->fWidth, pPMDRigidBody->fHeight, pPMDRigidBody->fDepth)) );
			break;

		case 2:	// カプセル
			shape.reset( new btCapsuleShape(pPMDRigidBody->fWidth, pPMDRigidBody->fHeight) );
			break;
		}

		// 質量と慣性テンソルの設定
		btScalar	btsMass(0.0f);
		btVector3	btv3LocalInertia(0.0f, 0.0f, 0.0f);

		// ボーン追従でない場合は質量を設定
		if (pPMDRigidBody->cbRigidBodyType != 0)	btsMass = pPMDRigidBody->fMass;

		// 慣性テンソルの計算
		if (btsMass != 0.0f)	shape->calculateLocalInertia(btsMass, btv3LocalInertia);

		// ボーンの位置取得
		D3DXVECTOR3 vec3BonePos;
		vec3BonePos = pBone->initPos_;

		// ボーンオフセット用トランスフォーム作成
		btMatrix3x3	btmRotationMat;
		btmRotationMat.setEulerZYX(pPMDRigidBody->vec3Rotation[0], pPMDRigidBody->vec3Rotation[1], pPMDRigidBody->vec3Rotation[2]);

		btTransform		bttrBoneOffset;

		bttrBoneOffset.setIdentity();
		bttrBoneOffset.setOrigin(btVector3(pPMDRigidBody->vec3Position[0], pPMDRigidBody->vec3Position[1], pPMDRigidBody->vec3Position[2]));
		bttrBoneOffset.setBasis(btmRotationMat);

		// 剛体の初期トランスフォーム作成
		btTransform bttrStartTransform;
		bttrStartTransform.setIdentity();
		bttrStartTransform.setOrigin(btVector3(vec3BonePos.x, vec3BonePos.y, vec3BonePos.z));
		bttrStartTransform = bttrStartTransform * bttrBoneOffset;


		//タイプ(0:Bone追従、1:物理演算、2:物理演算(Bone位置合せ)) 
		mBoneType = pPMDRigidBody->cbRigidBodyType;
		switch (pPMDRigidBody->cbRigidBodyType)
		{
		case 0:
			motionState.reset( new btKinematicMotionState(bttrStartTransform, bttrBoneOffset, pBone) );
			break;
		case 1:
			motionState.reset( new btDefaultMotionState(bttrStartTransform) );
			break;
		case 2:
			motionState.reset( new btDefaultMotionState(bttrStartTransform) );
			break;
			//case 2 :pbtMotionState = new btKinematicMotionState( bttrTransform, bttrBoneOffset, pBone );	break;
		default: assert(false && "failed PMDRigidBody::initialize."); break;
		}

		// 剛体のパラメータの設定
		btRigidBody::btRigidBodyConstructionInfo	btRbInfo(btsMass, motionState.get(), shape.get(), btv3LocalInertia);
		btRbInfo.m_linearDamping = pPMDRigidBody->fLinearDamping;	// 移動減
		btRbInfo.m_angularDamping = pPMDRigidBody->fAngularDamping;	// 回転減
		btRbInfo.m_restitution = pPMDRigidBody->fRestitution;	// 反発力
		btRbInfo.m_friction = pPMDRigidBody->fFriction;		// 摩擦力
		btRbInfo.m_additionalDamping = true;

		// 剛体の作成
		rigidBody.reset( new btRigidBody(btRbInfo) );
		mRigidBodyComponent = new Component::RigidBodyComponent(
			this,
			shape,
			motionState,
			rigidBody );


		// Kinematic設定
		if (pPMDRigidBody->cbRigidBodyType == kFollowUpBone)
		{
			mRigidBodyComponent->setIsKinematic(true);
		}
		else {
			//TRACE1( "%s isn't Kinematic.\n", pBone->getName() );
		}

		//pRigidBody_->setSleepingThresholds( 0.0f, 0.0f );v

		//if(btsMass==0){ TRACE1( "%s is static.\n", pBone->getName() ); }

		// 剛体をシミュレーションワールドに追加
		BulletPhysics::Manager *mngr = BulletPhysics::Manager::instance();

		
		//MMDで独自のフィルタリングのため
		mCollisionFilterGroup = 0x0001 << (pPMDRigidBody->cbColGroupIndex);
		mCollisionFilterMask = pPMDRigidBody->unColGroupMask;

		mCanCollideCallback = new CanCollideCallback(mCollisionFilterGroup, mCollisionFilterMask);
		mRigidBodyComponent->setCanCollideCallback(mCanCollideCallback);

		mBoneOffsetTransform = bttrBoneOffset;
		mInvStartTransform = bttrStartTransform.inverse();

		mBone = pBone;


		if (strncmp(pBone->getName(), "センター", 20) == 0) {
			m_bNoCopyToBone = true;
		}
		else {
			m_bNoCopyToBone = false;
		}

		return true;
	}



	// ボーンの姿勢を剛体の姿勢と一致させる(そのフレームのシミュレーション終了後に呼ぶ)
	void PMDRigidBody::updateBoneTransform(void)
	{
		if (mBoneType != kFollowUpBone && !m_bNoCopyToBone)
		{
			btTransform	bttrBoneTransform = mRigidBodyComponent->getRigidBody()->getCenterOfMassTransform() * mInvStartTransform;
			mBone->skinningMatrix_ = toDxMatrix(bttrBoneTransform);
		}
	}

	void PMDRigidBody::release(void)
	{
		if (mRigidBodyComponent)
		{
			removeFromWorld();

		}
		SAFE_DELETE(mRigidBodyComponent);
		SAFE_DELETE(mCanCollideCallback);
	}

	void PMDRigidBody::debugDraw() {
		mBone->debug_draw();
	}
	//剛体をboneの姿勢に一致させる
	void PMDRigidBody::fitBone(void)
	{
		btTransform bttrBoneTransform = toBtTransform(mBone->getSkinningMatrix());
		btTransform bttrStratTransform = mBoneOffsetTransform;
		btVector3 v = mBoneOffsetTransform.getOrigin();
		bttrStratTransform.setOrigin(v + toBtVector3(mBone->initPos_));
		mInvStartTransform = bttrStratTransform.inverse();

		btTransform bttrTransform = bttrBoneTransform*bttrStratTransform;
		auto rb = mRigidBodyComponent->getRigidBody();

		rb->setCenterOfMassTransform(bttrTransform);

		rb->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
		rb->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
		rb->setInterpolationLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
		rb->setInterpolationAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
		rb->setInterpolationWorldTransform(rb->getCenterOfMassTransform());
		rb->clearForces();

		for (int i = rb->getNumConstraintRefs() - 1; i > -1; --i) {
			btGeneric6DofSpringConstraint *pC = dynamic_cast<btGeneric6DofSpringConstraint*>(rb->getConstraintRef(i));
			assert(pC);
			if (pC) {
				pC->calculateTransforms();
			}
		}

	}

	void PMDRigidBody::addToWorld() {
		assert(mRigidBodyComponent);

		if (mRigidBodyComponent) {
			mRigidBodyComponent->addToWorld(
				BulletPhysics::MMDObjectFilter,
				BulletPhysics::MMDObjectFilter);
		}
	}

	bool PMDRigidBody::removeFromWorld() {
		assert(mRigidBodyComponent);
		if (mRigidBodyComponent) {
			return mRigidBodyComponent->removeFromWorld();
		}
		return false;
	}

	void PMDRigidBody::setVelocityZero() {
		assert(mRigidBodyComponent);
		auto rb = mRigidBodyComponent->getRigidBody();

		rb->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
		rb->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));

		rb->clearForces();

		for (int i = rb->getNumConstraintRefs() - 1; i > -1; --i) {
			btGeneric6DofSpringConstraint *pC = dynamic_cast<btGeneric6DofSpringConstraint*>(rb->getConstraintRef(i));
			assert(pC);
			if (pC) {
				pC->calculateTransforms();
			}
		}
	}

	btRigidBody* PMDRigidBody::getRigidBody() {
		return mRigidBodyComponent->getRigidBody().get();
	}


	int PMDRigidBody::calculateDamage()
	{
		assert(false && 
			"ここをとおることはないはず、設計的に呼ぶはずない\
			mmdオブジェクトは他のものに触れられないので\
			そういう風に設計しなおしたのならここも変える必要がある");
		return 0;
	}

	bool PMDRigidBody::canDamage()
	{
		assert(false &&
			"ここをとおることはないはず、設計的に呼ぶはずない\
			mmdオブジェクトは他のものに触れられないので\
			そういう風に設計しなおしたのならここも変える必要がある");
		return false;
	}

	const GameObjectData::WeaponStatus * PMDRigidBody::getWeaponStatus()
	{
		assert(false &&
			"ここをとおることはないはず、設計的に呼ぶはずない\
			mmdオブジェクトは他のものに触れられないので\
			そういう風に設計しなおしたのならここも変える必要がある");
		return nullptr;
	}



}