#pragma once
#include"Label.h"
#include<string>


namespace GUI{
class Manager;

//押したの検知
class PushableLabel : public Label {
public:
	PushableLabel(
		int x, int y,
		int sizeX, int sizeY,
		unsigned int color = 0xffffffff,
		unsigned int fontColor = 0xff000000,
		float u0=0.f, float v0=0.f,
		float u1=1.f, float v1=1.f );
	virtual ~PushableLabel();

	bool isPushed()const{
		return mIsPushed;
	}
	//マウスが自身の領域上にあるか
	bool isHover()const{
		return mIsHover;
	}
	bool isPushing()const{
		return mIsPushing;
	}

	//falseにするとisPusshing()とisPushed()を常にfalseに返すようにする
	void setPushable(bool enable);

	virtual void update();
	virtual void draw( Manager* mngr );

private:
	//disallow copy
	PushableLabel( const PushableLabel& );	
	//disallow assin
	void operator=( const PushableLabel& );
private:	
	bool		mIsPushed;//ボタン上で押して離した場合true
	bool		mIsPushing;//ボタン上で押した場合true
	bool		mIsHover;//ボタン上にマウスカソールがある場合true
	bool		mPushable;
};

}//namespace GUI
