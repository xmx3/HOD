#pragma once
#include"GameObjectData/fwd.h"
#include"GameObject/SharedPtrs.h"
#include<string>
//#include"Item/Item.h"
namespace boost{
	namespace serialization{
		class access;
	}
}

namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}
namespace XmlLoader {
	class PlayerData;
	typedef std::shared_ptr<PlayerData> PlayerDataSharedPtr;
	class Character;
//
//enum StageSelectedFlags{
//	Stage1 = 0x1,
//	Stage2 = 0x2,
//	Stage3 = 0x4,
//	Stage4 = 0x8,
//	Stage5 = 0x10,
//	Stage6 = 0x20,
//	Stage7 = 0x40,
//	Stage8 = 0x80,
//	Stage9	= 0x100,
//	Stage10	= 0x200,
//	Stage11	= 0x400,
//	Stage12	= 0x800,
//	Stage13	= 0x1000,
//	Stage14	= 0x2000,
//	Stage15	= 0x4000,
//	Stage16	= 0x8000,
//};

//PlayerData
class PlayerData {
public:
	friend class std::_Ref_count_obj<PlayerData>;
	static PlayerDataSharedPtr create( const std::string &fileName="" );

	~PlayerData();
	
	bool loadBinary( const char *fileName );
	bool loadBinaryFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveBinary( const char *fileName )const;
	
	bool loadText( const char *fileName );
	bool loadTextFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveText( const char *fileName )const;
	
	bool loadXML( const char *fileName );
	bool loadXMLFromArchive( const GameLib::FileIO::InFile &infileInArchive );
	bool saveXML( const char *fileName )const;

	//void addItem( Item::ItemSharedPtr item );
	//bool removeItem( const Item::ItemSharedPtr &item );
	//void swapItem( unsigned int index0, unsigned int index1 );
	
	//mItems[index].swap( refItem );
	//void swapItemAt( unsigned int index,const Item::ItemSharedPtr &refItem );
	//bool removeItem( unsigned int index );

	//void loadStart();

private:
	//use create
	PlayerData();
	//disallow
	PlayerData(const PlayerData& );
	//disallow
	void operator=(const PlayerData& );

	//void setCurrentTime();
	
	//std::vector<Item::ItemSharedPtr> mItems;
	//std::vector<int> mItemList;

	int mClearedStage;//クリアしたステージ
	Character* mMiku;

	
	//0番目が操作する人
	//std::vector<CharacterSharedPtr> mCharacters;

	friend boost::serialization::access;	
	//基底クラスのselialize関数を直接呼び出さないこと！！
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);
};

}//end namespace XmlLoader