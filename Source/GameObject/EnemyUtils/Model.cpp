#include"Model.h"

#include"helper/XmlHelperFuncs.h"

#include<GameLib/GameLib.h>

#include<GameLib/FileIO/InFile.h>

#include<btBulletCollisionCommon.h>

#include"GameObject/Accessory.h"

#include"MMD/AnimationState/Hook/AccessoryHook.h"
#include"MMD/AnimationModel.h"
#include"MMD/AnimationState/Default.h"
#include"MMD/AnimationState/StartEnd.h"

#include"helper/MyOutputDebugString.h"

#include"GameObjectData/WeaponStatus.h"

#include<d3dx9.h>
#include"BulletPhysics/BulletPhysicsHelper.h"
namespace{
	using namespace GameLib::PseudoXml;

//	static std::pair< const std::string, std::shared_ptr<GameObject::Accessory> > createAccessoryPair( btCollisionObject* ignoredObj, const ConstElement &e ){
//	using GameLib::RefString;
//
//	const char *name=NULL;
//	const char *templateAccessoryName=NULL; 
//
//	int numAttributes = e.attributeNumber();
//	for( int i=0; i<numAttributes; ++i )
//	{
//		ConstAttribute & a = e.attribute(i);
//		const char *attributeName = a.name();
//		if( RefString("name") == attributeName ){
//			name=a.value();
//		} else if( RefString("templateAccessory") == attributeName ){
//			templateAccessoryName=a.value();
//		} else{
//			STRONG_ASSERT( false && "attribute of Accessory Element is wrong!" );
//		}
//	}
//	assert(name);
//	assert(templateAccessoryName);
//
//	std::shared_ptr<GameObject::Accessory> acce =
//		GameObject::AccessoryUtils::Manager::instance()->createAccessory(
//		templateAccessoryName,
//		ignoredObj,
//		btTransform::getIdentity() );
//	return std::make_pair( std::string(name), acce );
//}
}//end unnamespace

namespace GameObject{
namespace EnemyUtil{

Model::XmlMap Model::mXmlMap; 

MMD::AnimationState::IAnimationState* Model::createAnimationState(
	GameObjectData::StatusSharedPtr status,
	const GameLib::PseudoXml::ConstElement &e )
{
	using namespace GameLib::PseudoXml;
	using namespace XmlHelperFuncs;

	MMD::AnimationState::IAnimationState* pOut =NULL;

	using GameLib::RefString;
	int num=e.attributeNumber();
	bool isBlend = false;
	bool isRepeat = false;
	bool isStand = true;
	float restartFrame=0;
	float endFrame=0;
	float playSpeed=1.f;

	enum AnimationStateType{
		dflt,//default予約語使うの気持ち悪いので
		startEnd
	};
	AnimationStateType type = dflt;


	for( int i=0; i<num; ++i ){
		ConstAttribute a = e.attribute(i);
		const char* attributeName = a.name();
		if( RefString("type") == attributeName ){
			RefString str( a.value() );
			if( str == "default" ){
				type=dflt;
			} else if( str == "startEnd" ){
				type=startEnd;
			} else {
				STRONG_ASSERT( false && " type attribute of Animation is wrong!" );
			}
		}
		else if( RefString("isBlend") == attributeName ){
			bool isOk = setBool( &isBlend, a );
			STRONG_ASSERT( isOk && "isBlend is wrong!" );
		}
		else if( RefString("isRepeat") == attributeName ){
			bool isOk = setBool( &isRepeat, a );
			STRONG_ASSERT( isOk && "isRepeat is wrong!" );
		}
		else if( RefString("isStand") == attributeName ){
			bool isOk = setBool( &isStand, a );
			STRONG_ASSERT( isOk && "isStand is wrong!" );
		}else if( RefString("restartFrame") == attributeName ){
			restartFrame = a.getFloatValue();
		}else if( RefString("endFrame") == attributeName ){
			endFrame = a.getFloatValue();
		}else if( RefString("vmdFile") == attributeName ){
			//do nothing
		}else if( RefString("playSpeed") == attributeName ){
			playSpeed = a.getFloatValue();
			assert( playSpeed != 0.f );
		}else {
			TRACE1("attribute name=%s\n", attributeName );
			STRONG_ASSERT( false && "attribute name is wrong!" );
		}
	}

	if( type == dflt){
		MMD::AnimationState::Default *p	= NEW MMD::AnimationState::Default( mModel, getVMDFileName(e), isBlend, isRepeat, isStand );
		p->setPlaySpeed( playSpeed );
		pOut = p;
	} else if( type == startEnd ){
		STRONG_ASSERT( !(restartFrame==0 && restartFrame==endFrame) && "restartFrame or endFrame is wrong!" );
		MMD::AnimationState::StartEnd *p = NEW MMD::AnimationState::StartEnd( mModel, getVMDFileName(e), restartFrame, endFrame, isBlend, isRepeat, isStand );
		p->setPlaySpeed( playSpeed );
		pOut = p;
	} else {
		assert( false );
	}

	//AccessoryHookの設定
	int numChild=e.childNumber();
	for( int i=0; i<numChild; ++i ){
		ConstElement c = e.child(i);
		if( RefString("AccessoryHook") == c.name() ){
			float drawStartFrame=-10.f;
			float drawEndFrame=-10.f;
			float hitStartFrame=-10.f;
			float hitEndFrame=-10.f;
			const char *accessoryName=NULL;
			const char *boneName=NULL;
			const char *weaponStatusFileName=NULL;
			for( int j=0, numAttributes=c.attributeNumber(); j<numAttributes; ++j ){
				ConstAttribute a=c.attribute(j);
				const char *attributeName=a.name();
				if( RefString("accessory") == attributeName ) {
					accessoryName=a.value();
				} else if( RefString("bone") == attributeName ) {
					boneName = a.value();
				} else if( RefString("hitStartFrame") == attributeName ) {
					hitStartFrame=a.getFloatValue();
				} else if( RefString("hitEndFrame") == attributeName ) {
					hitEndFrame=a.getFloatValue();
				} else if( RefString("drawStartFrame") == attributeName ) {
					drawStartFrame=a.getFloatValue();
				} else if( RefString("drawEndFrame") == attributeName ) {
					drawEndFrame=a.getFloatValue();
				} else if( RefString("weaponStatusFile") == attributeName ) {
					weaponStatusFileName=a.value();
				} else {
					TRACE1( "attribute name = %s\n", attributeName );
					STRONG_ASSERT( false && "AccessoryHook Attribute is wrong!" );
				}
			}
			assert(accessoryName);
			assert(boneName);
			//getFoloat()が失敗した場合0だから0のほうがいいか？
			assert( !(hitStartFrame==-10 && hitEndFrame==-10) );
			assert( !(drawStartFrame==-10 && drawEndFrame==-10) );
			assert(weaponStatusFileName);

			std::shared_ptr<Accessory> accessory = getAccessory(accessoryName);
			if( accessory ){
			} else {
				STRONG_ASSERT( false && "" );
			}
			MMD::Bone *bone = mModel->getBone( boneName );
			STRONG_ASSERT( bone && "bone not found." );
			accessory->attachBone( bone );
			//xmlで制御できるようにしてもいい
			accessory->enableContactResponse( false );
			using namespace GameObjectData;
			WeaponStatusSharedPtr weaponStatus(  NEW WeaponStatus( status ) );
			GameLib::FileIO::InFile infile =  GameLib::FileIO::InFile::create( weaponStatusFileName );
			weaponStatus->loadTextFromArchive( infile );

			using namespace MMD::AnimationState::Hook;
			IHookSharedPtr spHook = AccessoryHook::create( 
				accessory,
				hitStartFrame, hitEndFrame,
				drawStartFrame, drawEndFrame,
				bone,
				false,
				weaponStatus );

			pOut->addHook(spHook);

		}

	}

	MMD::AnimationState::BaseAnimationState *base = dynamic_cast<MMD::AnimationState::BaseAnimationState *>(pOut);
	assert(base);

	//hookの数数えておいて
	//どこからfixed_vector を探してくるか　動的配列にすべきか
	dynamic_cast<MMD::AnimationState::BaseAnimationState *>(pOut)->shrinkToFitAllHookContainers();
	return pOut;
}

Model::Model()
	:mModel(NULL),
	mStandAnim(NULL),
	mRunAnim(NULL),
	mHeightOffset(0.f)
{}
Model::~Model(){
	SAFE_DELETE( mModel );
	SAFE_DELETE( mStandAnim );
	SAFE_DELETE( mRunAnim );
}

void Model::init( const btTransform &world ){
	D3DXMATRIX dxW = toDxMatrix(world);
	//dxW._42 -= mHeightOffset;

	D3DXVECTOR3 offset;
	D3DXVec3TransformNormal( &offset, &D3DXVECTOR3( 0.f, -mHeightOffset, 0.f ), &dxW );
	dxW._41 += offset.x;
	dxW._42 += offset.y;
	dxW._43 += offset.z;


	mModel->init( dxW, mStandAnim );
}
void Model::draw() const{
	mModel->draw();
	for(
		AccessoryMap::const_iterator it= mAccessoryMap.begin(), end =mAccessoryMap.end();
		it!=end;
		++it )
	{
		//canDraw();
		if( it->second->canDraw() ){
			it->second->draw();
			//it->second->debug_draw();
		}
	}
}
void Model::debugDraw() const{
	mModel->debugDraw();
}
void Model::update( const btTransform &world, float elapsedTime ){
	D3DXMATRIX dxW = toDxMatrix(world);

	D3DXVECTOR3 offset;
	D3DXVec3TransformNormal( &offset, &D3DXVECTOR3( 0.f, -mHeightOffset, 0.f ), &dxW );
	dxW._41 += offset.x;
	dxW._42 += offset.y;
	dxW._43 += offset.z;


	mModel->update( dxW, elapsedTime );
}
bool Model::isAnimOver() const{
	return mModel->isAnimOver();
}
	
float Model::getFrame() const{
	return mModel->getFrame();
}

MMD::Bone* Model::getBone( const char* boneName ){
	return mModel->getBone( boneName );
}

void Model::loadXML(
	const char *fileName,
	btCollisionObject* ignoredObject,//accessoryが親を無視するために必要
	GameObjectData::StatusSharedPtr status//武器が攻撃力を求めるために必要
){
	using namespace GameLib::PseudoXml;
	using namespace XmlHelperFuncs;

	if(!(ignoredObject && status) ){
		assert(false && "parameters is NULL");
		return;
	}

	if(mModel){
		assert(false && "init doubled");
		return;
	}

	using GameLib::RefString;
	Document modelXml;
	XmlMap::iterator it = mXmlMap.find(fileName);
	if( it==mXmlMap.end() ){
		GameLib::FileIO::InFile xmlFile;
		xmlFile= GameLib::FileIO::InFile::create( fileName );
		if( xmlFile.isError() ){
			STRONG_ASSERT(false);
			return;
		}
		while( !xmlFile.isFinished() ){}

		modelXml = Document::create( xmlFile.data(), xmlFile.size() );
		if( modelXml.isError() ){
			STRONG_ASSERT(false);
			return;
		}
		mXmlMap.insert( std::make_pair( fileName, modelXml ) );
	} else {
		modelXml = it->second;
	}

	ConstElement modelElem= findElement( modelXml.root(), "Model" );
	int numAttributes = modelElem.attributeNumber();
	RefString pmdFile;
	bool enablePhysics=false;

	for( int ia=0; ia<numAttributes; ++ia )
	{
		ConstAttribute & a = modelElem.attribute(ia);
		const char *attributeName = a.name();
		if( RefString("heightOffset") == attributeName ){
			mHeightOffset = a.getFloatValue();
		} else if( RefString("pmdFile") == attributeName ){
			pmdFile = a.value();
		} else {
			TRACE1( "this attribute name is wrong! %s\n", attributeName ); 
			STRONG_ASSERT( false );
		}
	}
	mModel = NEW MMD::AnimationModel();
	mModel->loadPMDFromDB( pmdFile.get(), enablePhysics );
	

	//アクセサリー作成、登録
	//{
	//	ConstElement accessoriesElem = findElement( modelElem, "Accessories");
	//	int numChild = accessoriesElem.childNumber();
	//	for(int ic=0; ic<numChild; ++ic ){
	//		ConstElement e = accessoriesElem.child(ic);
	//		STRONG_ASSERT(RefString( "Accessory") == e.name() && "element of Accessory is wrong."  );
	//		//登録
	//		AccessoryMap::_Pairib pair = mAccessoryMap.insert( createAccessoryPair( ignoredObject, e ) );
	//		assert(pair.second && "accessory key name is doubled.");
	//	}
	//}
	
	//アニメーション作成
	{
		ConstElement animationsElem = findElement( modelElem, "Animations");
	
		ConstElement e = findElement( animationsElem, "StandAnimation" );
		mStandAnim = createAnimationState( status, e );

		e = findElement( animationsElem, "RunAnimation" );
		mRunAnim = createAnimationState( status, e );
	}
}

std::shared_ptr<Accessory> Model::getAccessory( const char* name ){
	AccessoryMap::iterator it = mAccessoryMap.find( name );
	if( it == mAccessoryMap.end() ){
		TRACE1( "%s not found", name );
		STRONG_ASSERT(false && "not found" );
		return std::shared_ptr<Accessory>();
	} else {
		return it->second;
	}
}

void Model::changeStandAnim(){
	mModel->changeAnimation(mStandAnim);
}
void Model::changeRunAnim(){
	mModel->changeAnimation(mRunAnim);
}

}//end namespace EnemyUtil
}//end namespace GameObject