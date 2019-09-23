#include"ImageButton.h"
#include"Manager.h"
#include<string.h>
#include<assert.h>
#include<GameLib/GameLib.h>
#include<GameLib/Input/Mouse.h>
#include<GameLib/Scene/PrimitiveRenderer.h>
#include<GameLib/Scene/StringRenderer.h>
#include<GameLib/Math/Vector2.h>
#include<GameLib/Graphics/Texture.h>


namespace GUI{
	const unsigned int ImageButton::skMaxChar = GUI_IMAGE_BUTTON_MAX_CHAR;
	using GameLib::Math::Vector2;

	ImageButton::ImageButton( 
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
			false, false,
			GameLib::Graphics::BLEND_LINEAR, GameLib::Graphics::CULL_NONE
		),
		mIsPushed(false),
		mIsPushing(false),
		mIsHover(false),
		mTexture(NULL),
		mU0(u0), mV0(v0),
		mU1(u1), mV1(v1),
		mBigSizeRate(1.1f)
	{
		memset( mText, 0x00, sizeof( mText ) );
		mTexture= NEW Texture();
	}
		
	ImageButton::~ImageButton(){
		SAFE_DELETE(mTexture);
	}
	void ImageButton::setText( const char *text ){
		assert( strlen( text ) < skMaxChar );
		if( strlen( text ) > skMaxChar )
		{
			return;
		}

		strncpy( mText, text, skMaxChar );

	}

	void ImageButton::setTexture( Texture t ){
		*mTexture=t;
	}

	void ImageButton::setUV( 
		float u0, float v0,
		float u1, float v1 )
	{
		mU0=u0; mV0=v0;
		mU1=u1; mV1=v1;
	}

	bool ImageButton::isPushed() const{
		return mIsPushed;
	}

	bool ImageButton::isHover() const{
		return mIsHover;
	}

	bool ImageButton::isPushing() const{
		return mIsPushing;
	}

	void ImageButton::update(){
		GameLib::Input::Mouse m;
		const int &x = m.x(); 
		const int &y = m.y(); 
		mIsPushed = false;

		//マウスカソールがボタン上にあるか？
		mIsHover = BaseComponent::isHover(x, y);
		
		//ボタン上でクリックしたとき
		if( m.isTriggered(m.BUTTON_LEFT) && mIsHover ){
			mIsPushing = true;
		}

		//ボタン上でクリックしてあり、離した場合
		if( mIsPushing  && m.isReleased( m.BUTTON_LEFT ) ) {
			//ボタン上で離した場合
			if( mIsHover )  {
				mIsPushed = true;
			}
			//押したフラグ解除
			mIsPushing = false;
		}


	}

	void ImageButton::draw( Manager* mngr ){
		namespace gs=GameLib::Scene;
		mRender->enableDepthTest( mIsEnableDepthTest );
		mRender->enableDepthWrite( mIsEnableDepthWrite );
		mRender->setBlendMode( mBlendMode );
		mRender->setCullMode( mCullMode );
		mRender->setTexture( *mTexture );
		if( mIsPushing && mIsHover ){
			mRender->addRectangle( 
				Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
				Vector2( static_cast<float>(mX+mSizeX*mBigSizeRate), static_cast<float>(mY+mSizeY*mBigSizeRate) ),
				Vector2( mU0, mV0 ),
				Vector2( mU1, mV1 ),
				mColor );
		}
		else {
			mRender->addRectangle( 
				Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
				Vector2( static_cast<float>(mX+mSizeX), static_cast<float>(mY+mSizeY) ),
				Vector2( mU0, mV0 ),
				Vector2( mU1, mV1 ),
				mColor );
		}
		
		
		//int startX, startY;
		//assert(strlen(mText)!=0);
		////中央寄せ
		//calcPosCenterAlign( &startX, &startY, mText );
		//mStringRender->add( startX, startY, mText, mFontColor );
		
		mRender->draw();
		//mStringRender->draw();
	}
}//namespace GUI;