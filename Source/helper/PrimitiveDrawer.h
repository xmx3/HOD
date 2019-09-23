#ifndef __PRIMITIVEDRAWER_H__
#define __PRIMITIVEDRAWER_H__
namespace GameLib { namespace Math {
class Vector3;
} } //GameLib::Math
struct D3DXVECTOR3;
class btVector3;
class btCollisionObject;

namespace PrimitiveDrawer {
	void draw( const btCollisionObject* obj, unsigned int color=0xffffffff, bool isWireFrame=false );

	void drawSphere( const btVector3 &pos, float radius=1.f, unsigned int color=0xffffffff );

	void drawSphere( const D3DXVECTOR3 &pos, float radius=1.f, unsigned int color=0xffffffff );

	void drawSphere( const GameLib::Math::Vector3 &pos, float radius=1.f, unsigned int color=0xffffffff );

	void drawLine( const GameLib::Math::Vector3 &p0,  const GameLib::Math::Vector3 &p1, unsigned int color=0xffffffff );
}
#endif