#pragma once

#include<btBulletCollisionCommon.h>
#include<cmath>


//y軸無限の円柱でbtCollisionObjectを制限する。
//範囲外にいた場合演習内に無理やり移動させる
//そうした場合mmd のrigidbodyはどうなる
void limitMovableArea(
	btCollisionObject* obj,
	const btVector3 &center,
	float radius) 
{
	assert(false && "途中で必要なくなったのでデバッグしてない");
	//参照にしてる気を付けて
	btVector3 &rPos = obj->getWorldTransform().getOrigin();

	const float &px = rPos.x();
	const float &pz = rPos.z();

	const float &cx = center.x();
	const float &cz = center.z();

	const float &diffx = px - cx;
	const float &diffz = pz - cz;
	float distance2 = std::powf(diffx, 2) + std::powf(diffz, 2);


	float distance = std::powf(distance2, 0.5f);

	//非数になる場合がありそう

	if (distance == 0.f && distance <= 0.0001f) {
		return;
	}
	
	//ここらへん怪しい
	if (distance > radius) {
		rPos.setX(cx + diffx*radius / distance);
		rPos.setZ(cz + diffz*radius / distance);
		//ここめり込んだらどうする
		//坂とかどうするの？

	}
}