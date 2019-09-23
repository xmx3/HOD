#ifndef __SEQUENCE_ENDING_H__
#define __SEQUENCE_ENDING_H__

#include "Sequence/Child.h"

class Image;

namespace Sequence{
class Parent;

class Ending : public Child{
public:
	Ending();
	~Ending();
	Base* update( Parent* );
	bool isReady();
private:
	Image* mImage;
	int mCount;
};

} //namespace Sequence

#endif
