#ifndef __CHARACTERTEST_H__
#define __CHARACTERTEST_H__
#include"GameObject/Character/old/OldCharacterControllerObject.h"
#include"helper/SphereMesh.h"
#include<btBulletDynamicsCommon.h>
#include<GameLib/Input/Keyboard.h>
#include<BulletCollision/CollisionDispatch/btGhostObject.h>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/Vertex.h>
#include"MMD/MMDMikuModel.h"
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"helper/MyOutputDebugString.h"

class CCharacterTest{
public:
	CCharacterTest()
		:mVelocity(10.f),
		mAngulerVelocity( 2.f*3.14f * 0.01 * 30.f ),//2PI * 回転/秒 * fps
		mControler( 
			btTransform( 
				btMatrix3x3(	1,0,0,
								0,1,0,
								0,0,1 ) ,
				btVector3(0, 30 , 0)
			) ,
			14.f, 2.f,
			10.f,
			2.f*3.14f * 0.01 * 30.f
		),
		mUpLength(60.f),
		mBackwardLength(30.f),
		mHeight(9.f),
		mWidth(3.f)
	{
		const btTransform &world = mControler.getWorldTransform();
		D3DXMATRIX dxW = toDxMatrix(world);
		dxW._42 -= mHeight;
		mModel.init( dxW );
	}
	virtual ~CCharacterTest()
	{}

	btTransform getWorldTransform()
	{
		const btTransform &world = mControler.getWorldTransform();
		return world;
	}

	void draw(){
		using namespace GameLib::Graphics;
		mControler.draw();
		mModel.draw();
		
		if(true){
			const btTransform &world = mControler.getWorldTransform();
			btVector3 z=world.getBasis()[2];
			btVector3 z0(0.f, 0.f, 1.f);
			float rad = acosf ( z.dot(z0) );
			float s = sinf(-rad);
			float c = cosf(-rad);
			//TRACE2("sin: %f, cos: %f \n", s, c);
			//TRACE2("x  : %f, z  : %f \n", z.x(), z.z() );
			btVector3 pos = world.getOrigin();
			VertexBuffer line = VertexBuffer::create(2);
			Vertex *pV=line.lock();
			{
				pV[0].mPosition.set( pos.x(), pos.y(), pos.z() );
				//pos- rotMat( axis(0,1,0), -acos(z・z0) )・z0
				pV[1].mPosition.set( pos.x()+z.x()*10, pos.y()-z.y()*10, pos.z()-z.z()*10 );
				pV[0].mNormal.set(0.f, 0.f, 0.f);
				pV[1].mNormal.set(0.f, 0.f, 0.f);
				pV[0].mColor = 0xff00ffff;
				pV[1].mColor = 0xff00ffff;
			}
			line.unlock( &pV );
			Matrix34 wm;
			wm.setIdentity();
			GameLib::Graphics::Manager mngr = GameLib::Graphics::Manager::instance();
			mngr.setWorldMatrix(wm);
			mngr.setTexture(0);
			mngr.setVertexBuffer( line );
			mngr.draw( 0, 1, PRIMITIVE_LINE );
		}
	}
	void update( float elapsedTime ){
		GameLib::Input::Keyboard k;
		bool isR=false, isL=false, isF=false, isB=false;
		
		if( k.isOn(k.KEY_UP) ) {
			isF=true;
		}
		if( k.isOn(k.KEY_DOWN) ) {
			isB=true;
		}
		if( k.isOn(k.KEY_RIGHT) ) {
			isR=true;
		}
		if( k.isOn(k.KEY_LEFT) ) {
			isL=true;
		}

		mControler.update( elapsedTime, isF, isB, isL, isR );
		const btTransform &world = mControler.getWorldTransform();
		D3DXMATRIX dxW = toDxMatrix(world);
		dxW._42 -= mHeight;
		mModel.update( dxW, elapsedTime );
	}
	void getView( btVector3 *pTarget, btVector3 *pCameraPos ){
		const btTransform &characterWorldTrans = mControler.getWorldTransform();
		btVector3 up = characterWorldTrans.getBasis()[1];
		up.normalize ();

		//mmdが左手座標として作られているので逆を向いているので反対方向を前とする。
		btVector3 backward = characterWorldTrans.getBasis()[2];
		backward.setX(-backward.x());
		backward.normalize ();


		btVector3 cameraTargetPosition = characterWorldTrans.getOrigin();
		btVector3 cameraPosition = cameraTargetPosition + up * mUpLength + backward * mBackwardLength;	
	
		//use the convex sweep test to find a safe position for the camera (not blocked by static geometry)
		btSphereShape cameraSphere(0.2f);
		btTransform cameraFrom,cameraTo;
		cameraFrom.setIdentity();
		cameraFrom.setOrigin(characterWorldTrans.getOrigin());
		cameraTo.setIdentity();
		cameraTo.setOrigin(cameraPosition);
	
		btCollisionWorld::ClosestConvexResultCallback cb( characterWorldTrans.getOrigin(), cameraTo.getOrigin() );
		cb.m_collisionFilterMask = btBroadphaseProxy::StaticFilter;
		
		BulletPhysics::Manager::instance()->getWorldPtr()->convexSweepTest( &cameraSphere, cameraFrom, cameraTo, cb );
		if (cb.hasHit())
		{

			btScalar minFraction  = cb.m_closestHitFraction;//btMax(btScalar(0.3),cb.m_closestHitFraction);
			cameraPosition.setInterpolate3(cameraFrom.getOrigin(),cameraTo.getOrigin(),minFraction);
		}
		if(pTarget){
			*pTarget=cameraTargetPosition;
		}
		if(pCameraPos){
			*pCameraPos=cameraPosition;
		}
	}

	//カメラの相対位置
	//カメラの位置をターゲットの上方のどのくらいの長さにおくか
	//計算式は以下になっている
	//btVector3 cameraPosition = cameraTargetPosition + up * mUpLength + backward * mBackwardLength;	
	void setUpLength( float upLength ){
		mUpLength=upLength;
	}
	
	//カメラの相対位置
	//カメラの位置をターゲットの後方のどのくらいの長さにおくか
	//btVector3 cameraPosition = cameraTargetPosition + up * mUpLength + backward * mBackwardLength;	
	//計算式は以下になっている
	void setBackwardLength( float backLength ){
		mBackwardLength=backLength;
	}
private:
	Old::CharacterControllerObject mControler;
	CMMD_MikuModel mModel;
	//btVector3 mPos;
	float mVelocity;
	float mAngulerVelocity;

	float mHeight;
	float mWidth;

	float mUpLength;//カメラの相対上方位置
	float mBackwardLength;//カメラの相対後方位置
};
#endif//__CHARACTERTEST_H__