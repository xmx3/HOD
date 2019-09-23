#include<GameLib/GameLib.h>
#include<GameLib/Graphics/Texture.h>
#include<GameLib/Scene/Font.h>
#include<GameLib/Scene/PrimitiveRenderer.h>
#include<GameLib/Scene/StringRenderer.h>

#include"Manager.h"
#include"IComponent.h"
#include"IModalDialog.h"

namespace GUI{
Manager			*Manager::mThis=NULL;
const char * Manager::mkTextureName = "Data/GUI/GUI.png";
	

Manager* Manager::instance(){
	if(mThis){
		return mThis;
	} else {
		mThis= NEW Manager();
		return mThis;
	}
}
void Manager::destory(){
	SAFE_DELETE(mThis);
}

Manager::Manager()
	:mTexture(NULL),
	//mRender(NULL),
	//mStringRender(NULL),
	//mFont(NULL),
	mModalDialog(NULL)
{
	mTexture = NEW Texture();
	//mRender= NEW PrimitiveRenderer();
	//mStringRender = NEW StringRenderer();
	//mFont = NEW Font();
	*mTexture = Texture::create( mkTextureName );
	//*mRender = PrimitiveRenderer::create( 256, 32 );
	//*mStringRender = StringRenderer::create( 1024, 64 );
	//*mFont = Font::create( "ＭＳ ゴシック", 24, false, false, false, true ); //MSは全角、次のスペースは半角。気をつけよう。
	//mStringRender->setFont(*mFont);
}
Manager::~Manager(){
	//mFont->release();
	//SAFE_DELETE(mFont);
	//SAFE_DELETE(mStringRender);
	//SAFE_DELETE(mRender);
	SAFE_DELETE(mTexture);
	mComponents.clear();
}

void Manager::draw(){
	
	for(
		std::list<IComponent*>::iterator it=mComponents.begin(), end=mComponents.end();
		it != end;
		++it )
	{
		
		//モーダルダイアルログがあるときはisPushedとかは以前の状態のまま
		if( !mModalDialog && (*it)->isEnabled() ){
			(*it)->update();
		}
		
		if( (*it)->isDrawAble() ){
			(*it)->draw(this);
		}
	}

	if( mModalDialog ){
		mModalDialog->update();
		mModalDialog->draw(this);
	}

	//mRender->draw();
	//mStringRender->draw();
}

void Manager::add( IComponent* component ){
	mComponents.push_back( component );
}

void Manager::remove( IComponent* component ){
	mComponents.remove( component );
}

bool Manager::isReady(){
	if( mTexture->isReady() ){
		return true;
	}
	return false;
}

//PrimitiveRenderer Manager::renderer(){
//	return *mRender;
//}
//StringRenderer Manager::stringRederer(){
//	return *mStringRender;
//}

Texture Manager::texture(){
	return *mTexture;
}

bool Manager::isInstance(){
	return mThis != 0;
}

//Font Manager::font(){
	//return *mFont;
//}

}//namespace GUI


