#pragma once
#include<BulletCollision/CollisionShapes/btCylinderShape.h>
#include"helper/parseEquals.h"
#include"helper/copyWithoutSpaceAndNewLineChar.h"
#include<assert.h>
#include<boost/optional.hpp>
#include<boost/lexical_cast.hpp>

#include<memory>
class btCollisionShape;
typedef std::shared_ptr<btCollisionShape> BtCollisionShapeSharedPtr;

namespace XmlLoader { namespace ShapeUtils {

class Cylinder  {
public:
	Cylinder( 
		const std::string &type,
		const std::string &arguments )
	{
		assert(type=="cylinder");

		boost::optional<float> halfExtentX;
		boost::optional<float> halfExtentY;
		boost::optional<float> halfExtentZ;

		const char* pNext=arguments.c_str();
		while( pNext ){
			using boost::lexical_cast;
			std::string left,right;
			pNext = parseEquals( pNext, &left, &right );
			if( left=="halfExtentX"){
				assert( !halfExtentX && "doble assigned!");
				halfExtentX = lexical_cast<float>(right);
			} else if( left=="halfExtentY"){
				assert( !halfExtentY && "doble assigned!");
				halfExtentY = lexical_cast<float>(right);
			}else if( left=="halfExtentZ"){
				assert( !halfExtentZ && "doble assigned!");
				halfExtentZ = lexical_cast<float>(right);
			} else {
				assert(left.empty());
			}
		}

		assert( halfExtentX &&
				halfExtentY &&
				halfExtentZ );
		
		mHalfExtents.setValue(
			*halfExtentX,
			*halfExtentY,
			*halfExtentZ );
	}

	virtual ~Cylinder(){}
	
	virtual BtCollisionShapeSharedPtr createBtCollisionShape( )
	{
		//return std::make_shared<btCylinderShape>( mHalfExtents );
		
		std::shared_ptr<btCylinderShape> cylinder( new btCylinderShape(mHalfExtents) );
		return cylinder;
	}
private:
	btVector3 mHalfExtents;
};
} }//end namespace XmlLoader::ShapeUtils
