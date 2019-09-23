#include <GameLib/GameLib.h>
#include <GameLib/Framework.h>
#include"Child.h"
#include"Parent.h"

namespace GameObject{ namespace EnemyUtils { namespace Updater {

Child::~Child(){
}

Base* Child::update( Base* p, float elapsedTime ){
	Parent* parent = dynamic_cast< Parent* >( p );
	ASSERT( parent );
	return update( parent, elapsedTime );
}

} } } //GameObject::EnemyUtils::Updater
