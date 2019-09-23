#pragma once
#include<sstream>
#include<assert.h>
#include"fwd.h"

#include<boost/serialization/assume_abstract.hpp>

namespace boost{
	namespace serialization{
		class access;
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

}//end namespace GameObjectData