#include"FlyweightTextureImpl.h"
GameLib::Graphics::Texture FlyWeightTexture::Impl_t::sWhiteTexture;
GameLib::Graphics::Texture FlyWeightTexture::Impl_t::sBlackTexture;

FlyWeightTexture::Impl_t::Impl_t( const std::string &filename ){
	if( filename=="/white" ){
		if(!sWhiteTexture){
			sWhiteTexture = GameLib::Graphics::Texture::create( 1, 1, false );
			unsigned* textureData;
			int pitch;
			sWhiteTexture.lock( &textureData, &pitch, 0 );
			*textureData = 0xffffffff;
			sWhiteTexture.unlock( &textureData );
			textureData = 0;
		}
		texture = sWhiteTexture;
		return;
	
	}
	else if( filename=="/black" ){
		if(!sBlackTexture){
			sBlackTexture = GameLib::Graphics::Texture::create( 1, 1, false );
			unsigned* textureData;
			int pitch;
			sBlackTexture.lock( &textureData, &pitch, 0 );
			*textureData = 0x00000000;
			sBlackTexture.unlock( &textureData );
			textureData = 0;
		}
		texture = sBlackTexture;
		return;
	}
	
	if( !filename.empty() ){
		texture = GameLib::Graphics::Texture::create( filename.c_str() );
	}
}