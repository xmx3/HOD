#ifndef __KZTR_GUI_BUTTON_H__
#define __KZTR_GUI_BUTTON_H__
#include"IComponent.h"

namespace GUI{
class Manager;
class Button : public ComponentWithRender {
public:
		
	Button( 
		int x, int y,
		int sizeX, int sizeY,
		unsigned int color = 0xffffffff,
		unsigned int fontColor = 0xff000000 );
		
	virtual ~Button();

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
	Button( const Button& );	
	//disallow assin
	void operator=( const Button& );
private:
#define GUI_BUTTON_MAX_CHAR 32
	char			mText[GUI_BUTTON_MAX_CHAR];
	
	
	bool		mIsPushed;//ボタン上で押して離した場合true
	bool		mIsPushing;//ボタン上で押した場合true
	bool		mIsHover;//ボタン上にマウスカソールがある場合true

	static const int skMaxChar;

	static const float	skU0, skV0;
	static const float	skU1, skV1;

	static const float	skUPushed0, skVPushed0;
	static const float	skUPushed1, skVPushed1;
};
}//namespace GUI
#endif//__KZTR_GUI_BUTTON_H__