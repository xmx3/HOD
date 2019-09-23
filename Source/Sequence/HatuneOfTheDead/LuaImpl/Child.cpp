#include <GameLib/GameLib.h>
#include "Sequence/HatuneOfTheDead/LuaImpl/Child.h"
#include "Sequence/HatuneOfTheDead/LuaImpl/Parent.h"

namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{

Child::~Child(){
}

Base* Child::update( Base* p ){
	Parent* parent = dynamic_cast< Parent* >( p );
	ASSERT( parent );
	return update( parent );
}

}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
