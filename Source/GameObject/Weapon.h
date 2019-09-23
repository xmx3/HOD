#pragma once
#include<memory>
#include<string>
#include<vector>
namespace MMD { namespace AnimationState {
	class IAnimationState;
	typedef std::shared_ptr<IAnimationState> IAnimationStateSharedPtr;
	//namespace Hook {
	//	class AccessoryHook;
	//	typedef std::shared_ptr<AccessoryHook> AccessoryHookSharedPtr;
	//}
}} //MMD::AnimationState


namespace GameObject{
	class Accessory;
	typedef std::shared_ptr<Accessory> AccessorySharedPtr;

class Weapon{
public:
	Weapon();
	~Weapon();

	void addAccessory(const AccessorySharedPtr &accessory );
	void addAnimation(const MMD::AnimationState::IAnimationStateSharedPtr &animation );

private:	
	std::string mName;
	
	std::vector<AccessorySharedPtr> mAccessories;
	std::vector<MMD::AnimationState::IAnimationStateSharedPtr> mAnimations;

};
}//end namespace GameObject