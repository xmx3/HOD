#pragma once

#include "Sequence/HatuneOfTheDead/CppImpl/Child.h"
#include<memory>
#include<vector>
namespace GameObject{
	class Player;
	class Enemy;
}

class Stage;


namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{
class Parent;

class Play : public Child{
public:
	Play();
	virtual ~Play();
	bool isReady();
	Base* update( Parent* );
	void draw();
private:
	Play( const Play & )=delete;
	void operator=( const Play & )=delete;

	GameObject::Player *mPlayer;
	typedef std::shared_ptr<GameObject::Enemy> SpEnemy;
	std::vector<SpEnemy> mEnemies;
};


}}} //namespace Sequence::HatuneOfTheDead::CppImpl
