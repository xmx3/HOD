#pragma once
#include "Sequence/Base.h"

namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{
class Parent;

class Child : public Base{
public:
	virtual ~Child();
	Base* update( Base* ); //‚±‚ê‚ÍÀ‘Ì‚ğì‚Á‚Ä‚â‚é
	virtual Base* update( Parent* ) = 0;
};


}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
