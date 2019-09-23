#pragma once
#include<memory>
#include<string>

namespace MME {
	namespace Object {
		class ModelKai;
		typedef std::shared_ptr<ModelKai> ModelKaiSharedPtr;
	}
}

namespace MMD {
	namespace AnimationState {
	}
}


namespace XmlLoader {
	namespace MMD {
		namespace AnimationState {

			class IAnimationState;
			typedef std::shared_ptr<IAnimationState> IAnimationStateSharedPtr;
		}
	}
}

namespace Lua {

//あたり判定なしモデル
//ルアで姿勢を制御し表示させたいときに使う
//場所と回転(姿勢)をアニメーションさせたい場合使うことを想定
//移動なしアニメーションを移動させるときに使用
//ゲームでは移動量をプログラム側からコントロールしたいため移動を伴わないアニメーションを使うことがある
//それをカットシーンで再利用、するためのクラス
//名前候補
//ModelRootController, TimeLine RootTransformController
//self.miku = Lua.ModelRootTransformTimeLineControllerModel(
//ModelTimeLineControllerに決定
//理由 コントロールしたいものがrootTransformとアニメーションだから
//
//というか入れる場所(名前空間)GameObject::Utilsあたりのほうがいいのでは


class ModelTimeLineController {
public:
	ModelTimeLineController(const MME::Object::ModelKaiSharedPtr &model);
	~ModelTimeLineController();

	void insert(
		float time,
		float x, float y, float z,
		float degreeX, float degreeY, float degreeZ,
		const std::string &animName );

	void update(float elapsedTime);

	//初期位置をセット(RigidBodyのため).
	void init();

	bool isAnimOver() const;

	MME::Object::ModelKaiSharedPtr getModel();

private:
	class Impl;
	Impl *mImpl;
};

}//end namespaceLua