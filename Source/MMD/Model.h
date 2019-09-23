#ifndef __MODEL_H__
#define __MODEL_H__
//#pragma once

//#pragma warning(disable:4244 4786 4819 4996)
#include<d3dx9.h>
#include<vector>
#include<map>
#include<string>
#include<memory>
#include<boost/shared_array.hpp>
#include"MMDMacro.h"

#include<GameLib/Math/Vector4.h>
#include<GameLib/Math/Matrix34.h>
#include<GameLib/Math/Matrix44.h>
#include<GameLib/Graphics/Texture.h>

#include"helper/FlyWeightTexture.h"

#define DEFALUT_ENABLE_PHYSICS false

namespace GameLib {
	namespace FileIO {
		class InFile;
	}
}

namespace MMD {

	class Bone;
	class Animation;
	class WrapperIK;
	class Face;
	class CFastVertexData;
	class Animation;
	class PMDRigidBody;
	class PMDConstraint;
	class VertexDataUsingVertexBlendShader;

	class TemplatePMD;
	typedef std::shared_ptr<TemplatePMD> TemplatePMDSharedPtr;

	class TemplateVMD;

#define MMD_DATA_PATH "Data/MMDData/pmd/MMD_Model/"


	class CModel
	{
	public:
		explicit CModel();
		virtual ~CModel();

		bool loadPMD(const char *fileName, bool isLoadBulletPysics = DEFALUT_ENABLE_PHYSICS);
		bool loadPMD(const GameLib::FileIO::InFile &inFile, bool isLoadBulletPysics = DEFALUT_ENABLE_PHYSICS);
		void loadPMDFromDB(const char *fileName, bool isEnableBulletPysics = DEFALUT_ENABLE_PHYSICS);
		void build(const std::shared_ptr<TemplatePMD> & pmd, bool isEnableBulletPysics);

		//現状まあまあの実装な気もするので、変えるときはよく考えること(animationStateも考慮にいれて)
		//loadVMDにするべきではないと思う
		//アニメーションとmodel別にするべきだと思う
		//anim = createAnim( model, fileName );
		//while( !anim->isReady() ){}//今の実装だとこれが出来ないmodel->isReady()とは分けたい。
		//addAnimation( anim );
		std::shared_ptr<Animation> loadVMD(const char *fileName);
		//bool loadVMD( const GameLib::FileIO::InFile &inFile,bool isLoadBulletPysics = DEFALUT_ENABLE_PHYSICS );
		//void loadVMDFromDB( const char *fileName );
		void build(const std::shared_ptr<TemplateVMD> & vmd);

		bool isReady();

		void update(const D3DXMATRIX &world, bool enablePhiscs = DEFALUT_ENABLE_PHYSICS);

		//右足(足首)とつま先のIKの目標位置のyを指定の高さにしてupdate()
		//つま先だけsetセットするほうがきれいに表示される
		//たとえば、空中にいるとき使うが空中用のアニメーション作って、通常のupdateを使うほうがきれい
		//void update(  const D3DXMATRIX &world, float groundHeight, bool enablePhiscs );

		//ボーン名がデフォルトと違う場合、使う。現状いらない
		//ボーンが見つからなかったらfalseを返す
		//bool setRightFootIKBone(const char* boneName="右足ＩＫ" );
		//ボーン名がデフォルトと違う場合、使う。現状いらない
		//ボーンが見つからなかったらfalseを返す
		//bool setLeftFootIKBone(const char* boneName="左足ＩＫ" );
		//ボーン名がデフォルトと違う場合、使う。現状いらない
		//ボーンが見つからなかったらfalseを返す
		//bool setRightToeIKBone(const char* boneName="右つま先ＩＫ" );
		//ボーン名がデフォルトと違う場合、使う。現状いらない
		//ボーンが見つからなかったらfalseを返す
		//bool setLeftToeIKBone(const char* boneName="左つま先ＩＫ" );


		void draw();
		void drawByMME();
		void debugDraw();

		const std::string & getFileName()const;


		//アニメーション関係
		//1frame 1/30秒
		//void setFrame( const unsigned int &index, const float &flame );
		//void stepFrame( const unsigned int &index, const float &flame );
		//bool isFrameOver( const unsigned int &index );
		//float getFrame( const int &index );

		//アニメーション関係
		//1frame 1/30秒
		void setFrame(const float &frame) { frame_ = frame; }
		float getFrame()const { return frame_; }
		void stepFrame(const float &frame) { frame_ += frame; }
		bool isFrameOver() const;
		int getAnimationsNum() const;
		void setCurrentAnimation(const std::shared_ptr<Animation> & anim) {
			currentAnimation_ = anim;
		}

		void fitRigidBodeisToBone(const D3DXMATRIX &world);
		void resetBones(const D3DXMATRIX &world);

		int getBonesCount() { return numBones_; }
		Bone* getBone(int index);
		Bone* getBone(const char *name);


		//Animation* findAnimation(const char* name);
		//void addAnimation(Animation* anim);
		//void resetAnimationWeight();
		//void setAnimationWeight(const unsigned int &animationIndex, const float &weight);
		//DWORD getAnimationCount() { return (DWORD)Animations_.size(); }
		//Animation* getAnimation(DWORD index) { return Animations_[index]; }

		//void SaveSmoother();
		struct Material {
			GameLib::Math::Vector4 diffuse_;
			GameLib::Math::Vector4 ambient_;
			GameLib::Math::Vector4 specular_;
			GameLib::Math::Vector4 emissive_;
			float power_;
			FlyWeightTexture texture_;
			unsigned char toonIndex_;
			unsigned char edgeFlag_;
			unsigned long numEdges_;
			GameLib::Graphics::Texture toonTexture_;
			GameLib::Math::Vector4 toonColor_;
			FlyWeightTexture sphereTexture_;
			int isSphereTextureAdditive_;
		};

		struct Subset {
			unsigned long materialIndex_;
			unsigned long faceIndex_;//開始面番号
			unsigned long faceCount_;
		};

		void addToWorld();
		void removeFromWorld();



		//剛体の速度を0にする
		//実験的コード
		//スカートのめり込み対策になるかと思ったが役に立たなかった
		void setVelocityZeroRigidBodies();

		//weightを1にし
		//現在の姿勢を保存する
		void startWeightBlend();
	private:
		//各ボーン(フレーム)を更新
		void updateBone(const D3DXMATRIX &world);

		//頂点バッファを更新
		void updateVertex();
		void updateIK();
		void updateFace();
		void updateFaceVertex();
		void updateRigidBody();
		//左右足(足首)IK、つまさきIKを指定した高さに
		//void setHeightFootIKBones(float groundHeight);
		void updateWeightBlend();
	private:
		DISALLOW_COPY_AND_ASSIGN(CModel);

		bool initPMD(const char *pData, unsigned long  size, bool isLoadBulletPhyisics);
		bool loadBulletPhysics(const char *pData, unsigned long size);
		//nextは次のデータ(rigidbody)が始まるアドレス。2重ポインタなのはアドレスが欲しいから
		bool skipPMDData(const char **next, const char *data, unsigned long size);
		void enablePhysics(bool enabled);

		std::shared_ptr< const std::string > fileName_;//stringとchar*混じったのいいの？
		std::shared_ptr< const std::string > modelName_;

		std::shared_ptr<VertexDataUsingVertexBlendShader> pVertexData_;

		unsigned long numMaterials_;
		boost::shared_array< Material >	materials_;
		unsigned long numSubsets_;
		boost::shared_array< Subset >		subsets_;

		unsigned short numBones_;
		boost::shared_array< Bone >		bones_;
		unsigned short numIks_;
		boost::shared_array< WrapperIK >	iks_;

		unsigned short numFaces_;
		boost::shared_array< Face > faces_;

		std::shared_ptr< std::vector<int> > rootBoneIndecies_;

		std::shared_ptr<Animation> currentAnimation_;

		unsigned long numRigidBodies_;
		//boost::shared_array< PMDRigidBody > rigidBodies_;
		std::shared_ptr<PMDRigidBody>* rigidBodies_;
		unsigned long numConstraints_;
		boost::shared_array< PMDConstraint > constraints_;

		boost::shared_array<FlyWeightTexture> toonTextures_;
		boost::shared_array<unsigned int> toonColors_;

		float frame_;

		//float SmootherWeight_;

		TemplatePMDSharedPtr loadingTemplatePMD_;

		bool isEnablePhysics_;

		//Bone *rightAnkleIkBone_;
		//Bone *rightToeIkBone_;
		//Bone *leftAnkleIkBone_;
		//Bone *leftToeIkBone_;

		float weight_;//weightBlend;
	};
}
#endif//__MODEL_H__


