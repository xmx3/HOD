#include"Manager.h"

#include<GameLib/GameLib.h>
#include<GameLib/FileIO/InFile.h>
#include<GameLib/FileIO/Manager.h>

#include<GameLib/PseudoXml/Document.h>
#include<GameLib/PseudoXml/Element.h>
#include<GameLib/PseudoXml/Attribute.h>
#include<GameLib/Base/RefString.h>

#include"TemplateAccessory.h"
#include"MME/TemplateModel.h"


#include<BulletCollision/CollisionShapes/btBoxShape.h>
#include<BulletCollision/CollisionShapes/btSphereShape.h>
//#include<BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include"BulletPhysics/BulletPhysicsHelper.h"

#include"helper/MyOutputDebugString.h"


#include"GameObject/Accessory.h"
#include"MME/Manager.h"

namespace GameObject {
namespace AccessoryUtils {
Manager::UptrManager Manager::mThis=NULL;


namespace{
	using namespace GameLib::FileIO;
	using namespace GameLib::PseudoXml;
	using namespace GameLib::Scene;
	using GameLib::RefString;
	
	SptrShape createShape( float *mass, const ConstElement &e, const MME::SptrTemplateModel &model  ){
		assert( RefString("Shape") == e.name() );
		enum ShapeType{
			sphere=0,
			box,
			mesh
		};

		int shapeType=-1;
		
		float radius=0.f;
		float halfExtentX=0.f;
		float halfExtentY=0.f;
		float halfExtentZ=0.f;
		float scale=1.f;

		int num=e.attributeNumber();
		for( int i=0; i<num; i++ ){
			ConstAttribute a = e.attribute(i);
			if( RefString("type") == a.name() ){
				if( RefString("mesh") == a.value() ){
					shapeType=mesh;
				} else if( RefString("sphere") == a.value() ){
					shapeType=sphere;
				} else if( RefString("box") == a.value() ){
					shapeType=box;
				} else {
					STRONG_ASSERT( false && "type attribute of Shape is wrong!" );
				}
			} else if( RefString("scale") == a.name() ){
				scale=a.getFloatValue();
			} else if( RefString("radius") == a.name() ){
				radius=a.getFloatValue();
			} else if( RefString("halfExtentX") == a.name() ){
				halfExtentX=a.getFloatValue();
			} else if( RefString("halfExtentY") == a.name() ){
				halfExtentY=a.getFloatValue();
			} else if( RefString("halfExtentZ") == a.name() ){
				halfExtentZ=a.getFloatValue();
			} else if( RefString("mass") == a.name() ){
				if(mass){
					*mass=a.getFloatValue();
				}
			} else {
				STRONG_ASSERT( false && "Model Attribute is wrong!" );
			}
		}

		SptrShape shape;
		if( shapeType == sphere ){
			assert(radius!=0.f);
			shape.reset( new btSphereShape( radius ) );
		} else if( shapeType == box ){
			assert(halfExtentX!=0.f);
			assert(halfExtentY!=0.f);
			assert(halfExtentZ!=0.f);
			shape.reset( 
				new btBoxShape( 
					btVector3( halfExtentX, halfExtentY, halfExtentZ )
				)
			);
		} else if( shapeType == mesh ) {
			if(mass){
				*mass=0.f;
			}
			
			while( !model->isFinished() ){}		
			
			int primitiveNumber=model->getIndexBuffer().indexNumber()/3;

			shape.reset(
				BulletPhysicsHelper::createBvhTriangleMeshShape(
					model->getVertexBuffer(),
					model->getIndexBuffer(),
					0, primitiveNumber,
					scale, scale, scale )
			);
			
		} else {
			STRONG_ASSERT(false && "type attribute of Shape element is wrong!" );
		}
		
		return shape;
	}

	//void registToMME( std::shared_ptr<Accessory> obj, const char *effectFile ){
	//	if(effectFile==NULL){
	//		const std::string& file = obj->getModelFileName();
	//	
	//		int pos = file.rfind('.');
	//		if( pos != std::string::npos){
	//			std::string fxFileName( file, 0, pos+1 );
	//			fxFileName.append( "fx" );
	//			//file exist?
	//			GameLib::FileIO::Manager m;
	//			m.enableHaltOnError(false);
	//			GameLib::FileIO::InFile in = GameLib::FileIO::InFile::create( fxFileName.c_str() );
	//			while( !in.isFinished() ){}
	//			//file dont exist.
	//			if( in.isError() ){
	//				m.enableHaltOnError(true);
	//				MME::Manager::instance()->regist( obj, NULL );					
	//			}
	//			else{
	//				m.enableHaltOnError(true);
	//				MME::Manager::instance()->regist( obj, fxFileName.c_str() );
	//			}

	//		} else {
	//			MME::Manager::instance()->regist( obj, NULL );
	//		}
	//	} else {
	//		MME::Manager::instance()->regist( obj, effectFile );
	//	}
	//}
} //end anonymousnamespaace 


Manager* Manager::instance(){
	if( !mThis )
	{
		mThis.reset( new Manager );
	}
	return mThis.get();
}
Manager::Manager(){
	using namespace GameLib::FileIO; 
	using namespace GameLib::PseudoXml;
	using GameLib::RefString;
	InFile f = InFile::create("Data/GameObjectSetting/Accessory/TemplateAccessory.xml");
	
	if( f.isError() ){
		STRONG_ASSERT( false && "TemplateAccessory.xml file not error!" );
	}
	while( !f.isFinished() ) {}

	Document xml = Document::create( f.data(), f.size() );

	int numChild=xml.childNumber();
	for( int ic=0; ic<numChild; ++ic )
	{
		SptrShape shape;

		const char *name;
			
		ConstElement shapeElem;
		ConstElement modelElem;
	
		ConstElement e = xml.child(ic);
		if( RefString("TemplateAccessory") == e.name() )
		{
			int numAttributes = e.attributeNumber();
			assert( numAttributes==1 );
			for( int ia=0; ia<numAttributes; ++ia )
			{
				ConstAttribute a = e.attribute(ia);
				if( RefString("name") == a.name() ){
					name=a.value();
				} else {
					STRONG_ASSERT( false && "TemplateAccessory.xml file not error!" );
				}
			}
			
			int numGrandChild = e.childNumber();
			assert( numGrandChild<=2 );
			for( int igc=0; igc<numGrandChild; ++igc ){
				ConstElement gc = e.child(igc);
				
				if( RefString("Shape") == gc.name() ){
					STRONG_ASSERT( !shapeElem && "Shape is doubled.");
					shapeElem = gc;
				}
				else if( RefString("Model") == gc.name() ){
					STRONG_ASSERT( !modelElem && "Model is doubled.");
					modelElem = gc;
				}
				else{
					STRONG_ASSERT( false && "TemplateAccessory.xml file not error!" );
				}
			}
		}
		else{
			STRONG_ASSERT( false );
		}

		ScaleAndSptrTemplateModel scaleAndTemplModel;
		scaleAndTemplModel.first = 0.f;
		scaleAndTemplModel.second.reset();
		if( modelElem ){
			scaleAndTemplModel = createTemplateModel( modelElem );
		}
		float mass=0.f;

		if( shapeElem ){
			shape = createShape( &mass, shapeElem, scaleAndTemplModel.second );
		}

		SptrTemplateAccessory tac( new TemplateAccessory( shape, scaleAndTemplModel.second, mass, scaleAndTemplModel.first ) );
		TemplateAccessoryMapType::_Pairib pair= mNameTemplateAccessoryMap.insert( make_pair( std::string(name), tac ) );
		if( !pair.second ){
			assert( false && "template Accessory name doubled!" );
		}
	}
}

Manager::~Manager(){};
void Manager::destroy(){
	mThis.reset(NULL);
}

//std::shared_ptr<Accessory> Manager::createAccessory( const char *name,  btCollisionObject *owner,  CBone *bone, const char* effectFile ){
//	TemplateAccessoryMapType::iterator it = mNameTemplateAccessoryMap.find( name );
//	
//	if( it==mNameTemplateAccessoryMap.end() ){
//		TRACE1( "%s is not found\n", name );
//		STRONG_ASSERT( false && "not found!" );
//		return std::shared_ptr<Accessory>();
//	} else {
//
//		std::shared_ptr<Accessory> result = it->second->createAccessory( owner, bone );
//		return result;
//	}
//}


//std::shared_ptr<Accessory> Manager::createAccessory( const std::string &filename, shapeSharedPtr,  btCollisionObject *owner,  const btTransform &startTrans, const char* effectFile ){
std::shared_ptr<Accessory> Manager::createAccessory( const char *name,  btCollisionObject *owner,  const btTransform &startTrans, const char* effectFile ){
	TemplateAccessoryMapType::iterator it = mNameTemplateAccessoryMap.find( name );
	
	if( it==mNameTemplateAccessoryMap.end() ){
		TRACE1( "%s is not found\n", name );
		STRONG_ASSERT( false && "not found!" );
		return std::shared_ptr<Accessory>();
	} else {
		std::shared_ptr<Accessory> result = it->second->createAccessory( owner, startTrans );
		//MME::Manager::instance()->regist( result, "ShaderTest/AutoLuminous3/AL_Object.fxsub" );

		return result;
	}
}

//std::shared_ptr<Model> Manager::getAccessoryModel( const char *name ){
//	TemplateAccessoryMapType::iterator it = mNameTemplateAccessoryMap.find( name );
//	
//	if( it==mNameTemplateAccessoryMap.end() ){
//		TRACE1( "%s is not found\n", name );
//		STRONG_ASSERT( false && "not found!" );
//		return std::shared_ptr<Model>();
//	} else {
//		return it->second->getModel();
//	}
//}


 Manager::ScaleAndSptrTemplateModel Manager::createTemplateModel( const GameLib::PseudoXml::ConstElement &e){
		assert( RefString("Model") == e.name() );

		const char *modelFileName=NULL;
		float scale=1.f;

		int num=e.attributeNumber();
		for( int i=0; i<num; i++ ){
			ConstAttribute a = e.attribute(i);
			if( RefString("file") == a.name() ){
				modelFileName=a.value();
			} else if( RefString("scale") == a.name() ){
				scale=a.getFloatValue();
			} else {
				STRONG_ASSERT( false && "Model Attribute is wrong!" );
			}
		}
		assert( modelFileName );

		MME::SptrTemplateModel templModel;
		TemplateModelMapType::iterator it = mNameTemplateModelMap.find( modelFileName );

		if( it==mNameTemplateModelMap.end() ){
			templModel = std::make_shared<MME::TemplateModel>(modelFileName);
			mNameTemplateModelMap.insert( std::make_pair( modelFileName, templModel ) );
		} else{
			templModel = it->second;
		}
		
		assert( scale!=0.f );
		assert( templModel );
		

		return std::make_pair( scale, templModel );
	}



}// end namespace AccessoryUtils
}// end namespace GameObject