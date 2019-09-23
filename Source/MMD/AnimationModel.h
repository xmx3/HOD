#ifndef __MMD_ANIMATIONMODEL_H__
#define __MMD_ANIMATIONMODEL_H__
#include<boost/unordered_map.hpp>

struct D3DXMATRIX;


namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}
namespace GameObject{
	class Accessory;
}

namespace MMD {


	class CModel;

	class TemplatePMD;
	typedef std::shared_ptr<TemplatePMD> TemplatePMDSharedPtr;

	class Bone;
	class Animation;

	namespace AnimationState{
		class IAnimationState;
		typedef std::shared_ptr<IAnimationState> IAnimationStateSharedPtr;
		namespace Hook{
			class IHook;
			typedef std::shared_ptr<IHook> IHookSharedPtr;
		}
	}


class AnimationModel{
public:
	AnimationModel();
	AnimationModel( const TemplatePMDSharedPtr &pmd, bool enablePhysics ); 
	virtual ~AnimationModel();	

	void loadPMD( const char *pmdName );
	void loadPMD( const GameLib::FileIO::InFile &inFile );
	void loadPMDFromDB( const char *fileName, bool enablePhysics );

	bool isReady();

	//Animationを返す。失敗したら空のポインタを返す
	std::shared_ptr<Animation> loadVMD( const char *vmdName );
	//indexを返す。失敗したら-1を返す。
	//int loadVMD( const GameLib::FileIO::InFile &inFile );	

	//見つからないならー1を返す
	//int getIndex( const char *vmdName ) const;

	//初期位置をセット(RigidBodyのため).
	//warpの方が名前いい?setInitWorldTransform();reset
	void init( const D3DXMATRIX &world, AnimationState::IAnimationState* anim );
	//初期位置をセット(RigidBodyのため).
	void init( const D3DXMATRIX &world, const std::string & animName );

	//using gamelib
	void draw() const;
	void drawByMME()const;
	void debugDraw() const;
	void update( const D3DXMATRIX &world, float elapsedTime );
	bool isAnimOver() const;
	
	std::shared_ptr<Animation> getCurrentAnimation() const;
	AnimationState::IAnimationState* getCurrentAnimationState();
	void changeAnimation( AnimationState::IAnimationState* state );
	float getFrame() const;

	//const char getPmdName() const;

	Bone* getBone( const char* boneName );
	const std::string& getModelFileName()const;

	void changeAnimation( const std::string& animName );

	std::shared_ptr<GameObject::Accessory> getAccessory( const std::string &name );

	void addHookToAnim( const std::string &toAnimName, const MMD::AnimationState::Hook::IHookSharedPtr &hook );
	void addAnimState( const std::string &animationName, const MMD::AnimationState::IAnimationStateSharedPtr &anim );
	void addAccessory( const std::string &name, const std::shared_ptr<GameObject::Accessory>& accessory  );

	const std::string& getCurrentAnimationName()const;

	//物理世界に追加
	void addToWorld();
	//物理世界から削除
	void removeFromWorld();

private:
	//disallow assingn
	AnimationModel( const AnimationModel& )=delete;
	//disallow copy
	void operator=( const AnimationModel& )=delete;
	
	//アクセサリの位置をBoneの位置に更新する
	void updateAccessories()const;

	CModel *mModel;

	AnimationState::IAnimationState *mState;

	//アニメーション状態はここで持つ必要あるのか？
	//他に適当な場所がないのでとりあえずおく
	typedef boost::unordered_map<std::string, MMD::AnimationState::IAnimationStateSharedPtr> AnimationMap;
	AnimationMap mAnimationMap;
	typedef boost::unordered_map< const std::string, std::shared_ptr<GameObject::Accessory> > AccessoryMap;
	//ここにアクセサリー置くのはよくない?、Acessoryの実装に依存してしまう
	//だがモデルを更新した後アクセサリーを更新したい
	//
	AccessoryMap mAccessoryMap;

};
}
#endif