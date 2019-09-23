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

#include <btBulletDynamicsCommon.h>


namespace XmlLoader { namespace ShapeUtils {

//当たり判定の大きさ（メッシュの大きさ）を変えたりするばあいこちらを使う
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
class Mesh  {
public:
	Mesh( 
		const std::string &type,
		const std::string &arguments )
		:mScale(0.f),mModel(NULL)
	{
		assert(type=="mesh");

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

	virtual ~Mesh(){
		delete mModel;
		mModel=0;
	}
	
	virtual BtCollisionShapeAndBtTriangleMesh createBtCollisionShape( )
	{
		while(!isReady()){}
		BtTriangleMeshSharedPtr mesh =  const_cast< XFile::Model&>(mModel->get()).createBtTriangleMesh();
		BtCollisionShapeSharedPtr shape( new btBvhTriangleMeshShape( mesh.get(), true ) );
		shape->setLocalScaling( btVector3( mScale, mScale, mScale ) );
		return std::make_pair( shape, mesh ) ;
	}

	virtual bool isReady(){
		return const_cast< XFile::Model&>(mModel->get()).isFinished();
	}
private:
	float mScale;
	std::string mXFileName;
	boost::flyweights::flyweight<
		boost::flyweights::key_value<std::string, XFile::Model >
	> *mModel;
};
} }//end namespace XmlLoader::ShapeUtils
