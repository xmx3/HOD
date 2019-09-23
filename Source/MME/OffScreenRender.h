#pragma once
#include<d3dx9.h>
#include"formats.h"
#include<string>
#include<vector>
#include<GameLib/Math/Vector4.h>
#include"StandardEffect.h"

namespace MME {
class BaseEffect;
class OffScreenRender;
typedef std::shared_ptr<OffScreenRender> OffScreenRenderSharedPtr;


class OffScreenRender {
public:
	static OffScreenRenderSharedPtr create( ID3DXEffect *effect, D3DXHANDLE hTex, const std::string& currentPath, LPD3DXEFFECTPOOL pool );
	static void clearCache();
	static void shrinkToFitCache();

	~OffScreenRender();

	bool isError()const;

	void send(ID3DXEffect *effect);


	void begin();
	void end();
	void draw();

	LPDIRECT3DTEXTURE9 getDxTexture();


	const std::string & getName()const;

	//void removeRemovableObjects();
	
	void add( const Object::IObjectSharedPtr &obj );
	
	void clearAllObjects();
	
	//存在しない場合NULLを返す
	StandardEffectSharedPtr findStandardEffect( const std::string &name );

	//オブジェクトのモデル名を入力として、
	//mDefalutEffectsの中から正規表現でマッチするエフェクトを探す。
	//なかった場合falseを返す
	bool findProperEffectName( std::string *found, const Object::IObjectSharedPtr &obj );

	//デバイスロスト時のための開放処理
	void backup();
	//デバイスロスト時のためのリソース再確保
	void recover();

	std::string findStandardEffect( const Object::IObjectSharedPtr &obj ); 

	unsigned int getNumberOfStandardEffects()const;
	StandardEffectSharedPtr getStandardEffectAt( unsigned int i);
private:
	OffScreenRender( ID3DXEffect *effect, D3DXHANDLE hTex, const std::string& currentPath, LPD3DXEFFECTPOOL pool );
	OffScreenRender( const OffScreenRender &src, ID3DXEffect *effect, D3DXHANDLE hTex, const std::string& currentPath, LPD3DXEFFECTPOOL pool );
	
	std::string mName;

	D3DXHANDLE mHandle;
	std::shared_ptr<IDirect3DTexture9> mTexture;
	std::shared_ptr<IDirect3DSurface9> mSurface;

	std::shared_ptr<IDirect3DSurface9> mZBuffer;

	
	LPDIRECT3DSURFACE9      mTempBackbuffer;	// 退避用バックバッファー
	LPDIRECT3DSURFACE9		mTempBackZ;			// 退避用バックバッファー用の深度バッファー
	D3DVIEWPORT9			mTempViewport;			// 退避用ビューポート


	// ビューポート情報の保持
	D3DVIEWPORT9 viewport1;

	GameLib::Math::Vector4	mClearColor;
	float					mClearDepth;
	int						mIsAntiAilias;
	std::string				mDescription;

	//・string DefaultEffect
	//　オフスクリーンレンダリングで使用するエフェクトファイルの割り当て方法を指定する。
	//　１つの割り当ては、以下の書式で記述する。
	//　
	//　　　"(オブジェクトファイル名)=(エフェクトファイル名);"
	//　　
	//　　オブジェクト毎に使用するエフェクトファイルを切り替えるには、この割り当てを複数回記述する。
	//　　複数回記述した場合、記述した順でオブジェクトファイル名が比較され、最初にマッチしたものが使用される。
	//　　
	//　　　例： string DefaultEffect = "self=hide; Mirror*.x=hide; *=MirrorObject.fx;";
	//　　
	//　　オブジェクトファイル名には"*"と"?"によるワイルドカードが指定できる。
	//　　特殊なオブジェクトファイル名として"self"が指定でき、これは、
	//　　このOFFSCREENRENDERTARGETを持つエフェクトが割り当てられたオブジェクト自身を表す。
	//　　
	//　　エフェクトファイル名に相対パスでファイル名を指定した場合、
	//　　参照元のエフェクトファイルが格納されているフォルダが基準となる。
	//　　
	//　　また、特殊なエフェクトファイル名として"none"と"hide"が指定でき、
	//　　これは、「エフェクトなし」と「非表示」を表す。
	//　　また、"main_default"を指定すると、メインスクリーンでのデフォルト動作と同様な、
	//　　オブジェクトファイルパスに基づくfxファイルやemdファイルの自動割当が行われる。
	//　　
	struct DefalutEffect;
	std::vector<DefalutEffect*> mDefalutEffects;
	
	std::vector<StandardEffectSharedPtr> mEffects;

	D3DFORMAT mFormat;
	unsigned int mHeight;
	unsigned int mWidth;
	int mMipLevels;

	static std::vector< std::weak_ptr<OffScreenRender> > sCache;

};

}// end namespace MME