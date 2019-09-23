#include"PushableLabel.h"
#include<GameLib/Input/Mouse.h>

namespace GUI {


PushableLabel::PushableLabel(
	int x, int y,
	int sizeX, int sizeY,
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
		u0, v1 ),
	mIsPushed(false),
	mIsPushing(false),
	mIsHover(false),
	mPushable(true)
{
}

PushableLabel::~PushableLabel(){
}
		
void PushableLabel::update(){
	Label::update();

	GameLib::Input::Mouse m;
	const int &x = m.x(); 
	const int &y = m.y(); 
	mIsPushed = false;

	//マウスカソールがボタン上にあるか？
	mIsHover = BaseComponent::isHover(x, y);

	if( mPushable ){
		//ボタン上でクリックしたとき
		if( m.isTriggered(m.BUTTON_LEFT) && mIsHover ){
			mIsPushing = true;
		}


		//ボタン上でクリックしてあり、離した場合
		if( mIsPushing  && m.isReleased( m.BUTTON_LEFT ) ) {
			//ボタン上で離した場合
			if( mIsHover )  {
				mIsPushed = true;
			}
			//押したフラグ解除
			mIsPushing = false;
		}
	}
}

void PushableLabel::draw( Manager* mngr ){
	Label::draw(mngr);
}

void PushableLabel::setPushable( bool enable ){
	mPushable = enable;
	
	if(!mPushable){
		mIsPushed=false;
		mIsPushing=false;
	}
}

}//namespace GUI