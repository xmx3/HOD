#ifndef __SEGABULLETDEBUGDRAWER__
#define __SEGABULLETDEBUGDRAWER__
#include "btBulletDynamicsCommon.h"
#include "MMD/MMDMacro.h"
#include <GameLib/Graphics/VertexBuffer.h>

namespace BulletPhysics {

class CSegaBulletDebugDrawer : public btIDebugDraw
{
public:
	CSegaBulletDebugDrawer();
	virtual ~CSegaBulletDebugDrawer();
	// btIDebugDraw interface
	virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
	virtual void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);
	virtual void	reportErrorWarning(const char* warningString);
	virtual void	draw3dText(const btVector3& location,const char* textString);
	virtual void	setDebugMode(int debugMode);
	virtual int		getDebugMode() const;
private:
	DISALLOW_COPY_AND_ASSIGN(CSegaBulletDebugDrawer);
	GameLib::Graphics::VertexBuffer vertexBuffer_;
};

}
#endif//__SEGABULLETDEBUGDRAWER__