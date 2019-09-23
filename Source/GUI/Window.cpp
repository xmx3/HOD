#include"Window.h"
#include<GameLib/GameLib.h>
#include<GameLib/Input/Mouse.h>
#include<GameLib/Graphics/Texture.h>
#include<GameLib/Scene/PrimitiveRenderer.h>
#include<GameLib/Math/Vector2.h>
#include<GameLib/Framework.h>
#include<algorithm>
#include<cassert>

namespace GUI{
using GameLib::Math::Vector2;
using GameLib::Graphics::Texture;
using GameLib::Scene::PrimitiveRenderer;

Window::Window(
	int x, int y,
	int sizeX, int sizeY,
	unsigned int color )
:mX(x), mY(y),
mSizeX(sizeX), mSizeY(sizeY),
mRender(NULL),
mTexture(NULL),
mU0(0.f), mV0(0.f),
mU1(1.f), mV1(1.f),
mColor(color),
mIsEnable(true),
mIsDrawAble(true),
mClickedX(0), mClickedY(0),
mClickedOffsetX(0), mClickedOffsetY(0),
mIsDraggAble(false),
mIsDragging(false),
mIsDropped(false)
{
	mTexture = NEW Texture();
	mRender = NEW PrimitiveRenderer();
	*mRender = PrimitiveRenderer::create( 6, 1 );
}
Window::~Window(){
	SAFE_DELETE(mTexture);
	SAFE_DELETE(mRender);
	mChildren.clear();
}
void Window::setPos( int x, int y){
	for(
		std::list<BaseComponent*>::iterator it=mChildren.begin(), end=mChildren.end();
		it != end;
		++it )
	{
		int cx,cy;//childX,ChildY
		(*it)->getPos( &cx, &cy );
		//古いの引いて、新しいの足す
		cx -= mX;
		cy -= mY;
		cx += x;
		cy += y;
		(*it)->setPos( cx, cy );
	}

	//最後に新しいのに更新
	mX=x;
	mY=y;
}

void Window::updateMouseControll(){
	GameLib::Input::Mouse m;
	const int &x = m.x(); 
	const int &y = m.y(); 
	mIsDropped = false;

	//window上でクリックしたとき
	if( m.isTriggered(m.BUTTON_LEFT) ){
		//マウスカソールがボタン上にあるか？
		if( x > mX &&
			x < mX+mSizeX &&
			y > mY &&
			y < mY+mSizeY )
		{
			//重なっているか調査
			bool isAnytingHover=false;
			for(
				std::list<BaseComponent*>::iterator it=mChildren.begin(), end=mChildren.end();
				it != end;
				++it )
			{		
				if( (*it)->isHover( x, y ) ){
					isAnytingHover=true;
					break;
				}
			}
			//重なっていないなら
			if( !isAnytingHover ){
				//dragging状態に移行
				mIsDragging = true;
				mClickedX = x;
				mClickedY = y;
				mClickedOffsetX = x-mX;
				mClickedOffsetY =y-mY;
			}
		}
	}

	//dragging中
	if( mIsDragging ) {
		//離した場合
		if( m.isReleased( m.BUTTON_LEFT ) )  {
			mIsDropped = true;
			mIsDragging = false;
		} else {

		}
	}
}

void Window::update() {
	//子供の値を使うので最初に子供をアップデート
	for(
		std::list<BaseComponent*>::iterator it=mChildren.begin(), end=mChildren.end();
		it != end;
		++it )
	{	
		if( (*it)->isEnabled() ){
			(*it)->update();
		}
	}

	updateMouseControll();
	
	if( mIsDraggAble ) {
		if( mIsDragging ) {
			GameLib::Input::Mouse m;
			GameLib::Framework f;
			const int width = f.width();
			const int height = f.height();
			int x = std::min( std::max( 0, m.x() ), width );
			int y = std::min( std::max( 0, m.y() ), height );
			setPos( x-mClickedOffsetX, y-mClickedOffsetY);
		}

		if( mIsDropped ) {
			GameLib::Input::Mouse m;
			GameLib::Framework f;
			const int width = f.width();
			const int height = f.height();
			int x = std::min( std::max( 0, m.x() ), width );
			int y = std::min( std::max( 0, m.y() ), height );
			setPos( x-mClickedOffsetX, y-mClickedOffsetY);
		}
	}
}

void Window::draw( Manager *mngr ){
	//windowは下地なので先に書く。
	
	//assert(*mTexture);

	//if(*mTexture)//豆腐を書くか？
	{
		mRender->setTexture( *mTexture );
		mRender->setBlendMode( GameLib::Graphics::BLEND_LINEAR );
		mRender->addRectangle( 
			Vector2( static_cast<float>(mX), static_cast<float>(mY) ),
			Vector2( static_cast<float>(mX+mSizeX), static_cast<float>(mY+mSizeY) ),
			Vector2( mU0, mV0 ),
			Vector2( mU1, mV1 ),
			mColor );
		mRender->draw();
	}

	//子はあとで書く
	for(
		std::list<BaseComponent*>::iterator it=mChildren.begin(), end=mChildren.end();
		it != end;
		++it )
	{	
		if( (*it)->isDrawAble() ){
			(*it)->draw( mngr );
		}
	}
}
void Window::add( BaseComponent *child ){
	int x,y;
	child->getPos( &x, &y );
	x += mX;
	y += mY;
	child->setPos(x ,y);
	mChildren.push_back(child);
}
void Window::remove( BaseComponent *child ){
	mChildren.remove(child);
}

void Window::setTexture( const Texture &t ){
	*mTexture = t;
}

}//namespace GUI