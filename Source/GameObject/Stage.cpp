#include "Stage.h"

#include<GameLib/Framework.h>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/IndexBuffer.h>
#include<btBulletDynamicsCommon.h>
#include"BulletPhysics/Manager.h"
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"MMD/ContainerHelper.h"
#include<GameLib/GameLib.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/PseudoXml/Document.h>
#include<GameLib/PseudoXml/Element.h>
#include<GameLib/PseudoXml/Attribute.h>
#include<GameLib/Base/RefString.h>
#include"helper/MyOutputDebugString.h"
//#include"XFile/Model.h"
#include"MME/Object/Accessory.h"
#include"MME/Drawer/GameDrawer.h"


using namespace GameLib::Math;
using namespace GameLib::Graphics;
using namespace GameLib;

namespace{
	static const float skDefalutScale=10.f;
}

namespace GameObject{
RTTI_IMPL( Stage , BaseObject );

StageSharedPtr Stage::create(const char * xmlStageInitFile ){
	StageSharedPtr sp( NEW Stage(xmlStageInitFile) );
	return sp;
}

Stage::Stage( const char * xmlInitStageFile )
	:mModel(NULL),
	mIsClear(false),
	mIsReady(false)
{
	
	GameLib::PseudoXml::Document d = GameLib::PseudoXml::Document::create( xmlInitStageFile ); 
	assert( !d.isError() );
	while( !d.isReady() ){
	}
	
	using namespace GameLib::PseudoXml;
	using GameLib::RefString;
	const char *stageFileName=NULL;
	float scale = 0.f;

	int numChild = d.childNumber();
	for( int ic=0; ic<numChild; ++ic )
	{
		ConstElement e = d.child(ic);
		RefString name(e.name());
		if( name=="Stage" ){
			int numElem=e.attributeNumber();
			for( int ie=0; ie<numElem; ++ie ){
				ConstAttribute a = e.attribute(ie);
				RefString attributeName( a.name() );
				if( attributeName=="file" ){
					stageFileName = a.value();
				} else if( attributeName=="scale" ){
					scale = a.getFloatValue();
				} else {
					TRACE2("%s of %s is wrong\n", a.name(), xmlInitStageFile );
					STRONG_ASSERT( false && "attribute name is wrong!" );
				}
			}
		} else {
			TRACE2("%s of %s is wrong", e.name(), xmlInitStageFile );
			STRONG_ASSERT( false && "element name is wrong!" );
		}
	}

	assert( scale!=0.f );
	assert( stageFileName );


	mModel = MME::Object::Accessory::create();
	mModel->init( stageFileName, scale, NULL );
}

Stage::~Stage(){
	MME::Drawer::GameDrawer::instance()->remove(mModel);

	for( vector<btRigidBody*>::iterator it=mRigidBodies.begin(), end=mRigidBodies.end(); it!=end; ++it){
		btRigidBody *pRigidBody = *it;
		//btRigidBody **ppRigidBody = &(*it);
		if(pRigidBody) {
			BulletPhysics::Manager::instance()->removeFromWorld( pRigidBody );
			btMotionState* pMotionState = pRigidBody->getMotionState();
			if(pMotionState) {
				SAFE_DELETE(pMotionState);
			}

			btCollisionShape* pShape = pRigidBody->getCollisionShape();
			if(pShape) {
				//メッシュデータがある場合
				btTriangleMeshShape* triMeshShape = dynamic_cast<btTriangleMeshShape*>(pShape);
				if( triMeshShape ) {
					if( triMeshShape->getMeshInterface() ) {
						btTriangleMesh *triMesh = dynamic_cast<btTriangleMesh*>(triMeshShape->getMeshInterface());
						SAFE_DELETE(triMesh);
					}
				}
				SAFE_DELETE(pShape);
			}
			//vectorの内部の
			//*it=NULLにしたいから2重ポインタ
			//SAFE_DELETE(*ppRigidBody);
			//わかりにくい
			delete(*it);
			*it=NULL;
		}
	}
	mRigidBodies | destroy();
}

void Stage::drawUsingGameLib() {
	Graphics::Manager m;
	m.setAmbientColor( Vector3(0.f, 0.f, 0.f) );
	m.setCullMode( CULL_FRONT );
	//m.setLightingMode( LIGHTING_NONE );
	m.setLightingMode( LIGHTING_PER_VERTEX );
	mModel->drawUsingGameLib();
}

void Stage::createBvhTriangleMesh(){
	//for(int i=0; i<mNumModels; ++i) {
	//	Batch b = mSceneContainer->batch(i);
	//	assert(mModels[0].vertexBuffer()==b.vertexBuffer());
	//	btRigidBody* pRb = BulletPhysicsHelper::createBvhTriangleMeshShapeRigidBody( 
	//		b.vertexBuffer(), b.indexBuffer(),
	//		b.bufferOffset(), b.primitiveNumber(),
	//		mScale.x, mScale.y, mScale.z );
	//	BulletPhysics::Manager::instance()->addToWorld( pRb );
	//	mRigidBodies.push_back(pRb);
	//}
	
	assert(mModel->getIndexBuffer().indexNumber()%3==0);
	float s =mModel->getScale();
	btRigidBody* pRb = BulletPhysicsHelper::createBvhTriangleMeshShapeRigidBody( 
		mModel->getVertexBuffer(), 
		mModel->getIndexBuffer(),
		0, mModel->getIndexBuffer().indexNumber()/3,
		s, s, s );
	mRigidBodies.push_back(pRb);
}


void Stage::addToWorld(){

	auto bullet = BulletPhysics::Manager::instance();

	for( vector<btRigidBody*>::iterator it=mRigidBodies.begin(), end=mRigidBodies.end(); it!=end; ++it){
		btRigidBody *pRigidBody = *it;
		bullet->addToWorld( pRigidBody );
	}

	MME::Drawer::GameDrawer::instance()->add(mModel);

}
void Stage::removeFromWorld(){
	auto bullet = BulletPhysics::Manager::instance();
	for( vector<btRigidBody*>::iterator it=mRigidBodies.begin(), end=mRigidBodies.end(); it!=end; ++it){
		btRigidBody *pRigidBody = *it;
		bullet->removeFromWorld( pRigidBody );
	}
	MME::Drawer::GameDrawer::instance()->remove(mModel);
}

bool Stage::isReady(){
	if( mIsReady ){
		return true;
	} else{
		if( mModel->isReady() ){
			createBvhTriangleMesh();
			mIsReady = true;
			return true;
		} else {
			return false;
		}
	}
}


int Stage::calculateDamage()
{
	assert(false && "ここをとおることはないはず、設計的に呼ぶはずない、rigidbodyのuserptrが0なのでonCollisionEnterEventを作る際はじかれるはず");
	return 0;
}

bool Stage::canDamage()
{
	assert(false && "ここをとおることはないはず、設計的に呼ぶはずない、rigidbodyのuserptrが0なのでonCollisionEnterEventを作る際はじかれるはず");
	return false;
}

const GameObjectData::WeaponStatus * Stage::getWeaponStatus()
{
	assert(false && "ここをとおることはないはず、設計的に呼ぶはずない、rigidbodyのuserptrが0なのでonCollisionEnterEventを作る際はじかれるはず");
	return nullptr;
}


} //end namespace GameObject