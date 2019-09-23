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

class Play : public Child{
public:
	Play();
	virtual ~Play();
	Base* update( Parent* );
private:
	Play( const Play & )=delete;
	void operator=( const Play & )=delete;

	GameObject::Player *mPlayer;
	typedef std::shared_ptr<GameObject::Enemy> SpEnemy;
	std::vector<SpEnemy> mEnemies;
};


}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
