#pragma once
#include"IComponent.h"

namespace GUI{ //tolua_export

// 表示中はウインドウの外の操作ができなくなる「モーダルダイアログ」(modal dialog)と、
// 他のウインドウの操作を行ってもよい「モードレスダイアログ」(modeless dialog)がある
//
//　開いている間は他のコンポーネントの状態は変更したくなかったのでshow(), hide()を作った。
//　
//  show()した後は、必ずhide()を呼ぶこと
//	show()は毎フレーム余呼んでも良いし、一回だけでも良いが、必ずhide()をすること

class IModalDialog : public IComponent { //tolua_export
public:
	IModalDialog();
	virtual ~IModalDialog();

//tolua_begin
	void show();
	void hide();
};

}//end namespace GUI
//tolua_end