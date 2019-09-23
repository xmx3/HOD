#pragma once
#include<memory>
#include<d3dx9.h>
#include<map>
#include"Enums.h"
#include"StandardEffect.h"
#include"PostEffect.h"
#include<GameLib/Math/Vector3.h>
#include<GameLib/Math/Vector4.h>
#include<GameLib/Graphics/Texture.h>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/IndexBuffer.h>
#include<GameLib/Graphics/AnimatedVertexBoneBuffer.h>
#include<GameLib/FileIO/InFile.h>
#include<boost/xpressive/xpressive_fwd.hpp>
#include<cassert>

namespace MME {

class BaseEffect;

class Manager {
public:
	//ゲームオブジェクト毎にfxファイルを指定したほうが便利だろうと思ったが、
	//(同じ初音ミクモデルでも違うエフェクトとが適用できるから)
	//材質毎に指定できるようにしたほうが便利な場面もあるよねとおもったが
	//後でエフェクトファイルごとにまとめて描画するので、GameObjectを渡すのは必須。
	//死んだ場合(メモリ開放)をどうするか(weak_ptrか？)
	//描画順が名前順(priorityを作るべきか？ とりあえずは名前を工夫して描画順をコントロールしろ)
	StandardEffectSharedPtr registStandardEffect( const char *fxFileName, GameLib::FileIO::InFile file );

	//void addToStandardEfffect(  const Object::IObjectSharedPtr &obj, const char *fxFileName );

	//削除する場合は、drawAllの一番初めにobj->canRemove()で確かめて削除する。
	//removeを実装しなかったのはどのstandardEffectとoffscreenにobjがあるのかわからないので、
	//全部調べる必要がある。それは非効率だと感じたから
	// void remove( Object::IObjectSharedPtr &obj );	
	// void removet( Object::IObjectSharedPtr &obj, const char *fxFileName );
	
	//void registStandardEffect( const char *fxFileName );
	//void unregistStandardEffect(  const char *fxFileName );

	//ポストエフェクトマップに登録
	//なければ新たに作る
	//エラーが起きてたら0を返す
	//描画順が名前順(priorityを作るべきか？ とりあえずは名前を工夫して描画順をコントロールしろ)
	PostEffectSharedPtr registPostEffect( const char *fxFileName, GameLib::FileIO::InFile file );
	//void unregistPostEffect(  const char *fxFileName );

	//void addToPostEffectEfffect(  const Object::IObjectSharedPtr &obj, const char *fxFileName );

	bool isReady();

	void drawAll();

	void drawIndexed(
		int offset, 
		int primitiveNumber );
	
	void draw( 
		int offset, 
		int primitiveNumber );

	void setVertexBuffer( GameLib::Graphics::VertexBuffer );
	void setIndexBuffer( GameLib::Graphics::IndexBuffer );
	void setAnimatedVertexBoneBuffer( GameLib::Graphics::AnimatedVertexBoneBuffer );
	
	void setTexture( GameLib::Graphics::Texture );
	void setToonTexture(  GameLib::Graphics::Texture );
	void setSphereTexture(  GameLib::Graphics::Texture );
	void setSphereTextureAdditive( bool isAdditive );

	//ビュー変換行列セット
	void setViewMatrix( const D3DXMATRIX& view );
	///透視変換行列セット
	void setProjectionMatrix( const D3DXMATRIX& proj );
	///ワールド変換行列セット
	void setWorldMatrix( const D3DXMATRIX& world );

	//ビュー変換行列ゲット
	const D3DXMATRIX & Manager::getViewMatrix()const;
	//透視変換行列ゲット
	const D3DXMATRIX & Manager::getProjectionMatrix()const;
	//ワールド変換行列ゲット
	const D3DXMATRIX & Manager::getWorldMatrix()const;


	//ライトビュー変換行列セット
	void setLightViewMatrix( int index, const D3DXMATRIX& lightView );
	///ライト透視変換行列セット
	void setLightProjectionMatrix( int index, const D3DXMATRIX& lightProjection );
	///ライトワールド変換行列セット
	void setLightWorldMatrix( int index, const D3DXMATRIX& lightWorld );

	///ライト位置
	void setLightPosition( int index, const GameLib::Math::Vector3& position );
	///ライト向き
	void setLightDirection( int index, const GameLib::Math::Vector3& dir );
	///ライト強度(100なら100mの距離で1の明るさになる。強度Iとして、明るさは「I/距離」で決まる)
	//ライト向きに対して正規化して書けるだけの予定
	//void setLightIntensity( int index, float intensity );
	
	///ライト色
	//とりあえず全部(diffuse, ambient, specular)同じ値にする
	void setLightColor( int index, const GameLib::Math::Vector4& );
	void setLightDiffuse( int index, const GameLib::Math::Vector4 &d );
	void setLightAmbient( int index, const GameLib::Math::Vector4 &a );
	void setLightSpecular( int index, const GameLib::Math::Vector4 &s );

	///視点位置
	void setEyePosition( const GameLib::Math::Vector3& position );
	void setEyeDirection( const GameLib::Math::Vector3& dir );
	///ディフューズカラー
	void setDiffuseColor( const GameLib::Math::Vector4& );
	///スペキュラ色
	void setSpecularColor( const GameLib::Math::Vector4& );
	///発光色
	void setEmissionColor( const GameLib::Math::Vector4& );
	///アンビエント色
	void setAmbientColor( const GameLib::Math::Vector4& );
	///輪郭色
	void setEdgeColor( const GameLib::Math::Vector4& );

	void setZNear( float );
	void setZFar( float );

	///透明度設定(gameLibの互換性のために、作ったがいらないな。)
	//diffuse, specular, ambientのアルファ値にセットする
	//void setTransparency( float );

	void setToonColor( const GameLib::Math::Vector4& );


	///スペキュラの鋭さ(大きいほど鋭い
	void setSpecularSharpness( float );
	void sendWorldMatrixArray( const D3DXMATRIX *WorldMatrices, int size );
	void enableVertexBlend( bool enable );

	GameLib::Math::Vector3 getLightDirection( int index ) const;
	
	
	void sendParamsToGameLibGraphicsManager();

	bool canDraw(
		UseTexture useTexture,
		UseSphereMap useSphereMap,
		UseToon useToon,
		unsigned int materialIndex )const;
	
	MMDPass getCurrentPass()const;

	void getCurrentPass(
		MMDPass *pass,
		UseTexture *useTexture,
		UseSphereMap *useSphereMap,
		UseToon *useToon,
		UseSelfShadow *useSelfShadow )const;


	//void matchByModelFileName( std::vector<Object::IObjectSharedPtr> *out, const boost::xpressive::sregex & filename  )const;
	
	void setCurrentEffect( BaseEffect *effect );

	void sendParams( BaseEffect* mme  );

	//offscreen内は探さない
	//見つからない場合はnullptrを返す
	StandardEffectSharedPtr findStandardEffect( const std::string &fullFileName );
	//offscreen内は探さない
	//見つからない場合はnullptrを返す
	PostEffectSharedPtr findPostEffect( const std::string &fullFileName );

	//offscreenないも探す
	//見つからない場合はnullptrを返す
	StandardEffectSharedPtr findStandardEffect( const std::string &fullFileName, const std::string &offScreenName, const std::string &effectFileNameInOffScreen );

	//void clearAllObjects();

	//デバイスロスト時のための開放処理
	void backup();
	//デバイスロスト時のためのリソース再確保
	void recover();

	void beginShadow();
	void endShadow();

	//debug用
	void drawShadowMapBuffer()const;
private:
	void loadDefalutEffect();

	//・妥当でないテクニックは除外される。
	//　http://msdn.microsoft.com/ja-jp/library/bb206324(v=VS.85).aspx
	//・MMDPass="object","object_ss"以外のテクニックでは、UseTexture,UseSphereMap,UseToonは正しく機能しない。
	//ポストエフェクトの前処理
	//MMEのスクリプトのScriptExternal=Colorの前の処理をする
	void preExe();
	//ポストエフェクトの後処理
	//MMEのスクリプトのScriptExternal=Colorの後の処理をする
	void postExe();

	//影テクスチャをつくりregister0にセットする
	//@param
	//enableFilter 影をぼかすか？
	void drawZPlot( bool enableFilter=true );

	void sendParamsIfIsChanged();

	

	//debug用
	void drawOffScreen( const char* effectFileName, const char *offscreenName )const;

	
	typedef std::map< const std::string, StandardEffectSharedPtr > StandardMap;
	StandardMap mStandards;
	typedef std::map< const std::string, PostEffectSharedPtr > PostMap;
	PostMap mPosts;

	BaseEffect *mCurrentEffect;
	LPD3DXEFFECTPOOL mPool;


	//中間データとして作ったけど、いらないんじゃないか？
	//でも、GameLibに切り替えるとき欲しい気がする。エフェクト(GPU)からもらってくるばいらんよな
	struct Material{
		Material()
			:mDiffuse(0.f, 0.f, 0.f, 0.f ),
			mAmbient(0.f, 0.f, 0.f, 0.f ),
			mSpecular(0.f, 0.f, 0.f, 0.f ),
			mToonColor(0.f, 0.f, 0.f, 0.f ),
			mIsChanged(true)
		{}
		~Material(){}
		void setDiffuse( const GameLib::Math::Vector4 &d ){
			mDiffuse = d;
			mIsChanged = true;
		}
		void setAmbient( const GameLib::Math::Vector4 &a ){
			mAmbient = a;
			mIsChanged = true;
		}
		void setSpecular( const GameLib::Math::Vector4 &s ){
			mSpecular = s;
			mIsChanged = true;
		}

		void setEmission( const GameLib::Math::Vector4 &e ){
			mEmission = e;
			mIsChanged = true;
		}

		void setSpecularSharpness( float sharpness ){
			mSharpness = sharpness;
			mIsChanged = true;
		}

		void setToonColor( const GameLib::Math::Vector4& toon ){
			mToonColor = toon;
			mIsChanged = true;
		}

		void setTransparency( float t ){
			mDiffuse.w=t;
			mAmbient.w=t;
			mSpecular.w=t;
			mEmission.w=t;
			mIsChanged = true;
		}

		GameLib::Math::Vector4 mDiffuse;
		GameLib::Math::Vector4 mAmbient;
		GameLib::Math::Vector4 mSpecular;
		GameLib::Math::Vector4 mEmission;
		GameLib::Math::Vector4 mToonColor;

		float mSharpness;
		bool mIsChanged;
	};

	enum{
		LIGHT_COUNT=4,
	};
	struct LightMaterials {
		LightMaterials()		
			:mIsChanged(true)
		{
			for(int i=0; i<LIGHT_COUNT; ++i ){
				mDiffuse[i].set(1.f, 1.f, 1.f, 1.f );
				mAmbient[i].set(1.f,1.f, 1.f, 1.f );
				mSpecular[i].set(1.f,1.f, 1.f, 1.f );
			}
		}
		void setDiffuse( int index, const GameLib::Math::Vector4 &d ){
			assert( index<LIGHT_COUNT );
			mDiffuse[index] = d;
			mIsChanged = true;
		}
		void setAmbient( int index, const GameLib::Math::Vector4 &a ){
			assert( index<LIGHT_COUNT );
			mAmbient[index] = a;
			mIsChanged = true;
		}
		void setSpecular( int index, const GameLib::Math::Vector4 &s ){
			assert( index<LIGHT_COUNT );
			mSpecular[index] = s;
			mIsChanged = true;
		}

		GameLib::Math::Vector4 mDiffuse[LIGHT_COUNT];
		GameLib::Math::Vector4 mAmbient[LIGHT_COUNT];
		GameLib::Math::Vector4 mSpecular[LIGHT_COUNT];
		bool mIsChanged;

	};

	struct LightCameras{
		LightCameras()
		 :mIsChanged(true)
		{}
		~LightCameras(){}

		void setPosition( int index, const GameLib::Math::Vector4& position ){
			mPosition[index] = position;
			mIsChanged = true;
		}
		void setDirection( int index, const GameLib::Math::Vector4& dir ){
			mDirection[index] = dir;
			mIsChanged = true;
		}

		//ビュー変換行列セット
		void setViewMatrix( int index, const D3DXMATRIX& view ){
			mView[index] = view;
			mIsChanged = true;
		}
		///透視変換行列セット
		void setProjectionMatrix( int index, const D3DXMATRIX& proj ){
			mProjection[index] = proj;
			mIsChanged = true;
		}
		///ワールド変換行列セット
		void setWorldMatrix( int index, const D3DXMATRIX& w ){
			mWorld[index] = w;
			mIsChanged = true;
		}

		GameLib::Math::Vector4 mPosition[LIGHT_COUNT];
		GameLib::Math::Vector4 mDirection[LIGHT_COUNT];

		D3DXMATRIX mWorld[LIGHT_COUNT];
		D3DXMATRIX mView[LIGHT_COUNT];
		D3DXMATRIX mProjection[LIGHT_COUNT];

		bool mIsChanged;
	};

	struct Camera {
		Camera()
			:mPosition(0.f),
			mDirection(0.f),

			mIsChanged(true)
		{}

		~Camera(){}

		void setPosition( const GameLib::Math::Vector4& position ){
			mPosition= position;
			mIsChanged = true;
		}
		void setDirection( const GameLib::Math::Vector4& dir ){
			mDirection = dir;
			mIsChanged = true;
		}

		//ビュー変換行列セット
		void setViewMatrix( const D3DXMATRIX& view ){
			mView = view;
			mIsChanged = true;
		}
		///透視変換行列セット
		void setProjectionMatrix( const D3DXMATRIX& proj ){
			mProjection = proj;
			mIsChanged = true;
		}
		///ワールド変換行列セット
		void setWorldMatrix( const D3DXMATRIX& w ){
			mWorld = w;
			mIsChanged = true;
		}

		void setZNear(float zn){
			mZNear=zn;
			mIsChanged = true;
		}
		void setZFar(float zf){
			mZFar=zf;
			mIsChanged = true;
		}

		GameLib::Math::Vector4 mPosition;
		GameLib::Math::Vector4 mDirection;

		D3DXMATRIX mWorld;
		D3DXMATRIX mView;
		D3DXMATRIX mProjection;
		float mZNear;
		float mZFar;
		bool mIsChanged;
	};

	LightCameras mLightCameras;
	LightMaterials mLightMaterials;
	Camera mCamera;
	Material mMaterial;
	GameLib::Math::Vector4 mEdgeColor;
	
	int mVertexNumber;

	bool mVertexBlendEnable;

	// バックバッファーの退避用
	LPDIRECT3DSURFACE9      mTempBackbuffer;	// バックバッファー
    LPDIRECT3DSURFACE9		mTempBackZ;		// バックバッファー用の深度バッファー
	D3DVIEWPORT9			mTempViewport;

	// シャドウマップとして使用するレンダリングターゲット（オリジナルサイズ）
	LPDIRECT3DTEXTURE9      mShadowTexture;		// テクスチャ
	LPDIRECT3DSURFACE9      mShadowTexSurface;	// テクスチャから取得するサーフェース
    LPDIRECT3DSURFACE9		mShadowTexZ;		// テクスチャ用の深度バッファー
	GameLib::Graphics::Texture mShadowDummyTexture;//GameLib::Graphics::Managerにおくるダミーのテクスチャ

	//シャドウにフィルタをかけるために使用
	PostEffectSharedPtr mGaussianEffect;
	GameLib::FileIO::InFile mGaussianFxFile;

	//アンチエイリアス
	PostEffectSharedPtr mFxaaEffect;
	GameLib::FileIO::InFile mFxaaFxFile;

	GameLib::FileIO::InFile mDefalutFxFile;
	GameLib::FileIO::InFile mDefalutPostFxFile;
	GameLib::FileIO::InFile mPointLightFxFile;

//以降はシングルトンの実装
public:
	static Manager* instance();
	void destroy();
private:
	Manager();
	~Manager();

	//disallow assign
	Manager( const Manager & );
	//disallow copy
	void operator=( const Manager & );
	struct Deleter
	{
		void operator()( Manager const* const p ) const
		{
			delete p;
		}
	};
	typedef std::unique_ptr< Manager, Deleter > UptrManager;
	static std::vector<UptrManager> mThese;
};
}//end namespace MME

