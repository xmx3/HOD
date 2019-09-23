#pragma once
#include<memory>

class btPersistentManifold;
class btCollisionObject;

namespace GameObject{
namespace OldPlayer{
class Player;
namespace Updater{
	class IUpdater;
	typedef std::shared_ptr<IUpdater> IUpdaterSharedPtr;

	enum State{
		QV_STAND,
		QV_RUN,
		QV_JUMP,
		QV_SWING,
		TPS_STAND,
		TPS_RUN,
		TPS_STEP,
		TPS_SWING,
		TPS_SHOT,
		CAR_STAND,
		CAR_RUN
	};

	//const char* getStateName( const State &state );

//class IParam{
//public:
//	IParam(){}
//	virtual ~IParam(){}
//	virtual State getState()const=0; 
//};

class IUpdater {
public:
	IUpdater(Player* player)
		:mPlayer(player)
	{}
	virtual ~IUpdater(){}

	//いろいろメリットはあるけど、
	//(このインターフェイスだけでほぼ必要としていることが一つの関数で出来る)
	//拡張性しやすい
	//dynamic_castの処理がいやだ
	//あらたなParamを作るのがめんどくさい
	//virtual void init( IParam* )=0;
	
	//virtual void init()=0;

	virtual void update(float elapsedTime)=0;
	
	//virtual bool canStart();
	//virtual void start();//init();
	//bool startIfCan();

	virtual State getState()const=0;
	//const char* getStateName()const{
	//	return getStateName( getState() );
	//}

	//ダメージ食らったとき、状態移行するため
	virtual void onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ){}
	virtual void onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ){}
	virtual void onCollisionExit( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj ){}
protected:
	Player *mPlayer;
private:
	IUpdater( const IUpdater & );
	void operator=( const IUpdater & );
};

/*
class Player::StandingUpdater : public IPlayerUpdater {
public:
	virtual ~StandingUpdater(){}
	virtual void operator()(Player*);
};
class Player::RunningUpdater : public IPlayerUpdater {
public:
	virtual ~RunningUpdater(){}
	virtual void operator()(Player*);

};
class Player::ChasingUpdater : public IPlayerUpdater {
public:
	virtual ~ChasingUpdater(){}
	virtual void operator()(Player*);
};
class Player::AttackingShortRangeUpdater : public IPlayerUpdater {
public:
	AttackingShortRangeUpdater()
		:mIsNext(false),
		mState(COMBO1)
	{}
	virtual ~AttackingShortRangeUpdater()
	{}
	virtual void operator()(Player*);
	void update1( Player* );
	void update2( Player* );
	void update3( Player* );
private:
	enum State {
		COMBO1,
		COMBO2,
		COMBO3
	};
	State mState;
	bool mIsNext; 
	float mEndFrame;

};
class Player::AttackingLongRangeUpdater : public IPlayerUpdater {
public:
	virtual ~AttackingLongRangeUpdater(){}
	virtual void operator()(Player*);
};
class Player::StumblingUpdater : public IPlayerUpdater {
public:
	virtual ~StumblingUpdater(){}
	virtual void operator()(Player*);
};
class Player::LyingUpdater : public IPlayerUpdater {
public:
	virtual ~LyingUpdater(){}
	virtual void operator()(Player*);
};

class Player::SwingUpdater : public IPlayerUpdater {
public:
	SwingUpdater();
	virtual ~SwingUpdater(){}
	virtual void operator()(Player*);
private:
	unsigned int mClickedNum;
	unsigned int mCurrentIdx;
};
*/

}//end namespace Updater{

}// end namespace Player{
}//end namespace GameObject
