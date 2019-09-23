#pragma once

#include "Sequence/HatuneOfTheDead/LuaImpl/Child.h"
#include<memory>
#include<vector>
namespace GameObject{
	class Player;
	class Enemy;
}

class Stage;


namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{
class Parent;

class GameLoop : public Child{
public:
	GameLoop();
	virtual ~GameLoop();
	Base* update( Parent* );
private:
	GameLoop( const GameLoop & )=delete;
	void operator=( const GameLoop & )=delete;

	GameObject::Player *mPlayer;
	typedef std::shared_ptr<GameObject::Enemy> SpEnemy;
	std::vector<SpEnemy> mEnemies;
};


}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
