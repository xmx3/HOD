#ifdef _WIN32
#include <windows.h>
#endif

#include <string>
#include <boost/utility/string_view.hpp>
#include <memory>

#include<assert.h>

#include "helper/MyOutputDebugString.h"

#include "LuaHelper.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include"tolua++.h"
#include"tolua_bind/luafunc_glue.h"



typedef std::unique_ptr<Lua::LuaHelper> UptrLua;

static UptrLua gLua;

//ファイルをロードした後
//luaのstartfunc関数を呼ぶを呼ぶ
void LoadLuaFiles( const char* arg );


void LuaCreate(const char* classname){
	if(gLua==nullptr){
		gLua.reset( new Lua::LuaHelper );
		// リロードと初期ロードをまとめる
		if (!gLua->DoFile("Script/common/explicit_globals.lua")) {
			TRACE1( "%s\n Exit!", gLua->GetErr() );
			exit(1);
		}

		std::string loadType(classname);
		assert(
			loadType == "luaTest" ||
			loadType == "HatuneOfTheDead" );


		loadType.append("/load");

		//これ引数commonとかにして共通部分のみロードしておく？
		LoadLuaFiles(loadType.c_str());
	}
	else {
		assert(false);
	}
}

void LuaDestroy(){
	gLua.reset(nullptr);
}


//状態遷移が全てルアに任せているわけではないので
//reload.lua、Sequence固有のreloadファイルを作るべきか
//
//リロードしたときc++のSequenceはどうするのか？
//Titleまで戻してしまうか？
//
//たとえば
//ReloadLuaFiles( "all" );を呼んだとする
//そうするとluaスクリプトのframefuncはTitle:framefuncを呼ぶようになる。
//そうした場合タイトル以外からReloadLuaFiles( "all" );を呼んだときバグになる
//ReloadLuaFileAll()を作ってその中で正しい状態に移行させる
//argを固定パラメータにするのは糞
//だったら、ReloadLuaFile( const char* fileName, const char* arg );のほうがましだろ
//
//いろいろ考えた結果一番最初の設計にしよう
//argでリロードするものを変える
//リロードするファイルは一種類
void ReloadLuaFiles( const char* arg ){
	using namespace Lua;
	LuaFuncParam param;
	param.String(arg);
	LuaFuncParam result;
	while (true) {
		if (gLua->DoFile("Script/game/reload.lua", &result, 2, &param)) {
			if (result.GetBool(0)) {
				// スクリプトリロード成功
				break;
			}
			WaitInputOnError(result.GetString(1), "Reload OK?");
		}
		else {
			WaitInputOnError(gLua->GetErr(), "Reload OK?");
		}
	}
}
void LoadLuaFiles(const char* arg ){
	ReloadLuaFiles(arg);

	// 初期化用Lua関数を呼ぶ
	Lua::LuaFuncParam result;
	if (!gLua->CallFunc("startfunc", &result, 1)) {
		TRACE1( "%s\n Exit!", gLua->GetErr() );
		exit(1);
	}
	else {
		// 関数の返り値
		const char *str = result.GetString(0);
	}
}

bool DoLuaFile(const char* path){
	std::string err;
	if (!gLua->DoFile(path, NULL, 0, NULL)) {
		// エラー文字列を返す
		err = gLua->GetErr();
		TRACE1("DoLuaFile: %s", err.c_str());
		return false;
	}
	return true;
}

// Luaのエラーを取得する
const char * GetLuaError() {
	return gLua->GetErr();
}

bool CallLuaFunc(const char *funcname, Lua::LuaFuncParam* result, int result_count, Lua::LuaFuncParam* params){
	return gLua->CallFunc( funcname, result, result_count, params );
}

// エラー時の入力待ち関数
void WaitInputOnError(const char *mes, const char *postfix)
{
#ifdef _WIN32
	char text[1000];
	strcpy(text, mes);
	strcat(text, ".\r\n");
	strcat(text, postfix);
	TRACE(mes);
	MessageBoxA(NULL, text, "Error", MB_OK);
#else
	char text[1000];
	strcpy(text, mes);
	strcat(text, ".\n ");
	strcat(text, postfix);
	strcat(text, "\n>");
	printf(text);
	getchar();
#endif
}	


//
//  class LuaFuncParamItem
//
namespace Lua {
// バッファ解放
void LuaFuncParamItem::ReleaseValue() {
	if (m_type == LUA_TSTRING) {
		if (m_str) delete [] m_str;
		m_str = NULL;
	}
}

// 数値をセット
void LuaFuncParamItem::SetNumber(double number) {
	ReleaseValue();
	m_type = LUA_TNUMBER;
	m_number = number;
}
// 文字列値をセット
void LuaFuncParamItem::SetString(const char * str) {
	ReleaseValue();
	m_type = LUA_TSTRING;
	size_t len = strlen(str);
	m_str = new char[len+1];
	if (m_str) {
		strncpy(m_str, str, len);
		m_str[len] = '\0';
	}
}
// nil値をセット
void LuaFuncParamItem::SetNil() {
	ReleaseValue();
	m_type = LUA_TNIL;
}
// bool値をセット
void LuaFuncParamItem::SetBool(bool value) {
	ReleaseValue();
	m_type = LUA_TBOOLEAN;
	m_bool = value;
}

// 格納している値をLuaスタックに積む
void LuaFuncParamItem::PushToStack(lua_State *L) {
	switch(m_type) {
	case LUA_TNUMBER: lua_pushnumber(L, m_number); break;
	case LUA_TSTRING: lua_pushstring(L, m_str); break;
	case LUA_TNIL: lua_pushnil(L); break;
	case LUA_TBOOLEAN: lua_pushboolean(L, m_bool); break;
	}
}

//
//  class LuaFuncParam
//

// パラメータを全クリア
void LuaFuncParam::Clear() {
	for(int i=0 ; i<m_params_count ; i++) {
		m_params[i].ReleaseValue();
	}
	m_params_count = 0;
}

// 数値パラメータの追加
LuaFuncParam & LuaFuncParam::Number(double number) {
	m_params[m_params_count].SetNumber(number);
	m_params_count++;
	return *this;
}
// 文字列パラメータの追加
LuaFuncParam & LuaFuncParam::String(const char *str) {
	m_params[m_params_count].SetString(str);
	m_params_count++;
	return *this;
}
// nilパラメータの追加
LuaFuncParam & LuaFuncParam::Nil() {
	m_params[m_params_count].SetNil();
	m_params_count++;
	return *this;
}
// ブール値パラメータの追加
LuaFuncParam & LuaFuncParam::Bool(bool value) {
	m_params[m_params_count].SetBool(value);
	m_params_count++;
	return *this;
}

// 指定インデックスのパラメータのNULLチェック
// (インデックスは０ベース）
bool LuaFuncParam::IsNil(int index) {
	if (index < 0 || index >= m_params_count ) return true;
	return m_params[index].IsNil();
}
// 指定インデックスのパラメータ数値取得
// (インデックスは０ベース）
double LuaFuncParam::GetNumber(int index) {
	if (index < 0 || index >= m_params_count ) return 0;
	if (m_params[index].GetType() != LUA_TNUMBER) {
		return 0;
	}
	return m_params[index].GetNumber();
}
// 指定インデックスのパラメータ文字列取得
// (インデックスは０ベース）
const char * LuaFuncParam::GetString(int index) {
	if (index < 0 || index >= m_params_count ) return NULL;
	if (m_params[index].GetType() != LUA_TSTRING) {
		return NULL;
	}
	return m_params[index].GetString();
}
// 指定インデックスのブール値取得
// (インデックスは０ベース）
const bool LuaFuncParam::GetBool(int index) {
	if (index < 0 || index >= m_params_count ) return NULL;
	if (m_params[index].GetType() != LUA_TBOOLEAN) {
		return NULL;
	}
	return m_params[index].GetBool();
}

// Luaスタックに引数をプッシュして、プッシュした引数の数を返す
int LuaFuncParam::PushToStack(lua_State *L) {
	for (int i=0 ; i<m_params_count ; i++) {
		m_params[i].PushToStack(L);
	}
	return m_params_count;
}

// Luaスタックから値を取得
// スタックトップからresult_count個の値を取得して格納
void LuaFuncParam::GetFromStack(lua_State *L, int result_count) {
	for ( int i=0 ; i<result_count ; i++) {
		int index = -result_count+i;
		int type = lua_type(L, index);
		switch(type) {
		case LUA_TNIL: this->Nil(); break;
		case LUA_TSTRING: this->String(lua_tostring(L, index)); break;
		case LUA_TNUMBER: this->Number(lua_tonumber(L, index)); break;
		case LUA_TBOOLEAN: this->Bool(lua_toboolean(L, index)? true:false); break;
		default: this->Nil(); break;
		}
	}
}



//
//  class LuaHelper
//


LuaHelper::LuaHelper()
	: m_L(NULL),
	m_pGetStackTraceFunc(NULL)
{
	m_L =luaL_newstate();
	luaL_openlibs(m_L);
	// toluaでCの関数やクラスをインポート
	tolua_luafunc_open(m_L);
	SetLua( m_L );

	// print関数を設定
	InitPrintFunc();

	// toluaでCの関数やクラスをインポート
	tolua_luafunc_open(m_L);

}

// Luaステートを閉じる
void LuaHelper::Close() {
	if (m_L)
	{
		lua_close(m_L);
		m_L = NULL;
	}
}

// Luaステートをセットする
// 同時に、debug.tracebackの実装へのポインタを得る
// （このため、Luaライブラリオープン後が望ましい）
void LuaHelper::SetLua(lua_State *L) {
	m_L = L;
	lua_getglobal(L, "debug");
	if (!lua_isnil(L, -1)) {
		lua_getfield(L, -1, "traceback");
		m_pGetStackTraceFunc = lua_tocfunction(L, -1);
	}
}

// print関数を設定
void LuaHelper::InitPrintFunc() {
	// Windows以外なら標準のもの(stdout出力）で良い
#ifdef _WIN32
	lua_register(m_L, "print", LuaHelper::LuaPrintWindows);
	lua_atpanic(m_L, LuaHelper::LuaPrintWindows);
#endif
}

#ifdef _WIN32
// print関数実装：VC++のメッセージとして出力
int LuaHelper::LuaPrintWindows(lua_State *L) {
	int count = lua_gettop(L);
	lua_getglobal(L, "tostring");
	for (int i=0 ; i<count ; i++) {
		lua_pushvalue(L, -1);
		lua_pushvalue(L, i+1);
		lua_call(L, 1, 1);
		const char *str = lua_tostring(L,-1);
		OutputDebugStringA((str) ? str : "");
		if (i != 0) OutputDebugStringA("\t");
		lua_pop(L, 1);
	}
	OutputDebugStringA("\n");
	return 0;
}
#endif


// リターン値とスタックの値からエラーメッセージを設定
void LuaHelper::AnalyzeError(int res_call, const char *location) {
	const char * reason = "";
	switch( res_call ) {
	case LUA_ERRRUN: reason = "SCRIPT RUNTIME ERROR"; break;
	case LUA_ERRSYNTAX: reason = "SCRIPT SYNTAX ERROR"; break;
	case LUA_ERRMEM: reason = "SCRIPT MEMORY ERROR"; break;
	case LUA_ERRFILE: reason = "SCRIPT FILE ERROR"; break;
	default: break;
	}
	// エラーメッセージ取得
	const char *mes = lua_tostring(m_L, -1);
	char err_mes[1000];
	sprintf(err_mes, "%s : %s", reason, mes);
	SetErr(location, err_mes);
}

// 関数コール
// result,paramsはNULLでも良い
bool LuaHelper::CallFunc(const char *funcname, LuaFuncParam* result, int result_count, LuaFuncParam* params) {
	int old_top = lua_gettop(m_L);

	// 返り値はクリアしておく
	if (result) result->Clear();

	// ランタイムエラー処理関数を積む
	lua_pushcfunction(m_L, m_pGetStackTraceFunc);

	// 関数をみつける
	lua_getglobal(m_L, funcname);
	if (!lua_isfunction(m_L, -1)) {
		char location[300] = "";
		sprintf(location, "calling function<%s>", funcname);
		SetErr(location, "the function not found.");
		return false;
	}

	// paramsによって指定された可変個の引数をスタックに置く
	int params_count = 0;
	if (params) {
		params_count = params->PushToStack(m_L);
	}

	// Lua内の関数をコール
	int res_call = lua_pcall(m_L, params_count, result_count, old_top);

	// エラー処理
	if (res_call != 0) {
		// エラーメッセージ生成
		char location[300] = "";
		sprintf(location, "calling function<%s>", funcname);
		AnalyzeError(res_call, location);
		// スタックを元に戻す
		lua_settop(m_L, old_top);
		return false;
	}

	// 返り値解析
	if (result) result->GetFromStack(m_L, result_count);

	// スタックを元に戻す
	lua_settop(m_L, old_top);

	return true;
}

// ファイル実行
// result,paramsはNULLでも良い
bool LuaHelper::DoFile(const char *path, LuaFuncParam* result, int result_count, LuaFuncParam* params) {
	int old_top = lua_gettop(m_L);

	// 返り値はクリアしておく
	if (result) result->Clear();

	// ランタイムエラー処理関数を積む
	lua_pushcfunction(m_L, m_pGetStackTraceFunc);

	// ファイルをロード
	int res_load = luaL_loadfile(m_L, path);
	// エラー処理
	if (res_load != 0) {
		// エラーメッセージ生成
		char location[300] = "";
		sprintf(location, "loading file<%s>", path);
		AnalyzeError(res_load, location);
		lua_settop(m_L, old_top); // スタックを元に戻す
		return false;
	}

	// paramsによって指定された可変個の引数をスタックに置く
	int params_count = 0;
	if (params) {
		params_count = params->PushToStack(m_L);
	}

	// ロードされたチャンクをコール
	int res_call = lua_pcall(m_L, params_count, result_count, old_top+1);

	// エラー処理
	if (res_call != 0) {
		// エラーメッセージ生成
		char location[300] = "";
		sprintf(location, "executing file<%s>", path);
		AnalyzeError(res_call, location);
		lua_settop(m_L, old_top); // スタックを元に戻す
		return false;
	}

	// 返り値解析
	if (result) result->GetFromStack(m_L, result_count);

	// スタックを元に戻す
	lua_settop(m_L, old_top);

	return true;
}

// エラーメッセージをセットする
void LuaHelper::SetErr(const char *location, const char *message) {
	sprintf(m_err, "%s : %s", location, message);
}


bool LuaHelper::ChangeScene() {
	const char *funcname="change_scene";
	LuaFuncParam* result=NULL;
	int result_count=0;
	LuaFuncParam* params=NULL;
	int old_top = lua_gettop(m_L);

	// 返り値はクリアしておく
	if (result) result->Clear();

	// ランタイムエラー処理関数を積む
	lua_pushcfunction(m_L, m_pGetStackTraceFunc);

	// 関数をみつける
	lua_getglobal(m_L, funcname);
	if (!lua_isfunction(m_L, -1)) {
		char location[300] = "";
		sprintf(location, "calling function<%s>", funcname);
		SetErr(location, "the function not found.");
		return false;
	}

	// paramsによって指定された可変個の引数をスタックに置く
	int params_count = 0;
	if (params) {
		params_count = params->PushToStack(m_L);
	}

	// Lua内の関数をコール
	int res_call = lua_pcall(m_L, params_count, result_count, old_top);

	// エラー処理
	if (res_call != 0) {
		// エラーメッセージ生成
		char location[300] = "";
		sprintf(location, "calling function<%s>", funcname);
		AnalyzeError(res_call, location);
		// スタックを元に戻す
		lua_settop(m_L, old_top);
		return false;
	}

	// 返り値解析
	if (result) result->GetFromStack(m_L, result_count);

	// スタックを元に戻す
	lua_settop(m_L, old_top);

	return true;
}
}