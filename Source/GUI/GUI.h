#ifndef __KZTR_GUI_H__
//GUIクラスって普通にかぶりそうだから、接頭辞つけておく
#define __KZTR_GUI_H__

#include<list>

class Image;
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


namespace GUI {

/*問題
	描画順をどうするか？
		優先度つきコンテナ？
		○考えない

	windowとか親関係をどうするか？
		
	シングルトンではなくたくさん必要だとする。では、呼び出すときどうする？
		○シングルトンでいく
		シングルトンでいいんじゃない？名前が悪い気がしてます。
		GUIManagerの名前だったらシングルトンでもオッケ？
		HUD gameHud = HUD::findInstance("game");
		HUD::create( const char*, いろいろ
		static std::map< const char*, HUD* > mThese;
		static void releaseAll();
		static void release( const char * );

	isEnable()有効かどうか。ボタンが上に上書きされていたら,押せなくする

	listをaddして、わざわざremoveしないようにしたい。そのためにはデストラクタでlistを知りたい。
		○シングルトンにしてるので、呼び出せる
		

	Texture defalutTexturを持たせる場合、参照カウントが巡回にならないか？

*/





//押してる間、ずっとtrueを返すボタン
//class RepeatButton{};
	
//オリジナル画像のボタン
//画像一まとめバージョンか画像2つバージョンか？
//class ImageButton{
//	ImageButton(
//		Texture tex,
//		Texture pushedTex,
//		int x, int y,
//		int sizeX, int sizeY,
//		float u0, float v0, 
//		float u1, float v1 );
	
//	
//class HorizotialSlider{};
//class VerticalScrollBar{};
//
//
////背景ありのLabel
//class Box{};
//
////一行の文字列
//class TextField{};
//class TextArea{};
//	
////チェックボックス
//class Toggle{};
//
//class Toolbar{};
//class SelectionGrid{};
//

}//namespace GUI

#endif