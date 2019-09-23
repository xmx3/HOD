#include "XFile/Document.h"
#include "XFile/Parser.h"
#include<assert.h>
#include"Model.h"

namespace XFile{

Document::Document( const char* data, int size ) : mParser( 0 ){
//cout.begin();
	mParser = NEW Parser( data, size );
//cout.end();
}

Document::~Document(){
	SAFE_DELETE( mParser );
}

bool Document::isValid() const { 
	return mParser->isValid();
}

void Document::convertToString( string* s ) const {
	mParser->toString( s );
}

GameLib::PseudoXml::Document Document::toXml() const {
	assert( isValid() );
	return mParser->toXml();
}

std::tuple<
	MeshSharedArray,
	int
>
Document::createMeshArray(  const std::string & textureFileFolder  )const{
	assert( isValid() );
	return mParser->createMeshArray( textureFileFolder );
}


} //namespace XFile
