#pragma once

#include<memory>
#include<map>
#include<vector>
#include"GameObjectData/Status.h"

class btCollisionObject;
class btTransform;

namespace MMD{
	class Bone;

	namespace AnimationState{
		class IAnimationState;
		typedef std::shared_ptr<IAnimationState> IAnimationStateSharedPtr;
		namespace Hook{
			class IHook;
			typedef std::shared_ptr<IHook> IHookSharedPtr;
		}
	}
}

namespace MME{
	namespace Object {
		class Model;
		typedef std::shared_ptr<Model> ModelSharedPtr;
	}
}

namespace GameLib {
	namespace PseudoXml {
		class ConstElement;
	}
}

namespace GameObject{
	class Accessory;
}
namespace MMD{
//アニメーションの固定化(changeStandAnim 等)とxmlロードのため
//changeStateをenum変数を使って実装する案もあったがわざわざenum調べるのだるい
//アクセサリをここに持たせるのがベターな気がした
//アクセサリを持つのがモデルだし、アニメーションに深く関係してくるので
//名前変更　
//class FixedAnimationModelWithAccessories;からHumanModelに

class HumanModel;
typedef std::shared_ptr<HumanModel> HumanModelSharedPtr;

class HumanModel {
public:
	HumanModel();
	HumanModel(
		MME::Object::ModelSharedPtr model,
		float heightOffset,
		MMD::AnimationState::IAnimationStateSharedPtr standAnim,
		MMD::AnimationState::IAnimationStateSharedPtr punchAnim,
		MMD::AnimationState::IAnimationStateSharedPtr runAnim,
		MMD::AnimationState::IAnimationStateSharedPtr stumbleAnim,
		MMD::AnimationState::IAnimationStateSharedPtr lieAnim,
		MMD::AnimationState::IAnimationStateSharedPtr swingAnim0,
		MMD::AnimationState::IAnimationStateSharedPtr swingAnim1,
		MMD::AnimationState::IAnimationStateSharedPtr swingAnim2,
		MMD::AnimationState::IAnimationStateSharedPtr swingAnim3
	);

	virtual ~HumanModel();
	
	bool isReady();

	//初期位置をセット(RigidBodyのため).
	//warpの方が名前いい?setInitWorldTransform();reset
	void init( const btTransform &world );
	
	//gameLibを使ったdraw
	void draw() const;
	//mmeを使う場合、drawする前に呼べ
	//アクセサリの位置をBoneの位置に更新する
	void preDrawMME()const;

	void update( const btTransform &world, float elapsedTime );
	bool isAnimOver() const;
	
	float getFrame() const;

	Bone* getBone( const char* boneName );

	void loadXML(
		const char *filename,
		btCollisionObject* ignoredObject,//accessoryが親を無視するために必要
		GameObjectData::StatusSharedPtr status//武器が攻撃力を求めるために必要
	);


	// enum AnimationType{
	//	Run=0,	
	//	Punch,......
	//};
	// void changeAnim( AnimationType );
	// void changeAnim( const std::string & );
	void changeStandAnim();
	void changeRunAnim();
	void changePunchAnim();
	void changeStumbleAnim();
	void changeLieAnim();
	void changeSwingAnim();

	std::shared_ptr<GameObject::Accessory> getAccessory( const char* name );

	int getNumSwingAnims()const{
		return mSwingAnims.size();
	}

	void addHookToStandAnim( MMD::AnimationState::Hook::IHookSharedPtr hook );
	void addHookToRunAnim( MMD::AnimationState::Hook::IHookSharedPtr hook );
	void addHookToPunchAnim( MMD::AnimationState::Hook::IHookSharedPtr hook );
	void addHookToStumbleAnim( MMD::AnimationState::Hook::IHookSharedPtr hook );
	void addHookToLieAnim( MMD::AnimationState::Hook::IHookSharedPtr hook );
	void addHookToSwingAnim( int index, MMD::AnimationState::Hook::IHookSharedPtr hook );

private:
	//disallow assingn
	HumanModel( const HumanModel& );
	//disallow copy
	void operator=( const HumanModel& );

	MMD::AnimationState::IAnimationStateSharedPtr createAnimationState(
		GameObjectData::StatusSharedPtr status,
		const GameLib::PseudoXml::ConstElement &e );

	MME::Object::ModelSharedPtr mModel;

	MMD::AnimationState::IAnimationStateSharedPtr mStandAnim;
	MMD::AnimationState::IAnimationStateSharedPtr mPunchAnim;
	MMD::AnimationState::IAnimationStateSharedPtr mRunAnim;
	MMD::AnimationState::IAnimationStateSharedPtr mStumbleAnim;
	MMD::AnimationState::IAnimationStateSharedPtr mLieAnim;
	std::vector< MMD::AnimationState::IAnimationStateSharedPtr > mSwingAnims;

	//std::map< std::string, MMD::AnimationState::IAnimationState* >

	typedef std::map< const std::string, std::shared_ptr<GameObject::Accessory> > AccessoryMap;
	AccessoryMap mAccessoryMap;

	float mHeightOffset;

};

}//end namespace MMD
