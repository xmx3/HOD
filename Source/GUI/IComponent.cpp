#include"IComponent.h"
#include"Manager.h"
#include"Fonts.h"
#include<assert.h>
#include<GameLib/Scene/PrimitiveRenderer.h>
#include<GameLib/Scene/StringRenderer.h>
#include<GameLib/Scene/Font.h>
#include<GameLib/GameLib.h>
#include<GameLib/Math/Vector2.h>
namespace GUI{

IComponent::~IComponent(){
	if( Manager::isInstance() ) {
		Manager::instance()->remove(this);
	} else{
		/*assert( false && "release order is wrong." &&
			"GUI::Manager release want to be last as you can. because of this class is depend on GUI::Manager::mComponents." &&
			"but GUI::Manager works without memory leak.");*/
	}

}

BaseComponent::BaseComponent( 
		int x, int y,
		int sizeX, int sizeY 
	)
	:mX(x), mY(y),
	mSizeX(sizeX), mSizeY(sizeY),
	mIsEnable(true), mIsDrawAble(true)
{}

BaseComponent::~BaseComponent(){
}

ComponentWithRender::ComponentWithRender( 
		int x, int y,
		int sizeX, int sizeY,
		unsigned int color,
		unsigned int fontColor,
		bool isEnableDepthTest,
		bool isEnableDepthWrite,
		GameLib::Graphics::BlendMode bm,
		GameLib::Graphics::CullMode cm,
		int vertexCapacity, int commandCapacity,
		int charCapacity, int charRequestCommandCapacity )
	:BaseComponent( x, y, sizeX, sizeY ),
	mColor(color),
	mFontColor(fontColor),
	mIsEnableDepthTest(isEnableDepthTest),
	mIsEnableDepthWrite(isEnableDepthWrite),
	mBlendMode(bm),
	mCullMode(cm),
	mRender(NULL),
	mStringRender(NULL)
{
	mRender = NEW PrimitiveRenderer();
	mStringRender = NEW StringRenderer();
	*mRender = PrimitiveRenderer::create( vertexCapacity,  commandCapacity );
	*mStringRender = StringRenderer::create( charCapacity, charRequestCommandCapacity );
	
	setFont( Fonts::getGothic() );
}


const int ComponentWithRender::skStringPosXOffset=5;

ComponentWithRender::~ComponentWithRender(){
	SAFE_DELETE( mStringRender );
	SAFE_DELETE(mRender);
}

void ComponentWithRender::calcPosCenterAlign( int *startX, int *startY, const char* text ) const{
	int left, top, right, bottom;  
	mStringRender->calcTextSize(
		&left, &top, &right, &bottom,
		GameLib::Vector2( 0.f, 0.f ),
		text );

	int textLen=strlen(text);
	assert( textLen!=0 );
	int h = mFont.charHeight();
	int w = right/textLen;

	int textSizeX = w*(textLen-1);
	//assert( mSizeX>textSizeX  );
	if( mSizeX>textSizeX ){
		if(startX){ *startX = mX + (mSizeX-textSizeX)/2; }
		if(startY){ *startY = mY + (mSizeY-h)/2; }
	} else {
		if(startX){ *startX = mX; }
		if(startY){ *startY = mY + (mSizeY-h)/2; }
	}	
}


void ComponentWithRender::setFont( GameLib::Scene::Font f ){
	mFont=f;
	mStringRender->setFont( mFont );
}

}