#pragma once
#include<d3dx9.h>

#include"ICamera.h"

namespace Camera {
	class FixedCamera : public ICamera {
	public:
		FixedCamera(
			const D3DXVECTOR3 &pos,
			const D3DXVECTOR3 &lookAt,
			const D3DXVECTOR3 &up,
			float viewAngleInDegree,
			float zNear,
			float zFar);
		virtual ~FixedCamera();
		void update(float elapsedTime);
	private:
		D3DXVECTOR3 mPos;
		D3DXVECTOR3 mLookAt;
		D3DXVECTOR3 mUp;
		float mViewAngle;//degree
		float mNear;
		float mFar;
	};
}