#include"PlayerMouse.h"
#include<btBulletCollisionCommon.h>
#include<GameLib/Input/Mouse.h>
#include"helper/ClickPos.h"
#include"SegaTypeHelper.h"
#include"GameObject/Rttis.h"

#include"BulletPhysics/Manager.h"
#include"helper/PrimitiveDrawer.h"
#include<memory>
#include<numeric>
//#include"GameObject/Stage.h"
//#include"GameObject/CharacterControllerGhostObject.h"

#include<GameLib/GameLib.h>
#include<GameLib/Scene/Model.h>
#include<GameLib/Scene/Container.h>
#include<GameLib/Math/Functions.h>

#include"BulletPhysics/HelperCallbacks.h"

#include"Component/BaseComponent.h"
#include"GameObject/BaseObject.h"
namespace Input {

namespace {
	const int kFlickEnableFrame=30;
//shared_from_this()の仕様が決まらないので一回コメントアウト
/*
Component::BaseComponentWeakPtr rayTest( const btVector3 &start, const btVector3 &end, float radius ){

	btSphereShape sphere(radius);
	

	//始点と終点
	btTransform bttr( btMatrix3x3::getIdentity(), start );
	btTransform bttr1( btMatrix3x3::getIdentity(), end );
	 
	btCollisionWorld::ClosestConvexResultCallback cb( start,  end );
	cb.m_collisionFilterMask = BulletPhysics::DynamicFilter;
		
	BulletPhysics::Manager::instance()->getWorldPtr()->convexSweepTest( &sphere, bttr, bttr1, cb );

	Component::BaseComponentWeakPtr ptr;
	if (cb.hasHit())
	{
		Component::BaseComponent* collision = nullptr;
		//ぶつかったのがStageかどうか
		//上のDynamicFilterによるフィルタリングでStageが指定されているStaticFilter排除しているので余計なことしているが
		//Stageとはぶつかりたくないというのをコードに示すためこのコードで
		if(
			(collision = static_cast<Component::BaseComponent*>(cb.m_hitCollisionObject->getUserPointer())) && 
			!collision->getOwner()->getRTTI().isExactly(GameObject::Rttis::Stage()) )
		{
			ptr = collision->shared_from_this();
		} else {
		}

	}
	return ptr;
}

//isCollidedObject : rayと指定オブジェクトがぶつかったかがぶつかったか
//closestObj : rayから最も近いオブジェクトを返す
void rayTestAndContactTest(
	Component::BaseComponentWeakPtr *closestObj,
	bool *isCollidedObject, const btCollisionObject *contactTestObject,
	const btVector3 &start, const btVector3 &end, float radius )
{
	assert( closestObj );
	assert( isCollidedObject );
	btSphereShape sphere(radius);
	
	//始点と終点
	btTransform bttr( btMatrix3x3::getIdentity(), start );
	btTransform bttr1( btMatrix3x3::getIdentity(), end );
	 
	BulletPhysics::ClosestConvexResultCallbackAndCheckToColllideWithObjA cb( contactTestObject, start,  end );
	cb.m_collisionFilterMask = BulletPhysics::DynamicFilter;
	
	//rayTestしつつcontactTestObjectから最も近いオブジェクト探す
	BulletPhysics::Manager::instance()->getWorldPtr()->convexSweepTest( &sphere, bttr, bttr1, cb );

	if (cb.hasHit())
	{
		if( isCollidedObject ){
			*isCollidedObject = cb.m_hasCollidedWithObjA;
		}

		Component::BaseComponent* collision = nullptr;

		//ぶつかったのがStageかどうか
		//上のDynamicFilterによるフィルタリングでStageが指定されているStaticFilter排除しているので余計なことしているが
		//Stageとはぶつかりたくないというのをコードに示すためこのコードで
		if (
			(collision = static_cast<Component::BaseComponent*>(cb.m_hitCollisionObject->getUserPointer())) &&
			!collision->getOwner()->getRTTI().isExactly(GameObject::Rttis::Stage()))
		{
			*closestObj = collision->shared_from_this();
		}
		else {
		}

	}
	//ぶつからなかった場合
	else {
		*isCollidedObject = false;
		assert( false == cb.m_hasCollidedWithObjA );
	}
}


//球とオブジェクトが接触しているか
//is sphere contacted with object?
bool contactTestBetweenSphereAndObject( float radius, btVector3 &spherePos, btCollisionObject *obj ){

	btSphereShape sphere(radius);
	btCollisionObject col;
	col.setCollisionShape( &sphere );
	col.setWorldTransform( btTransform( btMatrix3x3::getIdentity(), spherePos ) );
	
	BulletPhysics::SimpleContactResultCallback cb; 
	BulletPhysics::Manager::instance()->getWorldPtr()->contactPairTest( &col, obj, cb );

	if (cb.mConnected)
	{
		return true;
	}
	return false;
}

//いちばん近いオブジェクトを返す
Component::BaseComponentWeakPtr contactTestAll( float radius, btVector3 &spherePos ){

	btSphereShape sphere(radius);
	btCollisionObject col;
	col.setCollisionShape( &sphere );
	col.setWorldTransform( btTransform( btMatrix3x3::getIdentity(), spherePos ) );
	
	BulletPhysics::ClosestObjectContactResultCallbackFromObjectA cb( &col ); 
	BulletPhysics::Manager::instance()->getWorldPtr()->contactTest( &col, cb );

	
	Component::BaseComponentWeakPtr wp;

	Component::BaseComponent* collision = nullptr;
	//ぶつかったのがStageかどうか
	//上のDynamicFilterによるフィルタリングでStageが指定されているStaticFilter排除しているので余計なことしているが
	//Stageとはぶつかりたくないというのをコードに示すためこのコードで
	if (
		cb.mClosestObj &&
		(collision = static_cast<Component::BaseComponent*>(cb.mClosestObj->getUserPointer())) &&
		!collision->getOwner()->getRTTI().isExactly(GameObject::Rttis::Stage()))
	{
		wp = collision->shared_from_this();
	}

	return wp;

}
*/

} //end anonymous namespace

PlayerMouse::PlayerMouse( btCollisionObject* player, float radius )
	:mClickedFrame(0),
	mIsOnPlayer(false),
	mMousePos( 0.f, 0.f, 0.f ),
	mClickedMousePos( 0.f, 0.f, 0.f ),
	mPlayerBtObject(player),
	mMouseRadius(radius),
	mHasClickedOnPlayer(false),
	mIsInit(false),
	mArrowModel(NULL)
{
	using namespace GameLib::Input;
	Mouse m;
	mClickedPos[0]=m.x();
	mClickedPos[1]=m.y();

	mMousePos = mPlayerBtObject->getWorldTransform().getOrigin();

	using namespace GameLib::Scene;
	mArrowModel = NEW Model();
	Container c = Container::create("Data/Model/Primitive/arrow.x.txt"); 
	while(!c.isReady()){}
	*mArrowModel = c.createModel(0);
	mArrowModel->setColor( GameLib::Vector3( 0.f, 1.f, 0.f ) );
	mArrowModel->setTransparency( 0.5f );

}
PlayerMouse::~PlayerMouse(){
	SAFE_DELETE(mArrowModel);
}
	
void PlayerMouse::update(const float elapsedTime){
	using namespace GameLib::Input;
	Mouse m;

	//ゲームWorld上のマウスの指し示す線(ray)を取得
	D3DXVECTOR3 dxStart, dxEnd;
	D3DXMATRIX matViewProj;
	matViewProj = toDxMatrix( GameLib::Graphics::Manager::instance().getProjectionViewMatrix() );
	ClickPos::getLine( &dxStart, &dxEnd, matViewProj );
	btVector3 start = toBtVector3( dxStart );
	btVector3 end = toBtVector3( dxEnd );

	//オブジェクトの"上平面"上にマウスカソールを射影
	{
		const btTransform &world = mPlayerBtObject->getWorldTransform();
		btVector3 normalPlane = world.getBasis()[1];
		normalPlane.normalize();
		btVector3 posPlane=world.getOrigin();
		btVector3 line = end-start;
		//原点に移動			
		float startToPlaneLength = (start-posPlane).dot(normalPlane);
		float length = line.normalize().dot( -normalPlane )*startToPlaneLength;
		//三角形の相似より
		float rate=startToPlaneLength*startToPlaneLength/length;
		assert( length!=0.f );
		mMousePos = line*rate + start;
		//TRACE1("startToPlaneLength:%f\n", startToPlaneLength );
		//TRACE3("(%f, %f, %f)\n", mMousePos.x(), mMousePos.y(), mMousePos.z() );
	}
	
	/*一旦コメントアウト
	auto baseComponent = contactTestAll(mMouseRadius, mMousePos);
	if ( auto p = baseComponent.lock()) {
		mOnObject = p->getOwner()->shared_from_this();
	}
	mIsOnPlayer = contactTestBetweenSphereAndObject( mMouseRadius, mMousePos, mPlayerBtObject ); 
	*/

	if(mIsInit){
		mIsInit=false;
		mDragingObject.reset();
		mHasClickedOnPlayer = false;
	}


	if( m.isTriggered(m.BUTTON_LEFT) ) {
		mDragingObject=mOnObject;
		mClickedFrame=0;
		//player上でクリックしたか？
		mHasClickedOnPlayer = mIsOnPlayer;
		mClickedPos[0] = m.x();
		mClickedPos[1] = m.y();

		mClickedMousePos = mMousePos;

	} else if( m.isReleased(m.BUTTON_LEFT) ) {
		//次のフレームは初期化処理を行う
		//ここで初期化を行わないのは、このフレーム内で
		//mDragingObject
		//mHasClickedOnPlayer
		//をほかのクラスから使いたいため
		mIsInit = true;
	} else if( m.isOn(m.BUTTON_LEFT) ) {
	} else {
	}
	
	++mClickedFrame;
}

// velocity = currentPos - oldPos	
bool PlayerMouse::isFlickedPlayer( int *velocityX, int *velocityY )const{
	using namespace GameLib::Input;
	Mouse m;

	if( m.isReleased(m.BUTTON_LEFT) && 
		mHasClickedOnPlayer &&
		mClickedFrame < kFlickEnableFrame )
	{
		*velocityX = m.x() - mClickedPos[0];
		*velocityY = m.y() - mClickedPos[1];
		return true;
	}
	return false;
}
bool PlayerMouse::isFlicked( int *velocityX, int *velocityY )const{
	using namespace GameLib::Input;
	Mouse m;

	if( m.isReleased(m.BUTTON_LEFT) && 
		mClickedFrame < kFlickEnableFrame )
	{
		*velocityX = m.x() - mClickedPos[0];
		*velocityY = m.y() - mClickedPos[1];
		return true;
	}
	return false;
}

bool PlayerMouse::onPlayer()const{
	return mIsOnPlayer;
}
bool PlayerMouse::onObject()const{
	return !mOnObject.expired();
}
	
bool PlayerMouse::isTriggeredPlayer()const {
	using namespace GameLib::Input;
	Mouse m;
	return m.isTriggered(m.BUTTON_LEFT) && mIsOnPlayer; 
}
bool PlayerMouse::isTriggeredObject()const {
	using namespace GameLib::Input;
	Mouse m;
	return m.isTriggered(m.BUTTON_LEFT) && !mOnObject.expired();
}

bool PlayerMouse::isClickingPlayer()const {
using namespace GameLib::Input;
	Mouse m;
	return m.isOn(m.BUTTON_LEFT) && mIsOnPlayer;
}
bool PlayerMouse::isClickingObject()const {
	using namespace GameLib::Input;
	Mouse m;
	return m.isOn(m.BUTTON_LEFT) && !mOnObject.expired();
}

bool PlayerMouse::isReleasedPlayer()const {
using namespace GameLib::Input;
	Mouse m;
	return m.isReleased(m.BUTTON_LEFT) && mIsOnPlayer;
}
bool PlayerMouse::isReleasedObject()const {
	using namespace GameLib::Input;
	Mouse m;
	return m.isReleased(m.BUTTON_LEFT) && !mOnObject.expired();
}

GameObject::BaseObjectObjectWeakPtr PlayerMouse::getOnObject(){
	//nullだととまる
	return mOnObject.lock();
}
GameObject::BaseObjectObjectWeakPtr PlayerMouse::getDragingObject(){
	//nullだととまる
	return mDragingObject.lock();
}

void PlayerMouse::drawMousePos( int color ) const{
	using namespace GameLib::Input;
	Mouse m;
	if(m.isOn( m.BUTTON_LEFT ) ){
		//flickのサポート
		if( mClickedFrame < kFlickEnableFrame ){
			//だんだん大きくなる
			//PrimitiveDrawer::drawSphere( mMousePos, mMouseRadius*0.5f*mClickedFrame/kFlickEnableFrame, color );
			//PrimitiveDrawer::drawSphere( mClickedMousePos, mMouseRadius*0.9f, color );
			
			//矢印
			btVector3 dir = mMousePos - mClickedMousePos;
			float scale = dir.length();
			if( scale == 0.f ){
				return;
			}
			dir.normalize();
			float dot = dir.dot( btVector3( 0.f,0.f,1.f ) );
			float rightOrLeft = dir.x()>0 ? 1.f : -1.f;
			float degree = GameLib::acos( dot ) * rightOrLeft;

			mArrowModel->setScale( GameLib::Vector3( scale ) );
			mArrowModel->setPosition( toVector3( mClickedMousePos ) );
			mArrowModel->setAngle( GameLib::Vector3(0.f, degree, 0.f ) );
			mArrowModel->draw();
		}
		//有効時間過ぎたら
		else {
			PrimitiveDrawer::drawSphere( mMousePos, mMouseRadius*0.9f, color );		
		}

	} else{
		PrimitiveDrawer::drawSphere( mMousePos, mMouseRadius, color );
	}
}

btVector3 PlayerMouse::getPos()const{
	return mMousePos;
}


}