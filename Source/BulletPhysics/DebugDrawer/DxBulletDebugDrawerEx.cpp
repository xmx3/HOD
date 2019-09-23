#include "DxBulletDebugDrawerEx.h"
#include <GameLib/Graphics/Manager.h>
#include <d3dx9.h>
#include <GameLib/Math/Matrix34.h>
#include<cassert>

namespace BulletPhysics {

CDxBulletDebugDrawerEx::CDxBulletDebugDrawerEx()
	:m_pVertex(NULL),
	mIndex(0),
	mBufferSize( 60000 ),//40byte*size
	mNumBuffers(0)
{
	mVertexBuffer = GameLib::Graphics::VertexBuffer::create(mBufferSize);
}

CDxBulletDebugDrawerEx::~CDxBulletDebugDrawerEx(){}

void CDxBulletDebugDrawerEx::drawLine(const btVector3& from, const btVector3& to, const btVector3& lineColor)
{

	if(mIndex>=mBufferSize){
		unlock();
		drawVertexBuffer();
		lock();
		++mNumBuffers;
		return;
	}
	assert(mIndex<mBufferSize);
	
	m_pVertex[mIndex].mPosition.set( from.x(), from.y(), from.z() );
	m_pVertex[mIndex].mNormal.set(1.f, 0.f, 0.f);
	m_pVertex[mIndex].mColor = D3DCOLOR_XRGB( BYTE(255*lineColor.x()), BYTE(255*lineColor.y()), BYTE(255*lineColor.z()) );
	++mIndex;
	
	assert(mIndex<mBufferSize);
	m_pVertex[mIndex].mPosition.set( to.x(), to.y(), to.z() );
	m_pVertex[mIndex].mNormal.set(0.f, 1.f, 0.f);	
	m_pVertex[mIndex].mColor = m_pVertex[0].mColor;
	++mIndex;
}

void CDxBulletDebugDrawerEx::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	// draw a line to represent the normal.  This only lasts one frame, and is hard to see.
	//   it might help to linger this drawn object onscreen for a while to make it more noticeable
	
	btVector3 const startPoint = PointOnB;
	btVector3 const endPoint = PointOnB + normalOnB * distance;
	
	drawLine( startPoint, endPoint, color );
}

void CDxBulletDebugDrawerEx::reportErrorWarning(const char* warningString)
{
	OutputDebugStringA( warningString );
}

void CDxBulletDebugDrawerEx::draw3dText(const btVector3& location, const char* textString)
{
	// not implemented
}

void CDxBulletDebugDrawerEx::setDebugMode(int debugMode)
{
	// not implemented, this class just draws everything all the time
}

int CDxBulletDebugDrawerEx::getDebugMode() const
{
	return -1; // draw everything
}

void CDxBulletDebugDrawerEx::lock() { 
	mIndex=0;
	assert(mIndex<mBufferSize);
	m_pVertex = mVertexBuffer.lock();
}
void CDxBulletDebugDrawerEx::unlock() { 
	mVertexBuffer.unlock(&m_pVertex);
}
void CDxBulletDebugDrawerEx::drawVertexBuffer() {
	GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
	//m.setLightingMode( GameLib::Graphics::LIGHTING_NONE );

	GameLib::Math::Matrix34 matI;
	matI.setIdentity();
	m.setWorldMatrix(matI);	
	m.setVertexBuffer(mVertexBuffer);
	m.draw(0, mIndex/2, GameLib::Graphics::PRIMITIVE_LINE );	
}

void CDxBulletDebugDrawerEx::drawWorld(btDiscreteDynamicsWorld *pWorld) {
  	mNumBuffers=0;
	lock();
	pWorld->debugDrawWorld();
	unlock();
	drawVertexBuffer();
}
}