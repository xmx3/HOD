#pragma once

namespace GameObject{ namespace EnemyUtils { namespace Updater {


class Base{
public:
	virtual ~Base(){} //‚È‚É‚à‚µ‚È‚¢‚Ì‚Å‚±‚ê‚Å‚¢‚¢
	virtual Base* update( Base*, float dt ) = 0;
};

} } } //GameObject::EnemyUtils::Updater

