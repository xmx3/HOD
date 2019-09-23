#pragma once
#include<memory>
#include<map>
#include<vector>
#include"GameObjectData/Status.h"
class btCollisionObject;
class btTransform;

namespace MMD{
	class Bone;
	class AnimationModel;
	namespace AnimationState{
		class IAnimationState;
	}
}

namespace GameLib {
	namespace PseudoXml {
		class Document;
		class ConstElement;
	}
}

namespace GameObject{
	class Accessory;
namespace EnemyUtil{

//アニメーションの固定化とxmlロードのため
class Model {
public:
	Model();
	virtual ~Model();
	
	//初期位置をセット(RigidBodyのため).
	//warpの方が名前いい?setInitWorldTransform();reset
	void init( const btTransform &world );
	void draw() const;
	void debugDraw() const;
	void update( const btTransform &world, float elapsedTime );
	bool isAnimOver() const;
	
	float getFrame() const;


	MMD::Bone* getBone( const char* boneName );

	void loadXML(
		const char *fileName,
		btCollisionObject* ignoredObject,//accessoryが親を無視するために必要
		GameObjectData::StatusSharedPtr status//武器が攻撃力を求めるために必要
	);
	void changeStandAnim();
	void changeRunAnim();

	std::shared_ptr<GameObject::Accessory> getAccessory( const char* name );

private:
	//disallow assingn
	Model( const Model& );
	//disallow copy
	void operator=( const Model& );

	MMD::AnimationState::IAnimationState * createAnimationState(
		GameObjectData::StatusSharedPtr status,
		const GameLib::PseudoXml::ConstElement &e );

	MMD::AnimationModel *mModel;

	MMD::AnimationState::IAnimationState *mStandAnim;
	MMD::AnimationState::IAnimationState *mRunAnim;

	typedef std::map< const std::string, std::shared_ptr<GameObject::Accessory> > AccessoryMap;
	AccessoryMap mAccessoryMap;

	float mHeightOffset;
	typedef std::map< const std::string, GameLib::PseudoXml::Document > XmlMap;
	static XmlMap mXmlMap; 

};

}//end namespace EnemyUtil
}//end namespace GameObject