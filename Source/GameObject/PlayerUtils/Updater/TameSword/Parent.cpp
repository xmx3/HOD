#include <GameLib/GameLib.h>
#include"Parent.h"
#include"Child.h"
#include"Stand.h"
#include"GameObject/Player.h"
#include<BulletDynamics/Dynamics/btRigidBody.h>
#include<assert.h>
namespace GameObject{ namespace PlayerUtils { namespace Updater { namespace TameSword {

Parent::Parent( Player *pl)
	:mChild( 0 ),
	mRigidBody(0),
	mStatus( pl->getStatus() ),
	mModel( pl->getModel() ),
	mMouse( pl->getMouse() ),
	mPlayer(pl)
{
	mRigidBody = btRigidBody::upcast(pl->getBtCollisionObject());
	mChild = new Stand(this);
}

Parent::~Parent(){
	//c‚Á‚Ä‚¢‚ê‚Î–•E
	SAFE_DELETE( mChild );
}

Root::Base* Parent::update( GrandParent* ,float dt ){
	Base* next = this;
		
	Base* nextChild = mChild->update( this, dt );
	if ( nextChild != mChild ){
		//‘JˆÚ”»’è
		TameSword::Child* casted = dynamic_cast< TameSword::Child* >( nextChild );
		if( casted ){
			SAFE_DELETE( mChild );
			mChild = casted;
		} else {
			assert(false && "İŒvã‚æ‚ë‚µ‚­‚È‚¢‹C‚ª‚·‚é" );
			//‚±‚±‚Åˆ—‚Å‚«‚È‚¢‚Ì‚Åã‚É”C‚¹‚é
			next = nextChild;
		}
		casted = nullptr;
	}

	return next;
}

} } } } //GameObject::PlayerUtils::Updater::TameSword
