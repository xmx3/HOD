#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>
#include"Child.h"
#include"Parent.h"

namespace GameObject{ namespace PlayerUtils { namespace Updater { namespace TameSword {


Child::Child(Parent* p)
	:mRigidBody(p->mRigidBody),
	mStatus( p->mStatus ),
	mModel( p->mModel ),
	mMouse( p->mMouse ),
	mPlayer( p->mPlayer )
{
}

Child::~Child(){
}

Base* Child::update( Base* p, float elapsedTime ){
	Parent* parent = dynamic_cast< Parent* >( p );
	ASSERT( parent );
	return update( parent, elapsedTime );
}

} } } }//GameObject::PlayerUtils::Updater::TameSword
