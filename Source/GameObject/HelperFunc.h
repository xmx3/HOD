#pragma once

namespace GUI{
	class Label;
}

namespace GameLib{
	namespace Math{
		class Vector4;
	}
}


namespace GameObject{

void drawBar( 
	GUI::Label *bar,
	const GameLib::Math::Vector4 &pos,
	int sizeX, int sizeY,
	unsigned int color);

void drawHpBar( 
	GUI::Label *hpBar,
	GUI::Label *hpBackGroundBar,
	const GameLib::Math::Vector4 &pos,
	float hpRate,
	unsigned int color,
	unsigned int bgColor );

}