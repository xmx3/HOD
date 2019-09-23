#pragma once
//#include <boost/container/flat_set.hpp>
#include <vector>
#include "MMD/MMDMacro.h"
#include <memory>

struct D3DXMATRIX;
struct D3DXVECTOR3;
namespace MMD {

	class TemplateVMD;
	typedef std::shared_ptr<TemplateVMD> TemplateVMDSharedPtr;
	
	class CameraOneFrameData;

	class CameraAnimation : public std::enable_shared_from_this<CameraAnimation> {
	public:
		CameraAnimation();
		virtual ~CameraAnimation();

		void insert(const CameraOneFrameData &framedata);
		void reserve(unsigned int size);
		void shrink_to_fit();

		void load(const std::string &vmdFileName);
		bool isReady();

		bool isOver(float time)const;

		//カメラに必要なパラメーターを計算する
		//frameではなくて時間で指定
		//内部でフレームに変換する
		void calc(
			float time,
			D3DXVECTOR3 *pCameraPos,
			D3DXVECTOR3 *pLookAt,
			D3DXVECTOR3 *pUp,
			float *pViewAngle);
	private:
		DISALLOW_COPY_AND_ASSIGN(CameraAnimation);
		//boost::container::flat_set<CameraOneFrameData> keys_;
		std::vector<CameraOneFrameData> keys_;

		MMD::TemplateVMDSharedPtr templateVmd_;

	};
}