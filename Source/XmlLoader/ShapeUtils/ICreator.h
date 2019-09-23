#pragma once
#include<memory>
class btCollisionShape;
typedef std::shared_ptr<btCollisionShape> BtCollisionShapeSharedPtr;

namespace XmlLoader{ namespace ShapeUtils{

//ShapeBase?
class ICreator{
public:
	ICreator(){}
	virtual ~ICreator(){}
	virtual BtCollisionShapeSharedPtr createBtCollisionShape()=0;
};

} }