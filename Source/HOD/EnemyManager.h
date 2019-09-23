#pragma once
#include<vector>
#include<memory>

namespace GameObject {
	class Enemy;
	typedef std::shared_ptr<Enemy> EnemySharedPtr;
}

namespace HOD {

class EnemyManager
{
public:
	EnemyManager() = default;
	~EnemyManager();

	void update(float elapsedTime);
	void postDraw();

	void add(const GameObject::EnemySharedPtr &enemy);
	void removeFromWorldAll();

private:
	EnemyManager(const EnemyManager&) = delete;
	void operator=(const EnemyManager&) = delete;

	std::vector<GameObject::EnemySharedPtr> mEnemies;

};

}