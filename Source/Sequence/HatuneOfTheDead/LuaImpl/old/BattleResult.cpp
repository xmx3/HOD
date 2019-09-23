#include "BattleResult.h"
#include "GUI/Button.h"
#include "GUI/Label.h"
#include "GUI/Manager.h"

#include "Parent.h"
#include "Play.h"

#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>

#include <boost/lexical_cast.hpp>
#include <string>

namespace Sequence{ namespace HatuneOfTheDead{ namespace LuaImpl {
	BattleResult::BattleResult()
		:mCount(0),
		mOk(NULL),
		mLabel(NULL)
	{
		int h = GameLib::Framework::instance().height();
		int w = GameLib::Framework::instance().width();
		int sizeX= 100;
		int sizeY= 50;
		mOk = NEW GUI::Button( w/2-sizeX/2, h/2-sizeY/2+100, sizeX, sizeY);
		mOk->setText("ok");
		GUI::Manager *mngr = GUI::Manager::instance();

		sizeX = 400;
		sizeY = 300;

		mLabel = NEW GUI::Label( w/2-sizeX/2, h/2-sizeY/2, sizeX, sizeY );
		mLabel->setFontColor(0xffff0000);

		mngr->add(mLabel);
		mngr->add(mOk);

	}

	BattleResult::~BattleResult(){
		SAFE_DELETE(mLabel);
		SAFE_DELETE(mOk);
	}

	Base* BattleResult::update( Parent* parent ){
		Base *next=this;
		if(mOk->isPushed()){
			next= new Play();
		}

		std::string text = boost::lexical_cast<std::string>(mCount);
		mLabel->setText( text.c_str() );

		if( mCount > 1000 && next==this ){
			next= new Play();
		}
		++mCount;
		parent->drawState();
		GUI::Manager::instance()->draw();
		
		return next;
	}
}}}//end Sequence::HatuneOfTheDead::LuaImpl
