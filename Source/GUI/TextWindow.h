#ifndef __GUI_TEXTWINDOW_H__
#define __GUI_TEXTWINDOW_H__
#include<vector>
#include<string>
#include<map>
#include"IComponent.h"
namespace GameLib {
	namespace Graphics {
		class Texture;
	}
	namespace PseudoXml{
		class Document;
	}
}

namespace GUI{

class Manager;

class TextWindow : public IComponent {
public:
	TextWindow(
		//int x, int y,
		//int sizeX, int sizeY,
		//unsigned int color,
		//unsigned int fontColor 
	);
	~TextWindow();

	bool load( const char* fileName );

	bool isReady();

	virtual void update();
	virtual void draw( Manager* );

	bool hasRead() const ;

	virtual bool isEnabled() const {
		return mIsEnable;
	}
	virtual void setIsEnabled( bool b ){
		mIsEnable = b;
	}

	virtual bool isDrawAble() const {
		return mIsDrawAble;
	}
	virtual void setIsDrawAble( bool b ){
		mIsDrawAble = b;
	}

	void setPos( int x, int y ){
		mX=x;
		mY=y;
	}

	void getPos( int *x, int *y) const {
		*x=mX;
		*y=mY;
	}
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

private:
	TextWindow( const TextWindow& );
	void operator=( const TextWindow& );

	void calcMaxCharLengthInDisplay();

	bool	mIsEnable;
	bool	mIsDrawAble;
	int		mSizeX, mSizeY;
	int		mX, mY;

	int		mIconSizeX, mIconSizeY;
	int		mIconX, mIconY;

	int const mFontOffsetX;
	int const mFontOffsetY;


	unsigned int	mColor; 
	unsigned int	mFontColor;

	bool							mIsEnableDepthTest;
	bool							mIsEnableDepthWrite;
	GameLib::Graphics::BlendMode	mBlendMode;
	GameLib::Graphics::CullMode		mCullMode;

	GameLib::Scene::PrimitiveRenderer		*mRender;
	GameLib::Scene::StringRenderer			*mStringRender;

	int mCurrentLine;
	int mCurrentCharPos;
	int mCurrentMessage;

	enum{
		DEFALUT_MAX_LENGTH_OF_LINE=40,
		DEFALUT_MAX_DISPLAY_LINES=3,
	};
	const int mkMaxLengthOfLine;
	const int mkMaxDisplayLines;

	typedef std::vector<std::string> Lines;
	typedef std::pair< std::string, GameLib::Graphics::Texture > Icon;// charName
	typedef std::pair< Icon, Lines > Message;
	
	std::vector<Message>	mMessages;

	GameLib::Graphics::Texture		*mWindowTexture;

	GameLib::PseudoXml::Document *mDocument;

	int mMaxCharLengthInDisplay;
	/*
<icon
  name = "初音ミク"
  file = "Data/GUI/Icon/dummy.bmp"
/>

<message
  name = "初音ミク"
  text = "\nおはaよ\n
おはよう123456789
あかさたなはまやらわa
　木理（もくめ）美（うるは）しき槻胴（けやきどう）、\n縁にはわざと赤樫を用ひたる岩畳（がんでふ）作りの長火鉢に対ひて話し敵（がたき）もなく唯一人、\n少しは淋しさうに坐り居る三十前後の女、\n男のやうに立派な眉を何日（いつ）掃ひしか剃つたる痕の青と、\n見る眼も覚むべき雨後の山の色をとゞめて翠（みどり）のひ一トしほ床しく、鼻筋つんと通り眼尻キリヽと上り、洗ひ髪をぐる／＼と酷（むご）く丸（まろ）めて引裂紙をあしらひに一本簪（いつぽんざし）でぐいと留めを刺した色気無の様はつくれど、"
/>
	*/


};


}

#endif
