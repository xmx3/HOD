#include"Player.h"

#include<GameLib/GameLib.h>
#include<GameLib/Framework.h>

#include"XmlLoader/Shape.h"
#include"XmlLoader/MME/Object/ModelKai.h"
#include"XmlLoader/Shape.h"
#include"GameObjectData/Status.h"
#include"GameObjectData/WeaponStatus.h"

#include<GameLib/FileIO/InFile.h>
#include<sstream>
#include"helper/BoostSerializationMacros.h"

#include"GameObject/Player.h"
#include"Input/PlayerMouse.h"

#include"Camera/FixedCamera.h"
#include"Camera/HodCamera.h"

#include"MMD/CameraAnimation.h"

#include<btBulletDynamicsCommon.h>

namespace XmlLoader { namespace GameObject {
		Player::Player()
			:mXmlFile(nullptr),
			mShape(nullptr),
			mStatus(nullptr),
			mModel(nullptr)
		{
			
		}

		Player::~Player() {
			SAFE_DELETE(mXmlFile);
			SAFE_DELETE(mModel)
			SAFE_DELETE(mShape);
			mStatus.reset();
		}

		void Player::loadXml(const std::string &filename) {
			SAFE_DELETE(mXmlFile);
			mXmlFile = new GameLib::FileIO::InFile();
			*mXmlFile = GameLib::FileIO::InFile::create(filename.c_str());
		}

		bool Player::isReady() {
			if (mXmlFile) {
				if (mXmlFile->isFinished()) {
					SAFE_DELETE(mShape);
					mStatus.reset();
					SAFE_DELETE(mModel);

					mShape = new Shape();
					mStatus = std::make_shared<GameObjectData::Status>();
					mModel = new MME::Object::ModelKai();

					std::istringstream in_file(
						std::string(mXmlFile->data(), mXmlFile->size()),
						std::ios::binary || std::ios::in);
					boost::archive::xml_iarchive in_archive(in_file, boost::archive::no_header);
					in_archive >> boost::serialization::make_nvp("Player", *this);
					SAFE_DELETE(mXmlFile);//もう使わないのでメモリ開放
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return mShape && mModel &&mModel->isReady();
			}
			return false;
		}

		::GameObject::PlayerSharedPtr Player::instance() {
			assert(isReady() && "準備完了してから読み出したい");
			while (!isReady()) {}

			std::shared_ptr<btCylinderShape> cylinder = std::dynamic_pointer_cast<btCylinderShape>(mShape->instanceBtCollisionShape().first);
			assert(cylinder);

			//rigidbodyの作成
			// 慣性テンソルの計算
			//回転しない
			btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
			//mShape->calculateLocalInertia( mMass, btv3LocalInertia );

			//static const btVector3 kDefalutInitPos( 0.f, 20.f, 0.f );
			static const btVector3 kDefalutInitPos(-80.f, 50.f, 0.f);
			
			// MotionStateを作成する。剛体の姿勢制御をするもの	
			std::shared_ptr<btDefaultMotionState> pMotionState( 
				new btDefaultMotionState(btTransform(btMatrix3x3::getIdentity(), kDefalutInitPos)));
			//なんとなくバグの原因かなと思ったので実際は変わらない
			//けどバレット関連でmakeshardは絶対やめたほうがいい
			//std::make_shared<btDefaultMotionState>(btTransform(btMatrix3x3::getIdentity(), kDefalutInitPos));
			
			// 剛体を作成する
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mMass, pMotionState.get(), cylinder.get(), btv3LocalInertia);
			//mRigidBody = std::make_shared<btRigidBody>( rbInfo );//bugります,原因はたぶんalign
			std::unique_ptr<btRigidBody> pRigidBody(new btRigidBody(rbInfo));
			
			//Mouseの作成
			std::shared_ptr<Input::PlayerMouse> pMouse =
				std::make_shared<Input::PlayerMouse>(pRigidBody.get(), mHeight*0.5f);

			
			//FixedCameraの作成
			//GameLib::Framework framework;
			//auto pCamera = std::make_shared<::Camera::FixedCamera>(
			//	D3DXVECTOR3(0.f, 70.f, 40.f),
			//	D3DXVECTOR3(0.f, 55.f, 0.f),
			//	D3DXVECTOR3(0.f, 1.f, 0.f),
			//	45.f,
			//	0.1f,
			//	30000.f);
			//std::shared_ptr<::Camera::ICamera> pICamera =
			//	std::dynamic_pointer_cast<::Camera::ICamera, ::Camera::FixedCamera>(pCamera);
			//
			//assert(pICamera);


			auto model = mModel->instance();

			//それよりもGameObjectを作る時これを使わないほうがいいと思う
			//ここにロードさせるほうがいいかも
			//これのメリットはプレイヤーに関して一か所にまとめられるということ
			//確かにそのメリットはアニメあたり判定ステータスを一か所にまとめられる
			//一か所にあれば調整しやすいが
			//仕様次第では回避できる気がする
			//そもそもステータスをどう使うか決まってないのがくそ
			
			typedef ::GameObject::Player InstancePlayer;
			return InstancePlayer::create(
				mHeight,
				model,
				cylinder,
				pMotionState,
				std::move(pRigidBody),
				nullptr,
				pMouse,
				mStatus->clone() );
		}



		template<class Archive>
		void Player::serialize(Archive& ar, const unsigned int version) {
			using boost::serialization::make_nvp;
			ar & make_nvp("Name", mName);
			ar & make_nvp("Height", mHeight);
			ar & make_nvp("Mass", mMass);
			ar & make_nvp("Shape", *mShape);
			ar & make_nvp("Status", *mStatus);
			ar & make_nvp("ModelKai", *mModel);
		}

		EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(Player);

} }//end XmlLoader::GameObject

BOOST_CLASS_IMPLEMENTATION(XmlLoader::GameObject::Player, boost::serialization::object_serializable);