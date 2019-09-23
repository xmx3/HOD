#ifndef __GAMEOBJECT_STAGE_STAGE_H__
#define __GAMEOBJECT_STAGE_STAGE_H__

#include<vector>
#include<GameLib/Math/Vector3.h>
#include"GameObject/SharedPtrs.h"
#include"GameObject/BaseObject.h"
#include<memory>


namespace MME {
	namespace Object{
		class Accessory;
		typedef std::shared_ptr<Accessory> AccessorySharedPtr;

	}
}

namespace GameLib{
	namespace Math{
		class Vector3;
		class Matrix44;
	}
}
class btRigidBody;

namespace GameObject {
class Stage;
typedef std::shared_ptr<Stage> StageSharedPtr;

//class Terrainに分割したほうがいいか？
//名前もsequenceとしてのstageなのか
//gameobjectとしてのstageなのかわかりにくい
//クリア関連イベントもここに持たせているけど、ここで管理するものなのか
//ゲームルールクラスとかほしいのか
//
//上のコメントあるけど
//多分これは俺がスクリプトでGameObjectを作りたいのか
//C++でGameObjectを作りたいかで変わってくる
//
//C++でGameObjectを作りたい場合はまあこのままでも問題ないだろう
//スクリプト側で作りたいと思うなら少なくとも上記のものをLuaで実装できるように
//しなければならないだろう
//
//Luaはレベルエディタでゲーム全体の振る舞いを作る気はないというのが現在の考えで変わりないのなら
//モデルとRigidBodyだけでいい


class Stage : public GameObject::BaseObject {
public:
	static StageSharedPtr create(const char * xmlInitStageFile );
	virtual ~Stage();
	void drawUsingGameLib();

	void createBvhTriangleMesh();
	
	RTTI_DECL;
	
	virtual btCollisionObject* getBtCollisionObject(){
		return NULL;
	}

	virtual void removeFromWorld();
	virtual void addToWorld();
	
	bool isClear()const {
		return mIsClear;
	}
	void handleEventThatDefeatedAllEnemies(){
		mIsClear = true;
	}

	bool isReady();

	virtual int calculateDamage()override;

	virtual bool canDamage()override;

	virtual const GameObjectData::WeaponStatus* getWeaponStatus()override;


private:
	//disallow raw pointer. use create()
	Stage( const char * xmlInitStageFile );
	//disallow assign
	Stage( const Stage & )=delete;
	//disallow copy
	void operator=( const Stage & )=delete;

	//XFile::Model				*mModel;
	MME::Object::AccessorySharedPtr		mModel;
	std::vector<btRigidBody*>	mRigidBodies;

	std::vector<EnemySharedPtr> mEnemies;

	bool mIsClear;
	bool mIsReady;
};


}//end namespace GameObject
#endif