#include"MMDDataBase.h"
#include"Model.h"
#include"TemplatePMD.h"
#include"TemplateVMD.h"
#include<GameLib/FileIO/InFile.h>
#include<assert.h>

namespace MMD {
	MMDDataBase::UptrMMDDB MMDDataBase::this_ = NULL;
	MMDDataBase::MMDDataBase() {}
	MMDDataBase::~MMDDataBase() {}

	MMDDataBase* MMDDataBase::instance() {
		if (!this_)
		{
			this_.reset(new MMDDataBase);
		}
		return this_.get();
	}

	void MMDDataBase::destroy() {
		this_.reset(NULL);
	}

	//void MMDDataBase::buildPMD(const char* name, CModel* model, bool isEnableBulletPysics ){
	//	MMDDataBase *db = MMDDataBase::instance();
	//	TemplatePMDSharedPtr pmd = db->findTemplatePMD(name);
	//	if(pmd){
	//		model->build( pmd, isEnableBulletPysics );
	//	} else {
	//		pmd = db->registerPMD( name );
	//		if( !pmd ) {
	//			assert(false && "pmd register failed" );
	//			return;
	//		}
	//		model->build( pmd, isEnableBulletPysics );
	//	}
	//}

	//TemplatePMDSharedPtr MMDDataBase::registerPMD( const char* name ){
	//	GameLib::FileIO::InFile inFile = GameLib::FileIO::InFile::create( name );
	//	
	//	if( inFile.isError() ){
	//		assert(false && "pmd register failed" );
	//		return NULL;
	//	}
	//
	//	while(!inFile.isFinished()){
	//
	//	}
	//	
	//	TemplatePMDSharedPtr pmd( new TemplatePMD(name) );
	//
	//	pmd->init( inFile.data(), inFile.size() );
	//	MMDDataBase::instance()->pmdMap_.insert( std::make_pair( std::string(name), pmd ) );
	//	return pmd;
	//}

	TemplatePMDSharedPtr MMDDataBase::findTemplatePMD(const char* name) {
		std::map< const std::string, TemplatePMDSharedPtr >::iterator it = pmdMap_.find(name);
		if (it != pmdMap_.end()) {
			return it->second;
		}
		else {
			return NULL;
		}
	}

	TemplateVMDSharedPtr MMDDataBase::registerTemplateVMD(const char* name) {

		TemplateVMDSharedPtr vmd(new TemplateVMD(name));

		vmdMap_.insert(std::make_pair(std::string(name), vmd));
		return vmd;
	}

	TemplateVMDSharedPtr MMDDataBase::findTemplateVMD(const char* name) {
		std::map< const std::string, TemplateVMDSharedPtr >::iterator it = vmdMap_.find(name);
		if (it != vmdMap_.end()) {
			return it->second;
		}
		else {
			return NULL;
		}
	}

	std::shared_ptr<Animation> MMDDataBase::createAnimationVMD(
		const char* pmdFileName,
		const char* vmdFileName,
		Bone* bones, unsigned long numBone,
		Face* faces, unsigned long numFaces)
	{
		MMDDataBase *db = MMDDataBase::instance();
		//コンパイルエラー
		//関数宣言だとコンパイラが判断する
		//PMDAndVMDFileName pmdvmdFile( std::string(pmdFileName), std::string(vmdFileName) );
		PMDAndVMDFileName pmdvmdFile((std::string(pmdFileName)), (std::string(vmdFileName)));

		std::map< PMDAndVMDFileName, std::shared_ptr<Animation> >::iterator it =
			//db->animationMap_.find( std::make_pair(std::string(pmdFileName),std::string(vmdFileName) ) );
			db->animationMap_.find(pmdvmdFile);

		if (it != db->animationMap_.end()) {
			return it->second;
		}
		else {
			std::shared_ptr<Animation> anim;

			TemplateVMDSharedPtr vmd = db->findTemplateVMD(vmdFileName);
			if (vmd) {
				anim = vmd->create(bones, numBone, faces, numFaces);
				//db->animationMap_.insert( std::make_pair( std::make_pair(std::string(pmdFileName),std::string(vmdFileName)), anim) );
				db->animationMap_.insert(std::make_pair(pmdvmdFile, anim));
			}
			else {
				vmd = db->registerTemplateVMD(vmdFileName);
				if (!vmd) {
					assert(false && "vmd register failed");
				}

				while (!vmd->isReady()) {}

				anim = vmd->create(bones, numBone, faces, numFaces);
				db->animationMap_.insert(std::make_pair(pmdvmdFile, anim));
				//db->animationMap_.insert( std::make_pair( std::make_pair(std::string(pmdFileName),std::string(vmdFileName)), anim) );
			}
			return anim;
		}
	}


	TemplatePMDSharedPtr MMDDataBase::registTemplatePMD(const char* name) {

		TemplatePMDSharedPtr pmd(new TemplatePMD(name));

		pmdMap_.insert(std::make_pair(std::string(name), pmd));
		return pmd;
	}



	TemplatePMDSharedPtr MMDDataBase::loadPMD(const char* filename) {
		MMDDataBase *db = MMDDataBase::instance();
		TemplatePMDSharedPtr pmd = db->findTemplatePMD(filename);
		if (pmd) {
			return pmd;
		}
		else {
			return db->registTemplatePMD(filename);
		}
	}

	TemplateVMDSharedPtr MMDDataBase::loadVMD(const char* filename) {
		MMDDataBase *db = MMDDataBase::instance();

		TemplateVMDSharedPtr vmd = db->findTemplateVMD(filename);
		if (vmd) {
			return vmd;
		}
		else {
			return db->registerTemplateVMD(filename);
		}

	}

	bool MMDDataBase::isReady() {
		bool result = true;
		MMDDataBase *db = MMDDataBase::instance();

		for (
			std::map< const std::string, TemplatePMDSharedPtr >::iterator
			it = db->pmdMap_.begin(),
			end = db->pmdMap_.end();
			it != end;
			++it)
		{
			it->second->isReady() ? 0 : result = false;
		}


		for (
			std::map< const std::string, TemplateVMDSharedPtr >::iterator
			it = db->vmdMap_.begin(),
			end = db->vmdMap_.end();
			it != end;
			++it)
		{
			it->second->isReady() ? 0 : result = false;
		}
		return result;
	}

	CameraAnimationSharedPtr MMDDataBase::getCameraAnimation(const std::string &vmdFileName)const {
		auto it = vmdMap_.find(vmdFileName);
		assert(it != vmdMap_.end());
		if (it != vmdMap_.end()) {
			return it->second->getCameraAnimation();
		}
		else {
			return nullptr;
		}

	}

}