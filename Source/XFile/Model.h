#pragma once
#include<d3dx9.h>
#include<string>
#include<boost/shared_array.hpp>

#include<GameLib/FileIO/InFile.h>
#include"XFile/Document.h"
#include"helper/FlyWeightTexture.h"

#include<GameLib/Graphics/Manager.h>
#include<GameLib/Math/Vector3.h>
#include<GameLib/Math/Vector4.h>
#include<GameLib/Math/Matrix34.h>
#include<GameLib/Graphics/IndexBuffer.h>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/Vertex.h>
#include"SegaTypeHelper.h"

#include"MME/Manager.h"

#include <btBulletDynamicsCommon.h>

namespace XFile{

struct Material {
	Material(){
		mTexture.resetWhiteTexture();
	}
	GameLib::Math::Vector4 mDiffuse; 
	GameLib::Math::Vector4 mAmbient; 
	GameLib::Math::Vector4 mSpecular;
	GameLib::Math::Vector4 mEmissive;
	float mPower;   
	FlyWeightTexture mTexture;
};

struct Subset {
	Subset()
		:mMaterialIndex(0),
		mFaceIndex(0),
		mFaceCount(0)
	{}

	unsigned long mMaterialIndex;
	unsigned long mFaceIndex;//開始面番号
	unsigned long mFaceCount;
};

struct Mesh{
	Mesh()
		:mNumMaterials(0),
		mMaterials(0),
		mNumSubsets(0),
		mSubsets(0)
	{}
	~Mesh(){
		delete[] mMaterials;
		mMaterials = 0;
		delete[] mSubsets;
		mSubsets = 0;
	}

	void setDiffuse( int i, const GameLib::Math::Vector4 &d ){
		mMaterials[i].mDiffuse = d;
	}

	void setSpecular( int i, const GameLib::Math::Vector4 &s ){
		mMaterials[i].mSpecular = s;
	}

	void setAmbient( int i, const GameLib::Math::Vector4 &a ){
		mMaterials[i].mAmbient = a;
	}

	void setEmissive( int i, const GameLib::Math::Vector4 &e ){
		mMaterials[i].mEmissive = e;
	}

	void setTexture( int i, const std::string &filename ){
		mMaterials[i].mTexture.reset( filename );
	}

	void setPower( int i, const float &power ){
		mMaterials[i].mPower = power;
	}

	void setSubset(
		int i, 
		unsigned long materialIndex,
		unsigned long faceIndex,//開始面番号
		unsigned long faceCount )
	{
		mSubsets[i].mMaterialIndex = materialIndex;
		mSubsets[i].mFaceIndex = faceIndex;
		mSubsets[i].mFaceCount = faceCount;
	}

	void createMaterials( unsigned long numMaterials ){
		mNumMaterials = numMaterials;
		delete [] mMaterials;
		mMaterials = 0;
		mMaterials = new Material[mNumMaterials];
	}

	void createSubsets( unsigned long numSubsets ){
		mNumSubsets = numSubsets;
		delete [] mSubsets;
		mSubsets=0;
		mSubsets = new Subset[mNumSubsets];
	}

	bool isReady(){
		for( unsigned int i=0; i<mNumSubsets; ++i ){
			if( !(mMaterials[ mSubsets[i].mMaterialIndex ].mTexture.isReady()) )
			{
				return false;
			}
		}
		return true;
	}


	unsigned long mNumMaterials;
	Material *mMaterials;
	unsigned long mNumSubsets;
	Subset *mSubsets;
	GameLib::Graphics::VertexBuffer mVertexBuffer;
	GameLib::Graphics::IndexBuffer mIndexBuffer;

	void draw( const GameLib::Math::Matrix34 &w34 ) const{
		GameLib::Graphics::Manager m;
		m.setVertexBuffer( mVertexBuffer );
		m.setIndexBuffer( mIndexBuffer );
		for( unsigned int i=0; i<mNumSubsets; ++i ){
			const Material & mtrl = mMaterials[ mSubsets[i].mMaterialIndex ];
			m.setDiffuseColor( mtrl.mDiffuse );
			m.setAmbientColor( mtrl.mAmbient );
			m.setSpecularColor( mtrl.mSpecular );
			m.setEmissionColor( mtrl.mEmissive  );
			m.setSpecularSharpness( mtrl.mPower );
			m.setTransparency( mtrl.mDiffuse.w );
			//if( !mMaterials[ mSubsets[i].mMaterialIndex ].mTexture.isReady() ){}
			m.setTexture( mMaterials[ mSubsets[i].mMaterialIndex ].mTexture );
			m.drawIndexed( mSubsets[i].mFaceIndex, mSubsets[i].mFaceCount );
		}
	}

	void drawByMME( const D3DXMATRIX &world ) const{
		::MME::Manager *mmem = ::MME::Manager::instance();// Miku Miku Effect Manager
		mmem->enableVertexBlend( false );

		//バッファをセット
		mmem->setVertexBuffer( mVertexBuffer );
		mmem->setIndexBuffer( mIndexBuffer );


		// サブセットの描画
		for (unsigned int subsetIdx=0; subsetIdx<mNumSubsets; ++subsetIdx) {
		
			const Subset& subset = mSubsets[subsetIdx];
		
			// 色、テクスチャ
			unsigned long mi=subset.mMaterialIndex;
			const Material & material = mMaterials[ mSubsets[mi].mMaterialIndex ];
			
			using namespace GameLib::Math;

			mmem->setDiffuseColor( material.mDiffuse );
			mmem->setAmbientColor( material.mAmbient );
			mmem->setSpecularColor( material.mSpecular );
			mmem->setSpecularSharpness( material.mPower );
			mmem->setEmissionColor( material.mEmissive );
			mmem->setToonColor( Vector4(1.f, 1.f, 1.f, 1.f) );
			mmem->setTexture( mMaterials[mi].mTexture );


			mmem->drawIndexed( subset.mFaceIndex, subset.mFaceCount );
		}

	}
};
typedef boost::shared_array<Mesh> MeshSharedArray;



class Model{
public:
	explicit Model(  const std::string &xFileName  )
	:mMeshs(),
	mFile(0),
	mIsError(false),
	mNumberMeshs(0),
	mFileName(xFileName),
	mBtMesh(0)
	{
		assert(!xFileName.empty());
		mFile = new GameLib::FileIO::InFile;
		*mFile = GameLib::FileIO::InFile::create( xFileName.c_str() );
	}
	~Model(){
		delete mFile;
		mFile=0;
	}

	bool isFinished(){
		if( mFile ){
			if( mFile->isFinished() ){
				//Xファイルデータ構築
				XFile::Document xFile( mFile->data(), mFile->size() );
				if ( !xFile.isValid() ){
					assert(false);
					mIsError = true;
				}
				else{
					int pos = mFileName.rfind('/');
					
					std::tuple<
					MeshSharedArray,
					int
					> meshsAndNum = xFile.createMeshArray( mFileName.substr(0, pos+1) );
					mNumberMeshs = std::get<1>(meshsAndNum);
					mMeshs = std::get<0>(meshsAndNum);
				}
	
				delete mFile;
				mFile = 0;
				return false;
			}
			else{
				return false;
			}
		}else{
			for( int i=0; i<mNumberMeshs; ++i ){
				if( !mMeshs[i].isReady() ){
					return false;
				}
			}
			return true;
		}
	}
	bool isError()const{
		return mIsError;
	}

	GameLib::Graphics::VertexBuffer getVertexBuffer(){
		assert( mNumberMeshs==1 );//modelが複数VertexBufferを持つと考えると非常にめんどくさいので
		return mMeshs[0].mVertexBuffer;
	}
	GameLib::Graphics::IndexBuffer getIndexBuffer(){
		assert( mNumberMeshs==1 );//modelが複数VertexBufferを持つと考えると非常にめんどくさいので
		return mMeshs[0].mIndexBuffer;
	}

	void draw( const GameLib::Math::Matrix34 &w34 ) const{
		GameLib::Graphics::Manager m;
		m.enableVertexBlend(false);
		m.setWorldMatrix( w34 );
		for( int i=0; i<mNumberMeshs; ++i ){
			mMeshs[i].draw( w34 );
		}
	}
	void drawByMME( const D3DXMATRIX &world )const{
		
		::MME::Manager *mmem = ::MME::Manager::instance();// Miku Miku Effect Manager
		//zplot時に問題あり(仕様か？）
		//MMDと仕様をあわせるため
		//xファイルを１０倍するするため
		//lightworldMatrixは常時単位行列で良いような
		//現状以下のようになっているが
		// ライトの目線によるワールドビュー射影変換をする
		//Out.Pos = mul( Pos, LightWorldViewProjMatrix );

		//こっちのほうは正しいのでは
		//Out.Pos = mul( mul(Pos,World), LightWorldViewProjMatrix );

		mmem->setWorldMatrix( world );
		mmem->setLightWorldMatrix( 0, world );

		for( int i=0; i<mNumberMeshs; ++i ){
			mMeshs[i].drawByMME( world );
		}
	}

	const std::string& getFileName()const{
		return mFileName;
	}
	std::shared_ptr<btCollisionShape> createSharedBtCollisionShape(){
		//create btTriangleMesh
		if(!mBtMesh){
			assert( mNumberMeshs==1 );//modelが複数VertexBufferを持つと考えると非常にめんどくさいので
			assert( mNumberMeshs==1 );//modelが複数VertexBufferを持つと考えると非常にめんどくさいので
			
			mBtMesh =  createBtTriangleMesh();
		}

		std::shared_ptr<btCollisionShape> result = std::make_shared<btBvhTriangleMeshShape>( mBtMesh.get(), true );
		return result;
	}

	std::shared_ptr<btTriangleMesh> createBtTriangleMesh()
	{
		//create btTriangleMesh
		assert( mNumberMeshs==1 );//modelが複数VertexBufferを持つと考えると非常にめんどくさいので
		assert( mNumberMeshs==1 );//modelが複数VertexBufferを持つと考えると非常にめんどくさいので

		std::shared_ptr<btTriangleMesh> btMesh = std::make_shared<btTriangleMesh>();

		GameLib::Graphics::VertexBuffer vb = mMeshs[0].mVertexBuffer;
		GameLib::Graphics::IndexBuffer ib = mMeshs[0].mIndexBuffer;
		int numIndex=ib.indexNumber();

		GameLib::Graphics::Vertex* vertices = vb.lock();
		unsigned short* indieces = ib.lock();
		for(int i=0; i<numIndex; i+=3)
		{
			assert( ((numIndex)%3)==0 );

			unsigned short i0 = indieces[i];
			unsigned short i1 = indieces[i+1];
			unsigned short i2 = indieces[i+2];
			btVector3 v0(  vertices[i0].mPosition.x,  vertices[i0].mPosition.y,  vertices[i0].mPosition.z );
			btVector3 v1(  vertices[i1].mPosition.x,  vertices[i1].mPosition.y,  vertices[i1].mPosition.z );
			btVector3 v2(  vertices[i2].mPosition.x,  vertices[i2].mPosition.y,  vertices[i2].mPosition.z );

			//左手座標から右手
			btMesh->addTriangle(v0,v2,v1);
			//trimesh->addTriangle(v0,v1,v2);
		}
		vb.unlock(&vertices);
		ib.unlock(&indieces);
	
		return btMesh;
	}
private:
	int mNumberMeshs;
	MeshSharedArray mMeshs;
	const std::string mFileName;
	GameLib::FileIO::InFile *mFile;
	bool mIsError;
	std::shared_ptr<btTriangleMesh> mBtMesh;

};


}//end namespace XFile
