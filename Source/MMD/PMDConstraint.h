//*********************************
// PMDコンストレイント(ジョイント)
//*********************************

#ifndef		_PMDCONSTRAINT_H_
#define		_PMDCONSTRAINT_H_

#include "Pmd.h"
#include "BulletPhysics/Manager.h"
#include <btBulletDynamicsCommon.h>

namespace MMD {

	class PMDRigidBody;

	//rigidBodyを参照しているのでそれを開放する前に開放すること。バグります
	//PMDRigidBodyに持たすという設計のほうが間違いがないか。
	class PMDConstraint
	{
	public:
		PMDConstraint(void);
		~PMDConstraint(void);

		bool initialize(const PMD_Constraint *pPMDConstraint, PMDRigidBody *pRigidBodyA, PMDRigidBody *pRigidBodyB);

		void release(void);

		void setEnable(bool enabled) {
			pConstraint_->setEnabled(enabled);
		}
		void setEquilibriumPoint() {
			pConstraint_->setEquilibriumPoint();
		}
		void enableSpring(bool enabled) {
			for (int i = 0; i < 6; ++i) {
				pConstraint_->enableSpring(i, enabled);
			}
		}
		void enableFeedback(bool enabled) {
			pConstraint_->enableFeedback(enabled);
		}

		void draw() {
			BulletPhysics::Manager::instance()->drawConstraint(pConstraint_);
		}

		void calcAnchorPos() {
			pConstraint_->calcAnchorPos();
		}

		void calculateTransforms() {
			pConstraint_->calculateTransforms();
		}

		void addToWorld();
		void removeFromWorld();

		void addToCutScene();
		void removeFromCutScene();


	private:
		btGeneric6DofSpringConstraint	*pConstraint_;
		//btGeneric6DofConstraint
		bool mIsInWorld;
		bool mIsInCutScene;
	};
}
#endif	// _PMDCONSTRAINT_H_
