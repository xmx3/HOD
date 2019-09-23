#pragma once
#include"IObject.h"
#include<memory>
#include<string>
struct D3DXMATRIX;

namespace GameObject{
	class Accessory;
	typedef std::shared_ptr<Accessory> AccessorySharedPtr;
}

namespace MMD {
	class AnimationModel;
	class TemplatePMD;
	typedef std::shared_ptr<TemplatePMD> TemplatePMDSharedPtr;

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
	namespace Object{

class ModelKai;
typedef std::shared_ptr<ModelKai> ModelKaiSharedPtr;

//MMD::AnimationModelのラッパークラス
class ModelKai : public IObject{
public:
	//shared_from_thisはコンストラクタ内で使えないのでこちらでMME::Managerに登録
	static ModelKaiSharedPtr create( const MMD::TemplatePMDSharedPtr &pmd, bool enablePhysics, float heightOffset );

	virtual ~ModelKai();

	virtual void draw()const;

	//vector3ではなくてfloatなのはMMEとの互換性を取るため
	virtual float getScale()const;
	//void setScale( float scale );

	virtual float getFaceValue(const std::string &faceName )const;

	virtual const D3DXMATRIX & getBoneMatrix( const std::string &boneName )const;

	virtual const std::string& getModelFileName()const;

	void update( const D3DXMATRIX & world, float elapsed );

	bool isReady();

	//void loadPMDFromDB( const char *fileName, bool enablePhysics );

	//初期位置をセット(RigidBodyのため).
	void init( const D3DXMATRIX &world, const std::string &animName );
	
	bool isAnimOver() const;
	
	void changeAnimation( const std::string &animName );
	//void addHookToAnim( const std::string &toAnimName, const MMD::AnimationState::Hook::IHookSharedPtr &hook );
	void addAnimState( const std::string &animationName, const MMD::AnimationState::IAnimationStateSharedPtr &anim );
	
	GameObject::AccessorySharedPtr getAccessory( const std::string &name );
	void addAccessory( const std::string &name, const GameObject::AccessorySharedPtr &accessory ); 	

	float getFrame() const;

	MMD::Bone* getBone( const char* boneName );
	MMD::AnimationModel* getAnimationModel(){
		return mModel;
	}

	//物理世界に追加
	void addToWorld();
	//物理世界から削除
	void removeFromWorld();

private:
	ModelKai( const MMD::TemplatePMDSharedPtr &pmd, bool enablePhysics, float heightOffset );
	//disallow assign
	ModelKai( const ModelKai& )=delete;
	//disallow copy
	void operator=( const ModelKai& )=delete;

private:
	MMD::AnimationModel *mModel;
	float mHeightOffset;
};

}// end namespace Object
}// end namespace MME

