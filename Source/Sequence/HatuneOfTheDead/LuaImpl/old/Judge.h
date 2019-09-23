#pragma once
#include "Sequence/HatuneOfTheDead/LuaImpl/Child.h"
class Image;

namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{
class Parent;

class Judge : public Child{
public:
	Judge();
	~Judge();
	Base* update( Parent* );
	bool isReady();
private:
	Image* mImage;
	int mCursorPosistion; 
};

}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
