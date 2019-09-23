#ifndef __GAMEOBJECT_ENEMYUTILS_MANAGER_H__
#define __GAMEOBJECT_ENEMYUTILS_MANAGER_H__
#include<memory>
#include<map>
#include<list>
#include<string>
#include"GameObject/SharedPtrs.h"

class btTransform;
class btCollisionObject;
class Enemy;
namespace GameObject{
namespace EnemyUtils{
class Manager {
public:
	static Manager* instance();
	static void destroy();

	//reserveSpawn(EnemySharedPtr, time)
	//spawn
	std::shared_ptr<Enemy> create( const char *name, const btTransform &startTrans, bool doEnemyAddToWorld  );
	bool registerEnemy(EnemySharedPtr);
private:
	Manager();
	~Manager();

	//disallow assign
	Manager( const Manager & );
	//disallow copy
	void operator=( const Manager & );
	struct Deleter
	{
		void operator()( Manager const* const p ) const
		{
			delete p;
		}
	};

	typedef std::unique_ptr< Manager, Deleter > UptrManager;
	static UptrManager mThis;

	typedef int TemplateEnemySharedPtr;
	std::map<std::string, TemplateEnemySharedPtr> mNameTemplateEnemyMap;

	std::list<IColliderSharedPtr> mLivingEnemies;
};

}// end namespace EnemyUtils
}// end namespace GameObject
#endif