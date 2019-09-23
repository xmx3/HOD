#include"Shape.h"
#include"ShapeUtils/Cylinder.h"
#include"ShapeUtils/Box.h"
#include"ShapeUtils/Mesh.h"
#include"ShapeUtils/ShareMesh.h"
#include<boost/optional.hpp>
#include<GameLib/GameLib.h>
#include<GameLib/Base/RefString.h>
#include<GameLib/PseudoXml/Element.h>
#include<GameLib/PseudoXml/Attribute.h>
#include<assert.h>

namespace XmlLoader {
namespace{
bool isXFile(const std::string & s )
{
	const std::string &extension=".x";
	int l = s.length();
	if(l==0){
		return false;
	}
	int pos = s.rfind(extension);
	if( pos==std::string::npos ){
		return false;
	}
	//std::cout << s << std::endl;
	//std::cout << "len "<< l << std::endl;
	//std::cout << "pos" << pos  << std::endl;
	//std::cout << l - pos << std::endl;
	return extension.length()==l-pos; 
}
}//end unnamespace


//ShapeSharedPtr Shape::create( 
//	const GameLib::PseudoXml::ConstElement &shapeElement,
//	const std::string modelFileName )//meshShapeを作るために欲しい
//{
//	using namespace GameLib::PseudoXml;
//	using GameLib::RefString;
//
//	boost::optional<std::string> type;
//	boost::optional<std::string> arguments;
//
//	//Shapeのパース;
//	if( RefString("Shape") == shapeElement.name() ){	
//		int num=shapeElement.attributeNumber();
//		for( int i=0; i<num; i++ ){
//			ConstAttribute a = shapeElement.attribute(i);
//			if( RefString("type") == a.name() ){
//				type =a.value();
//			} else if( RefString("arguments") == a.name() ){
//				arguments =a.value();
//			} else {
//				STRONG_ASSERT( false && "Shape Attribute is wrong!" );
//			}
//		}
//	}
//	assert(type);
//	assert(arguments);
//	
//	if( *type == "cylinder" ){}
//	else if( 
//		*type == "mesh" ||
//		*type == "sphere" ||
//		*type == "box" ||
//		*type == "capusel")
//	{
//		assert(false && "not impl" );
//		//meshはXFileにしか対応していない
//		assert( !(*type=="mesh") || isXFile( modelFileName) );
//		//ここでファイル名を使ってメッシュを作るがそのときflyweightを使って
//		//ロードしないことを確認しろ
//		//ok
//	}
//	else {
//		STRONG_ASSERT( false && "type attribute of Shape is wrong!" );
//	}
//	return std::make_shared<Shape>( *type, *arguments, modelFileName );
//}
//
//
//ShapeSharedPtr Shape::create(
//	const std::string modelFileName )//meshShapeを作るために欲しい
//{
//	return std::make_shared<Shape>( "", "", modelFileName );
//}

BtCollisionShapeAndBtTriangleMesh Shape::instanceBtCollisionShape(){
	using namespace ShapeUtils;
	if(mType=="cylinder"){
		Cylinder c( mType, mArguments );
		return BtCollisionShapeAndBtTriangleMesh( c.createBtCollisionShape(), nullptr );
	}
	else if(mType=="sphere"){
		assert(false && "not impl" );	
	}
	else if(mType=="box"){
		Box b( mType, mArguments );
		return BtCollisionShapeAndBtTriangleMesh( b.createBtCollisionShape(), nullptr );
	}
	else if(mType=="capusel"){
		assert(false && "not impl" );
	}
	else if(mType=="mesh"){
		assert( isXFile( mModelFile ) );
		Mesh m( mType, mArguments );
		return m.createBtCollisionShape();
	} else if(mType=="shareMesh"){
		ShareMesh c( mType, mArguments );
		return BtCollisionShapeAndBtTriangleMesh( c.createBtCollisionShape(), nullptr );
	}else {
		STRONG_ASSERT( false && "type attribute of Shape is wrong!" );
	}
	
	return BtCollisionShapeAndBtTriangleMesh( nullptr, nullptr );
}

bool Shape::isReady(){
	assert(false);
	return true;
}


}//end namespace XmlLoader
