#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include<vector>
#include"MMDMacro.h"
#include"BezierCurve.h"
#include<memory>
#include<string>
#include<boost/shared_array.hpp>


namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}

namespace MMD {

	class Bone;
	class Face;
	class FaceKey;
	class BoneKey;
	class TemplateVMD;

	class Animation {
	public:
		Animation();
		virtual ~Animation();
		void init(
			const TemplateVMD &vmd,
			Bone* bones, const unsigned long &numBones,
			Face* faces, const unsigned long &numFaces);

		const char* getName() { return name_->c_str(); }

		//void setFrame( const float &frame ){ frame_=frame; }
		//float getFrame(){ return frame_; }
		//void stepFrame( const float &frame ){ frame_+=frame; }

		//bool isOver() const { return frame_>=maxFrame_; }
		float getMaxFrame() const { return maxFrame_; }

		//void resetRelativeBones();
		void updateBones(Bone *bones, float frame);
		void updateFace(float frame);
	private:
		DISALLOW_COPY_AND_ASSIGN(Animation);
		std::shared_ptr<const std::string> name_;
		unsigned long numBoneKeys_;
		boost::shared_array<BoneKey> boneKeys_;
		unsigned long numFaceKeys_;
		boost::shared_array<FaceKey> faceKeys_;

		float maxFrame_;

		//現状はモデル一つにつきframe持たせてる
		//もしアニメごとにframe持たせたいと思ったらここに持たせること
		//もし、歩きアニメの5フレームのところと　振る動作10フレームをあわせたいとなると
		//その場合は個別modelごとに持たせる必要あり
		//現状はモデル名とアニメーションが一緒だとAnimation配列は共通だが
		//blendさせたい場合だとここが共通じゃなくなり
		//templateAnimationが欲しくなってくる
		//float frame_;
	};

}
#endif __ANIMATION_H__
