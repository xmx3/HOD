#ifndef __SEQUENCE_BASE_H__
#define __SEQUENCE_BASE_H__

namespace Sequence{

class Base{
public:
	virtual ~Base(){} //‚È‚É‚à‚µ‚È‚¢‚Ì‚Å‚±‚ê‚Å‚¢‚¢
	virtual Base* update( Base* ) = 0;
};

} //namespace Sequence

#endif