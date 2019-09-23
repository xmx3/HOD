#include <GameLib/GameLib.h>
#include "Sequence/Parent.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Parent.h"
#include "Sequence/HatuneOfTheDead/CppImpl/Ready.h"
#include "Sequence/HatuneOfTheDead/CppImpl/State.h"
#include "helper/Image.h"
#include "MMD/MMDDataBase.h"
#include "MME/Manager.h"


namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{

Parent::Parent()
	:mChild( 0 ),
	mState(0) {
	mState =  State::instance();

	//Å‰‚ÍReady
	mChild = new Ready(mState);
}

Parent::~Parent(){
	State::instance()->release();
	SAFE_DELETE( mChild );
}

Base* Parent::update( GrandParent* ){
	Base* next = this;
	Base* nextChild = mChild->update( this );
	//‘JˆÚ”»’è
	if ( nextChild != mChild ){
		HatuneOfTheDead::CppImpl::Child* casted = dynamic_cast< HatuneOfTheDead::CppImpl::Child* >( nextChild );
		if ( casted ){
			SAFE_DELETE( mChild );
			mChild = casted;
		}else{
			next = nextChild;
		}
		casted = 0;
	}
	nextChild = 0; //”O‚Ì‚½‚ß

	return next;
}

void Parent::updateState() {
	mState->update();
}
void Parent::drawState() {
	mState->draw();
}

bool Parent::isReady() {
	static int c = 0;
	++c;
	if (c < 300) {
		return false;
	}
	return mState->isReady();
}

bool Parent::isClear() const {
	return mState->isClear();
}


}}} //namespace Sequence::HatuneOfTheDead::CppImpl
