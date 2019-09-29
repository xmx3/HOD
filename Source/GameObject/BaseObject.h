#pragma once
class btPersistentManifold;
class btCollisionObject;
#include"RTTI/RTTI.h"
#include"Component/RigidBodyComponent.h"
#include"GameObjectData/WeaponStatus.h"
#include<memory>



namespace GameObjectData {
	class WeaponStatus;
}

namespace GameObject {
	class BaseObject;
	typedef std::weak_ptr<BaseObject> BaseObjectWeakPtr;
	typedef std::shared_ptr<BaseObject> BaseObjectSharedPtr;
	

	//BaseActor
	//BaseGameObject
	//
	class BaseObject : public std::enable_shared_from_this<BaseObject> {
	public:
		BaseObject()=default;
		virtual ~BaseObject()=default;
	
		virtual const RTTI & getRTTI() const = 0
		{
			return rtti;
		}
		static const RTTI rtti;


		//ダメージ関連はどう実装しようか。迷った。
		//だが時間が限られていること、システムをシンプルにしたいこと
		//継承でインターフェイスを作り階層的な構造でシンプルに実装することにした
		//ほかの案としては
		//コンポーネントにする
		//デリゲーターを使う
		//イベント駆動にするといったue的な設計もプログラミングしてみたかったがとりあえず
		//ダメージを計算しないオブジェクトもいるしゲームエンジン的に考えれば分割させたほうが正しいのだろうが
		//HODしか使う気ないしこのエンジンはいろいろ書き直したい、再設計しなおしたいところもある。
		//HOD専用のゲームオブジェクトだと思えば問題ないでしょう
		//意思決定をコンピュータに任せるのではなく前もって行う。
		
		//ここでダメージ計算を行う、ヒットバック処理等はまた別の所で行う
		//バーチャルにする必要なし
		//現状BaseObjectの状態で呼ぶ気なし
		//引数BaseObjectにしているけどWeaponStatusだよね
		//virtual void takeDamage(
		//	BaseObject* DamageCauser
		//)=0;

		virtual int calculateDamage()=0;

		//ダメージを与えるオブジェクトかどうか？
		virtual bool canDamage() = 0;

		//ダメージを求めるのに使用
		//ダメージを与えるオブジェクトでなければnullを返すこともある
		virtual const GameObjectData::WeaponStatus* getWeaponStatus()=0;

		unsigned short mDamageGroup;
		unsigned short mDamageMask;		
	};


}
