#include<d3dx9.h>
#include<MMD/Fwd.h>
#include"ICamera.h"

namespace Camera {
	//Hatune Of the Dead用カメラ
	//まあ名前普通にアニメーションカメラでいいよね
	class HodCamera : public ICamera
	{
	public:
		HodCamera(MMD::CameraAnimationSharedPtr camera);
		~HodCamera();
		void update(float dt);
		//引数がnullptrなら何もしない
		void getCameraParameter(
			D3DXVECTOR3	*pCameraPos,
			D3DXVECTOR3	*pLookAt,
			D3DXVECTOR3 *pUp,
			float		*pViewAngle)const;
		float getTime()const;
		const D3DXMATRIX& getViewProj()const;
		void setTime(float time);
		bool isAnimeOver()const;
		bool isReady();

	private:
		void sendParamToShader();
		MMD::CameraAnimationSharedPtr mCameraAnim;
		float		mTime;
		D3DXVECTOR3	mCameraPos;
		D3DXVECTOR3	mLookAt;
		D3DXVECTOR3 mUp;
		float		mViewAngle;
		D3DXMATRIX	mViewProj;
	};

}//namespace Camera

