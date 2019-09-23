#include"BulletPhysicsHelper.h"
#include<GameLib/Graphics/Vertex.h>
#include<BulletCollision/CollisionShapes/btShapeHull.h>

namespace BulletPhysicsHelper {

	//pObjにNULLを入れたいので参照。
////ダブルポインタだとわざわざ、ダブルポインタにしなければならないので自然に使えない
//inline static void deleteSafely( btCollisionObject* &pObj ){
//	btRigidBody	*pRigidBody = btRigidBody::upcast( pObj );
//
//	if( pRigidBody && pRigidBody->getMotionState() )
//	{
//		btMotionState* pMotion = pRigidBody->getMotionState();
//		SAFE_DELETE(pMotion);
//	}
//
//	if( pObj->getCollisionShape() ) {
//		btCollisionShape* pShape = pObj->getCollisionShape();
//			
//		//メッシュデータがある場合
//		//btTriangleMeshShape* triMeshShape = dynamic_cast<btTriangleMeshShape*>(pShape);
//		//if( triMeshShape ) {
//		//	if( triMeshShape->getMeshInterface() ) {
//		//		btTriangleMesh *triMesh = dynamic_cast<btTriangleMesh*>(triMeshShape->getMeshInterface());
//		//		SAFE_DELETE(triMesh);
//		//	}
//		//}
//			
//		SAFE_DELETE(pShape);
//	}
//
//	SAFE_DELETE(pObj);
//}
//
////pObjにNULLを入れたいので参照。
////ダブルポインタだとわざわざ、ダブルポインタにしなければならないので自然に使えない
//inline static void deleteSafely( btRigidBody* &pRigidBody ){
//	if( pRigidBody && pRigidBody->getMotionState() )
//	{
//		btMotionState* pMotion = pRigidBody->getMotionState();
//		SAFE_DELETE(pMotion);
//	}
//
//	if( pRigidBody->getCollisionShape() ) {
//		btCollisionShape* pShape = pRigidBody->getCollisionShape();
//			
//		//メッシュデータがある場合
//		//btTriangleMeshShape* triMeshShape = dynamic_cast<btTriangleMeshShape*>(pShape);
//		//if( triMeshShape ) {
//		//	if( triMeshShape->getMeshInterface() ) {
//		//		btTriangleMesh *triMesh = dynamic_cast<btTriangleMesh*>(triMeshShape->getMeshInterface());
//		//		SAFE_DELETE(triMesh);
//		//	}
//		//}
//			
//		SAFE_DELETE(pShape);
//	}
//
//	SAFE_DELETE(pRigidBody);
//}


static btRigidBody* createConvexHullShapeRigidBody(
		GameLib::Graphics::VertexBuffer vb,
		GameLib::Graphics::IndexBuffer ib,
		const float &mass )
{
	btTriangleMesh trimesh;
	GameLib::Graphics::Vertex* vertices = vb.lock();
	unsigned short* indieces = ib.lock();
	for(int i=0, numIndex=ib.indexNumber(); i<numIndex; i+=3)
	{
		unsigned short i0 = indieces[i];
		unsigned short i1 = indieces[i+1];
		unsigned short i2 = indieces[i+2];
		btVector3 v0(  vertices[i0].mPosition.x,  vertices[i0].mPosition.y,  vertices[i0].mPosition.z );
		btVector3 v1(  vertices[i1].mPosition.x,  vertices[i1].mPosition.y,  vertices[i1].mPosition.z );
		btVector3 v2(  vertices[i2].mPosition.x,  vertices[i2].mPosition.y,  vertices[i2].mPosition.z );
		//左手座標系から右手座標へ
		trimesh.addTriangle(v0,v2,v1);
	}
	vb.unlock(&vertices);
	ib.unlock(&indieces);

	
	btConvexTriangleMeshShape  tmpConvexShape(&trimesh);
	
	//create a hull approximation
	btShapeHull hull(&tmpConvexShape);
	btScalar margin = tmpConvexShape.getMargin();
	hull.buildHull(margin);
	//tmpConvexShape.setUserPointer(hull);
	
	//AllocConsole();
	//FILE* fp;
	//freopen_s(&fp, "CONOUT$","w", stdout);
	//freopen_s(&fp, "CONIN$", "r", stdin);

	//printf("old numTriangles= %d\n", trimesh.getNumTriangles() );
	//printf("old numIndices = %d\n", ib.indexNumber() );
	//printf("old numVertices = %d\n", vb.vertexNumber());

	//printf("reducing vertices by creating a convex hull\n");

	//printf("new numTriangles = %d\n", hull.numTriangles ());
	//printf("new numIndices = %d\n", hull.numIndices ());
	//printf("new numVertices = %d\n", hull.numVertices ());

	//FreeConsole();
	
	btConvexHullShape* convexHullShape = new btConvexHullShape();
	for (int i=0; i<hull.numVertices(); ++i)
	{
		convexHullShape->addPoint(hull.getVertexPointer()[i]);	
	}
	
	// 慣性テンソルの計算
	btVector3 btv3LocalInertia(0.f, 0.f, 0.f);
	if( mass != 0.0f )	convexHullShape->calculateLocalInertia( mass, btv3LocalInertia );

	// MotionStateを作成する。剛体の姿勢制御をするもの	
	btTransform trGroundTransform;
	trGroundTransform.setIdentity();
	btMotionState *pMotionState = new btDefaultMotionState( trGroundTransform );

	// 剛体を作成する
	// 質量 0.0、慣性テンソル 0.0 ならこの剛体は動かない
	btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, pMotionState, convexHullShape, btv3LocalInertia );
	btRigidBody	*pRigidBody = new btRigidBody( rbInfo );
	
	return pRigidBody;
}
/*
static btRigidBody* createBvhTriangleMeshShapeRigidBody(
		GameLib::Graphics::VertexBuffer vb,
		GameLib::Graphics::IndexBuffer ib,
		int offset,
		int primitiveNumber,
		const float &scaleX,
		const float &scaleY,
		const float &scaleZ )
{
	//引数に入れるべきか迷った
	static const float mass=0.f; 

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

	btCollisionShape *shape = new btBvhTriangleMeshShape( trimesh, true );
	
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
*/
static btRigidBody* createBvhTriangleMeshShapeRigidBody(
		GameLib::Graphics::VertexBuffer vb,
		GameLib::Graphics::IndexBuffer ib,
		const float &scaleX,
		const float &scaleY,
		const float &scaleZ )
{
	assert( (ib.indexNumber()%3)==0 && "ptimitiveType must be Triangle." );
	return createBvhTriangleMeshShapeRigidBody( vb, ib, 0, ib.indexNumber()/3, scaleX, scaleY, scaleZ );
}

btRigidBody* createSphere( const btVector3 &pos, const btVector3 &velocity, const float &mass, const float &radius )
{
	btCollisionShape* pShape = NULL;
	pShape = new btSphereShape(radius);

	bool isDynamic = (mass != 0.f);
	// 慣性テンソルの計算
	btVector3 localInertia(0,0,0);
	if (isDynamic) {
		pShape->calculateLocalInertia(mass, localInertia);
	}
	// モーションステートを作成
	btTransform matAttiude;
	matAttiude.setIdentity();
	matAttiude.setOrigin(pos);
	btDefaultMotionState* pMotionState = new btDefaultMotionState( matAttiude );

	// RigidBodyを生成
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, pMotionState, pShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	body->setLinearVelocity(velocity);

	return body;
	//pBtWorld_->addRigidBody(body);
}
/*
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
*/
static btRigidBody* createBvhTriangleMeshShapeRigidBody(
		const float *vertices,
		const int &arrayNum )
{
	float mass=0.f;

	btTriangleMesh *trimesh = new btTriangleMesh();
	for(int i=0; i<arrayNum; i+=9)
	{
		btVector3 v0(  vertices[i+0], vertices[i+1], vertices[i+2] );
		btVector3 v1(  vertices[i+3], vertices[i+4], vertices[i+5] );
		btVector3 v2(  vertices[i+6], vertices[i+7], vertices[i+8] );

		trimesh->addTriangle(v0,v2,v1);
	}

	btCollisionShape *shape = new btBvhTriangleMeshShape( trimesh, true );
	
	btTransform transform;
	transform.setIdentity();

	btRigidBody	*pRigidBody = createRigidBody( mass, transform, shape);

	return pRigidBody;
}

}//end namespace BulletPhsicsHelper