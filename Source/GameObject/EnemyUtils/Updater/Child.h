#pragma once
#include"Base.h"

namespace GameObject{ namespace EnemyUtils { namespace Updater {
class Parent;

class Child : public Base{
public:
	virtual ~Child();
	Base* update( Base*, float dt ); //これは実体を作ってやる
	virtual Base* update( Parent* , float dt ) = 0;
};

} } } //GameObject::EnemyUtils::Updater

