#pragma once
#include<d3dx9.h>
#include<memory>

namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}
namespace MMD {

	class BezierCurve;

	//boneをアニメーションさせるための1フレーム分のデータ
	struct OneFrameData {
		OneFrameData(
			float frame,
			const D3DXVECTOR3 &pos,
			const D3DXQUATERNION &rot,
			const std::shared_ptr< BezierCurve > &interpolationX,
			const std::shared_ptr< BezierCurve > &interpolationY,
			const std::shared_ptr< BezierCurve > &interpolationZ,
			const std::shared_ptr< BezierCurve > &interpolationQ)
			:frame_(frame),
			pos_(pos),
			rot_(rot),
			interpolationX_(interpolationX),
			interpolationY_(interpolationY),
			interpolationZ_(interpolationZ),
			interpolationQ_(interpolationQ)
		{}



		bool operator<(const OneFrameData & right)const {
			return frame_ < right.frame_;
		}
		bool operator<(const float & rightFrame)const {
			return frame_ < rightFrame;
		}

		float frame_;
		D3DXVECTOR3 pos_;
		D3DXQUATERNION rot_;
		std::shared_ptr< BezierCurve > interpolationX_;
		std::shared_ptr< BezierCurve > interpolationY_;
		std::shared_ptr< BezierCurve > interpolationZ_;
		std::shared_ptr< BezierCurve > interpolationQ_;
	};
}