#include "BezierCurve.h"

#include <assert.h>
#include <cmath>

namespace MMD {
	void BezierCurve::init(float x1, float y1, float x2, float y2)
	{
		if (x1 == y1 && x2 == y2)
		{
			isLinear_ = true;
		}
		else
		{
			x1 = (x1 / 127.0f) * 3.0f;
			y1 = (y1 / 127.0f) * 3.0f;

			x2 = (x2 / 127.0f) * 3.0f;
			y2 = (y2 / 127.0f) * 3.0f;

			// 高速化のためテーブル化しておく
			yValueCacheArray_[0] = 0.0f;
			yValueCacheArray_[YVAL_DIV_NUM] = 1.0f;

			float	fAddX = 1.0f / (float)YVAL_DIV_NUM;

			for (int i = 1; i < YVAL_DIV_NUM; i++)
			{
				yValueCacheArray_[i] = getYValue(fAddX * i, x1, y1, x2, y2);
			}

			isLinear_ = false;
		}
	}

	//------------------------
	// X値に対応するY値を返す
	//------------------------
	float BezierCurve::getYValue(float fX, float fX1, float fY1, float fX2, float fY2)
	{
		float	fT = fX;
		float	fInvT = 1.0f - fT;

		for (int i = 0; i < 32; i++)
		{
			float	fTempX = fInvT*fInvT*fT*fX1 + fInvT*fT*fT*fX2 + fT*fT*fT;

			fTempX -= fX;
			if (fabsf(fTempX) < 0.0001f)
			{
				break;
			}
			else
			{
				fT -= fTempX * 0.5f;
				fInvT = 1.0f - fT;
			}
		}

		return fInvT*fInvT*fT*fY1 + fInvT*fT*fT*fY2 + fT*fT*fT;
	}

	//==================
	// 曲線補間値を返す
	//==================
	float BezierCurve::getInterValue(float fX)
	{
		assert(fX >= 0 && fX <= 1 && "fX must be between 0 and 1.");
		if (isLinear_)	return fX;	// 線形補間

		// テーブルを線形補間する
		fX *= (float)YVAL_DIV_NUM;

		int		iIdx = (int)fX;

		fX -= iIdx;

		return yValueCacheArray_[iIdx] * (1.0f - fX) + yValueCacheArray_[iIdx + 1] * fX;
	}
}