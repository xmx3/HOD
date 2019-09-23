#pragma once

namespace MME{ namespace Object{
	class ModelKai;
} }

namespace Input{
class PlayerMouse;
}

namespace GameObjectData{
	class Status;
}

namespace GameObject{ 
	class Player;
namespace PlayerUtils { namespace Updater {

//この状態遷移の設計は
//1状態につき1つのアニメー^ションにしたほうが
//コードが分かりやすい

class Base{
public:
	virtual ~Base(){} //なにもしないのでこれでいい
	virtual Base* update( Base*, float dt ) = 0;
};

} } } //GameObject::PlayerUtils::Updater

