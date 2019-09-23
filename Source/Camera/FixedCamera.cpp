#include "FixedCamera.h"
#include<GameLib/GameLib.h>
#include<GameLib/Framework.h>
#include<GameLib/Math/Matrix34.h>
#include<GameLib/Math/Matrix44.h>
#include<GameLib/Math/Vector3.h>
#include<GameLib/Graphics/Manager.h>

#include"MME/Manager.h"

#include"LSPSM.h"

#include"SegaTypeHelper.h"



Camera::FixedCamera::FixedCamera(
	const D3DXVECTOR3 & pos,
	const D3DXVECTOR3 & lookAt,
	const D3DXVECTOR3 & up,
	float viewAngle,
	float zNear, float zFar)
	:mPos(pos),
	mLookAt(lookAt),
	mUp(up),
	mViewAngle(viewAngle),
	mNear(zNear),
	mFar(zFar)
{
}

Camera::FixedCamera::~FixedCamera()
{
}

void Camera::FixedCamera::update(float elapsedTime)
{
	GameLib::Framework fw = GameLib::Framework::instance();
	GameLib::Matrix44 pvm, pm;
	pm.setPerspectiveTransform(
		mViewAngle,
		static_cast< float >(fw.width()),
		static_cast< float >(fw.height()),
		mNear,
		mFar);

	GameLib::Vector3 eyePos, lookAt, up;
	eyePos = toVector3(mPos);
	lookAt = toVector3(mLookAt);
	up = toVector3(mUp);

	GameLib::Matrix34 vm;
	vm.setViewTransformLH(
		eyePos,
		lookAt,
		up);

	pvm.setMul(pm, vm);

	GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
	gm.setProjectionViewMatrix(pvm);
	gm.setEyePosition(eyePos);

	//MME‚ÌÝ’è
	{
		MME::Manager *m = MME::Manager::instance();
		m->setEyePosition(eyePos);
		GameLib::Vector3 dir;
		dir.setSub(lookAt, eyePos);
		dir.normalize();
		m->setEyeDirection(dir);
		GameLib::Matrix34 world;
		world.setIdentity();
		D3DXMATRIX dxvm, dxpm;
		dxvm = toDxMatrix(vm);
		dxpm = toDxMatrix(pm);
		m->setViewMatrix(dxvm);
		m->setProjectionMatrix(dxpm);
		m->setZNear(mNear);
		m->setZFar(mFar);
		LSPSMCalculator lspsm;

		//GameLib::Input::Keyboard k;
		//if( k.isTriggered('s') ){
		//	enableLSPSM=!enableLSPSM;
		//}
		lspsm.SetUseLSPSM(true);
		lspsm.SetEyePos(toDxVec3(eyePos));
		pm.setPerspectiveTransform(45.f,
			static_cast<float>(fw.width()),
			static_cast<float>(fw.height()),
			5.f,//‘å‚«‚ß‚É‚Æ‚¢‚¤‚©‚à‚¤‚·‚±‚µ[‚³‚Ì¸“x‚ð‚¿‚å‚¤‚Ç—Ç‚¢‚æ‚¤‚É‚·‚é•û–@‚Í‚È‚¢‚©
			500.f);

		lspsm.SetEyeProjection(toDxMatrix(pm));
		lspsm.SetEyeView(dxvm);
		lspsm.SetLightDir(toDxVec3(m->getLightDirection(0)));
		lspsm.SetViewDir(toDxVec3(dir));
		lspsm.SetNearClip(5.f);
		lspsm.UpdateShadowMatrix();

		//m->setEyePosition( lightPos );
		//Matrix34 lvm;
		//lvm.setViewTransformLH( 
		//	lightPos,
		//	target, 
		//	Vector3( 1, 0, 0) );

		//Vector3 lightDir = 

		m->setLightViewMatrix(0, lspsm.GetLightView());
		m->setLightProjectionMatrix(0, lspsm.GetLightProjection());
	}
}
