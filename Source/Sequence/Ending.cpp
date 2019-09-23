#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>
#include <GameLib/DebugScreen.h>

using namespace GameLib;

#include "Sequence/Ending.h"
#include "Sequence/Parent.h"
#include "Sequence/Title.h"

#include "helper/Image.h"

namespace Sequence{

Ending::Ending() : mImage( 0 ), mCount( 0 ){
	mImage = new Image( "Data/GUI/image/dummy.dds" ); 
}

Ending::~Ending(){
	SAFE_DELETE( mImage );
}

Base* Ending::update( Parent* ){
	Base* next = this;
	if(!isReady()){
		return next;
	}

	if ( mCount == 120 ){ //2•b‘Ò‚Â 
		next = new Title;
	}
	//•`‰æ
	mImage->draw();
	//š‚ğo‚·
	DebugScreen sc;
	sc.setPosition( 0, 0 );
	sc << "µÒÃŞÄ³! ±ÅÀÊ ºÉ¹Ş°Ñ¦ ¾²Ê¼Ï¼À\nÂ¸¯ÀËÄ Ë×ÔÏÀ¶¼\n       kgme\n";

	++mCount;

	return next;
}

bool Ending::isReady(){
	return mImage->isReady();
}

} //namespace Sequence