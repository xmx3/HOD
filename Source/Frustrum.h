#pragma once
#include<d3dx9.h>



//点と視錐台との衝突判定を調べるクラス
class Frustrum {
public:
	Frustrum(const D3DXMATRIX &viewprojection);

	Frustrum(const Frustrum&) = delete;
	void operator=(const Frustrum&) = delete;

	//点が視錐台の中にあるか
	bool isInside(const D3DXVECTOR3 &point);

	//点が視錐台の中にないなら、
	//最近接点をoutClosestPointに代入
	//また最も近い平面をoutClosestPlane代入する
	//nullptrなら何もしない
	bool calculateClosestPoint(
		D3DXVECTOR3 *outClosestPoint,
		D3DXPLANE *outClosestPlane,
		const D3DXVECTOR3 &point);


	//下記indexが各平面に対応
	//	LEFT=0,
	//	RIGHT=1,
	//	UP=2,
	//	DOWN=3,
	//	NEAR=4,
	//	FAR=5
	//
	D3DXPLANE mPlane[6];
};

