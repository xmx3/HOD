#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>
#include "Sequence/Test.h"
#include "Sequence/Game/Game_Parent.h"
#include "Sequence/Dance/Parent.h"
#include "Sequence/Test.h"
#include "Sequence/LuaTest/Test.h"


#include "MMD/MMDDataBase.h"
#include "MME/Manager.h"




namespace Sequence{

Test::Test() 
{

}

Test::~Test(){
	//MME::Manager::instance()->destroy();
	MMD::MMDDataBase::destroy();
}

Base* Test::update( Parent* parent ){
	Base* next = this;
	//next = NEW Game::Parent();
	next = NEW Dance::Parent();
	//next = NEW LuaSeq::Test();
	
	return next;
}

} //namespace Sequence