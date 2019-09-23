#pragma once
#include<GameLib/Graphics/Texture.h>
#include"FlyWeightTexture.h"
#include<string>

struct FlyWeightTexture::Impl_t{
	Impl_t( const std::string &filename );
	~Impl_t(){}
	operator const GameLib::Graphics::Texture&()const{
		return texture;
	}

	bool isWhiteTexture()const{
		return texture==sWhiteTexture;
	}

	bool isBlackTexture()const{
		return texture==sBlackTexture;
	}

	GameLib::Graphics::Texture texture;
	static GameLib::Graphics::Texture sWhiteTexture;
	static GameLib::Graphics::Texture sBlackTexture;
};

