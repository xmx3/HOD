#ifndef __KZTR_GUI_LABEL_H__
#define __KZTR_GUI_LABEL_H__
#include"IComponent.h"
#include<string>
namespace GameLib{
	namespace Graphics{
		class Texture;
	}
}


namespace GUI{
class Manager;

//画像と文字。クリックできない
class Label : public ComponentWithRender {
public:
	Label(
		int x, int y,
		int sizeX, int sizeY,
		unsigned int color = 0xffffffff,
		unsigned int fontColor = 0xff000000,
		float u0=0.f, float v0=0.f,
		float u1=1.f, float v1=1.f );
	virtual ~Label();
		
	void setTexture( GameLib::Graphics::Texture t );
	void setText( const char *text );
	void setUV( 
		float u0, float v0,
		float u1, float v1 );

	virtual void update();
	virtual void draw( Manager* mngr );

private:
	//disallow copy
	Label( const Label& );	
	//disallow assin
	void operator=( const Label& );
private:	
	GameLib::Graphics::Texture		*mTexture;
	enum{
		GUI_LABEL_MAX_CHAR=256,
	};
	char		mText[GUI_LABEL_MAX_CHAR];

	float	mU0, mV0;
	float	mU1, mV1;
};


}//namespace GUI
#endif//__KZTR_GUI_LABEL_H__