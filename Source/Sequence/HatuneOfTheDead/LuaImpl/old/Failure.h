#pragma once
#include "Sequence/HatuneOfTheDead/LuaImpl/Child.h"
class Image;

namespace Sequence{
namespace HatuneOfTheDead{
namespace LuaImpl{
class Parent;

class Failure : public Child{
public:
	Failure();
	~Failure();
	Base* update( Parent* );
	bool isReady();
private:
	Image* mImage;
	int mCount;
};

}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
