#include"VerticalScrollBar.h"
#include"Label.h"
#include"DraggableLabel.h"
#include"helper/MyOutputDebugString.h"
#include<assert.h>
#include<GameLib/Input/Mouse.h>
namespace GUI{

VerticalScrollBar::VerticalScrollBar( 
		int x, int y,
		int sizeX, int sizeY,
		int barSize )
		:BaseComponent( x, y, sizeX, sizeY ),
		mBackGround(0),
		mBar(0),
		mOldBarPosX(x), mOldBarPosY(y)
{
	assert( sizeY>=barSize );
	mBackGround = new Label( x, y, sizeX, sizeY, 0x88888888 );
	mBar = new DraggableLabel(
		x, y, 
		sizeX, barSize,
		x, x,
		y, y+sizeY-barSize );
}
VerticalScrollBar::~VerticalScrollBar(){
	delete mBackGround;
	mBackGround =0;
	delete mBar;
	mBar = 0;
}


void VerticalScrollBar::update(){
	GameLib::Input::Mouse m;
	int x = m.x();
	int y = m.y();
	struct Rect{
		int left, right, top, bottom;
	};
	
	//クリックした位置にバーを移動する
	if( !hasScrolled() &&
		m.isTriggered( GameLib::Input::Mouse::BUTTON_LEFT ) )
	{

		struct Xy{
			int x,y;
		};
		Xy barSize;
		Xy barPos;
		mBar->getSize( &barSize.x, &barSize.y );
		mBar->getPos( &barPos.x, &barPos.y );

		Rect upper;
		upper.left =mX;
		upper.top = mY;
		upper.right = mX+barSize.x;
		upper.bottom = barPos.y;
		
		Rect lower;
		lower.left = mX;
		lower.top = upper.bottom + barSize.y;
		lower.right = mX+barSize.x;
		lower.bottom = mY+mSizeY;
			
		//上部をクリックした場合
		if( upper.left<x && x<upper.right &&
			upper.top<y  && y<upper.bottom )
		{
			mBar->setPos( x, y-1 );

		}
		//下部をクリックした場合
		else if( 
			lower.left<x && x<lower.right &&
			lower.top<y  && y<lower.bottom )
		{
			mBar->setPos( x-barSize.x, y-barSize.y+1 );
		}
	}
	
	mBar->getPos( &mOldBarPosX, &mOldBarPosY );
	mBackGround->update();
	mBar->update();

}
void VerticalScrollBar::draw( Manager* mngr ){
	mBackGround->draw(mngr);
	mBar->draw(mngr);
}

float VerticalScrollBar::getValue()const{
	int x,y, sizeX, sizeY;
	mBar->getPos( &x, &y );
	mBar->getSize( &sizeX, &sizeY );

	if( float length=static_cast<float>(mSizeY-sizeY) ){
		return static_cast<float>(y-mY)/length;
	}
	else{
		return 0.f;
		 
	}
}

void VerticalScrollBar::setBarLength( int length ){
	assert( mSizeY>=length );	
	assert( length>0 );	
	mBar->setSize( mSizeX, length );
	mBar->setMoveableArea( mX, mY, mX, mY+mSizeY-length );
}

bool VerticalScrollBar::hasScrolled()const{
	return mBar->isDragging() || mBar->isDropped();
}



}