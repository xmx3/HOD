#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__
#include<GameLib/Framework.h>
class TimeManager{
public:
	static TimeManager* instance();
	static int getFrameRate() {
		return GameLib::Framework::frameRate();
	}
	void start() {
		mStart=GameLib::Framework::time();
	}
	int end() const {
		return GameLib::Framework::time()- mStart;
	}

private:
	TimeManager mThis;
	float mDeltaTime;
	int mStart;

};
#endif//__TIME_MANAGER_H__