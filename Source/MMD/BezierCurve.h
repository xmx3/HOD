#ifndef __BEZIERCURVE_H__
#define __BEZIERCURVE_H__
#include "MMDMacro.h"
namespace MMD {
	class BezierCurve {
	public:
		BezierCurve() :isLinear_(true) {}
		virtual ~BezierCurve() {};
		void init(float x1, float y1, float x2, float y2);
		float getInterValue(float fX);
	private:
		DISALLOW_COPY_AND_ASSIGN(BezierCurve);

		float getYValue(float fX, float fX1, float fY1, float fX2, float fY2);

#define	YVAL_DIV_NUM	16

		float	yValueCacheArray_[YVAL_DIV_NUM + 1];

		bool	isLinear_;
	};
}

#endif//__BEZIERCURVE_H__