#pragma once
#include "Sequence/HatuneOfTheDead/CppImpl/Child.h"
class Image;

namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{
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

}}} //namespace Sequence::HatuneOfTheDead::CppImpl
