#pragma once
#ifndef __INPUT_PLAYERMOUSE_H__
#define __INPUT_PLAYERMOUSE_H__

#include<LinearMath/btVector3.h>
#include<memory>

namespace GameObject {
	class BaseObject;
	typedef std::weak_ptr<BaseObject> BaseObjectObjectWeakPtr;
}

namespace GameLib{
	namespace Scene{
		class Model;
	}
}

class btCollisionObject;


namespace Input{
/*
	実装方法として
		btGhostPairCacheObject* を使う方法
			毎回場所と入っているやつを更新して、bulletphisicsManagerのonEnter,onExit見たいな実装方法にするのもあり
			下はPairでなくても良いね。
		
			typedef std::pair< btCollisionObject*, btCollisionObject* > CollisionPair;
			typedef std::set< CollisionPair > CollisionPairs;
			CollisionPairs							previousCollisionPairs_;
			CollisionPairs							clickedCollisionPairs_;

		レイを飛ばす方法

		contactPairTest

		playerはcontactPairTestがはやそう

		問題は複数のオブジェクトが接触している場合をどうするか？
			レイがやりやすい

		レイでやる

//playerと循環参照になりそうで怖い
//IColliderSharedPtr mOnObjectがplayerのとき削除できますか？
//ということで
//IColliderWeakPtrにした。

*/
class PlayerMouse {
public:
	PlayerMouse( btCollisionObject* player, float radius );
	~PlayerMouse();
	
	void update(const float elapsedTime);

	// velocity = currentPos - oldPos	
	bool isFlickedPlayer( int *velocityX, int *velocityY )const;
	bool isFlicked( int *velocityX, int *velocityY )const;

	bool onPlayer()const;
	//Q 範囲内にgameObjectがいる場合の選択しているオブジェクトの優先度をどうする。
	//A カメラからの距離に近いオブジェクト（プレイヤーから近いオブジェクトもありかなと思った）
	bool onObject()const;
	
	bool isTriggeredPlayer()const;
	bool isTriggeredObject()const;
	bool isClickingPlayer()const;	
	bool isClickingObject()const;	
	bool isReleasedPlayer()const;
	bool isReleasedObject()const;

	GameObject::BaseObjectObjectWeakPtr  getOnObject();
	GameObject::BaseObjectObjectWeakPtr getDragingObject();

	//GameObject::IColliderSharedPtr getOnObject()const;
	//GameObject::IColliderSharedPtr getDragingObject()const;

	btVector3 getPos()const;

	bool isModeChangeButtonPushed() const;

	void drawMousePos( int color=0xffffffff ) const;
private:
	PlayerMouse( const PlayerMouse & );
	void operator=( const PlayerMouse & );
	
	int mClickedPos[2];
	int mClickedFrame;;
	
	bool mIsOnPlayer;

	//playerをクリックしたか
	bool mHasClickedOnPlayer;

	//初期化するか
	bool mIsInit;

	btVector3 mMousePos;
	btVector3 mClickedMousePos;
	float mMouseRadius;
	
	btCollisionObject *mPlayerBtObject;

	GameObject::BaseObjectObjectWeakPtr mOnObject;
	GameObject::BaseObjectObjectWeakPtr mDragingObject;

	GameLib::Scene::Model *mArrowModel;

};

}//end namespace Input
#endif
