#ifndef __SPHEREMESH_H__
#define __SPHEREMESH_H__

#include"MMD/MMDMacro.h"
#include<GameLib/Scene/Model.h>
#include<GameLib/Scene/Container.h>
#include"SegaTypeHelper.h"
#include<GameLib/Graphics/Manager.h>
#include<btBulletDynamicsCommon.h>

class SphereMesh {
public:
	SphereMesh()
	{
		mSceneContainer = GameLib::Scene::Container::create( "Data/Model/Primitive/sphere.x.txt" );
		while ( !mSceneContainer.isReady() ){
			;
		}
		mModel=mSceneContainer.createModel(0);
		
	}
	~SphereMesh(){
	}

	void draw( const btTransform &btMat, const float &radius, unsigned int color=0xffffffff ){
		float a;
		
		GameLib::Math::Vector3 rgb;
		rgb.set(
			static_cast<float>( ( (color & 0x00ff0000) >> 16 ) ) / 255.f,
			static_cast<float>( ( (color & 0x0000ff00) >> 8 ) ) / 255.f, 
			static_cast<float>( ( (color & 0x000000ff) ) ) / 255.f );
		
		a=static_cast<float>( ( (color & 0xff000000) >> 24 ) ) / 255.f;
		GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
		gm.setAmbientColor(rgb);
		mModel.setColor(rgb);
		mModel.setTransparency(a);
		mModel.setPosition( toVector3( btMat.getOrigin() ) );
		mModel.setScale( GameLib::Math::Vector3(radius, radius, radius) );
		mModel.draw();
	}

	void draw( const btCollisionObject *obj, unsigned int color=0xffffffff ){
		if( obj->getCollisionShape()->getShapeType() != SPHERE_SHAPE_PROXYTYPE ){
			assert(false);
			return;
		}

		float a;
		GameLib::Math::Vector3 rgb;
		rgb.set(
			static_cast<float>( ( (color & 0x00ff0000) >> 16 ) ) / 255.f,
			static_cast<float>( ( (color & 0x0000ff00) >> 8 ) ) / 255.f, 
			static_cast<float>( ( (color & 0x000000ff) ) ) / 255.f );
		
		a=static_cast<float>( ( (color & 0xff000000) >> 24 ) ) / 255.f;
		GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
		gm.setAmbientColor(rgb);
		mModel.setColor(rgb);
		mModel.setTransparency(a);

		const float radius = static_cast<const btSphereShape*>( obj->getCollisionShape() )->getRadius();
		
		mModel.setPosition( toVector3( obj->getWorldTransform().getOrigin() ) );
		mModel.setScale( GameLib::Math::Vector3(radius, radius, radius) );
		mModel.draw();
	}
private:
	DISALLOW_COPY_AND_ASSIGN(SphereMesh);
	GameLib::Scene::Container	mSceneContainer;
	GameLib::Scene::Model		mModel;
};
#endif//__SPHEREMESH_H__