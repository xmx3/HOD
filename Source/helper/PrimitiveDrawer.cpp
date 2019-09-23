#include"PrimitiveDrawer.h"
#include"BoxMesh.h"
#include"SphereMesh.h"
#include<assert.h>
#include<btBulletCollisionCommon.h>
#include<GameLib/GameLib.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/Vertex.h>

#include"BulletPhysics/DebugDrawer/BtCollisionObjectDrawer.h"
#include<d3dx9.h>
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"SegaTypeHelper.h"
namespace PrimitiveDrawer {
	
	void draw( const btCollisionObject* obj, unsigned int color, bool isWireFrame){
		static BoxMesh sBoxMesh;
		static SphereMesh sSphereMesh;

		IDirect3DDevice9* pDevice = GameLib::Graphics::Manager::instance().dxDevice();
		if( isWireFrame ){
			//フィルモード（塗りつぶしモード）の設定
			HRESULT hr = pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			assert( SUCCEEDED( hr ) );
		}

		switch( obj->getCollisionShape()->getShapeType()  ){
		case BOX_SHAPE_PROXYTYPE :
			sBoxMesh.draw(obj, color );
			break;
		case SPHERE_SHAPE_PROXYTYPE :
			sSphereMesh.draw( obj, color );
			break;
		case TRIANGLE_MESH_SHAPE_PROXYTYPE :
			BulletPhysics::BtCollisionObjectDrawer::draw(obj, color );
			break;
		default:
			assert(false && "not impl");
			break;
		}

		if( isWireFrame ){

			HRESULT hr = pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
			assert( SUCCEEDED( hr ) );
		}

	}

	void drawSphere( const btVector3 &pos, float radius, unsigned int color ){
		static SphereMesh sSphereMesh;
		sSphereMesh.draw( 
			btTransform( btMatrix3x3::getIdentity(), pos ),
			radius,
			color );
	}

	void drawSphere( const D3DXVECTOR3 &pos, float radius, unsigned int color ){
		static SphereMesh sSphereMesh;
		sSphereMesh.draw( 
			btTransform( btMatrix3x3::getIdentity(), toBtVector3(pos) ),
			radius,
			color );
	}

	void drawSphere( const GameLib::Vector3 &pos, float radius, unsigned int color ){
		static SphereMesh sSphereMesh;
		sSphereMesh.draw( 
			btTransform( btMatrix3x3::getIdentity(), toBtVector3(pos) ),
			radius,
			color );
	}

	void drawLine( const GameLib::Vector3 &p0,  const GameLib::Vector3 &p1, unsigned int color ){
		using namespace GameLib::Graphics;
		using namespace GameLib;
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
		VertexBuffer vb = VertexBuffer::create(2);

		Vertex* v = vb.lock(); //書き込みポインタを得る
		//位置を入れる
		v[ 0 ].mPosition.set( p0.x, p0.y, p0.z );
		v[ 1 ].mPosition.set( p1.x, p1.y, p1.z );
		v[ 0 ].mNormal.set( 0.f, 1.f, 0.f );
		v[ 1 ].mNormal.set( 0.f, 1.f, 0.f );
		//頂点カラーを入れる
		v[ 0 ].mColor = color;
		v[ 1 ].mColor = color;
		//テクスチャ座標を入れる(適当)
		//v[ 0 ].mUv.set( 0.f, 0.f );
		//v[ 1 ].mUv.set( 0.f, 1.f );
		//書き終わったら閉じる
		vb.unlock( &v );

		//使うデータを指定する
		m.setTexture(0);
		m.enableVertexBlend(false);
		Matrix34 w;
		w.setIdentity();
		m.setWorldMatrix(w); 
		m.setVertexBuffer( vb );

		m.draw( 0, 1, PRIMITIVE_LINE );

	}
}