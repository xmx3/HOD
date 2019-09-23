#pragma once

#include"Sequence/HatuneOfTheDead/CppImpl/Child.h"
#include"GameObject/SharedPtrs.h"
#include<memory>

class Image;

namespace XmlLoader {
	namespace GameObject {
		class Enemy;
		typedef std::shared_ptr<Enemy> EnemySharedPtr;
		class Player;
	}
}


namespace MMD {
	class CameraAnimation;
}

namespace Sequence{
namespace HatuneOfTheDead{
namespace CppImpl{
class Parent;
class State;
class Ready : public Child{
public:
	Ready(State* state);
	~Ready();
	Base* update( Parent* );
private:
	//疑似的なwait()
	//使い方を気を付けること
	//コードの一か所でしか使えない
	//違う場所で使いたければ新たに関数と変数を定義すること
	bool wait30Frame() {
		if (mIsStartedForWait30) {
			if (mCount > 30) {
				return true;
			}
			//こうしておけばオーバーフローが起きない
			++mCountForWait30;
		}
		else {
			mIsStartedForWait30 = true;
			mCountForWait30 = 0;
			//オーバーフロー対策のためにカウントするのを後にしたため
			//ここで足しておく
			++mCountForWait30;

		}
		return false;
	}
	int mIsStartedForWait30;
	bool mCountForWait30;

	bool wait10Frame() {
		if (mIsStartedForWait10) {
			if (mCount > 10) {
				return true;
			}
			//こうしておけばオーバーフローが起きない
			++mCountForWait10;
		}
		else {
			mIsStartedForWait10 = true;
			mCountForWait10 = 0;
			//オーバーフロー対策のためにカウントするのを後にしたため
			//ここで足しておく
			++mCountForWait10;

		}
		return false;
	}
	int mIsStartedForWait10;
	bool mCountForWait10;




	XmlLoader::GameObject::Player *mPlayer;
	XmlLoader::GameObject::EnemySharedPtr mEnemy;



	State *mState;
	Image* mImage;
	int mCount;
	std::shared_ptr<MMD::CameraAnimation> mCameraAnimation;
	GameObject::StageSharedPtr	mStage;

};

}}} //namespace Sequence::HatuneOfTheDead::CppImpl
