#ifndef __KZTR_GUI_MANAGER_H__
#define __KZTR_GUI_MANAGER_H__
#include<list>
#include"IModalDialog.h"

namespace GameLib{
	namespace Scene{
		class StringRenderer;
		class Font;
		class PrimitiveRenderer;
	}
	namespace Graphics{
		class Texture;
	}
}
using GameLib::Scene::StringRenderer;
using GameLib::Scene::Font;
using GameLib::Scene::PrimitiveRenderer;
using GameLib::Graphics::Texture;


namespace GUI{
class IComponent;
class IModalDialog;
/*問題点
TODO
下のいろいろと問題じゃないか？
リファクタリング案
	unique_ptrあたりで片づける
	コンストラクタでロードを待つ
	すべてリソースを読み込ませる
	待たせてもそこまで遅くないでしょ

*/
/*使い方
GUI::Manager::instance();
したら一回
GUI::Manager::instance()->isReady();
でテクスチャロード終わったことを確認すること

使い終わったら、必ず
	GUI::Manager::instance()->destory();
を呼ぶこと。

void constructor_or_init(){
	mLabel = new GUI::Label( 50, 50, 200, 200 );
	mLabel->setText( "redｄｄｄｄｄｄｄｄ長い文をどうする" );
	GUI::Manager::instance()->add( mLabel );
	Texture t = Texture::create( "Data/alphablend_gradation_white_256x1.png" );
	//Texture t = Texture::create( "Data/alphablend_gadation_black_256x1.png" );
	//Texture t = Texture::create( "Data/gradation_black_white.png" );
	while(!t.isReady()){}
	mLabel->setTexture(t);
	mLabel->setColor( 0xffff0000 );

	mButton = new GUI::Button( 50, 100, 200, 50 );
	mButton->setText( "push start" );
	mButton->setColor( 0xffffff00 );
	
	//不透明
	mButton->setBlendMode( GameLib::Graphics::BLEND_OPAQUE);
	mButton->setIsEnableDepthTest(false);
	mButton->setIsEnableDepthWrite(false);
	
	GUI::Manager::instance()->add( mButton );
	

	mImageButton = new GUI::ImageButton( 300, 0, 100, 100 );
	//何もセットしないと豆腐
	//mImageButton->setTexture(0);
	mImageButton->setText( "nya---" );
	mImageButton->setFontColor( 0xff0000ff );
	GUI::Manager::instance()->add( mImageButton );
}

void gameLoop(){
	if( mButton->isPushed() ){
		//next Game Scene
	}
	
	if( mImageButton->isPushing() ){
		if( mImageButton->isHover() ){
			mImageButton->setText( "pushing. hover" );			
		} else {
			mImageButton->setText( "pushing" );
		}
	} else if( mImageButton->isPushed() ){
		std::ostringstream oss;
		oss << "押した時間: " << GameLib::Framework::instance().time();
		mImageButton->setText( oss.str().c_str() );
	}
		
	//描画
	GUI::Manager::instance()->draw();
}

void destory(){
	SAFE_DELETE( mImageButton );
	SAFE_DELETE( mLabel );
	SAFE_DELETE( mButton );
	GUI::Manager::instance()->destory();
}
*/

//GUIMangaer
class Manager {
public:
	friend class IComponent;
	
	friend void IModalDialog::show();
	friend void IModalDialog::hide();
	
	/*font関連はひとまず置いとく。
	enum FONT_STYLE
	{
		GOTHIC,
	
	};
	//boldとかitalicとかどうするの？
	void changeFont( FONT_STYLE ){}
	*/

	static Manager* instance();
	static void destory();
	void draw();
	void add( IComponent* component );
	void remove( IComponent* component );
	bool isReady();

	//PrimitiveRenderer renderer();
	//StringRenderer stringRederer();
	Texture texture();
	//Font font();

private:
	Manager();
	~Manager();
	static bool isInstance();//GUI::Icomponentのため
private:
	static Manager			*mThis;
	static const char		*mkTextureName;

	Texture					*mTexture;
	//PrimitiveRenderer		*mRender;//毎回頂点データ構築するのかよ。無駄無駄すぎる
	//StringRenderer			*mStringRender;
	//std::vector<Font*>		mFonts;
	//Font					*mFont;
	
	std::list<GUI::IComponent*> mComponents;
	IModalDialog *mModalDialog;
};
}//namespace GUI
#endif//__KZTR_GUI_MANAGER_H__