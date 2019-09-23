#pragma once
#include <memory>
#include <vector>
class FileLoader;

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

namespace Batch {
class StandardEffectBatch;
class PostEffectBatch;
typedef std::vector<Object::IObjectWeakPtr> DrawObjects;
typedef std::shared_ptr< DrawObjects > DrawObjectsSharedPtr;
} // namespace Batch


namespace Drawer{ namespace CutSceneImpl { namespace Light {
//デバッグ用にインターフェイスは同じで、ロード、描画を軽くした
class Impl {
public:
	static Impl* instance();
	static void destroy();
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
private:
	Batch::StandardEffectBatch*	mDrawGBuffer;
	Batch::PostEffectBatch*			mLuminous;
	Batch::PostEffectBatch*			mFxaa;
	Batch::PostEffectBatch*			mPointLight;
	FileLoader *mFileLoader;
	Batch::DrawObjectsSharedPtr mObjectsPtr;
	Batch::DrawObjectsSharedPtr mLightsPtr;

	Impl();
	~Impl();

	//disallow assign
	Impl( const Impl & )=delete;
	//disallow copy
	void operator=( const Impl & )=delete;
	struct Deleter
	{
		void operator()( Impl const* const p ) const
		{
			delete p;
		}
	};

	typedef std::unique_ptr< Impl, Deleter > Uptr;
	static Uptr mThis;

};
} } } }// namespace MME::Drawer::CutSceneImpl::Light
