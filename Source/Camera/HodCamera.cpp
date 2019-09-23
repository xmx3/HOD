#include"HodCamera.h"
#include"MMD/CameraAnimation.h"

#include<GameLib/GameLib.h>
#include<GameLib/Framework.h>
#include<GameLib/Math/Matrix34.h>
#include<GameLib/Math/Matrix44.h>
#include<GameLib/Math/Vector3.h>
#include<GameLib/Graphics/Manager.h>

#include"MME/Manager.h"

#include"LSPSM.h"

#include"SegaTypeHelper.h"

#include"helper/MyOutputDebugString.h"

namespace Camera {

HodCamera::HodCamera(MMD::CameraAnimationSharedPtr camera)
	:mCameraAnim(camera),
	mTime(0.f)
{
	if (mCameraAnim->isReady()) {
		update(0.f);
	}
}

HodCamera::~HodCamera()
{
}

void HodCamera::update(float dt)
{
	mTime += dt;
	mCameraAnim->calc(mTime, &mCameraPos, &mLookAt, &mUp, &mViewAngle);
	sendParamToShader();
	//TRACE3("%f, %f, %f\n", mCameraPos.x, mCameraPos.y, mCameraPos.z);
}

void HodCamera::getCameraParameter(D3DXVECTOR3 * pCameraPos, D3DXVECTOR3 * pLookAt, D3DXVECTOR3 * pUp, float * pViewAngle) const
{
	if (pCameraPos) {
		*pCameraPos = mCameraPos;
	}

	if (pLookAt) {
		*pLookAt = mLookAt;
	}

	if (pUp) {
		*pUp = mUp;
	}

	if (pViewAngle) {
		*pViewAngle = mViewAngle;
	}
}

float HodCamera::getTime() const
{
	return mTime;
}

const D3DXMATRIX& HodCamera::getViewProj() const
{
	return mViewProj;
}

void HodCamera::setTime(float time)
{
	mTime = time;
}

bool HodCamera::isAnimeOver() const
{
	return mCameraAnim->isOver(mTime);
}

bool HodCamera::isReady()
{
	return mCameraAnim->isReady();
}

void HodCamera::sendParamToShader()
{
	GameLib::Framework fw = GameLib::Framework::instance();

	D3DXMATRIX  world, view, proj;
	D3DXMatrixIdentity(&world);


	D3DXMatrixLookAtLH(&view, &mCameraPos, &mLookAt, &mUp);

	float aspect = static_cast<float>(fw.width()) / static_cast<float>(fw.height());

	MME::Manager *mme = MME::Manager::instance();

	D3DXMatrixPerspectiveFovLH(&proj, mViewAngle, aspect, 0.1f, 3000.f);
	
	mme->setWorldMatrix(world);
	mme->setViewMatrix(view);
	mme->setProjectionMatrix(proj);
	mme->setZNear(0.1f);
	mme->setZFar(3000.f);
	
	mViewProj = view * proj;

	GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
	gm.setProjectionViewMatrix(toMatrix44(mViewProj));
	gm.setEyePosition(toVector3(mCameraPos));

	
	
	// /*--なにかあったらここから

	static const float zNear = 0.1f;
	static const float zFar = 10000.f;

	GameLib::Matrix44 pvm, pm;
	pm.setPerspectiveTransform(
		mViewAngle,
		static_cast< float >(fw.width()),
		static_cast< float >(fw.height()),
		zNear,
		zFar );

	GameLib::Vector3 eyePos, lookAt, up;
	eyePos = toVector3(mCameraPos);
	lookAt = toVector3(mLookAt);
	up = toVector3(mUp);

	GameLib::Matrix34 vm;
	vm.setViewTransformLH(
		eyePos,
		lookAt,
		up);

	pvm.setMul(pm, vm);


	//MMEの設定
	{
		MME::Manager *m = MME::Manager::instance();
		m->setEyePosition(eyePos);
		GameLib::Vector3 dir;
		dir.setSub(lookAt, eyePos);
		dir.normalize();
		m->setEyeDirection(dir);
		D3DXMATRIX dxvm, dxpm;
		dxvm = toDxMatrix(vm);
		dxpm = toDxMatrix(pm);
		LSPSMCalculator lspsm;

		lspsm.SetUseLSPSM(true);
		lspsm.SetEyePos(toDxVec3(eyePos));
		pm.setPerspectiveTransform(45.f,
			static_cast<float>(fw.width()),
			static_cast<float>(fw.height()),
			5.f,//大きめにというかもうすこし深さの精度をちょうど良いようにする方法はないか
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
	//*/--ここまでコメントアウト
	
}

}