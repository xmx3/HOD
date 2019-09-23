#pragma once
#include "Sequence/HatuneOfTheDead/CppImpl/Child.h"

namespace GUI{
	class Button;
	class Label;
}


namespace Sequence{ namespace HatuneOfTheDead{ namespace CppImpl{
class Parent;

class BattleResult : public Child{
public:
	BattleResult();
	virtual ~BattleResult();
	Base* update( Parent* );
private:
	GUI::Button *mOk;
	GUI::Label *mLabel;
	int mCount;
};

}}} //namespace Sequence::HatuneOfTheDead::CppImpl
