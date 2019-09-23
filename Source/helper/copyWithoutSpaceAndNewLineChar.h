#pragma once
static void copyWithoutSpaceAndNewLineChar( std::string *dst, const std::string & src ){
	dst->clear();
	for( 
			std::string::const_iterator it=src.begin(), end=src.end();
			it!=end;
			++it )
	{
		if(
			*it=='\n' ||
			*it=='\r' ||
			*it== '\t' ||
			*it==' '  ||
			*it=='@' ){
			continue;
		}
		dst->push_back(*it);
	}
}
