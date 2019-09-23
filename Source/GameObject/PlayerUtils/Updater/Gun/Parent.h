#pragma once
#include<memory>
#include"MME/Object/ModelKai.h"
#include"Input/PlayerMouse.h"
#include"../Child.h"
class btVector3;
class btRigidBody;

namespace GameObjectData{
	class Status;
}

namespace GameObject{
class Player;

namespace PlayerUtils { namespace Updater { namespace Gun {

namespace Root = GameObject::PlayerUtils::Updater;
class Child;
typedef Root::Parent GrandParent;



class Parent : public Root::Child {
public:
	Parent(Player*);
	~Parent();

	virtual Root::Base* update( GrandParent*, float dt);
//private:
	btRigidBody *mRigidBody;
	GameObjectData::Status *mStatus;
	MME::Object::ModelKai *mModel;
	Input::PlayerMouse *mMouse;
	Player* mPlayer;
	Root::Gun::Child* mChild;	
	//Camera::PlayerCamera *mCamera;shared_ptr
	//Input::PlayerMouse *mMouse;shared_ptr
};

} } } } //GameObject::PlayerUtils::Updater::SimpleWalker


