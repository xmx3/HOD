#include"Enemy.h"

#include<BulletCollision/CollisionShapes/btBoxShape.h>
#include<btBulletDynamicsCommon.h>
#include<GameLib/FileIO/InFile.h>
#include<GameLib/GameLib.h>
#include<sstream>

#include"helper/BoostSerializationMacros.h"
#include"helper/MyOutputDebugString.h"
#include"XmlLoader/MME/Object/ModelKai.h"
#include"XmlLoader/Shape.h"
#include"GameObject/Enemy.h"
#include"GameObjectData/Status.h"
#include"GameObjectData/WeaponStatus.h"






namespace XmlLoader{ namespace GameObject{
Enemy::Enemy()
	:mXmlFile(nullptr),
	mMass(0.f),
	mModel(nullptr),
	mShape(nullptr),
	mStatus(nullptr)
{
	mModel = new MME::Object::ModelKai();
	mShape = new Shape();
	mStatus = new GameObjectData::Status();
}

Enemy::~Enemy(){
	SAFE_DELETE(mXmlFile);
	SAFE_DELETE(mModel);
	SAFE_DELETE(mShape);
	SAFE_DELETE(mStatus);
}

void Enemy::loadXml( const std::string &filename ){
	SAFE_DELETE(mXmlFile);
	mXmlFile = new GameLib::FileIO::InFile();
	*mXmlFile = GameLib::FileIO::InFile::create( filename.c_str() );

}

bool Enemy::isReady(){
	if(mXmlFile){
		if( mXmlFile->isFinished() ){
			std::istringstream in_file( 
				std::string(mXmlFile->data(), mXmlFile->size()),
				std::ios::binary || std::ios::in );
			boost::archive::xml_iarchive in_archive(in_file, boost::archive::no_header );
			in_archive >> boost::serialization::make_nvp("Enemy", *this );
			SAFE_DELETE(mXmlFile);//もう使わないのでメモリ開放
			return false;
		}
	} else {
		//return mModel->isReady() && mShape->isReady();
		return mModel->isReady();
	}
	return false;
}

::GameObject::EnemySharedPtr Enemy::instance(){
	if (!isReady()) {
		TRACE("Enemy's Resource has not loaded. it will load at this frame.");
	}
	while(!isReady()){}
	
	std::shared_ptr<btBoxShape> box = std::dynamic_pointer_cast<btBoxShape>(mShape->instanceBtCollisionShape().first);

	//rigidbodyの作成
	// 慣性テンソルの計算
	//回転しない
	btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
	//mShape->calculateLocalInertia( mMass, btv3LocalInertia );

	//static const btVector3 kDefalutInitPos( 0.f, 20.f, 0.f );
	static const btVector3 kDefalutInitPos(0.f, 0.f, 0.f);

	// MotionStateを作成する。剛体の姿勢制御をするもの	
	std::shared_ptr<btDefaultMotionState> pMotionState =
		std::make_shared<btDefaultMotionState>(btTransform(btMatrix3x3::getIdentity(), kDefalutInitPos));

	// 剛体を作成する
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mMass, pMotionState.get(), box.get(), btv3LocalInertia);
	//mRigidBody = std::make_shared<btRigidBody>( rbInfo );//bugります,原因はたぶんalign
	std::unique_ptr<btRigidBody> pRigidBody(new btRigidBody(rbInfo));


	auto status = mStatus->clone();

	typedef ::GameObject::Enemy InstanceEnemy;
	return InstanceEnemy::create(
		mMass,
		mModel->instance(),
		box,
		pMotionState,
		std::move(pRigidBody),
		status );
		
}

EnemySharedPtr XmlLoader::GameObject::Enemy::createSP()
{
	return std::make_shared<Enemy>();
}



template<class Archive>
void Enemy::serialize(Archive& ar, const unsigned int version){
	using boost::serialization::make_nvp;
	ar & make_nvp( "name", mName );

	ar & make_nvp("mass", mMass);

	ar & make_nvp( "Shape", *mShape );
	
	ar & make_nvp( "ModelKai", *mModel );

	ar & make_nvp( "Status", *mStatus );
}

EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION(Enemy);

}}//end XmlLoader::GameObject

BOOST_CLASS_IMPLEMENTATION(XmlLoader::GameObject::Enemy, boost::serialization::object_serializable);
