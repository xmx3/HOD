#include"TransparentButton.h"
#include"Manager.h"
#include<string.h>
#include<assert.h>
#include<GameLib/Input/Mouse.h>
#include<GameLib/Scene/PrimitiveRenderer.h>
#include<GameLib/Scene/StringRenderer.h>
#include<GameLib/Math/Vector2.h>
#include<GameLib/Graphics/Texture.h>


namespace GUI{
	using GameLib::Math::Vector2;
	const float TransparentButton::skU0 =   0.f/512.f;
	const float TransparentButton::skV0 = 128.f/512.f;
	const float TransparentButton::skU1 = 128.f/512.f;
	const float TransparentButton::skV1 = 192.f/512.f;
						 
	TransparentButton::TransparentButton( 
		int x, int y,
		int sizeX, int sizeY,
		unsigned int fontColor )
		:ComponentWithRender(
			x, y,
			sizeX, sizeY,
			0x0,//transparent
			fontColor,
			false, false,
			GameLib::Graphics::BLEND_LINEAR, GameLib::Graphics::CULL_NONE,
			12, 2//
		),
		mIsPushed(false),
		mIsPushing(false),
		mIsHover(false)
	{
		memset( mText, 0x00, sizeof( mText ) );
	}
		
	TransparentButton::~TransparentButton(){
	}

	void TransparentButton::setText( const char *text ){
		assert( strlen( text ) < kMaxChar );
		if( strlen( text ) > kMaxChar )
		{
			return;
		}

		strncpy( mText, text, kMaxChar );

	}

	bool TransparentButton::isPushed() const{
		return mIsPushed;
	}

	bool TransparentButton::isHover() const {
		return mIsHover;
	}

	void TransparentButton::update(){
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
		if( mIsPushing  && m.isReleased(m.BUTTON_LEFT) ) {
			//ボタン上で離した場合
			if( mIsHover )  {
				mIsPushed = true;
			}
			mIsPushing = false;
		}
	}
	void TransparentButton::draw( Manager* mngr ){
		namespace gs=GameLib::Scene;
		mRender->enableDepthTest( mIsEnableDepthTest );
		mRender->enableDepthWrite( mIsEnableDepthWrite );
		mRender->setBlendMode( mBlendMode );
		mRender->setCullMode( mCullMode );
		
		//マウスカーソルがボタン上にあるなら
		//選択テクスチャを表示
		if( mIsHover ){
			unsigned int color=0xffffffff;
			if( mIsPushing ){
				color=0xffffff00;//押している場合は黄色
			}

			mRender->setTexture( mngr->texture() );
			mRender->addRectangle( 
				Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
				Vector2( static_cast<float>(mX+mSizeX), static_cast<float>(mY+mSizeY) ),
				Vector2( skU0, skV0 ),
				Vector2( skU1, skV1 ),
				color );
			mRender->setTexture( 0 );
			mRender->addRectangle( 
				Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
				Vector2( static_cast<float>(mX+mSizeX), static_cast<float>(mY+mSizeY) ),
				Vector2( 0.f, 0.f ),
				Vector2( 1.f, 1.f ),
				mColor );
		}
		else{
			mRender->setTexture( 0 );
			mRender->addRectangle( 
				Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
				Vector2( static_cast<float>(mX+mSizeX), static_cast<float>(mY+mSizeY) ),
				Vector2( 0.f, 0.f ),
				Vector2( 1.f, 1.f ),
				mColor );
		}
		
		int startX, startY;
		//中央寄せ
		calcPosCenterAlign( &startX, &startY, mText );
		mStringRender->add( startX, startY, mText, mFontColor );

		mRender->draw();
		mStringRender->draw();
	}
}//namespace GUI;