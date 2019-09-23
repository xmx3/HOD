#pragma once
#include <memory>
#include <vector>

namespace GameObject { namespace AccessoryUtils { namespace MME {
class Model;
typedef std::shared_ptr<Model>  ModelSharedPtr;
} } } //end namespace GameObject::AccessoryUtils::MME

namespace MME {

namespace Object{
class IObject;
typedef std::shared_ptr<IObject> IObjectSharedPtr;
	typedef std::weak_ptr<IObject> IObjectWeakPtr;
class ModelKai;
typedef std::shared_ptr<ModelKai> ModelKaiSharedPtr;
class PointLight;
typedef std::shared_ptr<PointLight> PointLightSharedPtr;
class Accessory;
typedef std::shared_ptr<Accessory> AccessorySharedPtr;
}//namespace Object

namespace Drawer { namespace CutScene {

void destroy();
bool isReady();
	
void draw();
	
void add( const Object::ModelKaiSharedPtr &);
void add( const Object::PointLightSharedPtr &);
void add( const Object::AccessorySharedPtr &);
void add( const GameObject::AccessoryUtils::MME::ModelSharedPtr&);
//void remove( obj )がない理由
//削除になるたびにremoveさせると
//コンテナがvectorなので遅い(削除したところをつめなければならない)
//ならばobj->setCanRemove(true);させて
//あとでまとめて削除させたほうが早い

} } }// namespace MME::Drawer::CutScene
