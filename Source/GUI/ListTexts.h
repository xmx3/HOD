#pragma once
#include"IComponent.h"
//#include<string>
//#include<list>
#include<vector>
#include<GameLib/Scene/Font.h>

namespace GUI{
class VerticalScrollBar;
class PushableLabel;
class ListTexts : public BaseComponent {
public:
	ListTexts(
		int x, int y,
		int sizeX, int sizeY
	);
	virtual ~ListTexts();

	void add( const char *text );
	//vectorを使っているので遅い
	void remove( const char *text );

	const char* currentText()const;
	void setSelectedIndex(unsigned int index);
	int getSelectedIndex()const;

	int count() const;

	virtual void update();
	virtual void draw( Manager* );

	void setFont( GameLib::Scene::Font f );

	GameLib::Scene::Font getFont()const{
		return mFont;
	}

	//int で返す場合、押されてない場合ー1、0番目が押された場合0(false)を返す動作が気持ち悪いのでboolで返した
	//どのボタンが押されたかはgetSelectedIndex()で取得しろ
	bool isPushedSelectedElement()const;

	void setText( unsigned int index, const char* text );

	void setPushable( unsigned int index, bool enable );

private:
	//vectorにしたわけ
	//　ランダムアクセスしたい
	//	eraseを1フレーム内に少ない回数(1回)しか動作させない。
	typedef std::vector<PushableLabel*> List;
	List mList;;
	//List::iterator mCurrentIt;
	int mSelectedIndex;
	VerticalScrollBar *mScrollBar;
	
	unsigned int mSelectedItemColor;
	unsigned int mHoverItemColor;//マウスが上にあるときの色
	unsigned int mItemColor;
	GameLib::Scene::Font mFont;
};
}