#ifndef __TEMPLATEPMD_H__
#define __TEMPLATEPMD_H__
#include"Model.h"
#include<memory>
#include<boost/shared_array.hpp>
#include<string>
#include<helper/FlyWeightTexture.h>

namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}

namespace MMD {
	class TemplatePMD;
	typedef std::shared_ptr<TemplatePMD> TemplatePMDSharedPtr;

	class WrapperIK;
	class Face;
	class VertexDataUsingVertexBlendShader;

	struct PMD_BONE;
	struct PMD_Constraint;
	struct PMD_RigidBody;

	class TemplatePMD {
	public:
		friend void CModel::build(const TemplatePMDSharedPtr &, bool);

		TemplatePMD(const char * name);
		~TemplatePMD();

		bool isReady();

	private:
		bool loadBulletPhysics(const char *pData, unsigned long size);
		bool init(const char *pData, unsigned long size);


		std::shared_ptr<const std::string> fileName_;
		std::shared_ptr<const std::string> modelName_;


		std::shared_ptr<VertexDataUsingVertexBlendShader> pVertexData_;

		unsigned long numMaterials_;
		boost::shared_array< CModel::Material >	materials_;
		unsigned long numSubsets_;
		boost::shared_array< CModel::Subset >	subsets_;

		unsigned short numBones_;
		boost::shared_array< PMD_BONE >		bonesData_;
		unsigned short numIks_;
		boost::shared_array< WrapperIK >	iks_;

		unsigned short numFaces_;
		boost::shared_array< Face > faces_;

		unsigned long numRigidBodies_;
		boost::shared_array< PMD_RigidBody > rigidBodiesData_;
		unsigned long numConstraints_;
		boost::shared_array< PMD_Constraint > constraintsData_;

		boost::shared_array<FlyWeightTexture> toonTextures_;
		boost::shared_array<unsigned int> toonColors_;

		GameLib::FileIO::InFile *file_;
	};
}
#endif