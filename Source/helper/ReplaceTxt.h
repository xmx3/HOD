#pragma once
#include<string>

//  •¶Žš—ñ‚ð’uŠ·‚·‚é
static std::string replaceText( std::string source, const std::string &serach, const std::string &replaceStr )
{
    std::string::size_type  pos( source.find( serach ) );
		
    while( pos != std::string::npos )
    {
        source.replace( pos, serach.length(), replaceStr );
        pos = source.find( serach, pos + replaceStr.length() );
    }

    return source;
}
