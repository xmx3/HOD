#include "EnemyManager.h"
#include"GameObject/Enemy.h"

HOD::EnemyManager::~EnemyManager()
{
}

void HOD::EnemyManager::update(float elapsedTime)
{
	for (auto& e : mEnemies) {
		e->update(elapsedTime);
	}

}

void HOD::EnemyManager::postDraw()
{
	for (auto& e : mEnemies) {
		e->postdraw();
	}

}

void HOD::EnemyManager::add(const GameObject::EnemySharedPtr & enemy)
{
	mEnemies.push_back(enemy);
}

void HOD::EnemyManager::removeFromWorldAll()
{
	for (auto &e : mEnemies) {
		e->removeFromWorld();
	}

}
