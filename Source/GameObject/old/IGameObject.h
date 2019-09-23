#pragma once
#include<memory>
#include"RTTI/RTTI.h"
#include<LinearMath/btTransform.h>
#include"GameObjectData/WeaponStatus.h"



namespace GameObject {
typedef unsigned int GameObjectId;

class IGameObject : public std::enable_shared_from_this<IGameObject>
{
public:
	//shared_ptrを返す create()を作ること
	//friend PlayerSharedPtr createPlayer();を宣言しておいて
	//createPlayer()にするべきか？グローバル関数型
	//Player::create()にするべきか？
	//
	//上のほうがファイル依存が少ないから上かな。Playerを知らなくてもいい
	//下はクラス内に入っているから、Playerを知らなくてはならない。
	
	//共変戻り値を返す静的仮想関数を作るように強制したいが、
	//スマートポインタを使っている限り無理
	//static  virtual IColliderSharedPtr create( IArgs* args )=0;

	virtual ~IGameObject() {}

	static IGameObject* cast(void *vp){
		return static_cast<IGameObject*>( vp );
	}

	GameObjectId getID() const{
		return mId;
	}
	
	RTTI_DECL;

	virtual const btTransform & getWorldTransform() const= 0;

	virtual btTransform & getWorldTransform()=0;
	void setWeaponStatus( GameObjectData::WeaponStatusSharedPtr weaponStatus )
	{
		mWeaponStatus = weaponStatus;
	}

	GameObjectData::WeaponStatusSharedPtr getWeaponStatus()const{
		return mWeaponStatus;
	}

	GameObjectData::StatusSharedPtr	getStatus()const{
		return mStatus;
	}

	void copyWeaponStatus( const GameObjectData::WeaponStatusSharedPtr &src );
	void copyWeaponStatus( const GameObjectData::WeaponStatus &src );

	//一回だけしか衝突しない場合
	bool canCollideOnlyOnce();
	
	void attack( GameObjectData::Status* );

protected:
	//shared_from_thisを使うためprotected
	//必ず、shared_ptrを使い、shared_ptrで管理しなければならない
	//オブジェクトを作成するのはcreate();
	IGameObject();

	static unsigned int getGameObjectsNum(){ return sNum; }
	
	GameObjectData::StatusSharedPtr		mStatus;	
	GameObjectData::WeaponStatusSharedPtr	mWeaponStatus;

private:
	//disallow
	IGameObject( const IGameObject& )=delete;
	void operator=( const IGameObject& )=delete;

	static unsigned int sNum;
	const GameObjectId mId;
};
}//end namespace