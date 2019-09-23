#include "Image.h"

#include <GameLib/Framework.h>
#include <GameLib/Math/Vector2.h>
#include <GameLib/Graphics/Texture.h>
#include <GameLib/Scene/PrimitiveRenderer.h>
#include <assert.h>
using namespace GameLib;
using namespace GameLib::Math;


Image::Image( const char* filename ) : 
mTexture( 0 ),
mRender(0)
{	
	mTexture = new GameLib::Graphics::Texture();
	*mTexture=GameLib::Graphics::Texture::create( filename );
	mRender = new GameLib::Scene::PrimitiveRenderer();
	*mRender = GameLib::Scene::PrimitiveRenderer::create( 6, 1 );//少ないか？三角形2つ、命令数1
}

Image::~Image(){
	SAFE_DELETE(mTexture);
	SAFE_DELETE(mRender);
}

//int Image::width() const {
//	return mTexture->width();
//}
//
//int Image::height() const {
//	return mTexture->height();
//}

//void Image::setRender( GameLib::Scene::PrimitiveRenderer mRender ){
//	mRender=mRender;
//}

bool Image::isReady() {
	return mTexture->isReady();
}

void Image::draw(
	const Vector2& pos0,
	const Vector2& pos1,
	const Vector2& uv0,
	const Vector2& uv1,
	unsigned color,
	float depth )
{
	//Zテスト無用。アルファブレンドON
	mRender->enableDepthTest( false );
	mRender->enableDepthWrite( false );
	mRender->setBlendMode( Graphics::BLEND_LINEAR );
	
	mRender->setTexture(*mTexture);

	mRender->addRectangle( 
		pos0,
		pos1,
		uv0,
		uv1,			
		color,
		depth );
	mRender->draw();
}

void Image::draw( unsigned color )
{
	//Zテスト無用。アルファブレンドON
	mRender->enableDepthTest( false );
	mRender->enableDepthWrite( false );
	mRender->setBlendMode( Graphics::BLEND_LINEAR );
	
	mRender->setTexture(*mTexture);

	Framework f= Framework::instance();
	
	mRender->addRectangle( 
		Vector2( 0.f, 0.f ),
		Vector2( static_cast<float>(f.width()),  static_cast<float>(f.height()) ),
		Vector2( 0.f, 0.f ),
		Vector2( 1.f, 1.f ),			
		color,
		0.f );
	mRender->draw();
}

