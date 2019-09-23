#pragma once
#include<GameLib/GameLib.h>
#include<assert.h>
#include<GameLib/PseudoXml/Document.h>
#include<GameLib/PseudoXml/Element.h>
#include<GameLib/PseudoXml/Attribute.h>
#include<GameLib/Base/RefString.h>

#include"helper/MyOutputDebugString.h"

#include<sstream>
#include<string>

namespace XmlHelperFuncs {
	using namespace GameLib::PseudoXml;
//孫まで探しにいかない
//見つからない場合は空のConstElementを返す
static ConstElement findElement( const ConstElement &e, const char *findElementName ){
	int numChild = e.childNumber();
	for( int i=0; i<numChild; ++i ){
		if( GameLib::RefString(e.child(i).name()) == findElementName ){
			return e.child(i);
		}
	}

	std::string message(findElementName);
	message.append( " didn't found!" );
	TRACE1("%s\n", message.c_str());
	STRONG_ASSERT( false && "element didn't find!" );

	//空っぽを返す
	return ConstElement(); 
}

static const char* getVMDFileName( const ConstElement &elem ){
	int num=elem.attributeNumber();
	for( int i=0; i<num; ++i ){
		if( GameLib::RefString("vmdFile") == elem.attribute(i).name() ){
			return elem.attribute(i).value();
		}
	}
	STRONG_ASSERT( false && "vmdFile Attribute didn't find!" );

	return NULL;
}

//文字列( a.value() )を分析して"true"ならばtrueを返す
//"false"ならfalseを返す
//エラーが起きたらassertを起こし、falseを返す。
static bool setBool(bool *out, const ConstAttribute &a ){
	GameLib::RefString str( a.value() );
	if( str == "true" ){
		*out=true;
		return true;
	} else if( str == "false" ){
		*out=false;
		return true;
	} else {
		assert(false);
		return false;
	}
}

//バグあり
//streamを次のタグ位置まで進める
//見つけたタグ名を返す
//見つからなかった場合空文字列を返す+assert
static std::string advanceToNextTag( std::istream &is ){
	assert(false);
	while( !is.eof() ){
		std::streamoff pos = is.tellg();
		char c;
		is >> c;
		if( c=='<' ){
			std::string tag;
			is >> tag;
			int size = tag.size();
			if( tag[size-1]=='>' ){
				tag.erase( size-1 );
			}
			is.seekg( pos );
			return tag;
		}
	}

	assert(false && "xml file is wrong. not found <");
	return std::string();
}	


} //end namespace XmlHelperFuncs
