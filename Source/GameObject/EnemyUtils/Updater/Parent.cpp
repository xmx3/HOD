#include <GameLib/GameLib.h>
#include"Parent.h"
#include"Child.h"

namespace GameObject{ namespace EnemyUtils { namespace Updater {

Parent::Parent(Enemy* enemy)
	:mChild( nullptr )
{
}

Parent::~Parent(){
	SAFE_DELETE( mChild );
}

void Parent::update( float dt ){
	Base* nextChild = mChild->update( this, dt );
	if ( nextChild != mChild ){
		//‘JˆÚ”»’è
		Child* casted = dynamic_cast< Child* >( nextChild );
		ASSERT( casted ); //¸”s‚Í‚ ‚è‚¦‚È‚¢B
		SAFE_DELETE( mChild );

		mChild = casted;
	}
	nextChild = 0; //”O‚Ì‚½‚ß
}

} } } //GameObject::EnemyUtils::Updater
