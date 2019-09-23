#ifndef __SEQUENCE_TITLE_H__
#define __SEQUENCE_TITLE_H__

#include"Sequence/Child.h"

class Image;
namespace GameLib{
	namespace Scene{
		class StringRenderer;
		class Font;
	}

	namespace Sound {
		class Wave;
		class Player;
	}
}
namespace GUI{
	class Button;
	class ImageButton;
	class Label;
	class Window;
	//class DraggableLabel;
	class Knob;
	class EditTextBox;
}

namespace Sequence{
class Parent;

class Title : public Child{
public:
	Title();
	~Title();
	Base* update( Parent* );
	bool isReady();
private:
	Image							*mImage; //ƒ^ƒCƒgƒ‹‰æ–Ê‰æ‘œ
	GameLib::Scene::StringRenderer	*mStringRenderer;
	GameLib::Scene::Font			*mFont;
	bool							mIsReady;
	GUI::ImageButton				*mNewButton;
	GUI::ImageButton				*mLoadButton;
	GUI::ImageButton				*mGameButton;
	GUI::EditTextBox				*mEditTextBox;
	GUI::ImageButton				*mDanceButton;
	GUI::ImageButton				*mLuaButton;


	int mCursorPosistion;

	GameLib::Sound::Wave			*mBgWave;

	GameLib::Sound::Player			*mBgPlayer;
	//GameLib::Sound::Player			*mEnterPlayer;
	//GameLib::Sound::Player			*mCancelPlayer;
	
};

} //namespace Sequence

#endif