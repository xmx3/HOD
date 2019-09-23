#pragma once
#include"../Base.h"

#include"MME/Object/ModelKai.h"
#include"Input/PlayerMouse.h"

class btVector3;
class btRigidBody;

namespace MME{ namespace Object{
	class ModelKai;
} }

namespace GameObjectData{
	class Status;
}

namespace GameObject{ namespace PlayerUtils { namespace Updater { namespace TameSword {
class Parent;

class Child : public Base{
public:
	Child(Parent *parent);
	virtual ~Child();
	Base* update( Base*, float dt ); //Ç±ÇÍÇÕé¿ëÃÇçÏÇ¡ÇƒÇ‚ÇÈ
	virtual Base* update( Parent* , float dt ) = 0;
protected:
	btRigidBody *mRigidBody;
	GameObjectData::Status *mStatus;
	MME::Object::ModelKai *mModel;
	Input::PlayerMouse *mMouse;
	Player* mPlayer;
};

} } } } //GameObject::PlayerUtils::Updater::TameSword

