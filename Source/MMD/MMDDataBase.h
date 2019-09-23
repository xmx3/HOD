#ifndef __MMDDATABASE_H__
#define __MMDDATABASE_H__
#include"Animation.h"
#include<map>
#include<memory>
#include<string>

namespace MMD {

	class CModel;
	class TemplatePMD;
	typedef std::shared_ptr<TemplatePMD> TemplatePMDSharedPtr;

	class TemplateVMD;
	typedef std::shared_ptr<TemplateVMD> TemplateVMDSharedPtr;

	class Animation;
	typedef std::shared_ptr<Animation> AnimationSharedPtr;


	class CameraAnimation;
	typedef std::shared_ptr<CameraAnimation> CameraAnimationSharedPtr;

	class MMDDataBase {
	public:
		static MMDDataBase* instance();
		static void destroy();

		//先に作っておくための関数郡
		//load待ちさせないため
		//だが、使い勝手が悪い、アセットクラスでも作るべきか
		static TemplatePMDSharedPtr loadPMD(const char* filename);
		static TemplateVMDSharedPtr loadVMD(const char* filename);

		static bool isReady();

		//static void buildPMD(const char* filename, CModel* model, bool isEnableBulletPysics );


		static AnimationSharedPtr
			createAnimationVMD(
				const char* pmdFilename,
				const char* vmdFilename,
				Bone* bones, unsigned long numBone,
				Face* faces, unsigned long numFaces);

		CameraAnimationSharedPtr getCameraAnimation(const std::string &vmdFileName)const;
	private:
		//singleton-----------------------------------------------------
		MMDDataBase();
		virtual ~MMDDataBase();

		//disallow assign
		MMDDataBase(const MMDDataBase &);
		//disallow copy
		void operator=(const MMDDataBase &);
		struct Deleter
		{
			void operator()(MMDDataBase const* const p) const
			{
				delete p;
			}
		};

		typedef std::unique_ptr< MMDDataBase, Deleter > UptrMMDDB;
		static UptrMMDDB this_;
		//-----------------------------------------------------



		//static TemplatePMDSharedPtr registerPMD(const char* filename );

		TemplateVMDSharedPtr registerTemplateVMD(const char* filename);
		TemplateVMDSharedPtr findTemplateVMD(const char* filename);

		TemplatePMDSharedPtr registTemplatePMD(const char* filename);
		TemplatePMDSharedPtr findTemplatePMD(const char* filename);



		std::shared_ptr<Animation> findAnimation(const char* pmdFile, const char* vmdFile);

		std::map< const std::string, TemplatePMDSharedPtr > pmdMap_;
		std::map< const std::string, TemplateVMDSharedPtr > vmdMap_;
		typedef std::pair< const std::string, const std::string > PMDAndVMDFileName;
		std::map< PMDAndVMDFileName, std::shared_ptr<Animation> > animationMap_;
	};
}
#endif