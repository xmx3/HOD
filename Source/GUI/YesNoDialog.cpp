#include"YesNoDialog.h"
#include"Button.h"
#include"Window.h"
#include<GameLib/GameLib.h>
#include<GameLib/Framework.h>
#include<GameLib/Graphics/Texture.h>
#include"Label.h"

namespace GUI{
YesNoDialog::YesNoDialog( const char *questionText )
	:mBtYes(NULL),
	mBtNo(NULL),
	mQuestionText(NULL),
	mWindow(NULL),
	mIsEnable(true),
	mIsDrawAble(true)
{
	//íËêî
	static const unsigned int green = 0xff33dd33;
	static const unsigned int white = 0xffffffff;
	static const unsigned int red = 0xffdd3333;
	
	static const unsigned int backGroundColor = 0xdd3333dd;


	GameLib::Framework fw;
	struct Xy{int x,y;};
	Xy size, pos;
	float rate = 2.f/3.f;
	size.x =static_cast<int>( fw.width()*rate );
	size.y =static_cast<int>( fw.height()*rate );
	pos.x = (fw.width() - size.x)/2;
	pos.y = (fw.height() - size.y)/2;

	mWindow = new Window( pos.x, pos.y, size.x, size.y, backGroundColor );
	mWindow->setIsDraggAble( false );
	//mWindow->setIsDrawAble( false );
	//GameLib::Graphics::Texture t = GameLib::Graphics::Texture::create("Data/GUI/ele2.png"); 
	//while(!t.isReady()){}
	//mWindow->setTexture(t);

	Xy posYes, sizeYes;
	sizeYes.x = size.x/3; 
	sizeYes.y = size.y/3;
	posYes.x = size.x/9;
	posYes.y = size.y/2 - sizeYes.y/2;
	
	mBtYes = new Button( posYes.x, posYes.y, sizeYes.x, sizeYes.y, green, white);
	mBtYes->setText( "ÇÕÇ¢" );
	mWindow->add( mBtYes );

	Xy posNo, sizeNo;
	sizeNo.x = size.x/3; 
	sizeNo.y = size.y/3;
	posNo.x = size.x*5/9;
	posNo.y = size.y/2 - sizeNo.y/2;
	mBtNo = new Button( posNo.x, posNo.y, sizeNo.x, sizeNo.y, red, white );
	mBtNo->setText( "Ç¢Ç¢Ç¶" );
	mWindow->add( mBtNo );

	mQuestionText = new Label( posYes.x, posYes.y/2, 0, 0, 0x00, white );
	mQuestionText->setText(questionText);
	mWindow->add( mQuestionText );
}

YesNoDialog::~YesNoDialog(){
	//mWindow->remove( mBtYes );
	SAFE_DELETE( mQuestionText );
	SAFE_DELETE( mBtNo );
	SAFE_DELETE( mBtYes );
	SAFE_DELETE( mWindow );
}

void YesNoDialog::update(){
	mWindow->update();
}
void YesNoDialog::draw( Manager* m){
	mWindow->draw(m);
}
bool YesNoDialog::isYes()const{
	return mBtYes->isPushed();
}

bool YesNoDialog::isNo()const{
	return mBtNo->isPushed();
}

}