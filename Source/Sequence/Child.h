#ifndef __SEQUENCE_CHILD_H__
#define __SEQUENCE_CHILD_H__

#include "Sequence/Base.h"

namespace Sequence{
class Parent;



class Child : public Base{
public:
	virtual ~Child();
	Base* update( Base* ); //‚±‚ê‚ÍÀ‘Ì‚ğì‚Á‚Ä‚â‚é
	virtual Base* update( Parent* ) = 0;
};

} //namespace Sequence

#endif