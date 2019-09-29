#include"Swing.h"
#include"Stand.h"
#include"Parent.h"
#include<GameLib/Input/Mouse.h>
#include"BulletPhysics/BulletPhysicsHelper.h"


namespace GameObject { namespace PlayerUtils{ namespace Updater { namespace Sword2 {

Swing::Swing( Parent* p  )
	:mModel(p->mModel),
	mMouse(p->mMouse),
	mNumPushedButton(1),
	mCurrentActionIndex(0)
{
	mModel->changeAnimation("swing0");
	//mModel->init( toDxMatrix( p->mRigidBody->getWorldTransform() ), "stand" );
}
Swing::~Swing(){}

Base* Swing::update( Parent *parent, float elapsedTime ){
	GameLib::Input::Mouse m;
	if( mModel->isAnimOver() ){
		if( mCurrentActionIndex == 0 &&
			mNumPushedButton > 0 )
		{
			++mCurrentActionIndex;
			mModel->changeAnimation( "swing1" );
		} else if( mCurrentActionIndex == 1 &&
			mNumPushedButton > 1 )
		{
			++mCurrentActionIndex;
			mModel->changeAnimation( "swing2" );
		} else if( mCurrentActionIndex == 2 &&
			mNumPushedButton > 2 )
		{
			++mCurrentActionIndex;
			mModel->changeAnimation( "swing3" );
		} else if( mCurrentActionIndex == 3 &&
			mNumPushedButton > 3 )
		{
			++mCurrentActionIndex;
			mModel->changeAnimation( "swing4" );
		}
		else if (mCurrentActionIndex == 4) {
			++mCurrentActionIndex;
			mModel->changeAnimation("swing_end");
		} else {
			mModel->changeAnimation( "stand" );
			return new Stand( parent );
		}
	}




	if( m.isTriggered(m.BUTTON_RIGHT) ){
		++mNumPushedButton;
	}

	return this;
}


} } } }//GameObject::PlayerUtils::Updater::Sword2