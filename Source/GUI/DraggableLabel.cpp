#include"DraggableLabel.h"
#include"Manager.h"
#include<GameLib/Graphics/Manager.h>
#include<GameLib/GameLib.h>
#include<GameLib/Framework.h>
#include<string.h>
#include<assert.h>
#include<GameLib/Input/Mouse.h>
#include<algorithm>
using GameLib::Math::Vector2;
namespace GUI {

DraggableLabel::DraggableLabel(
	int x, int y,
	int sizeX, int sizeY,
	int minX, int maxX,
	int minY, int maxY,
	unsigned int color,
	unsigned int fontColor,
	float u0, float v0,
	float u1, float v1 )
	:Label( 
		x, y,
		sizeX, sizeY,
		color,
		fontColor,
		u0, v0,
		u1, v1
	),
	mClickedX(0), mClickedY(0),
	mClickedOffsetX(0), mClickedOffsetY(0),
	mIsDragging(false),
	mIsDropped(false),
	mArea( minX, minY, maxX, maxY )
{}

DraggableLabel::~DraggableLabel(){
}

void DraggableLabel::update(){
	GameLib::Input::Mouse m;
	const int &x = m.x(); 
	const int &y = m.y(); 
	mIsDropped = false;
	//window上でクリックしたとき
	if( m.isTriggered(m.BUTTON_LEFT) ){
		//マウスカソールがボタン上にあるか？
		if( isHover(x,y) )
		{
			//dragging状態に移行
			mIsDragging = true;
			mClickedX = x;
			mClickedY = y;
			mClickedOffsetX = x-mX;
			mClickedOffsetY =y-mY;
		}
	}

	//dragging中
	if( mIsDragging ) {
		//離した場合
		if( m.isReleased( m.BUTTON_LEFT ) )  {
			mIsDropped = true;
			mIsDragging = false;
		} else {

		}
	}

	if( mIsDragging ) {
		GameLib::Input::Mouse m;
		//int x = std::min( std::max( mArea.left, m.x()-mClickedOffsetX ), mArea.right );
		//int y = std::min( std::max( mArea.top, m.y()-mClickedOffsetY ), mArea.bottom );
		//setPos( x, y);
		setPos( m.x()-mClickedOffsetX, m.y()-mClickedOffsetY );
	}

	if( mIsDropped ) {
		GameLib::Input::Mouse m;
		//int x = std::min( std::max( mArea.left, m.x()-mClickedOffsetX ), mArea.right );
		//int y = std::min( std::max( mArea.top, m.y()-mClickedOffsetY ), mArea.bottom );
		//setPos( x, y);
		setPos( m.x()-mClickedOffsetX, m.y()-mClickedOffsetY );
	}

	Label::update();
}

void DraggableLabel::draw( Manager* mngr ){
	
	Label::draw( mngr );
}

//void DraggableLabel::limitPosition(){
//	mX = std::min( std::max( mArea.left, mX ), mArea.right );
//	mY = std::min( std::max( mArea.top, mY ), mArea.bottom );
//}

void DraggableLabel::setPos( int x, int y ){
	mX = std::min( std::max( mArea.left, x ), mArea.right );
	mY = std::min( std::max( mArea.top, y ), mArea.bottom );
}

}//namespace GUI