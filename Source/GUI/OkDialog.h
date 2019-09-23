#pragma once
#include"IModalDialog.h"
#include<string>

//tolua_begin
namespace GUI{
	class Window;
	class Button;
class OkDialog : public IModalDialog {
public:
	OkDialog();
	virtual ~OkDialog();

	void update();
	void draw( Manager* );

	bool isEnabled() const {
		return mIsEnable;
	}
	void setIsEnabled( bool b ){
		mIsEnable = b;
	}

	bool isDrawAble() const {
		return mIsDrawAble;
	}
	void setIsDrawAble( bool b ){
		mIsDrawAble = b;
	}

	void setText(const std::string &text);

	bool isOk()const;
//tolua_end
protected:
	bool	mIsEnable;
	bool	mIsDrawAble;

	Window *mWindow;
	Button *mOkButton;
//tolua_begin
};
}//end namespace GUI
//tolua_end