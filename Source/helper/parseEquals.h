#pragma once
#include<string>
#include<assert.h>
#include<vector>
#include"helper/DeleteSpace.h"

//"left = right;"といった文字列を分割しセミコロンの次を返す
//最終行の場合セミコロンがない場合がある
static const char* parseEquals( const char *line, std::string *left, std::string *right ){

	const char* semicolonPos = strchr( line, ';' );
	//not found
	//assert( semicolonPos && "';' must be exist." );
	
	//std::cout << "line :  " << std::string( script, semicolonPos ) << std::endl;

	const char* eqPos = strchr( line, '=' );
	//空行の場合やスクリプトの終わりの場合
	if( eqPos==0 ){
		std::string temp(line);
		deleteExtraChars(&temp);
		assert(temp.empty());
		return eqPos;
	}
	left->assign( line, eqPos );
	deleteExtraChars( left );
	//std::cout << "command: " <<command << std::endl;
	//std::cout << "operand: " << operand << std::endl;
	
	if(semicolonPos==0){
		right->assign( eqPos+1 );
		deleteExtraChars( right );
		return semicolonPos;
	}else{
		right->assign( eqPos+1, semicolonPos );
		deleteExtraChars( right );
		return semicolonPos+1;
	}
} 