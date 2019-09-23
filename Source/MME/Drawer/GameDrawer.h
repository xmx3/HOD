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

//manager drawer batch ŒÂX‚Ì–ðŠ„‚ð‚æ‚­l‚¦‚ÄÝŒv‚·‚×‚«‚¾
//Drawer‚ðì‚Á‚½‚Ì‚Í_“î‚È•`‰æ‚ð‚µ‚½‚©‚Á‚½‚Ì‚Å
//
namespace Drawer {
class GameDrawer {
public:
	static GameDrawer* instance();
	static void destroy();
	bool isReady();
	
	void draw();
	
	void add( const Object::ModelKaiSharedPtr &);
	void add( const Object::PointLightSharedPtr &);
	void add( const Object::AccessorySharedPtr &);
	void add( const GameObject::AccessoryUtils::MME::ModelSharedPtr&);
	
	//void remove( obj )‚Í‘¦”pŠü‚Í‚µ‚È‚¢
	//íœ‚É‚È‚é‚½‚Ñ‚Éremove‚³‚¹‚é‚Æ
	//ƒRƒ“ƒeƒi‚ªvector‚È‚Ì‚Å’x‚¢(íœ‚µ‚½‚Æ‚±‚ë‚ð‚Â‚ß‚È‚¯‚ê‚Î‚È‚ç‚È‚¢)
	//‚È‚ç‚Îobj->setCanRemove(true);‚³‚¹‚é‚¾‚¯‚É‚µ‚Ä‚¢‚é
	//‚ ‚Æ‚Å‚Ü‚Æ‚ß‚Äíœ‚³‚¹‚½‚Ù‚¤‚ª‘‚¢
	//forceRemove‚ðì‚é‚×‚«‚©
	//‚ ‚Æíœ‚µ–Y‚ê‚Ä‚¢‚Ä‚àweak_ptr‚È‚Ì‚ÅƒŠƒ\[ƒX‚ªíœ‚³‚ê‚½‚çupdate()ŽšŽ©“®íœ‚·‚é
	//add‚Æremove‚Å‚í‚©‚è‚â‚·‚¢‚æ‚¤‚É‘ÎÌ«‚ª—~‚µ‚©‚Á‚½‚Ì‚Åremove‚ð‚Â‚­‚Á‚½B
	//ŽÀÛ‚È‚©‚Í
	//obj->setCanRemove(true);‚¾‚¯

	void remove(const Object::ModelKaiSharedPtr &);
	void remove(const Object::PointLightSharedPtr &);
	void remove(const Object::AccessorySharedPtr &);
	void remove(const GameObject::AccessoryUtils::MME::ModelSharedPtr&);


private:
	Batch::StandardEffectBatch*	mDrawGBuffer;
	Batch::PostEffectBatch*			mLuminous;
	Batch::PostEffectBatch*			mFxaa;
	Batch::PostEffectBatch*			mPointLight;
	FileLoader *mFileLoader;
	Batch::DrawObjectsSharedPtr mObjectsPtr;
	Batch::DrawObjectsSharedPtr mLightsPtr;

	GameDrawer();
	~GameDrawer();

	//disallow assign
	GameDrawer( const GameDrawer & );
	//disallow copy
	void operator=( const GameDrawer & );
	struct Deleter
	{
		void operator()( GameDrawer const* const p ) const
		{
			delete p;
		}
	};

	typedef std::unique_ptr< GameDrawer, Deleter > Uptr;
	static Uptr mThis;

};
} }  // namespace MME::Drawer
