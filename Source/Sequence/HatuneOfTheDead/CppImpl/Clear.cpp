#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>
#include <GameLib/DebugScreen.h>
using namespace GameLib;

#include "Sequence/HatuneOfTheDead/CppImpl/Clear.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Parent.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Ready.h"
#include "Sequence/Ending.h"
#include "helper/Image.h"

namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{

Clear::Clear() : mImage( 0 ), mCount( 0 ){
	mImage = new Image( "Data/GUI/image/dummy.dds" ); 
}

Clear::~Clear(){
	SAFE_DELETE( mImage );
}

Base* Clear::update( Parent* parent ){
	Base* next = this;
	if(!isReady()){
		return next;
	}

	if ( mCount == 60 ){ //1•b‘Ò‚Â 
		next = new Ending;
	}
	//•`‰æ
	//j‚¢‚ÌƒƒbƒZ[ƒW‚ð•`‰æ
	mImage->draw();
	//ƒNƒŠƒA[‚ÆŽš‚ð•`‚­
	DebugScreen sc;
	sc.draw( 0, 0, "¸Ø±°! next Ending!" );

	++mCount;

	return next;
}
bool Clear::isReady(){
	return mImage->isReady();
}

}}} //namespace Sequence::HatuneOfTheDead::CppImpl
