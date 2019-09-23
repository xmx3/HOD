#ifndef __BOXMESH_H__
#define __BOXMESH_H__

#include"MMD/MMDMacro.h"
#include"SegaTypeHelper.h"
#include<GameLib/Graphics/Manager.h>
#include<btBulletCollisionCommon.h>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/IndexBuffer.h>
#include<GameLib/Graphics/Vertex.h>
#include<GameLib/Math/Matrix34.h>
#include<GameLib/Graphics/Texture.h>
#include<assert.h>

class BoxMesh {
public:
	BoxMesh()
	{
		using namespace GameLib::Graphics;

		mVertexBuffer = VertexBuffer::create( 8 ); //8頂点の頂点バッファ
		Vertex* v = mVertexBuffer.lock(); //書き込みポインタを得る
		//位置を入れる
		v[ 0 ].mPosition.set( -0.5f, -0.5f, -0.5f );
		v[ 1 ].mPosition.set( -0.5f, -0.5f, 0.5f );
		v[ 2 ].mPosition.set( -0.5f, 0.5f, -0.5f );
		v[ 3 ].mPosition.set( -0.5f, 0.5f, 0.5f );
		v[ 4 ].mPosition.set( 0.5f, -0.5f, -0.5f );
		v[ 5 ].mPosition.set( 0.5f, -0.5f, 0.5f );
		v[ 6 ].mPosition.set( 0.5f, 0.5f, -0.5f );
		v[ 7 ].mPosition.set( 0.5f, 0.5f, 0.5f );
		//法線を入れる。斜めに出ている法線にしてみる。長さはだいたい1
		v[ 0 ].mNormal.set( -0.57f, -0.57f, -0.57f );
		v[ 1 ].mNormal.set( -0.57f, -0.57f, 0.57f );
		v[ 2 ].mNormal.set( -0.57f, 0.57f, -0.57f );
		v[ 3 ].mNormal.set( -0.57f, 0.57f, 0.57f );
		v[ 4 ].mNormal.set( 0.57f, -0.57f, -0.57f );
		v[ 5 ].mNormal.set( 0.57f, -0.57f, 0.57f );
		v[ 6 ].mNormal.set( 0.57f, 0.57f, -0.57f );
		v[ 7 ].mNormal.set( 0.57f, 0.57f, 0.57f );
		//頂点カラーを入れる(ライティングの効果を見たいので真っ白
		for ( int i = 0; i < 8; ++i ){
			v[ i ].mColor = 0xffffffff;
		}
		//テクスチャ座標を入れる(適当)
		v[ 0 ].mUv.set( 0.f, 0.f );
		v[ 1 ].mUv.set( 0.f, 1.f );
		v[ 2 ].mUv.set( 1.f, 0.f );
		v[ 3 ].mUv.set( 1.f, 1.f );
		v[ 4 ].mUv.set( 0.f, 0.f );
		v[ 5 ].mUv.set( 0.f, 1.f );
		v[ 6 ].mUv.set( 1.f, 0.f );
		v[ 7 ].mUv.set( 1.f, 1.f );
		//書き終わったら閉じる
		mVertexBuffer.unlock( &v );

		//-------------インデクスバッファを作る--------------------
		//3インデクスで三角形一つなので、インデクスバッファのサイズは普通3の倍数になる
		mIndexBuffer = IndexBuffer::create( 36 ); //36頂点のインデクスバッファ
		unsigned short indices[ 36 ] = {
			0, 1, 3, 3, 2, 0,
			4, 6, 7, 7, 5, 4,
			0, 4, 5, 5, 1, 0,
			2, 3, 7, 7, 6, 2,
			7, 3, 1, 1, 5, 7,
			2, 6, 4, 4, 0, 2,
		};
		unsigned short* iBuffer = mIndexBuffer.lock();
		for ( int i = 0; i < 36; ++i ){
			iBuffer[ i ] = indices[ i ];
		}
		mIndexBuffer.unlock( &iBuffer );

	}
	~BoxMesh()
	{}

	void draw( const btTransform &btMat, const btVector3 &halfExtensions, unsigned int color=0xffffffff ) const {
		float a;
		GameLib::Math::Vector3 rgb;
		rgb.set(
			static_cast<float>( ( (color & 0x00ff0000) >> 16 ) ) / 255.f,
			static_cast<float>( ( (color & 0x0000ff00) >> 8 ) ) / 255.f, 
			static_cast<float>( ( (color & 0x000000ff) ) ) / 255.f );
		
		a=static_cast<float>( ( (color & 0xff000000) >> 24 ) ) / 255.f;
		
		
		GameLib::Math::Matrix34 w;
		GameLib::Math::Matrix33 s, r;
		s.setScaling( 2.f*halfExtensions.x(), 2.f*halfExtensions.y(), 2.f*halfExtensions.z() );
		r = toMatrix33( btMat.getBasis() );
		r *= s;
		const btVector3 & v = btMat.getOrigin();
		w.m00 = r.m00;
		w.m01 = r.m01;
		w.m02 = r.m02;
		w.m03 = v.x();
		w.m10 = r.m10;
		w.m11 = r.m11;
		w.m12 = r.m12;
		w.m13 = v.y();
		w.m20 = r.m20;
		w.m21 = r.m21;
		w.m22 = r.m22;
		w.m23 = v.z();
		GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
		gm.enableVertexBlend(false);
		gm.setWorldMatrix(w);


		const GameLib::Vector3 zero( 0.f, 0.f, 0.f );
		const GameLib::Vector3 one( 1.f, 1.f, 1.f );
		gm.setAmbientColor( rgb );
		gm.setDiffuseColor( one );
		gm.setSpecularColor( zero );
		gm.setEmissionColor( zero );
		gm.setSpecularSharpness( 0.f );
		gm.setTransparency( a );

		gm.setVertexBuffer( mVertexBuffer );
		gm.setIndexBuffer( mIndexBuffer );
		gm.setTexture( 0 );
		gm.drawIndexed( 0, 12 );
	}

	void draw( const btCollisionObject *obj, unsigned int color=0xffffffff ) const {
		if( obj->getCollisionShape()->getShapeType() != BOX_SHAPE_PROXYTYPE ){
			assert(false);
			return;
		}

		float a;
		GameLib::Math::Vector3 rgb;
		rgb.set(
			static_cast<float>( ( (color & 0x00ff0000) >> 16 ) ) / 255.f,
			static_cast<float>( ( (color & 0x0000ff00) >> 8 ) ) / 255.f, 
			static_cast<float>( ( (color & 0x000000ff) ) ) / 255.f );
		
		a=static_cast<float>( ( (color & 0xff000000) >> 24 ) ) / 255.f;

		const btVector3 &halfExtensions = static_cast<const btBoxShape*>( obj->getCollisionShape() )->getHalfExtentsWithMargin();
		GameLib::Math::Matrix34 w;
		GameLib::Math::Matrix33 s, r;
		s.setScaling( 2.f*halfExtensions.x(), 2.f*halfExtensions.y(), 2.f*halfExtensions.z() );
		r = toMatrix33( obj->getWorldTransform().getBasis() );
		r *= s;
		const btVector3 & v = obj->getWorldTransform().getOrigin();
		w.m00 = r.m00;
		w.m01 = r.m01;
		w.m02 = r.m02;
		w.m03 = v.x();
		w.m10 = r.m10;
		w.m11 = r.m11;
		w.m12 = r.m12;
		w.m13 = v.y();
		w.m20 = r.m20;
		w.m21 = r.m21;
		w.m22 = r.m22;
		w.m23 = v.z();
		GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
		gm.enableVertexBlend(false);
		gm.setWorldMatrix(w);

		const GameLib::Vector3 zero( 0.f, 0.f, 0.f );
		const GameLib::Vector3 one( 1.f, 1.f, 1.f );
		gm.setAmbientColor( one );
		gm.setDiffuseColor( rgb );
		gm.setSpecularColor( zero );
		gm.setEmissionColor( zero );
		gm.setSpecularSharpness( 0.f );
		gm.setTransparency( a );

		gm.setVertexBuffer( mVertexBuffer );
		gm.setIndexBuffer( mIndexBuffer );
		gm.setTexture( 0 );
		gm.drawIndexed( 0, 12 );
	}
private:
	DISALLOW_COPY_AND_ASSIGN(BoxMesh);
	GameLib::Graphics::VertexBuffer mVertexBuffer;
	GameLib::Graphics::IndexBuffer mIndexBuffer;
};
#endif//__BOXMESH_H__