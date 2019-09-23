#pragma once
#include<d3dx9.h>
#include"helper/MyOutputDebugString.h"
#include<vector>
#include<list>
#include"Enums.h"
#include<GameLib/Graphics/Texture.h>
#include<GameLib/Math/Vector4.h>
#include<memory>
#include<string>
#include<boost/unordered/unordered_map_fwd.hpp>
#include<boost/xpressive/xpressive_fwd.hpp>
#include"Object/IObject.h"
#include<GameLib/FileIO/InFile.h>


namespace MME {
	class Texture;
	typedef std::shared_ptr<Texture> TextureSharedPtr;
	class RenderTarget; 
	typedef std::shared_ptr<RenderTarget> RenderTargetSharedPtr;
	class RenderDepthStencil;
	typedef std::shared_ptr<RenderDepthStencil> RenderDepthStencilSharedPtr;

	class Technique;
	class Manager;
	class BaseTechnique;
	class StandardTechnique;
	class OffScreenRender;
	typedef std::shared_ptr<OffScreenRender> OffScreenRenderSharedPtr;
	class ControlObjectSelf;
	class BaseEffect;
typedef std::shared_ptr<BaseEffect> BaseEffectSharedPtr;
class BaseEffect {
public:
	enum ScriptOrder {
		SO_STANDARD=0,
		SO_POST_PROCESS=1,

	};

	BaseEffect( const std::string &fxFileName, GameLib::FileIO::InFile file, LPD3DXEFFECTPOOL pool );
	virtual ~BaseEffect();
	
	//name.empty()の場合NULLを返す
	RenderTargetSharedPtr findRenderTarget( const std::string &name );
	//name.empty()の場合NULLを返す
	RenderDepthStencilSharedPtr findRenderDepthStencil( const std::string &name );
	//name.empty()の場合NULLを返す
	OffScreenRenderSharedPtr findOffScreen(  const std::string &name );

	//RenderTargetがNULLだとデフォルトのバックバッファに戻す
	void setRenderTarget( int renderTargetIndex, RenderTarget *texture );
	//RenderTargetがNULLだとデフォルトのZBuffeに戻す
	void setRenderDepthStencil( RenderDepthStencil *rds );

	void clearRenderTarget( float r, float g, float b, float a );
	void clearRenderDepthStencil( float z );

	bool isError()const{
		return mIsError;
	}
	const std::string& getName()const{
		return mName;
	}

	void sendMatrices(
		const D3DXMATRIX &w,
		const D3DXMATRIX &v,
		const D3DXMATRIX &p );

	void sendLightMatrices(
		const D3DXMATRIX &w,
		const D3DXMATRIX &v,
		const D3DXMATRIX &p );


	void setTexture( GameLib::Graphics::Texture tex );
	///ライト位置
	void setLightPosition( const GameLib::Math::Vector4& position );
	///ライト向き
	void setLightDirection( const GameLib::Math::Vector4& dir );
	///ライト強度(100なら100mの距離で1の明るさになる。強度Iとして、明るさは「I/距離」で決まる)
	//ライト向きに対して正規化して書けるだけの予定
	//void setLightIntensity( int index, float intensity );
	///ライト色
	//void setLightColor( const GameLib::Math::Vector4& );
	void setLightDiffuse( const GameLib::Math::Vector4& );
	void setLightAmbient( const GameLib::Math::Vector4& );
	void setLightSpecular( const GameLib::Math::Vector4& );
	///視点位置
	void setEyePosition( const GameLib::Math::Vector4& position );
	void setEyeDirection( const GameLib::Math::Vector4& dir );
	///ディフューズカラー
	void setDiffuseColor( const GameLib::Math::Vector4& );
	///スペキュラ色
	void setSpecularColor( const GameLib::Math::Vector4& );
	///発光色
	void setEmissionColor( const GameLib::Math::Vector4& );
	///アンビエント色
	void setAmbientColor( const GameLib::Math::Vector4& );
	///透明度設定
	//vector4の4番目になっている
	//void setTransparency( float );
	///スペキュラの鋭さ
	void setSpecularSharpness( float );
	//toonColor
	void setToonColor( const GameLib::Math::Vector4& );
	void setToonTexture( GameLib::Graphics::Texture toonTexture );

	void sendWorldMatrixArray( const D3DXMATRIX *WorldMatrices, int size );
	
	
	//"TIME"は、0フレーム目からの再生時間を表す。
	//例えば、0フレーム目では、0.0（秒）となり、45フレーム目では1.5（秒）となる。
	//これ少ないフレーム数なら良いけど多くなるとfloat誤差で値が変わらなくなり
	//バグになる恐れが、
	//そもそもゲーム開始からの経過時間とかオーバーフローさせる前提でやるしか
	void setTime( float time );

	void setElapsedTime( float elapsedTime );

	void setEdgeColor( const GameLib::Math::Vector4& c );

	void setZNear( float znear );
	void setZFar( float zFar );

	//void enableVertexBlend( bool enable );

	//void setParams( Manager *mngr );

	void commitChanges();

	//レンダラーターゲットやさまざまなテクスチャをエフェクトにセット
	void setTextures();

	void setViewportPixelSize( float x, float y );

	void setSphereTexture( GameLib::Graphics::Texture toonTexture );
	void setSphereTextureAdditive( bool isAdditive );

	
	bool canDraw( UseTexture useTexture, UseSphereMap useSphereMap, UseToon useToon, unsigned int materialIndex ) const;
	MMDPass getCurrentPass()const{
		return mPass;
	}

	void getCurrentPass(
		MMDPass *pass,
		UseTexture *useTexture,
		UseSphereMap *useSphereMap,
		UseToon *useToon,
		UseSelfShadow *useSelfShadow )const
	{
		*pass = mPass;
		*useTexture = mUseTexture;
		*useSphereMap = mUseSphereMap;
		*useToon = mUseToon;
		*useSelfShadow = mUseSelfShadow;
	}

	void drawOffScreen();

	//MMDPass Object_SS と UseSelfShadow　を見分けるために使用
	bool isThereObject_SSInShader()const{
		return mIsThereObject_SSInShader;
	}
	//デバイスロスト時のための開放処理
	void backup();
	//デバイスロスト時のためのリソース再確保
	void recover();
	
	
	void releaseCurrentBackBuffers();

	bool enable()const{
		return mIsEnable;
	}
	//predrawとpostdrawとか描画中に呼ぶとレンダリングターゲットが
	//バグるので、その間は絶対に呼び出さないこと
	bool setEnable(bool e){
		return mIsEnable=e;
	}

	//void setFloat( const std::string &name, float value );
	//void setFloatArray( const std::string &name, const float *pValue, unsigned int count );
	//void setInt( const std::string &name, int value );
	//void setIntArray( const std::string &name, const int *pValue, unsigned int count );

	D3DXHANDLE getHandle(const std::string &name )const;

	void setFloat( D3DXHANDLE h, float value );
	void setFloatArray( D3DXHANDLE h, const float *pValue, unsigned int count );
	void setInt( D3DXHANDLE h, int value );
	void setIntArray( D3DXHANDLE h, const int *pValue, unsigned int count );


	//void add( const Object::IObjectSharedPtr& );
	
	//void removeObjectsAsPossible();
	//void removeObjectsThatCanRemove();
	//void removeRemovableObjects();

	void drawGeometry();

	//void matchByModelFileName( std::vector<Object::IObjectSharedPtr> *out, const boost::xpressive::sregex & filename  )const;

	//void clearAllObjects();


	//vectorにする利点　メモリ使わない、並びが追加順になる
	//listにする利点　削除挿入が早い、並びが追加順になる
	//setにする利点、削除挿入findがO(log n) 2重追加を許さない 並びがメモリ順になる
	//unordered_set 削除挿入findが早い(メモリさえあれば)、順番ばらばら
	typedef std::vector<Object::IObjectWeakPtr> DrawObjects;
	typedef std::shared_ptr< DrawObjects > DrawObjectsSharedPtr;
	void setObjectsPtr(const DrawObjectsSharedPtr &);
	
	unsigned int getNumberOfOffScreens()const;
	OffScreenRenderSharedPtr getOffScreenAt( unsigned int i);
protected:
	//disallow
	BaseEffect(const BaseEffect&);
	//disallow
	void operator=(const BaseEffect&);
	
	//スクリプトの空白を実装するために必要
	//空白に当たるRTを保存する
	//RenderColorTarget=(テクスチャ名 or 空白)
	//・RenderColorTarget0=(テクスチャ名 or 空白)
	//・RenderColorTarget1=(テクスチャ名 or 空白)
	//・RenderColorTarget2=(テクスチャ名 or 空白)
	//・RenderColorTarget3=(テクスチャ名 or 空白)
	//・RenderDepthStencilTarget=(テクスチャ名 or 空白)
	void saveCurrentBackBuffers();

	void setUseFlag()const;

	//void clearAllObjectsInOffScreen();

	const std::string mName;
	ID3DXEffect *mEffect;
	
	enum {
		kMatrixHandlesSize=24
	};
	//enum {
	//	kFloat4HandlesSize=13
	//}; 
	D3DXHANDLE mMatrixHandles[kMatrixHandlesSize];
	D3DXHANDLE mLightMatrixHandles[kMatrixHandlesSize];
	
	D3DXHANDLE mWorldMatixArrayHandle;
	//D3DXHANDLE mFloat4Handles[kFloat4HandlesSize];

	//float4 Handles
	//geometory
	D3DXHANDLE mDiffuse;      
	D3DXHANDLE mAmbient;      
	D3DXHANDLE mSpecular;      
	D3DXHANDLE mPosition;//camera
	D3DXHANDLE mDirection;//camera
	D3DXHANDLE mEdgeColor;
	D3DXHANDLE mEmissive;     
	D3DXHANDLE mToonColor;    
	//light
	D3DXHANDLE mLightDiffuse;      
	D3DXHANDLE mLightAmbient;      
	D3DXHANDLE mLightSpecular;      
	D3DXHANDLE mLightPosition;
	D3DXHANDLE mLightDirection;

	//float Handle
	D3DXHANDLE mSpecularPowerHandle;
	D3DXHANDLE mTimeHandle;
	D3DXHANDLE mElapsedTimeHandle;
	D3DXHANDLE mStandardGlobalHandle;
	
	//float2
	D3DXHANDLE mViewPortPixelSize;
	
	//etc
	//bool	 spadd;    // スフィアマップ加算合成フラグ
	D3DXHANDLE mSpAddHandle;
	//bool     parthf;   // パースペクティブフラグ
	D3DXHANDLE mParthfHandle;
	//bool     transp;   // 半透明フラグ
	D3DXHANDLE mTranspHandle;
	
	D3DXHANDLE mUseTextureHandle;
	D3DXHANDLE mUseSphereMapHandle;
	D3DXHANDLE mUseToonHandle;

	D3DXHANDLE mMaterialTextureHandle;
	D3DXHANDLE mSphereMapTextureHandle;
	D3DXHANDLE mToonTextureHandle;

	D3DXHANDLE mZNearHandle;
	D3DXHANDLE mZFarHandle;

	
	std::vector<TextureSharedPtr> mTextures;
	std::vector<RenderTargetSharedPtr> mRenderTargets;
	std::vector<RenderDepthStencilSharedPtr> mRenderDepthStencils;
	std::vector<OffScreenRenderSharedPtr> mOffScreenRenders;

	//key: 変数名、value:　変数へのハンドル
	//boost::unordered_map< std::string, D3DXHANDLE > *mVariables;

	ControlObjectSelf* mControlObjectSelf;

	enum{
		kNumBackBuffers=4,
	};
	LPDIRECT3DSURFACE9 mDefaultBackBuffer[kNumBackBuffers];
	LPDIRECT3DSURFACE9 mDefaultZBuffer;

	bool mIsError;

	ScriptOrder mScriptOrder;

	StandardTechnique *mCurrentTech;

	//現在の描画状態
	MMDPass mPass;
	UseTexture mUseTexture;
	UseSphereMap mUseSphereMap;
	UseToon mUseToon;
	UseSelfShadow mUseSelfShadow;

	//shader内でobject_ssを使っているか?
	//使っていた場合、MMDassがobjectでuseSelfShadowの指定がないものをuseSelfShadow=falseにする
	bool mIsThereObject_SSInShader;
	static GameLib::Graphics::Texture msWhiteTexture; 

	bool mIsEnable;

	
	DrawObjectsSharedPtr mObjects;

};

}//end namespace MME