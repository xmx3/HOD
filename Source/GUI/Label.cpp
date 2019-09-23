#include"Label.h"
#include"Manager.h"
#include<GameLib/Graphics/Texture.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/GameLib.h>
#include<string.h>
#include<assert.h>
#include<GameLib/Scene/PrimitiveRenderer.h>
#include<GameLib/Scene/StringRenderer.h>
#include<GameLib/Math/Vector2.h>

using GameLib::Math::Vector2;

namespace GUI {


Label::Label(
	int x, int y,
	int sizeX, int sizeY,
	unsigned int color,
	unsigned int fontColor,
	float u0, float v0,
	float u1, float v1 )
	:ComponentWithRender( 
		x, y,
		sizeX, sizeY,
		color,
		fontColor,
		false, false, GameLib::Graphics::BLEND_LINEAR, GameLib::Graphics::CULL_NONE
	),
	mU0(u0), mV0(v0),
	mU1(u1), mV1(v1)
{
	mTexture= NEW GameLib::Graphics::Texture();
	memset( mText, 0x00, sizeof( mText ) );
}

Label::~Label(){
	SAFE_DELETE(mTexture);
}
		
void Label::setTexture( Texture t ){
	*mTexture=t;
}

void Label::setText( const char *text ){
	assert( strlen( text ) < GUI_LABEL_MAX_CHAR );
	if( strlen( text ) > GUI_LABEL_MAX_CHAR )
	{
		return;
	}

	strncpy( mText, text, GUI_LABEL_MAX_CHAR );
}
void Label::setUV( 
	float u0, float v0,
	float u1, float v1 )
{
	mU0=u0; mV0=v0;
	mU1=u1; mV1=v1;
}

void Label::update(){}

void Label::draw( Manager* mngr ){

	mRender->enableDepthTest( mIsEnableDepthTest );
	mRender->enableDepthWrite( mIsEnableDepthWrite );
	mRender->setBlendMode( mBlendMode );
	mRender->setCullMode( mCullMode );
	
	mStringRender->add( mX, mY, mText, mFontColor );

	if(*mTexture)
	{
		mRender->setTexture( *mTexture );
	} else {
		mRender->setTexture( 0 );
		//assert(false && "you don't set a Texture.");
	}
	mRender->addRectangle( 
		Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
		Vector2( static_cast<float>(mX+mSizeX), static_cast<float>(mY+mSizeY) ),
		Vector2( mU0, mV0 ),
		Vector2( mU1, mV1 ),
		mColor );

	mRender->draw();
	mStringRender->draw();
}

}//namespace GUI