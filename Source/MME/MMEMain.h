#pragma once
#include"Object/IObject.h"
#include<GameLib/Graphics/Texture.h>
#include<d3dx9.h>

#include<GameLib/Math/Vector3.h>

namespace MME{

	void regist( Object::IObjectSharedPtr obj, const char *fxFileName, const char *path=0 );
	void unregist( Object::IObjectSharedPtr obj );

	void registPostEffect(  const char *fxFileName, const char *path=0 );

	void preExe();
	void postExe();

	void drawAll();

	///設定したテクスチャ、頂点バッファ、インデクスバッファで描画
	void drawIndexed(
		int offset, 
		int primitiveNumber );
	///設定したテクスチャ、頂点バッファで描画
	void draw( 
		int offset, 
		int primitiveNumber );

	//void setVertexBuffer( VertexBuffer );
	//void setIndexBuffer( IndexBuffer );
	//void setAnimatedVertexBoneBuffer( AnimatedVertexBoneBuffer );
	void setTexture( GameLib::Graphics::Texture );

	//ビュー変換行列セット
	void setViewMatrix( const D3DXMATRIX& m );
	///透視変換行列セット
	void setProjectionMatrix( const D3DXMATRIX& m );
	///ワールド変換行列セット
	void setWorldMatrix( const D3DXMATRIX& m );

	using GameLib::Math::Vector3;
	///ライト位置
	void setLightPosition( int index, const Vector3& position );
	///ライト向き
	void setLightDirection( int index, const Vector3& dir );
	///ライト強度(100なら100mの距離で1の明るさになる。強度Iとして、明るさは「I/距離」で決まる)
	//ライト向きに対して正規化して書けるだけの予定
	//void setLightIntensity( int index, float intensity );
	///ライト色
	void setLightColor( int index, const Vector3& );
	///視点位置
	void setEyePosition( const Vector3& position );
	void setEyeDirection( const Vector3& dir );
	///ディフューズカラー
	void setDiffuseColor( const Vector3& );
	///スペキュラ色
	void setSpecularColor( const Vector3& );
	///発光色
	void setEmissionColor( const Vector3& );
	///アンビエント色
	void setAmbientColor( const Vector3& );
	///透明度設定
	void setTransparency( float );
	///スペキュラの鋭さ(大きいほど鋭い。数字の意味は別の本を読もう)
	void setSpecularSharpness( float );
	
	void sendParamsToGameLibGraphicsManager();
}