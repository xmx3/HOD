#include"HelperFunc.h"
#include<GameLib/Framework.h>
#include<GameLib/Math/Vector3.h>
#include<GameLib/Math/Vector4.h>
#include<GameLib/Math/Matrix44.h>
#include<GameLib/Graphics/Manager.h>
#include"GUI/Label.h"


namespace GameObject{
void drawBar( 
	GUI::Label *bar,
	const GameLib::Math::Vector4 &pos,
	int sizeX, int sizeY,
	unsigned int color)
{

	//posÇíÜêSÇ…ÇµÇΩÇ¢
	GameLib::Math::Vector4 screenPos;

	GameLib::Graphics::Manager m;
	GameLib::Framework fw;

	m.getProjectionViewMatrix().mul( &screenPos, pos );

	screenPos.x /= screenPos.w;
	screenPos.y /= screenPos.w;
	screenPos.z /= screenPos.w;
	
	sizeX = static_cast<int>(sizeX*screenPos.z);
	sizeY = static_cast<int>(sizeY*screenPos.z);
	bar->setSize( sizeX, sizeY );
	
	//posÇíÜêSÇ…ÇµÇΩÇ¢ÇÃÇ≈sizeÇÃîºï™Ç∏ÇÁÇ∑
	int screenX = static_cast<int>( (screenPos.x+1.f)*fw.width()/2.f ) - sizeX/2;
	int screenY = static_cast<int>( (-screenPos.y+1.f)*fw.height()/2.f) - sizeY/2;
	bar->setPos( 
		screenX,
		screenY );

	
	bar->setColor( color );
}

void drawHpBar( 
	GUI::Label *hpBar,
	GUI::Label *hpBackGroundBar,
	const GameLib::Math::Vector4 &pos,
	float hpRate,
	unsigned int color,
	unsigned int bgColor )
{
	int sizeX = 30;
	int sizeY = 5;

	GameLib::Math::Vector4 screenPos;

	GameLib::Graphics::Manager m;
	GameLib::Framework fw;

	m.getProjectionViewMatrix().mul( &screenPos, pos );

	screenPos.x /= screenPos.w;
	screenPos.y /= screenPos.w;
	screenPos.z /= screenPos.w;
	
	sizeX = static_cast<int>(sizeX*screenPos.z);
	sizeY = static_cast<int>(sizeY*screenPos.z);
	hpBackGroundBar->setSize( sizeX, sizeY );
	hpBar->setSize( static_cast<int>(sizeX*hpRate), static_cast<int>(sizeY*hpRate) );

	//posÇíÜêSÇ…ÇµÇΩÇ¢ÇÃÇ≈sizeÇÃîºï™Ç∏ÇÁÇ∑
	int screenX = static_cast<int>( (screenPos.x+1.f)*fw.width()/2.f ) - sizeX/2;
	int screenY = static_cast<int>( (-screenPos.y+1.f)*fw.height()/2.f) - sizeY/2;
	
	hpBar->setPos( 
		screenX,
		screenY );

	hpBackGroundBar->setPos( 
		screenX,
		screenY );

	
	hpBar->setColor( color );
	hpBackGroundBar->setColor( bgColor );
}


}