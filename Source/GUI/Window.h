#ifndef __KZTR_GUI_WINDOW_H__
#define __KZTR_GUI_WINDOW_H__
#include<list>
#include"IComponent.h"

namespace GameLib{
	namespace Scene{
		class PrimitiveRenderer;
	}
	namespace Graphics{
		class Texture;
	}
	//namespace Math{
	//	class Vector2;
	//}
}


namespace GUI{
class Manager;

//–¼‘OGroup‚É‚µ‚Ä‚à‚¢‚¢‚©‚à
class Window : public IComponent {
public:
	Window(
		int x, int y,
		int sizeX, int sizeY,
		unsigned int color = 0xffffffff );
	virtual ~Window();

	virtual void update();
	virtual void draw( Manager *mngr );

	bool isDragging() const {
		return mIsDragging;
	}
	bool isDropped() const {
		return mIsDropped;		
	};
	
	bool isDraggAble() const{
		return mIsDraggAble;
	}

	void setIsDraggAble( bool b ) {
		mIsDraggAble=b;
		if(!b){
			mIsDragging=false;
			mIsDropped=false;
		}
	}

	bool isEnabled() const {
		return mIsEnable;
	}
	void setIsEnabled( bool b ){
		mIsEnable = b;
	}

	bool isDrawAble() const {
		return mIsDrawAble;
	}
	void setIsDrawAble( bool b ){
		mIsDrawAble = b;
	}

	void setPos( int x, int y );
	void getPos( int *x, int *y ) const {
		*x=mX;
		*y=mY;
	}

	void setTexture( const GameLib::Graphics::Texture &t );
	void setUV( 
		float u0, float v0,
		float u1, float v1 )
	{
		mU0=u0;
		mV0=v0;
		mU1=u1;
		mV1=v1;
	}
	void setColor( unsigned int c ){
		mColor=c;
	}


	void add( BaseComponent* child );
	void remove( BaseComponent*  child );
private:
	//disallow copy
	Window( const Window& );	
	//disallow assin
	void operator=( const Window& );

	void updateMouseControll();

	int		mSizeX, mSizeY;
	int		mX, mY;

	GameLib::Scene::PrimitiveRenderer *mRender;

	GameLib::Graphics::Texture *mTexture;
	float	mU0, mV0;
	float	mU1, mV1;
	unsigned int mColor;

	bool	mIsEnable;
	bool	mIsDrawAble;
	
	int		mClickedX, mClickedY;
	int		mClickedOffsetX, mClickedOffsetY;
	bool	mIsDraggAble;
	bool	mIsDragging;
	bool	mIsDropped;

	std::list<BaseComponent*>	mChildren;

};


}//namespace GUI
#endif//__KZTR_GUI_WINDOW_H__