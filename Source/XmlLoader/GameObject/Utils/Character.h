#pragma once
#include<string>
#include<memory>
#include<boost/serialization/serialization.hpp>

namespace GameLib {
	namespace FileIO {
		class InFile;
	}
}

namespace GameObject {
	namespace Utils {
		class Character;
		typedef std::shared_ptr<Character> CharacterSharedPtr;
	}
}

namespace XmlLoader{
	namespace MME {
		namespace Object {
			class ModelKai;
		}
	}

	class Shape;

namespace GameObject {
	namespace Utils {
		//各キャラに対応した様々な設定を保持するクラス
		//人間でない場合はとか、ほかに追加パラメータ足したい場合もありそう
		class Character {
		private:
			typedef ::GameObject::Utils::CharacterSharedPtr InstancedCharacterSharedPtr;
		public:
			Character();
			~Character();

			InstancedCharacterSharedPtr instance();

			void loadStart(const std::string  &filenam);

			bool isReady();

		private:
			//disallow
			Character(const Character &) = delete;
			//disallow
			void operator=(const Character &) = delete;

			friend boost::serialization::access;
			//基底クラスのselialize, save, load関数を直接呼び出さないこと！！
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version);


			GameLib::FileIO::InFile *mFile;

			std::string mName;
			float mHeight;
			float mMass;
			Shape *mShape;
			MME::Object::ModelKai *mModel;

		};

}}}//end XmlLoader::GameObject::Utils