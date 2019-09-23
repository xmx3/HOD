#include"OkDialog.h"
#include"Button.h"
#include"Window.h"
#include<GameLib/GameLib.h>
#include<GameLib/Framework.h>
#include<GameLib/Graphics/Texture.h>

namespace GUI{
OkDialog::OkDialog()
	:mOkButton(NULL),
	mWindow(NULL),
	mIsEnable(true),
	mIsDrawAble(true)
{
	GameLib::Framework fw;
	struct Xy{int x,y;};
	Xy size, pos;
	size.x = fw.width()/2;
	size.y = fw.height()/2;
	pos.x = fw.width()/4;
	pos.y = fw.height()/4;

	mWindow = new Window( pos.x, pos.y, size.x, size.y );
	//mWindow->setIsDrawAble( false );
	mWindow->setColor( 0x77000000 );
	//GameLib::Graphics::Texture t = GameLib::Graphics::Texture::create("Data/GUI/ele2.png"); 
	//while(!t.isReady()){}
	//mWindow->setTexture(t);

	Xy posb, sizeb;//size_Button
	sizeb.x = size.x/3; 
	sizeb.y = size.y/3;
	posb.x = size.x/2 - sizeb.x/2;
	posb.y = size.y/2 - sizeb.y/2;
	mOkButton = new Button( posb.x, posb.y, sizeb.x, sizeb.y );
	mOkButton->setText( "ok" );
	//mOkButton->setColor( 0x777777ff );
	mOkButton->setFontColor( 0xff000000 );
	mWindow->add( mOkButton );
}

OkDialog::~OkDialog(){
	mWindow->remove( mOkButton );
	SAFE_DELETE( mOkButton );
	SAFE_DELETE( mWindow );
}

void OkDialog::update(){
	mWindow->update();
}
void OkDialog::draw( Manager* m){
	mWindow->draw(m);
}
bool OkDialog::isOk()const{
	return mOkButton->isPushed();
}

void OkDialog::setText(const std::string &text) {
	mOkButton->setText(text.c_str());
}

}