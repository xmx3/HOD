#pragma once
#include<map>
#include"Item.h"
#include<string>
#include<assert.h>
#include<unordered_map>

namespace Serialization{ namespace Item{
class Smith{
public:
	ItemSharedPtr get( const std::string &name );
	void init( const std::string &filename );
	bool isReady();
private:
	std::unordered_map<std::string, ItemSharedPtr> mItemTable;
};
} }//end namespace Serialization::Item