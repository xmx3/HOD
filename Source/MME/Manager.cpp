#include"Manager.h"
#include<GameLib/Graphics/Manager.h>
#include<assert.h>
#include"StandardEffect.h"
#include"PostEffect.h"
#include"BaseEffect.h"
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/Vertex.h>
#include"SegaTypeHelper.h"
#include"OffScreenRender.h"
#include<mmsystem.h>
#include<boost/timer.hpp>
#include<GameLib/Input/Keyboard.h>
#include"MME/Drawer/CutScene.h"
#include"MME/Drawer/GameDrawer.h"
#include"MME/Object/PointLight.h"


#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#endif//SAFE_RELEASE



namespace{
	static const char *skDefalutFxFileName = "ShaderTest/Basic/deffered_shading_luminous/basic.fx";
	//static const char *skDefalutFxFileName = "ShaderTest/Basic/full.fx";//defalut
	//static const char *skDefalutFxFileName = "ShaderTest/Basic/deffered_shading/basic.fx";
	//static const char *skDefalutFxFileName = "ShaderTest/Basic/deffered_shading_shadow/basic.fx";
	
	//static const char *skDefalutPostFxFileName = NULL;
	static const char *skDefalutPostFxFileName = "ShaderTest/Basic/deffered_shading_luminous/postEffect.fx";
	
	//static const char *skFXAAFileName = NULL;
	static const char *skFXAAFileName = "ShaderTest/Fxaa/fxaa.fx";
	

	static const char *skGaussianFxFileName= NULL;
	//static const char *skGaussianFxFileName= "ShaderTest/Gaussian/Gaussian.fx";

	//static const char *skPointLightFxFileName=NULL;
	static const char *skPointLightFxFileName="ShaderTest/Basic/DSPoinghtLight.fx";


	static const bool skEnableFileter=false;
	static const float skShadowTexSizeRate=3.0f;
	//static const D3DFORMAT skShadowFMT = D3DFMT_A16B16G16R16F;
	//static const D3DFORMAT skShadowFMT = D3DFMT_A8R8G8B8;
	static const D3DFORMAT skShadowFMT = D3DFMT_G32R32F;
	//static const D3DFORMAT skShadowFMT = D3DFMT_R32F;
	//static const D3DFORMAT skShadowFMT = D3DFMT_G16R16F;
	//ワールド座標空間上でのディスプレイの位置
	void calcWorldPosFromDisplayPos(
		D3DXVECTOR3 *pOut,
		const D3DXVECTOR3 &vDisplayPos,//Z値が0だとカメラの位置、Z値が1だと奥の座標(カメラが移す最も遠い位置)
		const  D3DXMATRIX &viewProj )
	{
		int x, y, width, height;
		GameLib::Graphics::Manager::instance().getViewport( &x, &y, &width, &height );
		D3DXMATRIX matI;
		D3DXMATRIX matViewPort;
		D3DXMATRIX matInverseViewPort, matInverseViewProj;
		D3DXMatrixIdentity( &matViewPort );
		matViewPort._11 = static_cast<float>( width )/2.0f;
		matViewPort._22 = static_cast<float>( -height )/2.0f;
		matViewPort._41 = static_cast<float>( width )/2.0f;
		matViewPort._42 = static_cast<float>( height )/2.0f;
		D3DXMatrixInverse( &matInverseViewPort, NULL, &matViewPort );
		
		D3DXMatrixInverse( &matInverseViewProj, NULL, &viewProj );

		D3DXMATRIX matITemp =  matInverseViewPort * matInverseViewProj; 

		D3DXVec3TransformCoord( pOut, &vDisplayPos, &matITemp );
		return;
	}

	void backup(){
		MME::Manager::instance()->backup();
	}
	void recover(){
		MME::Manager::instance()->recover();
	}


}// end unnamed space

namespace MME {
using namespace GameLib::Math;

std::vector<Manager::UptrManager> Manager::mThese;


Manager* Manager::instance() {
	unsigned int index=0;
	if( ! (index < mThese.size()) ){
		mThese.resize( index+1 );
	}

	if( !mThese[index] )
	{
		mThese.emplace( mThese.begin()+index, new Manager );
	}
	return mThese[index].get();
}

// 解放
void Manager::destroy()
{
	for( int i=0, size=mThese.size(); i<size; ++i ){
		if(this==mThese[i].get()){
			mThese[i].reset();
			//やっていることは delete this;に近い
			return;
		}
	}
	MME::Object::PointLight::destroy();
	MME::Drawer::GameDrawer::destroy();
	MME::Drawer::CutScene::destroy();
}

Manager::Manager()
	:mCurrentEffect(NULL),
	mPool(NULL),
	mVertexNumber(0),
	mVertexBlendEnable(false),
	mTempBackbuffer(0),
	mTempBackZ(0),
	mShadowTexture(0),	
	mShadowTexSurface(0),
	mShadowTexZ(0),
	mGaussianEffect(0),
	mFxaaEffect(0),
	mEdgeColor( 0.f, 0.f, 0.f, 1.f )
{
	if( skGaussianFxFileName ){
		mGaussianFxFile = GameLib::FileIO::InFile::create( skGaussianFxFileName );
	}

	assert( skDefalutFxFileName );
	mDefalutFxFile = GameLib::FileIO::InFile::create( skDefalutFxFileName );

	if( skDefalutPostFxFileName ){
		mDefalutPostFxFile = GameLib::FileIO::InFile::create( skDefalutPostFxFileName );
	}

	if( skFXAAFileName ){
		mFxaaFxFile = GameLib::FileIO::InFile::create( skFXAAFileName );
	}
	
	if( skPointLightFxFileName ){
		mPointLightFxFile  = GameLib::FileIO::InFile::create( skPointLightFxFileName );
	}

	HRESULT hr;
	//エフェクト間で共有するパラメータのプールを作成
	hr=D3DXCreateEffectPool( &mPool );
	assert( SUCCEEDED(hr) );

	GameLib::Graphics::Manager m;
	m.setRecoverFunc( ::recover );
	m.setBackupFunc( ::backup );
	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();
	int w = static_cast<int>( static_cast<float>(m.width())*skShadowTexSizeRate );
	int h = static_cast<int>( static_cast<float>(m.height())*skShadowTexSizeRate );
	
	// シャドウマップとして使用するテクスチャの作成
	hr = pDevice->CreateTexture(
		w, h,			
		1,	
		D3DUSAGE_RENDERTARGET,
		skShadowFMT,
		D3DPOOL_DEFAULT,
		&mShadowTexture,
		NULL);
	assert( SUCCEEDED(hr) );
	D3DSURFACE_DESC desc;
	mShadowTexture->GetLevelDesc( 0, &desc );
	assert( desc.Height==h );
	assert( desc.Width==w );

	// テクスチャからレンダリングターゲットにするサーフェースの取得
	hr=mShadowTexture->GetSurfaceLevel(0, &mShadowTexSurface);
	assert( SUCCEEDED(hr) );

	// テクスチャへのレンダリングに使う深度バッファーの作成
	hr=pDevice->CreateDepthStencilSurface(
		w, h,		
		D3DFMT_D24X8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&mShadowTexZ,
		NULL);
	assert( SUCCEEDED(hr) );

	//真っ白テクスチャ準備
	mShadowDummyTexture = GameLib::Graphics::Texture::create( 1, 1, false );
	unsigned* textureData;
	int pitch;
	mShadowDummyTexture.lock( &textureData, &pitch, 0 );
	*textureData = 0xffffffff;
	mShadowDummyTexture.unlock( &textureData );
	textureData = 0;

	pDevice->SetTexture( 0, mShadowTexture);	
}

Manager::~Manager(){
	SAFE_RELEASE(mPool);
	SAFE_RELEASE(mShadowTexSurface);
	SAFE_RELEASE(mShadowTexture);
	SAFE_RELEASE(mShadowTexZ);
};


StandardEffectSharedPtr Manager::registStandardEffect( const char *fxFileName, GameLib::FileIO::InFile file )
{
	StandardMap::iterator it = mStandards.find( fxFileName );
	if( it==mStandards.end() ){
		StandardEffectSharedPtr se = std::make_shared<StandardEffect>( fxFileName, file, mPool );
		assert( !se->isError() );
		if( se->isError() ){
			return nullptr;
		}
		StandardMap::_Pairib ib = mStandards.insert( std::make_pair( se->getName(), se ) );
		it=ib.first;
	}
	return it->second;;

}

//void Manager::addToStandardEfffect(  const Object::IObjectSharedPtr &obj, const char *fxFileName ){
//	if(fxFileName==NULL){
//		fxFileName = skDefalutFxFileName;
//	}
//
//	StandardMap::iterator it = mStandards.find( fxFileName );
//	if( it==mStandards.end() ){
//		assert(false && "file not found" );
//	} else {
//		it->second->add( obj );
//	}
//}


PostEffectSharedPtr Manager::registPostEffect( const char *fxFileName, GameLib::FileIO::InFile file ){
	PostMap::iterator it = mPosts.find( fxFileName );
	if( it==mPosts.end() ){
		PostEffectSharedPtr pe = std::make_shared<PostEffect>(fxFileName, file, mPool);
		assert( !pe->isError() );
		if( pe->isError() ){
			return nullptr;
		}
		PostMap::_Pairib ib = mPosts.insert( std::make_pair( pe->getName(), pe ) );
		it=ib.first;
	}
	return it->second;;
}

//void Manager::addToPostEffectEfffect( const Object::IObjectSharedPtr &obj, const char *fxFileName ){
//	PostMap::iterator it = mPosts.find( fxFileName );
//	if( it==mPosts.end() ){
//		assert(false && "file not found ");
//	} else {
//		it->second->add( obj );
//	}
//
//}



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
void Manager::drawAll()
{
	bool isGraphicsHigh=true;
	GameLib::Graphics::Manager m;
	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();

	using namespace GameLib::Graphics;
	m.setBlendMode( BLEND_LINEAR );
	//mmdは左手座標
	m.setCullMode( CULL_FRONT );
	m.enableDepthTest( true );
	m.enableDepthWrite( true );

	m.enableMME(true);


	//for(
	//	StandardMap::iterator
	//	it=mStandards.begin(),
	//	end=mStandards.end();
	//	it!=end;
	//	++it )
	//{
	//	it->second->removeRemovableObjects();
	//}

	//for(
	//	PostMap::iterator
	//	it=mPosts.begin(),
	//	end=mPosts.end();
	//	it!=end;
	//	++it )
	//{
	//	it->second->removeRemovableObjects();
	//}

	//boost::timer t;

	if(isGraphicsHigh){ drawZPlot(skEnableFileter); }

	//TRACE1( "zplot end!  %f sec\n", t.elapsed() );
	//t.restart();

	for(
		StandardMap::iterator
		it=mStandards.begin(),
		end=mStandards.end();
		it!=end;
		++it )
	{
		//boost::timer t;
		//t.restart();
		//TRACE1( "%s start!\n", it->first.c_str() );

		it->second->drawOffScreen();

		//TRACE2( "%s end!  %f sec\n", it->first.c_str(), t.elapsed() );
	}
	
	if(mFxaaEffect) mFxaaEffect->preDraw();
	preExe();

	//for(
	//	StandardMap::iterator
	//	it=mStandards.begin(),
	//	end=mStandards.end();
	//	it!=end;
	//	++it )
	//{
	//	MME::StandardEffect* effect = it->second.get();
	//	effect->drawZPrePass();
	//}

	for(
		StandardMap::iterator
		it=mStandards.begin(),
		end=mStandards.end();
		it!=end;
		++it )
	{
		MME::StandardEffect* effect = it->second.get();
		//selfshadow
		if(isGraphicsHigh){
			effect->drawObjectSS();
		} else {
			effect->drawObject();		
		}
	}
	
	//エッジが１ピクセル以下であったりすると、FXAAでノイズのようになってしまう
	for(
		StandardMap::iterator
		it=mStandards.begin(),
		end=mStandards.end();
		it!=end;
		++it )
	{
		MME::StandardEffect* effect = it->second.get();
		effect->drawEdge();		
	}
		
	postExe();

	if(mFxaaEffect) mFxaaEffect->postDraw();

	m.dxDevice()->SetRenderTarget( 1, NULL );
	m.dxDevice()->SetRenderTarget( 2, NULL );
	m.dxDevice()->SetRenderTarget( 3, NULL );

	mCurrentEffect=0;
	
	//後始末　強制的にVertexBlendを無効にしておく
	//困るのはGameLib::Graphics::ManagerのVertexBlendEnableが無効なのに、有効な値が入っている場合なので
	//GameLib::Graphics::ManagerのVertexBlendEnableが有効の場合はすぐに正しい値を代入するはずなので問題なし
	//GameLib::Graphics::ManagerのVertexBlendEnableが無効でここのVertexBlendEnableも無効ならば問題なし
	m.enableMME(false);
	m.enableVertexBlend(true);
	m.enableVertexBlend(false);

	drawShadowMapBuffer();

	//drawOffScreen( "ShaderTest/AutoLuminous4/AutoLuminous.fx", "AL_EmitterRT" );
	//drawOffScreen( "ShaderTest/AutoLuminous4/AutoLuminousBasic.fx", "ALB_EmitterRT" );

	sendParamsToGameLibGraphicsManager();

}

void Manager::preExe(){
	for(
		PostMap::reverse_iterator
			it=mPosts.rbegin(),
			end=mPosts.rend();
		it!=end;
		++it )
	{
		it->second->preDraw();
	}
}

void Manager::postExe(){
	for(
		PostMap::iterator
			it=mPosts.begin(),
			end=mPosts.end();
		it!=end;
		++it )
	{
		it->second->postDraw();
	}
}

void Manager::sendParamsIfIsChanged(){
	if( mLightCameras.mIsChanged ){
		mCurrentEffect->sendLightMatrices(
			mLightCameras.mWorld[0],
			mLightCameras.mView[0],
			mLightCameras.mProjection[0] );
		mCurrentEffect->setLightPosition( mLightCameras.mPosition[0] );
		mCurrentEffect->setLightDirection( mLightCameras.mDirection[0] );
		mLightCameras.mIsChanged = false;
	}

	if( mLightMaterials.mIsChanged ){
		mCurrentEffect->setLightDiffuse( mLightMaterials.mDiffuse[0] );
		mCurrentEffect->setLightAmbient( mLightMaterials.mAmbient[0] );
		mCurrentEffect->setLightSpecular( mLightMaterials.mSpecular[0] );
		mLightMaterials.mIsChanged = false;
	}

	if( mCamera.mIsChanged ){
		mCurrentEffect->sendMatrices(
			mCamera.mWorld,
			mCamera.mView,
			mCamera.mProjection );
		mCurrentEffect->setEyePosition( mCamera.mPosition );
		mCurrentEffect->setEyeDirection( mCamera.mDirection );
		mCurrentEffect->setZNear( mCamera.mZNear );
		mCurrentEffect->setZFar( mCamera.mZFar );
		mCamera.mIsChanged = false;
	}

	if( mMaterial.mIsChanged ){
		mCurrentEffect->setDiffuseColor( mMaterial.mDiffuse );
		mCurrentEffect->setAmbientColor( mMaterial.mAmbient );
		mCurrentEffect->setSpecularColor( mMaterial.mSpecular );
		mCurrentEffect->setEmissionColor( mMaterial.mEmission );
		mCurrentEffect->setSpecularSharpness( mMaterial.mSharpness );
		mCurrentEffect->setToonColor( mMaterial.mToonColor );
		mMaterial.mIsChanged = false;
	}
	float t= static_cast<float>(timeGetTime()) * 0.001f;
	//TRACE1( "time %f\n", t );
	mCurrentEffect->setTime( t );
}

void Manager::sendParams( BaseEffect* e ){
	e->sendLightMatrices(
		mLightCameras.mWorld[0],
		mLightCameras.mView[0],
		mLightCameras.mProjection[0] );
	e->setLightPosition( mLightCameras.mPosition[0] );
	e->setLightDirection( mLightCameras.mDirection[0] );
	mLightCameras.mIsChanged = false;

	e->setLightDiffuse( mLightMaterials.mDiffuse[0] );
	e->setLightAmbient( mLightMaterials.mAmbient[0] );
	e->setLightSpecular( mLightMaterials.mSpecular[0] );
	mLightMaterials.mIsChanged = false;

	e->sendMatrices(
		mCamera.mWorld,
		mCamera.mView,
		mCamera.mProjection );
	e->setEyePosition( mCamera.mPosition );
	e->setEyeDirection( mCamera.mDirection );
	e->setZNear( mCamera.mZNear );
	e->setZFar( mCamera.mZFar );
	mCamera.mIsChanged = false;

	e->setDiffuseColor( mMaterial.mDiffuse );
	e->setAmbientColor( mMaterial.mAmbient );
	e->setSpecularColor( mMaterial.mSpecular );
	e->setEmissionColor( mMaterial.mEmission );
	e->setSpecularSharpness( mMaterial.mSharpness );
	mMaterial.mIsChanged = false;

	D3DXMATRIX matIdentity[1];
	D3DXMatrixIdentity( &matIdentity[0] );
	e->sendWorldMatrixArray( &matIdentity[0], 1 );
	GameLib::Graphics::Manager m;
	m.setAnimatedVertexBoneBuffer( 0 );

	float t= static_cast<float>(timeGetTime()) * 0.001f;
	//TRACE1( "time %f\n", t );
	e->setTime( t );

	e->setElapsedTime( 1.f/60.f );

	e->setEdgeColor( mEdgeColor );

	mVertexBlendEnable=false;
}

///設定したテクスチャ、頂点バッファ、インデクスバッファで描画
void Manager::drawIndexed(
	int offset, 
	int primitiveNumber )
{
	sendParamsIfIsChanged();

	GameLib::Graphics::Manager m;
	IDirect3DDevice9 *pDevice = m.dxDevice();
	HRESULT hr;
	mCurrentEffect->commitChanges();
	hr = pDevice->DrawIndexedPrimitive( 
		D3DPT_TRIANGLELIST,
		0,
		0,
		mVertexNumber,
		offset,
		primitiveNumber );
	assert( SUCCEEDED( hr ) && "DrawPrimitive : INVALID CALL" );
}
///設定したテクスチャ、頂点バッファで描画
void Manager::draw( 
	int offset, 
	int primitiveNumber )
{
	sendParamsIfIsChanged();
	GameLib::Graphics::Manager m;
	IDirect3DDevice9 *pDevice = m.dxDevice();
	HRESULT hr;
	mCurrentEffect->commitChanges();
	
	hr = pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, offset, primitiveNumber );
	assert( SUCCEEDED( hr ) && "DrawPrimitive : INVALID CALL" );
}

void Manager::setVertexBuffer( GameLib::Graphics::VertexBuffer vb ){
	GameLib::Graphics::Manager m;
	m.setVertexBuffer( vb );
	mVertexNumber = vb.vertexNumber();
}

void Manager::setIndexBuffer( GameLib::Graphics::IndexBuffer ib ){
	GameLib::Graphics::Manager m;
	m.setIndexBuffer( ib );
}
void Manager::setAnimatedVertexBoneBuffer( GameLib::Graphics::AnimatedVertexBoneBuffer avb ){
	GameLib::Graphics::Manager m;
	m.setAnimatedVertexBoneBuffer( avb );
}

void Manager::setTexture( GameLib::Graphics::Texture tex ){
	mCurrentEffect->setTexture( tex );
}

//ビュー変換行列セット
void Manager::setViewMatrix( const D3DXMATRIX& m ){
	mCamera.setViewMatrix(  m );
}
//透視変換行列セット
void Manager::setProjectionMatrix( const D3DXMATRIX& m ){
	mCamera.setProjectionMatrix( m );
}
//ワールド変換行列セット
void Manager::setWorldMatrix( const D3DXMATRIX& m ){
	mCamera.setWorldMatrix( m );
}

void Manager::setZNear( float zn){
	mCamera.setZNear(zn);
}
void Manager::setZFar( float zf){
	mCamera.setZFar(zf);

}


//ビュー変換行列ゲット
const D3DXMATRIX& Manager::getViewMatrix()const{
	return mCamera.mView;
}
//透視変換行列ゲット
const D3DXMATRIX& Manager::getProjectionMatrix()const{
	return mCamera.mProjection;
}
//ワールド変換行列ゲット
const D3DXMATRIX& Manager::getWorldMatrix()const{
	return mCamera.mWorld;
}

//視点位置
void Manager::setEyePosition( const GameLib::Math::Vector3& position ){
	mCamera.setPosition( Vector4( position.x, position.y, position.z, 1.f ) );
}
void Manager::setEyeDirection( const GameLib::Math::Vector3& dir ){
	mCamera.setDirection( Vector4( dir.x, dir.y, dir.z, 0.f ) );
}
//ライト位置
void Manager::setLightPosition( int index, const Vector3& position ){
	mLightCameras.setPosition( index, Vector4( position.x, position.y, position.z, 1.f ) );
}
///ライト向き
void Manager::setLightDirection( int index, const Vector3& dir ){
	mLightCameras.setDirection( index, Vector4( dir.x, dir.y, dir.z, 0.f ) );
}
//ライト強度(100なら100mの距離で1の明るさになる。強度Iとして、明るさは「I/距離」で決まる)
//ライト向きに対して正規化して書けるだけの予定
//void Manager::setLightIntensity( int index, float intensity );

/////ライト色
void Manager::setLightColor( int index, const Vector4& c ){
	mLightMaterials.setAmbient( index, c );
	mLightMaterials.setDiffuse( index, c );
	mLightMaterials.setSpecular( index, c );
}

void Manager::setLightDiffuse( int index, const GameLib::Math::Vector4 &d ){
	mLightMaterials.setDiffuse( index , d );
}
void Manager::setLightAmbient( int index, const GameLib::Math::Vector4 &a ){
	mLightMaterials.setAmbient( index , a );

}
void Manager::setLightSpecular( int index, const GameLib::Math::Vector4 &s ){
	mLightMaterials.setSpecular( index , s );
}


//ディフューズカラー
void Manager::setDiffuseColor( const Vector4& d){
	mMaterial.setDiffuse( d );
}
//スペキュラ色
void Manager::setSpecularColor( const Vector4& sp){
	mMaterial.setSpecular( sp );
}
//発光色
void Manager::setEmissionColor( const Vector4& em ){
	mMaterial.setEmission( em );
}
//アンビエント色
void Manager::setAmbientColor( const Vector4& amb){
	mMaterial.setAmbient( amb );
}
//輪郭色
void Manager::setEdgeColor( const GameLib::Math::Vector4& edge ){
	mEdgeColor = edge;
}

//透明度設定
//void Manager::setTransparency( float t ){
//	mMaterial.setTransparency( t );
//}

void Manager::setToonColor( const GameLib::Math::Vector4 &toon ){
	mMaterial.setToonColor( toon );
}

//スペキュラの鋭さ(大きいほど鋭い。数字の意味は別の本を読もう)
void Manager::setSpecularSharpness( float ss){
	mMaterial.setSpecularSharpness( ss );
}

void Manager::sendWorldMatrixArray( const D3DXMATRIX *worldMatrices, int size ){
	mCurrentEffect->sendWorldMatrixArray( worldMatrices, size );
}

void Manager::enableVertexBlend( bool enable ){
	if( enable!=mVertexBlendEnable ){
		if( enable==false ){
			D3DXMATRIX matIdentity[1];
			D3DXMatrixIdentity( &matIdentity[0] );
			mCurrentEffect->sendWorldMatrixArray( &matIdentity[0], 1 );
			GameLib::Graphics::Manager m;
			m.setAnimatedVertexBoneBuffer( 0 );
		}
		mVertexBlendEnable=enable;
	}
}


	
void Manager::sendParamsToGameLibGraphicsManager(){
	//でふぉをるとと感じる値に近いのを送っておく
	bool depthWrite = true;
	bool depthTest = true;
	GameLib::Graphics::BlendMode blendMode = GameLib::Graphics::BLEND_LINEAR;
	GameLib::Graphics::CullMode cullMode = GameLib::Graphics::CULL_FRONT;
	GameLib::Graphics::Manager m;
	m.enableDepthWrite( depthWrite );
	m.enableDepthTest( depthTest );
	m.setBlendMode( blendMode );
	m.setCullMode( cullMode );
	m.setDiffuseColor( Vector3( 1.f, 1.f, 1.f ) );
	m.setLightingMode( GameLib::Graphics::LIGHTING_NONE );
	m.enableVertexBlend(false);
	
	m.setTexture(0);

	GameLib::Math::Matrix34 wm;
	wm.setIdentity();
	m.setWorldMatrix( wm );	
	//列ベクトル→行ベクトル掛け算順番注意
	m.setProjectionViewMatrix( toMatrix44( mCamera.mView * mCamera.mProjection  ) );
	m.setEyePosition( mCamera.mPosition );

	for( int i=0; i<4; ++i ){
		//m.setLightIntensity( i, mLightCameras.);
		m.setLightColor( i, mLightMaterials.mDiffuse[i] );
		m.setLightPosition( i, mLightCameras.mPosition[i] );
	}

}

//ライトビュー変換行列セット
void Manager::setLightViewMatrix( int index, const D3DXMATRIX& lightView ){
	mLightCameras.setViewMatrix( index, lightView );
}
///ライト透視変換行列セット
void Manager::setLightProjectionMatrix( int index, const D3DXMATRIX& lightProjection ){
	mLightCameras.setProjectionMatrix( index, lightProjection );
}
///ライトワールド変換行列セット
void Manager::setLightWorldMatrix( int index, const D3DXMATRIX& lightWorld ){
	mLightCameras.setWorldMatrix( index, lightWorld );
}

void Manager::drawShadowMapBuffer() const {

	
	bool depthWrite = true;
	bool depthTest = false;
	GameLib::Graphics::BlendMode blendMode = GameLib::Graphics::BLEND_OPAQUE;
	GameLib::Graphics::CullMode cullMode = GameLib::Graphics::CULL_NONE;
	GameLib::Graphics::Manager m;
	
	m.enableDepthWrite( depthWrite );
	m.enableDepthTest( depthTest );
	m.setBlendMode( blendMode );
	m.setCullMode( cullMode );
	m.setDiffuseColor( Vector3( 1.f, 1.f, 1.f ) );
	m.setLightingMode( GameLib::Graphics::LIGHTING_NONE );
	m.enableVertexBlend(false);
	
	int width, height;
	m.getViewport( 0, 0, &width, &height );
	
	//スクリーン座標->クリップ空間変換行列	
	Matrix44 screenToClipTransform;

	//バグ対策
	//effectファイルでレジスタを汚していて
	//すでに同じのが入っていると、GameLib::Graphics::Managerにはじかれ、
	//汚れたままのMatrixを使うことになってしまう(mMatricesChangedがfalseのまま)
	//全部送るとまたこの作業後、全部送るのは効率的ではないためここで部分的に送る
	//gameLibのMatrixはMMEと連動していないため
	//必ず正しい値が入るように2度入れする
	m.setProjectionViewMatrix( screenToClipTransform );
	Matrix34 wm;
	m.setWorldMatrix( wm );
	wm.setIdentity();
	m.setWorldMatrix( wm );

	screenToClipTransform.setOrthogonalTransform(
		0.f, static_cast< float >( width ), 
		static_cast< float >( height ), 0.f, //下、上の順で、下はheight,上は0であることに注意
		0.f, 1.f );
	
	m.setProjectionViewMatrix( screenToClipTransform );
	
	float rate=1.2f;
	Vector2 vDisplayRect0( static_cast< float >(width)/rate, static_cast< float >(height)/rate );
	Vector2 vDisplayRect1( static_cast< float >(width), static_cast< float >(height) );

	GameLib::Graphics::VertexBuffer vb = GameLib::Graphics::VertexBuffer::create( 6 );
	GameLib::Graphics::Vertex *v;
	v = vb.lock();
	v[0].mPosition.set(vDisplayRect0.x, vDisplayRect0.y, 0, 1.f);
	v[0].mUv.set( 0.f, 0.f );
	v[0].mColor = 0xffffffff;

	v[1].mPosition.set(vDisplayRect1.x, vDisplayRect0.y, 0, 1.f);
	v[1].mUv.set( 1.f, 0.f );
	v[1].mColor = 0xffffffff;

	v[2].mPosition.set(vDisplayRect1.x, vDisplayRect1.y, 0, 1.f);
	v[2].mUv.set( 1.f, 1.f );
	v[2].mColor = 0xffffffff;

	v[3].mPosition.set(vDisplayRect0.x, vDisplayRect0.y, 0, 1.f);
	v[3].mUv.set( 0.f, 0.f );
	v[3].mColor = 0xffffffff;

	v[4].mPosition.set(vDisplayRect0.x, vDisplayRect1.y, 0, 1.f);
	v[4].mUv.set( 0.f, 1.f );
	v[4].mColor = 0xffffffff;

	v[5].mPosition.set(vDisplayRect1.x, vDisplayRect1.y, 0, 1.f);
	v[5].mUv.set( 1.f, 1.f );
	v[5].mColor = 0xffffffff;
	
	vb.unlock( &v );

	
	//dummyを送る、送らないと真っ白にされるので
	m.setTexture( mShadowDummyTexture );
	m.dxDevice()->SetTexture( 1, mShadowTexture );
	m.setVertexBuffer( vb );
	m.draw( 0, 2 );
}

void Manager::drawOffScreen( const char* effectFileName, const char *offscreenName ) const {
	bool depthWrite = true;
	bool depthTest = false;
	GameLib::Graphics::BlendMode blendMode = GameLib::Graphics::BLEND_OPAQUE;
	GameLib::Graphics::CullMode cullMode = GameLib::Graphics::CULL_NONE;
	GameLib::Graphics::Manager m;
	
	m.enableDepthWrite( depthWrite );
	m.enableDepthTest( depthTest );
	m.setBlendMode( blendMode );
	m.setCullMode( cullMode );
	m.setDiffuseColor( Vector3( 1.f, 1.f, 1.f ) );
	m.setLightingMode( GameLib::Graphics::LIGHTING_NONE );
	m.enableVertexBlend(false);
	
	int width, height;
	m.getViewport( 0, 0, &width, &height );
	
	//スクリーン座標->クリップ空間変換行列	
	Matrix44 screenToClipTransform;

	//バグ対策
	//effectファイルでレジスタを汚していて
	//すでに同じのが入っていると、GameLib::Graphics::Managerにはじかれ、
	//汚れたままのMatrixを使うことになってしまう(mMatricesChangedがfalseのまま)
	//全部送るとまたこの作業後、全部送るのは効率的ではないためここで部分的に送る
	//gameLibのMatrixはMMEと連動していないため
	//必ず正しい値が入るように2度入れする
	m.setProjectionViewMatrix( screenToClipTransform );
	Matrix34 wm;
	m.setWorldMatrix( wm );
	wm.setIdentity();
	m.setWorldMatrix( wm );

	screenToClipTransform.setOrthogonalTransform(
		0.f, static_cast< float >( width ), 
		static_cast< float >( height ), 0.f, //下、上の順で、下はheight,上は0であることに注意
		0.f, 1.f );
	
	m.setProjectionViewMatrix( screenToClipTransform );
	
	float rate=1.5f;
	//float rate=1.2f;
	Vector2 vDisplayRect0( static_cast< float >(width)/rate, static_cast< float >(height)/rate );
	Vector2 vDisplayRect1( static_cast< float >(width), static_cast< float >(height) );

	GameLib::Graphics::VertexBuffer vb = GameLib::Graphics::VertexBuffer::create( 6 );
	GameLib::Graphics::Vertex *v;
	v = vb.lock();
	v[0].mPosition.set(vDisplayRect0.x, vDisplayRect0.y, 0, 1.f);
	v[0].mUv.set( 0.f, 0.f );
	v[0].mColor = 0xffffffff;

	v[1].mPosition.set(vDisplayRect1.x, vDisplayRect0.y, 0, 1.f);
	v[1].mUv.set( 1.f, 0.f );
	v[1].mColor = 0xffffffff;

	v[2].mPosition.set(vDisplayRect1.x, vDisplayRect1.y, 0, 1.f);
	v[2].mUv.set( 1.f, 1.f );
	v[2].mColor = 0xffffffff;

	v[3].mPosition.set(vDisplayRect0.x, vDisplayRect0.y, 0, 1.f);
	v[3].mUv.set( 0.f, 0.f );
	v[3].mColor = 0xffffffff;

	v[4].mPosition.set(vDisplayRect0.x, vDisplayRect1.y, 0, 1.f);
	v[4].mUv.set( 0.f, 1.f );
	v[4].mColor = 0xffffffff;

	v[5].mPosition.set(vDisplayRect1.x, vDisplayRect1.y, 0, 1.f);
	v[5].mUv.set( 1.f, 1.f );
	v[5].mColor = 0xffffffff;
	
	vb.unlock( &v );

	PostMap::const_iterator it = mPosts.find( effectFileName );
	assert( it!=mPosts.cend() );

	OffScreenRenderSharedPtr ofsc = it->second->findOffScreen( offscreenName );
	assert(ofsc);

	//dummyを送る、送らないと真っ白にされるので
	m.setTexture( mShadowDummyTexture );
	m.dxDevice()->SetTexture( 1, ofsc->getDxTexture() );
	m.setVertexBuffer( vb );
	m.draw( 0, 2 );
}

void Manager::setToonTexture( GameLib::Graphics::Texture toonTexture ){
	mCurrentEffect->setToonTexture( toonTexture );
}

void Manager::setSphereTexture(  GameLib::Graphics::Texture sphereTexture ){
	mCurrentEffect->setSphereTexture( sphereTexture );
}

void Manager::setSphereTextureAdditive(  bool isAdditive ){
	mCurrentEffect->setSphereTextureAdditive( isAdditive );
}

bool Manager::canDraw(
	UseTexture useTexture,
	UseSphereMap useSphereMap,
	UseToon useToon,
	unsigned int materialIndex )const
{
	return
		mCurrentEffect->canDraw( useTexture, useSphereMap, useToon, materialIndex );
}

//void Manager::matchByModelFileName( std::vector<Object::IObjectSharedPtr> *out, const boost::xpressive::sregex & filename  )const
//{
//	for(
//		StandardMap::const_iterator
//		it=mStandards.cbegin(),
//			end=mStandards.cend();
//		it!=end;
//		++it )
//	{
//		it->second->matchByModelFileName( out, filename );
//	}
//	out->shrink_to_fit();
//}

void Manager::drawZPlot( bool enableFilter ){
	HRESULT hr;
	GameLib::Graphics::Manager m;
	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();

	// ビューポート情報の保持
	D3DVIEWPORT9 viewport1;
	pDevice->GetViewport(&viewport1);

	// バックバッファーへのインターフェースの保持
	pDevice->GetRenderTarget(0, &mTempBackbuffer);

	// 深度バッファーのインターフェースの保持
    pDevice->GetDepthStencilSurface( &mTempBackZ); 

	// テクスチャをレンダリングターゲットに設定
	pDevice->SetRenderTarget(0, mShadowTexSurface);

	// テクスチャ用の深度バッファを設定
	pDevice->SetDepthStencilSurface(mShadowTexZ);

	// レンダリングターゲットを初期化
	hr=pDevice->Clear(0,NULL, 
		D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f, 0);
	assert( SUCCEEDED(hr) );

	// ビューポートをテクスチャ画像のサイズに設定
	D3DSURFACE_DESC desc;
	mShadowTexture->GetLevelDesc( 0, &desc );
	D3DVIEWPORT9 viewport2 = { 0, 0, desc.Width, desc.Height, 0.0f, 1.0f };
	pDevice->SetViewport(&viewport2);

	if( enableFilter ) mGaussianEffect->preDraw();

	//zplot
	for(
		StandardMap::iterator
			it=mStandards.begin(),
			end=mStandards.end();
		it!=end;
		++it )
	{
		//boost::timer t;
		//t.restart();
		//TRACE1( "%s start!\n", it->first.c_str() );

		it->second->drawZPlot();
		//TRACE2( "%s end!  %f sec\n", it->first.c_str(), t.elapsed() );
	}

	if( enableFilter )  mGaussianEffect->postDraw();


	// 保存しておいたバックバッファをレンダリングターゲットに設定
	pDevice->SetRenderTarget(0, mTempBackbuffer);

	// 保存しておいたバックバッファの深度バッファを設定
	pDevice->SetDepthStencilSurface(mTempBackZ);

	// 保存しておいたビューポートを元に戻す
	pDevice->SetViewport(&viewport1);

	// シャドウバッファのサンプラ。"register(s0)"なのはMMDがs0を使っているから
	//これ重い
	//pDevice->SetTexture( 0, mShadowTexture);
	
	SAFE_RELEASE( mTempBackbuffer );
	SAFE_RELEASE( mTempBackZ );
	
}

MMDPass Manager::getCurrentPass()const{
	return mCurrentEffect->getCurrentPass();
}

void Manager::getCurrentPass(
		MMDPass *pass,
		UseTexture *useTexture,
		UseSphereMap *useSphereMap,
		UseToon *useToon,
		UseSelfShadow *useSelfShadow )const
{
	mCurrentEffect->getCurrentPass(
		pass,
		useTexture,
		useSphereMap,
		useToon,
		useSelfShadow );
}

void Manager::setCurrentEffect( BaseEffect *effect ){
	assert( mCurrentEffect==0 || (mCurrentEffect!=0 && effect==0) );
	mCurrentEffect = effect;
}

StandardEffectSharedPtr Manager::findStandardEffect( const std::string &fullFileName ){
	StandardMap::iterator it = mStandards.find( fullFileName );
	if( it==mStandards.end() ){
		return nullptr;
	}
	else {
		return it->second;
	}
}

PostEffectSharedPtr Manager::findPostEffect( const std::string &fullFileName ){
	PostMap::iterator it = mPosts.find( fullFileName );
	if( it==mPosts.end() ){
		return nullptr;
	}
	else {
		return it->second;
	}
}

StandardEffectSharedPtr Manager::findStandardEffect( const std::string &effectFileName, const std::string &offScreenName, const std::string &effectFileNameInOffScreen ){
	MME::BaseEffectSharedPtr ptr =  findPostEffect( effectFileName );
	if( !ptr ){
		ptr = findStandardEffect( effectFileName );
	}

	if( !ptr ){
		assert(false);
		return nullptr;
	}

	OffScreenRenderSharedPtr os = ptr->findOffScreen( offScreenName );
	if( os==NULL ){
		assert(false);
		return nullptr;
	}

	StandardEffectSharedPtr effectInOffScreen = os->findStandardEffect( effectFileNameInOffScreen );
	if( !effectInOffScreen ){
		assert(false);
		return nullptr;
	}
	return effectInOffScreen;

}

GameLib::Math::Vector3 Manager::getLightDirection( int index ) const{
	return mLightCameras.mDirection[index];
}

void Manager::backup(){
	if( mGaussianEffect ){
		mGaussianEffect->backup();
		mGaussianEffect->setTextures();
	}
	GameLib::Graphics::Manager m;
	//HRESULT hr;

	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();

	//hr=pDevice->SetTexture( 0, 0 );
	//assert( SUCCEEDED(hr) );

	//SAFE_RELEASE(mTempBackbuffer);
    //SAFE_RELEASE(mTempBackZ);


	SAFE_RELEASE(mShadowTexSurface);
	SAFE_RELEASE(mShadowTexture);
	SAFE_RELEASE(mShadowTexZ);

	for(
		PostMap::iterator
			it=mPosts.begin(),
			end=mPosts.end();
		it!=end;
		++it )
	{
		it->second->backup();
	}

	for(
		StandardMap::iterator
		it=mStandards.begin(),
		end=mStandards.end();
	it!=end;
	++it )
	{
		it->second->backup();
	}

}
void Manager::recover(){
	if( mGaussianEffect ){
		mGaussianEffect->recover();
	}
	GameLib::Graphics::Manager m;

	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();
	int w = static_cast<int>( static_cast<float>(m.width())*skShadowTexSizeRate );
	int h = static_cast<int>( static_cast<float>(m.height())*skShadowTexSizeRate );
	
	HRESULT hr;
	// シャドウマップとして使用するテクスチャの作成
	hr = pDevice->CreateTexture(
		w, h,			
		1,	
		D3DUSAGE_RENDERTARGET,
		skShadowFMT,
		D3DPOOL_DEFAULT,
		&mShadowTexture,
		NULL);
	assert( SUCCEEDED(hr) );
	D3DSURFACE_DESC desc;
	mShadowTexture->GetLevelDesc( 0, &desc );
	assert( desc.Height==h );
	assert( desc.Width==w );


	// テクスチャからレンダリングターゲットにするサーフェースの取得
	hr=mShadowTexture->GetSurfaceLevel(0, &mShadowTexSurface);
	assert( SUCCEEDED(hr) );

	// テクスチャへのレンダリングに使う深度バッファーの作成
	hr=pDevice->CreateDepthStencilSurface(
		w, h,		
		D3DFMT_D24X8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&mShadowTexZ,
		NULL);
	assert( SUCCEEDED(hr) );
	
	pDevice->SetTexture( 0, mShadowTexture);


	for(
		PostMap::iterator
			it=mPosts.begin(),
			end=mPosts.end();
		it!=end;
		++it )
	{
		it->second->recover();
	}

	for(
		StandardMap::iterator
		it=mStandards.begin(),
		end=mStandards.end();
	it!=end;
	++it )
	{
		it->second->recover();
	}
}

void Manager::loadDefalutEffect(){
	GameLib::Graphics::Manager m;
	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();
	
	assert( mGaussianEffect==NULL );

	if( mGaussianFxFile ){
		mGaussianEffect = std::make_shared<PostEffect>( skGaussianFxFileName, mGaussianFxFile, mPool );
		mGaussianFxFile.release();
	}

	assert( mFxaaEffect == NULL );
	if(skFXAAFileName){
		mFxaaEffect = std::make_shared<PostEffect>(skFXAAFileName, mFxaaFxFile, mPool );
		mFxaaFxFile.release();
	}

	if(skPointLightFxFileName){
		registPostEffect(skPointLightFxFileName, mPointLightFxFile );
		mPointLightFxFile.release();
	}

	if(skDefalutPostFxFileName){		
		registPostEffect(skDefalutPostFxFileName, mDefalutPostFxFile);
		mDefalutPostFxFile.release();
	}
	
	

	registStandardEffect( skDefalutFxFileName, mDefalutFxFile );
	mDefalutFxFile.release();
}

bool Manager::isReady(){
	if( !mDefalutFxFile &&
		!mDefalutPostFxFile &&
		!mGaussianFxFile &&
		!mFxaaFxFile &&
		!mPointLightFxFile )
	{
		return true;
	}

	bool isFinished = mDefalutFxFile.isFinished();
	isFinished = isFinished && ( mDefalutPostFxFile ? mDefalutFxFile.isFinished() : true );
	isFinished = isFinished && ( mGaussianFxFile ? mGaussianFxFile.isFinished() : true );
	isFinished = isFinished && ( mFxaaFxFile ? mFxaaFxFile.isFinished() : true );
	isFinished = isFinished && ( mPointLightFxFile ? mPointLightFxFile.isFinished() : true );

	if( isFinished ){
		loadDefalutEffect();
		return true;
	} else {
		return false;
	}
}

void Manager::beginShadow(){
	HRESULT hr;
	GameLib::Graphics::Manager m;
	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();

	// ビューポート情報の保持
	pDevice->GetViewport(&mTempViewport);

	// バックバッファーへのインターフェースの保持
	pDevice->GetRenderTarget(0, &mTempBackbuffer);

	// 深度バッファーのインターフェースの保持
    pDevice->GetDepthStencilSurface( &mTempBackZ); 

	// テクスチャをレンダリングターゲットに設定
	pDevice->SetRenderTarget(0, mShadowTexSurface);

	// テクスチャ用の深度バッファを設定
	pDevice->SetDepthStencilSurface(mShadowTexZ);

	// レンダリングターゲットを初期化
	hr=pDevice->Clear(0,NULL, 
		D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f, 0);
	assert( SUCCEEDED(hr) );

	// ビューポートをテクスチャ画像のサイズに設定
	D3DSURFACE_DESC desc;
	mShadowTexture->GetLevelDesc( 0, &desc );
	D3DVIEWPORT9 viewport2 = { 0, 0, desc.Width, desc.Height, 0.0f, 1.0f };
	pDevice->SetViewport(&viewport2);
}

void Manager::endShadow(){
	
	GameLib::Graphics::Manager m;
	LPDIRECT3DDEVICE9 pDevice = m.dxDevice();

	// 保存しておいたバックバッファをレンダリングターゲットに設定
	pDevice->SetRenderTarget(0, mTempBackbuffer);

	// 保存しておいたバックバッファの深度バッファを設定
	pDevice->SetDepthStencilSurface(mTempBackZ);

	// 保存しておいたビューポートを元に戻す
	pDevice->SetViewport(&mTempViewport);

	// シャドウバッファのサンプラ。"register(s0)"なのはMMDがs0を使っているから
	//これ重い
	//pDevice->SetTexture( 0, mShadowTexture);
	
	SAFE_RELEASE( mTempBackbuffer );
	SAFE_RELEASE( mTempBackZ );
}


//void Manager::clearAllObjects(){
//	for(
//		StandardMap::const_iterator
//		it=mStandards.cbegin(),
//			end=mStandards.cend();
//		it!=end;
//		++it )
//	{
//		it->second->clearAllObjects();
//	}
//
//	for(
//		PostMap::reverse_iterator
//			it=mPosts.rbegin(),
//			end=mPosts.rend();
//		it!=end;
//		++it )
//	{
//		it->second->clearAllObjectsInOffScreen();
//	}
//}



}//end namespace MME