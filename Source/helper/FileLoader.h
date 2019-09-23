#ifndef __FILELOADER_H__
#define __FILELOADER_H__

#include<map>
#include<string>
#include<GameLib/FileIO/InFile.h>
#include<vector>

namespace GameLib {
	namespace FileIO {
		class InFile;
	}
}

class FileLoader {
public:
	typedef std::pair< const std::string, GameLib::FileIO::InFile > NameAndFile;
	typedef std::vector<NameAndFile> FileList;
	typedef std::vector<std::string> FileNameList;

	FileLoader(){}
	~FileLoader(){}

	void insert( const std::string &name );
	bool isFinished();
	GameLib::FileIO::InFile get(  const std::string& name );

	FileNameList getAllFileNames();
	
private:
	typedef std::map< const std::string, GameLib::FileIO::InFile > FileMap;
	FileMap mName_File;
};


#endif