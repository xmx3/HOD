#include"BtCollisionObjectDrawer.h"
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Math/Matrix34.h>
#include"SegaTypeHelper.h"
#include"BulletPhysics/Manager.h"

#include<btBulletDynamicsCommon.h>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/Vertex.h>

namespace BulletPhysics {


using namespace GameLib::Graphics;
using namespace GameLib::Math;

//VertexBuffer BtCollisionObjectDrawer::m_sBox		= NULL;
//VertexBuffer BtCollisionObjectDrawer::m_sSphere	= NULL;
//VertexBuffer BtCollisionObjectDrawer::m_sCapsule	= NULL;
//VertexBuffer BtCollisionObjectDrawer::m_sCone		= NULL;
//VertexBuffer BtCollisionObjectDrawer::m_sCylinder	= NULL;
//
//void BtCollisionObjectDrawer::init(){
//	release();
//	static const float d = 1.0f; // ボックスの寸法
//	static const float r = 1.0f; // 球の半径
//	static const float r1 = r * 1.41421356f / 2;
//	static const float h = r / 2;
//	// 頂点
//	static float box[30][3] =
//	{
//		// ボックス
//		{  -d, -d, -d, },	// 0
//		{  -d, -d,  d, },
//		
//		{  -d, -d,  d, },
//		{  -d,  d,  d, },
//		
//		{  -d,  d,  d, },
//		{  -d,  d, -d, },
//		
//		{  -d,  d, -d, },
//		{   d, -d, -d, },	// 4
//		
//		{   d, -d, -d, },	// 4
//		{  -d, -d, -d, },
//		
//		{  -d, -d, -d, },
//		{  -d,  d, -d, },
//		
//		{  -d,  d, -d, },
//		{   d,  d, -d, },
//		
//		{   d,  d, -d, },
//		{   d, -d,  d, },	// 8
//		
//		{   d, -d,  d, },	// 8
//		{   d, -d, -d, },
//		
//		{   d, -d, -d, },
//		{   d,  d, -d, },
//		
//		{   d,  d, -d, },
//		{   d,  d,  d, },
//		
//		{   d,  d,  d, },
//		{  -d, -d,  d, },	// 12
//		
//		{  -d, -d,  d, },	// 12
//		{   d, -d,  d, },
//		
//		{   d, -d,  d, },
//		{   d,  d,  d, },
//		
//		{   d,  d,  d, },
//		{  -d,  d,  d, },
//	};
//	
//	static float sphere[52][3] =
//	{	
//		// 球
//		{   r, 0,   0, },	// 0
//		{  r1, 0,  r1, },
//		
//		{  r1, 0,  r1, },
//		{   0, 0,   r, },
//		
//		{   0, 0,   r, },
//		{ -r1, 0,  r1, },
//		
//		{ -r1, 0,  r1, },
//		{  -r, 0,   0, },
//		
//		{  -r, 0,   0, },
//		{ -r1, 0, -r1, },
//		
//		{ -r1, 0, -r1, },
//		{   0, 0,  -r, },
//		
//		{   0, 0,  -r, },
//		{  r1, 0, -r1, },
//		
//		{  r1, 0, -r1, },
//		{   r, 0,   0, },
//		
//		{   r, 0,   0, },
//		{   r,   0, 0, },	// 9
//		
//		{   r,   0, 0, },	// 9
//		{  r1,  r1, 0, },
//		
//		{  r1,  r1, 0, },
//		{   0,   r, 0, },
//		
//		{   0,   r, 0, },
//		{ -r1,  r1, 0, },
//		
//		{ -r1,  r1, 0, },
//		{  -r,   0, 0, },
//		
//		{  -r,   0, 0, },
//		{ -r1, -r1, 0, },
//		
//		{ -r1, -r1, 0, },
//		{   0,  -r, 0, },
//		
//		{   0,  -r, 0, },
//		{  r1, -r1, 0, },
//		
//		{  r1, -r1, 0, },
//		{   r,   0, 0, },
//		
//		{   r,   0, 0, },
//		{  0,   0,   r, },	// 18
//		
//		{  0,   0,   r, },	// 18
//		{  0,  r1,  r1, },
//		
//		{  0,  r1,  r1, },
//		{  0,   r,   0, },
//		
//		{  0,   r,   0, },
//		{  0,  r1, -r1, },
//		
//		{  0,  r1, -r1, },
//		{  0,   0,  -r, },
//		
//		{  0,   0,  -r, },
//		{  0, -r1, -r1, },
//		
//		{  0, -r1, -r1, },
//		{  0,  -r,   0, },
//		
//		{  0,  -r,   0, },
//		{  0, -r1,  r1, },
//		
//		{  0, -r1,  r1, },
//		{  0,   0,   r, },
//	};
//	static float capsule[][3] =
//	{
//		// カプセル
//		{ -r,  h, 0, },		// 65
//		{ -r, -h, 0, },
//		{  r,  h, 0, },		// 67
//		{  r, -h, 0, },
//		{ 0, h,   -r, },	// 69
//		{ 0, -h,  -r, },
//		{ 0, h,   r, },		// 71
//		{ 0, -h,  r, },
//	
//	};	
//	static float cylinder[][3] =
//	{
//		// 円筒
//		{   r, r,   0, },	// 73
//		{  r1, r,  r1, },
//		{   0, r,   r, },
//		{ -r1, r,  r1, },
//		{  -r, r,   0, },
//		{ -r1, r, -r1, },
//		{   0, r,  -r, },
//		{  r1, r, -r1, },
//		{   r, r,   0, },
//
//		{   r, -r,   0, },	// 82
//		{  r1, -r,  r1, },
//		{   0, -r,   r, },
//		{ -r1, -r,  r1, },
//		{  -r, -r,   0, },
//		{ -r1, -r, -r1, },
//		{   0, -r,  -r, },
//		{  r1, -r, -r1, },
//		{   r, -r,   0, },
//	};
//
//
//	m_sBox		= VertexBuffer::create(30);	
//	Vertex *v=m_sBox.lock();
//	{
//		for(int i=0, num=m_sBox.vertexNumber(); i<num; ++i )
//		{
//			v[i].mPosition.set( box[i][0], box[i][1], box[i][2] );
//			v[i].mNormal.set(0.f, 0.f, 0.f);
//			v[i].mColor = 0xffffffff;
//			v[i].mUv.set(0.f, 0.f);
//		}
//	}
//	m_sBox.unlock(&v);
//
//	m_sSphere	= VertexBuffer::create(52);
//	v=m_sSphere.lock();
//	{
//		for(int i=0, num=m_sSphere.vertexNumber(); i<num; ++i )
//		{
//			v[i].mPosition.set( sphere[i][0], sphere[i][1], sphere[i][2] );
//			v[i].mNormal.set(0.f, 0.f, 0.f);
//			v[i].mColor = 0xffffffff;
//			v[i].mUv.set(0.f, 0.f);
//		}
//	}
//	m_sSphere.unlock(&v);
//	
//	//m_sCapsule	= VertexBuf;fer::create();
//	//m_sCone		= VertexBuffer::create();
//	//m_sCylinder	= VertexBuffer::create();
//}
//
//void BtCollisionObjectDrawer::release(){
//	m_sBox.release();
//	m_sSphere.release();
//	m_sCapsule.release();
//	m_sCone.release();
//	m_sCylinder.release();
//}

void BtCollisionObjectDrawer::draw(const btCollisionObject *pObj, unsigned int color )
{
	const btTransform & world= pObj->getWorldTransform();
	
	btCollisionShape const *pShape = pObj->getCollisionShape();
	btVector3 btColor;
	btColor.setX( static_cast<float>( ( (color & 0x00ff0000) >> 16 ) ) / 255.f  );
	btColor.setY( static_cast<float>( ( (color & 0x0000ff00) >> 8 ) ) / 255.f );
	btColor.setZ( static_cast<float>( ( (color & 0x000000ff) ) ) / 255.f );
	BulletPhysics::Manager::instance()->getWorldPtr()->debugDrawObject( world, pShape, btColor );
	
	//int type= pShape->getShapeType();
	//
	//btSphereShape;
	//btCapsuleShape cp(1,1);
	////cp.geth
	//btBoxShape;
	//btConeShape;
	//btCylinderShape;

	//switch(type){
	//case CAPSULE_SHAPE_PROXYTYPE:
	//	drawSphere( world, pShape, color);
	//	break;
	//case SPHERE_SHAPE_PROXYTYPE:
	//	drawSphere( world, pShape, color);
	//	break;	
	//case BOX_SHAPE_PROXYTYPE:
	//	break;
	//	
	//default:
	//	assert( false && "this type is not implemented." );
	//	break;
	//}
	//
}

//void BtCollisionObjectDrawer::drawSphere( const btTransform &btWorld, btCollisionShape *pShape, unsigned int color )
//{
//	btIDebugDraw *pBtDrawer = BulletPhysics::Manager::instance()->getDebugDrawerPtr();
//	btSphereShape *pSphere = dynamic_cast<btSphereShape*>(pShape);
//	btVector3 btColor;
//	btColor.setX( static_cast<float>( ( (color & 0x00ff0000) >> 16 ) ) / 255.f  );
//	btColor.setY( static_cast<float>( ( (color & 0x0000ff00) >> 8 ) ) / 255.f );
//	btColor.setZ( static_cast<float>( ( (color & 0x000000ff) ) ) / 255.f );
//	pBtDrawer->drawSphere( pSphere->getRadius(), btWorld, btColor );	
//}

}