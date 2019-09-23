#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>
#include"Child.h"
#include"Parent.h"

namespace GameObject{ namespace PlayerUtils { namespace Updater { namespace Sword2 {

Child::~Child(){
}

Base* Child::update( Base* p, float elapsedTime ){
	Parent* parent = dynamic_cast< Parent* >( p );
	ASSERT( parent );
	return update( parent, elapsedTime );
}

} } } }//GameObject::PlayerUtils::Updater::Sword2
