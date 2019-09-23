#include "DxBulletDebugDrawer.h"
#include <GameLib/Graphics/Manager.h>
#include <GameLib/Graphics/Vertex.h>
#include "GameLib/Graphics/VertexBuffer.h"
#include <d3dx9.h>
#include <GameLib/Math/Matrix34.h>
#include <GameLib/Graphics/Texture.h>
#include <cassert>

namespace BulletPhysics {

void CDxBulletDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& lineColor)
{
	GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
	HRESULT hr;
	//m.setLightingMode( GameLib::Graphics::LIGHTING_NONE );

	//DWORD oldLightingState;
	//hr=m.dxDevice()->GetRenderState( D3DRS_LIGHTING, &oldLightingState );
	//assert( SUCCEEDED(hr) );
	//// disable lighting for the lines
	//hr=m.dxDevice()->SetRenderState( D3DRS_LIGHTING, FALSE );
	//assert( SUCCEEDED(hr) );

	GameLib::Graphics::Vertex verts[2];
	
	verts[0].mPosition.set( from.x(), from.y(), from.z() );
	verts[0].mNormal.set(0.f, 1.f, 0.f);
	verts[0].mColor = D3DCOLOR_XRGB( BYTE(255*lineColor.x()), BYTE(255*lineColor.y()), BYTE(255*lineColor.z()) );
	verts[1].mPosition.set( to.x(), to.y(), to.z() );
	verts[1].mNormal.set(0.f, 1.f, 0.f);	
	verts[1].mColor = verts[0].mColor;
	
	//D3DXMATRIX world;
	//D3DXMatrixIdentity(&world);
	//m.dxDevice()->SetTransform(D3DTS_WORLD, &world);
	GameLib::Math::Matrix34 matI;
	matI.setIdentity();
	m.setWorldMatrix(matI);	
	m.setTexture(0);
	//GameLib::Graphics::VertexBuffer dummy = GameLib::Graphics::VertexBuffer::create(1);
	//m.setVertexBuffer(dummy);
	//何も描画しないでここまでくるとassertで止まる。
	//ワールド行列とか更新したいのでdraw()呼びたい
	m.draw(0, 0 );
	hr=m.dxDevice()->DrawPrimitiveUP( D3DPT_LINELIST, 1, verts, sizeof(GameLib::Graphics::Vertex) );
	assert( SUCCEEDED(hr) );
	
	// restore original lighting state
	//hr=m.dxDevice()->SetRenderState( D3DRS_LIGHTING, oldLightingState );
	//assert( SUCCEEDED(hr) );
}

void CDxBulletDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	// draw a line to represent the normal.  This only lasts one frame, and is hard to see.
	//   it might help to linger this drawn object onscreen for a while to make it more noticeable
	
	btVector3 const startPoint = PointOnB;
	btVector3 const endPoint = PointOnB + normalOnB * distance;
	
	drawLine( startPoint, endPoint, color );
}

void CDxBulletDebugDrawer::reportErrorWarning(const char* warningString)
{
	OutputDebugStringA( warningString );
}

void CDxBulletDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
	// not implemented
}

void CDxBulletDebugDrawer::setDebugMode(int debugMode)
{
	// not implemented, this class just draws everything all the time
}

int CDxBulletDebugDrawer::getDebugMode() const
{
	return -1; // draw everything
}
}