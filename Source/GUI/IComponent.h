#ifndef __KZTR_GUI_ICOMPONENT_H__
#define __KZTR_GUI_ICOMPONENT_H__
#include<GameLib/Scene/Font.h>
namespace GameLib {
	namespace Graphics {
		enum BlendMode;
		enum CullMode;
	}
	namespace Scene{
		class StringRenderer;
		class PrimitiveRenderer;
		class Font;
	}
}



namespace GUI{

class Manager;

class IComponent {
public:
	virtual ~IComponent();
	
	virtual void update()=0;
	virtual void draw( Manager* )=0;

	virtual bool isEnabled() const =0;
	virtual void setIsEnabled( bool )=0;

	virtual bool isDrawAble() const =0;
	virtual void setIsDrawAble( bool )=0;
	
	//virtual void setFontColor( unsigned int fc )=0;
	//virtual void setColor( unsigned int c )=0;
};

class IPos {
public:
	IPos(){}
	virtual ~IPos(){}
	virtual void setPos( int x, int y )=0;
	virtual void getPos( int *x, int *y) const=0;
};

class ISize {
public:
	ISize(){}
	virtual ~ISize(){}
	virtual void setSize( int sizeX, int sizeY )=0;
	virtual void getSize( int *sizeX, int *sizeY) const=0;
};

//class IHover


class BaseComponent : public IComponent, public ISize, public IPos {
public:
	BaseComponent( 
		int x, int y,
		int sizeX, int sizeY );

	virtual ~BaseComponent();

	virtual void update()=0;
	virtual void draw( Manager* )=0;

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

	virtual void setPos( int x, int y ){
		mX=x;
		mY=y;
	}

	void getPos( int *x, int *y) const {
		*x=mX;
		*y=mY;
	}

	void setSize( int sizeX, int sizeY ){
		mSizeX=sizeX;
		mSizeY=sizeY;
	}

	void getSize( int *sizeX, int *sizeY) const {
		*sizeX=mSizeX;
		*sizeY=mSizeY;
	}
	
	//ボタン上にあるか？
	bool isHover( int x, int y ) const { 
		if( x > mX &&
			x < mX+mSizeX &&
			y > mY &&
			y < mY+mSizeY )
		{
			return true;
		}
		return false;
	}
protected:
	bool	mIsEnable;
	bool	mIsDrawAble;
	int		mSizeX, mSizeY;
	int		mX, mY;
};
//実装を便利にするヘルパークラス
class ComponentWithRender : public BaseComponent{
public:
	//int vertexCapacity=6, int commandCapacity=1,
	//上2つの引数は	GameLib::Scene::PrimitiveRendererを初期化するのに使用
	//PrimitiveRenderer::create( vertexCapacity,  commandCapacity );
	//
	//int charCapacity=256, int charRequestCommandCapacity=16 
	//GameLib::Scene::StringRendererを初期化するのに使用
	//*mStringRender = StringRenderer::create( charCapacity, charRequestCommandCapacity );
	ComponentWithRender( 
		int x, int y,
		int sizeX, int sizeY,
		unsigned int color,
		unsigned int fontColor,
		bool isEnableDepthTest,
		bool isEnableDepthWrite,
		GameLib::Graphics::BlendMode bm,
		GameLib::Graphics::CullMode cm,
		int vertexCapacity=6, int commandCapacity=1,
		int charCapacity=256, int charRequestCommandCapacity=16 );

	virtual ~ComponentWithRender();

	void setFontColor( unsigned int fc ){
		mFontColor=fc;
	}

	void setColor( unsigned int c ){
		mColor=c;
	}

	void setIsEnableDepthTest( bool isdt ){
		mIsEnableDepthTest=isdt;
	}
	void setIsEnableDepthWrite(bool isdw ){
		mIsEnableDepthWrite=isdw;
	}
	void setBlendMode( GameLib::Graphics::BlendMode bm ){
		mBlendMode=bm;
	}
	void setCullMode( GameLib::Graphics::CullMode cm ){
		mCullMode=cm;
	}

	const GameLib::Scene::Font & font()const{
		return mFont;
	}

	void setFont( GameLib::Scene::Font f );


protected:
	//中央寄せ
	//一列の場合のみ
	void calcPosCenterAlign( int *startX, int *startY, const char* text )const;

	unsigned int	mColor; 
	unsigned int	mFontColor;

	bool							mIsEnableDepthTest;
	bool							mIsEnableDepthWrite;
	GameLib::Graphics::BlendMode	mBlendMode;
	GameLib::Graphics::CullMode		mCullMode;

	GameLib::Scene::Font					mFont;
	GameLib::Scene::PrimitiveRenderer		*mRender;
	GameLib::Scene::StringRenderer			*mStringRender;
	
	static const int skStringPosXOffset;
};


}//namespace GUI
#endif//__KZTR_GUI_ICOMPONENT_H__