#pragma once
#include<memory>
#include<string>
#include<vector>


class btTransform;
namespace GameObject {
	class Enemy;
	typedef std::shared_ptr<Enemy> EnemySharedPtr;
}

namespace XmlLoader {
	namespace GameObject {
		class Enemy;
		typedef std::shared_ptr<Enemy> EnemySharedPtr;
	}
}

namespace HOD {

class EnemySpawner {
public:
	EnemySpawner();
	~EnemySpawner();

	void update(float elapsedTime);

	//予約したときにEnemyを作るか
	//予約を実行しEnemyが作成されるときにEnemyを作るべきか迷った
	//これらは生成したEnemyの生存管理をどうするか？にかかわって来る
	//
	//案1
	//敵生存管理クラスに放り込む
	//案2
	//予約したときにEnemyを作り、返り値にスマートポインターで返す
	//
	//案2で行こうと思う
	//予約した時点でEnemyを作りたい
	//ゲーム開始時点でロード等完了しておきたいし、（完了してなくてはスムーズにゲームが進行しないし、ロード中の表示とか考えてないし)
	//2のほうが1フレーム間でのCPU負荷が高いかもしれないが、(予約はたぶん1フレームで予約し作成するので）
	//たいした負荷ではないと思われるし、負荷があったとしてもゲーム初期化中なので許容できるだろう
	//のちに敵生存クラスに突っ込むかほかの方法考えるかは好きにすればいいや

	//敵の出現を予約する
	//ここで敵ポインタを返すがaddToWorldしないこと
	//この予約時間前にaddToWorldした場合予約時間にassertさせる
	//位置変化とかはさせない
	//enemyNameが見つからなかったら空っぽのスマートポインターを返す
	GameObject::EnemySharedPtr reserve(const std::string &enemyName, float spawnTime, const btTransform& trans);

	//同じファイル名を重複して登録できるので気を付けること
	void loadEnemy(const std::string &filename);

	bool isReady();

	//違うところでloadさせたXmlLoader::GameObject::EnemySharedPtrを登録させる
	//enemy->isReady()がtrueになっていること推奨
	void registerEnemy(XmlLoader::GameObject::EnemySharedPtr enemy);

	void setTime(float t) {
		mTime = t;
	}
private:
	//すでにリソースをロードしているのならロードしないという仕様をこのクラスに入れようか迷ったが
	//入れないことにした。
	//スクリプトからリソースを更新したいときに言い手が浮かばなったことが一つ
	//その仕様は自然ではないと感じたのが理由。さすがにはじいてしまうのがデフォルトにはしたくない

	std::vector<XmlLoader::GameObject::EnemySharedPtr> mTempateEnemies;

	//現在ロード中のenemyを入れておくところ
	//ロードが終わったらmTemplateEnemiesに移動させる
	//
	//mapかvectorで迷ったがvectorで行くことにした
	//同じファイルを2重ロードしてしまうことができてしまうが別に問題はないだろうと判断
	//どうせロードし終わったら出ていくし
	std::vector<XmlLoader::GameObject::EnemySharedPtr> mLoadingTempateEnemies;
	
	
	struct Request;
	std::vector<Request> mRequests;
	float mTime;	
};


}

