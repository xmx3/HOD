#include"EnemySpawner.h"

#include<algorithm>
#include<assert.h>
#include<btBulletCollisionCommon.h>

#include"GameObject/Enemy.h"
#include"helper/MyOutputDebugString.h"
#include"XmlLoader/GameObject/Enemy.h"


namespace HOD {
	
namespace {

	std::vector<XmlLoader::GameObject::EnemySharedPtr>::iterator 
		find(
			std::vector<XmlLoader::GameObject::EnemySharedPtr> &refSource,
			const std::string &findName)
	{


		auto isName = [findName](const XmlLoader::GameObject::EnemySharedPtr &enemy) -> bool
		{
			return enemy->getName() == findName;

		};

		auto itTemplateEnemy = std::find_if(refSource.begin(), refSource.end(), isName);
		return itTemplateEnemy;
	}
}//end nonamespace



struct EnemySpawner::Request {
	float mSpawnTime;
	std::string mName;
	btTransform mTrans;
	GameObject::EnemySharedPtr mEnemy;

	bool operator<(const Request & right)const {
		return mSpawnTime < right.mSpawnTime;
	}

	bool operator<(const float & time)const {
		return mSpawnTime < time;
	}
};

EnemySpawner::EnemySpawner()
	:mTime(0.f)
{
}

EnemySpawner::~EnemySpawner() {}

void EnemySpawner::update(float elapsedTime) {

	//まあわざわざ線形探索しなくても一番最初の配列の要素の時間と現在時刻+elapsedTimeを比べて小さければ敵を出現させて削除するでいいんだけど
	//巻き戻しとかさせる気ないしわざわざ2部探索させる必要性を感じないが、そこまで負荷でないのでいいか
	//途中から実行してゲームデザイン修正したいというのもあるかもだし
	auto it = std::lower_bound(mRequests.begin(), mRequests.end(), mTime);
	auto itStart = it;
	while (it != mRequests.end() && it->mSpawnTime < mTime + elapsedTime) {
		auto e = it->mEnemy;
		
		if (e->isInWorld()) {
			//あさーと出すだけ何もしない
			assert(false);
		}
		else {
			e->getWorldTransform() = it->mTrans;
			e->addToWorld();
		}
		++it;

	}
	//本当は順番を逆にして後ろから削除するようにすれば削除した後詰める作業がいらないので効率的だが実装してしまったしこのままで
	//一応実験コードはsorted_reverese_vector.cppとして書いた
	//
	//ここも途中から始まるとかないと思う(デバッグ時、途中スタートは十分あり得るか)からitStartはmRequests.begin()でいいと思うけど
	//
	//だって使わないでしょ、わざわざ出現時刻が現在時刻より古いのを使う場面が思いつかないけど…
	//まあデバッグで使うかもぐらいか
	mRequests.erase(itStart, it);

	mTime += elapsedTime;
}

GameObject::EnemySharedPtr EnemySpawner::reserve(const std::string& enemyName, float spawnTime, const btTransform& trans) {
	
	GameObject::EnemySharedPtr outEnemy;
	
	auto itTemplateEnemy = find(mTempateEnemies, enemyName);
	
	if (itTemplateEnemy == mTempateEnemies.end()) {
		assert(false && "名前が見つかりません");
	}
	else {
		outEnemy = itTemplateEnemy->get()->instance();
		Request req{
			spawnTime,
			enemyName,
			trans,
			outEnemy
		};

		std::vector<Request>::iterator it = std::lower_bound(mRequests.begin(), mRequests.end(), req  );
		mRequests.insert(it, std::move(req));

	}
	
	return outEnemy;
}

void HOD::EnemySpawner::registerEnemy(XmlLoader::GameObject::EnemySharedPtr enemy)
{
	//ロードさせたのを登録させたい
	if (!enemy->isReady()) {
		TRACE("enemy is not ready! it will force to be ready at this frame.");
		while (!enemy->isReady()) {}
	}

	auto it = find(mTempateEnemies, enemy->getName() );
	if (it == mTempateEnemies.end())
	{
		mTempateEnemies.push_back(enemy);
	}
	else {
		assert(false && "same name is registered!");
	}
}

void HOD::EnemySpawner::loadEnemy(const std::string & filename)
{
	auto enemy = XmlLoader::GameObject::Enemy::createSP();
	enemy->loadXml(filename);
	
	mLoadingTempateEnemies.push_back(enemy);
}


bool HOD::EnemySpawner::isReady()
{
	if (mLoadingTempateEnemies.empty()) {
		return true;
	}

	//std::vector< XmlLoader::GameObject::EnemySharedPtr > finished;
	auto isReady = [this](const XmlLoader::GameObject::EnemySharedPtr &enemy)->bool
	{
		bool result = enemy->isReady();
		
		//Loading中から完了したに移し、参照カウントを増やす
		//削除はループが終わった後でやる
		//とういうか必要なくなった部分のコンテナ詰める作業をremove_ifにやってもらう
		if (result) {
			mTempateEnemies.push_back(enemy);
			//finished.push_back(enemy);
			//メンバ変数のキャプチャがなんかうまくいかないのでとりあえずだけどうまくいったな
			//コメントアウトしていいと思いますがとっておきますか
		}
		return result;
	};


	auto itNewEnd = std::remove_if(
		mLoadingTempateEnemies.begin(),
		mLoadingTempateEnemies.end(),
		isReady );

	mLoadingTempateEnemies.erase(
		itNewEnd,
		mLoadingTempateEnemies.end());

	

	return false;
}

}
