#pragma once

#include<string>
#include<memory>
#include<boost/serialization/serialization.hpp>
#include<boost/serialization/split_member.hpp>
#include"MME/Object/ModelKai.h"

class btCollisionObject;
class btTransform;


namespace GameLib {
	namespace FileIO {
		class InFile;
	}
}

namespace GameObject {
	class Player;
	typedef std::shared_ptr<Player> PlayerSharedPtr;
	class ICollider;
	typedef std::shared_ptr<ICollider> IColliderSharedPtr;
}


namespace GameObjectData {
	class Status;
	typedef std::shared_ptr<Status> StatusSharedPtr;
	class WeaponStatus;
}

namespace XmlLoader {
	class Shape;
	namespace MME {
		namespace Object {
			class ModelKai;
		}
	}

	namespace GameObject {
		class Player {
		public:
			Player();
			~Player();

			void loadXml(const std::string &file);

			bool isReady();

			::GameObject::PlayerSharedPtr instance();

			const std::string & getName()const {
				return mName;
			}

		private:
			//disallow
			Player(const Player&)=delete;
			//disalow
			void operator=(const Player&)=delete;

			friend boost::serialization::access;
			//基底クラスのselialize, save, load関数を直接呼び出さないこと！！
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version);

			GameLib::FileIO::InFile *mXmlFile;
			std::string mName;
			float mHeight;
			Shape *mShape;
			float mMass;
			std::shared_ptr<GameObjectData::Status> mStatus;
			MME::Object::ModelKai *mModel;

		};
	}
}//end namespace XmlLoader::GameObject