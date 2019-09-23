#ifndef __SEQUENCE_GAME_OVER_H__
#define __SEQUENCE_GAME_OVER_H__

#include "Sequence/Child.h"

class Image;

namespace Sequence{
class Parent;

class GameOver : public Child{
public:
	GameOver();
	~GameOver();
	Base* update( Parent* );
	bool isReady();
private:
	Image* mImage;
	int mCount;
};

} //namespace Sequence

#endif
