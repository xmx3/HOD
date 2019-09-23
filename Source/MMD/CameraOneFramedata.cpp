#include"CameraOneFrameData.h"
#include<assert.h>
#include"BezierCurve.h"

namespace MMD {
	CameraOneFrameData::CameraOneFrameData(
		float frame,
		float distance,
		const D3DXVECTOR3 &pos,
		const D3DXQUATERNION &q,
		float viewAngle,//’PˆÊ‚Írad
		bool parth,
		const std::shared_ptr< BezierCurve > &ix,
		const std::shared_ptr< BezierCurve > &iy,
		const std::shared_ptr< BezierCurve > &iz,
		const std::shared_ptr< BezierCurve > &iq,
		const std::shared_ptr< BezierCurve > &id,
		const std::shared_ptr< BezierCurve > &iv
	)
		:frame_(frame),
		distance_(distance),
		pos_(pos),
		rot_(q),
		viewAngle_(viewAngle),
		parth_(parth),
		interpolationX_(ix),
		interpolationY_(iy),
		interpolationZ_(iz),
		interpolationQ_(iq),
		interpolationD_(id),
		interpolationV_(iv)
	{}

	CameraOneFrameData::~CameraOneFrameData() {}

	bool CameraOneFrameData::operator<(const CameraOneFrameData & right)const {
		return frame_ < right.frame_;
	}
	bool CameraOneFrameData::operator<(const float & rightFrame)const {
		return frame_ < rightFrame;
	}
}