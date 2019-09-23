#pragma once
#include<memory>
#include"MME/Object/ModelKai.h"
#include"Input/PlayerMouse.h"
#include"../Child.h"
class btVector3;
class btRigidBody;

/*
move, run, walk
point
target

move だと無機質すぎるか
strafという関数に対してwalkのほうがマッチしている気がする
mover->move( pos );
mover->walk( pos );

namespace Car{
	class Mover;
}
namespace Point{
	class Mover;
}

namespace Target{
	class Mover;
}

右クリックの動作と左クリックの動作を
武器変更どうする


class CarMover;
class PoinMover;

if(isAnimOver()){
	changeAnim();
	next=new Stand()
}


class Shooter : public CarMover{};

うーん
Shooter::Parent
Shooter::Stand

Jumper::Stand
Jumper::Jump
Jumper::Walk

namespace 武器毎 にstand, run, swing
updaterでなにしたいの？

if( mouse.on(left) ){
	walkIf( target );
}

*/
namespace GameObjectData{
	class Status;
}

namespace GameObject{
class Player;

namespace PlayerUtils {namespace Updater { namespace SimpleWalker {

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
	Root::SimpleWalker::Child* mChild;	
	//Camera::PlayerCamera *mCamera;shared_ptr
	//Input::PlayerMouse *mMouse;shared_ptr
};

} } } } //GameObject::PlayerUtils::Updater::SimpleWalker


