#pragma once
#ifndef __GAMEOBJECTDATA_STATUS_H__
#define __GAMEOBJECTDATA_STATUS_H__
#include<assert.h>
#include<algorithm>
#include"fwd.h"
#include"helper/RangeNumber.h"

namespace boost{
	namespace serialization{
		class access;
	}
}

namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}

namespace GameObjectData{
	
class Status {
public:
	static StatusSharedPtr create(){
		StatusSharedPtr st( new Status() );
		return st;
	}
	Status();
	virtual ~Status(){}

	StatusSharedPtr clone()const;

	//基底クラスのserialize関数を直接呼び出さないこと！！
	friend class boost::serialization::access;
	

	RangeNumber<float> hp;
	RangeNumber<float> mp;
	RangeNumber<float> lp;
	RangeNumber<float> stamina;
	
	RangeNumber<float> str;
	RangeNumber<float> inte;
	RangeNumber<float> will;
	RangeNumber<float> dex;
	RangeNumber<float> qui;
	RangeNumber<float> vit;
	RangeNumber<float> psy;
	RangeNumber<float> luck;

	float mass;

	//3種類のスピードを持つようにしておく
	//使い方は実装による
	//playerの場合
	//非戦闘時と戦闘時の歩きのスピードに使う
	float speedLow;
	float speed;
	float speedHigh;

	float jumpSpeed;

	float angleSpeed;//角速度

	float accel;

	//スタミナの使用量	
	float usageStaminaPerSecSpeedLow;	// 単位 stamina/seccond
	float usageStaminaPerSecSpeed;		// 単位 stamina/seccond
	float usageStaminaPerSecSpeedHigh;	// 単位 stamina/seccond
	float usageStaminaPerJump;			// 単位 stamina/jump
	float healingStaminaPerSec;//回復量
	
	//属性防御
	unsigned int elementalDefs;


	unsigned short downValue;
	unsigned short staggerValue;
	float elapsedTimeAfterDamaged;
	
	unsigned char group;

	unsigned char damageCorrectedRate;

	//剛体
	bool canStagger;//superArmor
	
	//全状態からLyingに移行できるように

	//硬直
	//ヒットストップ
	//ガード
	//削り

	float unContrableTime;
	float mutekiTime;//invincibleTime;
	
	//超必殺技ゲージ
	//覚醒
	//オーラ
	unsigned char powerGauge;
	
	bool loadBinary( const char *fileName );
	bool loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveBinary( const char *fileName );
	
	bool loadText( const char *fileName );
	bool loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveText( const char *fileName );
	
	bool loadXML( const char *fileName );
	bool loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveXML( const char *fileName );

	void reset();

	void update( float dt );
	
	//it return true, if it is died.
	bool isDied()const{
		return hp <= 0;
	}
	//基本は　この式返す。elemDef(0-254) * vit * (100 + vitRate) / 100;
	//だが、属性防御値がmaxの場合　unsigned int max(-1)を返す;
	//unsigned int calcDef( unsigned char damageTypes ) const {
	//	char num=0;
	//	unsigned char elementalDef = 0;

	//	for( char i=0; i<16 ; ++i ){
	//		if(  1 & (damageTypes>>i) ){
	//			num+=1;
	//			elementalDef += ( ( 0xf << (4*i) ) & elementalDefs ) >> (4*i) ;
	//		}
	//	}
	//	//0-15 を 0-255
	//	unsigned char averageDef = num==0 ? 0 : elementalDef*17/num;
	//	unsigned int def = averageDef==255 ? -1 : averageDef * vit  / 100;
	//	return def;
	//}

	bool emptyStamina()const;
	bool overStamina( const float &usageStamina )const{
		return stamina < usageStamina;
	}
	bool overOrEqualStamina( const float & usageStamina )const{
		return stamina <= usageStamina;	
	}

	bool canJump()const{
		return stamina >= usageStaminaPerJump;
	}

	bool canRunHighSpeed( const float & elapsedTime )const{
		return stamina >= usageStaminaPerSecSpeedHigh * elapsedTime;
	}

	bool canRun( const float & elapsedTime )const{
		return stamina >= usageStaminaPerSecSpeedLow * elapsedTime;
	}
	bool canWalk( const float & elapsedTime )const{
		return stamina >= usageStaminaPerSecSpeedLow * elapsedTime;
	}

	void jump(){
		assert( canJump() );
		stamina.add( -usageStaminaPerJump );
	}

	void runHighSpeed( const float & elapsedTime ){
		assert( canRunHighSpeed( elapsedTime ) );
		stamina.add(-usageStaminaPerSecSpeedHigh * elapsedTime );
	}

	void run( const float & elapsedTime ){
		assert( canRun(elapsedTime) );
		stamina.add(-usageStaminaPerSecSpeed * elapsedTime);
	}
	void walk( const float & elapsedTime ){
		assert( canWalk(elapsedTime) );
		stamina.add(-usageStaminaPerSecSpeedLow * elapsedTime);
	}

	void healStamina( const float & elapsedTime ){
		stamina.add(healingStaminaPerSec * elapsedTime);
	}

	float getSpeed() const {
		return speed;
	}

	float getSpeedHigh() const {
		return speedHigh;
	}
	float getSpeedLow() const {
		return speedLow;
	}

	float getAngleSpeed()const {
		return angleSpeed;
	}

private:
	//基底クラスのserialize関数を直接呼び出さないこと！！
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver);
	template<class Archive>
	void load(Archive& ar, const unsigned int version);
	template<class Archive>
	void save(Archive& ar, const unsigned int version)const;


	//clone関数実装のためクラス内では許可する
	Status(const Status &) = default;
	//禁止
	void operator=(const Status &) = delete;
};

}//end GameObjectData
#endif //__GAMEOBJECTDATA_STATUS_H__