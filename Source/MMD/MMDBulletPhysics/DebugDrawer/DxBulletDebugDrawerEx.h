#ifndef __DXBULLETDEBUGDRAWEREX_H__
#define __DXBULLETDEBUGDRAWEREX_H__
#include <btBulletDynamicsCommon.h>
#include "MMD/MMDMacro.h"
#include "GameLib/Graphics/VertexBuffer.h"
#include "GameLib/Graphics/Vertex.h"

namespace BulletPhysics {


//àÍâÒÇ≤Ç∆Ç…èëÇ≠ÇÒÇ≈ÇÕÇ»Ç≠ÇƒíôÇﬂÇƒÇ®Ç≠Drawer
class CDxBulletDebugDrawerEx : public btIDebugDraw
{
public:
	CDxBulletDebugDrawerEx();
	virtual ~CDxBulletDebugDrawerEx();
	// btIDebugDraw interface
	virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
	virtual void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);
	virtual void	reportErrorWarning(const char* warningString);
	virtual void	draw3dText(const btVector3& location,const char* textString);
	virtual void	setDebugMode(int debugMode);
	virtual int		getDebugMode() const;

	void initVertexBuffer( int numVerteices );

	void drawWorld(btDiscreteDynamicsWorld *pWorld);
private:
	DISALLOW_COPY_AND_ASSIGN(CDxBulletDebugDrawerEx);
	void lock();
	void unlock();
	void drawVertexBuffer();

	GameLib::Graphics::VertexBuffer mVertexBuffer;
	GameLib::Graphics::Vertex* m_pVertex;
	int mIndex;
	int mBufferSize;
	int mNumBuffers;
};

}
#endif//__DXBULLETDEBUGDRAWEREX_H__