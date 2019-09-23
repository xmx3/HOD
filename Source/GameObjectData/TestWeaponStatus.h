#pragma once
#include<vector>
#include<map>
#include<string>
#include<memory>
#include<sstream>
#include <boost/serialization/assume_abstract.hpp>

#include"fwd.h"

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

namespace GameObjectData {

//class AdditionalEffect{
//public:
//	virtual ~AdditionalEffect(){}
//	virtual void exec( Status *st )=0;
//};
//static std::map< std::string, AdditionalEffect* > gsAdditionalEffectMap;

//exvsとボーダーブレイク, saga参考
//saga



class IWeaponStatus{
public:
	//IWeaponStatus( StatusSharedPtr status );
	IWeaponStatus()
		:hitbackValue_(0.f), 
		canCollideOnlyOnce_(false)
	{};
	virtual ~IWeaponStatus(){}

	virtual void attack( Status* st )=0;

	virtual void print( std::ostringstream &ss )const{
		assert(false);
	}

	//純粋仮想関数にする意味ないだろ。実装同じだし
	//u-nn
	//オブジェクトを吹き飛ばすか
	//オブジェクトを後ろに下がらすか？
	bool canHitBack()const{
		return hitbackValue_!=0.f;
	}

	bool canCollideOnlyOnce()const{
		return canCollideOnlyOnce_;
	}

	//ヒットバックするときに与える値
	//こんな感じで使用
	//mRigidBody->applyCentralImpulse( dir*mMass*hitbackValue );
	float hitbackValue_;
	bool canCollideOnlyOnce_;


private:
	//disallow assign
	IWeaponStatus( const IWeaponStatus & );
	//disallow copy
	void operator=( const IWeaponStatus & );

	friend boost::serialization::access;
	//基底クラスのserialize関数を直接呼び出さないこと！！
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		using boost::serialization::make_nvp;
		ar & make_nvp("hitbackValue",			hitbackValue_ );
		ar & make_nvp("canCollideOnlyOnce",		canCollideOnlyOnce_ );
	}
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(IWeaponStatus)


class SwordWeaponStatus : public IWeaponStatus {
public:
	SwordWeaponStatus();
	SwordWeaponStatus( StatusSharedPtr status );
	virtual ~SwordWeaponStatus(){}
	friend boost::serialization::access;
	
	//DamageTypeでビット演算フラグ管理
	unsigned char damageTypes_;

	int atk_;

	float damageCorrectedRate_;//ダメージ補正率
	unsigned char downValue_;//ダウン値
	unsigned char staggerValue_;//よろけ値
	float unControlableTime_;//操作不可能時間、硬直時間

	//一回攻撃するごとに使用するスタミナ
	unsigned short stamina_;
	
	std::string accessoryName_;
	int hitStartFrame_;
	int hitEndFrame_;
	//武器の出し入れは別のところで管理しよう
	//int drawStartFrame_;
	//int drawEndFrame_;
	std::string equipBoneName_;
	
	StatusWeakPtr me_;

	//std::vector<AdditionalEffect*> additionalEffects;
	//AdditionalEffect *additionalEffects;
	//unsigned char numAdditionalEffects

	bool loadBinary( const char *fileName );
	bool loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveBinary( const char *fileName )const;
	
	bool loadText( const char *fileName );
	bool loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveText( const char *fileName )const;
	
	bool loadXML( const char *fileName );
	bool loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveXML( const char *fileName )const;
	
	void print( std::ostringstream &ss ) const;
	
	//me(Status) 以外をコピー
	void copy( const SwordWeaponStatusSharedPtr &src ){
		hitbackValue_ 				= src->hitbackValue_; 
		canCollideOnlyOnce_			= src->canCollideOnlyOnce_; 
		damageTypes_				= src->damageTypes_; 
		atk_ 						= src->atk_;
		damageCorrectedRate_		= src->damageCorrectedRate_; 
		downValue_  				= src->downValue_;
		staggerValue_	 			= src->staggerValue_; 
		unControlableTime_			= src->unControlableTime_; 
		stamina_					= src->stamina_;
		accessoryName_				= src->accessoryName_;
		hitStartFrame_				= src->hitStartFrame_;
		hitEndFrame_				= src->hitEndFrame_;
		equipBoneName_				= src->equipBoneName_;
	}

	//対象にダメージを与える
	virtual void attack( Status *enemy);

private:
	//disallow assign
	SwordWeaponStatus( const SwordWeaponStatus & );
	//disallow copy
	void operator=( const SwordWeaponStatus & );


	//基底クラスのserialize関数を直接呼び出さないこと！！
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		using boost::serialization::make_nvp;
		// save/load base class information
		ar & make_nvp("IWeaponStatus", boost::serialization::base_object<IWeaponStatus>(*this) );
		ar & make_nvp("damageTypes",			damageTypes_ );
		ar & make_nvp("atk",					atk_ );
		ar & make_nvp("damageCorrectedRate",	damageCorrectedRate_ );
		ar & make_nvp("downValue",				downValue_ ); 
		ar & make_nvp("staggerValue",			staggerValue_ );
		ar & make_nvp("unControlableTime",		unControlableTime_ );
		ar & make_nvp("stamina",				stamina_ );
		ar & make_nvp("accessoryName",			accessoryName_ 	);	
		ar & make_nvp("hitStartFrame",			hitStartFrame_	);
		ar & make_nvp("hitEndFrame",			hitEndFrame_	);
		ar & make_nvp("equipBoneName",			equipBoneName_	);
	}
};
}//end namespace GameObjectData
