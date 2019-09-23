#pragma once
#include<GameLib/Graphics/Texture.h>
#include<string>

#include<boost/flyweight/flyweight_fwd.hpp>
#include <boost/flyweight/key_value_fwd.hpp>


//ちょっと使いにくい
//理由
//	FlyWeightTexture t = createWhiteTexture();が出来ないため


//所有権を保持してるが、委譲する機能はつけていない
//あくまで作成時の補助クラスでしかない
//もし、テクスチャを委譲したければ
//  FlyWeightTexture flyweightTex( "texname" );
//	GameLib::Graphics::Texture t = (const GameLib::Graphics::Texture& )flyweightTex;
//flyweightTex.reset( newfilename );　か　deleteされても所有権は委譲されている
//その場合は、新しくtexname を作った場合、新たなテクスチャは新しく作られ、flyweightの機能は有しない
//以下の2つはファイル名は特殊な実装とかぶるのが嫌なので禁止
//  FlyWeightTexture flyweightTex( "/white" );
//  FlyWeightTexture flyweightTex( "/black" );
class FlyWeightTexture{
public:
	//空のテクスチャ(GameLib::TextureのmImpl=0のtexture)を作る
	//デフォルトは白にするという案も合ったが、MMEのuseTextureにあわせやすいのでデフォルトは空のテクスチャにした
	//reset("")でも空のテクスチャを生成できる
	FlyWeightTexture();
	FlyWeightTexture( const std::string &filename );
	~FlyWeightTexture();
	operator const GameLib::Graphics::Texture&()const;
	
	void reset( const std::string &filename );
	void resetWhiteTexture();
	void resetBlackTexture();

	bool isReady();
	bool isError()const;

	bool isBlackTexture()const;
	bool isWhiteTexture()const;

private:
	//disallow
	FlyWeightTexture( const FlyWeightTexture& );
	//disallow
	void operator=( const FlyWeightTexture& );
	struct Impl_t;
	typedef boost::flyweights::flyweight<
		boost::flyweights::key_value<std::string, Impl_t >
	> Impl;
	Impl *mImpl;
};

