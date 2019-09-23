#pragma once
#include<d3dx9.h>
#include<string>
#include"Object/IObject.h"
#include<vector>

namespace MME{

class ControlObjectSelf{
public:
	//@param name : CONTROLOBJECTのnameアノテーションの値
	//現状selfのみ
	ControlObjectSelf( ID3DXEffect *effect , const std::string &name );
	~ControlObjectSelf();

	void send( ID3DXEffect *effect, Object::IObjectSharedPtr object );
private:
	std::string mName;
	
	D3DXHANDLE mhCanDraw;
	D3DXHANDLE mhScale;
	D3DXHANDLE mhOffset;
	D3DXHANDLE mhTransform;

	//ボーン名 : PMDモデルの指定ボーンの座標またはワールド変換行列を取得する。
	//　　　　 　型はfloat3,float4,float4x4のうちいずれか。
	//作るならば
	//std::vector<D3DXHANDLE> mBones;
	//とりあえず単位行列でも送っておくか？

	//表情名　 : PMDモデルの指定した表情の値を取得する。型はfloat。
	//作らない。改造範囲がMMDのCModelまで及ぶ。
	//めんどくさい
	
	//とりあえず、指定したファイル名のオブジェクトが存在しない場合、以下の値が設定される。の値を入れておこう
	std::vector<D3DXHANDLE> mFloats;//0.0
	std::vector<D3DXHANDLE> mFloat3s;//(0,0,0)
	std::vector<D3DXHANDLE> mFloat4s;//(0,0,0,1)
	std::vector<D3DXHANDLE> mMatricies;



	D3DXHANDLE mhX;		//"X"      : アクセサリの位置X(アクセサリパネルのX)。型はfloat。
	D3DXHANDLE mhY;		//"Y"      : アクセサリの位置Y(アクセサリパネルのY)。型はfloat。
	D3DXHANDLE mhZ;		//"Z"      : アクセサリの位置Z(アクセサリパネルのZ)。型はfloat。
	D3DXHANDLE mhXYZ;	//"XYZ"    : アクセサリの位置(アクセサリパネルのX,Y,Z)。型はfloat3。
	D3DXHANDLE mhRx;	//"Rx"     : アクセサリの回転X(アクセサリパネルのRx)。型はfloat。(※１）
	D3DXHANDLE mhRy;	//"Ry"     : アクセサリの回転Y(アクセサリパネルのRy)。型はfloat。
	D3DXHANDLE mhRz;	//"Rz"     : アクセサリの回転Z(アクセサリパネルのRz)。型はfloat。
	D3DXHANDLE mhRxyz;	//"Rxyz"   : アクセサリの回転(アクセサリパネルのRx,Ry,Rz)。型はfloat3。
	D3DXHANDLE mhSi;	//"Si"     : アクセサリのサイズ(アクセサリパネルのSi)。型はfloat。（※２）
	D3DXHANDLE mhTr;	//"Tr"     : アクセサリの透明度(アクセサリパネルのSi)。型はfloat。

	//・指定したファイル名のオブジェクトが存在しない場合、以下の値が設定される。
	//Xファイルの場合：
	//　スケーリング値　：10
	//　オフセット値　　：(0,0,0,1)
	//　ワールド変換行列：スケーリング行列（xyz各10倍）
	//　特殊item値　　　：0
	//PMDファイルの場合：
	//　スケーリング値　：1
	//　オフセット値　　：(0,0,0,1)
	//　ワールド変換行列：単位行列
	//　ボーンの座標　　：(0,0,0,1)
	//　ボーンの変換行列：単位行列
	//　表情値　　　　　：0
};

}