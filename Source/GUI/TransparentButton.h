#pragma once
#include"IComponent.h"

namespace GUI{
class Manager;
class TransparentButton : public ComponentWithRender {
public:
		
	TransparentButton( 
		int x, int y,
		int sizeX, int sizeY,
		unsigned int fontColor = 0xff000000 );
		
	virtual ~TransparentButton();

	bool isPushed() const;
	void setIsPushed( bool b ){
		mIsPushed = b;
	}
	//マウスが自身の領域上にあるか
	bool isHover() const;

	virtual void update();
	virtual void draw( Manager* mngr );

	void setText( const char *text );

private:
	//disallow copy
	TransparentButton( const TransparentButton& );	
	//disallow assin
	void operator=( const TransparentButton& );
	using ComponentWithRender::setColor;
private:
	enum{
		kMaxChar=32,
	};
	char			mText[kMaxChar];
	
	
	bool		mIsPushed;//ボタン上で押して離した場合true
	bool		mIsPushing;//ボタン上で押した場合true
	bool		mIsHover;//ボタン上にマウスカソールがある場合true
	
	static const float	skU0, skV0;
	static const float	skU1, skV1;
};
}//namespace GUI
