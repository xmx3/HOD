#include"CharacterControllerObject.h"

#include<GameLib/GameLib.h>
#include<GameLib/DebugScreen.h>
#include<btBulletDynamicsCommon.h>
#include<BulletCollision/CollisionDispatch/btGhostObject.h>
#include<BulletDynamics/Character/btKinematicCharacterController.h>
#include"BulletPhysics/CharacterController/kztrCharacterController2.h"

#include"BulletPhysics/BulletPhysics_Manager.h"
#include"helper/MyOutputDebugString.h"
#include"helper/PrintBtVector3.h"
#include<tchar.h>

//どのように動くかのテストのためのinclude。マウスとかのコントローラはここに置かない
#include"MouseWrapper.h"
#include<GameLib/Input/Keyboard.h>

namespace GameObject {

RTTI_IMPL( CharacterControllerObject , IGameObject );

static float calcVel(
	const float &resist,
	const float &vel0,//現在の速度
	const float &maxVel,
	const float &accel )
{
	float vel = vel0 + accel - resist*vel0;
	if( vel > maxVel ){
		vel=maxVel;
	}
	if( vel < resist ){
		vel=0.f;
	}
	return vel;
}




CharacterControllerObject::CharacterControllerObject(
	const btTransform &startTransform, 
	float characterHeight,
	float characterWidth,
	float maxSpeed,
	float maxAngularSpeed )
	:mId( getGameObjectsNum() ),
	mCharacter(NULL),
	mGhostObject(NULL),
	mMaxSpeed(maxSpeed),
	mMaxAngularSpeed(maxAngularSpeed),
	mIsDash(false), mIsJump(false),
	mIsInWorld(false),
	mIsArrived(true),
	mFilterGroup(btBroadphaseProxy::DefaultFilter),
	mFilterMask(btBroadphaseProxy::AllFilter & ~BulletPhysics::Manager::MMDObjectFilter )
{
	btDiscreteDynamicsWorld *pWorld = BulletPhysics::Manager::instance()->getWorldPtr();
	btAxisSweep3* sweepBP = dynamic_cast<btAxisSweep3*>(pWorld->getBroadphase());
	assert( sweepBP && "" );
	mGhostObject = new btPairCachingGhostObject();
	mGhostObject->setWorldTransform(startTransform);
	mGhostObject->setUserPointer( this );
	
	btConvexShape* capsule = new btCapsuleShape(characterWidth, characterHeight);
	mGhostObject->setCollisionShape (capsule);
	//mGhostObject->setCollisionFlags (  btCollisionObject::CF_CHARACTER_OBJECT );//mGhostObject->getCollisionFlags() |

	btScalar stepHeight = btScalar(0.35);
	//mCharacter = new btKinematicCharacterController (mGhostObject,capsule,stepHeight);
	mCharacter = new kztr::CharacterController2( mGhostObject, capsule, stepHeight);
	
	addToWorld();
	

}

CharacterControllerObject::~CharacterControllerObject(){
	removeFromWorld();
	
	//cleanup in the reverse order of creation/initialization
	
	btCollisionShape *shape=mGhostObject->getCollisionShape();
	SAFE_DELETE(shape);
	SAFE_DELETE(mCharacter);
	SAFE_DELETE(mGhostObject);
}

void CharacterControllerObject::update( float elapsedTime )
{

	/* Character stuff &*/
	if (mCharacter)
	{
		
	}
	
	///set walkDirection for our character
	btTransform xform;
	xform = mGhostObject->getWorldTransform ();
	
	//example
	//btVector3 z=xform.getBasis()[2];
	//btVector3 z0(0.f, 0.f, 1.f);
	//float rad = acosf ( z.dot(z0) );
	//float s = sinf(-rad);
	//float c = cosf(-rad);
	//TRACE2("sin: %f, cos: %f \n", s, c);
	//TRACE2("x  : %f, z  : %f \n", z.x(), z.z() );
	
	//座標系?、右ねじ、左ねじ?
	//問題は回転が逆となりモデルの向きと進む向きが一致しないこと。
	//理由が説明できないのが気持ち悪い。
	//この成分はz軸がどれだけ射影されているかの値だと俺は思っているけど違うのか？
	//ちがうわ。これが原因だ。
	//assert( xform.getBasis()[2] == xform*btVector3(0,0,1) );
	//は一致しない
	//bulletphysicsのデモが上手く言ってるように見えるのは左右対象のオブジェクトを使っているから

	
	//以下の計算は前がどっちにあるかを調べる。
	//用は下2つの計算式と同じ
	//example1 逆回転する
	//btVector3 z0(0.f, 0.f, 1.f);
	//btVector3 z=xform.getBasis()[2];
	//rotMat( axis(0,1,0), -acos(z・z0) )・z0

	//exsample2　軸を求める
	//xform*z0
	btVector3 forwardDir = xform.getBasis()[2];
	forwardDir.setX(-forwardDir.x());
	//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
	forwardDir = -forwardDir;
	forwardDir.normalize ();


	//printf("forwardDir=%f,%f,%f\n",forwardDir[0],forwardDir[1],forwardDir[2]);
	btVector3 upDir = xform.getBasis()[1];
	btVector3 strafeDir = xform.getBasis()[0];
	upDir.normalize ();
	strafeDir.normalize();

	btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
	mSpeed = mMaxSpeed * elapsedTime;

	btScalar angularSpeed = mMaxAngularSpeed * elapsedTime;
	
	bool isBrake = false;

	//targetの方向に向く
	{
		//mTargetをオブジェクト"上平面状"に落とす。
		btVector3 targetDir = mTarget-mGhostObject->getWorldTransform().getOrigin();
		targetDir -= targetDir.dot( upDir ) * upDir;
		float theata;
		//0割対策
		if( targetDir.length2() == 0.f ){
			theata = 0.f;
		} else {
			targetDir.normalize();
			theata = acosf( forwardDir.dot(targetDir) );
		}
		//0割対策etc まあ上でやっているのでいらないが
		//非数の場合、(同じ方向の場合)
		if( theata!=theata ){
			//bool a=theata<0.001f;
			//bool b=theata>0.001f;
			return;
		}
		//120度以上の場合 ブレーキかける
		if(theata>3.14159265f*2.f/3.f){
			isBrake=true;
		}
		//0-1の間に変える。90度のとき一番回転する
		float s=sinf(theata);
		s*=s;//動きが早すぎるため調整

		//TRACE1("targetPos	:%f\n", targetPos.y() );
		//TRACE1("theata		:%f\n", theata);
		//TRACE1("sin			:%f\n", s);
		
		//回転させる量
		theata=angularSpeed*s;
		
		//回転が右か左か。cosで+-が消えてるのですべて＋の回転になっているので
		btVector3 cross=forwardDir.cross(targetDir);
		if( cross.y() < 0.f){
			theata=-theata;
		}

		if(theata!=0.f){
			btMatrix3x3 orn = mGhostObject->getWorldTransform().getBasis();
			orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0), theata));
			mGhostObject->getWorldTransform ().setBasis(orn);
		}
	}


	if(mIsDash){
		mCharacter->setVelocity( forwardDir*mCharacter->getMinSpeed() );
		//mCharacter->applyCentralForce( forwardDir*100.f );
		mCharacter->addAccelVelocityForTimeInterval( forwardDir*mSpeed, 6.f/30.f );
	}

	//controllerでのjump
	if( mIsJump ){
		mCharacter->setJumpSpeed( 30.f );
		mCharacter->jump();
	}
	
	//壁蹴りの処理
	if(false)
	if( mIsJump ) {
		//足からrayCast出して、ぶつかればジャンプできる
		btSphereShape sphere(0.4f);
		btTransform from,to;
		from.setIdentity();
		const btTransform &characterWorldTrans = getWorldTransform();
		from.setOrigin( characterWorldTrans.getOrigin() );
		const btCapsuleShape *shape = dynamic_cast<const btCapsuleShape*>( mGhostObject->getCollisionShape() );
		assert(shape);
		//足元からレイを出す
		const float &offsetY = shape->getHalfHeight();
		from.getOrigin().setY( from.getOrigin().y() - offsetY );
		to.setIdentity();
		//壁までの距離が3以下なら、壁蹴りする
		static const float kDistanceToAllowJump=3.f;
		to.setOrigin( from.getOrigin()+forwardDir*kDistanceToAllowJump );
	
		btCollisionWorld::ClosestConvexResultCallback cb( from.getOrigin(), to.getOrigin() );
		//静的物体のみ当たり判定ありのmask
		cb.m_collisionFilterMask = btBroadphaseProxy::StaticFilter;
		
		BulletPhysics::Manager::instance()->getWorldPtr()->convexSweepTest( &sphere, from, to, cb );
		
		//壁蹴りできるよ
		if (cb.hasHit())
		{
			//btScalar minFraction  = cb.m_closestHitFraction;//btMax(btScalar(0.3),cb.m_closestHitFraction);
			//壁蹴りの処理	
		}

	}
	mMode = MODE_ACCEL;

}

const btTransform & CharacterControllerObject::getWorldTransform() const {
	return mGhostObject->getWorldTransform();
}
btTransform & CharacterControllerObject::getWorldTransgorm(){
	return mGhostObject->getWorldTransform();
}


void CharacterControllerObject::draw() const {
	BulletPhysics::Manager::drawObject( mGhostObject, 0xff000000 );
}

void CharacterControllerObject::warp( const btVector3 &pos ) {
	mCharacter->warp( pos );
}

void CharacterControllerObject::setUserPtr( void *ptr ){
	mGhostObject->setUserPointer( ptr );
}
const btVector3& CharacterControllerObject::getVelocity() const {
	return mCharacter->getVelocity();
}

bool CharacterControllerObject::onGround() const{
	return mCharacter->onGround();
}
bool CharacterControllerObject::onGroundPerhaps() const{
	return mCharacter->onGroundPerhaps();
}

btCollisionObject* CharacterControllerObject::getBtCollisionObject(){
	return mGhostObject;
}

void CharacterControllerObject::removeFromWorld(){
	if(mIsInWorld) {
		btDiscreteDynamicsWorld *pWorld = BulletPhysics::Manager::instance()->getWorldPtr();
		//BulletPhysics::Manager* mngr = BulletPhysics::Manager::instance();
		if (mCharacter)
		{
			pWorld->removeCollisionObject( mGhostObject );
			pWorld->removeAction( mCharacter );
		}
		mIsInWorld = false;
	}
}

void CharacterControllerObject::addToWorld(){
	if(!mIsInWorld) {
		btDiscreteDynamicsWorld *pWorld = BulletPhysics::Manager::instance()->getWorldPtr();
		pWorld->addCollisionObject(
			mGhostObject,
			mFilterGroup,
			mFilterMask
		);

		pWorld->addAction(mCharacter);
		mTarget = mGhostObject->getWorldTransform().getOrigin();
		mIsInWorld = true;
	}
}

void CharacterControllerObject::walkControleUpdate( float elapsedTime ){
	///set walkDirection for our character
	btTransform xform;
	xform = mGhostObject->getWorldTransform ();
	
	//example
	//btVector3 z=xform.getBasis()[2];
	//btVector3 z0(0.f, 0.f, 1.f);
	//float rad = acosf ( z.dot(z0) );
	//float s = sinf(-rad);
	//float c = cosf(-rad);
	//TRACE2("sin: %f, cos: %f \n", s, c);
	//TRACE2("x  : %f, z  : %f \n", z.x(), z.z() );
	
	//座標系?、右ねじ、左ねじ?
	//問題は回転が逆となりモデルの向きと進む向きが一致しないこと。
	//理由が説明できないのが気持ち悪い。
	//この成分はz軸がどれだけ射影されているかの値だと俺は思っているけど違うのか？
	//ちがうわ。これが原因だ。
	//assert( xform.getBasis()[2] == xform*btVector3(0,0,1) );
	//は一致しない
	//bulletphysicsのデモが上手く言ってるように見えるのは左右対象のオブジェクトを使っているから

	
	//以下の計算は前がどっちにあるかを調べる。
	//用は下2つの計算式と同じ
	//example1 逆回転する
	//btVector3 z0(0.f, 0.f, 1.f);
	//btVector3 z=xform.getBasis()[2];
	//rotMat( axis(0,1,0), -acos(z・z0) )・z0

	//exsample2　軸を求める
	//xform*z0
	btVector3 forwardDir = xform.getBasis()[2];
	forwardDir.setX(-forwardDir.x());
	//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
	forwardDir = -forwardDir;
	forwardDir.normalize();

	//printf("forwardDir=%f,%f,%f\n",forwardDir[0],forwardDir[1],forwardDir[2]);
	btVector3 upDir = xform.getBasis()[1];
	btVector3 strafeDir = xform.getBasis()[0];
	upDir.normalize ();
	strafeDir.normalize ();

	btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
	mSpeed = mMaxSpeed * elapsedTime;

	btScalar angularSpeed = mMaxAngularSpeed * elapsedTime;
	if (mIsLeft)
	{
		btMatrix3x3 orn = mGhostObject->getWorldTransform().getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0), angularSpeed));
		mGhostObject->getWorldTransform ().setBasis(orn);
	}

	if (mIsRight)
	{
		btMatrix3x3 orn = mGhostObject->getWorldTransform().getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0), -angularSpeed));
		mGhostObject->getWorldTransform ().setBasis(orn);
	}

	if (mIsUp)
	{
		walkDirection += forwardDir;
	}
	if (mIsDown)
	{
		walkDirection -= forwardDir;	
	}

	mCharacter->setWalkDirection(walkDirection*mSpeed);
	mMode = MODE_WALK;
	
}

void CharacterControllerObject::update2( float elapsedTime )
{
	///set walkDirection for our character
	const btTransform &xform = mGhostObject->getWorldTransform ();
	
	//example
	//btVector3 z=xform.getBasis()[2];
	//btVector3 z0(0.f, 0.f, 1.f);
	//float rad = acosf ( z.dot(z0) );
	//float s = sinf(-rad);
	//float c = cosf(-rad);
	//TRACE2("sin: %f, cos: %f \n", s, c);
	//TRACE2("x  : %f, z  : %f \n", z.x(), z.z() );
	
	//座標系?、右ねじ、左ねじ?
	//問題は回転が逆となりモデルの向きと進む向きが一致しないこと。
	//理由が説明できないのが気持ち悪い。
	//この成分はz軸がどれだけ射影されているかの値だと俺は思っているけど違うのか？
	//ちがうわ。これが原因だ。
	//assert( xform.getBasis()[2] == xform*btVector3(0,0,1) );
	//は一致しない
	//bulletphysicsのデモが上手く言ってるように見えるのは左右対象のオブジェクトを使っているから

	
	//以下の計算は前がどっちにあるかを調べる。
	//用は下2つの計算式と同じ
	//example1 逆回転する
	//btVector3 z0(0.f, 0.f, 1.f);
	//btVector3 z=xform.getBasis()[2];
	//rotMat( axis(0,1,0), -acos(z・z0) )・z0

	//exsample2　軸を求める
	//xform*z0
	btVector3 forwardDir = xform.getBasis()[2];
	forwardDir.setX(-forwardDir.x());
	//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
	forwardDir = -forwardDir;
	forwardDir.normalize ();


	//printf("forwardDir=%f,%f,%f\n",forwardDir[0],forwardDir[1],forwardDir[2]);
	btVector3 upDir = xform.getBasis()[1];
	btVector3 strafeDir = xform.getBasis()[0];
	upDir.normalize ();
	strafeDir.normalize();

	
	if(!mIsArrived){

		//bool isBrake = false;

		//targetの方向に向く
		{
			//mTargetをオブジェクト"上平面状"に落とす。
			btVector3 targetDir = mTarget-mGhostObject->getWorldTransform().getOrigin();
			targetDir -= targetDir.dot( upDir ) * upDir;
			float theata;
			//0割対策
			if( targetDir.length2() == 0.f ){
				theata = 0.f;
			} else {
				targetDir.normalize();
				theata = acosf( forwardDir.dot(targetDir) );
			}
			//0割対策etc まあ上でやっているのでいらないが
			//非数の場合、(同じ方向の場合)
			if( theata!=theata ){
				//bool a=theata<0.001f;
				//bool b=theata>0.001f;
				return;
			}
			//120度以上の場合 ブレーキかける
			//if(theata>3.14159265f*2.f/3.f){
			//	isBrake=true;
			//}
		
			//回転させる量
			btScalar angularSpeed = mMaxAngularSpeed * elapsedTime;
			assert( theata>=0.f );
			if( theata > angularSpeed ){
				theata=angularSpeed;
			}
			//回転が右か左か。cosで+-が消えてるのですべて＋の回転になっているので
			btVector3 cross=forwardDir.cross(targetDir);
			if( cross.y() < 0.f){
				theata=-theata;
			}

			if(theata!=0.f){
				btMatrix3x3 orn = mGhostObject->getWorldTransform().getBasis();
				orn *= btMatrix3x3(btQuaternion(btVector3(0,1,0), theata));
				mGhostObject->getWorldTransform ().setBasis(orn);
			}

			btVector3 walkDir = (mTarget-xform.getOrigin());
			walkDir.setY(0.f);		
			const float distance = walkDir.length();
		
			if(distance < 000001.f){
				mCharacter->setWalkDirection( btVector3( 0.f, 0.f, 0.f ) );
				mIsArrived=true;
			}
			else
			{
				walkDir.normalize();
			
				//mSpeed = mMaxSpeed * elapsedTime;
				mSpeed = mMaxSpeed * 1.f/60.f;
		
				if( distance < mSpeed ){
					mSpeed = distance;
				} 
				//TRACE0(_T("pos : ") );
				//PrintBtVector3::toOutput( xform.getOrigin() );
				//TRACE0(_T("pos+vel : ") );
				//PrintBtVector3::toOutput(xform.getOrigin()+walkDir*mSpeed);
				mCharacter->setWalkDirection( walkDir*mSpeed );
			}
		}
	} else {
		mCharacter->setWalkDirection( btVector3( 0.f, 0.f, 0.f ) );
	}

	//controllerでのjump
	if( mIsJump ){
		mCharacter->setJumpSpeed( 30.f );
		mCharacter->jump();
	}
	
	//壁蹴りの処理
	if(false)
	if( mIsJump ) {
		//足からrayCast出して、ぶつかればジャンプできる
		btSphereShape sphere(0.4f);
		btTransform from,to;
		from.setIdentity();
		const btTransform &characterWorldTrans = getWorldTransform();
		from.setOrigin( characterWorldTrans.getOrigin() );
		const btCapsuleShape *shape = dynamic_cast<const btCapsuleShape*>( mGhostObject->getCollisionShape() );
		assert(shape);
		//足元からレイを出す
		const float &offsetY = shape->getHalfHeight();
		from.getOrigin().setY( from.getOrigin().y() - offsetY );
		to.setIdentity();
		//壁までの距離が3以下なら、壁蹴りする
		static const float kDistanceToAllowJump=3.f;
		to.setOrigin( from.getOrigin()+forwardDir*kDistanceToAllowJump );
	
		btCollisionWorld::ClosestConvexResultCallback cb( from.getOrigin(), to.getOrigin() );
		//静的物体のみ当たり判定ありのmask
		cb.m_collisionFilterMask = btBroadphaseProxy::StaticFilter;
		
		BulletPhysics::Manager::instance()->getWorldPtr()->convexSweepTest( &sphere, from, to, cb );
		
		//壁蹴りできるよ
		if (cb.hasHit())
		{
			//btScalar minFraction  = cb.m_closestHitFraction;//btMax(btScalar(0.3),cb.m_closestHitFraction);
			//壁蹴りの処理	
		}

	}
	mMode = MODE_CLICK;
}

void CharacterControllerObject::checkArrivalInNexTime() {
	if( !mIsArrived && mMode==MODE_CLICK){
		btVector3 walkDir = (mTarget-mGhostObject->getWorldTransform().getOrigin());
		walkDir.setY(0.f);		
		const float distance = walkDir.length();
		
		if(distance < 000001.f){
			mCharacter->setWalkDirection( btVector3( 0.f, 0.f, 0.f ) );
			mIsArrived=true;			
			return;

		}
		walkDir.normalize();
		
		if( distance < mSpeed ){
			mSpeed = distance;
			mCharacter->setWalkDirection( mSpeed*walkDir );				
		}

	}
}

}//end namespace GameObject
