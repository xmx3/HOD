#ifndef __MOUSECONTROLLER_H__
#define __MOUSECONTROLLER_H__
#include<GameLib/Input/Mouse.h>
using namespace GameLib::Input;

class CMouseController{
public:
	static float velocityY()
	{
		Mouse m;
		return static_cast<float>(m.velocityY());
	}
	static float velocityX()
	{
		Mouse m;
		return static_cast<float>(m.velocityX());
	}

	static bool isOnLeftClick(){
		Mouse m;
		m.isOn(Mouse::BUTTON_LEFT);
		return !mIsOnLeftDoubleClicked && m.isOn(Mouse::BUTTON_LEFT);
	}

	static bool isTriggeredLeftClick(){
		Mouse m;
		m.isOn(Mouse::BUTTON_LEFT);
		return !mIsOnLeftDoubleClicked && m.isTriggered(Mouse::BUTTON_LEFT);
	}


	static bool isOnLeftDoubleClick(){
		return mIsOnLeftDoubleClicked;
	}

	static bool isTriggeredLeftDoubleClick(){
		return mIsTriggeredLeftDoubleClicked;
	}

	static void update(){
		Mouse m;
		//ダブルクリック状態
		//ボタンをずっと押してる場合
		if( mIsOnLeftDoubleClicked ){
			if( m.isOn(Mouse::BUTTON_LEFT) ){
				//継続
				mIsOnLeftDoubleClicked=true;
				mIsTriggeredLeftDoubleClicked=false;
				mLeftDoubleClickAbleTime=0;
			}
			else{
				//通常状態に戻る
				mIsOnLeftDoubleClicked=false;
				mIsTriggeredLeftDoubleClicked=false;
				mLeftDoubleClickAbleTime=0;
			}
		}
		//ダブルクリック可能状態
		else if(mLeftDoubleClickAbleTime > 0){
			--mLeftDoubleClickAbleTime;
			//ダブルクリックしたボタンを押す
			if( m.isTriggered(Mouse::BUTTON_LEFT) ){
				//ダブルクリック中に状態遷移
				mIsOnLeftDoubleClicked=true;
				mIsTriggeredLeftDoubleClicked=true;
				mLeftDoubleClickAbleTime=0;
			}
		}
		//通常状態
		else{
			if( m.isTriggered(Mouse::BUTTON_LEFT) ){
				//ダブルクリック可能状態に遷移
				mLeftDoubleClickAbleTime=DOUBLE_CLICK_ABLE_TIME;
			}
		}
	}
private:
	CMouseController();
	~CMouseController();
	static int mLeftDoubleClickAbleTime;
	static bool mIsOnLeftDoubleClicked;
	static bool mIsTriggeredLeftDoubleClicked;

	static int const DOUBLE_CLICK_ABLE_TIME;
};



#endif//__MOUSECONTROLLER_H__