#pragma once
#include"Enums.h"


namespace MME {

//
class IDrawable {
public:
	IDrawable(){}
	virtual ~IDrawable(){}
	virtual void drawByMME()=0;
};
}