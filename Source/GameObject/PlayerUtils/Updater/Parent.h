#pragma once
#include<memory>
#include"MME/Object/ModelKai.h"
#include"Input/PlayerMouse.h"

class btVector3;
class btRigidBody;

namespace GameObjectData{
	class Status;
}

namespace GameObject{ 
class Player;
namespace PlayerUtils { namespace Updater {
class Child;


class Parent{
public:
	Parent(Player*);
	~Parent();

	void update( float dt);
	Child* mChild;	
};

} } } //GameObject::PlayerUtils::Updater


