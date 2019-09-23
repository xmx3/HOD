#pragma once
#include<string>
#include<memory>


class btCollisionShape;
typedef std::shared_ptr<btCollisionShape> BtCollisionShapeSharedPtr;

namespace MME {
	namespace Object {
		class ModelKai;
		typedef std::shared_ptr<ModelKai> ModelKaiSharedPtr;
	}
}

namespace GameObject {namespace Utils {
	//各キャラに対応した様々な設定を保持するクラス
	//モデルとあたり判定系の情報をまとめたかった
	//人間でない場合はとか、ほかに追加パラメータ足したい場合もありそう
	//ModelTimeLineControllerとPlayer(Enemy、GameObject）の共通部分を保持するためのクラス
	//GameObjectを継承してないからUtilsネームスペースに入れたけど

	//一番初めの考えではモデルとあたり判定はペアで持つべきと思っていたけど
	//別々のほうがいいかもね
	//ミクというキャラクターは同じあたり判定を持ち重さや形が一緒みたいな考え方があったからだね
	//イベントも考慮してプログラムの再利用をしやすいように考えてだと思う
	//コンポーネントとして考え始めた場合それらは別々にしてGameObjectの中で組み合わせるべきではないかと感じている

	class Character {
	public:
		Character(
			const std::string &name,
			float height,
			float mass,
			BtCollisionShapeSharedPtr shape,
			MME::Object::ModelKaiSharedPtr model
		);
		~Character();
		
		const std::string& getName()const {
			return mName;
		}

		float getHeight() const {
			return mHeight;
		}


		BtCollisionShapeSharedPtr getShape() const {
			return mShape;
		}

		MME::Object::ModelKaiSharedPtr getModel() const {
			return mModel;
		}
		
		float getMass() const {
			return mMass;
		}

	private:
		Character(const Character &) = delete;
		void operator=(const Character &) = delete;

		std::string mName;
		float mHeight;
		float mMass;
		BtCollisionShapeSharedPtr mShape;
		MME::Object::ModelKaiSharedPtr mModel;
	
	};

} }//end GameObject::Utils