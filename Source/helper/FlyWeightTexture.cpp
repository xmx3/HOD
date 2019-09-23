#include"FlyWeightTexture.h"
#include<boost/flyweight.hpp>
#include<boost/flyweight/key_value.hpp>

#include"FlyWeightTextureImpl.h"
#include<assert.h>

FlyWeightTexture::FlyWeightTexture()
:mImpl(0)
{
	mImpl=0;
	mImpl = new Impl( "/white" );
}

FlyWeightTexture::FlyWeightTexture( const std::string &filename )
:mImpl(0)
{
	assert( filename!="/white" && "don't use '/white' in file name! it has already used in program." );
	assert( filename!="/black" && "don't use '/black' in file name! it has already used in program." );

	mImpl = new Impl( filename );
}
FlyWeightTexture::~FlyWeightTexture(){
	delete mImpl;
	mImpl=0;
}
FlyWeightTexture::operator const GameLib::Graphics::Texture&()const{
	assert(mImpl);
	return mImpl->get().texture;
}

void FlyWeightTexture::reset(const std::string &filename){
	delete mImpl;
	mImpl=0;
	mImpl = new Impl( filename );
}

bool FlyWeightTexture::isReady(){
	assert( mImpl );
	return  const_cast<GameLib::Graphics::Texture*>( &(mImpl->get().texture) )->isReady();
}

bool FlyWeightTexture::isError()const{
	assert(mImpl);
	return const_cast<GameLib::Graphics::Texture*>( &(mImpl->get().texture) )->isError();
}

void FlyWeightTexture::resetWhiteTexture(){
	delete mImpl;
	mImpl=0;
	mImpl = new Impl( "/white" );
}
void FlyWeightTexture::resetBlackTexture(){
	delete mImpl;
	mImpl=0;
	mImpl = new Impl( "/black" );
}



bool FlyWeightTexture::isBlackTexture()const{
	return mImpl->get().isBlackTexture();
}
bool FlyWeightTexture::isWhiteTexture()const{
	return mImpl->get().isWhiteTexture();
}