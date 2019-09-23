#ifndef __DXBULLETDEBUGDRAWER__
#define __DXBULLETDEBUGDRAWER__
#include <btBulletDynamicsCommon.h>
#include "MMD/MMDMacro.h"
#include <GameLib/Graphics/VertexBuffer.h>

namespace BulletPhysics {

class CDxBulletDebugDrawer : public btIDebugDraw
{
public:
	CDxBulletDebugDrawer(){
		mVB = GameLib::Graphics::VertexBuffer::create(2);
	}
	virtual ~CDxBulletDebugDrawer(){
		mVB.release();
	};
	// btIDebugDraw interface
	virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
	virtual void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);
	virtual void	reportErrorWarning(const char* warningString);
	virtual void	draw3dText(const btVector3& location,const char* textString);
	virtual void	setDebugMode(int debugMode);
	virtual int		getDebugMode() const;
private:
	DISALLOW_COPY_AND_ASSIGN(CDxBulletDebugDrawer);
	GameLib::Graphics::VertexBuffer mVB;
};

}
#endif//__DXBULLETDEBUGDRAWER__