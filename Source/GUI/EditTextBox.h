#ifndef __KZTR_GUI_EDITTEXTBOX_H__
#define __KZTR_GUI_EDITTEXTBOX_H__
#pragma once
#include"IComponent.h"
#include<string>

namespace GUI{
class Manager;


class EditTextBox : public ComponentWithRender {
public:
	EditTextBox(
		int x, int y,
		int sizeX, int sizeY,
		unsigned int color = 0xffffffff,
		unsigned int fontColor = 0xff000000 );
	virtual ~EditTextBox();
	
	virtual void update();
	virtual void draw( Manager* mngr );
	bool onFocus()const;
	
	const std::string & getText()const;
	void clearText();
private:
	//disallow copy
	EditTextBox( const EditTextBox& );	
	//disallow assin
	void operator=( const EditTextBox& );

	void drawComposition();
	void drawCandidate();
	void drawIndicator();
	void drawText();
	void drawBG();
private:	
	int mCursolPos;//何文字目,スクリーン座標は後で求める
	std::string mText;
	bool mOnFocus;

};


}//namespace GUI
#endif//__KZTR_GUI_EDITTEXTBOX_H__