#pragma once

#include"GameObject/IGameObject.h"
#include"RTTI/RTTI.h"
#include"MME/Object/Accessory.h"
#include"BulletPhysics/BulletPhysicsHelper.h"
class Bone;
class btCollisionObject;
class btCollisionShape;
class btTransform;


namespace GameObject {

class MME_Accessory;
typedef std::shared_ptr<MME_Accessory> MME_AccessorySharedPtr;


//
class MME_Accessory : public IGameObject {
public:
	//make_sharedがprivate　コンストラクタ呼ぶのに必要
	friend class std::_Ref_count_obj<MME_Accessory>;

	static MME_AccessorySharedPtr create( const char *name, const btTransform & startTr, const char* effect=NULL ){
		MME_AccessorySharedPtr r = std::make_shared<MME_Accessory>( name, startTr, effect );
		return r;
	}

	virtual ~MME_Accessory(){}

	RTTI_HEADER_IMPL(MME_Accessory);

	bool canDraw()const{
		return mModel->canDraw();
	}

	void setCanDraw( bool canDraw ){
		mModel->setCanDraw(canDraw);
	}

	void setCanDraw( MME::MMDPass pass, bool canDraw ){
		mModel->setCanDraw( pass, canDraw );
	}

	virtual const btTransform & getWorldTransform() const {
		return mTransform; 
	}

	virtual btTransform & getWorldTransform() {
		return mTransform;
	}
	void remove(){
		mModel->setCanRemove(true);
	}

	//void registOffScreen( const char *effectFileName ,const char *offScreenName, const char *effectFileNameInOffScreen ){
	//	mModel->registOffScreen( effectFileName, offScreenName, effectFileNameInOffScreen );
	//}

private:
	MME_Accessory( const char *name, const btTransform & startTr, const char* effect=NULL ){
		mModel = std::make_shared<MME::Object::Accessory>();
		mModel->init( name, toDxMatrix(startTr), effect );
	}
	MME_Accessory( const MME_Accessory & );
	void operator=( const MME_Accessory & );
	
	std::shared_ptr<MME::Object::Accessory> mModel;
	btTransform mTransform;
};

}//end namespace GameObject
