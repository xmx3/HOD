#include"IObject.h"
#include<string>
#include<d3dx9.h>
#include<memory>
#include"MME/Enums.h"
#include"MME/BaseEffect.h"
#include"MME/OffScreenRender.h"
#include"MME/Manager.h"

namespace MME{
	namespace Object{

IObject::IObject()
	:mCanDraw(true),
	mTr(1.0),
	mSi(1.0),
	mCanRemove(false)
{
	for( int i=0; i<MME::MP_NUM; i++ ){
		mCanDrawMMDPass[i]=true;
	}

	D3DXMatrixIdentity( &mTransform );
}

IObject::~IObject(){}

//void IObject::registOffScreen( const char *effectFileName ,const char *offScreenName, const char *effectFileNameInOffScreen ){
//	MME::Manager *mngr = MME::Manager::instance();
//	MME::BaseEffectSharedPtr ptr =  mngr->findPostEffect( effectFileName );
//	if( !ptr ){
//		ptr = mngr->findStandardEffect( effectFileName );
//	}
//
//	if( !ptr ){
//		assert(false);
//		return;
//	}
//
//	OffScreenRenderSharedPtr os = ptr->findOffScreen( offScreenName );
//	if( os==NULL ){
//		assert(false);
//		return;
//	}
//
//	StandardEffectSharedPtr effectInOffScreen = os->findStandardEffect( effectFileNameInOffScreen );
//	if( !effectInOffScreen ){
//		assert(false);
//		return;
//	}
//	effectInOffScreen->add( shared_from_this() );
//}
//

bool IObject::canDraw()const{
	return mCanDraw;
}

void IObject::setCanDraw( bool canDraw ){
	mCanDraw = canDraw;
}

void IObject::setCanDraw( MME::MMDPass pass, bool canDraw ){
	mCanDrawMMDPass[pass]=canDraw;
}

float IObject::getSi()const{
	return mSi;
}
float IObject::getTr()const{
	return mTr;
}

const D3DXMATRIX & IObject::getWorldTransform() const{
	return mTransform;
}

bool IObject::canRemove()const{
	return mCanRemove;
}

void IObject::setCanRemove( bool canRemove ){
	mCanRemove = canRemove;
}

}//end namespace Object
}// end namespace MME