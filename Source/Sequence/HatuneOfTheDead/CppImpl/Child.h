#pragma once
#include "Sequence/Base.h"

namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{
class Parent;

class Child : public Base{
public:
	virtual ~Child();
	Base* update( Base* ); //����͎��̂�����Ă��
	virtual Base* update( Parent* ) = 0;
};


}}} //namespace Sequence::HatuneOfTheDead::CppImpl