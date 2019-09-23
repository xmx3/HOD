#pragma once
#include<btBulletCollisionCommon.h>
#include<BulletCollision/BroadphaseCollision/btOverlappingPairCallback.h>
#include"BulletPhysics/Manager.h"
#include"MMD/PMDRigidBody.h"
//ルール
//btCollisionObjectのUserPointerはRigidBodyComponent*かnullptrとする
//
//両方ともmmdオブジェクトの場合はぶつかる
//mmdオブジェクトは他のオブジェクトにはぶつからない
//mmdオブジェクトかどうかはgroupで判別する

//多重継承した場合のvoid*からのインターフェイスクラスへのキャストはうまくいかずバグを生みやすい
//バグった場合動く場合もあるがvtableが壊れてる
//継承順などを考慮すれば動くが避けたい
//なのでバグを消すためにvoid*からのキャストは元のクラスに戻したいというのがあった

namespace BulletPhysics {
	namespace FilterCallback {

		class FilterCallbackUsingCollisionComponent : public btOverlapFilterCallback
		{
		public:
			// return true when pairs need collision
			virtual bool	needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const
			{
				bool collides = (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) != 0;
				collides = collides && (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask) != 0;


				//MMDObjectとゲームオブジェクトはぶつからない
				//MMDでもフィルタリングを使っているので
				//unsigned short 15グループだけでは足りない。
				//なののでmmdで使用している分は拡張させる
				//そもそも6グループ分はBulletPhysics本体で使っている
				//定義してあるだけでStaticFilter以外は使っていないっぽいけど
				///optional filtering to cull potential collisions
				//enum CollisionFilterGroups
				//{
				//        DefaultFilter = 1,
				//        StaticFilter = 2,
				//        KinematicFilter = 4,
				//        DebrisFilter = 8,
				//		SensorTrigger = 16,
				//		CharacterFilter = 32,
				//        AllFilter = -1 //all bits sets: DefaultFilter | StaticFilter | KinematicFilter | DebrisFilter | SensorTrigger
				//};

				//StaticFileter使用箇所
				/*btDiscreteDynamicWorld.cpp内-------------------------------
				void	btDiscreteDynamicsWorld::addRigidBody(btRigidBody* body)
				{
				if (!body->isStaticOrKinematicObject() && !(body->getFlags() &BT_DISABLE_WORLD_GRAVITY))
				{
				body->setGravity(m_gravity);
				}

				if (body->getCollisionShape())
				{
				if (!body->isStaticObject())
				{
				m_nonStaticRigidBodies.push_back(body);
				} else
				{
				body->setActivationState(ISLAND_SLEEPING);
				}

				bool isDynamic = !(body->isStaticObject() || body->isKinematicObject());
				short collisionFilterGroup = isDynamic? short(btBroadphaseProxy::DefaultFilter) : short(btBroadphaseProxy::StaticFilter);
				short collisionFilterMask = isDynamic? 	short(btBroadphaseProxy::AllFilter) : 	short(btBroadphaseProxy::AllFilter ^ btBroadphaseProxy::StaticFilter);

				addCollisionObject(body,collisionFilterGroup,collisionFilterMask);
				}
				}
				*/

				btCollisionObject *co0 = static_cast<btCollisionObject*>(proxy0->m_clientObject);
				btCollisionObject *co1 = static_cast<btCollisionObject*>(proxy1->m_clientObject);
				Component::RigidBodyComponent *rbc0 = static_cast<Component::RigidBodyComponent*>(co0->getUserPointer());
				Component::RigidBodyComponent *rbc1 = static_cast<Component::RigidBodyComponent*>(co1->getUserPointer());

				collides = collides;



				//これif分の条件の書き方が回りくどいような
				//xor使えばきれいに書けそうだがわかりにくいか

				//両者ともMMDObjectの場合
				if (
					collides &&
					proxy0->m_collisionFilterGroup == BulletPhysics::MMDObjectFilter &&
					proxy1->m_collisionFilterGroup == BulletPhysics::MMDObjectFilter)
				{
					
					assert(rbc0 && rbc1);
					if (rbc0 && rbc1) {
						return rbc0->canCollide(co1) && rbc1->canCollide(co0);
					}
				}

				//MMDObjectとゲームオブジェクトはぶつからないので
				//つまり、どちらかがMMDオブジェクトならぶつからない
				collides = collides && proxy0->m_collisionFilterGroup != BulletPhysics::MMDObjectFilter;
				collides = collides && proxy1->m_collisionFilterGroup != BulletPhysics::MMDObjectFilter;


				if (collides) {
					if (rbc0 && rbc1) {
						return rbc0->canCollide(co1) && rbc1->canCollide(co0);
					}
					//rbcがnullptrの場合必ずぶつかる
					else {
						return true;
					}
				}
				return false;
			}
		};
	}
}
