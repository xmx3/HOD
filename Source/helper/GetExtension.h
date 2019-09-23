#pragma once
#include<string>
#include<assert.h>

static std::string getExtension( const std::string &src){
	int index = src.rfind( ".", src.size());
	if( index == std::string::npos){
		assert( false && "Šg’£q‚ª‘¶İ‚µ‚È‚¢");
	}
	std::string str;
	str = src.substr( index + 1);
	return str;
}