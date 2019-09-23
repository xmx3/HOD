#include"FileLoader.h"
#include<GameLib/GameLib.h>

#include<GameLib/FileIO/Manager.h>
#include<GameLib/FileIO/InFile.h>
#include<assert.h>
#include<string>

#include<GameLib/PseudoXml/Document.h>
#include<GameLib/PseudoXml/Attribute.h>
#include<GameLib/PseudoXml/Element.h>

#include<GameLib/Base/RefString.h>

#include"helper/XmlHelperFuncs.h"

namespace{
//bool isExtension(const std::string & s, const std::string &extension=".pmd" )
//{
//	int l = s.length();
//	if(l==0){
//		return false;
//	}
//	int pos = s.rfind(extension);
//	if( pos==std::string::npos ){
//		return false;
//	}
//	//std::cout << s << std::endl;
//	//std::cout << "len "<< l << std::endl;
//	//std::cout << "pos" << pos  << std::endl;
//	//std::cout << l - pos << std::endl;
//	return extension.length()==l-pos; 
//}

}


//void FileLoader::insert( const std::string& name, GameLib::FileIO::InFile file ){
//	FileMap::_Pairib pairib =
//		mName_File.insert( std::make_pair( name, file ) );
//	assert( pairib.second && "key doubled!" );
//}

void FileLoader::insert( const std::string& name ){
	GameLib::FileIO::InFile file = GameLib::FileIO::InFile::create( name.c_str() );

	FileMap::_Pairib pairib =
		mName_File.insert( std::make_pair( name, file ) );
	assert( pairib.second && "key doubled!" );
}

bool FileLoader::isFinished(){
	for( FileMap::iterator it=mName_File.begin(), end=mName_File.end(); it!=end; ++it ){
		if(!it->second.isFinished()){
			return false;
		}
		
	}
	return true;
}
GameLib::FileIO::InFile FileLoader::get(  const std::string& name ){
	return mName_File.find( name )->second;
}
//

/*-----------------------
<Files>
  <File name = "Data/MMDData/pmd/ミクダヨーver102_1/ミクダヨーver102_1（MMO用）.pmd" />
  <File name = "Data/MMDData/vmd/mikudayo_run.vmd" />
  <File name = "Data/MMDData/vmd/mikudayo_walk.vmd" />
  <File name = "Data/MMDData/vmd/mikudayo_stand.vmd" />
</Files>
------------------------*/
	//上記の形式のxmlファイルを登録する
//パースするのは別クラスだろ
//void FileLoader::loadFromXML( const std::string &xmlfilename ){
//	using GameLib::RefString;
//	using namespace GameLib::PseudoXml;
//	using namespace XmlHelperFuncs;
//
//
//	GameLib::FileIO::InFile xmlFile;
//	xmlFile= GameLib::FileIO::InFile::create( xmlfilename.c_str() );
//	if( xmlFile.isError() ){
//		STRONG_ASSERT(false);
//		return;
//	}
//	while( !xmlFile.isFinished() ){}
//
//	Document modelXml = Document::create( xmlFile.data(), xmlFile.size() );
//	if( modelXml.isError() ){
//		STRONG_ASSERT(false);
//		return;
//	}
//
//	ConstElement filesElem= findElement( modelXml.root(), "Files" );
//	int numElems = filesElem.childNumber();
//	for( int ie=0; ie<numElems; ++ie ){
//		ConstElement file = filesElem.child(ie);
//		if( RefString("File")==file.name() ){
//			
//			int numAttributes = file.attributeNumber();
//			assert( numAttributes == 1 );
//			for( int ia=0; ia<numAttributes; ++ia )
//			{
//				ConstAttribute & a = file.attribute(ia);
//				const char *attributeName = a.name();
//				if( RefString("name") == attributeName ){
//					insert( a.value() );
//				} else {
//					TRACE1( "this attribute name is wrong! %s\n", attributeName ); 
//					STRONG_ASSERT( false );
//				}
//			}
//
//		}else{
//			STRONG_ASSERT(false && "element name is wrong!" );
//		}
//	}
//}
//

FileLoader::FileNameList FileLoader::getAllFileNames(){
	FileNameList result;
	for( FileMap::iterator it=mName_File.begin(), end=mName_File.end(); it!=end; ++it ){
		result.push_back( it->first );
		
	}
	return result;

}

