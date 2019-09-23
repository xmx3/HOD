#pragma once
#include"Sequence/Child.h"
#include"XmlLoader/PlayerData.h"

namespace Sequence{
class Parent;
class Base;
namespace HatuneOfTheDead{
namespace LuaImpl{
class Child;
class State;

class Parent : public Sequence::Child{
public:
	typedef Sequence::Parent GrandParent;
	Parent();
	Parent( XmlLoader::PlayerDataSharedPtr );
	virtual ~Parent();
	Base* update( GrandParent* );

	void drawState();
	void updateState();
	bool isReady();
	bool isClear()const;

	void reloadLua();
private:
	HatuneOfTheDead::LuaImpl::Child	*mChild;
	HatuneOfTheDead::LuaImpl::State	*mState;
};


}}} //namespace Sequence::HatuneOfTheDead::LuaImpl
