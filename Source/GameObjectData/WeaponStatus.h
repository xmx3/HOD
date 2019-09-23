#ifndef __GAMEOBJECTDATA_WEAPONSTATUS_H__
#define __GAMEOBJECTDATA_WEAPONSTATUS_H__

#include<vector>
#include<map>
#include<string>
#include"fwd.h"
#include"Status.h"

namespace boost{
	namespace serialization{
		class access;
	}
}

namespace GameLib{
	namespace FileIO {
		class InFile;
	}
	namespace PseudoXml {
		class ConstElement;
	}
}


namespace GameObjectData {


class AdditionalEffect{
public:
	virtual ~AdditionalEffect(){}
	virtual void exec( Status *st )=0;
};
//static std::map< std::string, AdditionalEffect* > gsAdditionalEffectMap;

//exvsとボーダーブレイク, saga参考
//saga


//DamageDataとかでもいいな
class WeaponStatus{
public:
	friend boost::serialization::access;
	
	WeaponStatus( StatusSharedPtr status );
	WeaponStatus();
	virtual ~WeaponStatus(){}


	unsigned char damageTypes;

	int atkHp;
	int atkMp;
	int atkLp;
	int atkStamina;
	
	unsigned char damageCorrectedRate;//ダメージ補正率
	unsigned char downValue;//ダウン値
	unsigned char staggerValue;//よろけ値
	float unControlableTime;//操作不可能時間、硬直時間

	//float knockBackNormalVel[3];
	float upDownwardOffset;//打ち上げ、たたきつけ攻撃のための値
	//float knockBackVelSpeed[3];//ぶっ飛び倍率 //いるか？
	
	//ヒットバックするときに与える値
	//こんな感じで使用
	//mRigidBody->applyCentralImpulse( dir*mMass*hitbackValue );
	float hitbackValue;

	//吹き飛ばすときに与える値
	//こんな感じで使用
	//mRigidBody->applyCentralImpulse( dir*mMass*hitbackValue );
	//float blowValue;
	
	unsigned short staminaPerAttack;//武器じゃなくてアニメーション行動にもたせた方がいい?

	bool canCollideOnlyOnce;

	StatusWeakPtr me;
	//std::vector<AdditionalEffect*> additionalEffects;
	//AdditionalEffect *additionalEffects;
	//unsigned char numAdditionalEffects

	bool loadBinary( const char *fileName );
	bool loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveBinary( const char *fileName );
	
	bool loadText( const char *fileName );
	bool loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveText( const char *fileName );
	
	bool loadXML( const char *fileName );
	bool loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveXML( const char *fileName );
	
	void print() const ;

	virtual int caluculateDamage()const;
	//me(Status) 以外をコピー
	//void copy( const WeaponStatus & );

private:
	//disallow assign
	//WeaponStatus( const WeaponStatus & );
	//disallow copy
	//void operator=( const WeaponStatus & );

	//基底クラスのserialize関数を直接呼び出さないこと！！
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver);
};

}//end namespace GameObjectData

#endif //__GAME_OBJECTDATA_WEAPONDATA_H__