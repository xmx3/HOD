#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>
#include <GameLib/Input/Keyboard.h>
#include <GameLib/Input/Mouse.h>
#include <GameLib/DebugScreen.h>
#include <GameLib/Scene/StringRenderer.h>
#include <GameLib/Scene/Font.h>
#include <GameLib/Math/Vector2.h>
#include <GameLib/Graphics/Texture.h>
#include <GameLib/Graphics/Enum.h>
#include <GameLib/Graphics/Manager.h>

#include <GameLib/Sound/Player.h>
#include <GameLib/Sound/Wave.h>
#include <GameLib/Sound/Manager.h>

using namespace GameLib;
using namespace GameLib::Scene;
using namespace GameLib::Math;
using namespace GameLib::Sound;
using GameLib::Graphics::Texture;

#include "Sequence/Title.h"
#include "Sequence/Load.h"
#include "Sequence/Parent.h"

#include "helper/Image.h"
#include "GUI/Button.h"
#include "GUI/Label.h"
#include "GUI/Manager.h"
#include "GUI/ImageButton.h"
#include "GUI/Window.h"
//#include "GUI/DraggableLabel.h"
//#include"GUI/VerticalScrollBar.h"
#include"GUI/ListTexts.h"
#include"GUI/EditTextBox.h"

#include<boost/lexical_cast.hpp>

#include<sstream>

#include"MME/Manager.h"

#include<tchar.h>

#include<GameLib/ImeUi/ImeUi.h>
#include<GameLib/WindowCreator/WindowCreator.h>

#include <msctf.h>
#include <Ime.h>



namespace Sequence{

Title::Title() 
	: mImage( 0 ),
	mCursorPosistion( 0 ),
	mFont(0),
	mStringRenderer(0),
	mIsReady(false),
	mNewButton(NULL),
	mLoadButton(NULL),
	mGameButton(NULL),
	mEditTextBox(nullptr),
	mLuaButton(nullptr),
	mBgPlayer(NULL),
	mBgWave(NULL)
{
	//MME::Manager::instance()->regist( NULL, NULL );
	mImage = new Image( "Data/GUI/image/dummy.dds" );
	mFont = new Font();
	*mFont = Font::create( "ＭＳ ゴシック", 32, false, false, false, true ); //MSは全角、次のスペースは半角。気をつけよう。
	mStringRenderer = new StringRenderer();
	*mStringRenderer = StringRenderer::create( 512, 32 );
	mStringRenderer->setFont(*mFont);
	
	mNewButton = new GUI::ImageButton( 300, 50, 200, 50 );
	//何もセットしないと豆腐
	//mLoadButton->setTexture(0);
	mNewButton->setText( "New" );
	mNewButton->setFontColor( 0xff000000 );
	GUI::Manager::instance()->add( mNewButton );
	

	mLoadButton = new GUI::ImageButton( 300, 120, 200, 50 );
	//何もセットしないと豆腐
	//mLoadButton->setTexture(0);
	mLoadButton->setText( "Load" );
	mLoadButton->setFontColor( 0xff000000 );
	GUI::Manager::instance()->add( mLoadButton );

	mGameButton = new GUI::ImageButton( 300, 190, 200, 50 );
	mGameButton->setText( "Game" );
	mGameButton->setFontColor( 0xff000000 );
	GUI::Manager::instance()->add( mGameButton );

	
	mDanceButton = new GUI::ImageButton( 300, 260, 200, 50 );
	mDanceButton->setText( "Dance" );
	mDanceButton->setFontColor( 0xff000000 );
	GUI::Manager::instance()->add( mDanceButton );

	mLuaButton = new GUI::ImageButton( 300, 330, 200, 50 );
	mLuaButton->setText( "Lua" );
	mLuaButton->setFontColor( 0xff000000 );
	GUI::Manager::instance()->add( mLuaButton );


	mEditTextBox = new GUI::EditTextBox( 300, 400, 200, 50 );
	GUI::Manager::instance()->add( mEditTextBox );


	mBgWave = NEW Wave;
	*mBgWave = Wave::create( "Data/sound/bgm/title.wav" );
	GameLib::WindowCreator wc;
	wc.initializeIme();
}

Title::~Title(){
	SAFE_DELETE( mBgWave );
	SAFE_DELETE( mBgPlayer );
	SAFE_DELETE( mEditTextBox );
	SAFE_DELETE( mLuaButton );
	SAFE_DELETE( mDanceButton );
	SAFE_DELETE( mGameButton );
	SAFE_DELETE( mLoadButton );
	SAFE_DELETE( mNewButton );

	SAFE_DELETE( mStringRenderer );
	SAFE_DELETE( mFont );
	SAFE_DELETE( mImage );
	//GUI::Manager::instance()->destory();
}

Base* Title::update( Parent* parent ){
	Base* next = this;
	isReady();
	
	if( mLoadButton->isPushed() ){
		if( next ==this) {
			next = new Load( );
			if(mBgPlayer){
				mBgPlayer->stop();
			}
		}
	} else if( mNewButton->isPushed() ){
		if( next ==this) {

			if(mBgPlayer){
				mBgPlayer->stop();
			}
		}
	} else if( mGameButton->isPushed() ){
		if( next ==this) {

			if(mBgPlayer){
				mBgPlayer->stop();
			}
		}
	} else if( mDanceButton->isPushed() ){
		if( next ==this) {

			if(mBgPlayer){
				mBgPlayer->stop();
			}
		}
	} else if( mLuaButton->isPushed() ){
		if( next ==this) {
			
			if(mBgPlayer){
				mBgPlayer->stop();
			}
		}
	}

	GameLib::Input::Keyboard k;
	if(k.isTriggered('q')){
		GameLib::Framework f;
		f.requestEnd();
	} else if(k.isTriggered('w')){
		GameLib::Framework f;
		bool isFull = f.isFullScreen();
		f.enableFullScreen(!isFull);
	}


	//描画
	mImage->draw();

/*
	static std::string text;
	
	if(k.isTriggered('c')){
		text.clear();
	}

	if( !GameLib::ImeUi::getInputString().empty() ){
		text.append(GameLib::ImeUi::getInputString());
	}
	if( int num = GameLib::ImeUi::getCandidateCount() ){
		for( int i=0; i<num; ++i ){
			TRACE2( "%d: %s\n", i, GameLib::ImeUi::getCandidate(i) );
		}
	}
*/
	
	//字を出す
	mStringRenderer->add( 300, 0 , "MMG\n" );
	mStringRenderer->draw();

	GUI::Manager::instance()->draw();
	GameLib::Framework fw;
	typedef DebugScreen::Color C;
	DebugScreen sc;
	sc.setPosition( 0, 20 );
	sc.precision( 3 );
	sc << C(0xff000000) << "framerate:"<< fw.frameRate() << endl;

	return next;
}

bool Title::isReady(){
	if(mIsReady){
		return mIsReady;
	}
	if( mImage->isReady() &&
		mBgWave->isReady() &&
		mBgPlayer==NULL )
	{
		STRONG_ASSERT( !mBgWave->isError() );
		mBgPlayer = NEW Sound::Player;
		*mBgPlayer = Sound::Player::create( *mBgWave );
		mBgPlayer->play(true);
	}
	return mIsReady;
}

} //namespace Sequence