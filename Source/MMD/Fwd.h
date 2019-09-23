#include<memory>
//様々なクラスの前方宣言
//主にシェアドポインタの前方宣言


namespace MMD {
	class BoneKey;
	typedef std::shared_ptr<BoneKey> BoneKeySharedPtr;

	class HumanModel;
	typedef std::shared_ptr<HumanModel> HumanModelSharedPtr;

	class CModel;

	class TemplatePMD;
	typedef std::shared_ptr<TemplatePMD> TemplatePMDSharedPtr;

	class TemplateVMD;
	typedef std::shared_ptr<TemplateVMD> TemplateVMDSharedPtr;

	class Animation;
	typedef std::shared_ptr<Animation> AnimationSharedPtr;


	class CameraAnimation;
	typedef std::shared_ptr<CameraAnimation> CameraAnimationSharedPtr;

	namespace AnimationState {
		class BaseAnimationState;
		class IAnimationState;
		typedef std::shared_ptr<IAnimationState> IAnimationStateSharedPtr;
		namespace Hook {
			class IHook;
			typedef std::shared_ptr<IHook> IHookSharedPtr;
			class AccessoryHook;
			typedef std::shared_ptr<AccessoryHook> AccessoryHookSharedPtr;
			class SoundHook;
			typedef std::shared_ptr<SoundHook> SoundHookSharedPtr;
		}
	}
}