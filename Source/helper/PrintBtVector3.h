#ifndef __PRINT_BTVECTOR3_H__
#define __PRINT_BTVECTOR3_H__
#include <GameLib/DebugScreen.h>
#include <btBulletCollisionCommon.h>
#include "helper/MyOutputDebugString.h"

class PrintBtVector3 {
public:
	static void toDebugScreen( const btTransform &bttr , int x=0, int y=0 ){
		toDebugScreen( bttr.getOrigin(), x, y );
	}
	static void toDebugScreen( const btVector3 &bv, int x=0, int y=0 ){
		typedef GameLib::DebugScreen::Color C;
		GameLib::DebugScreen sc;
		sc.setPosition( x, y );
		sc.precision( 3 );
		sc << C(0xff000000);
		sc << "( "<<bv.x() << ", " << bv.y() << ", " << bv.z() << ")" << GameLib::endl;
	}

	static void toOutput( const btTransform &bttr ){
		toOutput( bttr.getOrigin() );
	}
	static void toOutput( const btVector3 &bv ){
		TRACE3( "( %f, %f, %f )\n", bv.x(), bv.y(), bv.z() ); 
	}
};

#endif