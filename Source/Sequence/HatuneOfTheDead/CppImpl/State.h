#pragma once
#include"Sequence/HatuneOfTheDead/CppImpl/Child.h"
#include<vector>
#include<memory>
#include"GameObject/SharedPtrs.h"


namespace MMD {
	class CameraAnimation;
}

namespace XmlLoader{ namespace GameObject{
	class Enemy;
	typedef std::shared_ptr<Enemy> EnemySharedPtr;
} }


namespace GameObject{
	class Enemy;
}



namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{

class State {
public:
	static State* instance();
	void release();



	bool isReady();
	bool isClear()const;
	void update();
	void draw();
	void setCameraAnimation( std::shared_ptr<MMD::CameraAnimation> cameraAnim);
	void setPlayer(const GameObject::PlayerSharedPtr &player);
	void setEnemy(const XmlLoader::GameObject::EnemySharedPtr &enemy);
	void setStage(const GameObject::StageSharedPtr &stage);
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

	GameObject::PlayerSharedPtr mPlayer;
	std::vector<GameObject::EnemySharedPtr> mEnemies;
	GameObject::StageSharedPtr	mStage;
	XmlLoader::GameObject::EnemySharedPtr mEnemy;

	std::shared_ptr<MMD::CameraAnimation> mCameraAnimation;

};

}}} //namespace Sequence::HatuneOfTheDead::CppImpl
