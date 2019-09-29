#pragma once
#include<GameLib/Scene/Font.h>
#include<GameLib/FileIO/OutFile.h>
#include<string>

//描画なしで表示する文字列だけ欲しい場合がないか?
//というかこのクラスに表示させる機能は分けたほうがよかったのでは
//void draw( float elapsed, std::string& out );


namespace Telop{
	void destroy();
	void insert( const char *text, float start, float duration );
	//現在表示してる字幕を消去
	void eraseNow();
	//ゼロからスタートしてるのを前提
	//途中からだと表示されない字幕あり
	//例　1秒から10秒間表示を2秒からはじめた場合、それは表示されない
	void draw( float elapsed );
	void setTime(float time );
	void setFont( GameLib::Scene::Font );
	void setDefalutDuration( float duration);
	void setDefalutFontColor( unsigned int);
	void setPos( unsigned int x, unsigned int y );
	
	/*
	@0, 120 :0xffff0000
	赤字幕
	@120, 120 :0xffffffff
	1にゃろめ
	@240, 120 :0xffffffff
	2 亜 a
	@   340, 120 
	何もなかったら白
	*/
	bool parse( const char* data, unsigned int size );
	
	/*
	@0, 120 :0xffff0000
	赤字幕
	@120, 120 :0xffffffff
	1にゃろめ
	@240, 120 :0xffffffff
	2 亜 a
	@   340, 120 
	何もなかったら白
	*/
	bool parse(const std::string &text);

	//テロップを全部再生したか？
	//ロードと勘違いするかもしれないので
	//isPlayEnd, isPlayOverといったほうがわかりやすいか？
	//テロップが何もない場合trueを返す
	bool isFinished();
	GameLib::FileIO::OutFile write(const char*filename );

}