#ifndef __MMDMACRO_H__
#define __MMDMACRO_H__

#include<boost/foreach.hpp>

#ifndef SAFE_DELETE
#define SAFE_DELETE( x ) { delete ( x ); ( x ) = 0; }
#endif//SAFE_DELETE

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY( x ) { delete[] ( x ); ( x ) = 0; }
#endif //SAFE_DELETE_ARRAY

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#endif//SAFE_RELEASE

//#ifndef foreach
//#define foreach BOOST_FOREACH
//#endif //foreach

#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName( const TypeName& )=delete; \
	void operator=( const TypeName& )=delete
#endif

#endif//__MMDMACRO_H__