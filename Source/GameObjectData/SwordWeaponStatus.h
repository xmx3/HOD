#pragma once
#include"IWeaponStatus.h"
#include<string>
#include<memory>
#include<sstream>
#include"fwd.h"

namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}

namespace GameObjectData {
class SwordWeaponStatus;
typedef std::shared_ptr<SwordStatus> SwordStatusSharedPtr;

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
	
	StatusWeakPtr me_;//owner_のほうが名前よろしくないですか？

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
