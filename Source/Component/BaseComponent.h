#pragma once
#include<memory>


namespace GameObject {
	class BaseObject;
}

namespace Component {
	class BaseComponent;
	typedef std::shared_ptr<BaseComponent> BaseComponentSharedPtr;
	typedef std::weak_ptr<BaseComponent> BaseComponentWeakPtr;

	//class BaseComponent : public std::enable_shared_from_this<BaseComponent> {
	class BaseComponent {
	public:
		virtual ~BaseComponent() = default;


		//getRTTI();//いらないかも
		//この関数はGameObject側か

		//BaseComponent* nextSibling();
		//いらないでしょここで複数コンポーネントを組み合わせ再利用のはGameObjectだし
		//ぐるぐる回すのをここで実装する必要はない

		GameObject::BaseObject* getOwner() {
			return mOwner;
		}
	//protected:
		BaseComponent()
			:mOwner(nullptr)
		{}
		GameObject::BaseObject* mOwner;


	};
}