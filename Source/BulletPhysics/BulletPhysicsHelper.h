#ifndef __BULLETPHYSICSHELPER__
#define __BULLETPHYSICSHELPER__
#include <d3dx9.h>
#include <btBulletDynamicsCommon.h>
#include <GameLib/Graphics/VertexBuffer.h>
#include <GameLib/Graphics/IndexBuffer.h>
#include<GameLib/Graphics/Vertex.h>
#include<GameLib/GameLib.h>
#include<cassert>

namespace BulletPhysicsHelper {

static btCollisionShape* createBvhTriangleMeshShape(
	GameLib::Graphics::VertexBuffer vb,
	GameLib::Graphics::IndexBuffer ib,
	int offset,
	int primitiveNumber,
	const float &scaleX,
	const float &scaleY,
	const float &scaleZ )
{
	btTriangleMesh *trimesh = new btTriangleMesh();
	GameLib::Graphics::Vertex* vertices = vb.lock();
	unsigned short* indieces = ib.lock();
	for(int i=offset, numIndex=offset+primitiveNumber*3; i<numIndex; i+=3)
	{
		assert( ((numIndex)%3)==0 );
		
		unsigned short i0 = indieces[i];
		unsigned short i1 = indieces[i+1];
		unsigned short i2 = indieces[i+2];
		btVector3 v0(  vertices[i0].mPosition.x*scaleX,  vertices[i0].mPosition.y*scaleY,  vertices[i0].mPosition.z*scaleZ );
		btVector3 v1(  vertices[i1].mPosition.x*scaleX,  vertices[i1].mPosition.y*scaleY,  vertices[i1].mPosition.z*scaleZ );
		btVector3 v2(  vertices[i2].mPosition.x*scaleX,  vertices[i2].mPosition.y*scaleY,  vertices[i2].mPosition.z*scaleZ );

		//左手座標から右手
		trimesh->addTriangle(v0,v2,v1);
		//trimesh->addTriangle(v0,v1,v2);
	}
	vb.unlock(&vertices);
	ib.unlock(&indieces);

	btCollisionShape *pShape = new btBvhTriangleMeshShape( trimesh, true );
	return pShape;
}



//頂点数を減少させて、凸型メッシュ状RigidBodyを作成
static btRigidBody* createConvexHullShapeRigidBody(
	GameLib::Graphics::VertexBuffer vb,
	GameLib::Graphics::IndexBuffer ib,
	const float &mass=0 );

//三角形メッシュ状RigidBodyを作成
//http://www.bulletphysics.com/Bullet/BulletFull/classbtBvhTriangleMeshShape.html
//The btBvhTriangleMeshShape is a static-triangle mesh shape with several optimizations,
//such as bounding volume hierarchy and cache friendly traversal for PlayStation 3 Cell SPU.
static btRigidBody* createBvhTriangleMeshShapeRigidBody(
	GameLib::Graphics::VertexBuffer vb,
	GameLib::Graphics::IndexBuffer ib,
	const float &scaleX=1.f,
	const float &scaleY=1.f,
	const float &scaleZ=1.f );
	
//三角形メッシュ状RigidBodyを作成
//http://www.bulletphysics.com/Bullet/BulletFull/classbtBvhTriangleMeshShape.html
//The btBvhTriangleMeshShape is a static-triangle mesh shape with several optimizations,
//such as bounding volume hierarchy and cache friendly traversal for PlayStation 3 Cell SPU.
//memo ここに摩擦力とか設定。すべる床とか
static btRigidBody* createBvhTriangleMeshShapeRigidBody(
	GameLib::Graphics::VertexBuffer vb,
	GameLib::Graphics::IndexBuffer ib,
	int offset,
	int primitiveNumber,
	const float &scaleX,
	const float &scaleY,
	const float &scaleZ )
{
	//0以外サポートしてない
	static const float mass=0.f;
	
	btCollisionShape *shape = 
		createBvhTriangleMeshShape( vb, ib, offset, primitiveNumber, scaleX, scaleY, scaleZ );
	
	//btBvhTriangleMeshShape* bvhTriShape = dynamic_cast<btBvhTriangleMeshShape*>(shape);
	//bvhTriShape->buildOptimizedBvh();
	//btTriangleMesh *newTriMesh = dynamic_cast<btTriangleMesh*>(bvhTriShape->getMeshInterface());
	//int oldNum = trimesh->getNumTriangles();
	//int n=newTriMesh->getNumTriangles();
	
	// 慣性テンソルの計算
	btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
	if( mass != 0.0f )	shape->calculateLocalInertia( mass, btv3LocalInertia );

	// MotionStateを作成する。剛体の姿勢制御をするもの	
	btTransform trGroundTransform;
	trGroundTransform.setIdentity();
	btMotionState *pMotionState = new btDefaultMotionState( trGroundTransform );

	// 剛体を作成する
	// 質量 0.0、慣性テンソル 0.0 ならこの剛体は動かない
	btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, pMotionState, shape, btv3LocalInertia );
	btRigidBody	*pRigidBody = new btRigidBody( rbInfo );
	
	return pRigidBody;
}


//const float *verticesは左手座標から右手座標に変換される
static btRigidBody* createBvhTriangleMeshShapeRigidBody(
	const float *vertices,
	const int &arrayNum );



static btRigidBody* createSphere(
	const btVector3 &pos,
	const btVector3 &velocity,
	const float &mass,
	const float &radius );

static btRigidBody* createRigidBody(const float &mass, const btTransform &trans, btCollisionShape* pShape )
{
	// 慣性テンソルの計算
	btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
	if( mass != 0.0f )	pShape->calculateLocalInertia( mass, btv3LocalInertia );

	// MotionStateを作成する。剛体の姿勢制御をするもの	
	btMotionState *pMotionState = new btDefaultMotionState( trans );

	// 剛体を作成する
	// 質量 0.0、慣性テンソル 0.0 ならこの剛体は動かない
	btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, pMotionState, pShape, btv3LocalInertia );
	btRigidBody	*pRigidBody = new btRigidBody( rbInfo );
	
	return pRigidBody;
}


inline static D3DXMATRIX toDxMatrix(const btMatrix3x3 &inMatrix) {
	return D3DXMATRIX( inMatrix[0][0],
					   inMatrix[1][0],
					   inMatrix[2][0],
								  0.f,
					   inMatrix[0][1],
					   inMatrix[1][1],
					   inMatrix[2][1],
								  0.f,
					   inMatrix[0][2],
					   inMatrix[1][2],
					   inMatrix[2][2],
								  0.f,
								  0.f,
								  0.f,
								  0.f,
								  1.f );//回転のみだからここ0でいいような

	//D3DXMATRIX outMatrix;
	//D3DXMatrixIdentity(&outMatrix);

	//outMatrix._11 = inMatrix[0][0];
	//outMatrix._12 = inMatrix[1][0];
	//outMatrix._13 = inMatrix[2][0];

	//outMatrix._21 = inMatrix[0][1];
	//outMatrix._22 = inMatrix[1][1];
	//outMatrix._23 = inMatrix[2][1];

	//outMatrix._31 = inMatrix[0][2];
	//outMatrix._32 = inMatrix[1][2];
	//outMatrix._33 = inMatrix[2][2];

	//return outMatrix;
}

inline static D3DXMATRIX toDxMatrix(const btTransform &bttr ) {
	const btMatrix3x3 &basis = bttr.getBasis();
	const btVector3 &vec3 = bttr.getOrigin();
	return D3DXMATRIX(
					   basis[0][0],
					   basis[1][0],
					   basis[2][0],
							   0.f,
					   basis[0][1],
					   basis[1][1],
					   basis[2][1],
							   0.f,
					   basis[0][2],
					   basis[1][2],
					   basis[2][2],
							   0.f,
						  vec3.x(),
						  vec3.y(),
						  vec3.z(),
						       1.f );

	//D3DXMATRIX outMatrix;
	//D3DXMatrixIdentity(&outMatrix);

	//outMatrix._11 = basis[0][0];
	//outMatrix._12 = basis[1][0];
	//outMatrix._13 = basis[2][0];

	//outMatrix._21 = basis[0][1];
	//outMatrix._22 = basis[1][1];
	//outMatrix._23 = basis[2][1];

	//outMatrix._31 = basis[0][2];
	//outMatrix._32 = basis[1][2];
	//outMatrix._33 = basis[2][2];

	//outMatrix._41 = vec3.getX();
	//outMatrix._42 = vec3.getY();
	//outMatrix._43 = vec3.getZ();

	//return outMatrix;
}



inline static btMatrix3x3 toBtMatrix3x3(const D3DXMATRIX &inMatrix) {
	return btMatrix3x3( 
						inMatrix._11, 
						inMatrix._21,
						inMatrix._31,
						inMatrix._12,
						inMatrix._22,
						inMatrix._32,
						inMatrix._13,
						inMatrix._23,
						inMatrix._33 );

	//btMatrix3x3 outMatrix;
	//outMatrix.setIdentity();

	//outMatrix[0][0] = inMatrix._11;
	//outMatrix[1][0] = inMatrix._12;
	//outMatrix[2][0] = inMatrix._13;

	//outMatrix[0][1] = inMatrix._21;
	//outMatrix[1][1] = inMatrix._22;
	//outMatrix[2][1] = inMatrix._23;

	//outMatrix[0][2] = inMatrix._31;
	//outMatrix[1][2] = inMatrix._32;
	//outMatrix[2][2] = inMatrix._33;

	//return outMatrix;
}

inline static btTransform toBtTransform( const D3DXMATRIX &inMatrix) {
	return btTransform( 
		btMatrix3x3( 
						inMatrix._11, 
						inMatrix._21,
						inMatrix._31,
						inMatrix._12,
						inMatrix._22,
						inMatrix._32,
						inMatrix._13,
						inMatrix._23,
						inMatrix._33 ),
		btVector3( inMatrix._41, inMatrix._42, inMatrix._43 ) 
	);
	//btTransform outBttr;
	//outBttr.setIdentity();
	//btMatrix3x3 btMatBasis = toBtMatrix3x3( inMatrix );
	//outBttr.setBasis( btMatBasis );
	//outBttr.setOrigin( btVector3( inMatrix._41, inMatrix._42, inMatrix._43 ) );
	//return outBttr;
}

inline static btVector3 toBtVector3( const D3DXVECTOR3 &v) {
	return btVector3(v.x, v.y, v.z);
}

inline static btVector3 toBtVector3( const D3DXVECTOR4 &v) {
	return btVector3(v.x, v.y, v.z);
}

inline static D3DXVECTOR3 toDxVec3( const btVector3 &v){
	//assert( D3DXVECTOR3( reinterpret_cast<const float*>(&v) ) == D3DXVECTOR3( v.x(), v.y(), v.z() ) );
	return D3DXVECTOR3( reinterpret_cast<const float*>(&v) );
}

inline static D3DXVECTOR4 toDxVec4( const btVector3 &v){
	//assert( D3DXVECTOR3( reinterpret_cast<const float*>(&v) ) == D3DXVECTOR3( v.x(), v.y(), v.z() ) );
	return D3DXVECTOR4( reinterpret_cast<const float*>(&v) );
}
static void deleteBvhTriangleMeshShape( void *p ) {
	btBvhTriangleMeshShape *pBvhms = static_cast<btBvhTriangleMeshShape*>(p);
	btTriangleMesh *triMesh = dynamic_cast<btTriangleMesh*>(pBvhms->getMeshInterface());
	SAFE_DELETE(triMesh);
	SAFE_DELETE(pBvhms);
}


}// end namespace BulletPhysicsHelper


using BulletPhysicsHelper::toBtMatrix3x3;
using BulletPhysicsHelper::toBtTransform;
using BulletPhysicsHelper::toBtVector3;
using BulletPhysicsHelper::toDxMatrix;
using BulletPhysicsHelper::toDxVec3;
using BulletPhysicsHelper::toDxVec4;

#endif//__BULLETPHYSICSHELPER__
