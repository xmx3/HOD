#pragma once
#include<d3dx9.h>
#include<memory>

namespace MMD {

	class BezierCurve;

	class CameraOneFrameData {
	public:
		friend class CameraAnimation;
		CameraOneFrameData(
			float frame,
			float distance,
			const D3DXVECTOR3 &pos,
			const D3DXQUATERNION &q,
			float viewAngle,
			bool parth,
			const std::shared_ptr< BezierCurve > &ix,
			const std::shared_ptr< BezierCurve > &iy,
			const std::shared_ptr< BezierCurve > &iz,
			const std::shared_ptr< BezierCurve > &iq,
			const std::shared_ptr< BezierCurve > &id,
			const std::shared_ptr< BezierCurve > &iv
		);
		~CameraOneFrameData();

		bool operator<(const CameraOneFrameData & right)const;
		bool operator<(const float & rightFrame)const;
	private:
		float frame_;			// フレーム番号
		float distance_; 	// 目標点とカメラの距離(目標点がカメラ前面でマイナス)
		D3DXVECTOR3 pos_;
		D3DXQUATERNION rot_;
		std::shared_ptr< BezierCurve > interpolationX_;
		std::shared_ptr< BezierCurve > interpolationY_;
		std::shared_ptr< BezierCurve > interpolationZ_;
		std::shared_ptr< BezierCurve > interpolationQ_;
		std::shared_ptr< BezierCurve > interpolationD_;//Distance(距離)の補完
		std::shared_ptr< BezierCurve > interpolationV_;//視野角(viewAngle)の補完
		float viewAngle_; // 視野角(deg)
		bool parth_; // パースペクティブ, 0:ON, 1:OFF//実装してない
	};
}


