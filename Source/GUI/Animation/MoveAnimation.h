#pragma once

#include"IAnimation.h"

namespace GUI{
	namespace Animation {

class MoveAnimation : public IAnimation {
public:
	MoveAnimation( 
		float startTime, float endTime,
		int startX, int startY,
		int endX, int endY);
	~MoveAnimation();

	void update( float dt , IComponent* );
	bool isOver()const;
private:
	float mStart, mEnd, mTime;
	int mEndX, mEndY;
	int mStartX, mStartY;

};
	}// end namespace Animation
}// end namespace GUI