#pragma once
#include"IObject.h"
#include<memory>
#include<string>
struct D3DXMATRIX;

namespace MMD{
	class Bone;

	class AnimationModel;
	namespace AnimationState{
		class IAnimationState;
	}
}


namespace MME{
	namespace Object{

class Model;
typedef std::shared_ptr<Model> ModelSharedPtr;

//MMD::AnimationModelのラッパークラス
class Model : public IObject{
public:
	//make_sharedがprivate　コンストラクタ呼ぶのに必要
	//vc2015からtr1より通常のネームスペースへ移行
	friend class std::_Ref_count_obj<Model>;


	//shared_from_thisはコンストラクタ内で使えないのでこちらでMME::Managerに登録
	static ModelSharedPtr create();

	virtual ~Model();

	virtual void draw()const;

	virtual float getScale()const;

	virtual float getFaceValue(const std::string &faceName )const;

	virtual const D3DXMATRIX & getBoneMatrix( const std::string &boneName )const;

	virtual const std::string& getModelFileName()const;

	void update( const D3DXMATRIX & world, float elapsed );

	bool isReady();

	void loadPMDFromDB( const char *fileName, bool enablePhysics );

	//初期位置をセット(RigidBodyのため).
	//warpの方が名前いい?setInitWorldTransform();reset
	void init( const D3DXMATRIX &world, MMD::AnimationState::IAnimationState* anim );
	
	bool isAnimOver() const;
	
	MMD::AnimationState::IAnimationState* getCurrentAnimationState();
	void changeAnimation( MMD::AnimationState::IAnimationState* state );
	float getFrame() const;

	MMD::Bone* getBone( const char* boneName );

	MMD::AnimationModel *getAnimationModel(){
		return mModel;
	}
private:
	Model();
	//disallow assign
	Model( const Model& )=delete;
	//disallow copy
	void operator=( const Model& )=delete;

private:
	MMD::AnimationModel *mModel;
};

}// end namespace Object
}// end namespace MME

