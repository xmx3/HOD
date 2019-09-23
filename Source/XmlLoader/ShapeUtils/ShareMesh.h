#pragma once
#include"helper/parseEquals.h"
#include<assert.h>
#include<boost/optional.hpp>
#include<boost/lexical_cast.hpp>
#include<boost/flyweight.hpp>
#include<boost/flyweight/key_value.hpp>

#include"XFile/Model.h"

#include<memory>
class btCollisionShape;
typedef std::shared_ptr<btCollisionShape> BtCollisionShapeSharedPtr;


namespace XmlLoader { namespace ShapeUtils {
//当たり判定の大きさを変えない場合はこちらを使う
//当たり判定のみにモデルを使う場合
//あらかじめ当たり判定のモデルをロードしておくこと,そのばあい当たり判定はshareMeshかempty(未実装)を指定するとよい
//ちょっと使いにくい
//例
//<Accessory0>
//  <name>negiShape</name>
//  <mass>0</mass>
//  <Model>
//    <xFile>Data/MMDData/Accessory/negiShape.x</xFile>
//    <scale>20</scale>
//  </Model>
//  <Shape>
//    <type>shareMesh</type>
//    <arguments>
//      scale=20;
//      xFile=Data/MMDData/Accessory/negiShape.x;
//    </arguments>
//  </Shape>
//</Accessory0>
class ShareMesh  {
public:
	ShareMesh( 
		const std::string &type,
		const std::string &arguments )
		:mScale(0.f),mModel(NULL)
	{
		assert(type=="shareMesh");

		boost::optional<float> scale;
		boost::optional<std::string> xfile;

		const char* pNext=arguments.c_str();
		while( pNext ){
			using boost::lexical_cast;
			std::string left,right;
			pNext = parseEquals( pNext, &left, &right );
			if( left=="scale"){
				assert( !scale && "doble assigned!");
				scale = lexical_cast<float>(right);
			} else if( left=="xFile"){
				assert( !xfile && "doble assigned!");
				xfile = right;
			} else{
				assert(left.empty()&&right.empty() );
			}
		}

		assert( scale &&
				xfile );
		
		mScale = *scale;
		mXFileName = *xfile;
		mModel = new boost::flyweights::flyweight<
		boost::flyweights::key_value< std::string, XFile::Model > >(mXFileName);
		assert( isReady() && "あらかじめモデルをロードしておくこと");		
	}

	virtual ~ShareMesh(){
		delete mModel;
		mModel=0;
	}
	
	virtual bool isReady(){
		return const_cast< XFile::Model&>(mModel->get()).isFinished();
	}

	virtual BtCollisionShapeSharedPtr createBtCollisionShape( )
	{
		BtCollisionShapeSharedPtr shape = const_cast< XFile::Model&>(mModel->get()).createSharedBtCollisionShape();
		const btVector3 &scale = shape->getLocalScaling();
		assert(
			scale == btVector3( 1.f, 1.f, 1.f ) ||
			scale == btVector3( mScale, mScale, mScale ) &&
			"use Mesh insted of SharedMesh." );
		shape->setLocalScaling( btVector3( mScale, mScale, mScale ) );
		return shape;
	}
private:
	float mScale;
	std::string mXFileName;
	boost::flyweights::flyweight<
		boost::flyweights::key_value<std::string, XFile::Model >
	> *mModel;
};
} }//end namespace XmlLoader::ShapeUtils
