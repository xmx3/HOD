#ifndef __MOUSE_WRAPPER_H__
#define __MOUSE_WRAPPER_H__

#include<GameLib/Input/Mouse.h>
//#include<GameLib/Math/Vector2.h>

using namespace GameLib::Input;
//using namespace GameLib::Math;

class CMouseWrapper{
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


	//ダブルクリックの最初のクリック間はtrueになる；
	static bool isOnClick( Mouse::Button b ){
		Mouse m;
		return !sIsOnDoubleClicked[b] && m.isOn(b);
	}

	static bool isTriggeredClick( Mouse::Button b ){
		Mouse m;
		return !sIsOnDoubleClicked[b] && m.isTriggered(b);
	}

	static bool isOnDoubleClick( Mouse::Button b ){
		return sIsOnDoubleClicked[b];
	}

	static bool isTriggeredDoubleClick(Mouse::Button b){
		Mouse m;		
		return sIsOnDoubleClicked[b] && m.isTriggered(b);
	}
	
	//マウスカーソルが右端にあるか
	static bool isCursolOnRight(){
		return sIsOnRight;
	}

		//マウスカーソルが左端にあるか
	static bool isCursolOnLeft(){
		return sIsOnLeft;
	}


	static void update(){
		Mouse m;
		//ボタンのクリック押下関連
		for(int i=0; i<2 ; ++i ) {
			Mouse::Button b = static_cast<Mouse::Button>(i);
			//ダブルクリック状態で
			//ボタンをずっと押してる場合
			if( sIsOnDoubleClicked[b] ){
				if( m.isOn( b ) ){
					//継続
					sIsOnDoubleClicked[b]=true;
					//sIsTriggeredDoubleClicked[b]=false;
					sDoubleClickAbleTime[b]=0;
				}
				else{
					//通常状態に戻る
					sIsOnDoubleClicked[b]=false;
					//sIsTriggeredDoubleClicked[b]=false;
					sDoubleClickAbleTime[b]=0;
				}
			}
			//ダブルクリック可能状態
			else if(sDoubleClickAbleTime[b] > 0){
				--sDoubleClickAbleTime[b];
				//ダブルクリックしたボタンを押す
				if( m.isTriggered( b ) ){
					//ダブルクリック中に状態遷移
					sIsOnDoubleClicked[b]=true;
					//sIsTriggeredDoubleClicked[b]=true;
					sDoubleClickAbleTime[b]=0;
				}
			}
			//通常状態
			else{
				if( m.isTriggered( b ) ){
					//ダブルクリック可能状態に遷移
					sDoubleClickAbleTime[b]=DOUBLE_CLICK_ABLE_TIME;
				}
			}
		}

		//マウスカーソルが右端か左端にあるか
		if( m.x() < skLeft ) {
			sIsOnLeft=true;
			sIsOnRight=false;
		} else if( m.x() > skRight ) {
			sIsOnLeft=false;
			sIsOnRight=true;
		} else {
			sIsOnLeft=false;
			sIsOnRight=false;
		} 
	}
private:
	CMouseWrapper();
	~CMouseWrapper();
	static int sDoubleClickAbleTime[2];
	static bool sIsOnDoubleClicked[2];
	
	//static bool sIsTriggeredDoubleClicked[2];いらない疑惑コメントアウト

	static bool sIsOnRight;
	static bool sIsOnLeft;

	//const にしているが　ゲーム中変えたい場面があるかも
	static const int skRight;
	static const int skLeft;

	static int const DOUBLE_CLICK_ABLE_TIME;
};

#endif