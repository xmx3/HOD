#include"Load.h"
#include"Title.h"

#include"XmlLoader/PlayerData.h"

#include<GameLib/GameLib.h>
#include<GameLib/Framework.h>
#include<GameLib/DebugScreen.h>

#include<GameLib/Graphics/Manager.h>

#include<GameLib/Sound/Player.h>
#include<GameLib/Sound/Wave.h>
#include<GameLib/Sound/Manager.h>

#include<boost/lexical_cast.hpp>

using namespace GameLib;
using namespace GameLib::Sound;

#include"helper/Image.h"
#include"GUI/Manager.h"
#include"GUI/ListTexts.h"
#include"GUI/TransparentButton.h"
#include"GUI/utility.h"

#include<assert.h>

namespace Sequence{

Load::Load() 
	:mBackGround( NULL ),
	mList(NULL),
	mBgPlayer(NULL),
	mBgWave(NULL),
	mBtBack(NULL)
{
	mBackGround = new Image( "Data/GUI/image/dummy.dds" );
	
	GameLib::Framework fw;
	int w = fw.width();
	int h = fw.height();

	struct PosSize{ 
		int x,y;//pos
		int w,h;//size
	};
	using namespace GUI;
	PosSize list={ 
		SaveLoadListTextPosSize::x(),
		SaveLoadListTextPosSize::y(),
		SaveLoadListTextPosSize::width(),
		SaveLoadListTextPosSize::height()
	};
	PosSize back={ list.x/2, list.y+list.h+h/40, list.w, h/10 };

	mBtBack = new GUI::TransparentButton( back.x, back.y, back.w, back.h );
	mBtBack->setText("–ß‚é");
	GUI::Manager::instance()->add( mBtBack );

	mList = GUI::createLoadListText();
	GUI::Manager::instance()->add( mList.get() );


	//mBgWave = NEW Wave;
	//*mBgWave = Wave::create( "Data/sound/bgm/title.wav" );
}

Load::~Load(){
	SAFE_DELETE( mBgWave );
	SAFE_DELETE( mBgPlayer );
	mList.reset();
	SAFE_DELETE( mBtBack );
	SAFE_DELETE( mBackGround );
}

Base* Load::update( Parent* parent ){
	Base* next = this;
	isReady();
	
	
	//•`‰æ
	mBackGround->draw();
	
	GUI::Manager::instance()->draw();


	if( mBtBack->isPushed() ){
		return new Title();
	}

	if( mList->isPushedSelectedElement() ){
		int index = mList->getSelectedIndex();
		std::string fileName("Data/sav/sav"+boost::lexical_cast<std::string>(index) );
	}
	
	return next;
}

bool Load::isReady(){
	mBackGround->isReady();
	return true;
}

} //namespace Sequence