#ifndef __TEMPLATEVMD_H__
#define __TEMPLATEVMD_H__
#include"Model.h"
#include<boost/shared_array.hpp>
#include<string>
#include<memory>

#include"CameraAnimation.h"



namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}

namespace MMD {

	class TemplateVMD;
	typedef std::shared_ptr<TemplateVMD> TemplateVMDSharedPtr;

	class Bone;
	class Face;

	class TemplateBoneKey;
	class TemplateFaceKey;

	class BoneKey;
	class FaceKey;

	class Animation;
	typedef std::shared_ptr<Animation> AnimationSharedPtr;


	class CameraAnimation;
	typedef std::shared_ptr<CameraAnimation> CameraAnimationSharedPtr;

	class TemplateVMD {
	public:
		explicit TemplateVMD(const char * name);
		~TemplateVMD();


		std::shared_ptr<Animation>
			create(
				Bone* bones, unsigned long numBone,
				Face* faces, unsigned long numFaces);
		//first arrayNum, second array
		std::pair< unsigned long, boost::shared_array<BoneKey> >
			createBoneKeyArray(Bone* bones, unsigned long numBone)const;

		//first arrayNum, second array
		std::pair< unsigned long, boost::shared_array<FaceKey> >
			createFaceKeyArray(Face* Faces, unsigned long numFaces)const;
		std::shared_ptr<const std::string> getFileName()const {
			return fileName_;
		}

		bool isReady();

		CameraAnimationSharedPtr getCameraAnimation()const;

	private:
		bool init(const char *pData, unsigned long size);

		std::shared_ptr<const std::string> fileName_;
		std::string header_;
		std::string modelName_;//çÏê¨ÉÇÉfÉãñº
		unsigned long numTemplateBoneKeys_;
		boost::shared_array<TemplateBoneKey> templateBoneKeys_;
		unsigned long numTemplateFaceKeys_;
		boost::shared_array<TemplateFaceKey> templateFaceKeys_;
		std::shared_ptr<CameraAnimation> camera_;
		float maxFrame_;
		bool hasPrinted_;

		GameLib::FileIO::InFile *file_;

	};
}
#endif