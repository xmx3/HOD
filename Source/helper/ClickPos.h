#ifndef __CLICKPOS_H__
#define __CLICKPOS_H__
#include<GameLib/Input/Mouse.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/Vertex.h>
#include<GameLib/Math/Matrix34.h>
#include<GameLib/Math/Vector2.h>
#include<d3dx9.h>
#include"MMD/MMDMacro.h"
#include<assert.h>
#include<btBulletDynamicsCommon.h>
#include"BulletPhysics/Manager.h"
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"helper/MyOutputDebugString.h"
#include<GameLib/Graphics/Texture.h>


class ClickPos{
public:
	//クリックしたワールド座標を得る。Z値が0だとカメラの写す位置、Z値が1だとターゲット位置の平面のクリックした座標
	static void getPos( 
		D3DXVECTOR3 *pOut,
		const  D3DXMATRIX &viewProj,
		float fZ=0.f	// 射影空間でのZ値（0～1）
		)
	{
		assert(fZ>=0.f && "fZ is wrong value");
		assert(fZ<=1.f && "fZ is wrong value");
		GameLib::Input::Mouse m;
		int x, y, width, height;
		GameLib::Graphics::Manager::instance().getViewport( &x, &y, &width, &height );
		D3DXMATRIX matI;
		D3DXMATRIX matViewPort;
		D3DXMATRIX matInverseViewPort, matInverseViewProj;
		D3DXMatrixIdentity( &matViewPort );
		matViewPort._11 = static_cast<float>( width )/2.0f;
		matViewPort._22 = static_cast<float>( -height )/2.0f;
		matViewPort._41 = static_cast<float>( width )/2.0f;
		matViewPort._42 = static_cast<float>( height )/2.0f;
		D3DXMatrixInverse( &matInverseViewPort, NULL, &matViewPort );
		
		D3DXMatrixInverse( &matInverseViewProj, NULL, &viewProj );
		
		D3DXMATRIX matITemp =  matInverseViewPort * matInverseViewProj; 

		D3DXVECTOR3 pos( static_cast<float>(m.x()), static_cast<float>(m.y()), fZ );
		D3DXVec3TransformCoord( pOut, &pos, &matITemp );
		return;
	}

	//マウス位置に対応する、ワールド座標を得る。
	static void getLine( D3DXVECTOR3 *pOutBegin, D3DXVECTOR3 *pOutEnd, const  D3DXMATRIX &viewProj ) {
		GameLib::Input::Mouse m;
		int x, y, width, height;
		GameLib::Graphics::Manager::instance().getViewport( &x, &y, &width, &height );
		D3DXMATRIX matInverseViewProj;
		D3DXMATRIX matViewPort;
		D3DXMATRIX matInverseViewPort;
		D3DXMatrixIdentity( &matViewPort );
		matViewPort._11 = static_cast<float>( width )/2.0f;
		matViewPort._22 = static_cast<float>( -height )/2.0f;
		matViewPort._41 = static_cast<float>( width )/2.0f;
		matViewPort._42 = static_cast<float>( height )/2.0f;
		D3DXMatrixInverse( &matInverseViewPort, NULL, &matViewPort );
		
		D3DXMatrixInverse( &matInverseViewProj, NULL, &viewProj );
		
		D3DXMATRIX matITemp =  matInverseViewPort * matInverseViewProj; 

		D3DXVECTOR3 begin( static_cast<float>(m.x()), static_cast<float>(m.y()), 0.f);
		D3DXVec3TransformCoord( pOutBegin, &begin, &matITemp );

		D3DXVECTOR3 end( static_cast<float>(m.x()), static_cast<float>(m.y()), 1.f );
		D3DXVec3TransformCoord( pOutEnd, &end, &matITemp );

		//TRACE3( "( %f, %f, %f )\n", pOutEnd->x, pOutEnd->y, pOutEnd->z );
		return;
	}


	static void debug_draw( const  D3DXMATRIX &viewProj, const D3DXVECTOR3 &target )
	{
		
		using namespace GameLib::Input;
		using namespace GameLib::Graphics;
		using namespace GameLib::Math;
		
		if(true)
		{
			D3DXVECTOR3 vec3;
			ClickPos::getPos( &vec3, viewProj, 0.f );
			VertexBuffer line = VertexBuffer::create(2);
			Vertex *pV=line.lock();
			{
				pV[0].mPosition.set( vec3.x, vec3.y, vec3.z );
				pV[1].mPosition = Vector4( target.x, target.y, target.z );
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

		
		if(true){
			D3DXVECTOR3 b,e;
			getLine( &b, &e, viewProj );
			VertexBuffer line = VertexBuffer::create(2);
			Vertex *pV=line.lock();
			{
				pV[0].mPosition.set( b.x, b.y, b.z );
				pV[1].mPosition.set( e.x, e.y, e.z );
				pV[0].mNormal.set(0.f, 0.f, 0.f);
				pV[1].mNormal.set(0.f, 0.f, 0.f);
				pV[0].mColor = 0xffff0000;
				pV[1].mColor = 0xff00ff00;
			}
			line.unlock( &pV );
			Matrix34 wm;
			wm.setIdentity();
			GameLib::Graphics::Manager mngr = GameLib::Graphics::Manager::instance();
			mngr.setWorldMatrix(wm);
			mngr.setVertexBuffer( line );
			mngr.draw( 0, 1, PRIMITIVE_LINE );
		}
	}

	static bool getPosRayCastWorld( btVector3 *pOut, const btVector3 &cameraTarget, const  D3DXMATRIX &viewProj )
	{
		D3DXVECTOR3 dxStart,dxEnd;
		getLine( &dxStart, &dxEnd, viewProj );
		btDiscreteDynamicsWorld *pWorld = BulletPhysics::Manager::instance()->getWorldPtr();
		btVector3	btStart = toBtVector3(dxStart),
					btEnd   = toBtVector3(dxEnd);
		
		btCollisionWorld::ClosestConvexResultCallback cb( btStart, btEnd );
		cb.m_collisionFilterMask = btBroadphaseProxy::StaticFilter;
		btTransform from, to;
		from.setIdentity();
		from.setOrigin(btStart);
		to.setIdentity();
		to.setOrigin(btEnd);
		
		btSphereShape sphere(0.2f);		
		BulletPhysics::Manager::instance()->getWorldPtr()->convexSweepTest( &sphere, from, to, cb );
		
		if (cb.hasHit())
		{

			btScalar minFraction  = cb.m_closestHitFraction;//btMax(btScalar(0.3),cb.m_closestHitFraction);
			pOut->setInterpolate3( from.getOrigin(), to.getOrigin(), minFraction);
			return true;
		}
		return false;
	}
private:
	ClickPos();
	~ClickPos();
	DISALLOW_COPY_AND_ASSIGN(ClickPos);
};


#endif//__CLICKPOS_H__