#pragma once
#include"IModalDialog.h"
namespace GUI{
	class Window;
	class Button;
	class Label;
//開いている間は他のコンポーネントの状態は変更しない

//exsample
//
////モーダルダイアルログが呼び出されてる間は他のGUIはアップデートされない
//	if( mBtQuit->isPushed() ){
//		mYesNo->show();
//		//yesnodialog
//		if( mYesNo->isYes() ){
//			GameLib::Framework::instance().requestEnd();
//		}else if( mYesNo->isNo() ){
//			mYesNo->hide();
//			mYesNo->init();
//		}
//	}
	
//	if( mBtQuit->isPushed() ){
//		static YesNoDialog sYesNo;//本来はポインタがお勧め
//		sYesNo.show();//毎フレーム呼ばなくてもオッケ
//		//yesnodialog
//		if( sYesNo.isYes() ){
//			GameLib::Framework::instance().requestEnd();
//		}
//	}
class YesNoDialog : public IModalDialog {
public:
	YesNoDialog( const char *questionText );
	virtual ~YesNoDialog();

	void update();
	void draw( Manager* );
	void init(){
		update();//とりあえずこれで良いや
	}

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

	bool isYes()const;
	bool isNo()const;

protected:
	bool	mIsEnable;
	bool	mIsDrawAble;

	Window *mWindow;
	Button *mBtYes;
	Button *mBtNo;
	Label  *mQuestionText;
};
}//end namespace GUI