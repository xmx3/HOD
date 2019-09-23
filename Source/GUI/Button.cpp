#include"Button.h"
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
	const float Button::skU0=0.f;
	const float Button::skV0=0.f;
	const float Button::skU1=128.f/512.f;
	const float Button::skV1=64.f/512;
						 
	const float Button::skUPushed0=0.f/512.f;
	const float Button::skVPushed0=64.f/512;
	const float Button::skUPushed1=128.f/512.f;
	const float Button::skVPushed1=128.f/512;

	const int	Button::skMaxChar = GUI_BUTTON_MAX_CHAR;

	Button::Button( 
		int x, int y,
		int sizeX, int sizeY,
		unsigned int color,
		unsigned int fontColor )
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
		mIsHover(false)
	{
		memset( mText, 0x00, sizeof( mText ) );
	}
		
	Button::~Button(){}
	void Button::setText( const char *text ){
		assert( strlen( text ) < skMaxChar );
		if( strlen( text ) > skMaxChar )
		{
			return;
		}

		strncpy( mText, text, skMaxChar );

	}

	bool Button::isPushed() const{
		return mIsPushed;
	}

	bool Button::isHover() const {
		return mIsHover;
	}

	void Button::update(){
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
	void Button::draw( Manager* mngr ){
		namespace gs=GameLib::Scene;
		mRender->enableDepthTest( mIsEnableDepthTest );
		mRender->enableDepthWrite( mIsEnableDepthWrite );
		mRender->setBlendMode( mBlendMode );
		mRender->setCullMode( mCullMode );
		mRender->setTexture( mngr->texture() );
		
		//マウスカーソルがボタン上にあるなら
		if( mIsHover ){
			//押したフラグが立っているならば、へこんだボタンを書く
			if(mIsPushing ){
				mRender->addRectangle( 
					Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
					Vector2( static_cast<float>(mX+mSizeX), static_cast<float>(mY+mSizeY) ),
					Vector2( skUPushed0, skVPushed0 ),
					Vector2( skUPushed1, skVPushed1 ),
					mColor );
			}
			else {
				GameLib::Input::Mouse m;
				//マウスカーソルがボタン上にあって、他のボタンを押していないならば、ちょっと大きく書く
				if( !m.isOn(m.BUTTON_LEFT) ){
					mRender->addRectangle( 
						Vector2( static_cast<float>(mX)*0.99f, static_cast<float>(mY)*0.99f ),
						Vector2( static_cast<float>(mX+mSizeX)*1.01f, static_cast<float>(mY+mSizeY)*1.01f ),
						Vector2( skU0, skV0 ),
						Vector2( skU1, skV1 ),
						mColor );
				}
				//ほかのボタンを押している可能性があるなら通常
				else {
					mRender->addRectangle( 
						Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
						Vector2( static_cast<float>(mX+mSizeX), static_cast<float>(mY+mSizeY) ),
						Vector2( skU0, skV0 ),
						Vector2( skU1, skV1 ),
						mColor );
				}
			}
		}
		else{
			mRender->addRectangle( 
				Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
				Vector2( static_cast<float>(mX+mSizeX), static_cast<float>(mY+mSizeY) ),
				Vector2( skU0, skV0 ),
				Vector2( skU1, skV1 ),
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