#include"Swing1.h"
#include"Stand.h"
#include"Parent.h"
#include<GameLib/Input/Mouse.h>
#include"BulletPhysics/BulletPhysicsHelper.h"
#include"GameObject/Accessory.h"
#include"GameObjectData/WeaponStatus.h"


namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace TameSword {

namespace {
	static const float skPusingShortTime = 1.f/30.f * 10.f; 
	static const float skPusingMiddleTime = 1.f/30.f * 20.f; 
	static const float skPusingLongTime = 1.f/30.f * 40.f; 
	enum {
		kLong,
		kMiddle,
		kShort,
		kVeryShort
	};

	int howLongWasButtonPushed(float time){
		if( time > skPusingLongTime ){
			return kLong;
		} else if( time > skPusingMiddleTime ){
			return kMiddle;
		} else if( time > skPusingShortTime ){
			return kShort;
		} else {
			return kVeryShort;
		}
	}


}//end unnamespace
Swing1::Swing1( Parent* p, float pushingButtonTime  )
	:Child(p)
{

	mModel->changeAnimation("swing1");
	//changeAnimationした瞬間にアクセサリの当たり判定等は変わってる
	//表示や物理世界に入ってないだけ
	//該当コード
	//void AccessoryHook::hookStart(){
	//	mAccessory->setWeaponStatus( mWeaponStatus );
	//	mAccessory->attachBone(mBone);
	//	mAccessory->enableContactResponse(mEnableContactResponse);
	//}


	Accessory* a = mModel->getAccessory("negiRight").get();
	assert(a);
	mOriginalScale = a->getScale();

	switch( howLongWasButtonPushed( pushingButtonTime) ){
	case kLong :
		a->setScale( mOriginalScale*4.f );
		break;
	case kMiddle :
		a->setScale( mOriginalScale*2.f );
		break;
	case kShort :
		a->setScale( mOriginalScale*1.f );
		break;
	case kVeryShort:
		break;
	default :
		break;
	}

}
Swing1::~Swing1(){
}

Base* Swing1::update( Parent *parent, float elapsedTime ){
	GameLib::Input::Mouse m;

	if( m.isOn(m.BUTTON_RIGHT) ){
		mPushingButtonTime+=elapsedTime;
		return this;
	} else {
		if( mModel->isAnimOver() ){
			//return new Swing2( parent, mPushingButtonTime );
		//} else {
			return new Stand(parent);
		}
	}

	return this;

}


} } } }//GameObject::PlayerUtils::Updater::TameSword
