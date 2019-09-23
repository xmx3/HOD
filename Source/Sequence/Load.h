#pragma once
#include"Sequence/Child.h"
#include<memory>

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
	class ListTexts;
	class TransparentButton;
}

namespace Sequence{
class Parent;

class Load : public Child{
public:
	Load();
	~Load();
	Base* update( Parent* );
	bool isReady();
private:
	Image		*mBackGround;
	std::shared_ptr<GUI::ListTexts>	mList;
	GUI::TransparentButton *mBtBack;//BuTton
	
	GameLib::Sound::Wave			*mBgWave;

	GameLib::Sound::Player			*mBgPlayer;
	
};

} //namespace Sequence
