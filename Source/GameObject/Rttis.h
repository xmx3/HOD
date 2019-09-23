#ifndef __GAMEOBJECT_RTTIS_H__
#define __GAMEOBJECT_RTTIS_H__

//ˆË‘¶ŠÖŒW‚ðŒ¸‚ç‚·‚½‚ß‚Ìƒwƒbƒ_
class RTTI;

namespace GameObject{

	namespace Rttis {
		const RTTI & Stage();
		const RTTI & Accessory();
		const RTTI & CharacterControllerGhostObject();
		const RTTI & CharacterControllerRigidBody();
		const RTTI & Enemy();
		const RTTI & Bullet();
		const RTTI & BoneCollisonObject();
		const RTTI & ICollider();
	};

}

#endif