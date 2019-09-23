#include"SoundManager.h"
#include<GameLib/GameLib.h>
#include<GameLib/Sound/Wave.h>
#include<GameLib/Sound/Player.h>
//#include<GameLib/Sound/Manager.h>
#include <sstream>
using namespace GameLib;

SoundManager::UptrManager SoundManager::mInstance = 0;

SoundManager* SoundManager::instance(){
	if(mInstance == 0){
		mInstance.reset( new SoundManager() );
	}
	return mInstance.get();
}

void SoundManager::create(){
	//ASSERT( !mInstance );
	if(mInstance == 0){
		mInstance.reset( new SoundManager() );
	}
}

void SoundManager::destroy(){
	//ASSERT( mInstance );
	mInstance.reset();
}

SoundManager::SoundManager() :
mSePlayerPos( 0 ){
	//ファイル名リストをロード開始。
	//ちゃんと作るならにはファイル名リストは別ファイルにしたり、
	//テキストファイルにしてロードしたりすることになる。

	//なお、これは試作なので全部同じファイル...
	const char* bgmFiles[] = {
		"title.wav", //BGM_TITLE
		"charara.wav", //BGM_GAME
	};
	const char* seFiles[] = {
		"dokaan.wav", //SE_EXPLOSION
		"dokaan.wav", //SE_DEATH
		"dokaan.wav", //SE_CURSOR_MOVE
		"dokaan.wav", //SE_SELECTION
		"dokaan.wav", //SE_SET_BOMB
	};
	ostringstream oss; //文字列合成用文字列ストリーム
	for ( int i = 0; i < BGM_MAX; ++i ){
		oss.str( "" ); //初期化
		oss << "data/sound/bgm/" << bgmFiles[ i ];
		mBgmWaves[ i ] = Sound::Wave::create( oss.str().c_str() );
	}
	for ( int i = 0; i < SE_MAX; ++i ){
		oss.str( "" ); //初期化
		oss << "data/sound/se/" << seFiles[ i ];
		mSeWaves[ i ] = Sound::Wave::create( oss.str().c_str() );
	}
}

SoundManager::~SoundManager(){
	//GameLib::Sound::Managerを開放する前に開放すること
	//SoundBufferを開放するためにDirectSoundが必要なので
}

bool SoundManager::isReady(){
	//全部のWaveがtrueを返すか調べる
	//&&を取っていくと一個でもfalseならfalseになるわけだ。
	bool ret = true;
	for ( int i = 0; i < BGM_MAX; ++i ){
		ret = ret && mBgmWaves[ i ].isReady();
	}
	for ( int i = 0; i < SE_MAX; ++i ){
		ret = ret && mSeWaves[ i ].isReady();
	}
	return ret;
}

void SoundManager::playBgm( Bgm bgm ){
	mBgmPlayer = Sound::Player::create( mBgmWaves[ bgm ] );
	mBgmPlayer.play( true ); //ループ再生
}

void SoundManager::stopBgm(){
	if ( mBgmPlayer ){
		mBgmPlayer.stop();
	}
}

void SoundManager::playSe( Se se ){
	mSePlayers[ mSePlayerPos ] = Sound::Player::create( mSeWaves[ se ] );
	mSePlayers[ mSePlayerPos ].play(); //再生
	++mSePlayerPos;
	//巻き戻し
	if ( mSePlayerPos == SE_PLAYER_MAX ){
		mSePlayerPos = 0;
	}
}
