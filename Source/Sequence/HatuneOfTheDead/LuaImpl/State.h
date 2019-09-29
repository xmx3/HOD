#pragma once
#include"Sequence/HatuneOfTheDead/LuaImpl/Child.h"
#include<vector>
#include<memory>
#include"GameObject/SharedPtrs.h"

class btTransform;


namespace HOD {
	class EnemyManager;
	class  EnemySpawner;
}

namespace Camera {
	class HodCamera;
	typedef std::shared_ptr<HodCamera> HodCameraSharedPtr;;

}

namespace XmlLoader{ namespace GameObject{
	class Player;
	typedef std::unique_ptr<Player> PlayerUniquePtr;
	class Enemy;
	typedef std::shared_ptr<Enemy> EnemySharedPtr;
} }


namespace GameObject{
	class Enemy;
	class Stage;
}



namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{
class Resource;

class State {
public:
	static State* instance();
	void release();

	bool isReady();
	bool isClear()const;
	void update();
	void draw();

	void removeFromWorldAll();
	void resetBulletPhysics();


	void resetAll();

	void reserveEnemySpawn(const std::string &enemyName, float spawnTime, const btTransform& trans);

	void build(Resource*);

	GameObject::Player* getPlayer();

	//void setCameraAnimation( std::shared_ptr<MMD::CameraAnimation> cameraAnim);
	//void setPlayer(const GameObject::PlayerSharedPtr &player);
	//void setStage(const GameObject::StageSharedPtr &stage);

	void setNextSequence(Base* next);
	Base* getNextSequence();
	
	bool needDrawCall()const;
	void setNeedDrawCall(bool b);
	void addScore(int score);
	int getScore()const;
	int getNumberKilledEnemy()const;
	int getPlayerHp()const;
private:
	State();
	virtual ~State();

	struct Deleter
	{
		void operator()(State const* const p) const
		{
			delete p;
		}
	};
	typedef std::unique_ptr<State, Deleter > UptrState;
	static UptrState mThis;


	State( const State & )=delete;
	void operator=( const State & )=delete;

	Base* mNextSequence;

	GameObject::PlayerSharedPtr mPlayer;
	XmlLoader::GameObject::PlayerUniquePtr mTemplatePlayer;

	GameObject::StageSharedPtr	mStage;

	std::shared_ptr<Camera::HodCamera> mCameraAnimation;

	std::unique_ptr<HOD::EnemyManager> mEnemyManager;
	std::unique_ptr<HOD::EnemySpawner> mEnemySpawner;

	bool mNeedDrawCall;
	int mScore;
	int mNumberKilledEnemy;
};

}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
