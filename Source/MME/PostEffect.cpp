#include"PostEffect.h"
#include"PostTechnique.h"
#include<assert.h>
#include"helper/ContainerHelper/safeDeleteAll.h"
#include"Manager.h"
namespace MME {

namespace{
}

PostEffect::PostEffect( const std::string &fxFileName, GameLib::FileIO::InFile file, LPD3DXEFFECTPOOL pool )
	:BaseEffect(fxFileName, file, pool)
{
	//現在の描画状態を保存
	mPass = MP_OBJECT;
	mUseTexture = DISABLE_TEXTURE;
	mUseSphereMap = DISABLE_SPHEREMAP;
	mUseToon = DISABLE_TOON;
	mUseSelfShadow = DISABLE_SELFSHADOW;

	if( mScriptOrder!=SO_POST_PROCESS ){
		mIsError=true;
		assert( false && "this effect is not post effect. please check STANDARDSGLOBAL." );
		return;
	}

	D3DXEFFECT_DESC effectDesc;
	mEffect->GetDesc( &effectDesc );

	for( UINT iTech=0; iTech < effectDesc.Techniques; ++iTech )
	{
		D3DXHANDLE hTech = mEffect->GetTechnique( iTech );
		assert( hTech );

		PostTechnique *tech = new PostTechnique( mEffect, hTech, this );
		mTechniques.push_back( tech );
		if( tech->isError() ){
			assert(false && "mmeの初期化に失敗しました");
			mIsError=true;
			return;
		}
	}
	mTechniques.shrink_to_fit();
	assert(mOffScreenRenders.empty() && "ポストエッフェクトにoffscreenいるか？");
}

PostEffect::~PostEffect(){
	using namespace ContainerHelper;
	mTechniques|safeDeleteAll();
}

void PostEffect::preDraw(){
	if(!mIsEnable){
		return;
	}
	
	PostTechnique* t = findTequnique( MP_OBJECT, false, false, false, false );
	saveCurrentBackBuffers();
	if(t){
		t->preExec();
	}
	else{
		assert(false);
	}
}
void PostEffect::postDraw(){
	if(!mIsEnable){
		return;
	}

	PostTechnique* t = findTequnique( MP_OBJECT, false, false, false, false );
	Manager *m = Manager::instance();
	m->sendParams( this );
	m->setCurrentEffect( this );
	//setTextures();
	if(t){
		t->postExec();
	}
	else{
		assert(false);
	}
	m->setCurrentEffect( 0 );
}

PostTechnique* PostEffect::findTequnique( MMDPass mmdPass, bool useTexture, bool useSphereMap, bool useToon, bool useSelfShadow )
{
	for( int i=0, size=mTechniques.size(); i<size; ++i ){
		if( mTechniques[i]->canUse( mmdPass, useTexture, useSphereMap, useToon, useSelfShadow ) )
		{
			return mTechniques[i];
		}
	}
	return 0;
}

}