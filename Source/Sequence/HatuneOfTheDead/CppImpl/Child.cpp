#include <GameLib/GameLib.h>
#include "Sequence/HatuneOfTheDead/CppImpl/Child.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Parent.h"

namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{

Child::~Child(){
}

Base* Child::update( Base* p ){
	Parent* parent = dynamic_cast< Parent* >( p );
	ASSERT( parent );
	return update( parent );
}

}}} //namespace Sequence::HatuneOfTheDead::CppImpl
