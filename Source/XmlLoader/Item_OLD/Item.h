#pragma once
#include"GameObjectData/fwd.h"
#include<string>
#include<vector>
#include<sstream>
#include<boost/serialization/split_member.hpp>

#include"RTTI/RTTI.h"
class btCollisionObject;
namespace MMD{
	class HumanModel;
	typedef std::shared_ptr<HumanModel> HumanModelSharedPtr;
}

namespace Serialization{
namespace Item{
	//名前きにいらない
	//Item::Item
	//class Base;

	class Item;
	typedef std::shared_ptr<Item> ItemSharedPtr;

class Item{
public:
	//Kind
	enum ActionType {
		SWING,
		SHOT,
	};
	Item()
		:name_("名無し"),
		explanation_("なし"),
		action_(SWING)
	{};
	virtual ~Item(){}

	//virtual const RTTI & getRTTI() const = 0;

	const std::string & getName()const{
		return name_;
	}
	const std::string & getExplanation()const{
		return explanation_;
	}

	//virtual void setOwner( const GameObjectData::StatusSharedPtr & )=0;
	
	//build Accessories and Hooks.
	//add hook and accessory to model.
	virtual void buildAccessories( MMD::HumanModel*, btCollisionObject* owner,  const GameObjectData::StatusSharedPtr &ownerSt  )=0;
	
	//違う実装案
	//struct AccessoryData{
	//	GameObjectAccessory a;
	//	std::string equip_position;
	//	std::string animation;
	//	hook;
	//}
	//virtual AccessoryData createAccessoryData();

	//unsigned int id_;
	std::string name_;
	std::string explanation_;
	ActionType action_;
private:
	friend boost::serialization::access;
	//基底クラスのserialize関数を直接呼び出さないこと！！
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		using boost::serialization::make_nvp;
		ar & make_nvp("name",			name_ );
		ar & make_nvp("explanation",	explanation_ );
		ar & make_nvp("action",			action_ );
	}

};
}//end namespace Item
}//end namespace Serialization