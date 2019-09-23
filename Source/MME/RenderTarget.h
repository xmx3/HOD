#pragma once
#include<d3dx9.h>
#include"formats.h"
#include<memory>
#include<string>
#include<vector>


#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#endif//SAFE_RELEASE


namespace MME {
class BaseEffect;
class RenderTarget;
typedef std::shared_ptr<RenderTarget> RenderTargetSharedPtr;

class RenderTarget {
public:
	static RenderTargetSharedPtr create(  ID3DXEffect *effect, D3DXHANDLE hTex );
	static void clearCache();
	static void shrinkToFitCache();
	~RenderTarget();

	bool isError()const;

	void send(ID3DXEffect *effect);

	//IDirect3DSurface9* getSurfLevel( UINT level );


	//名前が目的語と主語でかぶっているがわかりやすいからこの名前にした
	//他候補としては
	//	setToDevice
	//	setSelf
	void setRenderTarget( int renderTargetIndex, BaseEffect* effect );

	const std::string & getName()const;

	//デバイスロスト時のための開放処理
	void backup();

	//デバイスロスト時のためのリソース再確保
	void recover();

private:
	RenderTarget( ID3DXEffect *effect, D3DXHANDLE hTex );

	RenderTarget( const RenderTarget &src, ID3DXEffect *effect, D3DXHANDLE hTex );

	std::string mName;//scriptで使用
	//	○コマンドS
	//・rendercolortarget=(テクスチャ名 or 空白)
	//・rendercolortarget0=(テクスチャ名 or 空白)
	//・rendercolortarget1=(テクスチャ名 or 空白)
	//・rendercolortarget2=(テクスチャ名 or 空白)
	//・rendercolortarget3=(テクスチャ名 or 空白)
	//　　レンダリングターゲットを設定する。

	D3DXHANDLE mHandle;
	std::shared_ptr<IDirect3DTexture9> mTexture;
	std::shared_ptr<IDirect3DSurface9> mSurface;
	D3DFORMAT mFormat;
	unsigned int mHeight;
	unsigned int mWidth;
	int mMipLevels;
	bool mIsShared;

	static std::vector< std::weak_ptr<RenderTarget> > sCache;

};

}// end namespace MME