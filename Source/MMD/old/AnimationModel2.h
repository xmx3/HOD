#pragma once

#include<memory>
#include<map>
#include<vector>
#include"GameObjectData/Status.h"
#include"AnimationModel.h"
#include"MME/Object/IObject.h"
#include<boost/unordered_map.hpp>

class btCollisionObject;
class btTransform;
class CBone;

namespace MMD{
	namespace AnimationState{
		class IAnimationState;
		typedef std::shared_ptr<IAnimationState> IAnimationStateSharedPtr;
		namespace Hook{
			class IHook;
			typedef std::shared_ptr<IHook> IHookSharedPtr;
		}
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
//animationModelの改良バージョン
class AnimationModel2 : public AnimationModel {
public:
	AnimationModel2();
	virtual ~AnimationModel2();
	
	bool isReady();

	//gameLibを使ったdraw
	void drawUsingGameLib() const;
	
	//mmeを使う場合、drawする前に呼べ
	//アクセサリの位置をBoneの位置に更新する
	void preDrawMME()const;

	void update( const btTransform &world, float elapsedTime );

	void loadXML(
		const char *filename,
		btCollisionObject* ignoredObject,//accessoryが親を無視するために必要
		GameObjectData::StatusSharedPtr status//武器が攻撃力を求めるために必要
	);

	void changeAnimation( const std::string& animName );

	std::shared_ptr<GameObject::Accessory> getAccessory( const std::string &name );

	void addHookToAnim( const std::string &toAnimName, MMD::AnimationState::Hook::IHookSharedPtr hook );


protected:
	//隠したいのでprotected
	//using AnimationModel::update;
	//using AnimationModel::isAnimOver;
	//using AnimationModel::getFrame;
	//using AnimationModel::getBone;
	//using AnimationModel::loadPMDFromDB;
	//using AnimationModel::getCurrentAnimationIndex;

private:
	//disallow assingn
	AnimationModel2( const AnimationModel2& );
	//disallow copy
	void operator=( const AnimationModel2& );

	MMD::AnimationState::IAnimationStateSharedPtr createAnimationState(
		GameObjectData::StatusSharedPtr status,
		const GameLib::PseudoXml::ConstElement &e );
	typedef boost::unordered_map<std::string, MMD::AnimationState::IAnimationStateSharedPtr> AnimationMap;
	AnimationMap mAnimationMap;
	typedef boost::unordered_map< const std::string, std::shared_ptr<GameObject::Accessory> > AccessoryMap;
	AccessoryMap mAccessoryMap;
};

//MMEObject対応バージョン
class AnimationModel3 : private AnimationModel2, public MME::Object::IObject {
public:
	~AnimationModel3(){
		//これいらんかsetCanRemove(true);
	}
	
	//初期位置をセット(RigidBodyのため).
	//warpの方が名前いい?setInitWorldTransform();reset
	void init( const btTransform &world );
	float mHeightOffset;
};

}//end namespace MMD
