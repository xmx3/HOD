#ifndef __GAMEOBJECT_ACCESSORYUTILS_TEMPLATEACCESSORY_H__
#define __GAMEOBJECT_ACCESSORYUTILS_TEMPLATEACCESSORY_H__
#include<memory>

class btCollisionShape;
class btCollisionObject;
class btTransform;
class CBone;

namespace GameObject {
class Accessory;
namespace AccessoryUtils {
typedef std::shared_ptr<btCollisionShape> SptrShape;
namespace MME{
	class TemplateModel;
	typedef std::shared_ptr<MME::TemplateModel> SptrTemplateModel;

}


//衝突形状、モデルの大きさ、モデル(vertexbuffer, IndexBuffer, material)を共通して使いたい
class TemplateAccessory {
public:	
	TemplateAccessory(
		SptrShape shape,
		MME::SptrTemplateModel model,
		float mass,
		float scale );
	~TemplateAccessory();

	//std::shared_ptr<Accessory> createAccessory( btCollisionObject *owner, CBone *bone );
	std::shared_ptr<Accessory> createAccessory( btCollisionObject *owner, const btTransform &startTrans );

	//SptrModel getModel(){
	//	return mModel;
	//}
private:
	TemplateAccessory( const TemplateAccessory & );
	void operator=( const TemplateAccessory & );

	SptrShape mShape;
	MME::SptrTemplateModel mTemplateModel;
	float mMass;
	float mScale;
};
}//end namespace AccessoryUtils
}//end namespace GameObject
#endif
