#include"ICollider.h"

namespace GameObject{

	//RTTI_ROOT_IMPL(GameObject::ICollider);
	RTTI_IMPL(ICollider, IGameObject );

	ICollider::ICollider()
		:mIsMMDObject(false)
	{
	}
}//end namespace GameObject
 