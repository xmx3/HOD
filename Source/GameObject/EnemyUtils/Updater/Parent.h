#pragma once

namespace GameObject{ 
	class Enemy;
namespace EnemyUtils { namespace Updater {
class Child;


class Parent{
public:
	Parent(Enemy* enemy);
	~Parent();

	void update( float dt);
	Child* mChild;	
};

} } } //GameObject::EnemyUtils::Updater


