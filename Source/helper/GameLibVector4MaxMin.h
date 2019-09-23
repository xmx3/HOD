#pragma once
#include<GameLib/GameLib.h>

	static GameLib::Vector4 max(
		const GameLib::Vector4 &a,
		const GameLib::Vector4 &b ){
			return GameLib::Vector4(
				std::max( a.x, b.x ),
				std::max( a.y, b.y ),
				std::max( a.z, b.z ),
				std::max( a.w, b.w ) );
	}

	static GameLib::Vector4 min(
		const GameLib::Vector4 &a,
		const GameLib::Vector4 &b ){
			return GameLib::Vector4(
				std::min( a.x, b.x ),
				std::min( a.y, b.y ),
				std::min( a.z, b.z ),
				std::min( a.w, b.w ) );
	}
