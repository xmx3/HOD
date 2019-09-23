#pragma once
#ifndef __SEQUENCE_TEST_H__
#define __SEQUENCE_TEST_H__

#include"Sequence/Child.h"

namespace Sequence{
class Parent;

class Test : public Child{
public:
	Test();
	~Test();
	Base* update( Parent* );
private:

};

} //namespace Sequence

#endif