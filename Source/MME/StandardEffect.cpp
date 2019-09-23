#include"StandardEffect.h"
#include"StandardTechnique.h"
#include<assert.h>
#include"helper/ContainerHelper/safeDeleteAll.h"
#include"OffScreenRender.h"
#include"ControlObjectSelf.h"
#include<boost/timer.hpp>
#include"MME/Manager.h"

#include<GameLib/Input/Keyboard.h>
namespace MME {
namespace{
	
} //end namespace

StandardEffect::StandardEffect( const std::string &fxFileName, GameLib::FileIO::InFile file, LPD3DXEFFECTPOOL pool )
	:BaseEffect(fxFileName, file, pool)
{

	if( mScriptOrder!=SO_STANDARD ){
		mIsError=true;
		assert( false && "this effect is not standard effect. please check STANDARDSGLOBAL." );
		return;
	}
	D3DXEFFECT_DESC effectDesc;
	mEffect->GetDesc( &effectDesc );

	for( UINT iTech=0; iTech < effectDesc.Techniques; ++iTech )
	{
		D3DXHANDLE hTech = mEffect->GetTechnique( iTech );
		assert( hTech );

		StandardTechnique *tech = new StandardTechnique( mEffect, hTech, this );
		mTechniques.push_back( tech );
		if( tech->isError() ){
			assert(false && "mmeÇÃèâä˙âªÇ…é∏îsÇµÇ‹ÇµÇΩ");
			mIsError=true;
			return;
		}
	}
	mTechniques.shrink_to_fit();
}

StandardEffect::~StandardEffect(){
	using namespace ContainerHelper;
	mTechniques|safeDeleteAll();
}

StandardTechnique* StandardEffect::findTequnique( MMDPass mmdPass, bool useTexture, bool useSphereMap, bool useToon, bool useSelfShadow )
{
	for( int i=0, size=mTechniques.size(); i<size; ++i ){
		if( mTechniques[i]->canUse( mmdPass, useTexture, useSphereMap, useToon, useSelfShadow ) )
		{
			return mTechniques[i];
		}
	}
	return 0;
}




void StandardEffect::drawZPlot(){
	MME::Manager *m = MME::Manager::instance();
	m->setCurrentEffect( this );
	m->sendParams( this );
	saveCurrentBackBuffers();
	//setTextures();

	
	drawTech( MP_ZPLOT, DISABLE_TEXTURE, DISABLE_SPHEREMAP, DISABLE_TOON, DISABLE_SELFSHADOW );
	
	m->setCurrentEffect( 0 );

}

void StandardEffect::drawObject(){
	
	MME::Manager *m = MME::Manager::instance();
	m->setCurrentEffect( this );
	m->sendParams( this );
	saveCurrentBackBuffers();
	//setTextures();

	drawTech( MP_OBJECT, ENABLE_TEXTURE, DISABLE_SPHEREMAP, DISABLE_TOON, DISABLE_SELFSHADOW );
	drawTech( MP_OBJECT, ENABLE_TEXTURE, ENABLE_SPHEREMAP,  DISABLE_TOON, DISABLE_SELFSHADOW );
	drawTech( MP_OBJECT, ENABLE_TEXTURE, DISABLE_SPHEREMAP, ENABLE_TOON,  DISABLE_SELFSHADOW );
	drawTech( MP_OBJECT, ENABLE_TEXTURE, ENABLE_SPHEREMAP,  ENABLE_TOON,  DISABLE_SELFSHADOW );

	m->setCurrentEffect( 0 );

}
void StandardEffect::drawObjectSS(){
	MME::Manager *m = MME::Manager::instance();
	m->setCurrentEffect( this );	
	m->sendParams( this );
	saveCurrentBackBuffers();
	//setTextures();

	drawTech( MP_OBJECT, ENABLE_TEXTURE, DISABLE_SPHEREMAP, DISABLE_TOON, ENABLE_SELFSHADOW );
	drawTech( MP_OBJECT, ENABLE_TEXTURE, ENABLE_SPHEREMAP,  DISABLE_TOON, ENABLE_SELFSHADOW );
	drawTech( MP_OBJECT, ENABLE_TEXTURE, DISABLE_SPHEREMAP, ENABLE_TOON,  ENABLE_SELFSHADOW );
	drawTech( MP_OBJECT, ENABLE_TEXTURE, ENABLE_SPHEREMAP,  ENABLE_TOON,  ENABLE_SELFSHADOW );

	//GameLib::Input::Keyboard k;
	//static int i=0;
	//if( k.isTriggered('d') )
	//{
	//	if(++i>3){
	//		i=0;
	//	}
	//}
	//switch(i){
	//	case 0:
	//		drawTech( MP_OBJECT, ENABLE_TEXTURE, DISABLE_SPHEREMAP, DISABLE_TOON, ENABLE_SELFSHADOW );
	//		break;
	//	case 1:
	//		drawTech( MP_OBJECT, ENABLE_TEXTURE, ENABLE_SPHEREMAP,  DISABLE_TOON, ENABLE_SELFSHADOW );
	//		break;
	//	case 2:
	//		drawTech( MP_OBJECT, ENABLE_TEXTURE, DISABLE_SPHEREMAP, ENABLE_TOON,  ENABLE_SELFSHADOW );
	//		break;
	//	case 3:
	//		drawTech( MP_OBJECT, ENABLE_TEXTURE, ENABLE_SPHEREMAP,  ENABLE_TOON,  ENABLE_SELFSHADOW );
	//		break;
	//}

	m->setCurrentEffect( 0 );

}
void StandardEffect::drawEdge(){
	MME::Manager *m = MME::Manager::instance();
	m->setCurrentEffect( this );
	m->sendParams( this );
	saveCurrentBackBuffers();
	//setTextures();

	drawTech( MP_EDGE, DISABLE_TEXTURE, DISABLE_SPHEREMAP, DISABLE_TOON, DISABLE_SELFSHADOW );

	m->setCurrentEffect( 0 );
}

void StandardEffect::drawZPrePass(){
	MME::Manager *m = MME::Manager::instance();
	m->setCurrentEffect( this );
	m->sendParams( this );
	saveCurrentBackBuffers();
	//setTextures();

	drawTech( MP_ZPREPASS, DISABLE_TEXTURE, DISABLE_SPHEREMAP, DISABLE_TOON, DISABLE_SELFSHADOW );

	m->setCurrentEffect( 0 );

}

void StandardEffect::drawTech(
	MMDPass mmdPass,
	UseTexture useTexture,
	UseSphereMap useSphereMap,
	UseToon useToon,
	UseSelfShadow useSelfShadow )
{
	//åªç›ÇÃï`âÊèÛë‘Çï€ë∂
	mPass = mmdPass;
	mUseTexture = useTexture;
	mUseSphereMap = useSphereMap;
	mUseToon = useToon;
	mUseSelfShadow = useSelfShadow;

	mCurrentTech = findTequnique(
		mPass, 
		mUseTexture!=0,
		mUseSphereMap!=0,
		mUseToon!=0,
		mUseSelfShadow!=0 );
	
	setUseFlag();

	if( mCurrentTech ){
		mCurrentTech->exec();
	}
	else{
		//defalutMME
		//assert(false);
		const char* passTexts[] = {
			"OBJECT",
			"ZPLOT",
			"OBJECT_SS",
			"SHADOW",  
			"EDGE",
			"ZPREPASS"
		};
		if(mPass!=MP_ZPREPASS){
			TRACE2("%s: %s dont draw\n", passTexts[mPass], mName.c_str() );
		}
	}
	mCurrentTech = 0;
}


}