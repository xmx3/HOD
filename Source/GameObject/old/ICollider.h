#pragma once

#include"IGameObject.h"
#include<btBulletCollisionCommon.h>
#include<GameLib/Math/Matrix34.h>
#include<GameLib/Math/Vector3.h>
#include<vector>
#include<algorithm>
#include<set>
#include"BulletPhysics/Manager.h"
#include"MME/Enums.h"

class RTTI;
namespace GameLib{
	namespace Math{
		class Vector3;
		class Matrix34;
	}
}
namespace GameObject {
typedef unsigned int GameObjectId;

enum GameObjectType{
	PLAYER,
	ENEMY,
	BULLET,
	LASER,
	CHARACTER_CONTROLLER_GHOST_OBJECT,
	CHARACTER_CONTROLLER_RIGIDBODY,
	BONE_COLLISION_OBJECT,
	RIGIDBODY,
	GHOST,
	MMD,
	STAGE,
	WEAPON,
	CHARACTER,
	CHARACTER_AND_WEAPON,
	EXPLOSION,
	BARRIER,
	ACCESSORY,
	MME_Model,
};

struct ResponseInfo;
struct ResponseInfo{
	enum DamageType{
		NOTHING		= 0x0000,
		FIRE		= 0x0001,
		ICE			= 0x0002,
		BEAM		= 0x0004,
		CLOSE_RANGE	= 0x0008,
		EXPLOSION	= 0x0010,
		POISON		= 0x0020,
		PARALYSIS	= 0x0040,
		SPECIAL		= 0x0080,
		PHYSICS		= 0x0100,
		REPEIAR		= 0x0200,
		SUPLLY		= 0x0400,
		ELECTRICITY	= 0x0800,
	};
	//exvsとボーダーブレイク参考
	float damage;
	short group;
	short correctedRate;//ダメージ補正率
	short downValue;//ダウン値
	short staggerValue;//よろけ値
	btVector3 knockBackVel;
	//btVector3 contactPosistions[4];
	//int contactNums;
	float unControlableTime;//操作不可能時間、硬直時間

	float upDownwardOffset;//打ち上げ、たたきつけ攻撃のための値
	btVector3 knockBackVelRate;//ぶっ飛び倍率 //いるか？

	DamageType damageType;

	//距離減衰どうする
	//接触した時点で計算

	//移動速度低下をどう処理する？
	//防御力低下
	//ECM

	//向こう側で消したいとき
	//ICollisionObject *me;
};


/*　攻撃力の式　基本
<a href="http://www10.atwiki.jp/g-vs/pages/88.html">機動戦士ガンダム ガンダムVS.ガンダム Wiki No.2 - ダメージ計算</a>
    ダメージ　＝　１発目の攻撃の威力　＋　１発目の攻撃の補正率×｛２発目の攻撃の威力　＋　２発目の攻撃の補正率×（３発目の…）｝
	単発ダメージ　＝ 威力 × ダメージレベル補正 × 補正率 × キャンセル補正 × ダウン追撃補正 × 誤射補正
					× 残り戦力ゲージ補正 × 攻撃側の（根性補正×連勝補正）×食らう側の（根性補正×連勝補正） 

【PSP】ガンダムNEXT PLUS 改造スレ 6
	威力値等リスト
全8行
1行目0xaaaabbbb:16bit区切り。+bbが威力。+aaがよろけ値。蓄積よろけ値100でよろけ
2行目0xccccdddd:16bit区切り。+ddがダウン値。100で割るとwiki等での数値。+ccが与補正値。5で割るとwiki等での数値
3行目0x00eeffgg:8bit。gg,自機ヒットストップ ff,敵機ヒットストップ ee,ヒットエフェクト(※1)
4行目0x3Fq00000:float。qヒットエフェクトの大きさ。あまりでかいとフリーズ。
5行目0xzzhh00ii:8bit。ii,ヒット音 hhダウン状態の敵に当てた時のふっ飛びかた。 zzダウン以外の状態の敵に当てた時のふっ飛び方。0x20920002で特殊キリモミ
6行目0x00jj00kk:8bit。kkがふっとび倍率。jjがベクトルに関する何か?大きくすると、一定方向にしか飛ばなくなる。
7行目0xmm00unrl:8bit。rl,ふっ飛び方向の横軸の補正。un,ふっ飛びの縦軸の補正。+,2全体的な角度の補正。mm,連続hitの際のhit間隔F。
8行目0xyy100000:8bit。yy,独自補正の適用フラグ(自爆など) 他不明
9行目0xtt010000:8bit。tt,格闘属性。9で射撃? 

ヒットストップとは
	攻撃判定が当たった時に起こる、互いの時間停止時間。またはその硬直やフレームのことをいう。

void damage( const damageInfo &di ) {
	float damage=0;
	//di damageInfo
	btVector3 knockBackVel = di.knockBackVel;

	if(di.group==mGroup){
		return;
	}

	float def = mDef;
	if( (mResistDamageType & di.damageType) !=0 )
		def=256.f;
		knockBackVel.setValue(0.f, 0.f, 0.f);
	}
	float defRate=1.f-def/256.f;
	defRate<0 ? defRate=0 : ;
	damage=damage * ( defRate );

	mController->setVelocity(  knockBackVel );

*/
//コピペ用
/*
	RTTI_DECL;
	virtual btCollisionObject* getBtCollisionObject();
	virtual void removeFromWorld();
	virtual void addToWorld();

#define GAME_OBJECT_INTERFACE_DECL \
	RTTI_DECL;
	virtual btCollisionObject* getBtCollisionObject(); \
	virtual const std::vector< const btCollisionObject* > & getNotCollideBtCollisionObjects() const; \
	virtual void removeFromWorld(); \
	virtual void addToWorld();
*/

class ICollider;
typedef std::shared_ptr<ICollider> IColliderSharedPtr;
typedef std::weak_ptr<ICollider> IColliderWeakPtr;

//list or vector or set or sort済みvector のどれがいいか？
//大量のデータを持つわけではないので, insert, findが早いsetにする。
//大量のデータを持つならsorted_vectorにする。
//const btCollisionObject*にしたのはshared_ptrだと循環参照になってしまう可能性が高いから
//実際にアクセスするわけではないので開放してたとしても問題はおきにくいと思った
//実際困るのが再利用する場合、リセットしなければ当たらない
typedef std::set< const btCollisionObject* > BtCollisionObjects;


//interfaceじゃないBase?
class ICollider : public IGameObject
{
public:
	virtual ~ICollider() {}

	static ICollider* cast(void *vp){
		return static_cast<ICollider*>( vp );
	}

	std::shared_ptr<ICollider> getIColliderSharedPtr(){
		std::shared_ptr<ICollider> r = std::dynamic_pointer_cast<ICollider>(shared_from_this());
		return r;
	}

	RTTI_DECL;
	
	//tofix
	//filtermaskとfilteridを追加させたほうが拡張性高い
	bool isMMDObject() const{
		return mIsMMDObject;
	}

	//拡張用
	bool enableCollidedMMDObject() const{
		return false;
	}

	//結論このクラスは物理衝突クラス
	//btCollisionObjectのuser_ptrには必ずこのクラスを継承したのが入る
	//よって必ずbtCollisionObjectを持たなければならない
	//	virtual btCollisionObject* getBtCollisionObject() = 0;
	//をnullを返す設計は許されない

	//考え中
	//MMEとアクセサリ、pmd
	//	継承新しいクラスColliderをつくり、以下の関数を新しいクラスに移動する
	//	バレット世界に入るクラスは全てColliderを使うようにする
	//	virtual btCollisionObject* getBtCollisionObject() = 0;
	//	virtual const btCollisionObject* getConstBtCollisionObject()const{
	//	const BtCollisionObjects & getNotCollideBtCollisionObjects() const
	//	void ignoreCollision( const btCollisionObject* obj ){
	//	bool canCollide( const btCollisionObject *obj  )const{
	//	void clearNotCollideObjects(){
	//	virtual void removeFromWorld() = 0;
	//	
	//	virtual void addToWorld() = 0;
	//	//btCollisionObjectが接触している間、呼ばれ続ける
	//	virtual void onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj){}
	//	
	//	//btCollisionObjectが衝突したとき呼ばれる
	//	virtual void onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj){}
	//	
	//	//btCollisionObjectが離れたとき呼ばれる
	//	virtual void onCollisionExit( btCollisionObject *me, btCollisionObject *obj ){}
	//？？いやそうするとこのクラスは一対何のためにあるんだ？
	//

	//NULLはだめ//基本は
	//NULLを許容するような設計にしたい
	//表示だけのオブジェクトのため(爆発等)
	//MME::ControlObjectSelfを考える
	//btCollisionObjectを持たない場合わけをどうするか
	virtual btCollisionObject* getBtCollisionObject() = 0;
	
	//継承すると継承してないほうを隠してしまうため( 同名のconstメンバー関数)、名前にConst付けた
	virtual const btCollisionObject* getConstBtCollisionObject()const{
		return const_cast<ICollider*>(this)->getBtCollisionObject();
	}

	//btCollisionObjectを持たない場合わけをどうするか
	//btCollisionObjectを持たない場合、オーバーライドすること
	//継承新しいクラスCollider
	virtual const btTransform & getWorldTransform() const {
		return getConstBtCollisionObject()->getWorldTransform();
	}

	virtual btTransform & getWorldTransform() {
		return getBtCollisionObject()->getWorldTransform();
	}


	//BoneCollisionObjectの自分のパンチが自分に当たらないようにするため必要
	//当たり判定を2つ以上持つ場合持つ場合（地形用、その他）、自分自身が当たらないようにするため必要。
	//
	const BtCollisionObjects & getNotCollideBtCollisionObjects() const
	{
		return mNotCollideObjects;
	}
	//void addNotCollideBtCollisionObject( const btCollisionObject* );
	//void removeNotCollideBtCollisionObject( const btCollisionObject* );
	
	
	void ignoreCollision( const btCollisionObject* obj ){
		//assert(!canCollide(obj) && " has hited already. do you want object to hit only once?" );
		mNotCollideObjects.insert( obj );
	}

	bool canCollide( const btCollisionObject *obj  )const{
		GameObject::BtCollisionObjects::const_iterator it = std::find( mNotCollideObjects.begin(), mNotCollideObjects.end(), obj );
		//見つかったら、衝突しない
		if( it!=mNotCollideObjects.end() ){
			return false;
		}
		return true;
	}
	
	void clearNotCollideObjects(){
		mNotCollideObjects.clear();
	}

	//わざわざインターフェイス強制させなくても良いと思う
	//世界が複数になったので
	//追加する世界を指定しなきゃいけないけどそんなのめんどくさいよね
	//ここでmNotCollideObjectsの初期化を行う
	//例1
	//	mNotCollideObjectsをクリアし、当たらないオブジェクトをもう一回入れなおす
	//	剣を持っている人と剣は当たらないように設定しなおす
	//例2
	//	モデルの初期化
	//	mModel->init( mRigidBody->getWorldTransform() );
	//
	//例3
	//	イベントの発生
	//	Event::Manager::instance()->queueEvent( Event::EventData::AddToWorld::create( getIColliderSharedPtr() ) );
	//virtual void removeFromWorld() = 0;
	//virtual void addToWorld() = 0;

	//btCollisionObjectが接触している間、呼ばれ続ける
	virtual void onCollisionStay( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj){}

	//btCollisionObjectが衝突したとき呼ばれる
	virtual void onCollisionEnter( btPersistentManifold *manifold, btCollisionObject *me, btCollisionObject *obj){}

	//btCollisionObjectが離れたとき呼ばれる
	virtual void onCollisionExit( btCollisionObject *me, btCollisionObject *obj ){}
	
protected:
	//shared_from_thisを使うためprotected
	//必ず、shared_ptrを使い、shared_ptrで管理しなければならない
	//オブジェクトを作成するのはcreate();
	ICollider();

	//static const std::vector< const btCollisionObject* > & getEmptyBtCollisionObjects(){
	//	return sEmptyCollisionObject;
	//}
protected:	
	const bool mIsMMDObject;
private:
	BtCollisionObjects mNotCollideObjects;
	//getNotCollideBtCollisionObjects()で何もいらない場合、空のvectorを返したいので
	//static const std::vector< const btCollisionObject* > sEmptyCollisionObject;
};

/*
class CPlayerActor : public GameObject {
public:
	CPlayerActor(){}
	virtual ~CPlayerActor(){}
	virtual GameObjectType getType(){ return PLAYER; }
	virtual bool isPhysical(){ return true; }
	virtual bool isGeometrical(){ return false; }
	virtual bool hasRigidBody(){ return true; }
	virtual void update(){}

	void draw();
	void setPosition( const Vector3& );
	void setAngleY( float );
	const Vector3* position() const;
	void getView( Matrix34* matrix, Vector3* position ) const;
	void setDamage( int damage );
	int getHitPoint() const;
	int getEnergy() const;
	bool getLockOn() const;
private:
	Vector3 mPos;
	float mAngleY;
	
	int mBulletNumber;

	int mCameraCount;
	int mCount; //移動開始後何フレーム経った？
	Vector3 mVelocity; //現在の平面速度
	float mAngleVelocityY; //振り向き速度

	int mHitPoint; //体力

	//weapon クラスを作るべきか?
	int mEnergy; //武器を撃つのに必要なエネルギー
	bool mLockOn; //ロックオンしてますか？

	Vector3 mClickPos;//target
	btRigidBody *m_pRigidBody;
};
*/
}//end namespace GameObject
