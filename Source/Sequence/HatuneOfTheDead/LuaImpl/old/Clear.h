#pragma once
#include "Sequence/HatuneOfTheDead/LuaImpl/Child.h"
class Image;

namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{
class Parent;

class Clear : public Child{
public:
	Clear();
	~Clear();
	Base* update( Parent* );
	bool isReady();
private:
	Image* mImage;
	int mCount;
};

}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
