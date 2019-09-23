#include"AnimationModel2.h"
#include"Bone.h"

#include"helper/XmlHelperFuncs.h"

#include<GameLib/GameLib.h>

#include<GameLib/FileIO/InFile.h>

#include<btBulletCollisionCommon.h>

#include"GameObject/Accessory.h"
#include"GameObject/AccessoryUtils/Manager.h"

#include"MMD/AnimationState/Hook/AccessoryHook.h"
//#include"MMD/AnimationModel.h"
#include"MMD/AnimationState/Default.h"
#include"MMD/AnimationState/StartEnd.h"

#include"helper/MyOutputDebugString.h"

#include"GameObjectData/WeaponStatus.h"

#include<d3dx9.h>
#include"BulletPhysics/BulletPhysicsHelper.h"

#include"GameObject/XmlFiles.h"

namespace{
	using namespace GameLib::PseudoXml;

	static std::pair< const std::string, std::shared_ptr<GameObject::Accessory> > createAccessoryPair( btCollisionObject* ignoredObj, const ConstElement &e ){
	using GameLib::RefString;

	const char *name=NULL;
	const char *templateAccessoryName=NULL; 

	int numAttributes = e.attributeNumber();
	for( int i=0; i<numAttributes; ++i )
	{
		ConstAttribute & a = e.attribute(i);
		const char *attributeName = a.name();
		if( RefString("name") == attributeName ){
			name=a.value();
		} else if( RefString("templateAccessory") == attributeName ){
			templateAccessoryName=a.value();
		} else{
			STRONG_ASSERT( false && "attribute of Accessory Element is wrong!" );
		}
	}
	assert(name);
	assert(templateAccessoryName);

	std::shared_ptr<GameObject::Accessory> acce =
		GameObject::AccessoryUtils::Manager::instance()->createAccessory(
		templateAccessoryName,
		ignoredObj,
		btTransform::getIdentity() );
	return std::make_pair( std::string(name), acce );
}
}//end unnamespace

namespace MMD{

MMD::AnimationState::IAnimationStateSharedPtr AnimationModel2::createAnimationState(
	GameObjectData::StatusSharedPtr status,
	const GameLib::PseudoXml::ConstElement &e )
{
	using namespace GameLib::PseudoXml;
	using namespace XmlHelperFuncs;

	MMD::AnimationState::IAnimationStateSharedPtr pOut;


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
		pOut.reset( new MMD::AnimationState::Default( this, getVMDFileName(e), isBlend, isRepeat, isStand ) );
		dynamic_cast<MMD::AnimationState::Default*>(pOut.get())->setPlaySpeed( playSpeed );
	} else if( type == startEnd ){
		STRONG_ASSERT( !(restartFrame==0 && restartFrame==endFrame) && "restartFrame or endFrame is wrong!" );
		pOut.reset( new MMD::AnimationState::StartEnd( this, getVMDFileName(e), restartFrame, endFrame, isBlend, isRepeat, isStand ) );
		dynamic_cast<MMD::AnimationState::StartEnd*>(pOut.get())->setPlaySpeed( playSpeed );
	} else {
		assert( false );
	}

	//AccessoryHookの設定
	int numChild=e.childNumber();
	for( int i=0; i<numChild; ++i ){
		ConstElement c = e.child(i);
		if( RefString("AccessoryHook") == c.name() ){
			//-10のわけ-1だったら実装を理解してると使いそうだから
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

			std::shared_ptr<GameObject::Accessory> accessory = getAccessory(accessoryName);
			if( accessory ){
			} else {
				STRONG_ASSERT( false && "" );
			}
			CBone *bone = getBone( boneName );
			STRONG_ASSERT( bone && "bone not found." );
			accessory->attachBone( bone );
			//xmlで制御できるようにしてもいい
			accessory->enableContactResponse( false );
			using namespace GameObjectData;
			WeaponStatusSharedPtr weaponStatus(  NEW WeaponStatus( status ) );
			GameLib::FileIO::InFile infile =  GameLib::FileIO::InFile::create( weaponStatusFileName );
			weaponStatus->loadTextFromArchive( infile );

			using namespace MMD::AnimationState::Hook;
			IHookSharedPtr spHook = AccessoryHook::create( accessory, hitStartFrame, hitEndFrame, drawStartFrame, drawEndFrame, bone, weaponStatus );

			pOut->addHook(spHook);
		}
	}

	MMD::AnimationState::BaseAnimationState *base = dynamic_cast<MMD::AnimationState::BaseAnimationState *>(pOut.get());
	assert(base);

	//hookの数数えておいて
	//どこからfixed_vector を探してくるか　動的配列にすべきか
	dynamic_cast<MMD::AnimationState::BaseAnimationState *>(pOut.get())->shrinkToFitAllHookContainers();
	return pOut;
}

AnimationModel2::AnimationModel2()
{}

AnimationModel2::~AnimationModel2(){
}

bool AnimationModel2::isReady(){
	if( AnimationModel::isReady() ){
		//for( 
		//	AnimationMap::iterator it=mAnimationMap.begin(), end=mAnimationMap.end();
		//	it!=end;
		//	++it )
		//{
		//}
		for( 
			AccessoryMap::iterator it=mAccessoryMap.begin(), end=mAccessoryMap.end();
			it!=end;
			++it )
		{
			if(it->second->isReady()){
			}else{
				return false;
			}
		}
		return true;
	}else{
		return false;
	}
	return false;

}
void AnimationModel2::drawUsingGameLib() const{
	AnimationModel::draw();
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

void AnimationModel2::preDrawMME() const{
	for(
		AccessoryMap::const_iterator it= mAccessoryMap.begin(), end =mAccessoryMap.end();
		it!=end;
		++it )
	{
		//canDraw();
		if( it->second->canDraw() ){
			it->second->preDrawMMD();
		}
	}
}



std::shared_ptr<GameObject::Accessory> AnimationModel2::getAccessory( const std::string &name ){
	AccessoryMap::iterator it = mAccessoryMap.find( name );
	if( it == mAccessoryMap.end() ){
		TRACE1( "%s not found", name );
		STRONG_ASSERT(false && "not found" );
		return std::shared_ptr<GameObject::Accessory>();
	} else {
		return it->second;
	}
}


//void AnimationModel2::debugDraw() const{
//	//mModel->debugDraw();
//}

/*
void AnimationModel2::loadXML(
	const char *filename,
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
	GameLib::FileIO::InFile xmlFile;
	xmlFile= GameLib::FileIO::InFile::create( filename );
	if( xmlFile.isError() ){
		STRONG_ASSERT(false);
		return;
	}
	while( !xmlFile.isFinished() ){}

	Document modelXml = Document::create( xmlFile.data(), xmlFile.size() );
	if( modelXml.isError() ){
		STRONG_ASSERT(false);
		return;
	}

	ConstElement modelElem= findElement( modelXml.root(), "Model" );
	int numAttributes = modelElem.attributeNumber();
	RefString pmdFile;
	bool enablePhysics=true;

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
	mModel = MME::Object::PmdModel::create();
	mModel->loadPMDFromDB( pmdFile.get(), enablePhysics );
	

	//アクセサリー作成、登録
	{
		ConstElement accessoriesElem = findElement( modelElem, "Accessories");
		int numChild = accessoriesElem.childNumber();
		for(int ic=0; ic<numChild; ++ic ){
			ConstElement e = accessoriesElem.child(ic);
			STRONG_ASSERT(RefString( "Accessory") == e.name() && "element of Accessory is wrong."  );
			//登録
			AccessoryMap::_Pairib pair = mAccessoryMap.insert( createAccessoryPair( ignoredObject, e ) );
			assert(pair.second && "accessory key name is doubled.");
		}
	}
	
	//アニメーション作成
	{
		ConstElement animationsElem = findElement( modelElem, "Animations");
	
		ConstElement e = findElement( animationsElem, "StandAnimation" );
		mStandAnim = createAnimationState( status, e );

		e = findElement( animationsElem, "RunAnimation" );
		mRunAnim = createAnimationState( status, e );

		e = findElement( animationsElem, "PunchAnimation" );
		mPunchAnim = createAnimationState( status, e );
	
		e = findElement( animationsElem, "StumbleAnimation" );
		mStumbleAnim = createAnimationState( status, e);

		e = findElement( animationsElem, "LieAnimation" );
		mLieAnim = createAnimationState( status, e);

		e = findElement( animationsElem, "SwingAnimations" );
		int numChild = e.childNumber();
		for(int ic=0; ic<numChild; ++ic ){
			ConstElement swingElem = e.child(ic);
			assert( RefString("SwingAnimation")==swingElem.name() && "swing animation element name is wrong." );
			mSwingAnims.push_back( createAnimationState( status, swingElem ) );
		}
		mSwingAnims.shrink_to_fit();
	}
}
/*
void AnimationModel2::changeAnimation( const std::string& animName ){
	AnimationMap::iterator it=mAnimationMap.find( animName );
	if(it!=mAnimationMap.end() ){
		AnimationModel::changeAnimation( it->second.get() );
	} else {
		assert(false);
	}
}


void AnimationModel2::addHookToAnim( const std::string &toAnimName, MMD::AnimationState::Hook::IHookSharedPtr hook ){
	AnimationMap::iterator it=mAnimationMap.find( toAnimName );
	if(it!=mAnimationMap.end() ){
		it->second->addHook( hook );
	} else {
		assert(false);
	}
}


/*
void AnimationModel2::draw()const{
	if(mCanDraw){
		AnimationModel::drawByMME();
	}
}

float AnimationModel2::getScale()const{
	return 1.0;
}


	
float AnimationModel2::getFaceValue(const std::string &faceName )const
{
	assert(false);
	return 0;
}

const D3DXMATRIX & AnimationModel2::getBoneMatrix( const std::string &boneName )const
{
	CBone *bone = const_cast<AnimationModel2*>(this)->getBone( boneName.c_str() );
	if(bone){
		return bone->getSkinningMatrix();
	} else{
		static D3DXMATRIX matI( 
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
		);
		return matI;
	}

};

const std::string& AnimationModel2::getModelFileName()const{
	return getModelFileName();
}
*/

}//end namespace MMD
