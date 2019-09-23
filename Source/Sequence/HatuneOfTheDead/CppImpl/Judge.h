#pragma once
#include "Sequence/HatuneOfTheDead/CppImpl/Child.h"
class Image;

namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{
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

}}} //namespace Sequence::HatuneOfTheDead::CppImpl
