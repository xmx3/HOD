#include "Light.h"
#include "MME/Manager.h"
#include "MME/Batch/StandardEffectBatch.h"
#include "MME/Batch/PostEffectBatch.h"
#include <GameLib/GameLib.h>//SAFE_DELETE
#include "helper/FileLoader.h"
#include "GameObject/AccessoryUtils/MME/Model.h"
#include "MME/Object/ModelKai.h"
#include "MME/Object/Accessory.h"
#include "MME/Object/PointLight.h"

#include <GameLib/Graphics/Manager.h>


namespace MME {
namespace {
using namespace Batch;
static const char *skDrawGBufferFxFileName = "ShaderTest/Basic/deffered_shading_luminous/basic.fx";
//static const char *skDrawGBufferFxFileName = "ShaderTest/Basic/full.fx";//defalut
//static const char *skDrawGBufferFxFileName = "ShaderTest/Basic/deffered_shading/basic.fx";
//static const char *skDrawGBufferFxFileName = "ShaderTest/Basic/deffered_shading_shadow/basic.fx";

static const char *skLuminousFxFileName = "ShaderTest/Basic/deffered_shading_luminous/postEffect.fx";

static const char *skFXAAFileName = "ShaderTest/Fxaa/fxaa.fx";

static const char *skPointLightFxFileName="ShaderTest/Basic/DSPoinghtLight.fx";

StandardEffectBatch* createStandardEffectBatchIf( const char* filename ){
	MME::Manager* mme= MME::Manager::instance();
	StandardEffectSharedPtr effect = mme->findStandardEffect( filename );
	if( effect ){
		return new StandardEffectBatch( effect );
	}
	return nullptr;	
}

PostEffectBatch* createPostEffectBatchIf( const char* filename ){
	MME::Manager* mme= MME::Manager::instance();
	PostEffectSharedPtr effect = mme->findPostEffect( filename );
	if( effect ){
		return new PostEffectBatch( effect );
	}
	return nullptr;
}

bool canRemove( const Object::IObjectWeakPtr & wp ){
	if( Object::IObjectSharedPtr sp = wp.lock() ){
		return sp->canRemove();
	} else{
		return true;
	}
}

}//end unnamespace

namespace Drawer { namespace CutSceneImpl { namespace Light {
Impl::Uptr Impl::mThis;

Impl* Impl::instance(){
	if( !mThis )
	{
		mThis.reset(  new Impl() );
	}
	return mThis.get();
}

void Impl::destroy(){
	
	mThis.reset( nullptr );
}

Impl::Impl()
	:mDrawGBuffer(nullptr),
	mLuminous(nullptr),
	mFxaa(nullptr),
	mPointLight(nullptr),
	mFileLoader(nullptr)
{
	mObjectsPtr.reset( new MME::Batch::DrawObjects );
	mLightsPtr.reset( new MME::Batch::DrawObjects );
	
	MME::Manager* mme= MME::Manager::instance();
	
	mDrawGBuffer = createStandardEffectBatchIf( skDrawGBufferFxFileName );
	if( mDrawGBuffer ){
		mDrawGBuffer->setObjectsPtr( mObjectsPtr );
	}
	
	if( mDrawGBuffer )
	{
		return;
	}
	
	mFileLoader = new FileLoader();
	
	if( !mDrawGBuffer ){
		mFileLoader->insert( skDrawGBufferFxFileName );
	}
}

Impl::~Impl(){
	SAFE_DELETE( mFileLoader );
	SAFE_DELETE( mDrawGBuffer );
	SAFE_DELETE( mLuminous );
	SAFE_DELETE( mFxaa );
	SAFE_DELETE( mPointLight );
}

bool Impl::isReady(){
	if( mFileLoader ){
		if(mFileLoader->isFinished()){
			
			MME::Manager* mme= MME::Manager::instance();
			if( !mDrawGBuffer ){
				mDrawGBuffer = new StandardEffectBatch(
					mme->registStandardEffect( 
							skDrawGBufferFxFileName,
							mFileLoader->get( skDrawGBufferFxFileName ) ) );
				mDrawGBuffer->setObjectsPtr( mObjectsPtr );
			}
					
			SAFE_DELETE(mFileLoader);
			return true;
		}
		else {
			return false;
		}
	}
	return true;
}

void Impl::draw(){
//	描画タイミングは、以下の通りです。
//(1) セルフシャドウ用Zバッファ描写(zplot)
//(2) OFFSCREENRENDERTARGET一式描画
//(3) ポストエフェクトのScriptの、先頭から"ScriptExternal=Color"まで
//(4) プリエフェクト
//(5) モデルよりも先に描画されるアクセサリ一式描画（object, object_ss）
//(6) 地面影一式描写（shadow） ※ただしアクセの描画順序は不定
//(7) モデル一式描画（object, object_ss）
//(8) エッジ一式描画（edge）
//(9) モデルより後に描写されるアクセサリ一式描写（object, object_ss）
//(10) ポストエフェクトのScriptの、"ScriptExternal=Color"から最後まで
//※(5)～(9)については、MMD側の描画順序に由来します。
	GameLib::Graphics::Manager m;
	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();

	using namespace GameLib::Graphics;
	m.setBlendMode( BLEND_LINEAR );
	//mmdは左手座標
	m.setCullMode( CULL_FRONT );
	m.enableDepthTest( true );
	m.enableDepthWrite( true );

	m.enableMME(true);

	MME::Manager* mme= MME::Manager::instance();

	DrawObjects::iterator it = std::remove_if( mObjectsPtr->begin(), mObjectsPtr->end(), canRemove );
	mObjectsPtr->erase( it, mObjectsPtr->end());

	//offscreenないからコメントアウトしても良いよ
	mDrawGBuffer->drawOffScreens();

	mDrawGBuffer->drawObject();		
	
	m.dxDevice()->SetRenderTarget( 1, NULL );
	m.dxDevice()->SetRenderTarget( 2, NULL );
	m.dxDevice()->SetRenderTarget( 3, NULL );

	mme->setCurrentEffect(nullptr);
	
	//後始末　強制的にVertexBlendを無効にしておく
	//困るのはGameLib::Graphics::ManagerのVertexBlendEnableが無効なのに、有効な値が入っている場合なので
	//GameLib::Graphics::ManagerのVertexBlendEnableが有効の場合はすぐに正しい値を代入するはずなので問題なし
	//GameLib::Graphics::ManagerのVertexBlendEnableが無効でここのVertexBlendEnableも無効ならば問題なし
	m.enableMME(false);
	m.enableVertexBlend(true);
	m.enableVertexBlend(false);

	//mme->drawShadowMapBuffer();

	mme->sendParamsToGameLibGraphicsManager();
}


void Impl::add( const Object::ModelKaiSharedPtr &obj){
	mObjectsPtr->push_back( obj );
}
void Impl::add( const Object::PointLightSharedPtr &obj){
}
	
void Impl::add( const Object::AccessorySharedPtr &obj){
	mObjectsPtr->push_back( obj );
}
void Impl::add( const GameObject::AccessoryUtils::MME::ModelSharedPtr &obj){
	mObjectsPtr->push_back( obj );
}

} } } }// namespace MME::Drawer::CutSceneImpl::Light
