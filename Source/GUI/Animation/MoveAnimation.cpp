#include"MoveAnimation.h"
#include"../IComponent.h"
#include<assert.h>

namespace GUI{
	namespace Animation {

namespace{
	float lerp( int start, int end, float t ){
		return start+(end-start)*t;
	}
}

MoveAnimation::MoveAnimation( 
	float startTime, float endTime,
	int startX, int startY,
	int endX, int endY )
	:mStartX(startX),mStartY(startY),
	mEndX(endX),mEndY(endY),
	mStart(startTime), mEnd(endTime),
	mTime(0.f)
{
}
MoveAnimation::~MoveAnimation(){}


void MoveAnimation::update(float dt, IComponent* co)
{
	IPos* pos = dynamic_cast<IPos*>(co);
	assert( pos );
	mTime+=dt;
	if( pos &&
		mTime<mEnd )
	{
		if(mTime>mStart){
			float t = (mTime-mStart)/(mEnd-mStart);
			pos->setPos( 
				static_cast<int>( lerp( mStartX, mEndX, t ) ),
				static_cast<int>( lerp( mStartY, mEndY, t ) )
			);
		}
	}
}

bool MoveAnimation::isOver()const
{
	return mTime>=mEnd;
}

	}// end namespace Animation
}// end namespace GUI