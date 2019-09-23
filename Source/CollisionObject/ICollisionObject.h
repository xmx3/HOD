#pragma once
class btPersistentManifold;
class btCollisionObject;

namespace CollisionObject {

	class ICollisionObject {
	public:
		ICollisionObject() {}
		virtual ~ICollisionObject() {}

		virtual bool isMMDObject() const = 0;
		virtual bool enableCollidedMMDObject() const = 0;

		//btCollisionObject‚ªÚG‚µ‚Ä‚¢‚éŠÔAŒÄ‚Î‚ê‘±‚¯‚é
		virtual void onCollisionStay(btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj) = 0;

		//btCollisionObject‚ªÕ“Ë‚µ‚½‚Æ‚«ŒÄ‚Î‚ê‚é
		virtual void onCollisionEnter(btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj) = 0;

		//btCollisionObject‚ª—£‚ê‚½‚Æ‚«ŒÄ‚Î‚ê‚é
		virtual void onCollisionExit(btCollisionObject *me, btCollisionObject *obj) = 0;

	private:
		ICollisionObject(const ICollisionObject &) = delete;
		void operator=(const ICollisionObject &) = delete;
	};

}//

