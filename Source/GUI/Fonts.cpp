#include "Fonts.h"
#include <memory>


namespace{
std::unique_ptr< GameLib::Scene::Font > gGothic;
}
namespace GUI{ namespace Fonts{

GameLib::Scene::Font getGothic(){
	if( !gGothic ){
		gGothic.reset( new  GameLib::Scene::Font() );
		*gGothic = GameLib::Scene::Font::create( "ＭＳ ゴシック", 24, false, false, false, true ); //MSは全角、次のスペースは半角。気をつけよう。
	}
	return *gGothic;
}

}}// end GUI::Fonts
