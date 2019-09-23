#pragma once

#include "Sequence/HatuneOfTheDead/LuaImpl/Child.h"
class Image;

namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{

class Parent;

class Pause : public Child{
public:
	Pause();
	~Pause();
	Base* update( Parent* );
	bool isReady();
private:
	Image* mImage;
	int mCursorPosistion; 
};

}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
