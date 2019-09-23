#ifndef __BTCOLLISIONOBJECTDRAWER_H__
#define __BTCOLLISIONOBJECTDRAWER_H__

#include"MMD/MMDMacro.h"
class btCollisionObject;

namespace BulletPhysics {

class BtCollisionObjectDrawer{
public:
	//static void init();
	//static void release();
	static void draw( const btCollisionObject *pObj, unsigned int color = 0xff000000 );
private:
	BtCollisionObjectDrawer();
	~BtCollisionObjectDrawer();
	DISALLOW_COPY_AND_ASSIGN(BtCollisionObjectDrawer);
	//static void drawSphere( const btTransform &btWorld, btCollisionShape *pShape, unsigned int color );
	//static void drawCapsuel( const btTransform &btWorld, btCollisionShape *pShape, unsigned int color );
	//static void drawBox( const btTransform &btWorld, btCollisionShape *pShape, unsigned int color );
	//static void drawCone( const btTransform &btWorld, btCollisionShape *pShape, unsigned int color );
	//static void drawCylinder( const btTransform &btWorld, btCollisionShape *pShape, unsigned int color );

	/*static VertexBuffer m_sBox;
	static VertexBuffer m_sSphere;
	static VertexBuffer m_sCapsule;
	static VertexBuffer m_sCone;
	static VertexBuffer m_sCylinder;*/
};
}
#endif//__BTCOLLISIONOBJECTDRAWER_H__
