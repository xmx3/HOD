#ifndef __NAMEANDFILE_H__
#define __NAMEANDFILE_H__
#include<GameLib/FileIO/InFile.h>
#include<string>
///読み込みファイルハンドル
class NameAndFile{
public:
	///ファイルロードを開始する
	NameAndFile(){}
	~NameAndFile(){}
	void load( const char* filename ){
		mFileName.assign(filename);
		mFile = GameLib::FileIO::InFile::create( filename );
	}
	///ロード容量ゲット
	int size() const{
		return mFile.size();
	}
	///ロード内容ゲット
	const char* data() const{
		return mFile.data();
	}
	///ロード終わった？
	bool isFinished() const{
		return mFile.isFinished();
	}
	///エラー出てます？
	bool isError() const{
		return mFile.isError();
	}

	const char* getName()const{
		return mFileName.c_str();
	}
private:
	NameAndFile( const NameAndFile& );
	NameAndFile& operator=( const NameAndFile& );
	std::string mFileName;
	GameLib::FileIO::InFile mFile;
};
#endif
