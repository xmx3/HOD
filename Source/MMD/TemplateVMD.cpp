#include"TemplateVMD.h"
#include"Vmd.h"
#include"TemplateBoneKey.h"
#include"ContainerHelper.h"
#include"TemplateFaceKey.h"
#include"BezierCurve.h"
#include<tuple>
#include<set>
#include<algorithm>
#include"helper/MyOutputDebugString.h"
#include"FaceKey.h"
#include"Animation.h"
#include"BoneKey.h"
#include<GameLib/FileIO/InFile.h>
#include"OneFrameData.h"
#include"CameraAnimation.h"
#include"CameraOneFrameData.h"
//namespace{
//	bool less( const TemplateBoneKey &left, const TemplateBoneKey &right ){
//		return left.operator<(right);
//	}
//}


namespace MMD {
	namespace {

		struct deleter {
			void operator()(CameraAnimation*p) {
				delete p;
			}
		};
		//見つかったらそれを返す、見つからなかった場合、新規に作って登録して今作ったのを返す
		std::shared_ptr< BezierCurve >
			createIfNotFound(
				const std::tuple<float, float, float, float> & key,
				std::map< std::tuple<float, float, float, float>, std::shared_ptr< BezierCurve > > *uniques
			)
		{
			typedef std::shared_ptr< BezierCurve > Bsptr;
			auto it = uniques->find(key);
			//作成
			if (it == uniques->end()) {
				Bsptr interpolation(new BezierCurve);
				//補完曲線(ベジェ曲線)の初期化
				interpolation->init(std::get<0>(key),
					std::get<1>(key),
					std::get<2>(key),
					std::get<3>(key));
				uniques->insert(std::make_pair(key, interpolation));
				return interpolation;
			}
			else {
				return it->second;
			}
		}

	}//end unnamespace

	TemplateVMD::TemplateVMD(const char * name)
		:numTemplateBoneKeys_(0),
		templateBoneKeys_(),
		numTemplateFaceKeys_(0),
		templateFaceKeys_(),
		maxFrame_(-1.f),//float minにするべきか(-max?)
		hasPrinted_(false),
		file_(0)
	{

		fileName_.reset(new std::string(name));
		file_ = new GameLib::FileIO::InFile();
		*file_ = GameLib::FileIO::InFile::create(name);

		if (file_->isError()) {
			assert(false && "vmd file not found.");
		}
		//isReady();
	}

	TemplateVMD::~TemplateVMD() {
		delete file_;
		file_ = 0;

		//bug調査用
		//if(camera_){
		//	camera_.get();
		//}
	}

	bool TemplateVMD::init(const char *pData, unsigned long size) {

		//ベジェ曲線を同じのを何個も作りたくないので共通化するためのコンテナ
		std::map< std::tuple<float, float, float, float>, std::shared_ptr< BezierCurve > > uniques;//uniqueInterpolations;

		CVmd vmd(pData, size);
		modelName_.assign(vmd.vmdHeader_.vmdModelName);
		header_.assign(vmd.vmdHeader_.vmdHeader);

		//いくつユニークなボーン名があるか,ボーン毎にいくつフレームがあるかを保存
		std::map<std::string, unsigned int > uniqueBoneNames;

		//ユニークなボーン名のみ保存
		//ついでに整列
		for (unsigned int i = 0; i < vmd.motionLength_; ++i)
		{
			uniqueBoneNames.emplace(std::make_pair(std::string(vmd.pMotions_[i].BoneName), 0));
		}

		for (unsigned int i = 0; i < vmd.motionLength_; ++i)
		{
			++uniqueBoneNames[std::string(vmd.pMotions_[i].BoneName)];
		}

		numTemplateBoneKeys_ = uniqueBoneNames.size();
		if (numTemplateBoneKeys_ != 0)
		{
			//あらかじめ必要な分だけ初期化	
			templateBoneKeys_.reset(new TemplateBoneKey[numTemplateBoneKeys_]);

			int bi = 0;
			for (auto it = uniqueBoneNames.begin(), end = uniqueBoneNames.end(); it != end; ++bi, ++it) {
				templateBoneKeys_[bi].setName(it->first.c_str());
				templateBoneKeys_[bi].reserve(it->second);
			}
		}

		for (unsigned int i = 0; i < vmd.motionLength_; ++i)
		{
			TemplateBoneKey* pbk = std::lower_bound(templateBoneKeys_.get(), templateBoneKeys_.get() + numTemplateBoneKeys_, std::string(vmd.pMotions_[i].BoneName));
			assert(
				pbk != templateBoneKeys_.get() + numTemplateBoneKeys_ &&
				std::string(vmd.pMotions_[i].BoneName) == std::string(pbk->getName()) && "not found");
			//template <class ForwardIterator, class T>
			//bool binary_search ( ForwardIterator first, ForwardIterator last, const T& value )
			//{
			//  first = lower_bound(first,last,value);
			//  return (first!=last && !(value<*first));
			//}
			D3DXQUATERNION q(vmd.pMotions_[i].Rotate[0], vmd.pMotions_[i].Rotate[1], vmd.pMotions_[i].Rotate[2], vmd.pMotions_[i].w);
			D3DXVECTOR3 pos(vmd.pMotions_[i].Location[0], vmd.pMotions_[i].Location[1], vmd.pMotions_[i].Location[2]);
			float frame = static_cast<float>(vmd.pMotions_[i].flameNo);
			if (maxFrame_ < frame) maxFrame_ = frame;

			typedef std::shared_ptr<BezierCurve> Bsptr;
			Bsptr ix, iy, iz, iq;//interpolation

			//ベジェ曲線を何度も同じの作るとメモリ消費するので共通化
			{
				auto key = std::make_tuple(
					static_cast<float>(vmd.pMotions_[i].Interpolation1[0]),
					static_cast<float>(vmd.pMotions_[i].Interpolation1[4]),
					static_cast<float>(vmd.pMotions_[i].Interpolation1[8]),
					static_cast<float>(vmd.pMotions_[i].Interpolation1[12]));
				ix = createIfNotFound(key, &uniques);
			}

			//ベジェ曲線
			{
				auto key = std::make_tuple(
					static_cast<float>(vmd.pMotions_[i].Interpolation2[0]),
					static_cast<float>(vmd.pMotions_[i].Interpolation2[4]),
					static_cast<float>(vmd.pMotions_[i].Interpolation2[8]),
					static_cast<float>(vmd.pMotions_[i].Interpolation2[12]));
				iy = createIfNotFound(key, &uniques);
			}

			{
				auto key = std::make_tuple(
					static_cast<float>(vmd.pMotions_[i].Interpolation3[0]),
					static_cast<float>(vmd.pMotions_[i].Interpolation3[4]),
					static_cast<float>(vmd.pMotions_[i].Interpolation3[8]),
					static_cast<float>(vmd.pMotions_[i].Interpolation3[12]));
				iz = createIfNotFound(key, &uniques);
			}

			{
				auto key = std::make_tuple(
					static_cast<float>(vmd.pMotions_[i].Interpolation4[0]),
					static_cast<float>(vmd.pMotions_[i].Interpolation4[4]),
					static_cast<float>(vmd.pMotions_[i].Interpolation4[8]),
					static_cast<float>(vmd.pMotions_[i].Interpolation4[12]));
				iq = createIfNotFound(key, &uniques);
			}

			pbk->insert(
				OneFrameData(
					frame,
					pos,
					q,
					ix,
					iy,
					iz,
					iq
				)
			);
		}//end for

		for (unsigned int i = 0; i < numTemplateBoneKeys_; ++i)
		{
			templateBoneKeys_[i].shrinkToFit();
		}


		//FaceKey初期化
		std::set<std::string> uniqueFaceNames;

		//ユニークなface名のみ保存
		//ついでに整列
		for (unsigned int i = 0; i < vmd.faceLength_; ++i)
		{
			uniqueFaceNames.insert(std::string(vmd.pFaces_[i].FaceName));
		}

		numTemplateFaceKeys_ = uniqueFaceNames.size();
		if (numTemplateFaceKeys_ != 0)
		{
			//あらかじめ必要な分だけ初期化
			templateFaceKeys_.reset(new TemplateFaceKey[numTemplateFaceKeys_]);
			int fi = 0;
			for (auto it = uniqueFaceNames.begin(), end = uniqueFaceNames.end(); it != end; ++fi, ++it) {
				templateFaceKeys_[fi].setName(it->c_str());
			}
		}
		for (unsigned int i = 0; i < vmd.faceLength_; ++i)
		{
			TemplateFaceKey* key = std::lower_bound(templateFaceKeys_.get(), templateFaceKeys_.get() + numTemplateFaceKeys_, std::string(vmd.pFaces_[i].FaceName));

			assert(
				key != templateFaceKeys_.get() + numTemplateFaceKeys_ &&
				std::string(vmd.pFaces_[i].FaceName) == std::string(key->getName()) && "not found");
			float t = static_cast<float>(vmd.pFaces_[i].flameNo);
			key->insert(t, vmd.pFaces_[i].weight);
			if (maxFrame_ < t) maxFrame_ = t;
		}

		for (unsigned int i = 0; i < numTemplateFaceKeys_; ++i)
		{
			templateFaceKeys_[i].shrinkToFit();
		}


		//カメラ初期化
		if (vmd.cameraLength_ > 0) {
			//bug　開放できない　オーバーロードしたdeleteが呼ばれて正しいデストラクタが呼ばれない
			//原因　テンプレートが実体化したときCameraAnimationの型がわからないからdelete(void*)を呼び出す
			//解決方法　templateVMD.hからCameraAnimationが見えるようにCameraAnimation.hをincludeする
			//camera_.reset( new CameraAnimation );//bug発生
			//camera_.reset( new CameraAnimation, deleter() );//ok
			camera_ = std::make_shared<CameraAnimation>();//ok
			camera_->reserve(vmd.cameraLength_);
			for (unsigned int i = 0; i < vmd.cameraLength_; ++i)
			{
				typedef std::shared_ptr<BezierCurve> Bsptr;
				Bsptr ix, iy, iz, iq, il, iv;//interpolation

				const CVmd::VMD_CAMERA &c = vmd.pCameras_[i];
				ix = createIfNotFound(
					std::make_tuple(
						static_cast<float>(c.interpolationX[0]),
						static_cast<float>(c.interpolationX[2]),
						static_cast<float>(c.interpolationX[1]),
						static_cast<float>(c.interpolationX[3])),
					&uniques);

				iy = createIfNotFound(
					std::make_tuple(
						static_cast<float>(c.interpolationY[0]),
						static_cast<float>(c.interpolationY[2]),
						static_cast<float>(c.interpolationY[1]),
						static_cast<float>(c.interpolationY[3])),
					&uniques);

				iz = createIfNotFound(
					std::make_tuple(
						static_cast<float>(c.interpolationZ[0]),
						static_cast<float>(c.interpolationZ[2]),
						static_cast<float>(c.interpolationZ[1]),
						static_cast<float>(c.interpolationZ[3])),
					&uniques);

				iq = createIfNotFound(
					std::make_tuple(
						static_cast<float>(c.interpolationQ[0]),
						static_cast<float>(c.interpolationQ[2]),
						static_cast<float>(c.interpolationQ[1]),
						static_cast<float>(c.interpolationQ[3])),
					&uniques);

				il = createIfNotFound(
					std::make_tuple(
						static_cast<float>(c.interpolationL[0]),
						static_cast<float>(c.interpolationL[2]),
						static_cast<float>(c.interpolationL[1]),
						static_cast<float>(c.interpolationL[3])),
					&uniques);

				iv = createIfNotFound(
					std::make_tuple(
						static_cast<float>(c.interpolationV[0]),
						static_cast<float>(c.interpolationV[2]),
						static_cast<float>(c.interpolationV[1]),
						static_cast<float>(c.interpolationV[3])),
					&uniques);

				D3DXQUATERNION q;
				D3DXQuaternionRotationYawPitchRoll(
					&q,
					-c.rotate[1],
					-c.rotate[0],
					c.rotate[2]);

				camera_->insert(CameraOneFrameData(
					static_cast<float>(c.flameNo),
					c.length,
					D3DXVECTOR3(c.position[0], c.position[1], c.position[2]),
					q,
					D3DXToRadian(c.viewAngleDegree),
					c.parth!=0,
					ix,
					iy,
					iz,
					iq,
					il,
					iv));
			}
		}
		return true;
	}
	std::pair< unsigned long, boost::shared_array<BoneKey> >
		TemplateVMD::createBoneKeyArray(
			Bone* bones, unsigned long boneNum) const
	{
		TemplateBoneKey *tbka = templateBoneKeys_.get();//TemplateBoneKeyArray
		unsigned long numBoneKeys = 0;
		for (unsigned long i = 0; i < numTemplateBoneKeys_; ++i) {
			Bone *bone = findNameInArray(bones, boneNum, tbka[i].getName());
			if (bone) {
				++numBoneKeys;
			}
		}

		boost::shared_array<BoneKey> boneKeyArray(new BoneKey[numBoneKeys]);
		unsigned long j = 0;
		for (unsigned long i = 0; i < numTemplateBoneKeys_; ++i) {
			Bone *bone = findNameInArray(bones, boneNum, tbka[i].getName());
			if (bone) {
				boneKeyArray[j].init(bone, tbka[i]);
				++j;
			}
			else {
				if (!hasPrinted_) {
					*const_cast<bool*>(&hasPrinted_) = true;
					TRACE3(
						"違うモデルで作られたモーションです。\n\
vmdファイル名:%s\n\
vmdヘッダー:%s\n\
作成モデル名:%s\n",
fileName_->c_str(), header_.c_str(), modelName_.c_str());
				}
			}
		}
		assert(j <= boneNum);
		return std::make_pair(numBoneKeys, boneKeyArray);
	}

	std::pair< unsigned long, boost::shared_array<FaceKey> >
		TemplateVMD::createFaceKeyArray(Face* faces, unsigned long numFaces)const {
		TemplateFaceKey *tfka = templateFaceKeys_.get();//TemplateBoneKeyArray

		unsigned long numFaceKeys = 0;
		for (unsigned long i = 0; i < numTemplateFaceKeys_; ++i) {
			Face *face = findNameInArray(faces, numFaces, tfka[i].getName());
			if (face) {
				++numFaceKeys;
			}
		}

		boost::shared_array<FaceKey> faceKeyArray(new FaceKey[numFaces]);
		unsigned long j = 0;
		for (unsigned long i = 0; i < numTemplateFaceKeys_; ++i) {
			Face *face = findNameInArray(faces, numFaces, tfka[i].getName());
			if (face) {
				faceKeyArray[j].init(face, tfka[i]);
				++j;
			}
			else {
				if (!hasPrinted_) {
					*const_cast<bool*>(&hasPrinted_) = true;
					TRACE3(
						"違うモデルで作られたモーションです。\n\
vmdファイル名:%s\n\
vmdヘッダー:%s\n\
作成モデル名:%s\n",
fileName_->c_str(), header_.c_str(), modelName_.c_str());
				}
			}
		}
		assert(j <= numFaces);
		return std::make_pair(numFaceKeys, faceKeyArray);
	}

	std::shared_ptr<Animation>
		TemplateVMD::create(
			Bone* bones, unsigned long numBones,
			Face* faces, unsigned long numFaces)
	{
		std::shared_ptr<Animation> ap(new Animation);
		ap->init(
			*this,
			bones, numBones,
			faces, numFaces);
		return ap;
	}


	bool TemplateVMD::isReady() {
		if (file_) {
			//load完了
			if (file_->isFinished()) {
				bool initOk = init(file_->data(), file_->size());
				assert(initOk);
				delete file_;
				file_ = 0;
				return true;
			}
			//loadまだ
			else {
				return false;
			}
			//初期化完了
		}
		else {
			return true;
		}
	}

	CameraAnimationSharedPtr TemplateVMD::getCameraAnimation()const {
		assert(camera_);
		return camera_;
	}
}