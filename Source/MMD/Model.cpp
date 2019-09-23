#define _CRT_SECURE_NO_WARNINGS
#include "Model.h"
#include "Pmd.h"
//#include "VertexData.h"
//#include "FastVertexData.h"
#include "VertexDataUsingVertexBlendShader.h"
#include "Bone.h"
#include "WrapperIK.h"
#include "Face.h"
#include "Animation.h"
#include "PMDRigidBody.h"
#include "PMDConstraint.h"
#include "ContainerHelper.h"
#include <stdio.h>
#include <algorithm>
#include <boost/timer.hpp>
#include <boost/lexical_cast.hpp>

#include"MMDDataBase.h"
#include"TemplatePMD.h"
#include"TemplateVMD.h"

#include<GameLib/FileIO/InFile.h>
#include"helper/PrimitiveDrawer.h"
#include"helper/MyOutputDebugString.h"

#include<GameLib/Graphics/Manager.h>

#ifdef _DEBUG
#define MODEL_TIME
#endif

namespace{

static const char skErrorIndex=-1;


template<typename T, std::size_t N> 
char (&lengthof_helper_char_array(T (&a)[N]))[N]; 
#define LENGTHOF(a) (sizeof(lengthof_helper_char_array(a)))
}

namespace MMD {

	//============================================================================
	// モデルの作成
	CModel::CModel()
		:pVertexData_(NULL),
		//rightAnkleIkBone_(NULL),
		//rightToeIkBone_(NULL),
		//leftAnkleIkBone_(NULL),
		//leftToeIkBone_(NULL),
		numMaterials_(0),
		numSubsets_(0),
		numBones_(0),
		numIks_(0),
		numFaces_(0),
		numRigidBodies_(0),
		rigidBodies_(nullptr),
		numConstraints_(0),
		frame_(0.f),
		loadingTemplatePMD_(0),
		isEnablePhysics_(false),
		weight_(0.f)
	{
	}
	CModel::~CModel() {
		removeFromWorld();
		SAFE_DELETE_ARRAY(rigidBodies_);
	}

	bool CModel::loadPMD(const char *fileName, bool isLoadBulletPysics) {
		assert(false && "use loadPMDFromDB");

		if (bones_) {
			assert(false && "dobled allocate!");
			return false;
		}

		GameLib::FileIO::InFile inFile = GameLib::FileIO::InFile::create(fileName);

		if (inFile.isError()) {
			return false;
		}
		while (!inFile.isFinished()) {}
		//GameLibを使わない読み込み
		//FILE	*pFile;
		//fpos_t	fposFileSize;
		//char *pData;

		//pFile = fopen( fileName, "rb" );
		//if( !pFile )	return false;	// ファイルが開けない

		// ファイルサイズ取得
		//fseek( pFile, 0, SEEK_END );
		//fgetpos( pFile, &fposFileSize );

		// メモリ確保
		//pData = (char *)malloc( (size_t)fposFileSize );

		// 読み込み
		//fseek( pFile, 0, SEEK_SET );
		//fread( pData, 1, (size_t)fposFileSize, pFile );

		//fclose( pFile );


		// モデルデータ初期化
		//bool	bRet = initPMD( pData, fposFileSize, isLoadBulletPysics );
		bool	bRet = initPMD(inFile.data(), inFile.size(), isLoadBulletPysics);
		assert(bRet && "モデルデータ初期化失敗");
		//free( pData );

		return bRet;
	}

	bool CModel::initPMD(const char *pData, unsigned long size, bool isLoadBulletPhiscs) {
		const char *pNext = pData;
		const char * const pDataTop = pData;
		// ヘッダのチェック
		const PMD_HEADER *pHeader = reinterpret_cast<const PMD_HEADER *>(pData);
		if (strcmp(pHeader->magic, "Pmd") != 0 || pHeader->version != 1.0f) {
			return false;	// ファイル形式が違う
		}
		// モデル名のコピー
		modelName_.reset(new std::string(pHeader->name));

		pNext += sizeof(PMD_HEADER);
		//頂点データの初期化
		pVertexData_.reset(new VertexDataUsingVertexBlendShader());
		pNext = pVertexData_->load(pNext);

		//真っ白テクスチャ準備
		//GameLib::Graphics::Texture whiteTexture = GameLib::Graphics::Texture::create( 1, 1, false );
		//unsigned* textureData;
		//int pitch;
		//whiteTexture.lock( &textureData, &pitch, 0 );
		//*textureData = 0xffffffff;
		//whiteTexture.unlock( &textureData );
		//textureData = 0;

		//materialの初期化
		numMaterials_ = *(reinterpret_cast<const unsigned long*>(pNext));
		pNext += sizeof(unsigned long);
		materials_.reset(new Material[numMaterials_]);

		for (unsigned long i = 0; i < numMaterials_; ++i) {
			const PMD_MATERIAL *pPMD = reinterpret_cast<const PMD_MATERIAL*>(pNext);
			Material *pM = &(materials_[i]);

			pM->diffuse_.set(
				pPMD->diffuse.r,
				pPMD->diffuse.g,
				pPMD->diffuse.b,
				pPMD->diffuse.a);

			pM->ambient_.set(
				pPMD->ambient.r,
				pPMD->ambient.g,
				pPMD->ambient.b,
				1.f);

			pM->specular_.set(
				pPMD->specular.r,
				pPMD->specular.g,
				pPMD->specular.b,
				1.f);

			pM->emissive_ = pM->ambient_;

			pM->power_ = pPMD->shininess;

			pM->isSphereTextureAdditive_ = false;

			// テクスチャ
			if (pPMD->textureFileName[0]) {
				assert(20 == sizeof(pPMD->textureFileName));
				assert(27 == strlen(MMD_DATA_PATH));
				assert(27 == LENGTHOF(MMD_DATA_PATH) - 1);//testしてないたぶん\0はいって28

				//\0入って欲しくないのでー1
				char filePath[LENGTHOF(pPMD->textureFileName) + LENGTHOF(MMD_DATA_PATH) - 1] = MMD_DATA_PATH;
				for (int i = 0; i < LENGTHOF(pPMD->textureFileName); ++i) {
					filePath[LENGTHOF(MMD_DATA_PATH) - 1 + i] = pPMD->textureFileName[i];
				}
				pM->texture_.reset(filePath);
				while (!pM->texture_.isReady())
				{
				}
			}
			else {
				pM->texture_.resetWhiteTexture();
			}

			pM->numEdges_ = pPMD->nEdges;
			pNext += sizeof(PMD_MATERIAL);
		}

		// サブセットの作成
		numSubsets_ = numMaterials_;
		subsets_.reset(new Subset[numSubsets_]);
		//合計のポリゴン数を格納するために使用
		DWORD numFace = 0;
		for (unsigned long i = 0, end = numMaterials_; i < end; ++i) {
			Subset* subset = &(subsets_[i]);
			subset->faceCount_ = materials_[i].numEdges_ / 3;
			subset->faceIndex_ = numFace;//開始面番号
			subset->materialIndex_ = i;
			numFace += subset->faceCount_;
		}

		//ボーンの初期化
		numBones_ = *(reinterpret_cast<const unsigned short*>(pNext));
		pNext += sizeof(unsigned short);

		bones_.reset(new Bone[numBones_]);
		rootBoneIndecies_.reset(new std::vector<int>);

		for (unsigned short i = 0; i < numBones_; ++i) {
			const PMD_BONE* pPMD = reinterpret_cast<const PMD_BONE*>(pNext);
			//どこに入っているか(配列)がほしいので遅延初期化
			bones_[i].init(bones_.get(), *pPMD, static_cast<int>(i));
			if (pPMD->parent == -1) {
				rootBoneIndecies_->push_back(i);
			}
			pNext += sizeof(PMD_BONE);
		}

		//IKの初期化
		numIks_ = *(reinterpret_cast<const unsigned short*>(pNext));
		pNext += sizeof(unsigned short);
		iks_.reset(new WrapperIK[numIks_]);

		for (unsigned short i = 0; i < numIks_; ++i) {
			//const PMD_IK* pPMD = reinterpret_cast<const PMD_IK*>(pNext);
			WrapperIK *pIK = &(iks_[i]);
			pNext = pIK->load(pNext, bones_.get(), numBones_);
		}

		//Faceの初期化
		numFaces_ = *(reinterpret_cast<const unsigned short*>(pNext));
		pNext += sizeof(unsigned short);
		faces_.reset(new Face[numFaces_]);

		Face *pBase = &(faces_[0]);
		pNext = pBase->load(pNext);
		for (unsigned short i = 1; i < numFaces_; ++i) {
			Face *pFace = &faces_[i];
			pNext = pFace->load(pNext);
			pFace->initalize(*pBase);
		}
#ifdef MODEL_TIME
		using namespace boost;
		boost::timer t; // タイマーの開始
#endif
	//サブセット, Faceを使ったソートをするためにここで初期化
		pVertexData_->init(subsets_.get(), numSubsets_, faces_.get(), numFaces_);
#ifdef MODEL_TIME
		OutputDebugStringA("VertexDataUsingVertexBlendShader::load() : ");
		OutputDebugStringA(lexical_cast<std::string>(t.elapsed()).c_str());
		OutputDebugStringA("\n");
		t.restart();
#endif


		enablePhysics(isLoadBulletPhiscs);
		if (isLoadBulletPhiscs) {
			unsigned long leftedDataSize = size - (pNext - pDataTop);
			bool b = skipPMDData(&pNext, pNext, leftedDataSize);
			assert(b && "");
			if (!b) { return false; }
			unsigned long bulletDataSize = size - (pNext - pDataTop);
			return loadBulletPhysics(pNext, bulletDataSize);
		}

		return true;

	}
	std::shared_ptr<Animation>  CModel::loadVMD(const char *fileName) {

		while (!isReady()) {}

		assert(bones_);
		// アニメーション初期化
		std::shared_ptr<Animation> anim =
			MMDDataBase::createAnimationVMD(
				fileName_->c_str(),
				fileName,
				bones_.get(), numBones_,
				faces_.get(), numFaces_
			);
		return anim;
	}

	void CModel::startWeightBlend()
	{
		weight_ = 1.f;
		for (std::vector<int>::iterator it = rootBoneIndecies_->begin(); it != rootBoneIndecies_->end(); ++it) {
			bones_[*it].saveWeightBlendMatrix();
		}

	}

	//アニメーションをウェイトで混ぜて使うことを想定してる
	//なので全てのアニメーションをまわす分が無駄
	//if文で速攻やめてるのでそこまで効率は悪くないが所詮アニメーションをブレンドする機会が多いとも思わない
	//この実装のいい点はインターフェイスがブレンドするときもしないときもひとつで済んでることだな
	void CModel::updateBone(const D3DXMATRIX &world ) {

		// アニメーションキーが関係するフレームの変形行列を計算
		if (currentAnimation_) {
			currentAnimation_->updateBones(bones_.get(), frame_);
		}
		// フレームの合成行列を計算
		for (std::vector<int>::iterator it = rootBoneIndecies_->begin(); it != rootBoneIndecies_->end(); ++it) {
			bones_[*it].updateSkinningMatrix(world);
		}
		
	}

	void CModel::updateWeightBlend() {
		for (std::vector<int>::iterator it = rootBoneIndecies_->begin(); it != rootBoneIndecies_->end(); ++it) {
			// アニメーション切り替え補間
			bones_[*it].exeWeightBlend(weight_);
		}
		if (weight_ > 0) {
			weight_ -= 0.1f;
			if (weight_ < 0) {
				weight_ = 0.f;
			}
		}

	}

	void CModel::updateVertex() {
	}

	void CModel::updateIK() {
		for (unsigned short i = 0; i < numIks_; ++i)
		{
			WrapperIK* ik = &iks_[i];
			ik->solve(bones_.get());
		}
	}

	//表情を複数のアニメーションから求める必要あるの？
	//ひとつの表情だけで良くないか？笑いながら起こるとか複数のアニメーションを合成すると笑いながら怒るとかできる
	void CModel::updateFace() {
		if (currentAnimation_) {
			currentAnimation_->updateFace(frame_);
		}
	}

	void CModel::updateFaceVertex() {
		pVertexData_->updateFaceVertex(faces_.get(), numFaces_);
	}

	void CModel::draw() {
		//using namespace boost;
		//boost::timer t; // タイマーの開始
		using namespace GameLib::Graphics;
		Manager m = Manager::instance();
		m.setBlendMode(BLEND_LINEAR);
		//MMDオブジェクトはカメラ左手座標系で書かれたいので
		//カメラ右手座標系で書く場合はCULL_BACK
		m.setCullMode(CULL_FRONT);
		m.enableDepthTest(true);
		m.enableDepthWrite(true);

		GameLib::Math::Matrix34 matW;
		matW.setIdentity();
		m.setWorldMatrix(matW);
		pVertexData_->draw(
			bones_.get(), numBones_,
			subsets_.get(), numSubsets_,
			materials_.get(), numMaterials_);
		//OutputDebugStringA( "draw(): " );
		//OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
		//OutputDebugStringA( "\n" );
		//t.restart();
	}

	void CModel::drawByMME() {
		//using namespace boost;
		//using namespace GameLib::Graphics;
		//Manager m = Manager::instance();
		////boost::timer t; // タイマーの開始
		//m.setBlendMode( BLEND_LINEAR );
		//m.setCullMode( CULL_FRONT );
		//m.enableDepthTest( true );
		//m.enableDepthWrite( true );

		pVertexData_->drawByMME(
			bones_.get(), numBones_,
			subsets_.get(), numSubsets_,
			materials_.get(), numMaterials_);
		//OutputDebugStringA( "draw(): " );
		//OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
		//OutputDebugStringA( "\n" );
		//t.restart();
	}
	void CModel::debugDraw() {
		//BulletPhysics::Manager::instance()->drawWorld();
		//BOOST_FOREACH(PMDConstraint* pC, constraints_){ pC->draw(); }
		//BOOST_FOREACH(PMDRigidBody *pR, rigidBodies_){
			//pR->debugDraw();
		//}
		for (unsigned short i = 0; i < numIks_; ++i) {
			WrapperIK *ik = &iks_[i];
			Bone *bonearray = bones_.get();;
			D3DXVECTOR3 pos = bonearray[ik->getIndex()].getPos();
			PrimitiveDrawer::drawSphere(pos, 1.f, 0xffff8888);
		}
	}
	void CModel::update(const D3DXMATRIX &world, bool enablePhiscs) {

		//using namespace boost;
		//boost::timer t; // タイマーの開始

		if (enablePhiscs) {
			//using namespace boost;
			//boost::timer t; // タイマーの開始
			updateBone(world);
			//OutputDebugStringA( "updateBone(): " );
			//OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
			//OutputDebugStringA( "\n" );
			//t.restart();

			updateIK();
			//OutputDebugStringA( "updateIK(): " );
			//OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
			//OutputDebugStringA( "\n" );
			//t.restart();

			updateWeightBlend();


			updateFace();
			//OutputDebugStringA( "updateFace(): " );
			//OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
			//OutputDebugStringA( "\n" );
			//t.restart();

			updateFaceVertex();
			//OutputDebugStringA( "updateFaceVertex(): " );
			//OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
			//OutputDebugStringA( "\n" );
			//t.restart();

			updateRigidBody();
			//OutputDebugStringA( "updateRigidBody(): " );
			//OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
			//OutputDebugStringA( "\n" );
			//t.restart();

			//updateVertex();
			//OutputDebugStringA( "updateVertex(): " );
			//OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
			//OutputDebugStringA( "\n" );
			//t.restart();

		}
		else {
			updateBone(world);
			updateIK();
			updateFace();
			updateFaceVertex();
			updateVertex();
		}

		//OutputDebugStringA( "CModel::update(): " );
		//OutputDebugStringA( lexical_cast<std::string>(t.elapsed()).c_str() );
		//OutputDebugStringA( "\n" );
		//t.restart();

	}

	bool CModel::skipPMDData(const char **next, const char *pData, unsigned long size) {
		const char * const pDataTop = pData;

		//-----------------------------------------------------
		// ここから剛体情報まで読み飛ばし

		// 表情枠用表示リスト
		unsigned char	cbFaceDispNum = *((unsigned char *)pData);
		pData += sizeof(unsigned char);

		pData += sizeof(unsigned short) * cbFaceDispNum;

		// ボーン枠用枠名リスト
		unsigned char	cbBoneDispNum = *((unsigned char *)pData);
		pData += sizeof(unsigned char);

		pData += sizeof(char) * 50 * cbBoneDispNum;

		// ボーン枠用表示リスト
		unsigned long	ulBoneFrameDispNum = *((unsigned long *)pData);
		pData += sizeof(unsigned long);

		pData += 3 * ulBoneFrameDispNum;

		// 後続データの有無をチェック
		if ((unsigned long)pData - (unsigned long)pDataTop >= size) {
			return false;
		}

		// 英語名対応
		unsigned char	cbEnglishNameExist = *((unsigned char *)pData);
		pData += sizeof(unsigned char);

		if (cbEnglishNameExist)
		{
			// モデル名とコメント(英語)
			pData += sizeof(char) * 276;

			// ボーン名(英語)
			pData += sizeof(char) * 20 * numBones_;

			// 表情名(英語)
			pData += sizeof(char) * 20 * (numFaces_ - 1);	// "base"は英語名リストには含まれない

			// ボーン枠用枠名リスト(英語)
			pData += sizeof(char) * 50 * (cbBoneDispNum);
		}

		// 後続データの有無をチェック(ここのチェックは不要かも)
		if ((unsigned long)pData - (unsigned long)pDataTop >= size) {
			return false;
		}

		// トゥーンテクスチャリスト
		pData += 100 * 10;		// ファイル名 100Byte * 10個

		// ここまで読み飛ばし
		//-----------------------------------------------------
		*next = pData;
		return true;
	}

	bool CModel::loadBulletPhysics(const char *pData, unsigned long size) {
		const char * const pDataTop = pData;

		// 後続データの有無をチェック
		if ((unsigned long)pData - (unsigned long)pDataTop >= size) {
			return false;
		}

		//-----------------------------------------------------
		// 剛体数取得
		numRigidBodies_ = *((unsigned long *)pData);
		pData += sizeof(unsigned long);

		// 剛体配列を作成
		if (numRigidBodies_)
		{

			rigidBodies_ = new std::shared_ptr<PMDRigidBody>[numRigidBodies_];

			for (unsigned long i = 0; i < numRigidBodies_; ++i) {
				rigidBodies_[i] = PMDRigidBody::create();
				PMDRigidBody *pRbody = rigidBodies_[i].get();


				const PMD_RigidBody *pPMDRigidBody = (const PMD_RigidBody *)pData;

				Bone *pBone = NULL;
				if (pPMDRigidBody->unBoneIndex == 0xFFFF) {
					pBone = findNameInArray(bones_.get(), numBones_, "センター");
				}
				else {
					pBone = &(bones_[pPMDRigidBody->unBoneIndex]);
				}
				pRbody->initialize(pPMDRigidBody, pBone);
				pData += sizeof(PMD_RigidBody);
			}
		}

		//-----------------------------------------------------
		// コンストレイント数取得
		numConstraints_ = *((unsigned long *)pData);
		pData += sizeof(unsigned long);

		// コンストレイント配列を作成
		if (numConstraints_)
		{
			constraints_.reset(new PMDConstraint[numConstraints_]);
			for (unsigned long i = 0; i < numConstraints_; ++i) {
				PMDConstraint *pC = &constraints_[i];

				const PMD_Constraint *pPMDConstraint = (const PMD_Constraint *)pData;

				PMDRigidBody *pRigidBodyA = rigidBodies_[pPMDConstraint->ulRigidA].get();
				PMDRigidBody *pRigidBodyB = rigidBodies_[pPMDConstraint->ulRigidB].get();

				pC->initialize(pPMDConstraint, pRigidBodyA, pRigidBodyB);
				pData += sizeof(PMD_Constraint);
			}
		}

		return true;
	}
	void CModel::updateRigidBody() {

		for (unsigned long i = 0; i < numRigidBodies_; ++i)
		{
			rigidBodies_[i]->updateBoneTransform();
		}
	}

	void CModel::enablePhysics(bool enabled) {
		//計算量減らすため
		//ikを全部計算してもかまわないが無駄になるため
		//mmdの実装だと全部trueか？
		for (unsigned long i = 0; i < numIks_; ++i)
		{
			if (enabled) {
				WrapperIK *pIK = &iks_[i];
				unsigned short bi = pIK->getIndex();
				const char *name = bones_[bi].getName();
				if (strcmp(name, "右足ＩＫ") == 0) {
					pIK->setEnable(true);
					//TRACE1("%s enable ik\n",name);
				}
				else if (strcmp(name, "右足つまさきＩＫ") == 0) {
					pIK->setEnable(true);
					//TRACE1("%s enable ik\n",name);
				}
				else if (strcmp(name, "左足ＩＫ") == 0) {
					pIK->setEnable(true);
					//TRACE1("%s enable ik\n",name);
				}
				else if (strcmp(name, "左足つまさきＩＫ") == 0) {
					pIK->setEnable(true);
					//TRACE1("%s enable ik\n",name);
				}
				else {
					pIK->setEnable(false);
					//TRACE1("%s disable ik\n",name);
				}
			}
			else {
				WrapperIK *pIK = &iks_[i];
				pIK->setEnable(true);
			}
		}
	}


	bool CModel::isFrameOver() const {
		return  currentAnimation_ && frame_ >= currentAnimation_->getMaxFrame();
	}

	void CModel::fitRigidBodeisToBone(const D3DXMATRIX &world) {
		updateBone(world);

		for (unsigned long i = 0; i < numRigidBodies_; ++i) {
			rigidBodies_[i]->fitBone();
		}
	}

	void CModel::resetBones(const D3DXMATRIX &world) {
		Bone* barray = bones_.get();
		for (unsigned long i = 0; i < numBones_; ++i) {
			barray[i].reset();
		}
		updateBone(world);
	}

	Bone* CModel::getBone(const char *name) {
		return findNameInArray(bones_.get(), numBones_, name);
	}
	Bone* CModel::getBone(int index) {
		return &bones_[index];
	}


	//void CModel::setHeightFootIKBones( float groundHeight ){
	//	//assert( rightAnkleIkBone_ && rightToeIkBone_ && leftAnkleIkBone_ && leftToeIkBone_ 
	//	//	&& 
	//	//	"rightAnkleIkBone_ and etc must be not NULL, \
	//	//	Please set right bone name Using setRightFootIKBone(), \
	//	//	Or Use update( world, enablePhysics) instead Of update( world, groundHeight, enablePhsics)." );
	//	if( rightAnkleIkBone_  )
	//	{
	//		rightAnkleIkBone_->getSkinningMatrix()._42 = groundHeight;
	//	}
	//	
	//	if( rightToeIkBone_  )
	//	{
	//		rightToeIkBone_->getSkinningMatrix()._42 = groundHeight;
	//	}
	//	
	//	if( leftAnkleIkBone_  )
	//	{
	//		leftAnkleIkBone_->getSkinningMatrix()._42 = groundHeight;
	//	}
	//
	//	if( leftToeIkBone_  )
	//	{
	//		leftToeIkBone_->getSkinningMatrix()._42 = groundHeight;
	//	}
	//}
	//
	//
	//bool CModel::setRightFootIKBone(const char* boneName )
	//{
	//	std::vector<Bone*>::iterator end=bones_.end();
	//	std::vector<Bone*>::iterator it= bones_ | find_name( boneName );
	//	if( it==end ){
	//		assert( false && boneName && " is not found." );
	//		return false;
	//	}
	//	rightAnkleIkBone_ = *it;
	//	return true;
	//}
	//
	//bool CModel::setLeftFootIKBone(const char* boneName )
	//{
	//	std::vector<Bone*>::iterator end=bones_.end();
	//	std::vector<Bone*>::iterator it= bones_ | find_name( boneName );
	//	if( it==end ){
	//		assert( false && boneName && " is not found." );
	//		return false;
	//	}
	//	leftAnkleIkBone_ = *it;
	//	return true;
	//}
	//bool CModel::setRightToeIKBone(const char* boneName )
	//{
	//	std::vector<Bone*>::iterator end=bones_.end();
	//	std::vector<Bone*>::iterator it= bones_ | find_name( boneName );
	//	if( it==end ){
	//		assert( false && boneName && " is not found." );
	//		return false;
	//	}
	//	rightToeIkBone_ = *it;
	//	return true;
	//}
	//
	//bool CModel::setLeftToeIKBone(const char* boneName )
	//{
	//	std::vector<Bone*>::iterator end=bones_.end();
	//	std::vector<Bone*>::iterator it= bones_ | find_name( boneName );
	//	if( it==end ){
	//		assert( false && boneName && " is not found." );
	//		return false;
	//	}
	//	leftToeIkBone_ = *it;
	//	return true;
	//}

	//右足(足首)とつま先のIKの目標位置のyを指定の高さにしてupdate()
	//void CModel::update(  const D3DXMATRIX &world, float groundHeight, bool enablePhiscs ){
	//	if( enablePhiscs ) {
	//		updateBone(world);
	//		
	//		setHeightFootIKBones(groundHeight);
	//		
	//		updateIK();
	//
	//		updateFace();
	//
	//		updateFaceVertex();
	//			
	//		updateRigidBody();
	//
	//		updateVertex();
	//		
	//	}
	//	else {
	//		updateBone(world);
	//		setHeightFootIKBones(groundHeight);		
	//		updateIK();
	//		updateFace();
	//		updateFaceVertex();
	//		updateVertex();
	//	}
	//
	//}


	bool CModel::loadPMD(const GameLib::FileIO::InFile &inFile, bool isLoadBulletPysics) {
		assert(false && "use loadPMDFromDB");
		if (bones_) {
			assert(false && "dobled allocate!");
			return false;
		}

		if (inFile.isError()) {
			assert(false);
			return false;
		}

		while (!inFile.isFinished()) {}

		// モデルデータ初期化
		bool	bRet = initPMD(inFile.data(), inFile.size(), isLoadBulletPysics);
		assert(bRet && "モデルデータ初期化失敗");

		return bRet;
	}

	void CModel::build(const TemplatePMDSharedPtr & pmd, bool isEnableBulletPysics) {
		fileName_ = pmd->fileName_;
		modelName_ = pmd->modelName_;

		pVertexData_ = pmd->pVertexData_;

		numMaterials_ = pmd->numMaterials_;
		materials_ = pmd->materials_;
		numSubsets_ = pmd->numSubsets_;
		subsets_ = pmd->subsets_;

		//ボーンの作成、初期化
		numBones_ = pmd->numBones_;
		bones_.reset(new Bone[numBones_]);
		rootBoneIndecies_.reset(new std::vector<int>);

		for (unsigned short i = 0; i < numBones_; ++i) {
			const PMD_BONE &pmdbone = pmd->bonesData_[i];
			//どこに入っているか(配列)がほしいので遅延初期化
			bones_[i].init(bones_.get(), pmdbone, static_cast<int>(i));
			if (pmdbone.parent == -1) {
				rootBoneIndecies_->push_back(i);
			}
		}
		rootBoneIndecies_->shrink_to_fit();

		numIks_ = pmd->numIks_;
		iks_ = pmd->iks_;

		numFaces_ = pmd->numFaces_;
		faces_ = pmd->faces_;

		toonColors_ = pmd->toonColors_;
		toonTextures_ = pmd->toonTextures_;

		if (isEnableBulletPysics) {
			numRigidBodies_ = pmd->numRigidBodies_;
			// 剛体配列を作成
			if (numRigidBodies_)
			{
				Bone *pCenterBone = findNameInArray(bones_.get(), numBones_, "センター");
				rigidBodies_ = new std::shared_ptr<PMDRigidBody>[numRigidBodies_];
				for (unsigned long i = 0; i < numRigidBodies_; ++i) {
					rigidBodies_[i] = PMDRigidBody::create();
					PMDRigidBody *pRbody = rigidBodies_[i].get();

					const PMD_RigidBody &refPMDRigidBody = pmd->rigidBodiesData_[i];

					Bone *pBone = NULL;
					if (refPMDRigidBody.unBoneIndex == 0xFFFF) {
						pBone = pCenterBone;
					}
					else {
						pBone = &(bones_[refPMDRigidBody.unBoneIndex]);
					}
					pRbody->initialize(&refPMDRigidBody, pBone);
				}
			}

			numConstraints_ = pmd->numConstraints_;

			// コンストレイント配列を作成
			if (numConstraints_)
			{
				constraints_.reset(new PMDConstraint[numConstraints_]);
				for (unsigned long i = 0; i < numConstraints_; ++i) {
					PMDConstraint *pC = &constraints_[i];

					const PMD_Constraint *pPMDConstraint = &pmd->constraintsData_[i];

					PMDRigidBody *pRigidBodyA = rigidBodies_[pPMDConstraint->ulRigidA].get();
					PMDRigidBody *pRigidBodyB = rigidBodies_[pPMDConstraint->ulRigidB].get();

					pC->initialize(pPMDConstraint, pRigidBodyA, pRigidBodyB);
				}
			}
		}
		enablePhysics(isEnableBulletPysics);
	}


	void CModel::loadPMDFromDB(const char *fileName, bool isEnableBulletPysics) {
		isEnablePhysics_ = isEnableBulletPysics;
		loadingTemplatePMD_ = MMDDataBase::loadPMD(fileName);
		assert(loadingTemplatePMD_);
		if (loadingTemplatePMD_) {
			if (loadingTemplatePMD_->isReady()) {
				build(loadingTemplatePMD_, isEnableBulletPysics);
				loadingTemplatePMD_.reset();
			}
		}
		return;
	}

	const std::string & CModel::getFileName()const {
		return *fileName_;
	}

	bool CModel::isReady() {
		if (loadingTemplatePMD_) {
			if (loadingTemplatePMD_->isReady()) {
				//load完了なので初期化
				build(loadingTemplatePMD_, isEnablePhysics_);
				loadingTemplatePMD_.reset();
				return true;
			}
			else {
				//load中
				return false;
			}
		}
		else {
			return true;
		}
	}

	void CModel::addToWorld() {

		for (unsigned long i = 0; i < numRigidBodies_; ++i) {
			rigidBodies_[i]->addToWorld();
		}

		for (unsigned long i = 0; i < numConstraints_; ++i) {
			constraints_[i].addToWorld();
		}
	}

	void CModel::removeFromWorld() {
		for (unsigned long i = 0; i < numRigidBodies_; ++i) {
			rigidBodies_[i]->removeFromWorld();
		}

		for (unsigned long i = 0; i < numConstraints_; ++i) {
			constraints_[i].removeFromWorld();
		}
	}






	void CModel::setVelocityZeroRigidBodies() {
		for (unsigned long i = 0; i < numRigidBodies_; ++i) {
			rigidBodies_[i]->setVelocityZero();
		}

	}

}