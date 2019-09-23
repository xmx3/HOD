/*
** Lua binding: luafunc
** Generated automatically by tolua++-1.0.92 on 09/11/19 10:02:20.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_luafunc_open (lua_State* tolua_S);

#include "Lua/LuaHelper.h"
#pragma warning(push)
#pragma warning(disable:4800)
#include "GUI/Manager.h"
#include "GUI/Label.h"
#include "GUI/IComponent.h"
#include "GUI/ImageButton.h"
#include <GameLib/Graphics/Texture.h>
#include "GUI/Window.h"
#include <Telop.h>
#include "../GUI/IModalDialog.h"
#include "../GUI/OkDialog.h"
#include<LinearMath/btTransform.h>
#include<LinearMath/btVector3.h>
#include<LinearMath/btScalar.h>
#include<LinearMath/btMatrix3x3.h>
#include"MMD/MMDDataBase.h"
#include"MMD/Animation.h"
#include"MMD/TemplateVMD.h"
namespace {
	typedef std::pair< unsigned long, boost::shared_array<MMD::BoneKey> > PairSizeAndBoneKeyArray;
	typedef std::pair< unsigned long, boost::shared_array<MMD::FaceKey> > PairSizeAndFaceKeyArray;
	typedef const std::string ConstString;
	typedef std::shared_ptr<ConstString> ConstStringSharedPtr; 
 }
#include"MMD/CameraAnimation.h"
#include<GameLib/Framework.h>
#include <GameLib/Graphics/Manager.h>
#include <GameLib/Graphics/AnimatedVertexBoneBuffer.h>
#include <GameLib/Graphics/VertexBuffer.h>
#include <GameLib/Graphics/IndexBuffer.h>
#include <GameLib/Graphics/Texture.h>
#include <GameLib/PseudoXml/Element.h>
#include<GameLib/Math/Vector4.h>
#include<GameLib/Math/Vector3.h>
#include<GameLib/Math/Matrix44.h>
#include<GameLib/Math/Matrix34.h>
#include<XmlLoader/MME/Object/ModelKai.h>
#include"XmlLoader/GameObject/Accessory.h"
#include"XmlLoader/GameObject/Player.h"
#include"XmlLoader/GameObject/Enemy.h"
#include<MME/Manager.h>
#include<MME/Drawer/CutScene.h>
#include<MME/Drawer/GameDrawer.h>
#include<MME/Object/ModelKai.h>
#include<MME/StandardEffect.h>
#include<MME/PostEffect.h>
#include<BulletPhysics/Manager.h>
#include"Sequence/HatuneOfTheDead/LuaImpl/State.h"
#include"Sequence/HatuneOfTheDead/LuaImpl/Resource.h"
#include"GameObject/Player.h"
#include"GameObject/Enemy.h"
#include"GameObject/Stage.h"
#include"Camera/FixedCamera.h"
#include"HOD/EnemySpawner.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_std__shared_ptr_GameObject__Stage_ (lua_State* tolua_S)
{
 std::shared_ptr<GameObject::Stage>* self = (std::shared_ptr<GameObject::Stage>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_MME__StandardEffect_ (lua_State* tolua_S)
{
 std::shared_ptr<MME::StandardEffect>* self = (std::shared_ptr<MME::StandardEffect>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_MMD__CameraAnimation_ (lua_State* tolua_S)
{
 std::shared_ptr<MMD::CameraAnimation>* self = (std::shared_ptr<MMD::CameraAnimation>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect___GameObject__AccessorySharedPtr (lua_State* tolua_S)
{
 ::GameObject::AccessorySharedPtr* self = (::GameObject::AccessorySharedPtr*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_XmlLoader__MME__Object__ModelKai (lua_State* tolua_S)
{
 XmlLoader::MME::Object::ModelKai* self = (XmlLoader::MME::Object::ModelKai*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GameLib__Math__Matrix34 (lua_State* tolua_S)
{
 GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_GameObject__Accessory_ (lua_State* tolua_S)
{
 std::shared_ptr<GameObject::Accessory>* self = (std::shared_ptr<GameObject::Accessory>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_PairSizeAndBoneKeyArray (lua_State* tolua_S)
{
 PairSizeAndBoneKeyArray* self = (PairSizeAndBoneKeyArray*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_btMatrix3x3 (lua_State* tolua_S)
{
 btMatrix3x3* self = (btMatrix3x3*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_btVector3 (lua_State* tolua_S)
{
 btVector3* self = (btVector3*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GameObject__Player (lua_State* tolua_S)
{
 GameObject::Player* self = (GameObject::Player*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GameObject__Enemy (lua_State* tolua_S)
{
 GameObject::Enemy* self = (GameObject::Enemy*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_XmlLoader__GameObject__Enemy (lua_State* tolua_S)
{
 XmlLoader::GameObject::Enemy* self = (XmlLoader::GameObject::Enemy*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GameLib__Graphics__Manager (lua_State* tolua_S)
{
 GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ConstStringSharedPtr (lua_State* tolua_S)
{
 ConstStringSharedPtr* self = (ConstStringSharedPtr*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_XmlLoader__GameObject__Accessory (lua_State* tolua_S)
{
 XmlLoader::GameObject::Accessory* self = (XmlLoader::GameObject::Accessory*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_MMD__CameraAnimation (lua_State* tolua_S)
{
 MMD::CameraAnimation* self = (MMD::CameraAnimation*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GUI__Label (lua_State* tolua_S)
{
 GUI::Label* self = (GUI::Label*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GUI__OkDialog (lua_State* tolua_S)
{
 GUI::OkDialog* self = (GUI::OkDialog*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_MMD__Animation_ (lua_State* tolua_S)
{
 std::shared_ptr<MMD::Animation>* self = (std::shared_ptr<MMD::Animation>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GameLib__Graphics__Texture (lua_State* tolua_S)
{
 GameLib::Graphics::Texture* self = (GameLib::Graphics::Texture*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_Camera__FixedCamera (lua_State* tolua_S)
{
 Camera::FixedCamera* self = (Camera::FixedCamera*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GameLib__Framework (lua_State* tolua_S)
{
 GameLib::Framework* self = (GameLib::Framework*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_GameObject__Enemy_ (lua_State* tolua_S)
{
 std::shared_ptr<GameObject::Enemy>* self = (std::shared_ptr<GameObject::Enemy>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_XmlLoader__GameObject__Enemy_ (lua_State* tolua_S)
{
 std::shared_ptr<XmlLoader::GameObject::Enemy>* self = (std::shared_ptr<XmlLoader::GameObject::Enemy>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_PairSizeAndFaceKeyArray (lua_State* tolua_S)
{
 PairSizeAndFaceKeyArray* self = (PairSizeAndFaceKeyArray*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_D3DXVECTOR3 (lua_State* tolua_S)
{
 D3DXVECTOR3* self = (D3DXVECTOR3*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GUI__ImageButton (lua_State* tolua_S)
{
 GUI::ImageButton* self = (GUI::ImageButton*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_GameObject__Utils__Character_ (lua_State* tolua_S)
{
 std::shared_ptr<GameObject::Utils::Character>* self = (std::shared_ptr<GameObject::Utils::Character>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_MME__PostEffect (lua_State* tolua_S)
{
 MME::PostEffect* self = (MME::PostEffect*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_MME__StandardEffect (lua_State* tolua_S)
{
 MME::StandardEffect* self = (MME::StandardEffect*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_MME__Object__ModelKai (lua_State* tolua_S)
{
 MME::Object::ModelKai* self = (MME::Object::ModelKai*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_MME__PostEffect_ (lua_State* tolua_S)
{
 std::shared_ptr<MME::PostEffect>* self = (std::shared_ptr<MME::PostEffect>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_MME__MMDPass (lua_State* tolua_S)
{
 MME::MMDPass* self = (MME::MMDPass*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect___GameObject__EnemySharedPtr (lua_State* tolua_S)
{
 ::GameObject::EnemySharedPtr* self = (::GameObject::EnemySharedPtr*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_MMD__AnimationSharedPtr (lua_State* tolua_S)
{
 MMD::AnimationSharedPtr* self = (MMD::AnimationSharedPtr*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_HOD__EnemySpawner (lua_State* tolua_S)
{
 HOD::EnemySpawner* self = (HOD::EnemySpawner*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_D3DXMATRIX (lua_State* tolua_S)
{
 D3DXMATRIX* self = (D3DXMATRIX*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_MMD__TemplateVMD_ (lua_State* tolua_S)
{
 std::shared_ptr<MMD::TemplateVMD>* self = (std::shared_ptr<MMD::TemplateVMD>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_btTransform (lua_State* tolua_S)
{
 btTransform* self = (btTransform*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GameObject__Stage (lua_State* tolua_S)
{
 GameObject::Stage* self = (GameObject::Stage*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_XmlLoader__GameObject__Player (lua_State* tolua_S)
{
 XmlLoader::GameObject::Player* self = (XmlLoader::GameObject::Player*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_GameObject__Player_ (lua_State* tolua_S)
{
 std::shared_ptr<GameObject::Player>* self = (std::shared_ptr<GameObject::Player>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GameLib__Math__Vector3 (lua_State* tolua_S)
{
 GameLib::Math::Vector3* self = (GameLib::Math::Vector3*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_btQuaternion (lua_State* tolua_S)
{
 btQuaternion* self = (btQuaternion*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_MMD__TemplatePMDSharedPtr (lua_State* tolua_S)
{
 MMD::TemplatePMDSharedPtr* self = (MMD::TemplatePMDSharedPtr*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GameLib__Math__Vector4 (lua_State* tolua_S)
{
 GameLib::Math::Vector4* self = (GameLib::Math::Vector4*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_MMD__TemplateVMD (lua_State* tolua_S)
{
 MMD::TemplateVMD* self = (MMD::TemplateVMD*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GameLib__Math__Matrix44 (lua_State* tolua_S)
{
 GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__shared_ptr_MME__Object__ModelKai_ (lua_State* tolua_S)
{
 std::shared_ptr<MME::Object::ModelKai>* self = (std::shared_ptr<MME::Object::ModelKai>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"std::shared_ptr<GameObject::Stage>");
 tolua_usertype(tolua_S,"std::shared_ptr<MME::StandardEffect>");
 tolua_usertype(tolua_S,"std::shared_ptr<MMD::CameraAnimation>");
 tolua_usertype(tolua_S,"Camera::Simple");
 tolua_usertype(tolua_S,"Camera::FixedCamera");
 tolua_usertype(tolua_S,"GUI::BaseComponent");
 tolua_usertype(tolua_S,"GameLib::Scene::Font");
 tolua_usertype(tolua_S,"MME::Manager");
 tolua_usertype(tolua_S,"XmlLoader::Actions");
 tolua_usertype(tolua_S,"MME::Object::IObject");
 tolua_usertype(tolua_S,"MME::Batch::PostEffectBatch");
 tolua_usertype(tolua_S,"GameObject::BaseObject");
 tolua_usertype(tolua_S,"MME::UseTexture");
 tolua_usertype(tolua_S,"GameLib::Graphics::IndexBuffer");
 tolua_usertype(tolua_S,"std::shared_ptr<Camera::ICamera>");
 tolua_usertype(tolua_S,"GameLib::Framework");
 tolua_usertype(tolua_S,"std::shared_ptr<MME::Object::Accessory>");
 tolua_usertype(tolua_S,"std::shared_ptr<GameObject::Enemy>");
 tolua_usertype(tolua_S,"std::shared_ptr<GameObject::Utils::Character>");
 tolua_usertype(tolua_S,"MMD::MMDDataBase");
 tolua_usertype(tolua_S,"btBoxShape");
 tolua_usertype(tolua_S,"GUI::IModalDialog");
 tolua_usertype(tolua_S,"Input::PlayerMouse");
 tolua_usertype(tolua_S,"D3DXMATRIX");
 tolua_usertype(tolua_S,"MME::MMDPass");
 tolua_usertype(tolua_S,"::GameObject::EnemySharedPtr");
 tolua_usertype(tolua_S,"GameObjectData::Status");
 tolua_usertype(tolua_S,"MME::UseSphereMap");
 tolua_usertype(tolua_S,"::GameObject::AccessorySharedPtr");
 tolua_usertype(tolua_S,"XmlLoader::MME::Object::ModelKai");
 tolua_usertype(tolua_S,"RTTI");
 tolua_usertype(tolua_S,"BaseObject");
 tolua_usertype(tolua_S,"MME::UseSelfShadow");
 tolua_usertype(tolua_S,"MMD::TemplateFaceKey");
 tolua_usertype(tolua_S,"XmlLoader::GameObject::Enemy");
 tolua_usertype(tolua_S,"EventManager");
 tolua_usertype(tolua_S,"GUI::Button");
 tolua_usertype(tolua_S,"XmlLoader::GameObject::Accessory");
 tolua_usertype(tolua_S,"D3DMATRIX");
 tolua_usertype(tolua_S,"GameLib::Math::Matrix33");
 tolua_usertype(tolua_S,"std::shared_ptr<GameObject::Player>");
 tolua_usertype(tolua_S,"MMD::TemplateVMD");
 tolua_usertype(tolua_S,"btRigidBody");
 tolua_usertype(tolua_S,"std::shared_ptr<MME::Object::PointLight>");
 tolua_usertype(tolua_S,"MME::UseToon");
 tolua_usertype(tolua_S,"GameObject::Accessory");
 tolua_usertype(tolua_S,"std::shared_ptr<btBoxShape>");
 tolua_usertype(tolua_S,"PairSizeAndFaceKeyArray");
 tolua_usertype(tolua_S,"GameLib::Math::Vector3");
 tolua_usertype(tolua_S,"GameLib::PseudoXml::ConstElement");
 tolua_usertype(tolua_S,"btGhostPairCallback");
 tolua_usertype(tolua_S,"btBroadphaseInterface");
 tolua_usertype(tolua_S,"GUI::ComponentWithRender");
 tolua_usertype(tolua_S,"Input::PlayerMouseSharedPtr");
 tolua_usertype(tolua_S,"std::shared_ptr<MMD::TemplateVMD>");
 tolua_usertype(tolua_S,"MME::Object::Accessory");
 tolua_usertype(tolua_S,"std::shared_ptr<btMotionState>");
 tolua_usertype(tolua_S,"std::shared_ptr<MME::PostEffect>");
 tolua_usertype(tolua_S,"BulletPhysics::CDxBulletDebugDrawer");
 tolua_usertype(tolua_S,"GameLib::Graphics::VertexBuffer");
 tolua_usertype(tolua_S,"GameLib::Math::Matrix34");
 tolua_usertype(tolua_S,"std::shared_ptr<GameObject::Accessory>");
 tolua_usertype(tolua_S,"btDiscreteDynamicsWorld");
 tolua_usertype(tolua_S,"PairSizeAndBoneKeyArray");
 tolua_usertype(tolua_S,"btMatrix3x3");
 tolua_usertype(tolua_S,"btVector3");
 tolua_usertype(tolua_S,"XmlLoader::Shape");
 tolua_usertype(tolua_S,"GameObject::Enemy");
 tolua_usertype(tolua_S,"btPersistentManifold");
 tolua_usertype(tolua_S,"GameObjectData::WeaponStatus");
 tolua_usertype(tolua_S,"GameLib::Graphics::Manager");
 tolua_usertype(tolua_S,"Component::RigidBodyComponent");
 tolua_usertype(tolua_S,"ConstStringSharedPtr");
 tolua_usertype(tolua_S,"Sequence::HatuneOfTheDead::LuaImpl::Resource");
 tolua_usertype(tolua_S,"GUI::Label");
 tolua_usertype(tolua_S,"std::shared_ptr<btRigidBody>");
 tolua_usertype(tolua_S,"MMD::FaceKey");
 tolua_usertype(tolua_S,"MMD::Animation");
 tolua_usertype(tolua_S,"Camera::PlayerCamera");
 tolua_usertype(tolua_S,"MME::BaseEffect");
 tolua_usertype(tolua_S,"btQuaternion");
 tolua_usertype(tolua_S,"D3DXVECTOR3");
 tolua_usertype(tolua_S,"GUI::ImageButton");
 tolua_usertype(tolua_S,"MMD::TemplateBoneKey");
 tolua_usertype(tolua_S,"LPD3DXEFFECTPOOL");
 tolua_usertype(tolua_S,"btCollisionObject");
 tolua_usertype(tolua_S,"MME::PostEffect");
 tolua_usertype(tolua_S,"HOD::EnemySpawner");
 tolua_usertype(tolua_S,"btMatrix3x3Data");
 tolua_usertype(tolua_S,"GameObject::AccessoryUtils::MME::Model");
 tolua_usertype(tolua_S,"GameLib::Framework::Configuration");
 tolua_usertype(tolua_S,"GameObject::Stage");
 tolua_usertype(tolua_S,"btMatrix3x3FloatData");
 tolua_usertype(tolua_S,"std::vector<XmlLoader::GameObject::EnemySharedPtr>");
 tolua_usertype(tolua_S,"BulletPhysics::CSegaBulletDebugDrawer");
 tolua_usertype(tolua_S,"GUI::Manager");
 tolua_usertype(tolua_S,"BulletPhysics::CDxBulletDebugDrawerEx");
 tolua_usertype(tolua_S,"IDirect3DTexture9");
 tolua_usertype(tolua_S,"MME::Object::ModelKai");
 tolua_usertype(tolua_S,"MMD::HumanModel");
 tolua_usertype(tolua_S,"std::shared_ptr<XmlLoader::GameObject::Enemy>");
 tolua_usertype(tolua_S,"btSphereShape");
 tolua_usertype(tolua_S,"GameObject::Utils::Character");
 tolua_usertype(tolua_S,"btMotionState");
 tolua_usertype(tolua_S,"D3DVECTOR");
 tolua_usertype(tolua_S,"btCylinderShape");
 tolua_usertype(tolua_S,"MME::Object::PointLight");
 tolua_usertype(tolua_S,"btCollisionShape");
 tolua_usertype(tolua_S,"std::shared_ptr<GameObject::AccessoryUtils::MME::Model>");
 tolua_usertype(tolua_S,"Camera::ICamera");
 tolua_usertype(tolua_S,"HOD::EnemyManager");
 tolua_usertype(tolua_S,"Sequence::Base");
 tolua_usertype(tolua_S,"GUI::Window");
 tolua_usertype(tolua_S,"Sequence::HatuneOfTheDead::LuaImpl::State");
 tolua_usertype(tolua_S,"btIDebugDraw");
 tolua_usertype(tolua_S,"GameLib::FileIO::InFile");
 tolua_usertype(tolua_S,"GUI::OkDialog");
 tolua_usertype(tolua_S,"btTypedConstraint");
 tolua_usertype(tolua_S,"GameLib::Graphics::Texture");
 tolua_usertype(tolua_S,"BulletPhysics::Manager");
 tolua_usertype(tolua_S,"GameLib::Math::Vector2");
 tolua_usertype(tolua_S,"MMD::CameraOneFrameData");
 tolua_usertype(tolua_S,"BulletPhysics::FilterCallbackUsingGameObject");
 tolua_usertype(tolua_S,"GameObject::ICollider");
 tolua_usertype(tolua_S,"GameObject::AccessoryUtils::MME::TemplateModel");
 tolua_usertype(tolua_S,"MMD::Bone");
 tolua_usertype(tolua_S,"MMD::AnimationModel");
 tolua_usertype(tolua_S,"XmlLoader::Camera::PlayerCamera");
 tolua_usertype(tolua_S,"BaseEffect");
 tolua_usertype(tolua_S,"MMD::AnimationState::IAnimationStateSharedPtr");
 tolua_usertype(tolua_S,"MMD::TemplatePMDSharedPtr");
 tolua_usertype(tolua_S,"MME::StandardEffect");
 tolua_usertype(tolua_S,"std::shared_ptr<MME::Object::ModelKai>");
 tolua_usertype(tolua_S,"MME::Drawer::GameDrawer");
 tolua_usertype(tolua_S,"IDirect3DDevice9");
 tolua_usertype(tolua_S,"GUI::IComponent");
 tolua_usertype(tolua_S,"MMD::BoneKey");
 tolua_usertype(tolua_S,"MME::Batch::StandardEffectBatch");
 tolua_usertype(tolua_S,"GameLib::Math::Vector4");
 tolua_usertype(tolua_S,"std::shared_ptr<MMD::TemplatePMD>");
 tolua_usertype(tolua_S,"GameLib::Graphics::AnimatedVertexBoneBuffer");
 tolua_usertype(tolua_S,"FileLoader");
 tolua_usertype(tolua_S,"btTransform");
 tolua_usertype(tolua_S,"btMatrix3x3DoubleData");
 tolua_usertype(tolua_S,"XmlLoader::GameObject::Player");
 tolua_usertype(tolua_S,"std::shared_ptr<GameObjectData::Status>");
 tolua_usertype(tolua_S,"MMD::CameraAnimation");
 tolua_usertype(tolua_S,"std::shared_ptr<MMD::Animation>");
 tolua_usertype(tolua_S,"std::shared_ptr<btCylinderShape>");
 tolua_usertype(tolua_S,"D3DXVECTOR4");
 tolua_usertype(tolua_S,"GameObject::Player");
 tolua_usertype(tolua_S,"MMD::Face");
 tolua_usertype(tolua_S,"GameLib::Math::Matrix44");
}

/* function: ReloadLuaFiles */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_ReloadLuaFiles00
static int tolua_luafunc_cfunc_ReloadLuaFiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* arg = ((const char*)  tolua_tostring(tolua_S,1,""));
  {
   ReloadLuaFiles(arg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReloadLuaFiles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DoLuaFile */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_DoLuaFile00
static int tolua_luafunc_cfunc_DoLuaFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  DoLuaFile(path);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DoLuaFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: WaitInputOnError */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_WaitInputOnError00
static int tolua_luafunc_cfunc_WaitInputOnError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* mes = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* postfix = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   WaitInputOnError(mes,postfix);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'WaitInputOnError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetLuaError */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_GetLuaError00
static int tolua_luafunc_cfunc_GetLuaError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   const char* tolua_ret = (const char*)  GetLuaError();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLuaError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  GUI::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Manager_instance00
static int tolua_luafunc_GUI_Manager_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUI::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GUI::Manager* tolua_ret = (GUI::Manager*)  GUI::Manager::instance();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GUI::Manager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destory of class  GUI::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Manager_destory00
static int tolua_luafunc_GUI_Manager_destory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUI::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GUI::Manager::destory();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  GUI::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Manager_draw00
static int tolua_luafunc_GUI_Manager_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::Manager* self = (GUI::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'",NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: add of class  GUI::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Manager_add00
static int tolua_luafunc_GUI_Manager_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GUI::IComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::Manager* self = (GUI::Manager*)  tolua_tousertype(tolua_S,1,0);
  GUI::IComponent* component = ((GUI::IComponent*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'add'",NULL);
#endif
  {
   self->add(component);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: remove of class  GUI::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Manager_remove00
static int tolua_luafunc_GUI_Manager_remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GUI::IComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::Manager* self = (GUI::Manager*)  tolua_tousertype(tolua_S,1,0);
  GUI::IComponent* component = ((GUI::IComponent*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'remove'",NULL);
#endif
  {
   self->remove(component);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  GUI::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Manager_isReady00
static int tolua_luafunc_GUI_Manager_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::Manager* self = (GUI::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  GUI::BaseComponent */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_BaseComponent_isEnabled00
static int tolua_luafunc_GUI_BaseComponent_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::BaseComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::BaseComponent* self = (const GUI::BaseComponent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsEnabled of class  GUI::BaseComponent */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_BaseComponent_setIsEnabled00
static int tolua_luafunc_GUI_BaseComponent_setIsEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::BaseComponent",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::BaseComponent* self = (GUI::BaseComponent*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsEnabled'",NULL);
#endif
  {
   self->setIsEnabled(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDrawAble of class  GUI::BaseComponent */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_BaseComponent_isDrawAble00
static int tolua_luafunc_GUI_BaseComponent_isDrawAble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::BaseComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::BaseComponent* self = (const GUI::BaseComponent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDrawAble'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isDrawAble();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDrawAble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsDrawAble of class  GUI::BaseComponent */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_BaseComponent_setIsDrawAble00
static int tolua_luafunc_GUI_BaseComponent_setIsDrawAble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::BaseComponent",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::BaseComponent* self = (GUI::BaseComponent*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsDrawAble'",NULL);
#endif
  {
   self->setIsDrawAble(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsDrawAble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPos of class  GUI::BaseComponent */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_BaseComponent_setPos00
static int tolua_luafunc_GUI_BaseComponent_setPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::BaseComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::BaseComponent* self = (GUI::BaseComponent*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPos'",NULL);
#endif
  {
   self->setPos(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPos of class  GUI::BaseComponent */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_BaseComponent_getPos00
static int tolua_luafunc_GUI_BaseComponent_getPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::BaseComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::BaseComponent* self = (const GUI::BaseComponent*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPos'",NULL);
#endif
  {
   self->getPos(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSize of class  GUI::BaseComponent */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_BaseComponent_setSize00
static int tolua_luafunc_GUI_BaseComponent_setSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::BaseComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::BaseComponent* self = (GUI::BaseComponent*)  tolua_tousertype(tolua_S,1,0);
  int sizeX = ((int)  tolua_tonumber(tolua_S,2,0));
  int sizeY = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSize'",NULL);
#endif
  {
   self->setSize(sizeX,sizeY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  GUI::BaseComponent */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_BaseComponent_getSize00
static int tolua_luafunc_GUI_BaseComponent_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::BaseComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::BaseComponent* self = (const GUI::BaseComponent*)  tolua_tousertype(tolua_S,1,0);
  int sizeX = ((int)  tolua_tonumber(tolua_S,2,0));
  int sizeY = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'",NULL);
#endif
  {
   self->getSize(&sizeX,&sizeY);
   tolua_pushnumber(tolua_S,(lua_Number)sizeX);
   tolua_pushnumber(tolua_S,(lua_Number)sizeY);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isHover of class  GUI::BaseComponent */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_BaseComponent_isHover00
static int tolua_luafunc_GUI_BaseComponent_isHover00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::BaseComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::BaseComponent* self = (const GUI::BaseComponent*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isHover'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isHover(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isHover'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontColor of class  GUI::ComponentWithRender */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ComponentWithRender_setFontColor00
static int tolua_luafunc_GUI_ComponentWithRender_setFontColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ComponentWithRender",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ComponentWithRender* self = (GUI::ComponentWithRender*)  tolua_tousertype(tolua_S,1,0);
  unsigned int fc = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontColor'",NULL);
#endif
  {
   self->setFontColor(fc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  GUI::ComponentWithRender */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ComponentWithRender_setColor00
static int tolua_luafunc_GUI_ComponentWithRender_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ComponentWithRender",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ComponentWithRender* self = (GUI::ComponentWithRender*)  tolua_tousertype(tolua_S,1,0);
  unsigned int c = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'",NULL);
#endif
  {
   self->setColor(c);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsEnableDepthTest of class  GUI::ComponentWithRender */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ComponentWithRender_setIsEnableDepthTest00
static int tolua_luafunc_GUI_ComponentWithRender_setIsEnableDepthTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ComponentWithRender",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ComponentWithRender* self = (GUI::ComponentWithRender*)  tolua_tousertype(tolua_S,1,0);
  bool isdt = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsEnableDepthTest'",NULL);
#endif
  {
   self->setIsEnableDepthTest(isdt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsEnableDepthTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsEnableDepthWrite of class  GUI::ComponentWithRender */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ComponentWithRender_setIsEnableDepthWrite00
static int tolua_luafunc_GUI_ComponentWithRender_setIsEnableDepthWrite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ComponentWithRender",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ComponentWithRender* self = (GUI::ComponentWithRender*)  tolua_tousertype(tolua_S,1,0);
  bool isdw = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsEnableDepthWrite'",NULL);
#endif
  {
   self->setIsEnableDepthWrite(isdw);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsEnableDepthWrite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_new00
static int tolua_luafunc_GUI_ImageButton_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int sizeX = ((int)  tolua_tonumber(tolua_S,4,0));
  int sizeY = ((int)  tolua_tonumber(tolua_S,5,0));
  unsigned int color = ((unsigned int)  tolua_tonumber(tolua_S,6,0xffffffff));
  unsigned int fontColor = ((unsigned int)  tolua_tonumber(tolua_S,7,0xff000000));
  float u0 = ((float)  tolua_tonumber(tolua_S,8,0.f));
  float v0 = ((float)  tolua_tonumber(tolua_S,9,0.f));
  float u1 = ((float)  tolua_tonumber(tolua_S,10,1.f));
  float v1 = ((float)  tolua_tonumber(tolua_S,11,1.f));
  {
   GUI::ImageButton* tolua_ret = (GUI::ImageButton*)  new GUI::ImageButton(x,y,sizeX,sizeY,color,fontColor,u0,v0,u1,v1);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GUI::ImageButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_new00_local
static int tolua_luafunc_GUI_ImageButton_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int sizeX = ((int)  tolua_tonumber(tolua_S,4,0));
  int sizeY = ((int)  tolua_tonumber(tolua_S,5,0));
  unsigned int color = ((unsigned int)  tolua_tonumber(tolua_S,6,0xffffffff));
  unsigned int fontColor = ((unsigned int)  tolua_tonumber(tolua_S,7,0xff000000));
  float u0 = ((float)  tolua_tonumber(tolua_S,8,0.f));
  float v0 = ((float)  tolua_tonumber(tolua_S,9,0.f));
  float u1 = ((float)  tolua_tonumber(tolua_S,10,1.f));
  float v1 = ((float)  tolua_tonumber(tolua_S,11,1.f));
  {
   GUI::ImageButton* tolua_ret = (GUI::ImageButton*)  new GUI::ImageButton(x,y,sizeX,sizeY,color,fontColor,u0,v0,u1,v1);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GUI::ImageButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_delete00
static int tolua_luafunc_GUI_ImageButton_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ImageButton* self = (GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPushed of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_isPushed00
static int tolua_luafunc_GUI_ImageButton_isPushed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::ImageButton* self = (const GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPushed'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPushed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPushed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isHover of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_isHover00
static int tolua_luafunc_GUI_ImageButton_isHover00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::ImageButton* self = (const GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isHover'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isHover();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isHover'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPushing of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_isPushing00
static int tolua_luafunc_GUI_ImageButton_isPushing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::ImageButton* self = (const GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPushing'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPushing();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPushing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_update00
static int tolua_luafunc_GUI_ImageButton_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ImageButton* self = (GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
  {
   self->update();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_draw00
static int tolua_luafunc_GUI_ImageButton_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GUI::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ImageButton* self = (GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
  GUI::Manager* mngr = ((GUI::Manager*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'",NULL);
#endif
  {
   self->draw(mngr);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_setText00
static int tolua_luafunc_GUI_ImageButton_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ImageButton* self = (GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'",NULL);
#endif
  {
   self->setText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTexture of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_setTexture00
static int tolua_luafunc_GUI_ImageButton_setTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ImageButton* self = (GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::Texture t = *((GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTexture'",NULL);
#endif
  {
   self->setTexture(t);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUV of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_setUV00
static int tolua_luafunc_GUI_ImageButton_setUV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ImageButton* self = (GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
  float u0 = ((float)  tolua_tonumber(tolua_S,2,0));
  float v0 = ((float)  tolua_tonumber(tolua_S,3,0));
  float u1 = ((float)  tolua_tonumber(tolua_S,4,0));
  float v1 = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUV'",NULL);
#endif
  {
   self->setUV(u0,v0,u1,v1);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUV'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_isEnabled00
static int tolua_luafunc_GUI_ImageButton_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::ImageButton* self = (const GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsEnabled of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_setIsEnabled00
static int tolua_luafunc_GUI_ImageButton_setIsEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ImageButton* self = (GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsEnabled'",NULL);
#endif
  {
   self->setIsEnabled(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDrawAble of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_isDrawAble00
static int tolua_luafunc_GUI_ImageButton_isDrawAble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::ImageButton* self = (const GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDrawAble'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isDrawAble();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDrawAble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsDrawAble of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_setIsDrawAble00
static int tolua_luafunc_GUI_ImageButton_setIsDrawAble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ImageButton* self = (GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsDrawAble'",NULL);
#endif
  {
   self->setIsDrawAble(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsDrawAble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPos of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_setPos00
static int tolua_luafunc_GUI_ImageButton_setPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ImageButton* self = (GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPos'",NULL);
#endif
  {
   self->setPos(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPos of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_getPos00
static int tolua_luafunc_GUI_ImageButton_getPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::ImageButton* self = (const GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPos'",NULL);
#endif
  {
   self->getPos(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSize of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_setSize00
static int tolua_luafunc_GUI_ImageButton_setSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::ImageButton* self = (GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
  int sizeX = ((int)  tolua_tonumber(tolua_S,2,0));
  int sizeY = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSize'",NULL);
#endif
  {
   self->setSize(sizeX,sizeY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  GUI::ImageButton */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_ImageButton_getSize00
static int tolua_luafunc_GUI_ImageButton_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::ImageButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::ImageButton* self = (const GUI::ImageButton*)  tolua_tousertype(tolua_S,1,0);
  int sizeX = ((int)  tolua_tonumber(tolua_S,2,0));
  int sizeY = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'",NULL);
#endif
  {
   self->getSize(&sizeX,&sizeY);
   tolua_pushnumber(tolua_S,(lua_Number)sizeX);
   tolua_pushnumber(tolua_S,(lua_Number)sizeY);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GUI::Label */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Label_new00
static int tolua_luafunc_GUI_Label_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUI::Label",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int sizeX = ((int)  tolua_tonumber(tolua_S,4,0));
  int sizeY = ((int)  tolua_tonumber(tolua_S,5,0));
  unsigned int color = ((unsigned int)  tolua_tonumber(tolua_S,6,0xffffffff));
  unsigned int fontColor = ((unsigned int)  tolua_tonumber(tolua_S,7,0xff000000));
  float u0 = ((float)  tolua_tonumber(tolua_S,8,0.f));
  float v0 = ((float)  tolua_tonumber(tolua_S,9,0.f));
  float u1 = ((float)  tolua_tonumber(tolua_S,10,1.f));
  float v1 = ((float)  tolua_tonumber(tolua_S,11,1.f));
  {
   GUI::Label* tolua_ret = (GUI::Label*)  new GUI::Label(x,y,sizeX,sizeY,color,fontColor,u0,v0,u1,v1);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GUI::Label");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GUI::Label */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Label_new00_local
static int tolua_luafunc_GUI_Label_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUI::Label",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int sizeX = ((int)  tolua_tonumber(tolua_S,4,0));
  int sizeY = ((int)  tolua_tonumber(tolua_S,5,0));
  unsigned int color = ((unsigned int)  tolua_tonumber(tolua_S,6,0xffffffff));
  unsigned int fontColor = ((unsigned int)  tolua_tonumber(tolua_S,7,0xff000000));
  float u0 = ((float)  tolua_tonumber(tolua_S,8,0.f));
  float v0 = ((float)  tolua_tonumber(tolua_S,9,0.f));
  float u1 = ((float)  tolua_tonumber(tolua_S,10,1.f));
  float v1 = ((float)  tolua_tonumber(tolua_S,11,1.f));
  {
   GUI::Label* tolua_ret = (GUI::Label*)  new GUI::Label(x,y,sizeX,sizeY,color,fontColor,u0,v0,u1,v1);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GUI::Label");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GUI::Label */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Label_delete00
static int tolua_luafunc_GUI_Label_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::Label* self = (GUI::Label*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  GUI::Label */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Label_setText00
static int tolua_luafunc_GUI_Label_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::Label",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::Label* self = (GUI::Label*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'",NULL);
#endif
  {
   self->setText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUV of class  GUI::Label */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_Label_setUV00
static int tolua_luafunc_GUI_Label_setUV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::Label",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::Label* self = (GUI::Label*)  tolua_tousertype(tolua_S,1,0);
  float u0 = ((float)  tolua_tonumber(tolua_S,2,0));
  float v0 = ((float)  tolua_tonumber(tolua_S,3,0));
  float u1 = ((float)  tolua_tonumber(tolua_S,4,0));
  float v1 = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUV'",NULL);
#endif
  {
   self->setUV(u0,v0,u1,v1);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUV'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Telop::insert */
#ifndef TOLUA_DISABLE_tolua_luafunc_Telop_insert00
static int tolua_luafunc_Telop_insert00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* text = ((const char*)  tolua_tostring(tolua_S,1,0));
  float start = ((float)  tolua_tonumber(tolua_S,2,0));
  float duration = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   Telop::insert(text,start,duration);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Telop::setFont */
#ifndef TOLUA_DISABLE_tolua_luafunc_Telop_setFont00
static int tolua_luafunc_Telop_setFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Scene::Font",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Scene::Font tolua_var_1 = *((GameLib::Scene::Font*)  tolua_tousertype(tolua_S,1,0));
  {
   Telop::setFont(tolua_var_1);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Telop::setDefalutDuration */
#ifndef TOLUA_DISABLE_tolua_luafunc_Telop_setDefalutDuration00
static int tolua_luafunc_Telop_setDefalutDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  {
   Telop::setDefalutDuration(duration);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDefalutDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Telop::setDefalutFontColor */
#ifndef TOLUA_DISABLE_tolua_luafunc_Telop_setDefalutFontColor00
static int tolua_luafunc_Telop_setDefalutFontColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int tolua_var_2 = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   Telop::setDefalutFontColor(tolua_var_2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDefalutFontColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Telop::parse */
#ifndef TOLUA_DISABLE_tolua_luafunc_Telop_parse00
static int tolua_luafunc_Telop_parse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* data = ((const char*)  tolua_tostring(tolua_S,1,0));
  unsigned int size = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Telop::parse(data,size);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'parse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: show of class  GUI::IModalDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_IModalDialog_show00
static int tolua_luafunc_GUI_IModalDialog_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::IModalDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::IModalDialog* self = (GUI::IModalDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'",NULL);
#endif
  {
   self->show();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hide of class  GUI::IModalDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_IModalDialog_hide00
static int tolua_luafunc_GUI_IModalDialog_hide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::IModalDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::IModalDialog* self = (GUI::IModalDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hide'",NULL);
#endif
  {
   self->hide();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_new00
static int tolua_luafunc_GUI_OkDialog_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUI::OkDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GUI::OkDialog* tolua_ret = (GUI::OkDialog*)  new GUI::OkDialog();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GUI::OkDialog");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_new00_local
static int tolua_luafunc_GUI_OkDialog_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUI::OkDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GUI::OkDialog* tolua_ret = (GUI::OkDialog*)  new GUI::OkDialog();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GUI::OkDialog");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_delete00
static int tolua_luafunc_GUI_OkDialog_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::OkDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::OkDialog* self = (GUI::OkDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_update00
static int tolua_luafunc_GUI_OkDialog_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::OkDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::OkDialog* self = (GUI::OkDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
  {
   self->update();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_draw00
static int tolua_luafunc_GUI_OkDialog_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::OkDialog",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GUI::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::OkDialog* self = (GUI::OkDialog*)  tolua_tousertype(tolua_S,1,0);
  GUI::Manager* tolua_var_3 = ((GUI::Manager*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'",NULL);
#endif
  {
   self->draw(tolua_var_3);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_isEnabled00
static int tolua_luafunc_GUI_OkDialog_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::OkDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::OkDialog* self = (const GUI::OkDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsEnabled of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_setIsEnabled00
static int tolua_luafunc_GUI_OkDialog_setIsEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::OkDialog",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::OkDialog* self = (GUI::OkDialog*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsEnabled'",NULL);
#endif
  {
   self->setIsEnabled(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDrawAble of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_isDrawAble00
static int tolua_luafunc_GUI_OkDialog_isDrawAble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::OkDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::OkDialog* self = (const GUI::OkDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDrawAble'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isDrawAble();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDrawAble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsDrawAble of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_setIsDrawAble00
static int tolua_luafunc_GUI_OkDialog_setIsDrawAble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::OkDialog",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::OkDialog* self = (GUI::OkDialog*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsDrawAble'",NULL);
#endif
  {
   self->setIsDrawAble(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsDrawAble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_setText00
static int tolua_luafunc_GUI_OkDialog_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUI::OkDialog",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUI::OkDialog* self = (GUI::OkDialog*)  tolua_tousertype(tolua_S,1,0);
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'",NULL);
#endif
  {
   self->setText(text);
   tolua_pushcppstring(tolua_S,(const char*)text);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOk of class  GUI::OkDialog */
#ifndef TOLUA_DISABLE_tolua_luafunc_GUI_OkDialog_isOk00
static int tolua_luafunc_GUI_OkDialog_isOk00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUI::OkDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUI::OkDialog* self = (const GUI::OkDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOk'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOk();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOk'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new00
static int tolua_luafunc_btTransform_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btTransform");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new00_local
static int tolua_luafunc_btTransform_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btTransform");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new01
static int tolua_luafunc_btTransform_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btQuaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btQuaternion* q = ((const btQuaternion*)  tolua_tousertype(tolua_S,2,0));
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform(*q);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new01_local
static int tolua_luafunc_btTransform_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btQuaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btQuaternion* q = ((const btQuaternion*)  tolua_tousertype(tolua_S,2,0));
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform(*q);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new02
static int tolua_luafunc_btTransform_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btQuaternion",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btQuaternion* q = ((const btQuaternion*)  tolua_tousertype(tolua_S,2,0));
  const btVector3* c = ((const btVector3*)  tolua_tousertype(tolua_S,3,0));
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform(*q,*c);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new02_local
static int tolua_luafunc_btTransform_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btQuaternion",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btQuaternion* q = ((const btQuaternion*)  tolua_tousertype(tolua_S,2,0));
  const btVector3* c = ((const btVector3*)  tolua_tousertype(tolua_S,3,0));
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform(*q,*c);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new03
static int tolua_luafunc_btTransform_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btMatrix3x3* b = ((const btMatrix3x3*)  tolua_tousertype(tolua_S,2,0));
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform(*b);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new03_local
static int tolua_luafunc_btTransform_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btMatrix3x3* b = ((const btMatrix3x3*)  tolua_tousertype(tolua_S,2,0));
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform(*b);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new04
static int tolua_luafunc_btTransform_new04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btMatrix3x3* b = ((const btMatrix3x3*)  tolua_tousertype(tolua_S,2,0));
  const btVector3* c = ((const btVector3*)  tolua_tousertype(tolua_S,3,0));
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform(*b,*c);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform_new03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new04_local
static int tolua_luafunc_btTransform_new04_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btMatrix3x3* b = ((const btMatrix3x3*)  tolua_tousertype(tolua_S,2,0));
  const btVector3* c = ((const btVector3*)  tolua_tousertype(tolua_S,3,0));
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform(*b,*c);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform_new03_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new05
static int tolua_luafunc_btTransform_new05(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btTransform* other = ((const btTransform*)  tolua_tousertype(tolua_S,2,0));
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform(*other);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform_new04(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_new05_local
static int tolua_luafunc_btTransform_new05_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btTransform* other = ((const btTransform*)  tolua_tousertype(tolua_S,2,0));
  {
   btTransform* tolua_ret = (btTransform*)  new btTransform(*other);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform_new04_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_delete00
static int tolua_luafunc_btTransform_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btTransform* self = (btTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mult of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_mult00
static int tolua_luafunc_btTransform_mult00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btTransform* self = (btTransform*)  tolua_tousertype(tolua_S,1,0);
  const btTransform* t1 = ((const btTransform*)  tolua_tousertype(tolua_S,2,0));
  const btTransform* t2 = ((const btTransform*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mult'",NULL);
#endif
  {
   self->mult(*t1,*t2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mult'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform__mul00
static int tolua_luafunc_btTransform__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btTransform* self = (const btTransform*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* x = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'",NULL);
#endif
  {
   btVector3 tolua_ret = (btVector3)  self->operator*(*x);
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform__mul01
static int tolua_luafunc_btTransform__mul01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btQuaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btTransform* self = (const btTransform*)  tolua_tousertype(tolua_S,1,0);
  const btQuaternion* q = ((const btQuaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'",NULL);
#endif
  {
   btQuaternion tolua_ret = (btQuaternion)  self->operator*(*q);
   {
#ifdef __cplusplus
    void* tolua_obj = new btQuaternion(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btQuaternion");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btQuaternion));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btQuaternion");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform__mul00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBasis of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_getBasis00
static int tolua_luafunc_btTransform_getBasis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btTransform* self = (btTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBasis'",NULL);
#endif
  {
   btMatrix3x3& tolua_ret = (btMatrix3x3&)  self->getBasis();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"btMatrix3x3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBasis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOrigin of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_getOrigin00
static int tolua_luafunc_btTransform_getOrigin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btTransform* self = (btTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOrigin'",NULL);
#endif
  {
   btVector3& tolua_ret = (btVector3&)  self->getOrigin();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"btVector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOrigin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotation of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_getRotation00
static int tolua_luafunc_btTransform_getRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btTransform* self = (const btTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotation'",NULL);
#endif
  {
   btQuaternion tolua_ret = (btQuaternion)  self->getRotation();
   {
#ifdef __cplusplus
    void* tolua_obj = new btQuaternion(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btQuaternion");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btQuaternion));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btQuaternion");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFromOpenGLMatrix of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_setFromOpenGLMatrix00
static int tolua_luafunc_btTransform_setFromOpenGLMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btTransform* self = (btTransform*)  tolua_tousertype(tolua_S,1,0);
  const float m = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFromOpenGLMatrix'",NULL);
#endif
  {
   self->setFromOpenGLMatrix(&m);
   tolua_pushnumber(tolua_S,(lua_Number)m);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFromOpenGLMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOpenGLMatrix of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_getOpenGLMatrix00
static int tolua_luafunc_btTransform_getOpenGLMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btTransform",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btTransform* self = (const btTransform*)  tolua_tousertype(tolua_S,1,0);
   float m = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOpenGLMatrix'",NULL);
#endif
  {
   self->getOpenGLMatrix(&m);
   tolua_pushnumber(tolua_S,(lua_Number)m);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOpenGLMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOrigin of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_setOrigin00
static int tolua_luafunc_btTransform_setOrigin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btTransform* self = (btTransform*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* origin = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOrigin'",NULL);
#endif
  {
   self->setOrigin(*origin);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOrigin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: invXform of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_invXform00
static int tolua_luafunc_btTransform_invXform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btTransform* self = (const btTransform*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* inVec = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'invXform'",NULL);
#endif
  {
   btVector3 tolua_ret = (btVector3)  self->invXform(*inVec);
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'invXform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBasis of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_setBasis00
static int tolua_luafunc_btTransform_setBasis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btTransform* self = (btTransform*)  tolua_tousertype(tolua_S,1,0);
  const btMatrix3x3* basis = ((const btMatrix3x3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBasis'",NULL);
#endif
  {
   self->setBasis(*basis);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBasis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotation of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_setRotation00
static int tolua_luafunc_btTransform_setRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btQuaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btTransform* self = (btTransform*)  tolua_tousertype(tolua_S,1,0);
  const btQuaternion* q = ((const btQuaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotation'",NULL);
#endif
  {
   self->setRotation(*q);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIdentity of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_setIdentity00
static int tolua_luafunc_btTransform_setIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btTransform* self = (btTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIdentity'",NULL);
#endif
  {
   self->setIdentity();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: inverse of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_inverse00
static int tolua_luafunc_btTransform_inverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btTransform* self = (const btTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'inverse'",NULL);
#endif
  {
   btTransform tolua_ret = (btTransform)  self->inverse();
   {
#ifdef __cplusplus
    void* tolua_obj = new btTransform(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btTransform");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btTransform));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btTransform");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'inverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: inverseTimes of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_inverseTimes00
static int tolua_luafunc_btTransform_inverseTimes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btTransform* self = (const btTransform*)  tolua_tousertype(tolua_S,1,0);
  const btTransform* t = ((const btTransform*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'inverseTimes'",NULL);
#endif
  {
   btTransform tolua_ret = (btTransform)  self->inverseTimes(*t);
   {
#ifdef __cplusplus
    void* tolua_obj = new btTransform(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btTransform");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btTransform));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btTransform");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'inverseTimes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform__mul02
static int tolua_luafunc_btTransform__mul02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btTransform",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btTransform* self = (const btTransform*)  tolua_tousertype(tolua_S,1,0);
  const btTransform* t = ((const btTransform*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'",NULL);
#endif
  {
   btTransform tolua_ret = (btTransform)  self->operator*(*t);
   {
#ifdef __cplusplus
    void* tolua_obj = new btTransform(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btTransform");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btTransform));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btTransform");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btTransform__mul01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIdentity of class  btTransform */
#ifndef TOLUA_DISABLE_tolua_luafunc_btTransform_getIdentity00
static int tolua_luafunc_btTransform_getIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   btTransform tolua_ret = (btTransform)  btTransform::getIdentity();
   {
#ifdef __cplusplus
    void* tolua_obj = new btTransform(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btTransform");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btTransform));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btTransform");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_new00
static int tolua_luafunc_btVector3_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   btVector3* tolua_ret = (btVector3*)  new btVector3();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btVector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_new00_local
static int tolua_luafunc_btVector3_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   btVector3* tolua_ret = (btVector3*)  new btVector3();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btVector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_new01
static int tolua_luafunc_btVector3_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const float _x = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float _y = ((const float)  tolua_tonumber(tolua_S,3,0));
  const float _z = ((const float)  tolua_tonumber(tolua_S,4,0));
  {
   btVector3* tolua_ret = (btVector3*)  new btVector3(_x,_y,_z);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btVector3");
   tolua_pushnumber(tolua_S,(lua_Number)_x);
   tolua_pushnumber(tolua_S,(lua_Number)_y);
   tolua_pushnumber(tolua_S,(lua_Number)_z);
  }
 }
 return 4;
tolua_lerror:
 return tolua_luafunc_btVector3_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_new01_local
static int tolua_luafunc_btVector3_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const float _x = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float _y = ((const float)  tolua_tonumber(tolua_S,3,0));
  const float _z = ((const float)  tolua_tonumber(tolua_S,4,0));
  {
   btVector3* tolua_ret = (btVector3*)  new btVector3(_x,_y,_z);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btVector3");
   tolua_pushnumber(tolua_S,(lua_Number)_x);
   tolua_pushnumber(tolua_S,(lua_Number)_y);
   tolua_pushnumber(tolua_S,(lua_Number)_z);
  }
 }
 return 4;
tolua_lerror:
 return tolua_luafunc_btVector3_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_new02
static int tolua_luafunc_btVector3_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btVector3* rhs = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
  {
   btVector3* tolua_ret = (btVector3*)  new btVector3(*rhs);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btVector3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btVector3_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_new02_local
static int tolua_luafunc_btVector3_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btVector3* rhs = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
  {
   btVector3* tolua_ret = (btVector3*)  new btVector3(*rhs);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btVector3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btVector3_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_delete00
static int tolua_luafunc_btVector3_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dot of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_dot00
static int tolua_luafunc_btVector3_dot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dot'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->dot(*v);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: length2 of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_length200
static int tolua_luafunc_btVector3_length200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'length2'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->length2();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'length2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: length of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_length00
static int tolua_luafunc_btVector3_length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'length'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: norm of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_norm00
static int tolua_luafunc_btVector3_norm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'norm'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->norm();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'norm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: safeNorm of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_safeNorm00
static int tolua_luafunc_btVector3_safeNorm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'safeNorm'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->safeNorm();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'safeNorm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: distance2 of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_distance200
static int tolua_luafunc_btVector3_distance200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'distance2'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->distance2(*v);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'distance2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: distance of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_distance00
static int tolua_luafunc_btVector3_distance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'distance'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->distance(*v);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'distance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: safeNormalize of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_safeNormalize00
static int tolua_luafunc_btVector3_safeNormalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'safeNormalize'",NULL);
#endif
  {
   btVector3& tolua_ret = (btVector3&)  self->safeNormalize();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"btVector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'safeNormalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: normalize of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_normalize00
static int tolua_luafunc_btVector3_normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'normalize'",NULL);
#endif
  {
   btVector3& tolua_ret = (btVector3&)  self->normalize();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"btVector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: normalized of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_normalized00
static int tolua_luafunc_btVector3_normalized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'normalized'",NULL);
#endif
  {
   btVector3 tolua_ret = (btVector3)  self->normalized();
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'normalized'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotate of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_rotate00
static int tolua_luafunc_btVector3_rotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* wAxis = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
  const float angle = ((const float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotate'",NULL);
#endif
  {
   btVector3 tolua_ret = (btVector3)  self->rotate(*wAxis,angle);
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: angle of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_angle00
static int tolua_luafunc_btVector3_angle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'angle'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->angle(*v);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'angle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: absolute of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_absolute00
static int tolua_luafunc_btVector3_absolute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'absolute'",NULL);
#endif
  {
   btVector3 tolua_ret = (btVector3)  self->absolute();
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'absolute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cross of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_cross00
static int tolua_luafunc_btVector3_cross00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cross'",NULL);
#endif
  {
   btVector3 tolua_ret = (btVector3)  self->cross(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cross'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: triple of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_triple00
static int tolua_luafunc_btVector3_triple00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v1 = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
  const btVector3* v2 = ((const btVector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'triple'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->triple(*v1,*v2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'triple'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: minAxis of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_minAxis00
static int tolua_luafunc_btVector3_minAxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'minAxis'",NULL);
#endif
  {
   int tolua_ret = (int)  self->minAxis();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'minAxis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: maxAxis of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_maxAxis00
static int tolua_luafunc_btVector3_maxAxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'maxAxis'",NULL);
#endif
  {
   int tolua_ret = (int)  self->maxAxis();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'maxAxis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: furthestAxis of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_furthestAxis00
static int tolua_luafunc_btVector3_furthestAxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'furthestAxis'",NULL);
#endif
  {
   int tolua_ret = (int)  self->furthestAxis();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'furthestAxis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closestAxis of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_closestAxis00
static int tolua_luafunc_btVector3_closestAxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closestAxis'",NULL);
#endif
  {
   int tolua_ret = (int)  self->closestAxis();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closestAxis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInterpolate3 of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_setInterpolate300
static int tolua_luafunc_btVector3_setInterpolate300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const btVector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v0 = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
  const btVector3* v1 = ((const btVector3*)  tolua_tousertype(tolua_S,3,0));
   float rt = ((  float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInterpolate3'",NULL);
#endif
  {
   self->setInterpolate3(*v0,*v1,rt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInterpolate3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: lerp of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_lerp00
static int tolua_luafunc_btVector3_lerp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
  const float t = ((const float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'lerp'",NULL);
#endif
  {
   btVector3 tolua_ret = (btVector3)  self->lerp(*v,t);
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#endif
   }
   tolua_pushnumber(tolua_S,(lua_Number)t);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'lerp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getX of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_getX00
static int tolua_luafunc_btVector3_getX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getX'",NULL);
#endif
  {
    const float tolua_ret = (  const float)  self->getX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getY of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_getY00
static int tolua_luafunc_btVector3_getY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getY'",NULL);
#endif
  {
    const float tolua_ret = (  const float)  self->getY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZ of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_getZ00
static int tolua_luafunc_btVector3_getZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZ'",NULL);
#endif
  {
    const float tolua_ret = (  const float)  self->getZ();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setX of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_setX00
static int tolua_luafunc_btVector3_setX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
   float _x = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setX'",NULL);
#endif
  {
   self->setX(_x);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setY of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_setY00
static int tolua_luafunc_btVector3_setY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
   float _y = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setY'",NULL);
#endif
  {
   self->setY(_y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZ of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_setZ00
static int tolua_luafunc_btVector3_setZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
   float _z = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZ'",NULL);
#endif
  {
   self->setZ(_z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setW of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_setW00
static int tolua_luafunc_btVector3_setW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
   float _w = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setW'",NULL);
#endif
  {
   self->setW(_w);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setW'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: x of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_x00
static int tolua_luafunc_btVector3_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'x'",NULL);
#endif
  {
    const float tolua_ret = (  const float)  self->x();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: y of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_y00
static int tolua_luafunc_btVector3_y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'y'",NULL);
#endif
  {
    const float tolua_ret = (  const float)  self->y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: z of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_z00
static int tolua_luafunc_btVector3_z00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'z'",NULL);
#endif
  {
    const float tolua_ret = (  const float)  self->z();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'z'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: w of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_w00
static int tolua_luafunc_btVector3_w00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'w'",NULL);
#endif
  {
    const float tolua_ret = (  const float)  self->w();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'w'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3__eq00
static int tolua_luafunc_btVector3__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* other = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMax of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_setMax00
static int tolua_luafunc_btVector3_setMax00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* other = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMax'",NULL);
#endif
  {
   self->setMax(*other);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMax'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMin of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_setMin00
static int tolua_luafunc_btVector3_setMin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* other = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMin'",NULL);
#endif
  {
   self->setMin(*other);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setValue of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_setValue00
static int tolua_luafunc_btVector3_setValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
  const float _x = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float _y = ((const float)  tolua_tonumber(tolua_S,3,0));
  const float _z = ((const float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setValue'",NULL);
#endif
  {
   self->setValue(_x,_y,_z);
   tolua_pushnumber(tolua_S,(lua_Number)_x);
   tolua_pushnumber(tolua_S,(lua_Number)_y);
   tolua_pushnumber(tolua_S,(lua_Number)_z);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSkewSymmetricMatrix of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_getSkewSymmetricMatrix00
static int tolua_luafunc_btVector3_getSkewSymmetricMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"btVector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
  btVector3* v0 = ((btVector3*)  tolua_tousertype(tolua_S,2,0));
  btVector3* v1 = ((btVector3*)  tolua_tousertype(tolua_S,3,0));
  btVector3* v2 = ((btVector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSkewSymmetricMatrix'",NULL);
#endif
  {
   self->getSkewSymmetricMatrix(v0,v1,v2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSkewSymmetricMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZero of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_setZero00
static int tolua_luafunc_btVector3_setZero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btVector3* self = (btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZero'",NULL);
#endif
  {
   self->setZero();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isZero of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_isZero00
static int tolua_luafunc_btVector3_isZero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isZero'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isZero();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isZero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fuzzyZero of class  btVector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btVector3_fuzzyZero00
static int tolua_luafunc_btVector3_fuzzyZero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btVector3* self = (const btVector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fuzzyZero'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->fuzzyZero();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fuzzyZero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_new00
static int tolua_luafunc_btMatrix3x3_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   btMatrix3x3* tolua_ret = (btMatrix3x3*)  new btMatrix3x3();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btMatrix3x3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_new00_local
static int tolua_luafunc_btMatrix3x3_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   btMatrix3x3* tolua_ret = (btMatrix3x3*)  new btMatrix3x3();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btMatrix3x3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_new01
static int tolua_luafunc_btMatrix3x3_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btQuaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btQuaternion* q = ((const btQuaternion*)  tolua_tousertype(tolua_S,2,0));
  {
   btMatrix3x3* tolua_ret = (btMatrix3x3*)  new btMatrix3x3(*q);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btMatrix3x3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btMatrix3x3_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_new01_local
static int tolua_luafunc_btMatrix3x3_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btQuaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btQuaternion* q = ((const btQuaternion*)  tolua_tousertype(tolua_S,2,0));
  {
   btMatrix3x3* tolua_ret = (btMatrix3x3*)  new btMatrix3x3(*q);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btMatrix3x3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btMatrix3x3_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_new02
static int tolua_luafunc_btMatrix3x3_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const float xx = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float xy = ((const float)  tolua_tonumber(tolua_S,3,0));
  const float xz = ((const float)  tolua_tonumber(tolua_S,4,0));
  const float yx = ((const float)  tolua_tonumber(tolua_S,5,0));
  const float yy = ((const float)  tolua_tonumber(tolua_S,6,0));
  const float yz = ((const float)  tolua_tonumber(tolua_S,7,0));
  const float zx = ((const float)  tolua_tonumber(tolua_S,8,0));
  const float zy = ((const float)  tolua_tonumber(tolua_S,9,0));
  const float zz = ((const float)  tolua_tonumber(tolua_S,10,0));
  {
   btMatrix3x3* tolua_ret = (btMatrix3x3*)  new btMatrix3x3(xx,xy,xz,yx,yy,yz,zx,zy,zz);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btMatrix3x3");
   tolua_pushnumber(tolua_S,(lua_Number)xx);
   tolua_pushnumber(tolua_S,(lua_Number)xy);
   tolua_pushnumber(tolua_S,(lua_Number)xz);
   tolua_pushnumber(tolua_S,(lua_Number)yx);
   tolua_pushnumber(tolua_S,(lua_Number)yy);
   tolua_pushnumber(tolua_S,(lua_Number)yz);
   tolua_pushnumber(tolua_S,(lua_Number)zx);
   tolua_pushnumber(tolua_S,(lua_Number)zy);
   tolua_pushnumber(tolua_S,(lua_Number)zz);
  }
 }
 return 10;
tolua_lerror:
 return tolua_luafunc_btMatrix3x3_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_new02_local
static int tolua_luafunc_btMatrix3x3_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const float xx = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float xy = ((const float)  tolua_tonumber(tolua_S,3,0));
  const float xz = ((const float)  tolua_tonumber(tolua_S,4,0));
  const float yx = ((const float)  tolua_tonumber(tolua_S,5,0));
  const float yy = ((const float)  tolua_tonumber(tolua_S,6,0));
  const float yz = ((const float)  tolua_tonumber(tolua_S,7,0));
  const float zx = ((const float)  tolua_tonumber(tolua_S,8,0));
  const float zy = ((const float)  tolua_tonumber(tolua_S,9,0));
  const float zz = ((const float)  tolua_tonumber(tolua_S,10,0));
  {
   btMatrix3x3* tolua_ret = (btMatrix3x3*)  new btMatrix3x3(xx,xy,xz,yx,yy,yz,zx,zy,zz);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btMatrix3x3");
   tolua_pushnumber(tolua_S,(lua_Number)xx);
   tolua_pushnumber(tolua_S,(lua_Number)xy);
   tolua_pushnumber(tolua_S,(lua_Number)xz);
   tolua_pushnumber(tolua_S,(lua_Number)yx);
   tolua_pushnumber(tolua_S,(lua_Number)yy);
   tolua_pushnumber(tolua_S,(lua_Number)yz);
   tolua_pushnumber(tolua_S,(lua_Number)zx);
   tolua_pushnumber(tolua_S,(lua_Number)zy);
   tolua_pushnumber(tolua_S,(lua_Number)zz);
  }
 }
 return 10;
tolua_lerror:
 return tolua_luafunc_btMatrix3x3_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_new03
static int tolua_luafunc_btMatrix3x3_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btMatrix3x3* other = ((const btMatrix3x3*)  tolua_tousertype(tolua_S,2,0));
  {
   btMatrix3x3* tolua_ret = (btMatrix3x3*)  new btMatrix3x3(*other);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btMatrix3x3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btMatrix3x3_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_new03_local
static int tolua_luafunc_btMatrix3x3_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btMatrix3x3* other = ((const btMatrix3x3*)  tolua_tousertype(tolua_S,2,0));
  {
   btMatrix3x3* tolua_ret = (btMatrix3x3*)  new btMatrix3x3(*other);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"btMatrix3x3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btMatrix3x3_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getColumn of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_getColumn00
static int tolua_luafunc_btMatrix3x3_getColumn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColumn'",NULL);
#endif
  {
   btVector3 tolua_ret = (btVector3)  self->getColumn(i);
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getColumn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRow of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_getRow00
static int tolua_luafunc_btMatrix3x3_getRow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRow'",NULL);
#endif
  {
   const btVector3& tolua_ret = (const btVector3&)  self->getRow(i);
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const btVector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3__seti00
static int tolua_luafunc_btMatrix3x3__seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  btVector3 tolua_value = *((btVector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'",NULL);
#endif
  self->operator[](i) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3__geti00
static int tolua_luafunc_btMatrix3x3__geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'",NULL);
#endif
  {
   btVector3 tolua_ret = (btVector3)  self->operator[](i);
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3__geti01
static int tolua_luafunc_btMatrix3x3__geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'",NULL);
#endif
  {
   const btVector3 tolua_ret = (const btVector3)  self->operator[](i);
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"const btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"const btVector3");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_btMatrix3x3__geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFromOpenGLSubMatrix of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_setFromOpenGLSubMatrix00
static int tolua_luafunc_btMatrix3x3_setFromOpenGLSubMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const float m = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFromOpenGLSubMatrix'",NULL);
#endif
  {
   self->setFromOpenGLSubMatrix(&m);
   tolua_pushnumber(tolua_S,(lua_Number)m);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFromOpenGLSubMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setValue of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_setValue00
static int tolua_luafunc_btMatrix3x3_setValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const float xx = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float xy = ((const float)  tolua_tonumber(tolua_S,3,0));
  const float xz = ((const float)  tolua_tonumber(tolua_S,4,0));
  const float yx = ((const float)  tolua_tonumber(tolua_S,5,0));
  const float yy = ((const float)  tolua_tonumber(tolua_S,6,0));
  const float yz = ((const float)  tolua_tonumber(tolua_S,7,0));
  const float zx = ((const float)  tolua_tonumber(tolua_S,8,0));
  const float zy = ((const float)  tolua_tonumber(tolua_S,9,0));
  const float zz = ((const float)  tolua_tonumber(tolua_S,10,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setValue'",NULL);
#endif
  {
   self->setValue(xx,xy,xz,yx,yy,yz,zx,zy,zz);
   tolua_pushnumber(tolua_S,(lua_Number)xx);
   tolua_pushnumber(tolua_S,(lua_Number)xy);
   tolua_pushnumber(tolua_S,(lua_Number)xz);
   tolua_pushnumber(tolua_S,(lua_Number)yx);
   tolua_pushnumber(tolua_S,(lua_Number)yy);
   tolua_pushnumber(tolua_S,(lua_Number)yz);
   tolua_pushnumber(tolua_S,(lua_Number)zx);
   tolua_pushnumber(tolua_S,(lua_Number)zy);
   tolua_pushnumber(tolua_S,(lua_Number)zz);
  }
 }
 return 9;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotation of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_setRotation00
static int tolua_luafunc_btMatrix3x3_setRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btQuaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const btQuaternion* q = ((const btQuaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotation'",NULL);
#endif
  {
   self->setRotation(*q);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEulerYPR of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_setEulerYPR00
static int tolua_luafunc_btMatrix3x3_setEulerYPR00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const float yaw = ((const float)  tolua_tonumber(tolua_S,2,0));
  const float pitch = ((const float)  tolua_tonumber(tolua_S,3,0));
  const float roll = ((const float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEulerYPR'",NULL);
#endif
  {
   self->setEulerYPR(yaw,pitch,roll);
   tolua_pushnumber(tolua_S,(lua_Number)yaw);
   tolua_pushnumber(tolua_S,(lua_Number)pitch);
   tolua_pushnumber(tolua_S,(lua_Number)roll);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEulerYPR'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEulerZYX of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_setEulerZYX00
static int tolua_luafunc_btMatrix3x3_setEulerZYX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
   float eulerX = ((  float)  tolua_tonumber(tolua_S,2,0));
   float eulerY = ((  float)  tolua_tonumber(tolua_S,3,0));
   float eulerZ = ((  float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEulerZYX'",NULL);
#endif
  {
   self->setEulerZYX(eulerX,eulerY,eulerZ);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEulerZYX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIdentity of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_setIdentity00
static int tolua_luafunc_btMatrix3x3_setIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIdentity'",NULL);
#endif
  {
   self->setIdentity();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIdentity of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_getIdentity00
static int tolua_luafunc_btMatrix3x3_getIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   btMatrix3x3 tolua_ret = (btMatrix3x3)  btMatrix3x3::getIdentity();
   {
#ifdef __cplusplus
    void* tolua_obj = new btMatrix3x3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btMatrix3x3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btMatrix3x3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btMatrix3x3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOpenGLSubMatrix of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_getOpenGLSubMatrix00
static int tolua_luafunc_btMatrix3x3_getOpenGLSubMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
   float m = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOpenGLSubMatrix'",NULL);
#endif
  {
   self->getOpenGLSubMatrix(&m);
   tolua_pushnumber(tolua_S,(lua_Number)m);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOpenGLSubMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotation of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_getRotation00
static int tolua_luafunc_btMatrix3x3_getRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btQuaternion",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  btQuaternion* q = ((btQuaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotation'",NULL);
#endif
  {
   self->getRotation(*q);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEulerYPR of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_getEulerYPR00
static int tolua_luafunc_btMatrix3x3_getEulerYPR00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
   float yaw = ((  float)  tolua_tonumber(tolua_S,2,0));
   float pitch = ((  float)  tolua_tonumber(tolua_S,3,0));
   float roll = ((  float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEulerYPR'",NULL);
#endif
  {
   self->getEulerYPR(yaw,pitch,roll);
   tolua_pushnumber(tolua_S,(lua_Number)yaw);
   tolua_pushnumber(tolua_S,(lua_Number)pitch);
   tolua_pushnumber(tolua_S,(lua_Number)roll);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEulerYPR'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEulerZYX of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_getEulerZYX00
static int tolua_luafunc_btMatrix3x3_getEulerZYX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
   float yaw = ((  float)  tolua_tonumber(tolua_S,2,0));
   float pitch = ((  float)  tolua_tonumber(tolua_S,3,0));
   float roll = ((  float)  tolua_tonumber(tolua_S,4,0));
  unsigned int solution_number = ((unsigned int)  tolua_tonumber(tolua_S,5,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEulerZYX'",NULL);
#endif
  {
   self->getEulerZYX(yaw,pitch,roll,solution_number);
   tolua_pushnumber(tolua_S,(lua_Number)yaw);
   tolua_pushnumber(tolua_S,(lua_Number)pitch);
   tolua_pushnumber(tolua_S,(lua_Number)roll);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEulerZYX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scaled of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_scaled00
static int tolua_luafunc_btMatrix3x3_scaled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* s = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scaled'",NULL);
#endif
  {
   btMatrix3x3 tolua_ret = (btMatrix3x3)  self->scaled(*s);
   {
#ifdef __cplusplus
    void* tolua_obj = new btMatrix3x3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btMatrix3x3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btMatrix3x3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btMatrix3x3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scaled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: transposeTimes of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_transposeTimes00
static int tolua_luafunc_btMatrix3x3_transposeTimes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const btMatrix3x3* m = ((const btMatrix3x3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'transposeTimes'",NULL);
#endif
  {
   btMatrix3x3 tolua_ret = (btMatrix3x3)  self->transposeTimes(*m);
   {
#ifdef __cplusplus
    void* tolua_obj = new btMatrix3x3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btMatrix3x3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btMatrix3x3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btMatrix3x3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'transposeTimes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: timesTranspose of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_timesTranspose00
static int tolua_luafunc_btMatrix3x3_timesTranspose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const btMatrix3x3* m = ((const btMatrix3x3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'timesTranspose'",NULL);
#endif
  {
   btMatrix3x3 tolua_ret = (btMatrix3x3)  self->timesTranspose(*m);
   {
#ifdef __cplusplus
    void* tolua_obj = new btMatrix3x3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btMatrix3x3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btMatrix3x3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btMatrix3x3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'timesTranspose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tdotx of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_tdotx00
static int tolua_luafunc_btMatrix3x3_tdotx00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tdotx'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->tdotx(*v);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tdotx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tdoty of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_tdoty00
static int tolua_luafunc_btMatrix3x3_tdoty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tdoty'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->tdoty(*v);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tdoty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tdotz of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_tdotz00
static int tolua_luafunc_btMatrix3x3_tdotz00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const btVector3* v = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tdotz'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->tdotz(*v);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tdotz'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: diagonalize of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_diagonalize00
static int tolua_luafunc_btMatrix3x3_diagonalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  btMatrix3x3* rot = ((btMatrix3x3*)  tolua_tousertype(tolua_S,2,0));
   float threshold = ((  float)  tolua_tonumber(tolua_S,3,0));
  int maxSteps = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'diagonalize'",NULL);
#endif
  {
   self->diagonalize(*rot,threshold,maxSteps);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'diagonalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cofac of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_cofac00
static int tolua_luafunc_btMatrix3x3_cofac00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  int r1 = ((int)  tolua_tonumber(tolua_S,2,0));
  int c1 = ((int)  tolua_tonumber(tolua_S,3,0));
  int r2 = ((int)  tolua_tonumber(tolua_S,4,0));
  int c2 = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cofac'",NULL);
#endif
  {
    float tolua_ret = (  float)  self->cofac(r1,c1,r2,c2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cofac'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: serialize of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_serialize00
static int tolua_luafunc_btMatrix3x3_serialize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btMatrix3x3Data",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  btMatrix3x3Data* dataOut = ((btMatrix3x3Data*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'serialize'",NULL);
#endif
  {
   self->serialize(*dataOut);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'serialize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: serializeFloat of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_serializeFloat00
static int tolua_luafunc_btMatrix3x3_serializeFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btMatrix3x3FloatData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btMatrix3x3* self = (const btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  btMatrix3x3FloatData* dataOut = ((btMatrix3x3FloatData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'serializeFloat'",NULL);
#endif
  {
   self->serializeFloat(*dataOut);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'serializeFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: deSerialize of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_deSerialize00
static int tolua_luafunc_btMatrix3x3_deSerialize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3Data",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const btMatrix3x3Data* dataIn = ((const btMatrix3x3Data*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'deSerialize'",NULL);
#endif
  {
   self->deSerialize(*dataIn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'deSerialize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: deSerializeFloat of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_deSerializeFloat00
static int tolua_luafunc_btMatrix3x3_deSerializeFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3FloatData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const btMatrix3x3FloatData* dataIn = ((const btMatrix3x3FloatData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'deSerializeFloat'",NULL);
#endif
  {
   self->deSerializeFloat(*dataIn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'deSerializeFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: deSerializeDouble of class  btMatrix3x3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_btMatrix3x3_deSerializeDouble00
static int tolua_luafunc_btMatrix3x3_deSerializeDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"btMatrix3x3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btMatrix3x3DoubleData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  btMatrix3x3* self = (btMatrix3x3*)  tolua_tousertype(tolua_S,1,0);
  const btMatrix3x3DoubleData* dataIn = ((const btMatrix3x3DoubleData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'deSerializeDouble'",NULL);
#endif
  {
   self->deSerializeDouble(*dataIn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'deSerializeDouble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  MMD::MMDDataBase */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_MMDDataBase_instance00
static int tolua_luafunc_MMD_MMDDataBase_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MMD::MMDDataBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MMD::MMDDataBase* tolua_ret = (MMD::MMDDataBase*)  MMD::MMDDataBase::instance();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MMD::MMDDataBase");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  MMD::MMDDataBase */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_MMDDataBase_destroy00
static int tolua_luafunc_MMD_MMDDataBase_destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MMD::MMDDataBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MMD::MMDDataBase::destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadPMD of class  MMD::MMDDataBase */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_MMDDataBase_loadPMD00
static int tolua_luafunc_MMD_MMDDataBase_loadPMD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MMD::MMDDataBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MMD::TemplatePMDSharedPtr tolua_ret = (MMD::TemplatePMDSharedPtr)  MMD::MMDDataBase::loadPMD(filename);
   {
#ifdef __cplusplus
    void* tolua_obj = new MMD::TemplatePMDSharedPtr(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"MMD::TemplatePMDSharedPtr");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MMD::TemplatePMDSharedPtr));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"MMD::TemplatePMDSharedPtr");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadPMD'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadVMD of class  MMD::MMDDataBase */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_MMDDataBase_loadVMD00
static int tolua_luafunc_MMD_MMDDataBase_loadVMD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MMD::MMDDataBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   std::shared_ptr<MMD::TemplateVMD> tolua_ret = (std::shared_ptr<MMD::TemplateVMD>)  MMD::MMDDataBase::loadVMD(filename);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<MMD::TemplateVMD>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MMD::TemplateVMD>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<MMD::TemplateVMD>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MMD::TemplateVMD>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadVMD'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  MMD::MMDDataBase */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_MMDDataBase_isReady00
static int tolua_luafunc_MMD_MMDDataBase_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MMD::MMDDataBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  MMD::MMDDataBase::isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createAnimationVMD of class  MMD::MMDDataBase */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_MMDDataBase_createAnimationVMD00
static int tolua_luafunc_MMD_MMDDataBase_createAnimationVMD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MMD::MMDDataBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"MMD::Bone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"MMD::Face",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pmdFilename = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* vmdFilename = ((const char*)  tolua_tostring(tolua_S,3,0));
  MMD::Bone* bones = ((MMD::Bone*)  tolua_tousertype(tolua_S,4,0));
  unsigned long numBone = ((unsigned long)  tolua_tonumber(tolua_S,5,0));
  MMD::Face* faces = ((MMD::Face*)  tolua_tousertype(tolua_S,6,0));
  unsigned long numFaces = ((unsigned long)  tolua_tonumber(tolua_S,7,0));
  {
   MMD::AnimationSharedPtr tolua_ret = (MMD::AnimationSharedPtr)  MMD::MMDDataBase::createAnimationVMD(pmdFilename,vmdFilename,bones,numBone,faces,numFaces);
   {
#ifdef __cplusplus
    void* tolua_obj = new MMD::AnimationSharedPtr(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"MMD::AnimationSharedPtr");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MMD::AnimationSharedPtr));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"MMD::AnimationSharedPtr");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createAnimationVMD'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCameraAnimation of class  MMD::MMDDataBase */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_MMDDataBase_getCameraAnimation00
static int tolua_luafunc_MMD_MMDDataBase_getCameraAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MMD::MMDDataBase",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MMD::MMDDataBase* self = (const MMD::MMDDataBase*)  tolua_tousertype(tolua_S,1,0);
  const std::string vmdFileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCameraAnimation'",NULL);
#endif
  {
   std::shared_ptr<MMD::CameraAnimation> tolua_ret = (std::shared_ptr<MMD::CameraAnimation>)  self->getCameraAnimation(vmdFileName);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<MMD::CameraAnimation>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MMD::CameraAnimation>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<MMD::CameraAnimation>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MMD::CameraAnimation>");
#endif
   }
   tolua_pushcppstring(tolua_S,(const char*)vmdFileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCameraAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  MMD::TemplateVMD */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_TemplateVMD_new00
static int tolua_luafunc_MMD_TemplateVMD_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MMD::TemplateVMD",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MMD::TemplateVMD* tolua_ret = (MMD::TemplateVMD*)  new MMD::TemplateVMD(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MMD::TemplateVMD");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  MMD::TemplateVMD */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_TemplateVMD_new00_local
static int tolua_luafunc_MMD_TemplateVMD_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MMD::TemplateVMD",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MMD::TemplateVMD* tolua_ret = (MMD::TemplateVMD*)  new MMD::TemplateVMD(name);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"MMD::TemplateVMD");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  MMD::TemplateVMD */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_TemplateVMD_delete00
static int tolua_luafunc_MMD_TemplateVMD_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MMD::TemplateVMD",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MMD::TemplateVMD* self = (MMD::TemplateVMD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  MMD::TemplateVMD */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_TemplateVMD_create00
static int tolua_luafunc_MMD_TemplateVMD_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MMD::TemplateVMD",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MMD::Bone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"MMD::Face",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MMD::TemplateVMD* self = (MMD::TemplateVMD*)  tolua_tousertype(tolua_S,1,0);
  MMD::Bone* bones = ((MMD::Bone*)  tolua_tousertype(tolua_S,2,0));
  unsigned long numBone = ((unsigned long)  tolua_tonumber(tolua_S,3,0));
  MMD::Face* faces = ((MMD::Face*)  tolua_tousertype(tolua_S,4,0));
  unsigned long numFaces = ((unsigned long)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'create'",NULL);
#endif
  {
    std::shared_ptr<MMD::Animation> tolua_ret = (  std::shared_ptr<MMD::Animation>)  self->create(bones,numBone,faces,numFaces);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<MMD::Animation>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MMD::Animation>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<MMD::Animation>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MMD::Animation>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createBoneKeyArray of class  MMD::TemplateVMD */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_TemplateVMD_createBoneKeyArray00
static int tolua_luafunc_MMD_TemplateVMD_createBoneKeyArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MMD::TemplateVMD",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MMD::Bone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MMD::TemplateVMD* self = (const MMD::TemplateVMD*)  tolua_tousertype(tolua_S,1,0);
  MMD::Bone* bones = ((MMD::Bone*)  tolua_tousertype(tolua_S,2,0));
  unsigned long numBone = ((unsigned long)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createBoneKeyArray'",NULL);
#endif
  {
   PairSizeAndBoneKeyArray tolua_ret = (PairSizeAndBoneKeyArray)  self->createBoneKeyArray(bones,numBone);
   {
#ifdef __cplusplus
    void* tolua_obj = new PairSizeAndBoneKeyArray(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"PairSizeAndBoneKeyArray");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(PairSizeAndBoneKeyArray));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"PairSizeAndBoneKeyArray");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createBoneKeyArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createFaceKeyArray of class  MMD::TemplateVMD */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_TemplateVMD_createFaceKeyArray00
static int tolua_luafunc_MMD_TemplateVMD_createFaceKeyArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MMD::TemplateVMD",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MMD::Face",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MMD::TemplateVMD* self = (const MMD::TemplateVMD*)  tolua_tousertype(tolua_S,1,0);
  MMD::Face* Faces = ((MMD::Face*)  tolua_tousertype(tolua_S,2,0));
  unsigned long numFaces = ((unsigned long)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createFaceKeyArray'",NULL);
#endif
  {
   PairSizeAndFaceKeyArray tolua_ret = (PairSizeAndFaceKeyArray)  self->createFaceKeyArray(Faces,numFaces);
   {
#ifdef __cplusplus
    void* tolua_obj = new PairSizeAndFaceKeyArray(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"PairSizeAndFaceKeyArray");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(PairSizeAndFaceKeyArray));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"PairSizeAndFaceKeyArray");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createFaceKeyArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFileName of class  MMD::TemplateVMD */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_TemplateVMD_getFileName00
static int tolua_luafunc_MMD_TemplateVMD_getFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MMD::TemplateVMD",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MMD::TemplateVMD* self = (const MMD::TemplateVMD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFileName'",NULL);
#endif
  {
   ConstStringSharedPtr tolua_ret = (ConstStringSharedPtr)  self->getFileName();
   {
#ifdef __cplusplus
    void* tolua_obj = new ConstStringSharedPtr(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"ConstStringSharedPtr");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ConstStringSharedPtr));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"ConstStringSharedPtr");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  MMD::TemplateVMD */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_TemplateVMD_isReady00
static int tolua_luafunc_MMD_TemplateVMD_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MMD::TemplateVMD",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MMD::TemplateVMD* self = (MMD::TemplateVMD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCameraAnimation of class  MMD::TemplateVMD */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_TemplateVMD_getCameraAnimation00
static int tolua_luafunc_MMD_TemplateVMD_getCameraAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MMD::TemplateVMD",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MMD::TemplateVMD* self = (const MMD::TemplateVMD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCameraAnimation'",NULL);
#endif
  {
   std::shared_ptr<MMD::CameraAnimation> tolua_ret = (std::shared_ptr<MMD::CameraAnimation>)  self->getCameraAnimation();
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<MMD::CameraAnimation>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MMD::CameraAnimation>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<MMD::CameraAnimation>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MMD::CameraAnimation>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCameraAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  MMD::CameraAnimation */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_CameraAnimation_new00
static int tolua_luafunc_MMD_CameraAnimation_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MMD::CameraAnimation* tolua_ret = (MMD::CameraAnimation*)  new MMD::CameraAnimation();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MMD::CameraAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  MMD::CameraAnimation */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_CameraAnimation_new00_local
static int tolua_luafunc_MMD_CameraAnimation_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MMD::CameraAnimation* tolua_ret = (MMD::CameraAnimation*)  new MMD::CameraAnimation();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"MMD::CameraAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  MMD::CameraAnimation */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_CameraAnimation_delete00
static int tolua_luafunc_MMD_CameraAnimation_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MMD::CameraAnimation* self = (MMD::CameraAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: insert of class  MMD::CameraAnimation */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_CameraAnimation_insert00
static int tolua_luafunc_MMD_CameraAnimation_insert00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const MMD::CameraOneFrameData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MMD::CameraAnimation* self = (MMD::CameraAnimation*)  tolua_tousertype(tolua_S,1,0);
  const MMD::CameraOneFrameData* framedata = ((const MMD::CameraOneFrameData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insert'",NULL);
#endif
  {
   self->insert(*framedata);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reserve of class  MMD::CameraAnimation */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_CameraAnimation_reserve00
static int tolua_luafunc_MMD_CameraAnimation_reserve00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MMD::CameraAnimation* self = (MMD::CameraAnimation*)  tolua_tousertype(tolua_S,1,0);
  unsigned int size = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reserve'",NULL);
#endif
  {
   self->reserve(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reserve'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: shrink_to_fit of class  MMD::CameraAnimation */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_CameraAnimation_shrink_to_fit00
static int tolua_luafunc_MMD_CameraAnimation_shrink_to_fit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MMD::CameraAnimation* self = (MMD::CameraAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'shrink_to_fit'",NULL);
#endif
  {
   self->shrink_to_fit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shrink_to_fit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: load of class  MMD::CameraAnimation */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_CameraAnimation_load00
static int tolua_luafunc_MMD_CameraAnimation_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MMD::CameraAnimation* self = (MMD::CameraAnimation*)  tolua_tousertype(tolua_S,1,0);
  const std::string vmdFileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'load'",NULL);
#endif
  {
   self->load(vmdFileName);
   tolua_pushcppstring(tolua_S,(const char*)vmdFileName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOver of class  MMD::CameraAnimation */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_CameraAnimation_isOver00
static int tolua_luafunc_MMD_CameraAnimation_isOver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MMD::CameraAnimation* self = (const MMD::CameraAnimation*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOver'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOver(time);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  MMD::CameraAnimation */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_CameraAnimation_isReady00
static int tolua_luafunc_MMD_CameraAnimation_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MMD::CameraAnimation* self = (MMD::CameraAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: calc of class  MMD::CameraAnimation */
#ifndef TOLUA_DISABLE_tolua_luafunc_MMD_CameraAnimation_calc00
static int tolua_luafunc_MMD_CameraAnimation_calc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MMD::CameraAnimation* self = (MMD::CameraAnimation*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
  D3DXVECTOR3* pCameraPos = ((D3DXVECTOR3*)  tolua_tousertype(tolua_S,3,0));
  D3DXVECTOR3* pLookAt = ((D3DXVECTOR3*)  tolua_tousertype(tolua_S,4,0));
  D3DXVECTOR3* pUp = ((D3DXVECTOR3*)  tolua_tousertype(tolua_S,5,0));
  float pViewAngle = ((float)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'calc'",NULL);
#endif
  {
   self->calc(time,pCameraPos,pLookAt,pUp,&pViewAngle);
   tolua_pushnumber(tolua_S,(lua_Number)pViewAngle);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  std::shared_ptr<MMD::TemplateVMD> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__new00
static int tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<MMD::TemplateVMD>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<MMD::TemplateVMD>* tolua_ret = (std::shared_ptr<MMD::TemplateVMD>*)  new std::shared_ptr<MMD::TemplateVMD>();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::shared_ptr<MMD::TemplateVMD>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  std::shared_ptr<MMD::TemplateVMD> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__new00_local
static int tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<MMD::TemplateVMD>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<MMD::TemplateVMD>* tolua_ret = (std::shared_ptr<MMD::TemplateVMD>*)  new std::shared_ptr<MMD::TemplateVMD>();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"std::shared_ptr<MMD::TemplateVMD>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  std::shared_ptr<MMD::TemplateVMD> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__delete00
static int tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<MMD::TemplateVMD>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<MMD::TemplateVMD>* self = (std::shared_ptr<MMD::TemplateVMD>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  std::shared_ptr<MMD::TemplateVMD> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__reset00
static int tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<MMD::TemplateVMD>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<MMD::TemplateVMD>* self = (std::shared_ptr<MMD::TemplateVMD>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
  {
   self->reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  std::shared_ptr<MMD::TemplateVMD> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__get00
static int tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<MMD::TemplateVMD>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<MMD::TemplateVMD>* self = (const std::shared_ptr<MMD::TemplateVMD>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
  {
   MMD::TemplateVMD* tolua_ret = (MMD::TemplateVMD*)  self->get();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MMD::TemplateVMD");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX_new00
static int tolua_luafunc_D3DXMATRIX_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  new D3DXMATRIX();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXMATRIX");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX_new00_local
static int tolua_luafunc_D3DXMATRIX_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  new D3DXMATRIX();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"D3DXMATRIX");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX_new01
static int tolua_luafunc_D3DXMATRIX_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const float tolua_var_131 = ((const float)  tolua_tonumber(tolua_S,2,0));
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  new D3DXMATRIX(&tolua_var_131);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXMATRIX");
   tolua_pushnumber(tolua_S,(lua_Number)tolua_var_131);
  }
 }
 return 2;
tolua_lerror:
 return tolua_luafunc_D3DXMATRIX_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX_new01_local
static int tolua_luafunc_D3DXMATRIX_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const float tolua_var_131 = ((const float)  tolua_tonumber(tolua_S,2,0));
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  new D3DXMATRIX(&tolua_var_131);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"D3DXMATRIX");
   tolua_pushnumber(tolua_S,(lua_Number)tolua_var_131);
  }
 }
 return 2;
tolua_lerror:
 return tolua_luafunc_D3DXMATRIX_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX_new02
static int tolua_luafunc_D3DXMATRIX_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DMATRIX* tolua_var_132 = ((const D3DMATRIX*)  tolua_tousertype(tolua_S,2,0));
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  new D3DXMATRIX(*tolua_var_132);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXMATRIX");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXMATRIX_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX_new02_local
static int tolua_luafunc_D3DXMATRIX_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DMATRIX* tolua_var_132 = ((const D3DMATRIX*)  tolua_tousertype(tolua_S,2,0));
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  new D3DXMATRIX(*tolua_var_132);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"D3DXMATRIX");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXMATRIX_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX_new03
static int tolua_luafunc_D3DXMATRIX_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,14,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,15,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,16,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,17,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,18,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
   float _11 = ((  float)  tolua_tonumber(tolua_S,2,0));
   float _12 = ((  float)  tolua_tonumber(tolua_S,3,0));
   float _13 = ((  float)  tolua_tonumber(tolua_S,4,0));
   float _14 = ((  float)  tolua_tonumber(tolua_S,5,0));
   float _21 = ((  float)  tolua_tonumber(tolua_S,6,0));
   float _22 = ((  float)  tolua_tonumber(tolua_S,7,0));
   float _23 = ((  float)  tolua_tonumber(tolua_S,8,0));
   float _24 = ((  float)  tolua_tonumber(tolua_S,9,0));
   float _31 = ((  float)  tolua_tonumber(tolua_S,10,0));
   float _32 = ((  float)  tolua_tonumber(tolua_S,11,0));
   float _33 = ((  float)  tolua_tonumber(tolua_S,12,0));
   float _34 = ((  float)  tolua_tonumber(tolua_S,13,0));
   float _41 = ((  float)  tolua_tonumber(tolua_S,14,0));
   float _42 = ((  float)  tolua_tonumber(tolua_S,15,0));
   float _43 = ((  float)  tolua_tonumber(tolua_S,16,0));
   float _44 = ((  float)  tolua_tonumber(tolua_S,17,0));
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  new D3DXMATRIX(_11,_12,_13,_14,_21,_22,_23,_24,_31,_32,_33,_34,_41,_42,_43,_44);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXMATRIX");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXMATRIX_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX_new03_local
static int tolua_luafunc_D3DXMATRIX_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,14,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,15,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,16,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,17,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,18,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
   float _11 = ((  float)  tolua_tonumber(tolua_S,2,0));
   float _12 = ((  float)  tolua_tonumber(tolua_S,3,0));
   float _13 = ((  float)  tolua_tonumber(tolua_S,4,0));
   float _14 = ((  float)  tolua_tonumber(tolua_S,5,0));
   float _21 = ((  float)  tolua_tonumber(tolua_S,6,0));
   float _22 = ((  float)  tolua_tonumber(tolua_S,7,0));
   float _23 = ((  float)  tolua_tonumber(tolua_S,8,0));
   float _24 = ((  float)  tolua_tonumber(tolua_S,9,0));
   float _31 = ((  float)  tolua_tonumber(tolua_S,10,0));
   float _32 = ((  float)  tolua_tonumber(tolua_S,11,0));
   float _33 = ((  float)  tolua_tonumber(tolua_S,12,0));
   float _34 = ((  float)  tolua_tonumber(tolua_S,13,0));
   float _41 = ((  float)  tolua_tonumber(tolua_S,14,0));
   float _42 = ((  float)  tolua_tonumber(tolua_S,15,0));
   float _43 = ((  float)  tolua_tonumber(tolua_S,16,0));
   float _44 = ((  float)  tolua_tonumber(tolua_S,17,0));
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  new D3DXMATRIX(_11,_12,_13,_14,_21,_22,_23,_24,_31,_32,_33,_34,_41,_42,_43,_44);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"D3DXMATRIX");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXMATRIX_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operatorFLOAT* of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX__FLOAT_00
static int tolua_luafunc_D3DXMATRIX__FLOAT_00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  D3DXMATRIX* self = (D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operatorFLOAT*'",NULL);
#endif
  {
   void* tolua_ret = (void*)  static_cast< void*>(*self);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.FLOAT*'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operatorconst FLOAT* of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX__const_FLOAT_00
static int tolua_luafunc_D3DXMATRIX__const_FLOAT_00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXMATRIX* self = (const D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operatorconst FLOAT*'",NULL);
#endif
  {
   const void* tolua_ret = (const void*)  static_cast< const void*>(*self);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.const FLOAT*'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX__add00
static int tolua_luafunc_D3DXMATRIX__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXMATRIX* self = (const D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'",NULL);
#endif
  {
   D3DXMATRIX tolua_ret = (D3DXMATRIX)  self->operator+();
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXMATRIX(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXMATRIX));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX__sub00
static int tolua_luafunc_D3DXMATRIX__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXMATRIX* self = (const D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'",NULL);
#endif
  {
   D3DXMATRIX tolua_ret = (D3DXMATRIX)  self->operator-();
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXMATRIX(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXMATRIX));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX__mul00
static int tolua_luafunc_D3DXMATRIX__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXMATRIX* self = (const D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0);
  const D3DXMATRIX* tolua_var_133 = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'",NULL);
#endif
  {
   D3DXMATRIX tolua_ret = (D3DXMATRIX)  self->operator*(*tolua_var_133);
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXMATRIX(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXMATRIX));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX__add01
static int tolua_luafunc_D3DXMATRIX__add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DXMATRIX* self = (const D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0);
  const D3DXMATRIX* tolua_var_134 = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'",NULL);
#endif
  {
   D3DXMATRIX tolua_ret = (D3DXMATRIX)  self->operator+(*tolua_var_134);
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXMATRIX(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXMATRIX));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXMATRIX__add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX__sub01
static int tolua_luafunc_D3DXMATRIX__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DXMATRIX* self = (const D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0);
  const D3DXMATRIX* tolua_var_135 = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'",NULL);
#endif
  {
   D3DXMATRIX tolua_ret = (D3DXMATRIX)  self->operator-(*tolua_var_135);
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXMATRIX(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXMATRIX));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXMATRIX__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX__mul01
static int tolua_luafunc_D3DXMATRIX__mul01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DXMATRIX* self = (const D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0);
   float tolua_var_136 = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'",NULL);
#endif
  {
   D3DXMATRIX tolua_ret = (D3DXMATRIX)  self->operator*(tolua_var_136);
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXMATRIX(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXMATRIX));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXMATRIX__mul00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX__div00
static int tolua_luafunc_D3DXMATRIX__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXMATRIX* self = (const D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0);
   float tolua_var_137 = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'",NULL);
#endif
  {
   D3DXMATRIX tolua_ret = (D3DXMATRIX)  self->operator/(tolua_var_137);
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXMATRIX(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXMATRIX));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXMATRIX");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  D3DXMATRIX */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMATRIX__eq00
static int tolua_luafunc_D3DXMATRIX__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXMATRIX* self = (const D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0);
  const D3DXMATRIX* tolua_var_138 = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='",NULL);
#endif
  {
    bool tolua_ret = (  bool)  self->operator==(*tolua_var_138);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3_new00
static int tolua_luafunc_D3DXVECTOR3_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   D3DXVECTOR3* tolua_ret = (D3DXVECTOR3*)  new D3DXVECTOR3();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXVECTOR3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3_new00_local
static int tolua_luafunc_D3DXVECTOR3_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   D3DXVECTOR3* tolua_ret = (D3DXVECTOR3*)  new D3DXVECTOR3();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"D3DXVECTOR3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3_new01
static int tolua_luafunc_D3DXVECTOR3_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CONST  float tolua_var_139 = ((CONST  float)  tolua_tonumber(tolua_S,2,0));
  {
   D3DXVECTOR3* tolua_ret = (D3DXVECTOR3*)  new D3DXVECTOR3(&tolua_var_139);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXVECTOR3");
   tolua_pushnumber(tolua_S,(lua_Number)tolua_var_139);
  }
 }
 return 2;
tolua_lerror:
 return tolua_luafunc_D3DXVECTOR3_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3_new01_local
static int tolua_luafunc_D3DXVECTOR3_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CONST  float tolua_var_139 = ((CONST  float)  tolua_tonumber(tolua_S,2,0));
  {
   D3DXVECTOR3* tolua_ret = (D3DXVECTOR3*)  new D3DXVECTOR3(&tolua_var_139);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"D3DXVECTOR3");
   tolua_pushnumber(tolua_S,(lua_Number)tolua_var_139);
  }
 }
 return 2;
tolua_lerror:
 return tolua_luafunc_D3DXVECTOR3_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3_new02
static int tolua_luafunc_D3DXVECTOR3_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"D3DVECTOR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CONST D3DVECTOR* tolua_var_140 = ((CONST D3DVECTOR*)  tolua_tousertype(tolua_S,2,0));
  {
   D3DXVECTOR3* tolua_ret = (D3DXVECTOR3*)  new D3DXVECTOR3(*tolua_var_140);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXVECTOR3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXVECTOR3_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3_new02_local
static int tolua_luafunc_D3DXVECTOR3_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"D3DVECTOR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CONST D3DVECTOR* tolua_var_140 = ((CONST D3DVECTOR*)  tolua_tousertype(tolua_S,2,0));
  {
   D3DXVECTOR3* tolua_ret = (D3DXVECTOR3*)  new D3DXVECTOR3(*tolua_var_140);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"D3DXVECTOR3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXVECTOR3_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3_new03
static int tolua_luafunc_D3DXVECTOR3_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
   float x = ((  float)  tolua_tonumber(tolua_S,2,0));
   float y = ((  float)  tolua_tonumber(tolua_S,3,0));
   float z = ((  float)  tolua_tonumber(tolua_S,4,0));
  {
   D3DXVECTOR3* tolua_ret = (D3DXVECTOR3*)  new D3DXVECTOR3(x,y,z);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXVECTOR3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXVECTOR3_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3_new03_local
static int tolua_luafunc_D3DXVECTOR3_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
   float x = ((  float)  tolua_tonumber(tolua_S,2,0));
   float y = ((  float)  tolua_tonumber(tolua_S,3,0));
   float z = ((  float)  tolua_tonumber(tolua_S,4,0));
  {
   D3DXVECTOR3* tolua_ret = (D3DXVECTOR3*)  new D3DXVECTOR3(x,y,z);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"D3DXVECTOR3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXVECTOR3_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operatorFLOAT* of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3__FLOAT_00
static int tolua_luafunc_D3DXVECTOR3__FLOAT_00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  D3DXVECTOR3* self = (D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operatorFLOAT*'",NULL);
#endif
  {
   void* tolua_ret = (void*)  static_cast< void*>(*self);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.FLOAT*'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operatorCONST FLOAT* of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3__CONST_FLOAT_00
static int tolua_luafunc_D3DXVECTOR3__CONST_FLOAT_00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXVECTOR3* self = (const D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operatorCONST FLOAT*'",NULL);
#endif
  {
   CONST void* tolua_ret = (CONST void*)  static_cast< CONST void*>(*self);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.CONST FLOAT*'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3__add00
static int tolua_luafunc_D3DXVECTOR3__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXVECTOR3* self = (const D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'",NULL);
#endif
  {
   D3DXVECTOR3 tolua_ret = (D3DXVECTOR3)  self->operator+();
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXVECTOR3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXVECTOR3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3__sub00
static int tolua_luafunc_D3DXVECTOR3__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXVECTOR3* self = (const D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'",NULL);
#endif
  {
   D3DXVECTOR3 tolua_ret = (D3DXVECTOR3)  self->operator-();
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXVECTOR3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXVECTOR3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3__add01
static int tolua_luafunc_D3DXVECTOR3__add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DXVECTOR3* self = (const D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
  CONST D3DXVECTOR3* tolua_var_141 = ((CONST D3DXVECTOR3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'",NULL);
#endif
  {
   D3DXVECTOR3 tolua_ret = (D3DXVECTOR3)  self->operator+(*tolua_var_141);
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXVECTOR3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXVECTOR3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXVECTOR3__add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3__sub01
static int tolua_luafunc_D3DXVECTOR3__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DXVECTOR3* self = (const D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
  CONST D3DXVECTOR3* tolua_var_142 = ((CONST D3DXVECTOR3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'",NULL);
#endif
  {
   D3DXVECTOR3 tolua_ret = (D3DXVECTOR3)  self->operator-(*tolua_var_142);
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXVECTOR3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXVECTOR3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_D3DXVECTOR3__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3__mul00
static int tolua_luafunc_D3DXVECTOR3__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXVECTOR3* self = (const D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
   float tolua_var_143 = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'",NULL);
#endif
  {
   D3DXVECTOR3 tolua_ret = (D3DXVECTOR3)  self->operator*(tolua_var_143);
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXVECTOR3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXVECTOR3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3__div00
static int tolua_luafunc_D3DXVECTOR3__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXVECTOR3* self = (const D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
   float tolua_var_144 = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'",NULL);
#endif
  {
   D3DXVECTOR3 tolua_ret = (D3DXVECTOR3)  self->operator/(tolua_var_144);
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DXVECTOR3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DXVECTOR3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DXVECTOR3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXVECTOR3__eq00
static int tolua_luafunc_D3DXVECTOR3__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXVECTOR3* self = (const D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
  CONST D3DXVECTOR3* tolua_var_145 = ((CONST D3DXVECTOR3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='",NULL);
#endif
  {
    bool tolua_ret = (  bool)  self->operator==(*tolua_var_145);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_get_D3DXVECTOR3_x
static int tolua_get_D3DXVECTOR3_x(lua_State* tolua_S)
{
  D3DXVECTOR3* self = (D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_set_D3DXVECTOR3_x
static int tolua_set_D3DXVECTOR3_x(lua_State* tolua_S)
{
  D3DXVECTOR3* self = (D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_get_D3DXVECTOR3_y
static int tolua_get_D3DXVECTOR3_y(lua_State* tolua_S)
{
  D3DXVECTOR3* self = (D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_set_D3DXVECTOR3_y
static int tolua_set_D3DXVECTOR3_y(lua_State* tolua_S)
{
  D3DXVECTOR3* self = (D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: z of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_get_D3DXVECTOR3_z
static int tolua_get_D3DXVECTOR3_z(lua_State* tolua_S)
{
  D3DXVECTOR3* self = (D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->z);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: z of class  D3DXVECTOR3 */
#ifndef TOLUA_DISABLE_tolua_set_D3DXVECTOR3_z
static int tolua_set_D3DXVECTOR3_z(lua_State* tolua_S)
{
  D3DXVECTOR3* self = (D3DXVECTOR3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->z = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  std::shared_ptr<MMD::CameraAnimation> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__new00
static int tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<MMD::CameraAnimation>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<MMD::CameraAnimation>* tolua_ret = (std::shared_ptr<MMD::CameraAnimation>*)  new std::shared_ptr<MMD::CameraAnimation>();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::shared_ptr<MMD::CameraAnimation>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  std::shared_ptr<MMD::CameraAnimation> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__new00_local
static int tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<MMD::CameraAnimation>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<MMD::CameraAnimation>* tolua_ret = (std::shared_ptr<MMD::CameraAnimation>*)  new std::shared_ptr<MMD::CameraAnimation>();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"std::shared_ptr<MMD::CameraAnimation>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  std::shared_ptr<MMD::CameraAnimation> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__delete00
static int tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<MMD::CameraAnimation>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<MMD::CameraAnimation>* self = (std::shared_ptr<MMD::CameraAnimation>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  std::shared_ptr<MMD::CameraAnimation> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__reset00
static int tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<MMD::CameraAnimation>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MMD::CameraAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<MMD::CameraAnimation>* self = (std::shared_ptr<MMD::CameraAnimation>*)  tolua_tousertype(tolua_S,1,0);
  MMD::CameraAnimation* tolua_var_4 = ((MMD::CameraAnimation*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
  {
   self->reset(tolua_var_4);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  std::shared_ptr<MMD::CameraAnimation> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__get00
static int tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<MMD::CameraAnimation>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<MMD::CameraAnimation>* self = (const std::shared_ptr<MMD::CameraAnimation>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
  {
   MMD::CameraAnimation* tolua_ret = (MMD::CameraAnimation*)  self->get();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MMD::CameraAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_create00
static int tolua_luafunc_GameLib_Graphics_Texture_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::PseudoXml::ConstElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::PseudoXml::ConstElement tolua_var_29 = *((GameLib::PseudoXml::ConstElement*)  tolua_tousertype(tolua_S,2,0));
  const char* path = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   GameLib::Graphics::Texture tolua_ret = (GameLib::Graphics::Texture)  GameLib::Graphics::Texture::create(tolua_var_29,path);
   {
#ifdef __cplusplus
    void* tolua_obj = new GameLib::Graphics::Texture(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Graphics::Texture");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GameLib::Graphics::Texture));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Graphics::Texture");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_create01
static int tolua_luafunc_GameLib_Graphics_Texture_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
  int height = ((int)  tolua_tonumber(tolua_S,3,0));
  bool createMipChain = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   GameLib::Graphics::Texture tolua_ret = (GameLib::Graphics::Texture)  GameLib::Graphics::Texture::create(width,height,createMipChain);
   {
#ifdef __cplusplus
    void* tolua_obj = new GameLib::Graphics::Texture(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Graphics::Texture");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GameLib::Graphics::Texture));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Graphics::Texture");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Graphics_Texture_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_create02
static int tolua_luafunc_GameLib_Graphics_Texture_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   GameLib::Graphics::Texture tolua_ret = (GameLib::Graphics::Texture)  GameLib::Graphics::Texture::create(filename);
   {
#ifdef __cplusplus
    void* tolua_obj = new GameLib::Graphics::Texture(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Graphics::Texture");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GameLib::Graphics::Texture));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Graphics::Texture");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Graphics_Texture_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_create03
static int tolua_luafunc_GameLib_Graphics_Texture_create03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* fileData = ((const char*)  tolua_tostring(tolua_S,2,0));
  int fileSize = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   GameLib::Graphics::Texture tolua_ret = (GameLib::Graphics::Texture)  GameLib::Graphics::Texture::create(fileData,fileSize);
   {
#ifdef __cplusplus
    void* tolua_obj = new GameLib::Graphics::Texture(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Graphics::Texture");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GameLib::Graphics::Texture));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Graphics::Texture");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Graphics_Texture_create02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: name of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_name00
static int tolua_luafunc_GameLib_Graphics_Texture_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Texture* self = (const GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'name'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->name();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_isReady00
static int tolua_luafunc_GameLib_Graphics_Texture_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Texture* self = (GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isError of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_isError00
static int tolua_luafunc_GameLib_Graphics_Texture_isError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Texture* self = (const GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isError'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isError();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: width of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_width00
static int tolua_luafunc_GameLib_Graphics_Texture_width00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Texture* self = (const GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'width'",NULL);
#endif
  {
   int tolua_ret = (int)  self->width();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'width'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: height of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_height00
static int tolua_luafunc_GameLib_Graphics_Texture_height00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Texture* self = (const GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'height'",NULL);
#endif
  {
   int tolua_ret = (int)  self->height();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'height'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: originalWidth of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_originalWidth00
static int tolua_luafunc_GameLib_Graphics_Texture_originalWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Texture* self = (const GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'originalWidth'",NULL);
#endif
  {
   int tolua_ret = (int)  self->originalWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'originalWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: originalHeight of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_originalHeight00
static int tolua_luafunc_GameLib_Graphics_Texture_originalHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Texture* self = (const GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'originalHeight'",NULL);
#endif
  {
   int tolua_ret = (int)  self->originalHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'originalHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mipmapNumber of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_mipmapNumber00
static int tolua_luafunc_GameLib_Graphics_Texture_mipmapNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Texture* self = (const GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mipmapNumber'",NULL);
#endif
  {
   int tolua_ret = (int)  self->mipmapNumber();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mipmapNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: write of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_write00
static int tolua_luafunc_GameLib_Graphics_Texture_write00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Texture* self = (GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'write'",NULL);
#endif
  {
   self->write(filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'write'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dxTeture of class  GameLib::Graphics::Texture */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Texture_dxTeture00
static int tolua_luafunc_GameLib_Graphics_Texture_dxTeture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Texture* self = (GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dxTeture'",NULL);
#endif
  {
   IDirect3DTexture9* tolua_ret = (IDirect3DTexture9*)  self->dxTeture();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"IDirect3DTexture9");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dxTeture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_new00
static int tolua_luafunc_GameLib_Math_Vector3_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Math::Vector3* tolua_ret = (GameLib::Math::Vector3*)  new GameLib::Math::Vector3();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_new00_local
static int tolua_luafunc_GameLib_Math_Vector3_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Math::Vector3* tolua_ret = (GameLib::Math::Vector3*)  new GameLib::Math::Vector3();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_new01
static int tolua_luafunc_GameLib_Math_Vector3_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float tolua_var_48 = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   GameLib::Math::Vector3* tolua_ret = (GameLib::Math::Vector3*)  new GameLib::Math::Vector3(tolua_var_48);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_new01_local
static int tolua_luafunc_GameLib_Math_Vector3_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float tolua_var_48 = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   GameLib::Math::Vector3* tolua_ret = (GameLib::Math::Vector3*)  new GameLib::Math::Vector3(tolua_var_48);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_new02
static int tolua_luafunc_GameLib_Math_Vector3_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float tolua_var_49 = ((float)  tolua_tonumber(tolua_S,2,0));
  float tolua_var_50 = ((float)  tolua_tonumber(tolua_S,3,0));
  float tolua_var_51 = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   GameLib::Math::Vector3* tolua_ret = (GameLib::Math::Vector3*)  new GameLib::Math::Vector3(tolua_var_49,tolua_var_50,tolua_var_51);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_new02_local
static int tolua_luafunc_GameLib_Math_Vector3_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float tolua_var_49 = ((float)  tolua_tonumber(tolua_S,2,0));
  float tolua_var_50 = ((float)  tolua_tonumber(tolua_S,3,0));
  float tolua_var_51 = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   GameLib::Math::Vector3* tolua_ret = (GameLib::Math::Vector3*)  new GameLib::Math::Vector3(tolua_var_49,tolua_var_50,tolua_var_51);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_new03
static int tolua_luafunc_GameLib_Math_Vector3_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const GameLib::Math::Vector3* tolua_var_52 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector3* tolua_ret = (GameLib::Math::Vector3*)  new GameLib::Math::Vector3(*tolua_var_52);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_new03_local
static int tolua_luafunc_GameLib_Math_Vector3_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const GameLib::Math::Vector3* tolua_var_52 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector3* tolua_ret = (GameLib::Math::Vector3*)  new GameLib::Math::Vector3(*tolua_var_52);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_new04
static int tolua_luafunc_GameLib_Math_Vector3_new04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const GameLib::Math::Vector4* tolua_var_53 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector3* tolua_ret = (GameLib::Math::Vector3*)  new GameLib::Math::Vector3(*tolua_var_53);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_new03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_new04_local
static int tolua_luafunc_GameLib_Math_Vector3_new04_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const GameLib::Math::Vector4* tolua_var_53 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector3* tolua_ret = (GameLib::Math::Vector3*)  new GameLib::Math::Vector3(*tolua_var_53);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_new03_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: set of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_set00
static int tolua_luafunc_GameLib_Math_Vector3_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_54 = ((float)  tolua_tonumber(tolua_S,2,0));
  float tolua_var_55 = ((float)  tolua_tonumber(tolua_S,3,0));
  float tolua_var_56 = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'",NULL);
#endif
  {
   self->set(tolua_var_54,tolua_var_55,tolua_var_56);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3__seti00
static int tolua_luafunc_GameLib_Math_Vector3__seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_58 = ((int)  tolua_tonumber(tolua_S,2,0));
  float tolua_value = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'",NULL);
#endif
  self->operator[](tolua_var_58) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3__geti00
static int tolua_luafunc_GameLib_Math_Vector3__geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_57 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'",NULL);
#endif
  {
   float tolua_ret = (float)  self->operator[](tolua_var_57);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3__geti01
static int tolua_luafunc_GameLib_Math_Vector3__geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const GameLib::Math::Vector3* self = (const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_59 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'",NULL);
#endif
  {
   float tolua_ret = (float)  self->operator[](tolua_var_59);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3__geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAdd of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_setAdd00
static int tolua_luafunc_GameLib_Math_Vector3_setAdd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_60 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* tolua_var_61 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAdd'",NULL);
#endif
  {
   self->setAdd(*tolua_var_60,*tolua_var_61);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAdd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAdd of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_setAdd01
static int tolua_luafunc_GameLib_Math_Vector3_setAdd01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_62 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  float tolua_var_63 = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAdd'",NULL);
#endif
  {
   self->setAdd(*tolua_var_62,tolua_var_63);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_setAdd00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSub of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_setSub00
static int tolua_luafunc_GameLib_Math_Vector3_setSub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_64 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* tolua_var_65 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSub'",NULL);
#endif
  {
   self->setSub(*tolua_var_64,*tolua_var_65);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSub of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_setSub01
static int tolua_luafunc_GameLib_Math_Vector3_setSub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_66 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  float tolua_var_67 = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSub'",NULL);
#endif
  {
   self->setSub(*tolua_var_66,tolua_var_67);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_setSub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMul of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_setMul00
static int tolua_luafunc_GameLib_Math_Vector3_setMul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_68 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* tolua_var_69 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMul'",NULL);
#endif
  {
   self->setMul(*tolua_var_68,*tolua_var_69);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMul of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_setMul01
static int tolua_luafunc_GameLib_Math_Vector3_setMul01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_70 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  float tolua_var_71 = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMul'",NULL);
#endif
  {
   self->setMul(*tolua_var_70,tolua_var_71);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_setMul00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNeg of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_setNeg00
static int tolua_luafunc_GameLib_Math_Vector3_setNeg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_72 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNeg'",NULL);
#endif
  {
   self->setNeg(*tolua_var_72);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNeg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMadd of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_setMadd00
static int tolua_luafunc_GameLib_Math_Vector3_setMadd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* a = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* b = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
  float c = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMadd'",NULL);
#endif
  {
   self->setMadd(*a,*b,c);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMadd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMsub of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_setMsub00
static int tolua_luafunc_GameLib_Math_Vector3_setMsub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* a = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* b = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
  float c = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMsub'",NULL);
#endif
  {
   self->setMsub(*a,*b,c);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMsub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: madd of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_madd00
static int tolua_luafunc_GameLib_Math_Vector3_madd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* a = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  float b = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'madd'",NULL);
#endif
  {
   self->madd(*a,b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'madd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: msub of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_msub00
static int tolua_luafunc_GameLib_Math_Vector3_msub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* a = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  float b = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'msub'",NULL);
#endif
  {
   self->msub(*a,b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'msub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dot of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_dot00
static int tolua_luafunc_GameLib_Math_Vector3_dot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Math::Vector3* self = (const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_73 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dot'",NULL);
#endif
  {
   float tolua_ret = (float)  self->dot(*tolua_var_73);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCross of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_setCross00
static int tolua_luafunc_GameLib_Math_Vector3_setCross00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* a = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* b = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCross'",NULL);
#endif
  {
   self->setCross(*a,*b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCross'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: normalize of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_normalize00
static int tolua_luafunc_GameLib_Math_Vector3_normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'normalize'",NULL);
#endif
  {
   self->normalize();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: length of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_length00
static int tolua_luafunc_GameLib_Math_Vector3_length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Math::Vector3* self = (const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'length'",NULL);
#endif
  {
   float tolua_ret = (float)  self->length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: squareLength of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_squareLength00
static int tolua_luafunc_GameLib_Math_Vector3_squareLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Math::Vector3* self = (const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'squareLength'",NULL);
#endif
  {
   float tolua_ret = (float)  self->squareLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'squareLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: min of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_min00
static int tolua_luafunc_GameLib_Math_Vector3_min00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_74 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'min'",NULL);
#endif
  {
   self->min(*tolua_var_74);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'min'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: max of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_max00
static int tolua_luafunc_GameLib_Math_Vector3_max00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_75 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'max'",NULL);
#endif
  {
   self->max(*tolua_var_75);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'max'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: min of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_min01
static int tolua_luafunc_GameLib_Math_Vector3_min01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_76 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* tolua_var_77 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'min'",NULL);
#endif
  {
   self->min(*tolua_var_76,*tolua_var_77);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_min00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: max of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector3_max01
static int tolua_luafunc_GameLib_Math_Vector3_max01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_78 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* tolua_var_79 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'max'",NULL);
#endif
  {
   self->max(*tolua_var_78,*tolua_var_79);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector3_max00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Vector3_x
static int tolua_get_GameLib__Math__Vector3_x(lua_State* tolua_S)
{
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Vector3_x
static int tolua_set_GameLib__Math__Vector3_x(lua_State* tolua_S)
{
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Vector3_y
static int tolua_get_GameLib__Math__Vector3_y(lua_State* tolua_S)
{
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Vector3_y
static int tolua_set_GameLib__Math__Vector3_y(lua_State* tolua_S)
{
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: z of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Vector3_z
static int tolua_get_GameLib__Math__Vector3_z(lua_State* tolua_S)
{
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->z);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: z of class  GameLib::Math::Vector3 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Vector3_z
static int tolua_set_GameLib__Math__Vector3_z(lua_State* tolua_S)
{
  GameLib::Math::Vector3* self = (GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->z = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix44_new00
static int tolua_luafunc_GameLib_Math_Matrix44_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Math::Matrix44* tolua_ret = (GameLib::Math::Matrix44*)  new GameLib::Math::Matrix44();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Matrix44");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix44_new00_local
static int tolua_luafunc_GameLib_Math_Matrix44_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Math::Matrix44* tolua_ret = (GameLib::Math::Matrix44*)  new GameLib::Math::Matrix44();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Matrix44");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIdentity of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix44_setIdentity00
static int tolua_luafunc_GameLib_Math_Matrix44_setIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIdentity'",NULL);
#endif
  {
   self->setIdentity();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPerspectiveTransform of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix44_setPerspectiveTransform00
static int tolua_luafunc_GameLib_Math_Matrix44_setPerspectiveTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
  float fieldOfViewYInRadian = ((float)  tolua_tonumber(tolua_S,2,0));
  float windowWidth = ((float)  tolua_tonumber(tolua_S,3,0));
  float windowHeight = ((float)  tolua_tonumber(tolua_S,4,0));
  float nearClip = ((float)  tolua_tonumber(tolua_S,5,0));
  float farClip = ((float)  tolua_tonumber(tolua_S,6,0));
  bool zBufferIsLinear = ((bool)  tolua_toboolean(tolua_S,7,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPerspectiveTransform'",NULL);
#endif
  {
   self->setPerspectiveTransform(fieldOfViewYInRadian,windowWidth,windowHeight,nearClip,farClip,zBufferIsLinear);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPerspectiveTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOrthogonalTransform of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix44_setOrthogonalTransform00
static int tolua_luafunc_GameLib_Math_Matrix44_setOrthogonalTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
  float left = ((float)  tolua_tonumber(tolua_S,2,0));
  float right = ((float)  tolua_tonumber(tolua_S,3,0));
  float bottom = ((float)  tolua_tonumber(tolua_S,4,0));
  float top = ((float)  tolua_tonumber(tolua_S,5,0));
  float front = ((float)  tolua_tonumber(tolua_S,6,0));
  float back = ((float)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOrthogonalTransform'",NULL);
#endif
  {
   self->setOrthogonalTransform(left,right,bottom,top,front,back);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOrthogonalTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: multiplyViewTransform of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix44_multiplyViewTransform00
static int tolua_luafunc_GameLib_Math_Matrix44_multiplyViewTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* eyePosition = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* eyeTarget = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
  const GameLib::Math::Vector3* upVector = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'multiplyViewTransform'",NULL);
#endif
  {
   self->multiplyViewTransform(*eyePosition,*eyeTarget,*upVector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'multiplyViewTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mul of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix44_mul00
static int tolua_luafunc_GameLib_Math_Matrix44_mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Math::Matrix44* self = (const GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Math::Vector4* out = ((GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* in = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mul'",NULL);
#endif
  {
   self->mul(out,*in);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMul of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix44_setMul00
static int tolua_luafunc_GameLib_Math_Matrix44_setMul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Matrix44* tolua_var_80 = ((const GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Matrix34* tolua_var_81 = ((const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMul'",NULL);
#endif
  {
   self->setMul(*tolua_var_80,*tolua_var_81);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix44__eq00
static int tolua_luafunc_GameLib_Math_Matrix44__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Math::Matrix44* self = (const GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Matrix44* tolua_var_82 = ((const GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*tolua_var_82);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m00 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m00
static int tolua_get_GameLib__Math__Matrix44_m00(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm00'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m00);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m00 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m00
static int tolua_set_GameLib__Math__Matrix44_m00(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm00'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m00 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m01 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m01
static int tolua_get_GameLib__Math__Matrix44_m01(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm01'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m01);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m01 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m01
static int tolua_set_GameLib__Math__Matrix44_m01(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm01'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m01 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m02 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m02
static int tolua_get_GameLib__Math__Matrix44_m02(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm02'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m02);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m02 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m02
static int tolua_set_GameLib__Math__Matrix44_m02(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm02'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m02 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m03 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m03
static int tolua_get_GameLib__Math__Matrix44_m03(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm03'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m03);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m03 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m03
static int tolua_set_GameLib__Math__Matrix44_m03(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm03'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m03 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m10 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m10
static int tolua_get_GameLib__Math__Matrix44_m10(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm10'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m10);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m10 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m10
static int tolua_set_GameLib__Math__Matrix44_m10(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm10'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m10 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m11 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m11
static int tolua_get_GameLib__Math__Matrix44_m11(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm11'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m11);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m11 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m11
static int tolua_set_GameLib__Math__Matrix44_m11(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm11'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m11 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m12 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m12
static int tolua_get_GameLib__Math__Matrix44_m12(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm12'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m12);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m12 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m12
static int tolua_set_GameLib__Math__Matrix44_m12(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm12'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m12 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m13 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m13
static int tolua_get_GameLib__Math__Matrix44_m13(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm13'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m13);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m13 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m13
static int tolua_set_GameLib__Math__Matrix44_m13(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm13'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m13 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m20 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m20
static int tolua_get_GameLib__Math__Matrix44_m20(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm20'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m20);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m20 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m20
static int tolua_set_GameLib__Math__Matrix44_m20(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm20'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m20 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m21 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m21
static int tolua_get_GameLib__Math__Matrix44_m21(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm21'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m21);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m21 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m21
static int tolua_set_GameLib__Math__Matrix44_m21(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm21'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m21 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m22 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m22
static int tolua_get_GameLib__Math__Matrix44_m22(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm22'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m22);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m22 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m22
static int tolua_set_GameLib__Math__Matrix44_m22(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm22'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m22 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m23 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m23
static int tolua_get_GameLib__Math__Matrix44_m23(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm23'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m23);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m23 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m23
static int tolua_set_GameLib__Math__Matrix44_m23(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm23'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m23 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m30 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m30
static int tolua_get_GameLib__Math__Matrix44_m30(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm30'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m30);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m30 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m30
static int tolua_set_GameLib__Math__Matrix44_m30(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm30'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m30 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m31 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m31
static int tolua_get_GameLib__Math__Matrix44_m31(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm31'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m31);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m31 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m31
static int tolua_set_GameLib__Math__Matrix44_m31(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm31'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m31 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m32 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m32
static int tolua_get_GameLib__Math__Matrix44_m32(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm32'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m32);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m32 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m32
static int tolua_set_GameLib__Math__Matrix44_m32(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm32'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m32 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m33 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix44_m33
static int tolua_get_GameLib__Math__Matrix44_m33(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm33'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m33);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m33 of class  GameLib::Math::Matrix44 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix44_m33
static int tolua_set_GameLib__Math__Matrix44_m33(lua_State* tolua_S)
{
  GameLib::Math::Matrix44* self = (GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm33'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m33 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_new00
static int tolua_luafunc_GameLib_Framework_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Framework* tolua_ret = (GameLib::Framework*)  new GameLib::Framework();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Framework");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_new00_local
static int tolua_luafunc_GameLib_Framework_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Framework* tolua_ret = (GameLib::Framework*)  new GameLib::Framework();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Framework");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_instance00
static int tolua_luafunc_GameLib_Framework_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Framework tolua_ret = (GameLib::Framework)  GameLib::Framework::instance();
   {
#ifdef __cplusplus
    void* tolua_obj = new GameLib::Framework(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Framework");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GameLib::Framework));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Framework");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: configure of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_configure00
static int tolua_luafunc_GameLib_Framework_configure00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Framework",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Framework::Configuration",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Framework* self = (GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Framework::Configuration* tolua_var_5 = ((GameLib::Framework::Configuration*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'configure'",NULL);
#endif
  {
   self->configure(tolua_var_5);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'configure'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_update00
static int tolua_luafunc_GameLib_Framework_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Framework* self = (GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
  {
   self->update();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enableFullScreen of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_enableFullScreen00
static int tolua_luafunc_GameLib_Framework_enableFullScreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Framework",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Framework* self = (GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
  bool tolua_var_6 = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableFullScreen'",NULL);
#endif
  {
   self->enableFullScreen(tolua_var_6);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableFullScreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: width of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_width00
static int tolua_luafunc_GameLib_Framework_width00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'width'",NULL);
#endif
  {
   int tolua_ret = (int)  self->width();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'width'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: height of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_height00
static int tolua_luafunc_GameLib_Framework_height00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'height'",NULL);
#endif
  {
   int tolua_ret = (int)  self->height();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'height'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: title of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_title00
static int tolua_luafunc_GameLib_Framework_title00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'title'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->title();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'title'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFullScreen of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_isFullScreen00
static int tolua_luafunc_GameLib_Framework_isFullScreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFullScreen'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFullScreen();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFullScreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFullScreenForbidden of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_isFullScreenForbidden00
static int tolua_luafunc_GameLib_Framework_isFullScreenForbidden00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFullScreenForbidden'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFullScreenForbidden();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFullScreenForbidden'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDragAndDropEnabled of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_isDragAndDropEnabled00
static int tolua_luafunc_GameLib_Framework_isDragAndDropEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDragAndDropEnabled'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isDragAndDropEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDragAndDropEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: requestEnd of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_requestEnd00
static int tolua_luafunc_GameLib_Framework_requestEnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Framework* self = (GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'requestEnd'",NULL);
#endif
  {
   self->requestEnd();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'requestEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEndRequested of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_isEndRequested00
static int tolua_luafunc_GameLib_Framework_isEndRequested00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEndRequested'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEndRequested();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEndRequested'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: time of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_time00
static int tolua_luafunc_GameLib_Framework_time00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'time'",NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->time();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'time'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: frameRate of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_frameRate00
static int tolua_luafunc_GameLib_Framework_frameRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'frameRate'",NULL);
#endif
  {
   int tolua_ret = (int)  self->frameRate();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'frameRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFrameRate of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_setFrameRate00
static int tolua_luafunc_GameLib_Framework_setFrameRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Framework",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Framework* self = (GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_7 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFrameRate'",NULL);
#endif
  {
   self->setFrameRate(tolua_var_7);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFrameRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: previousFrameInterval of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_previousFrameInterval00
static int tolua_luafunc_GameLib_Framework_previousFrameInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'previousFrameInterval'",NULL);
#endif
  {
   int tolua_ret = (int)  self->previousFrameInterval();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'previousFrameInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isClipCursorEnabled of class  GameLib::Framework */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Framework_isClipCursorEnabled00
static int tolua_luafunc_GameLib_Framework_isClipCursorEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Framework",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Framework* self = (const GameLib::Framework*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isClipCursorEnabled'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isClipCursorEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isClipCursorEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_new00
static int tolua_luafunc_GameLib_Graphics_Manager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Graphics::Manager* tolua_ret = (GameLib::Graphics::Manager*)  new GameLib::Graphics::Manager();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Graphics::Manager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_new00_local
static int tolua_luafunc_GameLib_Graphics_Manager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Graphics::Manager* tolua_ret = (GameLib::Graphics::Manager*)  new GameLib::Graphics::Manager();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Graphics::Manager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_instance00
static int tolua_luafunc_GameLib_Graphics_Manager_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Graphics::Manager tolua_ret = (GameLib::Graphics::Manager)  GameLib::Graphics::Manager::instance();
   {
#ifdef __cplusplus
    void* tolua_obj = new GameLib::Graphics::Manager(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Graphics::Manager");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GameLib::Graphics::Manager));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Graphics::Manager");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVertexBuffer of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setVertexBuffer00
static int tolua_luafunc_GameLib_Graphics_Manager_setVertexBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::VertexBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::VertexBuffer tolua_var_8 = *((GameLib::Graphics::VertexBuffer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVertexBuffer'",NULL);
#endif
  {
   self->setVertexBuffer(tolua_var_8);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVertexBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIndexBuffer of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setIndexBuffer00
static int tolua_luafunc_GameLib_Graphics_Manager_setIndexBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::IndexBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::IndexBuffer tolua_var_9 = *((GameLib::Graphics::IndexBuffer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIndexBuffer'",NULL);
#endif
  {
   self->setIndexBuffer(tolua_var_9);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIndexBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimatedVertexBoneBuffer of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setAnimatedVertexBoneBuffer00
static int tolua_luafunc_GameLib_Graphics_Manager_setAnimatedVertexBoneBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::AnimatedVertexBoneBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::AnimatedVertexBoneBuffer tolua_var_10 = *((GameLib::Graphics::AnimatedVertexBoneBuffer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimatedVertexBoneBuffer'",NULL);
#endif
  {
   self->setAnimatedVertexBoneBuffer(tolua_var_10);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimatedVertexBoneBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTexture of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setTexture00
static int tolua_luafunc_GameLib_Graphics_Manager_setTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::Texture tolua_var_11 = *((GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTexture'",NULL);
#endif
  {
   self->setTexture(tolua_var_11);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enableDepthTest of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_enableDepthTest00
static int tolua_luafunc_GameLib_Graphics_Manager_enableDepthTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  bool tolua_var_12 = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableDepthTest'",NULL);
#endif
  {
   self->enableDepthTest(tolua_var_12);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableDepthTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enableDepthWrite of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_enableDepthWrite00
static int tolua_luafunc_GameLib_Graphics_Manager_enableDepthWrite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  bool tolua_var_13 = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableDepthWrite'",NULL);
#endif
  {
   self->enableDepthWrite(tolua_var_13);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableDepthWrite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendMode of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setBlendMode00
static int tolua_luafunc_GameLib_Graphics_Manager_setBlendMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::BlendMode tolua_var_14 = ((GameLib::Graphics::BlendMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendMode'",NULL);
#endif
  {
   self->setBlendMode(tolua_var_14);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCullMode of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setCullMode00
static int tolua_luafunc_GameLib_Graphics_Manager_setCullMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::CullMode tolua_var_15 = ((GameLib::Graphics::CullMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCullMode'",NULL);
#endif
  {
   self->setCullMode(tolua_var_15);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCullMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextureFilter of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setTextureFilter00
static int tolua_luafunc_GameLib_Graphics_Manager_setTextureFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::TextureFilter tolua_var_16 = ((GameLib::Graphics::TextureFilter) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextureFilter'",NULL);
#endif
  {
   self->setTextureFilter(tolua_var_16);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextureFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setProjectionViewMatrix of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setProjectionViewMatrix00
static int tolua_luafunc_GameLib_Graphics_Manager_setProjectionViewMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Matrix44",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Matrix44* m = ((const GameLib::Math::Matrix44*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setProjectionViewMatrix'",NULL);
#endif
  {
   self->setProjectionViewMatrix(*m);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setProjectionViewMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWorldMatrix of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setWorldMatrix00
static int tolua_luafunc_GameLib_Graphics_Manager_setWorldMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Matrix34* m = ((const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWorldMatrix'",NULL);
#endif
  {
   self->setWorldMatrix(*m);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWorldMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getProjectionViewMatrix of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_getProjectionViewMatrix00
static int tolua_luafunc_GameLib_Graphics_Manager_getProjectionViewMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Manager* self = (const GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getProjectionViewMatrix'",NULL);
#endif
  {
   const GameLib::Math::Matrix44& tolua_ret = (const GameLib::Math::Matrix44&)  self->getProjectionViewMatrix();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const GameLib::Math::Matrix44");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getProjectionViewMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldMatrix of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_getWorldMatrix00
static int tolua_luafunc_GameLib_Graphics_Manager_getWorldMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Manager* self = (const GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldMatrix'",NULL);
#endif
  {
   const GameLib::Math::Matrix34& tolua_ret = (const GameLib::Math::Matrix34&)  self->getWorldMatrix();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const GameLib::Math::Matrix34");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWorldMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewport of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setViewport00
static int tolua_luafunc_GameLib_Graphics_Manager_setViewport00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int width = ((int)  tolua_tonumber(tolua_S,4,0));
  int height = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewport'",NULL);
#endif
  {
   self->setViewport(x,y,width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewport'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getViewport of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_getViewport00
static int tolua_luafunc_GameLib_Graphics_Manager_getViewport00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  int xOut = ((int)  tolua_tonumber(tolua_S,2,0));
  int yOut = ((int)  tolua_tonumber(tolua_S,3,0));
  int widthOut = ((int)  tolua_tonumber(tolua_S,4,0));
  int heightOut = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getViewport'",NULL);
#endif
  {
   self->getViewport(&xOut,&yOut,&widthOut,&heightOut);
   tolua_pushnumber(tolua_S,(lua_Number)xOut);
   tolua_pushnumber(tolua_S,(lua_Number)yOut);
   tolua_pushnumber(tolua_S,(lua_Number)widthOut);
   tolua_pushnumber(tolua_S,(lua_Number)heightOut);
  }
 }
 return 4;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getViewport'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawIndexed of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_drawIndexed00
static int tolua_luafunc_GameLib_Graphics_Manager_drawIndexed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  int offset = ((int)  tolua_tonumber(tolua_S,2,0));
  int primitiveNumber = ((int)  tolua_tonumber(tolua_S,3,0));
  GameLib::Graphics::PrimitiveType tolua_var_17 = ((GameLib::Graphics::PrimitiveType) (int)  tolua_tonumber(tolua_S,4,GameLib::Graphics::PRIMITIVE_TRIANGLE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawIndexed'",NULL);
#endif
  {
   self->drawIndexed(offset,primitiveNumber,tolua_var_17);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawIndexed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_draw00
static int tolua_luafunc_GameLib_Graphics_Manager_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  int offset = ((int)  tolua_tonumber(tolua_S,2,0));
  int primitiveNumber = ((int)  tolua_tonumber(tolua_S,3,0));
  GameLib::Graphics::PrimitiveType tolua_var_18 = ((GameLib::Graphics::PrimitiveType) (int)  tolua_tonumber(tolua_S,4,GameLib::Graphics::PRIMITIVE_TRIANGLE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'",NULL);
#endif
  {
   self->draw(offset,primitiveNumber,tolua_var_18);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: blendToScreen of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_blendToScreen00
static int tolua_luafunc_GameLib_Graphics_Manager_blendToScreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::Texture tolua_var_19 = *((GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'blendToScreen'",NULL);
#endif
  {
   self->blendToScreen(tolua_var_19);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'blendToScreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enableFullScreen of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_enableFullScreen00
static int tolua_luafunc_GameLib_Graphics_Manager_enableFullScreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  bool tolua_var_20 = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableFullScreen'",NULL);
#endif
  {
   self->enableFullScreen(tolua_var_20);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableFullScreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: width of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_width00
static int tolua_luafunc_GameLib_Graphics_Manager_width00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Manager* self = (const GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'width'",NULL);
#endif
  {
   int tolua_ret = (int)  self->width();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'width'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: height of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_height00
static int tolua_luafunc_GameLib_Graphics_Manager_height00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Manager* self = (const GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'height'",NULL);
#endif
  {
   int tolua_ret = (int)  self->height();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'height'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fullScreenWindowWidth of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_fullScreenWindowWidth00
static int tolua_luafunc_GameLib_Graphics_Manager_fullScreenWindowWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Manager* self = (const GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fullScreenWindowWidth'",NULL);
#endif
  {
   int tolua_ret = (int)  self->fullScreenWindowWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fullScreenWindowWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fullScreenWindowHeight of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_fullScreenWindowHeight00
static int tolua_luafunc_GameLib_Graphics_Manager_fullScreenWindowHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Manager* self = (const GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fullScreenWindowHeight'",NULL);
#endif
  {
   int tolua_ret = (int)  self->fullScreenWindowHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fullScreenWindowHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: frameId of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_frameId00
static int tolua_luafunc_GameLib_Graphics_Manager_frameId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Manager* self = (const GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'frameId'",NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->frameId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'frameId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: captureScreen of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_captureScreen00
static int tolua_luafunc_GameLib_Graphics_Manager_captureScreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'captureScreen'",NULL);
#endif
  {
   self->captureScreen(filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'captureScreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightingMode of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setLightingMode00
static int tolua_luafunc_GameLib_Graphics_Manager_setLightingMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::LightingMode tolua_var_21 = ((GameLib::Graphics::LightingMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightingMode'",NULL);
#endif
  {
   self->setLightingMode(tolua_var_21);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightingMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightPosition of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setLightPosition00
static int tolua_luafunc_GameLib_Graphics_Manager_setLightPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const GameLib::Math::Vector3* position = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightPosition'",NULL);
#endif
  {
   self->setLightPosition(index,*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightIntensity of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setLightIntensity00
static int tolua_luafunc_GameLib_Graphics_Manager_setLightIntensity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  float intensity = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightIntensity'",NULL);
#endif
  {
   self->setLightIntensity(index,intensity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightIntensity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightColor of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setLightColor00
static int tolua_luafunc_GameLib_Graphics_Manager_setLightColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const GameLib::Math::Vector3* tolua_var_22 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightColor'",NULL);
#endif
  {
   self->setLightColor(index,*tolua_var_22);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEyePosition of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setEyePosition00
static int tolua_luafunc_GameLib_Graphics_Manager_setEyePosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* position = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEyePosition'",NULL);
#endif
  {
   self->setEyePosition(*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEyePosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDiffuseColor of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setDiffuseColor00
static int tolua_luafunc_GameLib_Graphics_Manager_setDiffuseColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_23 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDiffuseColor'",NULL);
#endif
  {
   self->setDiffuseColor(*tolua_var_23);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDiffuseColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpecularColor of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setSpecularColor00
static int tolua_luafunc_GameLib_Graphics_Manager_setSpecularColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_24 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpecularColor'",NULL);
#endif
  {
   self->setSpecularColor(*tolua_var_24);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpecularColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEmissionColor of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setEmissionColor00
static int tolua_luafunc_GameLib_Graphics_Manager_setEmissionColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_25 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEmissionColor'",NULL);
#endif
  {
   self->setEmissionColor(*tolua_var_25);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEmissionColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAmbientColor of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setAmbientColor00
static int tolua_luafunc_GameLib_Graphics_Manager_setAmbientColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_26 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAmbientColor'",NULL);
#endif
  {
   self->setAmbientColor(*tolua_var_26);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAmbientColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTransparency of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setTransparency00
static int tolua_luafunc_GameLib_Graphics_Manager_setTransparency00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_27 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTransparency'",NULL);
#endif
  {
   self->setTransparency(tolua_var_27);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTransparency'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpecularSharpness of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_setSpecularSharpness00
static int tolua_luafunc_GameLib_Graphics_Manager_setSpecularSharpness00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_28 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpecularSharpness'",NULL);
#endif
  {
   self->setSpecularSharpness(tolua_var_28);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpecularSharpness'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dxDevice of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_dxDevice00
static int tolua_luafunc_GameLib_Graphics_Manager_dxDevice00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dxDevice'",NULL);
#endif
  {
   IDirect3DDevice9* tolua_ret = (IDirect3DDevice9*)  self->dxDevice();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"IDirect3DDevice9");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dxDevice'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLightingMode of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_getLightingMode00
static int tolua_luafunc_GameLib_Graphics_Manager_getLightingMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Graphics::Manager* self = (const GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLightingMode'",NULL);
#endif
  {
   GameLib::Graphics::LightingMode tolua_ret = (GameLib::Graphics::LightingMode)  self->getLightingMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLightingMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendWorldMatrixArray of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_sendWorldMatrixArray00
static int tolua_luafunc_GameLib_Graphics_Manager_sendWorldMatrixArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Matrix34* matArray = ((const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,2,0));
  unsigned int matrixArrayLength = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendWorldMatrixArray'",NULL);
#endif
  {
   self->sendWorldMatrixArray(matArray,matrixArrayLength);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendWorldMatrixArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enableVertexBlend of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_enableVertexBlend00
static int tolua_luafunc_GameLib_Graphics_Manager_enableVertexBlend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableVertexBlend'",NULL);
#endif
  {
   self->enableVertexBlend(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableVertexBlend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enableMME of class  GameLib::Graphics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Graphics_Manager_enableMME00
static int tolua_luafunc_GameLib_Graphics_Manager_enableMME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Graphics::Manager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Graphics::Manager* self = (GameLib::Graphics::Manager*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableMME'",NULL);
#endif
  {
   self->enableMME(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableMME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new00
static int tolua_luafunc_GameLib_Math_Vector4_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new00_local
static int tolua_luafunc_GameLib_Math_Vector4_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new01
static int tolua_luafunc_GameLib_Math_Vector4_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float tolua_var_30 = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(tolua_var_30);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new01_local
static int tolua_luafunc_GameLib_Math_Vector4_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float tolua_var_30 = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(tolua_var_30);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new02
static int tolua_luafunc_GameLib_Math_Vector4_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float tolua_var_31 = ((float)  tolua_tonumber(tolua_S,2,0));
  float tolua_var_32 = ((float)  tolua_tonumber(tolua_S,3,0));
  float tolua_var_33 = ((float)  tolua_tonumber(tolua_S,4,0));
  float tolua_var_34 = ((float)  tolua_tonumber(tolua_S,5,1.f));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(tolua_var_31,tolua_var_32,tolua_var_33,tolua_var_34);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new02_local
static int tolua_luafunc_GameLib_Math_Vector4_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float tolua_var_31 = ((float)  tolua_tonumber(tolua_S,2,0));
  float tolua_var_32 = ((float)  tolua_tonumber(tolua_S,3,0));
  float tolua_var_33 = ((float)  tolua_tonumber(tolua_S,4,0));
  float tolua_var_34 = ((float)  tolua_tonumber(tolua_S,5,1.f));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(tolua_var_31,tolua_var_32,tolua_var_33,tolua_var_34);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new03
static int tolua_luafunc_GameLib_Math_Vector4_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const GameLib::Math::Vector4* tolua_var_35 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(*tolua_var_35);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new03_local
static int tolua_luafunc_GameLib_Math_Vector4_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const GameLib::Math::Vector4* tolua_var_35 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(*tolua_var_35);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new04
static int tolua_luafunc_GameLib_Math_Vector4_new04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const GameLib::Math::Vector3* tolua_var_36 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(*tolua_var_36);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new04_local
static int tolua_luafunc_GameLib_Math_Vector4_new04_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const GameLib::Math::Vector3* tolua_var_36 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(*tolua_var_36);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new03_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new05
static int tolua_luafunc_GameLib_Math_Vector4_new05(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btVector3* tolua_var_37 = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(*tolua_var_37);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new04(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new05_local
static int tolua_luafunc_GameLib_Math_Vector4_new05_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btVector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const btVector3* tolua_var_37 = ((const btVector3*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(*tolua_var_37);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new04_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new06
static int tolua_luafunc_GameLib_Math_Vector4_new06(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DXVECTOR3* tolua_var_38 = ((const D3DXVECTOR3*)  tolua_tousertype(tolua_S,2,0));
  float tolua_var_39 = ((float)  tolua_tonumber(tolua_S,3,1.f));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(*tolua_var_38,tolua_var_39);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new05(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new06_local
static int tolua_luafunc_GameLib_Math_Vector4_new06_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DXVECTOR3* tolua_var_38 = ((const D3DXVECTOR3*)  tolua_tousertype(tolua_S,2,0));
  float tolua_var_39 = ((float)  tolua_tonumber(tolua_S,3,1.f));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(*tolua_var_38,tolua_var_39);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new05_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new07
static int tolua_luafunc_GameLib_Math_Vector4_new07(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXVECTOR4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DXVECTOR4* tolua_var_40 = ((const D3DXVECTOR4*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(*tolua_var_40);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new06(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_new07_local
static int tolua_luafunc_GameLib_Math_Vector4_new07_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXVECTOR4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const D3DXVECTOR4* tolua_var_40 = ((const D3DXVECTOR4*)  tolua_tousertype(tolua_S,2,0));
  {
   GameLib::Math::Vector4* tolua_ret = (GameLib::Math::Vector4*)  new GameLib::Math::Vector4(*tolua_var_40);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Vector4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4_new06_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: set of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4_set00
static int tolua_luafunc_GameLib_Math_Vector4_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_41 = ((float)  tolua_tonumber(tolua_S,2,0));
  float tolua_var_42 = ((float)  tolua_tonumber(tolua_S,3,0));
  float tolua_var_43 = ((float)  tolua_tonumber(tolua_S,4,0));
  float tolua_var_44 = ((float)  tolua_tonumber(tolua_S,5,1.f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'",NULL);
#endif
  {
   self->set(tolua_var_41,tolua_var_42,tolua_var_43,tolua_var_44);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4__seti00
static int tolua_luafunc_GameLib_Math_Vector4__seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_46 = ((int)  tolua_tonumber(tolua_S,2,0));
  float tolua_value = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'",NULL);
#endif
  self->operator[](tolua_var_46) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4__geti00
static int tolua_luafunc_GameLib_Math_Vector4__geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_45 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'",NULL);
#endif
  {
   float tolua_ret = (float)  self->operator[](tolua_var_45);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Vector4__geti01
static int tolua_luafunc_GameLib_Math_Vector4__geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const GameLib::Math::Vector4* self = (const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
  int tolua_var_47 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'",NULL);
#endif
  {
   float tolua_ret = (float)  self->operator[](tolua_var_47);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Vector4__geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Vector4_x
static int tolua_get_GameLib__Math__Vector4_x(lua_State* tolua_S)
{
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Vector4_x
static int tolua_set_GameLib__Math__Vector4_x(lua_State* tolua_S)
{
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Vector4_y
static int tolua_get_GameLib__Math__Vector4_y(lua_State* tolua_S)
{
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Vector4_y
static int tolua_set_GameLib__Math__Vector4_y(lua_State* tolua_S)
{
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: z of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Vector4_z
static int tolua_get_GameLib__Math__Vector4_z(lua_State* tolua_S)
{
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->z);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: z of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Vector4_z
static int tolua_set_GameLib__Math__Vector4_z(lua_State* tolua_S)
{
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->z = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: w of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Vector4_w
static int tolua_get_GameLib__Math__Vector4_w(lua_State* tolua_S)
{
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'w'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->w);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: w of class  GameLib::Math::Vector4 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Vector4_w
static int tolua_set_GameLib__Math__Vector4_w(lua_State* tolua_S)
{
  GameLib::Math::Vector4* self = (GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'w'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->w = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_new00
static int tolua_luafunc_GameLib_Math_Matrix34_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Math::Matrix34* tolua_ret = (GameLib::Math::Matrix34*)  new GameLib::Math::Matrix34();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameLib::Math::Matrix34");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_new00_local
static int tolua_luafunc_GameLib_Math_Matrix34_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameLib::Math::Matrix34* tolua_ret = (GameLib::Math::Matrix34*)  new GameLib::Math::Matrix34();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"GameLib::Math::Matrix34");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIdentity of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setIdentity00
static int tolua_luafunc_GameLib_Math_Matrix34_setIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIdentity'",NULL);
#endif
  {
   self->setIdentity();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTranslation of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setTranslation00
static int tolua_luafunc_GameLib_Math_Matrix34_setTranslation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_83 = ((float)  tolua_tonumber(tolua_S,2,0));
  float tolua_var_84 = ((float)  tolua_tonumber(tolua_S,3,0));
  float tolua_var_85 = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTranslation'",NULL);
#endif
  {
   self->setTranslation(tolua_var_83,tolua_var_84,tolua_var_85);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTranslation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTranslation of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setTranslation01
static int tolua_luafunc_GameLib_Math_Matrix34_setTranslation01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_86 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTranslation'",NULL);
#endif
  {
   self->setTranslation(*tolua_var_86);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Matrix34_setTranslation00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotationX of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setRotationX00
static int tolua_luafunc_GameLib_Math_Matrix34_setRotationX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_87 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotationX'",NULL);
#endif
  {
   self->setRotationX(tolua_var_87);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotationX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotationY of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setRotationY00
static int tolua_luafunc_GameLib_Math_Matrix34_setRotationY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_88 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotationY'",NULL);
#endif
  {
   self->setRotationY(tolua_var_88);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotationY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotationZ of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setRotationZ00
static int tolua_luafunc_GameLib_Math_Matrix34_setRotationZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_89 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotationZ'",NULL);
#endif
  {
   self->setRotationZ(tolua_var_89);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotationZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaling of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setScaling00
static int tolua_luafunc_GameLib_Math_Matrix34_setScaling00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float xyz = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaling'",NULL);
#endif
  {
   self->setScaling(xyz);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaling'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaling of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setScaling01
static int tolua_luafunc_GameLib_Math_Matrix34_setScaling01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaling'",NULL);
#endif
  {
   self->setScaling(x,y,z);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Matrix34_setScaling00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaling of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setScaling02
static int tolua_luafunc_GameLib_Math_Matrix34_setScaling02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_90 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaling'",NULL);
#endif
  {
   self->setScaling(*tolua_var_90);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Matrix34_setScaling01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewTransform of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setViewTransform00
static int tolua_luafunc_GameLib_Math_Matrix34_setViewTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* eyePosition = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* eyeTarget = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
  const GameLib::Math::Vector3* upVector = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewTransform'",NULL);
#endif
  {
   self->setViewTransform(*eyePosition,*eyeTarget,*upVector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewTransformRH of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setViewTransformRH00
static int tolua_luafunc_GameLib_Math_Matrix34_setViewTransformRH00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* eyePosition = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* eyeTarget = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
  const GameLib::Math::Vector3* upVector = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewTransformRH'",NULL);
#endif
  {
   self->setViewTransformRH(*eyePosition,*eyeTarget,*upVector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewTransformRH'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewTransformLH of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setViewTransformLH00
static int tolua_luafunc_GameLib_Math_Matrix34_setViewTransformLH00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* eyePosition = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* eyeTarget = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
  const GameLib::Math::Vector3* upVector = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewTransformLH'",NULL);
#endif
  {
   self->setViewTransformLH(*eyePosition,*eyeTarget,*upVector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewTransformLH'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: translate of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_translate00
static int tolua_luafunc_GameLib_Math_Matrix34_translate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_91 = ((float)  tolua_tonumber(tolua_S,2,0));
  float tolua_var_92 = ((float)  tolua_tonumber(tolua_S,3,0));
  float tolua_var_93 = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'translate'",NULL);
#endif
  {
   self->translate(tolua_var_91,tolua_var_92,tolua_var_93);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'translate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: translate of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_translate01
static int tolua_luafunc_GameLib_Math_Matrix34_translate01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_94 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'translate'",NULL);
#endif
  {
   self->translate(*tolua_var_94);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Matrix34_translate00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotateX of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_rotateX00
static int tolua_luafunc_GameLib_Math_Matrix34_rotateX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_95 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotateX'",NULL);
#endif
  {
   self->rotateX(tolua_var_95);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotateX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotateY of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_rotateY00
static int tolua_luafunc_GameLib_Math_Matrix34_rotateY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_96 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotateY'",NULL);
#endif
  {
   self->rotateY(tolua_var_96);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotateY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotateZ of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_rotateZ00
static int tolua_luafunc_GameLib_Math_Matrix34_rotateZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_97 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotateZ'",NULL);
#endif
  {
   self->rotateZ(tolua_var_97);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotateZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scale of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_scale00
static int tolua_luafunc_GameLib_Math_Matrix34_scale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float xyz = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scale'",NULL);
#endif
  {
   self->scale(xyz);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scale of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_scale01
static int tolua_luafunc_GameLib_Math_Matrix34_scale01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scale'",NULL);
#endif
  {
   self->scale(x,y,z);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Matrix34_scale00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: scale of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_scale02
static int tolua_luafunc_GameLib_Math_Matrix34_scale02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* tolua_var_98 = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scale'",NULL);
#endif
  {
   self->scale(*tolua_var_98);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Matrix34_scale01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: mul of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_mul00
static int tolua_luafunc_GameLib_Math_Matrix34_mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Math::Matrix34* self = (const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Math::Vector3* out = ((GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* in = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mul'",NULL);
#endif
  {
   self->mul(out,*in);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: mul33 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_mul3300
static int tolua_luafunc_GameLib_Math_Matrix34_mul3300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Math::Matrix34* self = (const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Math::Vector3* out = ((GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Vector3* in = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mul33'",NULL);
#endif
  {
   self->mul33(out,*in);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mul33'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMul of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setMul00
static int tolua_luafunc_GameLib_Math_Matrix34_setMul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Matrix34* tolua_var_99 = ((const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Matrix34* tolua_var_100 = ((const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMul'",NULL);
#endif
  {
   self->setMul(*tolua_var_99,*tolua_var_100);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMul of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setMul01
static int tolua_luafunc_GameLib_Math_Matrix34_setMul01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Matrix33",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Matrix34* tolua_var_101 = ((const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,2,0));
  const GameLib::Math::Matrix33* tolua_var_102 = ((const GameLib::Math::Matrix33*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMul'",NULL);
#endif
  {
   self->setMul(*tolua_var_101,*tolua_var_102);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_GameLib_Math_Matrix34_setMul00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34__eq00
static int tolua_luafunc_GameLib_Math_Matrix34__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameLib::Math::Matrix34* self = (const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Matrix34* tolua_var_103 = ((const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*tolua_var_103);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: transpose33 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_transpose3300
static int tolua_luafunc_GameLib_Math_Matrix34_transpose3300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'transpose33'",NULL);
#endif
  {
   self->transpose33();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'transpose33'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTransposed33 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setTransposed3300
static int tolua_luafunc_GameLib_Math_Matrix34_setTransposed3300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Matrix34* tolua_var_104 = ((const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTransposed33'",NULL);
#endif
  {
   self->setTransposed33(*tolua_var_104);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTransposed33'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: invert of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_invert00
static int tolua_luafunc_GameLib_Math_Matrix34_invert00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'invert'",NULL);
#endif
  {
   self->invert();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'invert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInverse of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameLib_Math_Matrix34_setInverse00
static int tolua_luafunc_GameLib_Math_Matrix34_setInverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Matrix34",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Matrix34* tolua_var_105 = ((const GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInverse'",NULL);
#endif
  {
   self->setInverse(*tolua_var_105);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m00 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m00
static int tolua_get_GameLib__Math__Matrix34_m00(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm00'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m00);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m00 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m00
static int tolua_set_GameLib__Math__Matrix34_m00(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm00'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m00 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m01 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m01
static int tolua_get_GameLib__Math__Matrix34_m01(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm01'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m01);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m01 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m01
static int tolua_set_GameLib__Math__Matrix34_m01(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm01'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m01 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m02 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m02
static int tolua_get_GameLib__Math__Matrix34_m02(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm02'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m02);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m02 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m02
static int tolua_set_GameLib__Math__Matrix34_m02(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm02'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m02 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m03 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m03
static int tolua_get_GameLib__Math__Matrix34_m03(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm03'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m03);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m03 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m03
static int tolua_set_GameLib__Math__Matrix34_m03(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm03'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m03 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m10 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m10
static int tolua_get_GameLib__Math__Matrix34_m10(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm10'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m10);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m10 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m10
static int tolua_set_GameLib__Math__Matrix34_m10(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm10'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m10 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m11 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m11
static int tolua_get_GameLib__Math__Matrix34_m11(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm11'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m11);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m11 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m11
static int tolua_set_GameLib__Math__Matrix34_m11(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm11'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m11 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m12 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m12
static int tolua_get_GameLib__Math__Matrix34_m12(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm12'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m12);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m12 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m12
static int tolua_set_GameLib__Math__Matrix34_m12(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm12'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m12 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m13 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m13
static int tolua_get_GameLib__Math__Matrix34_m13(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm13'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m13);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m13 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m13
static int tolua_set_GameLib__Math__Matrix34_m13(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm13'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m13 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m20 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m20
static int tolua_get_GameLib__Math__Matrix34_m20(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm20'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m20);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m20 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m20
static int tolua_set_GameLib__Math__Matrix34_m20(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm20'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m20 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m21 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m21
static int tolua_get_GameLib__Math__Matrix34_m21(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm21'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m21);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m21 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m21
static int tolua_set_GameLib__Math__Matrix34_m21(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm21'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m21 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m22 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m22
static int tolua_get_GameLib__Math__Matrix34_m22(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm22'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m22);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m22 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m22
static int tolua_set_GameLib__Math__Matrix34_m22(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm22'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m22 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m23 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_get_GameLib__Math__Matrix34_m23
static int tolua_get_GameLib__Math__Matrix34_m23(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm23'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m23);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m23 of class  GameLib::Math::Matrix34 */
#ifndef TOLUA_DISABLE_tolua_set_GameLib__Math__Matrix34_m23
static int tolua_set_GameLib__Math__Matrix34_m23(lua_State* tolua_S)
{
  GameLib::Math::Matrix34* self = (GameLib::Math::Matrix34*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm23'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m23 = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  XmlLoader::MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_MME_Object_ModelKai_new00
static int tolua_luafunc_XmlLoader_MME_Object_ModelKai_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"XmlLoader::MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   XmlLoader::MME::Object::ModelKai* tolua_ret = (XmlLoader::MME::Object::ModelKai*)  new XmlLoader::MME::Object::ModelKai();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"XmlLoader::MME::Object::ModelKai");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  XmlLoader::MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_MME_Object_ModelKai_new00_local
static int tolua_luafunc_XmlLoader_MME_Object_ModelKai_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"XmlLoader::MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   XmlLoader::MME::Object::ModelKai* tolua_ret = (XmlLoader::MME::Object::ModelKai*)  new XmlLoader::MME::Object::ModelKai();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"XmlLoader::MME::Object::ModelKai");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  XmlLoader::MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_MME_Object_ModelKai_delete00
static int tolua_luafunc_XmlLoader_MME_Object_ModelKai_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::MME::Object::ModelKai* self = (XmlLoader::MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadStart of class  XmlLoader::MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_MME_Object_ModelKai_loadStart00
static int tolua_luafunc_XmlLoader_MME_Object_ModelKai_loadStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::MME::Object::ModelKai* self = (XmlLoader::MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadStart'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->loadStart(fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  XmlLoader::MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_MME_Object_ModelKai_isReady00
static int tolua_luafunc_XmlLoader_MME_Object_ModelKai_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::MME::Object::ModelKai* self = (XmlLoader::MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  XmlLoader::MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_MME_Object_ModelKai_instance00
static int tolua_luafunc_XmlLoader_MME_Object_ModelKai_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::MME::Object::ModelKai* self = (XmlLoader::MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'instance'",NULL);
#endif
  {
    std::shared_ptr<MME::Object::ModelKai> tolua_ret = (  std::shared_ptr<MME::Object::ModelKai>)  self->instance();
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<MME::Object::ModelKai>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MME::Object::ModelKai>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<MME::Object::ModelKai>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MME::Object::ModelKai>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  XmlLoader::GameObject::Accessory */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Accessory_new00
static int tolua_luafunc_XmlLoader_GameObject_Accessory_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"XmlLoader::GameObject::Accessory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   XmlLoader::GameObject::Accessory* tolua_ret = (XmlLoader::GameObject::Accessory*)  new XmlLoader::GameObject::Accessory();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"XmlLoader::GameObject::Accessory");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  XmlLoader::GameObject::Accessory */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Accessory_new00_local
static int tolua_luafunc_XmlLoader_GameObject_Accessory_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"XmlLoader::GameObject::Accessory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   XmlLoader::GameObject::Accessory* tolua_ret = (XmlLoader::GameObject::Accessory*)  new XmlLoader::GameObject::Accessory();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"XmlLoader::GameObject::Accessory");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  XmlLoader::GameObject::Accessory */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Accessory_delete00
static int tolua_luafunc_XmlLoader_GameObject_Accessory_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Accessory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Accessory* self = (XmlLoader::GameObject::Accessory*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  XmlLoader::GameObject::Accessory */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Accessory_isReady00
static int tolua_luafunc_XmlLoader_GameObject_Accessory_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Accessory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Accessory* self = (XmlLoader::GameObject::Accessory*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  XmlLoader::GameObject::Accessory */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Accessory_instance00
static int tolua_luafunc_XmlLoader_GameObject_Accessory_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Accessory",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btCollisionObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Accessory* self = (XmlLoader::GameObject::Accessory*)  tolua_tousertype(tolua_S,1,0);
  btCollisionObject* owner = ((btCollisionObject*)  tolua_tousertype(tolua_S,2,0));
  const btTransform* startTrans = ((const btTransform*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'instance'",NULL);
#endif
  {
  ::GameObject::AccessorySharedPtr tolua_ret = (::GameObject::AccessorySharedPtr)  self->instance(owner,*startTrans);
   {
#ifdef __cplusplus
    void* tolua_obj = new::GameObject::AccessorySharedPtr(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"::GameObject::AccessorySharedPtr");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(::GameObject::AccessorySharedPtr));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"::GameObject::AccessorySharedPtr");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_create00
static int tolua_luafunc_GameObject_Player_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"std::shared_ptr<MME::Object::ModelKai>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"std::shared_ptr<btCylinderShape>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"std::shared_ptr<btMotionState>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"std::shared_ptr<btRigidBody>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,7,"std::shared_ptr<Camera::ICamera>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,8,"Input::PlayerMouseSharedPtr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,9,"std::shared_ptr<GameObjectData::Status>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float height = ((float)  tolua_tonumber(tolua_S,2,0));
   std::shared_ptr<MME::Object::ModelKai> model = *((  std::shared_ptr<MME::Object::ModelKai>*)  tolua_tousertype(tolua_S,3,0));
   std::shared_ptr<btCylinderShape> shape = *((  std::shared_ptr<btCylinderShape>*)  tolua_tousertype(tolua_S,4,0));
   std::shared_ptr<btMotionState> motionState = *((  std::shared_ptr<btMotionState>*)  tolua_tousertype(tolua_S,5,0));
   std::shared_ptr<btRigidBody> rigidbody = *((  std::shared_ptr<btRigidBody>*)  tolua_tousertype(tolua_S,6,0));
   std::shared_ptr<Camera::ICamera> camera = *((  std::shared_ptr<Camera::ICamera>*)  tolua_tousertype(tolua_S,7,0));
  Input::PlayerMouseSharedPtr mouse = *((Input::PlayerMouseSharedPtr*)  tolua_tousertype(tolua_S,8,0));
   std::shared_ptr<GameObjectData::Status> status = *((  std::shared_ptr<GameObjectData::Status>*)  tolua_tousertype(tolua_S,9,0));
  {
   std::shared_ptr<GameObject::Player> tolua_ret = (std::shared_ptr<GameObject::Player>)  GameObject::Player::create(height,model,shape,motionState,rigidbody,camera,mouse,status);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<GameObject::Player>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Player>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<GameObject::Player>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Player>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_create01
static int tolua_luafunc_GameObject_Player_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"std::shared_ptr<GameObject::Utils::Character>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"std::shared_ptr<GameObjectData::Status>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
   std::shared_ptr<GameObject::Utils::Character> character = *((  std::shared_ptr<GameObject::Utils::Character>*)  tolua_tousertype(tolua_S,2,0));
   std::shared_ptr<GameObjectData::Status> status = *((  std::shared_ptr<GameObjectData::Status>*)  tolua_tousertype(tolua_S,3,0));
  {
   std::shared_ptr<GameObject::Player> tolua_ret = (std::shared_ptr<GameObject::Player>)  GameObject::Player::create(character,status);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<GameObject::Player>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Player>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<GameObject::Player>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Player>");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameObject_Player_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_delete00
static int tolua_luafunc_GameObject_Player_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: release of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_release00
static int tolua_luafunc_GameObject_Player_release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'release'",NULL);
#endif
  {
   self->release();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_update00
static int tolua_luafunc_GameObject_Player_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
  float elapsedTime = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
  {
   self->update(elapsedTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: preDraw of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_preDraw00
static int tolua_luafunc_GameObject_Player_preDraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Player* self = (const GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'preDraw'",NULL);
#endif
  {
   self->preDraw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'preDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawHUD of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_drawHUD00
static int tolua_luafunc_GameObject_Player_drawHUD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Player* self = (const GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawHUD'",NULL);
#endif
  {
   self->drawHUD();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawHUD'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRTTI of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_getRTTI00
static int tolua_luafunc_GameObject_Player_getRTTI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Player* self = (const GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRTTI'",NULL);
#endif
  {
   const RTTI& tolua_ret = (const RTTI&)  self->getRTTI();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const RTTI");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRTTI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rtti of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_get_GameObject__Player_rtti
static int tolua_get_GameObject__Player_rtti(lua_State* tolua_S)
{
  tolua_pushusertype(tolua_S,(void*)&GameObject::Player::rtti,"const RTTI");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromWorld of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_removeFromWorld00
static int tolua_luafunc_GameObject_Player_removeFromWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromWorld'",NULL);
#endif
  {
   self->removeFromWorld();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFromWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addToWorld of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_addToWorld00
static int tolua_luafunc_GameObject_Player_addToWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addToWorld'",NULL);
#endif
  {
   self->addToWorld();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addToWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onCollisionEnter of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_onCollisionEnter00
static int tolua_luafunc_GameObject_Player_onCollisionEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btPersistentManifold",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"btCollisionObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"btCollisionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
  btPersistentManifold* manifold = ((btPersistentManifold*)  tolua_tousertype(tolua_S,2,0));
  btCollisionObject* me = ((btCollisionObject*)  tolua_tousertype(tolua_S,3,0));
  btCollisionObject* obj = ((btCollisionObject*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onCollisionEnter'",NULL);
#endif
  {
   self->onCollisionEnter(manifold,me,obj);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onCollisionEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onCollisionStay of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_onCollisionStay00
static int tolua_luafunc_GameObject_Player_onCollisionStay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btPersistentManifold",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"btCollisionObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"btCollisionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
  btPersistentManifold* manifold = ((btPersistentManifold*)  tolua_tousertype(tolua_S,2,0));
  btCollisionObject* me = ((btCollisionObject*)  tolua_tousertype(tolua_S,3,0));
  btCollisionObject* obj = ((btCollisionObject*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onCollisionStay'",NULL);
#endif
  {
   self->onCollisionStay(manifold,me,obj);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onCollisionStay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onCollisionExit of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_onCollisionExit00
static int tolua_luafunc_GameObject_Player_onCollisionExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btCollisionObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"btCollisionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
  btCollisionObject* me = ((btCollisionObject*)  tolua_tousertype(tolua_S,2,0));
  btCollisionObject* obj = ((btCollisionObject*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onCollisionExit'",NULL);
#endif
  {
   self->onCollisionExit(me,obj);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onCollisionExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getElapsedTime of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_getElapsedTime00
static int tolua_luafunc_GameObject_Player_getElapsedTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Player* self = (const GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getElapsedTime'",NULL);
#endif
  {
   float tolua_ret = (float)  self->getElapsedTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getElapsedTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMouse of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_getMouse00
static int tolua_luafunc_GameObject_Player_getMouse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMouse'",NULL);
#endif
  {
   Input::PlayerMouse* tolua_ret = (Input::PlayerMouse*)  self->getMouse();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Input::PlayerMouse");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMouse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMousePos of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_getMousePos00
static int tolua_luafunc_GameObject_Player_getMousePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Player* self = (const GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMousePos'",NULL);
#endif
  {
   btVector3 tolua_ret = (btVector3)  self->getMousePos();
   {
#ifdef __cplusplus
    void* tolua_obj = new btVector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(btVector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"btVector3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMousePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getModel of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_getModel00
static int tolua_luafunc_GameObject_Player_getModel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getModel'",NULL);
#endif
  {
   MME::Object::ModelKai* tolua_ret = (MME::Object::ModelKai*)  self->getModel();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MME::Object::ModelKai");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getModel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeight of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_getHeight00
static int tolua_luafunc_GameObject_Player_getHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Player* self = (const GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHeight'",NULL);
#endif
  {
   float tolua_ret = (float)  self->getHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStatus of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_getStatus00
static int tolua_luafunc_GameObject_Player_getStatus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStatus'",NULL);
#endif
  {
   GameObjectData::Status* tolua_ret = (GameObjectData::Status*)  self->getStatus();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameObjectData::Status");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStatus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCharacter of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_getCharacter00
static int tolua_luafunc_GameObject_Player_getCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCharacter'",NULL);
#endif
  {
    std::shared_ptr<GameObject::Utils::Character> tolua_ret = (  std::shared_ptr<GameObject::Utils::Character>)  self->getCharacter();
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<GameObject::Utils::Character>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Utils::Character>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<GameObject::Utils::Character>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Utils::Character>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onGround of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_onGround00
static int tolua_luafunc_GameObject_Player_onGround00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Player* self = (const GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onGround'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onGround();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onGround'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addActions of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_addActions00
static int tolua_luafunc_GameObject_Player_addActions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"XmlLoader::Actions",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
  XmlLoader::Actions* actions = ((XmlLoader::Actions*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addActions'",NULL);
#endif
  {
   self->addActions(actions);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addActions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBtCollisionObject of class  GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Player_getBtCollisionObject00
static int tolua_luafunc_GameObject_Player_getBtCollisionObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Player* self = (GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBtCollisionObject'",NULL);
#endif
  {
   btCollisionObject* tolua_ret = (btCollisionObject*)  self->getBtCollisionObject();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btCollisionObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBtCollisionObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  XmlLoader::GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Player_new00
static int tolua_luafunc_XmlLoader_GameObject_Player_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"XmlLoader::GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   XmlLoader::GameObject::Player* tolua_ret = (XmlLoader::GameObject::Player*)  new XmlLoader::GameObject::Player();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"XmlLoader::GameObject::Player");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  XmlLoader::GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Player_new00_local
static int tolua_luafunc_XmlLoader_GameObject_Player_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"XmlLoader::GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   XmlLoader::GameObject::Player* tolua_ret = (XmlLoader::GameObject::Player*)  new XmlLoader::GameObject::Player();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"XmlLoader::GameObject::Player");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  XmlLoader::GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Player_delete00
static int tolua_luafunc_XmlLoader_GameObject_Player_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Player* self = (XmlLoader::GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadXml of class  XmlLoader::GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Player_loadXml00
static int tolua_luafunc_XmlLoader_GameObject_Player_loadXml00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Player",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Player* self = (XmlLoader::GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
  const std::string file = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadXml'",NULL);
#endif
  {
   self->loadXml(file);
   tolua_pushcppstring(tolua_S,(const char*)file);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadXml'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  XmlLoader::GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Player_isReady00
static int tolua_luafunc_XmlLoader_GameObject_Player_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Player* self = (XmlLoader::GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  XmlLoader::GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Player_instance00
static int tolua_luafunc_XmlLoader_GameObject_Player_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Player* self = (XmlLoader::GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'instance'",NULL);
#endif
  {
    std::shared_ptr<GameObject::Player> tolua_ret = (  std::shared_ptr<GameObject::Player>)  self->instance();
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<GameObject::Player>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Player>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<GameObject::Player>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Player>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  XmlLoader::GameObject::Player */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Player_getName00
static int tolua_luafunc_XmlLoader_GameObject_Player_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XmlLoader::GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XmlLoader::GameObject::Player* self = (const XmlLoader::GameObject::Player*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_create00
static int tolua_luafunc_GameObject_Enemy_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"std::shared_ptr<MME::Object::ModelKai>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"std::shared_ptr<btBoxShape>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"std::shared_ptr<btMotionState>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"std::shared_ptr<btRigidBody>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,7,"std::shared_ptr<GameObjectData::Status>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
   std::shared_ptr<MME::Object::ModelKai> model = *((  std::shared_ptr<MME::Object::ModelKai>*)  tolua_tousertype(tolua_S,3,0));
   std::shared_ptr<btBoxShape> shape = *((  std::shared_ptr<btBoxShape>*)  tolua_tousertype(tolua_S,4,0));
   std::shared_ptr<btMotionState> motionState = *((  std::shared_ptr<btMotionState>*)  tolua_tousertype(tolua_S,5,0));
   std::shared_ptr<btRigidBody> rigidbody = *((  std::shared_ptr<btRigidBody>*)  tolua_tousertype(tolua_S,6,0));
   std::shared_ptr<GameObjectData::Status> status = *((  std::shared_ptr<GameObjectData::Status>*)  tolua_tousertype(tolua_S,7,0));
  {
   std::shared_ptr<GameObject::Enemy> tolua_ret = (std::shared_ptr<GameObject::Enemy>)  GameObject::Enemy::create(mass,model,shape,motionState,rigidbody,status);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<GameObject::Enemy>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Enemy>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<GameObject::Enemy>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Enemy>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_delete00
static int tolua_luafunc_GameObject_Enemy_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Enemy* self = (GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRTTI of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_getRTTI00
static int tolua_luafunc_GameObject_Enemy_getRTTI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Enemy* self = (const GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRTTI'",NULL);
#endif
  {
   const RTTI& tolua_ret = (const RTTI&)  self->getRTTI();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const RTTI");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRTTI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rtti of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_get_GameObject__Enemy_rtti
static int tolua_get_GameObject__Enemy_rtti(lua_State* tolua_S)
{
  tolua_pushusertype(tolua_S,(void*)&GameObject::Enemy::rtti,"const RTTI");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: postdraw of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_postdraw00
static int tolua_luafunc_GameObject_Enemy_postdraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Enemy* self = (const GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'postdraw'",NULL);
#endif
  {
   self->postdraw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'postdraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_update00
static int tolua_luafunc_GameObject_Enemy_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Enemy* self = (GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
  float elapsedTime = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
  {
   self->update(elapsedTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromWorld of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_removeFromWorld00
static int tolua_luafunc_GameObject_Enemy_removeFromWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Enemy* self = (GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromWorld'",NULL);
#endif
  {
   self->removeFromWorld();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFromWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addToWorld of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_addToWorld00
static int tolua_luafunc_GameObject_Enemy_addToWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Enemy* self = (GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addToWorld'",NULL);
#endif
  {
   self->addToWorld();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addToWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onCollisionEnter of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_onCollisionEnter00
static int tolua_luafunc_GameObject_Enemy_onCollisionEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Enemy",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btPersistentManifold",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"btCollisionObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"btCollisionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Enemy* self = (GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
  btPersistentManifold* manifold = ((btPersistentManifold*)  tolua_tousertype(tolua_S,2,0));
  btCollisionObject* me = ((btCollisionObject*)  tolua_tousertype(tolua_S,3,0));
  btCollisionObject* obj = ((btCollisionObject*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onCollisionEnter'",NULL);
#endif
  {
   self->onCollisionEnter(manifold,me,obj);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onCollisionEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDied of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_isDied00
static int tolua_luafunc_GameObject_Enemy_isDied00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Enemy* self = (const GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDied'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isDied();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDied'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateWhenDied of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_updateWhenDied00
static int tolua_luafunc_GameObject_Enemy_updateWhenDied00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Enemy* self = (GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_148 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateWhenDied'",NULL);
#endif
  {
   self->updateWhenDied(tolua_var_148);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateWhenDied'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBtCollisionObject of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_getBtCollisionObject00
static int tolua_luafunc_GameObject_Enemy_getBtCollisionObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Enemy* self = (GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBtCollisionObject'",NULL);
#endif
  {
   btCollisionObject* tolua_ret = (btCollisionObject*)  self->getBtCollisionObject();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btCollisionObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBtCollisionObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getConstBtCollisionObject of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_getConstBtCollisionObject00
static int tolua_luafunc_GameObject_Enemy_getConstBtCollisionObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Enemy* self = (const GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getConstBtCollisionObject'",NULL);
#endif
  {
   const btCollisionObject* tolua_ret = (const btCollisionObject*)  self->getConstBtCollisionObject();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"const btCollisionObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getConstBtCollisionObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldTransform of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_getWorldTransform00
static int tolua_luafunc_GameObject_Enemy_getWorldTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Enemy* self = (const GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldTransform'",NULL);
#endif
  {
   const btTransform& tolua_ret = (const btTransform&)  self->getWorldTransform();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const btTransform");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWorldTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldTransform of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_getWorldTransform01
static int tolua_luafunc_GameObject_Enemy_getWorldTransform01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GameObject::Enemy* self = (GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldTransform'",NULL);
#endif
  {
   btTransform& tolua_ret = (btTransform&)  self->getWorldTransform();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"btTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_luafunc_GameObject_Enemy_getWorldTransform00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: isInWorld of class  GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Enemy_isInWorld00
static int tolua_luafunc_GameObject_Enemy_isInWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Enemy* self = (const GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isInWorld'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isInWorld();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isInWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  XmlLoader::GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Enemy_new00
static int tolua_luafunc_XmlLoader_GameObject_Enemy_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"XmlLoader::GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   XmlLoader::GameObject::Enemy* tolua_ret = (XmlLoader::GameObject::Enemy*)  new XmlLoader::GameObject::Enemy();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"XmlLoader::GameObject::Enemy");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  XmlLoader::GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Enemy_new00_local
static int tolua_luafunc_XmlLoader_GameObject_Enemy_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"XmlLoader::GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   XmlLoader::GameObject::Enemy* tolua_ret = (XmlLoader::GameObject::Enemy*)  new XmlLoader::GameObject::Enemy();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"XmlLoader::GameObject::Enemy");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  XmlLoader::GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Enemy_delete00
static int tolua_luafunc_XmlLoader_GameObject_Enemy_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Enemy* self = (XmlLoader::GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createSP of class  XmlLoader::GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Enemy_createSP00
static int tolua_luafunc_XmlLoader_GameObject_Enemy_createSP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"XmlLoader::GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<XmlLoader::GameObject::Enemy> tolua_ret = (std::shared_ptr<XmlLoader::GameObject::Enemy>)  XmlLoader::GameObject::Enemy::createSP();
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<XmlLoader::GameObject::Enemy>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<XmlLoader::GameObject::Enemy>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<XmlLoader::GameObject::Enemy>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<XmlLoader::GameObject::Enemy>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createSP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadXml of class  XmlLoader::GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Enemy_loadXml00
static int tolua_luafunc_XmlLoader_GameObject_Enemy_loadXml00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Enemy",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Enemy* self = (XmlLoader::GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
  const std::string file = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadXml'",NULL);
#endif
  {
   self->loadXml(file);
   tolua_pushcppstring(tolua_S,(const char*)file);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadXml'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  XmlLoader::GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Enemy_isReady00
static int tolua_luafunc_XmlLoader_GameObject_Enemy_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Enemy* self = (XmlLoader::GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  XmlLoader::GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Enemy_instance00
static int tolua_luafunc_XmlLoader_GameObject_Enemy_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XmlLoader::GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XmlLoader::GameObject::Enemy* self = (XmlLoader::GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'instance'",NULL);
#endif
  {
  ::GameObject::EnemySharedPtr tolua_ret = (::GameObject::EnemySharedPtr)  self->instance();
   {
#ifdef __cplusplus
    void* tolua_obj = new::GameObject::EnemySharedPtr(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"::GameObject::EnemySharedPtr");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(::GameObject::EnemySharedPtr));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"::GameObject::EnemySharedPtr");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  XmlLoader::GameObject::Enemy */
#ifndef TOLUA_DISABLE_tolua_luafunc_XmlLoader_GameObject_Enemy_getName00
static int tolua_luafunc_XmlLoader_GameObject_Enemy_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XmlLoader::GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XmlLoader::GameObject::Enemy* self = (const XmlLoader::GameObject::Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'",NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  std::shared_ptr<XmlLoader::GameObject::Enemy> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__new00
static int tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<XmlLoader::GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<XmlLoader::GameObject::Enemy>* tolua_ret = (std::shared_ptr<XmlLoader::GameObject::Enemy>*)  new std::shared_ptr<XmlLoader::GameObject::Enemy>();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::shared_ptr<XmlLoader::GameObject::Enemy>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  std::shared_ptr<XmlLoader::GameObject::Enemy> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__new00_local
static int tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<XmlLoader::GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<XmlLoader::GameObject::Enemy>* tolua_ret = (std::shared_ptr<XmlLoader::GameObject::Enemy>*)  new std::shared_ptr<XmlLoader::GameObject::Enemy>();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"std::shared_ptr<XmlLoader::GameObject::Enemy>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  std::shared_ptr<XmlLoader::GameObject::Enemy> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__delete00
static int tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<XmlLoader::GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<XmlLoader::GameObject::Enemy>* self = (std::shared_ptr<XmlLoader::GameObject::Enemy>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  std::shared_ptr<XmlLoader::GameObject::Enemy> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__reset00
static int tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<XmlLoader::GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"XmlLoader::GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<XmlLoader::GameObject::Enemy>* self = (std::shared_ptr<XmlLoader::GameObject::Enemy>*)  tolua_tousertype(tolua_S,1,0);
  XmlLoader::GameObject::Enemy* tolua_var_106 = ((XmlLoader::GameObject::Enemy*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
  {
   self->reset(tolua_var_106);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  std::shared_ptr<XmlLoader::GameObject::Enemy> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__get00
static int tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<XmlLoader::GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<XmlLoader::GameObject::Enemy>* self = (const std::shared_ptr<XmlLoader::GameObject::Enemy>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
  {
   XmlLoader::GameObject::Enemy* tolua_ret = (XmlLoader::GameObject::Enemy*)  self->get();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"XmlLoader::GameObject::Enemy");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_instance00
static int tolua_luafunc_MME_Manager_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MME::Manager* tolua_ret = (MME::Manager*)  MME::Manager::instance();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MME::Manager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_destroy00
static int tolua_luafunc_MME_Manager_destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy'",NULL);
#endif
  {
   self->destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_isReady00
static int tolua_luafunc_MME_Manager_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawAll of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_drawAll00
static int tolua_luafunc_MME_Manager_drawAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawAll'",NULL);
#endif
  {
   self->drawAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawIndexed of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_drawIndexed00
static int tolua_luafunc_MME_Manager_drawIndexed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int offset = ((int)  tolua_tonumber(tolua_S,2,0));
  int primitiveNumber = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawIndexed'",NULL);
#endif
  {
   self->drawIndexed(offset,primitiveNumber);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawIndexed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_draw00
static int tolua_luafunc_MME_Manager_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int offset = ((int)  tolua_tonumber(tolua_S,2,0));
  int primitiveNumber = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'",NULL);
#endif
  {
   self->draw(offset,primitiveNumber);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVertexBuffer of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setVertexBuffer00
static int tolua_luafunc_MME_Manager_setVertexBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::VertexBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::VertexBuffer tolua_var_107 = *((GameLib::Graphics::VertexBuffer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVertexBuffer'",NULL);
#endif
  {
   self->setVertexBuffer(tolua_var_107);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVertexBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIndexBuffer of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setIndexBuffer00
static int tolua_luafunc_MME_Manager_setIndexBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::IndexBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::IndexBuffer tolua_var_108 = *((GameLib::Graphics::IndexBuffer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIndexBuffer'",NULL);
#endif
  {
   self->setIndexBuffer(tolua_var_108);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIndexBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimatedVertexBoneBuffer of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setAnimatedVertexBoneBuffer00
static int tolua_luafunc_MME_Manager_setAnimatedVertexBoneBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::AnimatedVertexBoneBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::AnimatedVertexBoneBuffer tolua_var_109 = *((GameLib::Graphics::AnimatedVertexBoneBuffer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimatedVertexBoneBuffer'",NULL);
#endif
  {
   self->setAnimatedVertexBoneBuffer(tolua_var_109);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimatedVertexBoneBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTexture of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setTexture00
static int tolua_luafunc_MME_Manager_setTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::Texture tolua_var_110 = *((GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTexture'",NULL);
#endif
  {
   self->setTexture(tolua_var_110);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setToonTexture of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setToonTexture00
static int tolua_luafunc_MME_Manager_setToonTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::Texture tolua_var_111 = *((GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setToonTexture'",NULL);
#endif
  {
   self->setToonTexture(tolua_var_111);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setToonTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSphereTexture of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setSphereTexture00
static int tolua_luafunc_MME_Manager_setSphereTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameLib::Graphics::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  GameLib::Graphics::Texture tolua_var_112 = *((GameLib::Graphics::Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSphereTexture'",NULL);
#endif
  {
   self->setSphereTexture(tolua_var_112);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSphereTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSphereTextureAdditive of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setSphereTextureAdditive00
static int tolua_luafunc_MME_Manager_setSphereTextureAdditive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  bool isAdditive = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSphereTextureAdditive'",NULL);
#endif
  {
   self->setSphereTextureAdditive(isAdditive);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSphereTextureAdditive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewMatrix of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setViewMatrix00
static int tolua_luafunc_MME_Manager_setViewMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const D3DXMATRIX* view = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewMatrix'",NULL);
#endif
  {
   self->setViewMatrix(*view);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setProjectionMatrix of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setProjectionMatrix00
static int tolua_luafunc_MME_Manager_setProjectionMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const D3DXMATRIX* proj = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setProjectionMatrix'",NULL);
#endif
  {
   self->setProjectionMatrix(*proj);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setProjectionMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWorldMatrix of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setWorldMatrix00
static int tolua_luafunc_MME_Manager_setWorldMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const D3DXMATRIX* world = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWorldMatrix'",NULL);
#endif
  {
   self->setWorldMatrix(*world);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWorldMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Manager::getViewMatrix of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_Manager__getViewMatrix00
static int tolua_luafunc_MME_Manager_Manager__getViewMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Manager* self = (const MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Manager::getViewMatrix'",NULL);
#endif
  {
   const D3DXMATRIX& tolua_ret = (const D3DXMATRIX&)  self->Manager::getViewMatrix();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const D3DXMATRIX");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Manager__getViewMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Manager::getProjectionMatrix of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_Manager__getProjectionMatrix00
static int tolua_luafunc_MME_Manager_Manager__getProjectionMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Manager* self = (const MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Manager::getProjectionMatrix'",NULL);
#endif
  {
   const D3DXMATRIX& tolua_ret = (const D3DXMATRIX&)  self->Manager::getProjectionMatrix();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const D3DXMATRIX");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Manager__getProjectionMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Manager::getWorldMatrix of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_Manager__getWorldMatrix00
static int tolua_luafunc_MME_Manager_Manager__getWorldMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Manager* self = (const MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Manager::getWorldMatrix'",NULL);
#endif
  {
   const D3DXMATRIX& tolua_ret = (const D3DXMATRIX&)  self->Manager::getWorldMatrix();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const D3DXMATRIX");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Manager__getWorldMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightViewMatrix of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setLightViewMatrix00
static int tolua_luafunc_MME_Manager_setLightViewMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const D3DXMATRIX* lightView = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightViewMatrix'",NULL);
#endif
  {
   self->setLightViewMatrix(index,*lightView);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightViewMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightProjectionMatrix of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setLightProjectionMatrix00
static int tolua_luafunc_MME_Manager_setLightProjectionMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const D3DXMATRIX* lightProjection = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightProjectionMatrix'",NULL);
#endif
  {
   self->setLightProjectionMatrix(index,*lightProjection);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightProjectionMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightWorldMatrix of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setLightWorldMatrix00
static int tolua_luafunc_MME_Manager_setLightWorldMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const D3DXMATRIX* lightWorld = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightWorldMatrix'",NULL);
#endif
  {
   self->setLightWorldMatrix(index,*lightWorld);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightWorldMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightPosition of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setLightPosition00
static int tolua_luafunc_MME_Manager_setLightPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const GameLib::Math::Vector3* position = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightPosition'",NULL);
#endif
  {
   self->setLightPosition(index,*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightDirection of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setLightDirection00
static int tolua_luafunc_MME_Manager_setLightDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const GameLib::Math::Vector3* dir = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightDirection'",NULL);
#endif
  {
   self->setLightDirection(index,*dir);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightColor of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setLightColor00
static int tolua_luafunc_MME_Manager_setLightColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const GameLib::Math::Vector4* tolua_var_113 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightColor'",NULL);
#endif
  {
   self->setLightColor(index,*tolua_var_113);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightDiffuse of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setLightDiffuse00
static int tolua_luafunc_MME_Manager_setLightDiffuse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const GameLib::Math::Vector4* d = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightDiffuse'",NULL);
#endif
  {
   self->setLightDiffuse(index,*d);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightDiffuse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightAmbient of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setLightAmbient00
static int tolua_luafunc_MME_Manager_setLightAmbient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const GameLib::Math::Vector4* a = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightAmbient'",NULL);
#endif
  {
   self->setLightAmbient(index,*a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightAmbient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLightSpecular of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setLightSpecular00
static int tolua_luafunc_MME_Manager_setLightSpecular00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const GameLib::Math::Vector4* s = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLightSpecular'",NULL);
#endif
  {
   self->setLightSpecular(index,*s);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLightSpecular'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEyePosition of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setEyePosition00
static int tolua_luafunc_MME_Manager_setEyePosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* position = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEyePosition'",NULL);
#endif
  {
   self->setEyePosition(*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEyePosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEyeDirection of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setEyeDirection00
static int tolua_luafunc_MME_Manager_setEyeDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector3* dir = ((const GameLib::Math::Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEyeDirection'",NULL);
#endif
  {
   self->setEyeDirection(*dir);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEyeDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDiffuseColor of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setDiffuseColor00
static int tolua_luafunc_MME_Manager_setDiffuseColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector4* tolua_var_114 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDiffuseColor'",NULL);
#endif
  {
   self->setDiffuseColor(*tolua_var_114);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDiffuseColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpecularColor of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setSpecularColor00
static int tolua_luafunc_MME_Manager_setSpecularColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector4* tolua_var_115 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpecularColor'",NULL);
#endif
  {
   self->setSpecularColor(*tolua_var_115);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpecularColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEmissionColor of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setEmissionColor00
static int tolua_luafunc_MME_Manager_setEmissionColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector4* tolua_var_116 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEmissionColor'",NULL);
#endif
  {
   self->setEmissionColor(*tolua_var_116);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEmissionColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAmbientColor of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setAmbientColor00
static int tolua_luafunc_MME_Manager_setAmbientColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector4* tolua_var_117 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAmbientColor'",NULL);
#endif
  {
   self->setAmbientColor(*tolua_var_117);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAmbientColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEdgeColor of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setEdgeColor00
static int tolua_luafunc_MME_Manager_setEdgeColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector4* tolua_var_118 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEdgeColor'",NULL);
#endif
  {
   self->setEdgeColor(*tolua_var_118);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEdgeColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZNear of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setZNear00
static int tolua_luafunc_MME_Manager_setZNear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_119 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZNear'",NULL);
#endif
  {
   self->setZNear(tolua_var_119);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZNear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZFar of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setZFar00
static int tolua_luafunc_MME_Manager_setZFar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_120 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZFar'",NULL);
#endif
  {
   self->setZFar(tolua_var_120);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZFar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setToonColor of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setToonColor00
static int tolua_luafunc_MME_Manager_setToonColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const GameLib::Math::Vector4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const GameLib::Math::Vector4* tolua_var_121 = ((const GameLib::Math::Vector4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setToonColor'",NULL);
#endif
  {
   self->setToonColor(*tolua_var_121);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setToonColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpecularSharpness of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setSpecularSharpness00
static int tolua_luafunc_MME_Manager_setSpecularSharpness00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_122 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpecularSharpness'",NULL);
#endif
  {
   self->setSpecularSharpness(tolua_var_122);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpecularSharpness'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendWorldMatrixArray of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_sendWorldMatrixArray00
static int tolua_luafunc_MME_Manager_sendWorldMatrixArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const D3DXMATRIX* WorldMatrices = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,2,0));
  int size = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendWorldMatrixArray'",NULL);
#endif
  {
   self->sendWorldMatrixArray(WorldMatrices,size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendWorldMatrixArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: enableVertexBlend of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_enableVertexBlend00
static int tolua_luafunc_MME_Manager_enableVertexBlend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableVertexBlend'",NULL);
#endif
  {
   self->enableVertexBlend(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableVertexBlend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLightDirection of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_getLightDirection00
static int tolua_luafunc_MME_Manager_getLightDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Manager* self = (const MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLightDirection'",NULL);
#endif
  {
   GameLib::Math::Vector3 tolua_ret = (GameLib::Math::Vector3)  self->getLightDirection(index);
   {
#ifdef __cplusplus
    void* tolua_obj = new GameLib::Math::Vector3(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Math::Vector3");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GameLib::Math::Vector3));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GameLib::Math::Vector3");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLightDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendParamsToGameLibGraphicsManager of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_sendParamsToGameLibGraphicsManager00
static int tolua_luafunc_MME_Manager_sendParamsToGameLibGraphicsManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendParamsToGameLibGraphicsManager'",NULL);
#endif
  {
   self->sendParamsToGameLibGraphicsManager();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendParamsToGameLibGraphicsManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canDraw of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_canDraw00
static int tolua_luafunc_MME_Manager_canDraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MME::UseTexture",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"MME::UseSphereMap",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"MME::UseToon",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Manager* self = (const MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  MME::UseTexture useTexture = *((MME::UseTexture*)  tolua_tousertype(tolua_S,2,0));
  MME::UseSphereMap useSphereMap = *((MME::UseSphereMap*)  tolua_tousertype(tolua_S,3,0));
  MME::UseToon useToon = *((MME::UseToon*)  tolua_tousertype(tolua_S,4,0));
  unsigned int materialIndex = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canDraw'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->canDraw(useTexture,useSphereMap,useToon,materialIndex);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentPass of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_getCurrentPass00
static int tolua_luafunc_MME_Manager_getCurrentPass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Manager* self = (const MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentPass'",NULL);
#endif
  {
   MME::MMDPass tolua_ret = (MME::MMDPass)  self->getCurrentPass();
   {
#ifdef __cplusplus
    void* tolua_obj = new MME::MMDPass(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"MME::MMDPass");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MME::MMDPass));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"MME::MMDPass");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentPass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentPass of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_getCurrentPass01
static int tolua_luafunc_MME_Manager_getCurrentPass01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MME::MMDPass",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"MME::UseTexture",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"MME::UseSphereMap",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"MME::UseToon",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"MME::UseSelfShadow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const MME::Manager* self = (const MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  MME::MMDPass* pass = ((MME::MMDPass*)  tolua_tousertype(tolua_S,2,0));
  MME::UseTexture* useTexture = ((MME::UseTexture*)  tolua_tousertype(tolua_S,3,0));
  MME::UseSphereMap* useSphereMap = ((MME::UseSphereMap*)  tolua_tousertype(tolua_S,4,0));
  MME::UseToon* useToon = ((MME::UseToon*)  tolua_tousertype(tolua_S,5,0));
  MME::UseSelfShadow* useSelfShadow = ((MME::UseSelfShadow*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentPass'",NULL);
#endif
  {
   self->getCurrentPass(pass,useTexture,useSphereMap,useToon,useSelfShadow);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_MME_Manager_getCurrentPass00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCurrentEffect of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_setCurrentEffect00
static int tolua_luafunc_MME_Manager_setCurrentEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MME::BaseEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  MME::BaseEffect* effect = ((MME::BaseEffect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCurrentEffect'",NULL);
#endif
  {
   self->setCurrentEffect(effect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCurrentEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendParams of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_sendParams00
static int tolua_luafunc_MME_Manager_sendParams00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MME::BaseEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  MME::BaseEffect* mme = ((MME::BaseEffect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendParams'",NULL);
#endif
  {
   self->sendParams(mme);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendParams'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findStandardEffect of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_findStandardEffect00
static int tolua_luafunc_MME_Manager_findStandardEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const std::string fullFileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findStandardEffect'",NULL);
#endif
  {
   std::shared_ptr<MME::StandardEffect> tolua_ret = (std::shared_ptr<MME::StandardEffect>)  self->findStandardEffect(fullFileName);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<MME::StandardEffect>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MME::StandardEffect>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<MME::StandardEffect>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MME::StandardEffect>");
#endif
   }
   tolua_pushcppstring(tolua_S,(const char*)fullFileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findStandardEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findPostEffect of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_findPostEffect00
static int tolua_luafunc_MME_Manager_findPostEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const std::string fullFileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findPostEffect'",NULL);
#endif
  {
   std::shared_ptr<MME::PostEffect> tolua_ret = (std::shared_ptr<MME::PostEffect>)  self->findPostEffect(fullFileName);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<MME::PostEffect>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MME::PostEffect>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<MME::PostEffect>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MME::PostEffect>");
#endif
   }
   tolua_pushcppstring(tolua_S,(const char*)fullFileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findPostEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findStandardEffect of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_findStandardEffect01
static int tolua_luafunc_MME_Manager_findStandardEffect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
  const std::string fullFileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string offScreenName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string effectFileNameInOffScreen = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findStandardEffect'",NULL);
#endif
  {
   std::shared_ptr<MME::StandardEffect> tolua_ret = (std::shared_ptr<MME::StandardEffect>)  self->findStandardEffect(fullFileName,offScreenName,effectFileNameInOffScreen);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<MME::StandardEffect>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MME::StandardEffect>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<MME::StandardEffect>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MME::StandardEffect>");
#endif
   }
   tolua_pushcppstring(tolua_S,(const char*)fullFileName);
   tolua_pushcppstring(tolua_S,(const char*)offScreenName);
   tolua_pushcppstring(tolua_S,(const char*)effectFileNameInOffScreen);
  }
 }
 return 4;
tolua_lerror:
 return tolua_luafunc_MME_Manager_findStandardEffect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: backup of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_backup00
static int tolua_luafunc_MME_Manager_backup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'backup'",NULL);
#endif
  {
   self->backup();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'backup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: recover of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_recover00
static int tolua_luafunc_MME_Manager_recover00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'recover'",NULL);
#endif
  {
   self->recover();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'recover'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: beginShadow of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_beginShadow00
static int tolua_luafunc_MME_Manager_beginShadow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'beginShadow'",NULL);
#endif
  {
   self->beginShadow();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'beginShadow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: endShadow of class  MME::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Manager_endShadow00
static int tolua_luafunc_MME_Manager_endShadow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Manager* self = (MME::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'endShadow'",NULL);
#endif
  {
   self->endShadow();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'endShadow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MME::Drawer::CutScene::destroy */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_CutScene_destroy00
static int tolua_luafunc_MME_Drawer_CutScene_destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MME::Drawer::CutScene::destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MME::Drawer::CutScene::isReady */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_CutScene_isReady00
static int tolua_luafunc_MME_Drawer_CutScene_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  MME::Drawer::CutScene::isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MME::Drawer::CutScene::draw */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_CutScene_draw00
static int tolua_luafunc_MME_Drawer_CutScene_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MME::Drawer::CutScene::draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MME::Drawer::CutScene::add */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_CutScene_add00
static int tolua_luafunc_MME_Drawer_CutScene_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<MME::Object::ModelKai>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<MME::Object::ModelKai>* tolua_var_123 = ((const std::shared_ptr<MME::Object::ModelKai>*)  tolua_tousertype(tolua_S,1,0));
  {
   MME::Drawer::CutScene::add(*tolua_var_123);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MME::Drawer::CutScene::add */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_CutScene_add01
static int tolua_luafunc_MME_Drawer_CutScene_add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<MME::Object::PointLight>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::shared_ptr<MME::Object::PointLight>* tolua_var_124 = ((const std::shared_ptr<MME::Object::PointLight>*)  tolua_tousertype(tolua_S,1,0));
  {
   MME::Drawer::CutScene::add(*tolua_var_124);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_MME_Drawer_CutScene_add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: MME::Drawer::CutScene::add */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_CutScene_add02
static int tolua_luafunc_MME_Drawer_CutScene_add02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<MME::Object::Accessory>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::shared_ptr<MME::Object::Accessory>* tolua_var_125 = ((const std::shared_ptr<MME::Object::Accessory>*)  tolua_tousertype(tolua_S,1,0));
  {
   MME::Drawer::CutScene::add(*tolua_var_125);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_MME_Drawer_CutScene_add01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: MME::Drawer::CutScene::add */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_CutScene_add03
static int tolua_luafunc_MME_Drawer_CutScene_add03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<GameObject::AccessoryUtils::MME::Model>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::shared_ptr<GameObject::AccessoryUtils::MME::Model>* tolua_var_126 = ((const std::shared_ptr<GameObject::AccessoryUtils::MME::Model>*)  tolua_tousertype(tolua_S,1,0));
  {
   MME::Drawer::CutScene::add(*tolua_var_126);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_MME_Drawer_CutScene_add02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_create00
static int tolua_luafunc_MME_Object_ModelKai_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const std::shared_ptr<MMD::TemplatePMD>",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<MMD::TemplatePMD>* pmd = ((const std::shared_ptr<MMD::TemplatePMD>*)  tolua_tousertype(tolua_S,2,0));
  bool enablePhysics = ((bool)  tolua_toboolean(tolua_S,3,0));
  float heightOffset = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   std::shared_ptr<MME::Object::ModelKai> tolua_ret = (std::shared_ptr<MME::Object::ModelKai>)  MME::Object::ModelKai::create(*pmd,enablePhysics,heightOffset);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<MME::Object::ModelKai>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MME::Object::ModelKai>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<MME::Object::ModelKai>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<MME::Object::ModelKai>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_delete00
static int tolua_luafunc_MME_Object_ModelKai_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_draw00
static int tolua_luafunc_MME_Object_ModelKai_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Object::ModelKai* self = (const MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'",NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScale of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_getScale00
static int tolua_luafunc_MME_Object_ModelKai_getScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Object::ModelKai* self = (const MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScale'",NULL);
#endif
  {
   float tolua_ret = (float)  self->getScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFaceValue of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_getFaceValue00
static int tolua_luafunc_MME_Object_ModelKai_getFaceValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Object::ModelKai* self = (const MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
  const std::string faceName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFaceValue'",NULL);
#endif
  {
   float tolua_ret = (float)  self->getFaceValue(faceName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)faceName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFaceValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBoneMatrix of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_getBoneMatrix00
static int tolua_luafunc_MME_Object_ModelKai_getBoneMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Object::ModelKai* self = (const MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
  const std::string boneName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBoneMatrix'",NULL);
#endif
  {
   const D3DXMATRIX& tolua_ret = (const D3DXMATRIX&)  self->getBoneMatrix(boneName);
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const D3DXMATRIX");
   tolua_pushcppstring(tolua_S,(const char*)boneName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBoneMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getModelFileName of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_getModelFileName00
static int tolua_luafunc_MME_Object_ModelKai_getModelFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Object::ModelKai* self = (const MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getModelFileName'",NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getModelFileName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getModelFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_update00
static int tolua_luafunc_MME_Object_ModelKai_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
  const D3DXMATRIX* world = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,2,0));
  float elapsed = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
  {
   self->update(*world,elapsed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_isReady00
static int tolua_luafunc_MME_Object_ModelKai_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_init00
static int tolua_luafunc_MME_Object_ModelKai_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXMATRIX",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
  const D3DXMATRIX* world = ((const D3DXMATRIX*)  tolua_tousertype(tolua_S,2,0));
  const std::string animName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'",NULL);
#endif
  {
   self->init(*world,animName);
   tolua_pushcppstring(tolua_S,(const char*)animName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isAnimOver of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_isAnimOver00
static int tolua_luafunc_MME_Object_ModelKai_isAnimOver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Object::ModelKai* self = (const MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isAnimOver'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isAnimOver();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isAnimOver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeAnimation of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_changeAnimation00
static int tolua_luafunc_MME_Object_ModelKai_changeAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
  const std::string animName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeAnimation'",NULL);
#endif
  {
   self->changeAnimation(animName);
   tolua_pushcppstring(tolua_S,(const char*)animName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addAnimState of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_addAnimState00
static int tolua_luafunc_MME_Object_ModelKai_addAnimState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const MMD::AnimationState::IAnimationStateSharedPtr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const MMD::AnimationState::IAnimationStateSharedPtr* anim = ((const MMD::AnimationState::IAnimationStateSharedPtr*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addAnimState'",NULL);
#endif
  {
   self->addAnimState(animationName,*anim);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addAnimState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAccessory of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_getAccessory00
static int tolua_luafunc_MME_Object_ModelKai_getAccessory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAccessory'",NULL);
#endif
  {
    std::shared_ptr<GameObject::Accessory> tolua_ret = (  std::shared_ptr<GameObject::Accessory>)  self->getAccessory(name);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<GameObject::Accessory>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Accessory>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<GameObject::Accessory>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Accessory>");
#endif
   }
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAccessory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addAccessory of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_addAccessory00
static int tolua_luafunc_MME_Object_ModelKai_addAccessory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const std::shared_ptr<GameObject::Accessory>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::shared_ptr<GameObject::Accessory>* accessory = ((const std::shared_ptr<GameObject::Accessory>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addAccessory'",NULL);
#endif
  {
   self->addAccessory(name,*accessory);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addAccessory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFrame of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_getFrame00
static int tolua_luafunc_MME_Object_ModelKai_getFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MME::Object::ModelKai* self = (const MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrame'",NULL);
#endif
  {
   float tolua_ret = (float)  self->getFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBone of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_getBone00
static int tolua_luafunc_MME_Object_ModelKai_getBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
  const char* boneName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBone'",NULL);
#endif
  {
   MMD::Bone* tolua_ret = (MMD::Bone*)  self->getBone(boneName);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MMD::Bone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimationModel of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_getAnimationModel00
static int tolua_luafunc_MME_Object_ModelKai_getAnimationModel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimationModel'",NULL);
#endif
  {
   MMD::AnimationModel* tolua_ret = (MMD::AnimationModel*)  self->getAnimationModel();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MMD::AnimationModel");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnimationModel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addToWorld of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_addToWorld00
static int tolua_luafunc_MME_Object_ModelKai_addToWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addToWorld'",NULL);
#endif
  {
   self->addToWorld();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addToWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromWorld of class  MME::Object::ModelKai */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Object_ModelKai_removeFromWorld00
static int tolua_luafunc_MME_Object_ModelKai_removeFromWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Object::ModelKai",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Object::ModelKai* self = (MME::Object::ModelKai*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromWorld'",NULL);
#endif
  {
   self->removeFromWorld();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFromWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  MME::Drawer::GameDrawer */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_GameDrawer_instance00
static int tolua_luafunc_MME_Drawer_GameDrawer_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MME::Drawer::GameDrawer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MME::Drawer::GameDrawer* tolua_ret = (MME::Drawer::GameDrawer*)  MME::Drawer::GameDrawer::instance();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MME::Drawer::GameDrawer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  MME::Drawer::GameDrawer */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_GameDrawer_destroy00
static int tolua_luafunc_MME_Drawer_GameDrawer_destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MME::Drawer::GameDrawer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MME::Drawer::GameDrawer::destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  MME::Drawer::GameDrawer */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_GameDrawer_isReady00
static int tolua_luafunc_MME_Drawer_GameDrawer_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Drawer::GameDrawer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Drawer::GameDrawer* self = (MME::Drawer::GameDrawer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  MME::Drawer::GameDrawer */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_GameDrawer_draw00
static int tolua_luafunc_MME_Drawer_GameDrawer_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Drawer::GameDrawer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Drawer::GameDrawer* self = (MME::Drawer::GameDrawer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'",NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: add of class  MME::Drawer::GameDrawer */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_GameDrawer_add00
static int tolua_luafunc_MME_Drawer_GameDrawer_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Drawer::GameDrawer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const std::shared_ptr<MME::Object::ModelKai>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::Drawer::GameDrawer* self = (MME::Drawer::GameDrawer*)  tolua_tousertype(tolua_S,1,0);
  const std::shared_ptr<MME::Object::ModelKai>* tolua_var_127 = ((const std::shared_ptr<MME::Object::ModelKai>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'add'",NULL);
#endif
  {
   self->add(*tolua_var_127);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: add of class  MME::Drawer::GameDrawer */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_GameDrawer_add01
static int tolua_luafunc_MME_Drawer_GameDrawer_add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Drawer::GameDrawer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const std::shared_ptr<MME::Object::PointLight>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  MME::Drawer::GameDrawer* self = (MME::Drawer::GameDrawer*)  tolua_tousertype(tolua_S,1,0);
  const std::shared_ptr<MME::Object::PointLight>* tolua_var_128 = ((const std::shared_ptr<MME::Object::PointLight>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'add'",NULL);
#endif
  {
   self->add(*tolua_var_128);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_MME_Drawer_GameDrawer_add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: add of class  MME::Drawer::GameDrawer */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_GameDrawer_add02
static int tolua_luafunc_MME_Drawer_GameDrawer_add02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Drawer::GameDrawer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const std::shared_ptr<MME::Object::Accessory>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  MME::Drawer::GameDrawer* self = (MME::Drawer::GameDrawer*)  tolua_tousertype(tolua_S,1,0);
  const std::shared_ptr<MME::Object::Accessory>* tolua_var_129 = ((const std::shared_ptr<MME::Object::Accessory>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'add'",NULL);
#endif
  {
   self->add(*tolua_var_129);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_MME_Drawer_GameDrawer_add01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: add of class  MME::Drawer::GameDrawer */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_Drawer_GameDrawer_add03
static int tolua_luafunc_MME_Drawer_GameDrawer_add03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::Drawer::GameDrawer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const std::shared_ptr<GameObject::AccessoryUtils::MME::Model>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  MME::Drawer::GameDrawer* self = (MME::Drawer::GameDrawer*)  tolua_tousertype(tolua_S,1,0);
  const std::shared_ptr<GameObject::AccessoryUtils::MME::Model>* tolua_var_130 = ((const std::shared_ptr<GameObject::AccessoryUtils::MME::Model>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'add'",NULL);
#endif
  {
   self->add(*tolua_var_130);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_MME_Drawer_GameDrawer_add02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  std::shared_ptr<MME::Object::ModelKai> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__new00
static int tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<MME::Object::ModelKai>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<MME::Object::ModelKai>* tolua_ret = (std::shared_ptr<MME::Object::ModelKai>*)  new std::shared_ptr<MME::Object::ModelKai>();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::shared_ptr<MME::Object::ModelKai>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  std::shared_ptr<MME::Object::ModelKai> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__new00_local
static int tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<MME::Object::ModelKai>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<MME::Object::ModelKai>* tolua_ret = (std::shared_ptr<MME::Object::ModelKai>*)  new std::shared_ptr<MME::Object::ModelKai>();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"std::shared_ptr<MME::Object::ModelKai>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  std::shared_ptr<MME::Object::ModelKai> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__delete00
static int tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<MME::Object::ModelKai>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<MME::Object::ModelKai>* self = (std::shared_ptr<MME::Object::ModelKai>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  std::shared_ptr<MME::Object::ModelKai> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__reset00
static int tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<MME::Object::ModelKai>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<MME::Object::ModelKai>* self = (std::shared_ptr<MME::Object::ModelKai>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
  {
   self->reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  std::shared_ptr<MME::Object::ModelKai> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__get00
static int tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<MME::Object::ModelKai>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<MME::Object::ModelKai>* self = (const std::shared_ptr<MME::Object::ModelKai>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
  {
   MME::Object::ModelKai* tolua_ret = (MME::Object::ModelKai*)  self->get();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MME::Object::ModelKai");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  MME::StandardEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_StandardEffect_new00
static int tolua_luafunc_MME_StandardEffect_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MME::StandardEffect",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"GameLib::FileIO::InFile",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"LPD3DXEFFECTPOOL",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string fxFileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  GameLib::FileIO::InFile file = *((GameLib::FileIO::InFile*)  tolua_tousertype(tolua_S,3,0));
  LPD3DXEFFECTPOOL pool = *((LPD3DXEFFECTPOOL*)  tolua_tousertype(tolua_S,4,0));
  {
   MME::StandardEffect* tolua_ret = (MME::StandardEffect*)  new MME::StandardEffect(fxFileName,file,pool);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MME::StandardEffect");
   tolua_pushcppstring(tolua_S,(const char*)fxFileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  MME::StandardEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_StandardEffect_new00_local
static int tolua_luafunc_MME_StandardEffect_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MME::StandardEffect",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"GameLib::FileIO::InFile",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"LPD3DXEFFECTPOOL",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string fxFileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  GameLib::FileIO::InFile file = *((GameLib::FileIO::InFile*)  tolua_tousertype(tolua_S,3,0));
  LPD3DXEFFECTPOOL pool = *((LPD3DXEFFECTPOOL*)  tolua_tousertype(tolua_S,4,0));
  {
   MME::StandardEffect* tolua_ret = (MME::StandardEffect*)  new MME::StandardEffect(fxFileName,file,pool);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"MME::StandardEffect");
   tolua_pushcppstring(tolua_S,(const char*)fxFileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  MME::StandardEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_StandardEffect_delete00
static int tolua_luafunc_MME_StandardEffect_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::StandardEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::StandardEffect* self = (MME::StandardEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawZPlot of class  MME::StandardEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_StandardEffect_drawZPlot00
static int tolua_luafunc_MME_StandardEffect_drawZPlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::StandardEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::StandardEffect* self = (MME::StandardEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawZPlot'",NULL);
#endif
  {
   self->drawZPlot();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawZPlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawObject of class  MME::StandardEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_StandardEffect_drawObject00
static int tolua_luafunc_MME_StandardEffect_drawObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::StandardEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::StandardEffect* self = (MME::StandardEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawObject'",NULL);
#endif
  {
   self->drawObject();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawObjectSS of class  MME::StandardEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_StandardEffect_drawObjectSS00
static int tolua_luafunc_MME_StandardEffect_drawObjectSS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::StandardEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::StandardEffect* self = (MME::StandardEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawObjectSS'",NULL);
#endif
  {
   self->drawObjectSS();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawObjectSS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawEdge of class  MME::StandardEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_StandardEffect_drawEdge00
static int tolua_luafunc_MME_StandardEffect_drawEdge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::StandardEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::StandardEffect* self = (MME::StandardEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawEdge'",NULL);
#endif
  {
   self->drawEdge();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawEdge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawZPrePass of class  MME::StandardEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_StandardEffect_drawZPrePass00
static int tolua_luafunc_MME_StandardEffect_drawZPrePass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::StandardEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::StandardEffect* self = (MME::StandardEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawZPrePass'",NULL);
#endif
  {
   self->drawZPrePass();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawZPrePass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  std::shared_ptr<MME::StandardEffect> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__StandardEffect__new00
static int tolua_luafunc_std_shared_ptr_MME__StandardEffect__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<MME::StandardEffect>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<MME::StandardEffect>* tolua_ret = (std::shared_ptr<MME::StandardEffect>*)  new std::shared_ptr<MME::StandardEffect>();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::shared_ptr<MME::StandardEffect>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  std::shared_ptr<MME::StandardEffect> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__StandardEffect__new00_local
static int tolua_luafunc_std_shared_ptr_MME__StandardEffect__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<MME::StandardEffect>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<MME::StandardEffect>* tolua_ret = (std::shared_ptr<MME::StandardEffect>*)  new std::shared_ptr<MME::StandardEffect>();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"std::shared_ptr<MME::StandardEffect>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  std::shared_ptr<MME::StandardEffect> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__StandardEffect__delete00
static int tolua_luafunc_std_shared_ptr_MME__StandardEffect__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<MME::StandardEffect>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<MME::StandardEffect>* self = (std::shared_ptr<MME::StandardEffect>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  std::shared_ptr<MME::StandardEffect> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__StandardEffect__reset00
static int tolua_luafunc_std_shared_ptr_MME__StandardEffect__reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<MME::StandardEffect>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<MME::StandardEffect>* self = (std::shared_ptr<MME::StandardEffect>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
  {
   self->reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  std::shared_ptr<MME::StandardEffect> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__StandardEffect__get00
static int tolua_luafunc_std_shared_ptr_MME__StandardEffect__get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<MME::StandardEffect>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<MME::StandardEffect>* self = (const std::shared_ptr<MME::StandardEffect>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
  {
   MME::StandardEffect* tolua_ret = (MME::StandardEffect*)  self->get();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MME::StandardEffect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  MME::PostEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_PostEffect_new00
static int tolua_luafunc_MME_PostEffect_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MME::PostEffect",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"GameLib::FileIO::InFile",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"LPD3DXEFFECTPOOL",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string fxFileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  GameLib::FileIO::InFile file = *((GameLib::FileIO::InFile*)  tolua_tousertype(tolua_S,3,0));
  LPD3DXEFFECTPOOL pool = *((LPD3DXEFFECTPOOL*)  tolua_tousertype(tolua_S,4,0));
  {
   MME::PostEffect* tolua_ret = (MME::PostEffect*)  new MME::PostEffect(fxFileName,file,pool);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MME::PostEffect");
   tolua_pushcppstring(tolua_S,(const char*)fxFileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  MME::PostEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_PostEffect_new00_local
static int tolua_luafunc_MME_PostEffect_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MME::PostEffect",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"GameLib::FileIO::InFile",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"LPD3DXEFFECTPOOL",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string fxFileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  GameLib::FileIO::InFile file = *((GameLib::FileIO::InFile*)  tolua_tousertype(tolua_S,3,0));
  LPD3DXEFFECTPOOL pool = *((LPD3DXEFFECTPOOL*)  tolua_tousertype(tolua_S,4,0));
  {
   MME::PostEffect* tolua_ret = (MME::PostEffect*)  new MME::PostEffect(fxFileName,file,pool);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"MME::PostEffect");
   tolua_pushcppstring(tolua_S,(const char*)fxFileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  MME::PostEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_PostEffect_delete00
static int tolua_luafunc_MME_PostEffect_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::PostEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::PostEffect* self = (MME::PostEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: preDraw of class  MME::PostEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_PostEffect_preDraw00
static int tolua_luafunc_MME_PostEffect_preDraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::PostEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::PostEffect* self = (MME::PostEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'preDraw'",NULL);
#endif
  {
   self->preDraw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'preDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: postDraw of class  MME::PostEffect */
#ifndef TOLUA_DISABLE_tolua_luafunc_MME_PostEffect_postDraw00
static int tolua_luafunc_MME_PostEffect_postDraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MME::PostEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MME::PostEffect* self = (MME::PostEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'postDraw'",NULL);
#endif
  {
   self->postDraw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'postDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  std::shared_ptr<MME::PostEffect> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__PostEffect__new00
static int tolua_luafunc_std_shared_ptr_MME__PostEffect__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<MME::PostEffect>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<MME::PostEffect>* tolua_ret = (std::shared_ptr<MME::PostEffect>*)  new std::shared_ptr<MME::PostEffect>();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::shared_ptr<MME::PostEffect>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  std::shared_ptr<MME::PostEffect> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__PostEffect__new00_local
static int tolua_luafunc_std_shared_ptr_MME__PostEffect__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<MME::PostEffect>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<MME::PostEffect>* tolua_ret = (std::shared_ptr<MME::PostEffect>*)  new std::shared_ptr<MME::PostEffect>();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"std::shared_ptr<MME::PostEffect>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  std::shared_ptr<MME::PostEffect> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__PostEffect__delete00
static int tolua_luafunc_std_shared_ptr_MME__PostEffect__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<MME::PostEffect>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<MME::PostEffect>* self = (std::shared_ptr<MME::PostEffect>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  std::shared_ptr<MME::PostEffect> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__PostEffect__reset00
static int tolua_luafunc_std_shared_ptr_MME__PostEffect__reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<MME::PostEffect>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<MME::PostEffect>* self = (std::shared_ptr<MME::PostEffect>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
  {
   self->reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  std::shared_ptr<MME::PostEffect> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_MME__PostEffect__get00
static int tolua_luafunc_std_shared_ptr_MME__PostEffect__get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<MME::PostEffect>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<MME::PostEffect>* self = (const std::shared_ptr<MME::PostEffect>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
  {
   MME::PostEffect* tolua_ret = (MME::PostEffect*)  self->get();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MME::PostEffect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: D3DXMatrixIdentity */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMatrixIdentity00
static int tolua_luafunc_D3DXMatrixIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  D3DXMATRIX* pOut = ((D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0));
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  D3DXMatrixIdentity(pOut);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXMATRIX");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'D3DXMatrixIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: D3DXMatrixIsIdentity */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMatrixIsIdentity00
static int tolua_luafunc_D3DXMatrixIsIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CONST D3DXMATRIX* pM = ((CONST D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0));
  {
    bool tolua_ret = (  bool)  D3DXMatrixIsIdentity(pM);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'D3DXMatrixIsIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: D3DXMatrixLookAtLH */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMatrixLookAtLH00
static int tolua_luafunc_D3DXMatrixLookAtLH00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  D3DXMATRIX* pOut = ((D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0));
  CONST D3DXVECTOR3* pEye = ((CONST D3DXVECTOR3*)  tolua_tousertype(tolua_S,2,0));
  CONST D3DXVECTOR3* pAt = ((CONST D3DXVECTOR3*)  tolua_tousertype(tolua_S,3,0));
  CONST D3DXVECTOR3* pUp = ((CONST D3DXVECTOR3*)  tolua_tousertype(tolua_S,4,0));
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  D3DXMatrixLookAtLH(pOut,pEye,pAt,pUp);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXMATRIX");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'D3DXMatrixLookAtLH'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: D3DXMatrixPerspectiveFovLH */
#ifndef TOLUA_DISABLE_tolua_luafunc_D3DXMatrixPerspectiveFovLH00
static int tolua_luafunc_D3DXMatrixPerspectiveFovLH00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"D3DXMATRIX",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  D3DXMATRIX* pOut = ((D3DXMATRIX*)  tolua_tousertype(tolua_S,1,0));
   float fovy = ((  float)  tolua_tonumber(tolua_S,2,0));
   float Aspect = ((  float)  tolua_tonumber(tolua_S,3,0));
   float zn = ((  float)  tolua_tonumber(tolua_S,4,0));
   float zf = ((  float)  tolua_tonumber(tolua_S,5,0));
  {
   D3DXMATRIX* tolua_ret = (D3DXMATRIX*)  D3DXMatrixPerspectiveFovLH(pOut,fovy,Aspect,zn,zf);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"D3DXMATRIX");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'D3DXMatrixPerspectiveFovLH'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_instance00
static int tolua_luafunc_BulletPhysics_Manager_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int index = ((int)  tolua_tonumber(tolua_S,2,BulletPhysics::GameWorldIndex));
  {
   BulletPhysics::Manager* tolua_ret = (BulletPhysics::Manager*)  BulletPhysics::Manager::instance(index);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"BulletPhysics::Manager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: release of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_release00
static int tolua_luafunc_BulletPhysics_Manager_release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'release'",NULL);
#endif
  {
   self->release();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addToWorld of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_addToWorld00
static int tolua_luafunc_BulletPhysics_Manager_addToWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btCollisionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
  btCollisionObject* pbtCo = ((btCollisionObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addToWorld'",NULL);
#endif
  {
   self->addToWorld(pbtCo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addToWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addToWorld of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_addToWorld01
static int tolua_luafunc_BulletPhysics_Manager_addToWorld01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btCollisionObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
  btCollisionObject* pbtCo = ((btCollisionObject*)  tolua_tousertype(tolua_S,2,0));
  unsigned short unGroupIdx = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  unsigned short unGroupMask = ((unsigned short)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addToWorld'",NULL);
#endif
  {
   self->addToWorld(pbtCo,unGroupIdx,unGroupMask);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_BulletPhysics_Manager_addToWorld00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addToWorld of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_addToWorld02
static int tolua_luafunc_BulletPhysics_Manager_addToWorld02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btRigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
  btRigidBody* pbtRB = ((btRigidBody*)  tolua_tousertype(tolua_S,2,0));
  unsigned short unGroupIdx = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  unsigned short unGroupMask = ((unsigned short)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addToWorld'",NULL);
#endif
  {
   self->addToWorld(pbtRB,unGroupIdx,unGroupMask);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_BulletPhysics_Manager_addToWorld01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addToWorld of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_addToWorld03
static int tolua_luafunc_BulletPhysics_Manager_addToWorld03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btRigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
  btRigidBody* pbtRB = ((btRigidBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addToWorld'",NULL);
#endif
  {
   self->addToWorld(pbtRB);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_BulletPhysics_Manager_addToWorld02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addToWorld of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_addToWorld04
static int tolua_luafunc_BulletPhysics_Manager_addToWorld04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btTypedConstraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
  btTypedConstraint* pctConstraint = ((btTypedConstraint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addToWorld'",NULL);
#endif
  {
   self->addToWorld(pctConstraint);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_BulletPhysics_Manager_addToWorld03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromWorld of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_removeFromWorld00
static int tolua_luafunc_BulletPhysics_Manager_removeFromWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btCollisionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
  btCollisionObject* pbtCo = ((btCollisionObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromWorld'",NULL);
#endif
  {
   self->removeFromWorld(pbtCo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFromWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromWorld of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_removeFromWorld01
static int tolua_luafunc_BulletPhysics_Manager_removeFromWorld01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btRigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
  btRigidBody* pbtRB = ((btRigidBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromWorld'",NULL);
#endif
  {
   self->removeFromWorld(pbtRB);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_BulletPhysics_Manager_removeFromWorld00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromWorld of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_removeFromWorld02
static int tolua_luafunc_BulletPhysics_Manager_removeFromWorld02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btTypedConstraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
  btTypedConstraint* pctConstraint = ((btTypedConstraint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromWorld'",NULL);
#endif
  {
   self->removeFromWorld(pctConstraint);
  }
 }
 return 0;
tolua_lerror:
 return tolua_luafunc_BulletPhysics_Manager_removeFromWorld01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_update00
static int tolua_luafunc_BulletPhysics_Manager_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
  float fElapsedTime = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
  {
   self->update(fElapsedTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawWorld of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_drawWorld00
static int tolua_luafunc_BulletPhysics_Manager_drawWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawWorld'",NULL);
#endif
  {
   self->drawWorld();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawObject of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_drawObject00
static int tolua_luafunc_BulletPhysics_Manager_drawObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const btCollisionObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const btCollisionObject* pObj = ((const btCollisionObject*)  tolua_tousertype(tolua_S,2,0));
  unsigned int color = ((unsigned int)  tolua_tonumber(tolua_S,3,0xff000000));
  {
   BulletPhysics::Manager::drawObject(pObj,color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawConstraint of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_drawConstraint00
static int tolua_luafunc_BulletPhysics_Manager_drawConstraint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"btTypedConstraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
  btTypedConstraint* pConstraint = ((btTypedConstraint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawConstraint'",NULL);
#endif
  {
   self->drawConstraint(pConstraint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawConstraint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearForces of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_clearForces00
static int tolua_luafunc_BulletPhysics_Manager_clearForces00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearForces'",NULL);
#endif
  {
   self->clearForces();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearForces'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldPtr of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_getWorldPtr00
static int tolua_luafunc_BulletPhysics_Manager_getWorldPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldPtr'",NULL);
#endif
  {
   btDiscreteDynamicsWorld* tolua_ret = (btDiscreteDynamicsWorld*)  self->getWorldPtr();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btDiscreteDynamicsWorld");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWorldPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDebugDrawerPtr of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_getDebugDrawerPtr00
static int tolua_luafunc_BulletPhysics_Manager_getDebugDrawerPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDebugDrawerPtr'",NULL);
#endif
  {
   btIDebugDraw* tolua_ret = (btIDebugDraw*)  self->getDebugDrawerPtr();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btIDebugDraw");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDebugDrawerPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkAllContactPoints of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_checkAllContactPoints00
static int tolua_luafunc_BulletPhysics_Manager_checkAllContactPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BulletPhysics::Manager* self = (BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkAllContactPoints'",NULL);
#endif
  {
   self->checkAllContactPoints();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkAllContactPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumberCollisionObjects of class  BulletPhysics::Manager */
#ifndef TOLUA_DISABLE_tolua_luafunc_BulletPhysics_Manager_getNumberCollisionObjects00
static int tolua_luafunc_BulletPhysics_Manager_getNumberCollisionObjects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BulletPhysics::Manager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BulletPhysics::Manager* self = (const BulletPhysics::Manager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumberCollisionObjects'",NULL);
#endif
  {
   int tolua_ret = (int)  self->getNumberCollisionObjects();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumberCollisionObjects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_instance00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Sequence::HatuneOfTheDead::LuaImpl::Resource* tolua_ret = (Sequence::HatuneOfTheDead::LuaImpl::Resource*)  Sequence::HatuneOfTheDead::LuaImpl::Resource::instance();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sequence::HatuneOfTheDead::LuaImpl::Resource");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: release of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_release00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::Resource* self = (Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'release'",NULL);
#endif
  {
   self->release();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_isReady00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::Resource* self = (Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadEnemy of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadEnemy00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::Resource* self = (Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadEnemy'",NULL);
#endif
  {
   self->loadEnemy(filename);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadEnemy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadPlayer of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadPlayer00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::Resource* self = (Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadPlayer'",NULL);
#endif
  {
   self->loadPlayer(filename);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadCameraAnimation of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadCameraAnimation00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadCameraAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::Resource* self = (Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadCameraAnimation'",NULL);
#endif
  {
   self->loadCameraAnimation(filename);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadCameraAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadStage of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadStage00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadStage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::Resource* self = (Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadStage'",NULL);
#endif
  {
   self->loadStage(filename);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadStage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instancePlayer of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_instancePlayer00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_instancePlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sequence::HatuneOfTheDead::LuaImpl::Resource* self = (const Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'instancePlayer'",NULL);
#endif
  {
    std::shared_ptr<GameObject::Player> tolua_ret = (  std::shared_ptr<GameObject::Player>)  self->instancePlayer();
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<GameObject::Player>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Player>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<GameObject::Player>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Player>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instancePlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStage of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_getStage00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_getStage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sequence::HatuneOfTheDead::LuaImpl::Resource* self = (const Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStage'",NULL);
#endif
  {
    std::shared_ptr<GameObject::Stage> tolua_ret = (  std::shared_ptr<GameObject::Stage>)  self->getStage();
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<GameObject::Stage>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Stage>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<GameObject::Stage>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Stage>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEnemies of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_getEnemies00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_getEnemies00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::Resource* self = (Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEnemies'",NULL);
#endif
  {
   const std::vector<XmlLoader::GameObject::EnemySharedPtr>& tolua_ret = (const std::vector<XmlLoader::GameObject::EnemySharedPtr>&)  self->getEnemies();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const std::vector<XmlLoader::GameObject::EnemySharedPtr>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEnemies'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCameraAnimation of class  Sequence::HatuneOfTheDead::LuaImpl::Resource */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_getCameraAnimation00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_getCameraAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::Resource* self = (Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCameraAnimation'",NULL);
#endif
  {
   const std::shared_ptr<MMD::CameraAnimation>& tolua_ret = (const std::shared_ptr<MMD::CameraAnimation>&)  self->getCameraAnimation();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const std::shared_ptr<MMD::CameraAnimation>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCameraAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_instance00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Sequence::HatuneOfTheDead::LuaImpl::State* tolua_ret = (Sequence::HatuneOfTheDead::LuaImpl::State*)  Sequence::HatuneOfTheDead::LuaImpl::State::instance();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sequence::HatuneOfTheDead::LuaImpl::State");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: release of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_release00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'release'",NULL);
#endif
  {
   self->release();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_isReady00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isClear of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_isClear00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_isClear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sequence::HatuneOfTheDead::LuaImpl::State* self = (const Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isClear'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isClear();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isClear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_update00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
  {
   self->update();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_draw00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'",NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reserveEnemySpawn of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_reserveEnemySpawn00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_reserveEnemySpawn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
  const std::string enemyName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  float spawnTime = ((float)  tolua_tonumber(tolua_S,3,0));
  const btTransform* trans = ((const btTransform*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reserveEnemySpawn'",NULL);
#endif
  {
   self->reserveEnemySpawn(enemyName,spawnTime,*trans);
   tolua_pushcppstring(tolua_S,(const char*)enemyName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reserveEnemySpawn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: build of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_build00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_build00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Sequence::HatuneOfTheDead::LuaImpl::Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
  Sequence::HatuneOfTheDead::LuaImpl::Resource* tolua_var_146 = ((Sequence::HatuneOfTheDead::LuaImpl::Resource*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'build'",NULL);
#endif
  {
   self->build(tolua_var_146);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'build'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlayer of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_getPlayer00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_getPlayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlayer'",NULL);
#endif
  {
   GameObject::Player* tolua_ret = (GameObject::Player*)  self->getPlayer();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameObject::Player");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNextSequence of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_setNextSequence00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_setNextSequence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Sequence::Base",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
  Sequence::Base* next = ((Sequence::Base*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNextSequence'",NULL);
#endif
  {
   self->setNextSequence(next);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNextSequence'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNextSequence of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_getNextSequence00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_getNextSequence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNextSequence'",NULL);
#endif
  {
   Sequence::Base* tolua_ret = (Sequence::Base*)  self->getNextSequence();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sequence::Base");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNextSequence'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: needDrawCall of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_needDrawCall00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_needDrawCall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sequence::HatuneOfTheDead::LuaImpl::State* self = (const Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'needDrawCall'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->needDrawCall();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'needDrawCall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNeedDrawCall of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_setNeedDrawCall00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_setNeedDrawCall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNeedDrawCall'",NULL);
#endif
  {
   self->setNeedDrawCall(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNeedDrawCall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetAll of class  Sequence::HatuneOfTheDead::LuaImpl::State */
#ifndef TOLUA_DISABLE_tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_resetAll00
static int tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_resetAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sequence::HatuneOfTheDead::LuaImpl::State",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sequence::HatuneOfTheDead::LuaImpl::State* self = (Sequence::HatuneOfTheDead::LuaImpl::State*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetAll'",NULL);
#endif
  {
   self->resetAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  HOD::EnemySpawner */
#ifndef TOLUA_DISABLE_tolua_luafunc_HOD_EnemySpawner_new00
static int tolua_luafunc_HOD_EnemySpawner_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HOD::EnemySpawner",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   HOD::EnemySpawner* tolua_ret = (HOD::EnemySpawner*)  new HOD::EnemySpawner();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"HOD::EnemySpawner");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  HOD::EnemySpawner */
#ifndef TOLUA_DISABLE_tolua_luafunc_HOD_EnemySpawner_new00_local
static int tolua_luafunc_HOD_EnemySpawner_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HOD::EnemySpawner",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   HOD::EnemySpawner* tolua_ret = (HOD::EnemySpawner*)  new HOD::EnemySpawner();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"HOD::EnemySpawner");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  HOD::EnemySpawner */
#ifndef TOLUA_DISABLE_tolua_luafunc_HOD_EnemySpawner_delete00
static int tolua_luafunc_HOD_EnemySpawner_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HOD::EnemySpawner",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HOD::EnemySpawner* self = (HOD::EnemySpawner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  HOD::EnemySpawner */
#ifndef TOLUA_DISABLE_tolua_luafunc_HOD_EnemySpawner_update00
static int tolua_luafunc_HOD_EnemySpawner_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HOD::EnemySpawner",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HOD::EnemySpawner* self = (HOD::EnemySpawner*)  tolua_tousertype(tolua_S,1,0);
  float elapsedTime = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
  {
   self->update(elapsedTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadEnemy of class  HOD::EnemySpawner */
#ifndef TOLUA_DISABLE_tolua_luafunc_HOD_EnemySpawner_loadEnemy00
static int tolua_luafunc_HOD_EnemySpawner_loadEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HOD::EnemySpawner",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HOD::EnemySpawner* self = (HOD::EnemySpawner*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadEnemy'",NULL);
#endif
  {
   self->loadEnemy(filename);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadEnemy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  HOD::EnemySpawner */
#ifndef TOLUA_DISABLE_tolua_luafunc_HOD_EnemySpawner_isReady00
static int tolua_luafunc_HOD_EnemySpawner_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HOD::EnemySpawner",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HOD::EnemySpawner* self = (HOD::EnemySpawner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reserve of class  HOD::EnemySpawner */
#ifndef TOLUA_DISABLE_tolua_luafunc_HOD_EnemySpawner_reserve00
static int tolua_luafunc_HOD_EnemySpawner_reserve00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HOD::EnemySpawner",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const btTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HOD::EnemySpawner* self = (HOD::EnemySpawner*)  tolua_tousertype(tolua_S,1,0);
  const std::string enemyName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  float spawnTime = ((float)  tolua_tonumber(tolua_S,3,0));
  const btTransform* trans = ((const btTransform*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reserve'",NULL);
#endif
  {
   self->reserve(enemyName,spawnTime,*trans);
   tolua_pushcppstring(tolua_S,(const char*)enemyName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reserve'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerEnemy of class  HOD::EnemySpawner */
#ifndef TOLUA_DISABLE_tolua_luafunc_HOD_EnemySpawner_registerEnemy00
static int tolua_luafunc_HOD_EnemySpawner_registerEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HOD::EnemySpawner",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"std::shared_ptr<XmlLoader::GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HOD::EnemySpawner* self = (HOD::EnemySpawner*)  tolua_tousertype(tolua_S,1,0);
   std::shared_ptr<XmlLoader::GameObject::Enemy> enemy = *((  std::shared_ptr<XmlLoader::GameObject::Enemy>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerEnemy'",NULL);
#endif
  {
   self->registerEnemy(enemy);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerEnemy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_create00
static int tolua_luafunc_GameObject_Stage_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameObject::Stage",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* xmlInitStageFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   std::shared_ptr<GameObject::Stage> tolua_ret = (std::shared_ptr<GameObject::Stage>)  GameObject::Stage::create(xmlInitStageFile);
   {
#ifdef __cplusplus
    void* tolua_obj = new std::shared_ptr<GameObject::Stage>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Stage>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::shared_ptr<GameObject::Stage>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::shared_ptr<GameObject::Stage>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_delete00
static int tolua_luafunc_GameObject_Stage_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Stage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Stage* self = (GameObject::Stage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawUsingGameLib of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_drawUsingGameLib00
static int tolua_luafunc_GameObject_Stage_drawUsingGameLib00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Stage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Stage* self = (GameObject::Stage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawUsingGameLib'",NULL);
#endif
  {
   self->drawUsingGameLib();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawUsingGameLib'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createBvhTriangleMesh of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_createBvhTriangleMesh00
static int tolua_luafunc_GameObject_Stage_createBvhTriangleMesh00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Stage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Stage* self = (GameObject::Stage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createBvhTriangleMesh'",NULL);
#endif
  {
   self->createBvhTriangleMesh();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createBvhTriangleMesh'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRTTI of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_getRTTI00
static int tolua_luafunc_GameObject_Stage_getRTTI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Stage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Stage* self = (const GameObject::Stage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRTTI'",NULL);
#endif
  {
   const RTTI& tolua_ret = (const RTTI&)  self->getRTTI();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const RTTI");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRTTI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rtti of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_get_GameObject__Stage_rtti
static int tolua_get_GameObject__Stage_rtti(lua_State* tolua_S)
{
  tolua_pushusertype(tolua_S,(void*)&GameObject::Stage::rtti,"const RTTI");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBtCollisionObject of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_getBtCollisionObject00
static int tolua_luafunc_GameObject_Stage_getBtCollisionObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Stage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Stage* self = (GameObject::Stage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBtCollisionObject'",NULL);
#endif
  {
   btCollisionObject* tolua_ret = (btCollisionObject*)  self->getBtCollisionObject();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"btCollisionObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBtCollisionObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromWorld of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_removeFromWorld00
static int tolua_luafunc_GameObject_Stage_removeFromWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Stage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Stage* self = (GameObject::Stage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromWorld'",NULL);
#endif
  {
   self->removeFromWorld();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFromWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addToWorld of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_addToWorld00
static int tolua_luafunc_GameObject_Stage_addToWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Stage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Stage* self = (GameObject::Stage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addToWorld'",NULL);
#endif
  {
   self->addToWorld();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addToWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isClear of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_isClear00
static int tolua_luafunc_GameObject_Stage_isClear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GameObject::Stage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GameObject::Stage* self = (const GameObject::Stage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isClear'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isClear();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isClear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: handleEventThatDefeatedAllEnemies of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_handleEventThatDefeatedAllEnemies00
static int tolua_luafunc_GameObject_Stage_handleEventThatDefeatedAllEnemies00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Stage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Stage* self = (GameObject::Stage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'handleEventThatDefeatedAllEnemies'",NULL);
#endif
  {
   self->handleEventThatDefeatedAllEnemies();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'handleEventThatDefeatedAllEnemies'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isReady of class  GameObject::Stage */
#ifndef TOLUA_DISABLE_tolua_luafunc_GameObject_Stage_isReady00
static int tolua_luafunc_GameObject_Stage_isReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameObject::Stage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameObject::Stage* self = (GameObject::Stage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isReady'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isReady();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  std::shared_ptr<GameObject::Player> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Player__new00
static int tolua_luafunc_std_shared_ptr_GameObject__Player__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<GameObject::Player>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<GameObject::Player>* tolua_ret = (std::shared_ptr<GameObject::Player>*)  new std::shared_ptr<GameObject::Player>();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::shared_ptr<GameObject::Player>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  std::shared_ptr<GameObject::Player> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Player__new00_local
static int tolua_luafunc_std_shared_ptr_GameObject__Player__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<GameObject::Player>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<GameObject::Player>* tolua_ret = (std::shared_ptr<GameObject::Player>*)  new std::shared_ptr<GameObject::Player>();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"std::shared_ptr<GameObject::Player>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  std::shared_ptr<GameObject::Player> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Player__delete00
static int tolua_luafunc_std_shared_ptr_GameObject__Player__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<GameObject::Player>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<GameObject::Player>* self = (std::shared_ptr<GameObject::Player>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  std::shared_ptr<GameObject::Player> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Player__reset00
static int tolua_luafunc_std_shared_ptr_GameObject__Player__reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<GameObject::Player>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameObject::Player",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<GameObject::Player>* self = (std::shared_ptr<GameObject::Player>*)  tolua_tousertype(tolua_S,1,0);
  GameObject::Player* tolua_var_147 = ((GameObject::Player*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
  {
   self->reset(tolua_var_147);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  std::shared_ptr<GameObject::Player> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Player__get00
static int tolua_luafunc_std_shared_ptr_GameObject__Player__get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<GameObject::Player>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<GameObject::Player>* self = (const std::shared_ptr<GameObject::Player>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
  {
   GameObject::Player* tolua_ret = (GameObject::Player*)  self->get();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameObject::Player");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  std::shared_ptr<GameObject::Enemy> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Enemy__new00
static int tolua_luafunc_std_shared_ptr_GameObject__Enemy__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<GameObject::Enemy>* tolua_ret = (std::shared_ptr<GameObject::Enemy>*)  new std::shared_ptr<GameObject::Enemy>();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::shared_ptr<GameObject::Enemy>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  std::shared_ptr<GameObject::Enemy> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Enemy__new00_local
static int tolua_luafunc_std_shared_ptr_GameObject__Enemy__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<GameObject::Enemy>* tolua_ret = (std::shared_ptr<GameObject::Enemy>*)  new std::shared_ptr<GameObject::Enemy>();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"std::shared_ptr<GameObject::Enemy>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  std::shared_ptr<GameObject::Enemy> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Enemy__delete00
static int tolua_luafunc_std_shared_ptr_GameObject__Enemy__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<GameObject::Enemy>* self = (std::shared_ptr<GameObject::Enemy>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  std::shared_ptr<GameObject::Enemy> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Enemy__reset00
static int tolua_luafunc_std_shared_ptr_GameObject__Enemy__reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameObject::Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<GameObject::Enemy>* self = (std::shared_ptr<GameObject::Enemy>*)  tolua_tousertype(tolua_S,1,0);
  GameObject::Enemy* tolua_var_149 = ((GameObject::Enemy*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
  {
   self->reset(tolua_var_149);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  std::shared_ptr<GameObject::Enemy> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Enemy__get00
static int tolua_luafunc_std_shared_ptr_GameObject__Enemy__get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<GameObject::Enemy>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<GameObject::Enemy>* self = (const std::shared_ptr<GameObject::Enemy>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
  {
   GameObject::Enemy* tolua_ret = (GameObject::Enemy*)  self->get();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameObject::Enemy");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  std::shared_ptr<GameObject::Stage> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Stage__new00
static int tolua_luafunc_std_shared_ptr_GameObject__Stage__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<GameObject::Stage>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<GameObject::Stage>* tolua_ret = (std::shared_ptr<GameObject::Stage>*)  new std::shared_ptr<GameObject::Stage>();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::shared_ptr<GameObject::Stage>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  std::shared_ptr<GameObject::Stage> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Stage__new00_local
static int tolua_luafunc_std_shared_ptr_GameObject__Stage__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::shared_ptr<GameObject::Stage>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::shared_ptr<GameObject::Stage>* tolua_ret = (std::shared_ptr<GameObject::Stage>*)  new std::shared_ptr<GameObject::Stage>();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"std::shared_ptr<GameObject::Stage>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  std::shared_ptr<GameObject::Stage> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Stage__delete00
static int tolua_luafunc_std_shared_ptr_GameObject__Stage__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<GameObject::Stage>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<GameObject::Stage>* self = (std::shared_ptr<GameObject::Stage>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  std::shared_ptr<GameObject::Stage> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Stage__reset00
static int tolua_luafunc_std_shared_ptr_GameObject__Stage__reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::shared_ptr<GameObject::Stage>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::shared_ptr<GameObject::Stage>* self = (std::shared_ptr<GameObject::Stage>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
  {
   self->reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  std::shared_ptr<GameObject::Stage> */
#ifndef TOLUA_DISABLE_tolua_luafunc_std_shared_ptr_GameObject__Stage__get00
static int tolua_luafunc_std_shared_ptr_GameObject__Stage__get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::shared_ptr<GameObject::Stage>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::shared_ptr<GameObject::Stage>* self = (const std::shared_ptr<GameObject::Stage>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
  {
   GameObject::Stage* tolua_ret = (GameObject::Stage*)  self->get();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameObject::Stage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Camera::FixedCamera */
#ifndef TOLUA_DISABLE_tolua_luafunc_Camera_FixedCamera_new00
static int tolua_luafunc_Camera_FixedCamera_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Camera::FixedCamera",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXVECTOR3* pos = ((const D3DXVECTOR3*)  tolua_tousertype(tolua_S,2,0));
  const D3DXVECTOR3* lookAt = ((const D3DXVECTOR3*)  tolua_tousertype(tolua_S,3,0));
  const D3DXVECTOR3* up = ((const D3DXVECTOR3*)  tolua_tousertype(tolua_S,4,0));
  float viewAngleInDegree = ((float)  tolua_tonumber(tolua_S,5,0));
  float zNear = ((float)  tolua_tonumber(tolua_S,6,0));
  float zFar = ((float)  tolua_tonumber(tolua_S,7,0));
  {
   Camera::FixedCamera* tolua_ret = (Camera::FixedCamera*)  new Camera::FixedCamera(*pos,*lookAt,*up,viewAngleInDegree,zNear,zFar);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Camera::FixedCamera");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Camera::FixedCamera */
#ifndef TOLUA_DISABLE_tolua_luafunc_Camera_FixedCamera_new00_local
static int tolua_luafunc_Camera_FixedCamera_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Camera::FixedCamera",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const D3DXVECTOR3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const D3DXVECTOR3* pos = ((const D3DXVECTOR3*)  tolua_tousertype(tolua_S,2,0));
  const D3DXVECTOR3* lookAt = ((const D3DXVECTOR3*)  tolua_tousertype(tolua_S,3,0));
  const D3DXVECTOR3* up = ((const D3DXVECTOR3*)  tolua_tousertype(tolua_S,4,0));
  float viewAngleInDegree = ((float)  tolua_tonumber(tolua_S,5,0));
  float zNear = ((float)  tolua_tonumber(tolua_S,6,0));
  float zFar = ((float)  tolua_tonumber(tolua_S,7,0));
  {
   Camera::FixedCamera* tolua_ret = (Camera::FixedCamera*)  new Camera::FixedCamera(*pos,*lookAt,*up,viewAngleInDegree,zNear,zFar);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Camera::FixedCamera");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Camera::FixedCamera */
#ifndef TOLUA_DISABLE_tolua_luafunc_Camera_FixedCamera_delete00
static int tolua_luafunc_Camera_FixedCamera_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera::FixedCamera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera::FixedCamera* self = (Camera::FixedCamera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  Camera::FixedCamera */
#ifndef TOLUA_DISABLE_tolua_luafunc_Camera_FixedCamera_update00
static int tolua_luafunc_Camera_FixedCamera_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera::FixedCamera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera::FixedCamera* self = (Camera::FixedCamera*)  tolua_tousertype(tolua_S,1,0);
  float elapsedTime = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'",NULL);
#endif
  {
   self->update(elapsedTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_luafunc_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"cfunc",0);
  tolua_beginmodule(tolua_S,"cfunc");
   tolua_function(tolua_S,"ReloadLuaFiles",tolua_luafunc_cfunc_ReloadLuaFiles00);
   tolua_function(tolua_S,"DoLuaFile",tolua_luafunc_cfunc_DoLuaFile00);
   tolua_function(tolua_S,"WaitInputOnError",tolua_luafunc_cfunc_WaitInputOnError00);
   tolua_function(tolua_S,"GetLuaError",tolua_luafunc_cfunc_GetLuaError00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GUI",0);
  tolua_beginmodule(tolua_S,"GUI");
   tolua_cclass(tolua_S,"IComponent","GUI::IComponent","",NULL);
   tolua_beginmodule(tolua_S,"IComponent");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Manager","GUI::Manager","",NULL);
   tolua_beginmodule(tolua_S,"Manager");
    tolua_function(tolua_S,"instance",tolua_luafunc_GUI_Manager_instance00);
    tolua_function(tolua_S,"destory",tolua_luafunc_GUI_Manager_destory00);
    tolua_function(tolua_S,"draw",tolua_luafunc_GUI_Manager_draw00);
    tolua_function(tolua_S,"add",tolua_luafunc_GUI_Manager_add00);
    tolua_function(tolua_S,"remove",tolua_luafunc_GUI_Manager_remove00);
    tolua_function(tolua_S,"isReady",tolua_luafunc_GUI_Manager_isReady00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"BaseComponent","GUI::BaseComponent","GUI::IComponent",NULL);
   tolua_beginmodule(tolua_S,"BaseComponent");
    tolua_function(tolua_S,"isEnabled",tolua_luafunc_GUI_BaseComponent_isEnabled00);
    tolua_function(tolua_S,"setIsEnabled",tolua_luafunc_GUI_BaseComponent_setIsEnabled00);
    tolua_function(tolua_S,"isDrawAble",tolua_luafunc_GUI_BaseComponent_isDrawAble00);
    tolua_function(tolua_S,"setIsDrawAble",tolua_luafunc_GUI_BaseComponent_setIsDrawAble00);
    tolua_function(tolua_S,"setPos",tolua_luafunc_GUI_BaseComponent_setPos00);
    tolua_function(tolua_S,"getPos",tolua_luafunc_GUI_BaseComponent_getPos00);
    tolua_function(tolua_S,"setSize",tolua_luafunc_GUI_BaseComponent_setSize00);
    tolua_function(tolua_S,"getSize",tolua_luafunc_GUI_BaseComponent_getSize00);
    tolua_function(tolua_S,"isHover",tolua_luafunc_GUI_BaseComponent_isHover00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"ComponentWithRender","GUI::ComponentWithRender","GUI::BaseComponent",NULL);
   tolua_beginmodule(tolua_S,"ComponentWithRender");
    tolua_function(tolua_S,"setFontColor",tolua_luafunc_GUI_ComponentWithRender_setFontColor00);
    tolua_function(tolua_S,"setColor",tolua_luafunc_GUI_ComponentWithRender_setColor00);
    tolua_function(tolua_S,"setIsEnableDepthTest",tolua_luafunc_GUI_ComponentWithRender_setIsEnableDepthTest00);
    tolua_function(tolua_S,"setIsEnableDepthWrite",tolua_luafunc_GUI_ComponentWithRender_setIsEnableDepthWrite00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"ImageButton","GUI::ImageButton","GUI::ComponentWithRender",tolua_collect_GUI__ImageButton);
   #else
   tolua_cclass(tolua_S,"ImageButton","GUI::ImageButton","GUI::ComponentWithRender",NULL);
   #endif
   tolua_beginmodule(tolua_S,"ImageButton");
    tolua_function(tolua_S,"new",tolua_luafunc_GUI_ImageButton_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_GUI_ImageButton_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_GUI_ImageButton_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_GUI_ImageButton_delete00);
    tolua_function(tolua_S,"isPushed",tolua_luafunc_GUI_ImageButton_isPushed00);
    tolua_function(tolua_S,"isHover",tolua_luafunc_GUI_ImageButton_isHover00);
    tolua_function(tolua_S,"isPushing",tolua_luafunc_GUI_ImageButton_isPushing00);
    tolua_function(tolua_S,"update",tolua_luafunc_GUI_ImageButton_update00);
    tolua_function(tolua_S,"draw",tolua_luafunc_GUI_ImageButton_draw00);
    tolua_function(tolua_S,"setText",tolua_luafunc_GUI_ImageButton_setText00);
    tolua_function(tolua_S,"setTexture",tolua_luafunc_GUI_ImageButton_setTexture00);
    tolua_function(tolua_S,"setUV",tolua_luafunc_GUI_ImageButton_setUV00);
    tolua_function(tolua_S,"isEnabled",tolua_luafunc_GUI_ImageButton_isEnabled00);
    tolua_function(tolua_S,"setIsEnabled",tolua_luafunc_GUI_ImageButton_setIsEnabled00);
    tolua_function(tolua_S,"isDrawAble",tolua_luafunc_GUI_ImageButton_isDrawAble00);
    tolua_function(tolua_S,"setIsDrawAble",tolua_luafunc_GUI_ImageButton_setIsDrawAble00);
    tolua_function(tolua_S,"setPos",tolua_luafunc_GUI_ImageButton_setPos00);
    tolua_function(tolua_S,"getPos",tolua_luafunc_GUI_ImageButton_getPos00);
    tolua_function(tolua_S,"setSize",tolua_luafunc_GUI_ImageButton_setSize00);
    tolua_function(tolua_S,"getSize",tolua_luafunc_GUI_ImageButton_getSize00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Label","GUI::Label","GUI::ComponentWithRender",tolua_collect_GUI__Label);
   #else
   tolua_cclass(tolua_S,"Label","GUI::Label","GUI::ComponentWithRender",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Label");
    tolua_function(tolua_S,"new",tolua_luafunc_GUI_Label_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_GUI_Label_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_GUI_Label_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_GUI_Label_delete00);
    tolua_function(tolua_S,"setText",tolua_luafunc_GUI_Label_setText00);
    tolua_function(tolua_S,"setUV",tolua_luafunc_GUI_Label_setUV00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Telop",0);
  tolua_beginmodule(tolua_S,"Telop");
   tolua_function(tolua_S,"insert",tolua_luafunc_Telop_insert00);
   tolua_function(tolua_S,"setFont",tolua_luafunc_Telop_setFont00);
   tolua_function(tolua_S,"setDefalutDuration",tolua_luafunc_Telop_setDefalutDuration00);
   tolua_function(tolua_S,"setDefalutFontColor",tolua_luafunc_Telop_setDefalutFontColor00);
   tolua_function(tolua_S,"parse",tolua_luafunc_Telop_parse00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GUI",0);
  tolua_beginmodule(tolua_S,"GUI");
   tolua_cclass(tolua_S,"IModalDialog","GUI::IModalDialog","GUI::IComponent",NULL);
   tolua_beginmodule(tolua_S,"IModalDialog");
    tolua_function(tolua_S,"show",tolua_luafunc_GUI_IModalDialog_show00);
    tolua_function(tolua_S,"hide",tolua_luafunc_GUI_IModalDialog_hide00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GUI",0);
  tolua_beginmodule(tolua_S,"GUI");
   tolua_cclass(tolua_S,"Window","GUI::Window","",NULL);
   tolua_beginmodule(tolua_S,"Window");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Button","GUI::Button","",NULL);
   tolua_beginmodule(tolua_S,"Button");
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"OkDialog","GUI::OkDialog","GUI::IModalDialog",tolua_collect_GUI__OkDialog);
   #else
   tolua_cclass(tolua_S,"OkDialog","GUI::OkDialog","GUI::IModalDialog",NULL);
   #endif
   tolua_beginmodule(tolua_S,"OkDialog");
    tolua_function(tolua_S,"new",tolua_luafunc_GUI_OkDialog_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_GUI_OkDialog_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_GUI_OkDialog_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_GUI_OkDialog_delete00);
    tolua_function(tolua_S,"update",tolua_luafunc_GUI_OkDialog_update00);
    tolua_function(tolua_S,"draw",tolua_luafunc_GUI_OkDialog_draw00);
    tolua_function(tolua_S,"isEnabled",tolua_luafunc_GUI_OkDialog_isEnabled00);
    tolua_function(tolua_S,"setIsEnabled",tolua_luafunc_GUI_OkDialog_setIsEnabled00);
    tolua_function(tolua_S,"isDrawAble",tolua_luafunc_GUI_OkDialog_isDrawAble00);
    tolua_function(tolua_S,"setIsDrawAble",tolua_luafunc_GUI_OkDialog_setIsDrawAble00);
    tolua_function(tolua_S,"setText",tolua_luafunc_GUI_OkDialog_setText00);
    tolua_function(tolua_S,"isOk",tolua_luafunc_GUI_OkDialog_isOk00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"btTransform","btTransform","",tolua_collect_btTransform);
  #else
  tolua_cclass(tolua_S,"btTransform","btTransform","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"btTransform");
   tolua_function(tolua_S,"new",tolua_luafunc_btTransform_new00);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btTransform_new00_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btTransform_new00_local);
   tolua_function(tolua_S,"new",tolua_luafunc_btTransform_new01);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btTransform_new01_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btTransform_new01_local);
   tolua_function(tolua_S,"new",tolua_luafunc_btTransform_new02);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btTransform_new02_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btTransform_new02_local);
   tolua_function(tolua_S,"new",tolua_luafunc_btTransform_new03);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btTransform_new03_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btTransform_new03_local);
   tolua_function(tolua_S,"new",tolua_luafunc_btTransform_new04);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btTransform_new04_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btTransform_new04_local);
   tolua_function(tolua_S,"new",tolua_luafunc_btTransform_new05);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btTransform_new05_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btTransform_new05_local);
   tolua_function(tolua_S,"delete",tolua_luafunc_btTransform_delete00);
   tolua_function(tolua_S,"mult",tolua_luafunc_btTransform_mult00);
   tolua_function(tolua_S,".mul",tolua_luafunc_btTransform__mul00);
   tolua_function(tolua_S,".mul",tolua_luafunc_btTransform__mul01);
   tolua_function(tolua_S,"getBasis",tolua_luafunc_btTransform_getBasis00);
   tolua_function(tolua_S,"getOrigin",tolua_luafunc_btTransform_getOrigin00);
   tolua_function(tolua_S,"getRotation",tolua_luafunc_btTransform_getRotation00);
   tolua_function(tolua_S,"setFromOpenGLMatrix",tolua_luafunc_btTransform_setFromOpenGLMatrix00);
   tolua_function(tolua_S,"getOpenGLMatrix",tolua_luafunc_btTransform_getOpenGLMatrix00);
   tolua_function(tolua_S,"setOrigin",tolua_luafunc_btTransform_setOrigin00);
   tolua_function(tolua_S,"invXform",tolua_luafunc_btTransform_invXform00);
   tolua_function(tolua_S,"setBasis",tolua_luafunc_btTransform_setBasis00);
   tolua_function(tolua_S,"setRotation",tolua_luafunc_btTransform_setRotation00);
   tolua_function(tolua_S,"setIdentity",tolua_luafunc_btTransform_setIdentity00);
   tolua_function(tolua_S,"inverse",tolua_luafunc_btTransform_inverse00);
   tolua_function(tolua_S,"inverseTimes",tolua_luafunc_btTransform_inverseTimes00);
   tolua_function(tolua_S,".mul",tolua_luafunc_btTransform__mul02);
   tolua_function(tolua_S,"getIdentity",tolua_luafunc_btTransform_getIdentity00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"btVector3","btVector3","",tolua_collect_btVector3);
  #else
  tolua_cclass(tolua_S,"btVector3","btVector3","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"btVector3");
   tolua_function(tolua_S,"new",tolua_luafunc_btVector3_new00);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btVector3_new00_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btVector3_new00_local);
   tolua_function(tolua_S,"new",tolua_luafunc_btVector3_new01);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btVector3_new01_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btVector3_new01_local);
   tolua_function(tolua_S,"new",tolua_luafunc_btVector3_new02);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btVector3_new02_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btVector3_new02_local);
   tolua_function(tolua_S,"delete",tolua_luafunc_btVector3_delete00);
   tolua_function(tolua_S,"dot",tolua_luafunc_btVector3_dot00);
   tolua_function(tolua_S,"length2",tolua_luafunc_btVector3_length200);
   tolua_function(tolua_S,"length",tolua_luafunc_btVector3_length00);
   tolua_function(tolua_S,"norm",tolua_luafunc_btVector3_norm00);
   tolua_function(tolua_S,"safeNorm",tolua_luafunc_btVector3_safeNorm00);
   tolua_function(tolua_S,"distance2",tolua_luafunc_btVector3_distance200);
   tolua_function(tolua_S,"distance",tolua_luafunc_btVector3_distance00);
   tolua_function(tolua_S,"safeNormalize",tolua_luafunc_btVector3_safeNormalize00);
   tolua_function(tolua_S,"normalize",tolua_luafunc_btVector3_normalize00);
   tolua_function(tolua_S,"normalized",tolua_luafunc_btVector3_normalized00);
   tolua_function(tolua_S,"rotate",tolua_luafunc_btVector3_rotate00);
   tolua_function(tolua_S,"angle",tolua_luafunc_btVector3_angle00);
   tolua_function(tolua_S,"absolute",tolua_luafunc_btVector3_absolute00);
   tolua_function(tolua_S,"cross",tolua_luafunc_btVector3_cross00);
   tolua_function(tolua_S,"triple",tolua_luafunc_btVector3_triple00);
   tolua_function(tolua_S,"minAxis",tolua_luafunc_btVector3_minAxis00);
   tolua_function(tolua_S,"maxAxis",tolua_luafunc_btVector3_maxAxis00);
   tolua_function(tolua_S,"furthestAxis",tolua_luafunc_btVector3_furthestAxis00);
   tolua_function(tolua_S,"closestAxis",tolua_luafunc_btVector3_closestAxis00);
   tolua_function(tolua_S,"setInterpolate3",tolua_luafunc_btVector3_setInterpolate300);
   tolua_function(tolua_S,"lerp",tolua_luafunc_btVector3_lerp00);
   tolua_function(tolua_S,"getX",tolua_luafunc_btVector3_getX00);
   tolua_function(tolua_S,"getY",tolua_luafunc_btVector3_getY00);
   tolua_function(tolua_S,"getZ",tolua_luafunc_btVector3_getZ00);
   tolua_function(tolua_S,"setX",tolua_luafunc_btVector3_setX00);
   tolua_function(tolua_S,"setY",tolua_luafunc_btVector3_setY00);
   tolua_function(tolua_S,"setZ",tolua_luafunc_btVector3_setZ00);
   tolua_function(tolua_S,"setW",tolua_luafunc_btVector3_setW00);
   tolua_function(tolua_S,"x",tolua_luafunc_btVector3_x00);
   tolua_function(tolua_S,"y",tolua_luafunc_btVector3_y00);
   tolua_function(tolua_S,"z",tolua_luafunc_btVector3_z00);
   tolua_function(tolua_S,"w",tolua_luafunc_btVector3_w00);
   tolua_function(tolua_S,".eq",tolua_luafunc_btVector3__eq00);
   tolua_function(tolua_S,"setMax",tolua_luafunc_btVector3_setMax00);
   tolua_function(tolua_S,"setMin",tolua_luafunc_btVector3_setMin00);
   tolua_function(tolua_S,"setValue",tolua_luafunc_btVector3_setValue00);
   tolua_function(tolua_S,"getSkewSymmetricMatrix",tolua_luafunc_btVector3_getSkewSymmetricMatrix00);
   tolua_function(tolua_S,"setZero",tolua_luafunc_btVector3_setZero00);
   tolua_function(tolua_S,"isZero",tolua_luafunc_btVector3_isZero00);
   tolua_function(tolua_S,"fuzzyZero",tolua_luafunc_btVector3_fuzzyZero00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"btMatrix3x3","btMatrix3x3","",tolua_collect_btMatrix3x3);
  #else
  tolua_cclass(tolua_S,"btMatrix3x3","btMatrix3x3","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"btMatrix3x3");
   tolua_function(tolua_S,"new",tolua_luafunc_btMatrix3x3_new00);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btMatrix3x3_new00_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btMatrix3x3_new00_local);
   tolua_function(tolua_S,"new",tolua_luafunc_btMatrix3x3_new01);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btMatrix3x3_new01_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btMatrix3x3_new01_local);
   tolua_function(tolua_S,"new",tolua_luafunc_btMatrix3x3_new02);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btMatrix3x3_new02_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btMatrix3x3_new02_local);
   tolua_function(tolua_S,"new",tolua_luafunc_btMatrix3x3_new03);
   tolua_function(tolua_S,"new_local",tolua_luafunc_btMatrix3x3_new03_local);
   tolua_function(tolua_S,".call",tolua_luafunc_btMatrix3x3_new03_local);
   tolua_function(tolua_S,"getColumn",tolua_luafunc_btMatrix3x3_getColumn00);
   tolua_function(tolua_S,"getRow",tolua_luafunc_btMatrix3x3_getRow00);
   tolua_function(tolua_S,".seti",tolua_luafunc_btMatrix3x3__seti00);
   tolua_function(tolua_S,".geti",tolua_luafunc_btMatrix3x3__geti00);
   tolua_function(tolua_S,".geti",tolua_luafunc_btMatrix3x3__geti01);
   tolua_function(tolua_S,"setFromOpenGLSubMatrix",tolua_luafunc_btMatrix3x3_setFromOpenGLSubMatrix00);
   tolua_function(tolua_S,"setValue",tolua_luafunc_btMatrix3x3_setValue00);
   tolua_function(tolua_S,"setRotation",tolua_luafunc_btMatrix3x3_setRotation00);
   tolua_function(tolua_S,"setEulerYPR",tolua_luafunc_btMatrix3x3_setEulerYPR00);
   tolua_function(tolua_S,"setEulerZYX",tolua_luafunc_btMatrix3x3_setEulerZYX00);
   tolua_function(tolua_S,"setIdentity",tolua_luafunc_btMatrix3x3_setIdentity00);
   tolua_function(tolua_S,"getIdentity",tolua_luafunc_btMatrix3x3_getIdentity00);
   tolua_function(tolua_S,"getOpenGLSubMatrix",tolua_luafunc_btMatrix3x3_getOpenGLSubMatrix00);
   tolua_function(tolua_S,"getRotation",tolua_luafunc_btMatrix3x3_getRotation00);
   tolua_function(tolua_S,"getEulerYPR",tolua_luafunc_btMatrix3x3_getEulerYPR00);
   tolua_function(tolua_S,"getEulerZYX",tolua_luafunc_btMatrix3x3_getEulerZYX00);
   tolua_function(tolua_S,"scaled",tolua_luafunc_btMatrix3x3_scaled00);
   tolua_function(tolua_S,"transposeTimes",tolua_luafunc_btMatrix3x3_transposeTimes00);
   tolua_function(tolua_S,"timesTranspose",tolua_luafunc_btMatrix3x3_timesTranspose00);
   tolua_function(tolua_S,"tdotx",tolua_luafunc_btMatrix3x3_tdotx00);
   tolua_function(tolua_S,"tdoty",tolua_luafunc_btMatrix3x3_tdoty00);
   tolua_function(tolua_S,"tdotz",tolua_luafunc_btMatrix3x3_tdotz00);
   tolua_function(tolua_S,"diagonalize",tolua_luafunc_btMatrix3x3_diagonalize00);
   tolua_function(tolua_S,"cofac",tolua_luafunc_btMatrix3x3_cofac00);
   tolua_function(tolua_S,"serialize",tolua_luafunc_btMatrix3x3_serialize00);
   tolua_function(tolua_S,"serializeFloat",tolua_luafunc_btMatrix3x3_serializeFloat00);
   tolua_function(tolua_S,"deSerialize",tolua_luafunc_btMatrix3x3_deSerialize00);
   tolua_function(tolua_S,"deSerializeFloat",tolua_luafunc_btMatrix3x3_deSerializeFloat00);
   tolua_function(tolua_S,"deSerializeDouble",tolua_luafunc_btMatrix3x3_deSerializeDouble00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MMD",0);
  tolua_beginmodule(tolua_S,"MMD");
   tolua_cclass(tolua_S,"MMDDataBase","MMD::MMDDataBase","",NULL);
   tolua_beginmodule(tolua_S,"MMDDataBase");
    tolua_function(tolua_S,"instance",tolua_luafunc_MMD_MMDDataBase_instance00);
    tolua_function(tolua_S,"destroy",tolua_luafunc_MMD_MMDDataBase_destroy00);
    tolua_function(tolua_S,"loadPMD",tolua_luafunc_MMD_MMDDataBase_loadPMD00);
    tolua_function(tolua_S,"loadVMD",tolua_luafunc_MMD_MMDDataBase_loadVMD00);
    tolua_function(tolua_S,"isReady",tolua_luafunc_MMD_MMDDataBase_isReady00);
    tolua_function(tolua_S,"createAnimationVMD",tolua_luafunc_MMD_MMDDataBase_createAnimationVMD00);
    tolua_function(tolua_S,"getCameraAnimation",tolua_luafunc_MMD_MMDDataBase_getCameraAnimation00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MMD",0);
  tolua_beginmodule(tolua_S,"MMD");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"TemplateVMD","MMD::TemplateVMD","",tolua_collect_MMD__TemplateVMD);
   #else
   tolua_cclass(tolua_S,"TemplateVMD","MMD::TemplateVMD","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"TemplateVMD");
    tolua_function(tolua_S,"new",tolua_luafunc_MMD_TemplateVMD_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_MMD_TemplateVMD_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_MMD_TemplateVMD_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_MMD_TemplateVMD_delete00);
    tolua_function(tolua_S,"create",tolua_luafunc_MMD_TemplateVMD_create00);
    tolua_function(tolua_S,"createBoneKeyArray",tolua_luafunc_MMD_TemplateVMD_createBoneKeyArray00);
    tolua_function(tolua_S,"createFaceKeyArray",tolua_luafunc_MMD_TemplateVMD_createFaceKeyArray00);
    tolua_function(tolua_S,"getFileName",tolua_luafunc_MMD_TemplateVMD_getFileName00);
    tolua_function(tolua_S,"isReady",tolua_luafunc_MMD_TemplateVMD_isReady00);
    tolua_function(tolua_S,"getCameraAnimation",tolua_luafunc_MMD_TemplateVMD_getCameraAnimation00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Bone","MMD::Bone","",NULL);
   tolua_beginmodule(tolua_S,"Bone");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Face","MMD::Face","",NULL);
   tolua_beginmodule(tolua_S,"Face");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"TemplateBoneKey","MMD::TemplateBoneKey","",NULL);
   tolua_beginmodule(tolua_S,"TemplateBoneKey");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"TemplateFaceKey","MMD::TemplateFaceKey","",NULL);
   tolua_beginmodule(tolua_S,"TemplateFaceKey");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"BoneKey","MMD::BoneKey","",NULL);
   tolua_beginmodule(tolua_S,"BoneKey");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"FaceKey","MMD::FaceKey","",NULL);
   tolua_beginmodule(tolua_S,"FaceKey");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Animation","MMD::Animation","",NULL);
   tolua_beginmodule(tolua_S,"Animation");
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CameraAnimation","MMD::CameraAnimation","",tolua_collect_MMD__CameraAnimation);
   #else
   tolua_cclass(tolua_S,"CameraAnimation","MMD::CameraAnimation","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CameraAnimation");
    tolua_function(tolua_S,"new",tolua_luafunc_MMD_CameraAnimation_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_MMD_CameraAnimation_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_MMD_CameraAnimation_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_MMD_CameraAnimation_delete00);
    tolua_function(tolua_S,"insert",tolua_luafunc_MMD_CameraAnimation_insert00);
    tolua_function(tolua_S,"reserve",tolua_luafunc_MMD_CameraAnimation_reserve00);
    tolua_function(tolua_S,"shrink_to_fit",tolua_luafunc_MMD_CameraAnimation_shrink_to_fit00);
    tolua_function(tolua_S,"load",tolua_luafunc_MMD_CameraAnimation_load00);
    tolua_function(tolua_S,"isOver",tolua_luafunc_MMD_CameraAnimation_isOver00);
    tolua_function(tolua_S,"isReady",tolua_luafunc_MMD_CameraAnimation_isReady00);
    tolua_function(tolua_S,"calc",tolua_luafunc_MMD_CameraAnimation_calc00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"std",0);
  tolua_beginmodule(tolua_S,"std");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"shared_ptr_MMD__TemplateVMD_","std::shared_ptr<MMD::TemplateVMD>","",tolua_collect_std__shared_ptr_MMD__TemplateVMD_);
   #else
   tolua_cclass(tolua_S,"shared_ptr_MMD__TemplateVMD_","std::shared_ptr<MMD::TemplateVMD>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"shared_ptr_MMD__TemplateVMD_");
    tolua_function(tolua_S,"new",tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__delete00);
    tolua_function(tolua_S,"reset",tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__reset00);
    tolua_function(tolua_S,"get",tolua_luafunc_std_shared_ptr_MMD__TemplateVMD__get00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"D3DXMATRIX","D3DXMATRIX","D3DMATRIX",tolua_collect_D3DXMATRIX);
  #else
  tolua_cclass(tolua_S,"D3DXMATRIX","D3DXMATRIX","D3DMATRIX",NULL);
  #endif
  tolua_beginmodule(tolua_S,"D3DXMATRIX");
   tolua_function(tolua_S,"new",tolua_luafunc_D3DXMATRIX_new00);
   tolua_function(tolua_S,"new_local",tolua_luafunc_D3DXMATRIX_new00_local);
   tolua_function(tolua_S,".call",tolua_luafunc_D3DXMATRIX_new00_local);
   tolua_function(tolua_S,"new",tolua_luafunc_D3DXMATRIX_new01);
   tolua_function(tolua_S,"new_local",tolua_luafunc_D3DXMATRIX_new01_local);
   tolua_function(tolua_S,".call",tolua_luafunc_D3DXMATRIX_new01_local);
   tolua_function(tolua_S,"new",tolua_luafunc_D3DXMATRIX_new02);
   tolua_function(tolua_S,"new_local",tolua_luafunc_D3DXMATRIX_new02_local);
   tolua_function(tolua_S,".call",tolua_luafunc_D3DXMATRIX_new02_local);
   tolua_function(tolua_S,"new",tolua_luafunc_D3DXMATRIX_new03);
   tolua_function(tolua_S,"new_local",tolua_luafunc_D3DXMATRIX_new03_local);
   tolua_function(tolua_S,".call",tolua_luafunc_D3DXMATRIX_new03_local);
   tolua_function(tolua_S,".FLOAT*",tolua_luafunc_D3DXMATRIX__FLOAT_00);
   tolua_function(tolua_S,".const FLOAT*",tolua_luafunc_D3DXMATRIX__const_FLOAT_00);
   tolua_function(tolua_S,".add",tolua_luafunc_D3DXMATRIX__add00);
   tolua_function(tolua_S,".sub",tolua_luafunc_D3DXMATRIX__sub00);
   tolua_function(tolua_S,".mul",tolua_luafunc_D3DXMATRIX__mul00);
   tolua_function(tolua_S,".add",tolua_luafunc_D3DXMATRIX__add01);
   tolua_function(tolua_S,".sub",tolua_luafunc_D3DXMATRIX__sub01);
   tolua_function(tolua_S,".mul",tolua_luafunc_D3DXMATRIX__mul01);
   tolua_function(tolua_S,".div",tolua_luafunc_D3DXMATRIX__div00);
   tolua_function(tolua_S,".eq",tolua_luafunc_D3DXMATRIX__eq00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"D3DXVECTOR3","D3DXVECTOR3","D3DVECTOR",tolua_collect_D3DXVECTOR3);
  #else
  tolua_cclass(tolua_S,"D3DXVECTOR3","D3DXVECTOR3","D3DVECTOR",NULL);
  #endif
  tolua_beginmodule(tolua_S,"D3DXVECTOR3");
   tolua_function(tolua_S,"new",tolua_luafunc_D3DXVECTOR3_new00);
   tolua_function(tolua_S,"new_local",tolua_luafunc_D3DXVECTOR3_new00_local);
   tolua_function(tolua_S,".call",tolua_luafunc_D3DXVECTOR3_new00_local);
   tolua_function(tolua_S,"new",tolua_luafunc_D3DXVECTOR3_new01);
   tolua_function(tolua_S,"new_local",tolua_luafunc_D3DXVECTOR3_new01_local);
   tolua_function(tolua_S,".call",tolua_luafunc_D3DXVECTOR3_new01_local);
   tolua_function(tolua_S,"new",tolua_luafunc_D3DXVECTOR3_new02);
   tolua_function(tolua_S,"new_local",tolua_luafunc_D3DXVECTOR3_new02_local);
   tolua_function(tolua_S,".call",tolua_luafunc_D3DXVECTOR3_new02_local);
   tolua_function(tolua_S,"new",tolua_luafunc_D3DXVECTOR3_new03);
   tolua_function(tolua_S,"new_local",tolua_luafunc_D3DXVECTOR3_new03_local);
   tolua_function(tolua_S,".call",tolua_luafunc_D3DXVECTOR3_new03_local);
   tolua_function(tolua_S,".FLOAT*",tolua_luafunc_D3DXVECTOR3__FLOAT_00);
   tolua_function(tolua_S,".CONST FLOAT*",tolua_luafunc_D3DXVECTOR3__CONST_FLOAT_00);
   tolua_function(tolua_S,".add",tolua_luafunc_D3DXVECTOR3__add00);
   tolua_function(tolua_S,".sub",tolua_luafunc_D3DXVECTOR3__sub00);
   tolua_function(tolua_S,".add",tolua_luafunc_D3DXVECTOR3__add01);
   tolua_function(tolua_S,".sub",tolua_luafunc_D3DXVECTOR3__sub01);
   tolua_function(tolua_S,".mul",tolua_luafunc_D3DXVECTOR3__mul00);
   tolua_function(tolua_S,".div",tolua_luafunc_D3DXVECTOR3__div00);
   tolua_function(tolua_S,".eq",tolua_luafunc_D3DXVECTOR3__eq00);
   tolua_variable(tolua_S,"x",tolua_get_D3DXVECTOR3_x,tolua_set_D3DXVECTOR3_x);
   tolua_variable(tolua_S,"y",tolua_get_D3DXVECTOR3_y,tolua_set_D3DXVECTOR3_y);
   tolua_variable(tolua_S,"z",tolua_get_D3DXVECTOR3_z,tolua_set_D3DXVECTOR3_z);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MMD",0);
  tolua_beginmodule(tolua_S,"MMD");
   tolua_cclass(tolua_S,"CameraOneFrameData","MMD::CameraOneFrameData","",NULL);
   tolua_beginmodule(tolua_S,"CameraOneFrameData");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"std",0);
  tolua_beginmodule(tolua_S,"std");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"shared_ptr_MMD__CameraAnimation_","std::shared_ptr<MMD::CameraAnimation>","",tolua_collect_std__shared_ptr_MMD__CameraAnimation_);
   #else
   tolua_cclass(tolua_S,"shared_ptr_MMD__CameraAnimation_","std::shared_ptr<MMD::CameraAnimation>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"shared_ptr_MMD__CameraAnimation_");
    tolua_function(tolua_S,"new",tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__delete00);
    tolua_function(tolua_S,"reset",tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__reset00);
    tolua_function(tolua_S,"get",tolua_luafunc_std_shared_ptr_MMD__CameraAnimation__get00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"Graphics",0);
   tolua_beginmodule(tolua_S,"Graphics");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Texture","GameLib::Graphics::Texture","",tolua_collect_GameLib__Graphics__Texture);
    #else
    tolua_cclass(tolua_S,"Texture","GameLib::Graphics::Texture","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Texture");
     tolua_function(tolua_S,"create",tolua_luafunc_GameLib_Graphics_Texture_create00);
     tolua_function(tolua_S,"create",tolua_luafunc_GameLib_Graphics_Texture_create01);
     tolua_function(tolua_S,"create",tolua_luafunc_GameLib_Graphics_Texture_create02);
     tolua_function(tolua_S,"create",tolua_luafunc_GameLib_Graphics_Texture_create03);
     tolua_function(tolua_S,"name",tolua_luafunc_GameLib_Graphics_Texture_name00);
     tolua_function(tolua_S,"isReady",tolua_luafunc_GameLib_Graphics_Texture_isReady00);
     tolua_function(tolua_S,"isError",tolua_luafunc_GameLib_Graphics_Texture_isError00);
     tolua_function(tolua_S,"width",tolua_luafunc_GameLib_Graphics_Texture_width00);
     tolua_function(tolua_S,"height",tolua_luafunc_GameLib_Graphics_Texture_height00);
     tolua_function(tolua_S,"originalWidth",tolua_luafunc_GameLib_Graphics_Texture_originalWidth00);
     tolua_function(tolua_S,"originalHeight",tolua_luafunc_GameLib_Graphics_Texture_originalHeight00);
     tolua_function(tolua_S,"mipmapNumber",tolua_luafunc_GameLib_Graphics_Texture_mipmapNumber00);
     tolua_function(tolua_S,"write",tolua_luafunc_GameLib_Graphics_Texture_write00);
     tolua_function(tolua_S,"dxTeture",tolua_luafunc_GameLib_Graphics_Texture_dxTeture00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"Math",0);
   tolua_beginmodule(tolua_S,"Math");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Vector3","GameLib::Math::Vector3","",tolua_collect_GameLib__Math__Vector3);
    #else
    tolua_cclass(tolua_S,"Vector3","GameLib::Math::Vector3","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Vector3");
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector3_new00);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector3_new00_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector3_new00_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector3_new01);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector3_new01_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector3_new01_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector3_new02);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector3_new02_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector3_new02_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector3_new03);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector3_new03_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector3_new03_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector3_new04);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector3_new04_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector3_new04_local);
     tolua_function(tolua_S,"set",tolua_luafunc_GameLib_Math_Vector3_set00);
     tolua_function(tolua_S,".seti",tolua_luafunc_GameLib_Math_Vector3__seti00);
     tolua_function(tolua_S,".geti",tolua_luafunc_GameLib_Math_Vector3__geti00);
     tolua_function(tolua_S,".geti",tolua_luafunc_GameLib_Math_Vector3__geti01);
     tolua_function(tolua_S,"setAdd",tolua_luafunc_GameLib_Math_Vector3_setAdd00);
     tolua_function(tolua_S,"setAdd",tolua_luafunc_GameLib_Math_Vector3_setAdd01);
     tolua_function(tolua_S,"setSub",tolua_luafunc_GameLib_Math_Vector3_setSub00);
     tolua_function(tolua_S,"setSub",tolua_luafunc_GameLib_Math_Vector3_setSub01);
     tolua_function(tolua_S,"setMul",tolua_luafunc_GameLib_Math_Vector3_setMul00);
     tolua_function(tolua_S,"setMul",tolua_luafunc_GameLib_Math_Vector3_setMul01);
     tolua_function(tolua_S,"setNeg",tolua_luafunc_GameLib_Math_Vector3_setNeg00);
     tolua_function(tolua_S,"setMadd",tolua_luafunc_GameLib_Math_Vector3_setMadd00);
     tolua_function(tolua_S,"setMsub",tolua_luafunc_GameLib_Math_Vector3_setMsub00);
     tolua_function(tolua_S,"madd",tolua_luafunc_GameLib_Math_Vector3_madd00);
     tolua_function(tolua_S,"msub",tolua_luafunc_GameLib_Math_Vector3_msub00);
     tolua_function(tolua_S,"dot",tolua_luafunc_GameLib_Math_Vector3_dot00);
     tolua_function(tolua_S,"setCross",tolua_luafunc_GameLib_Math_Vector3_setCross00);
     tolua_function(tolua_S,"normalize",tolua_luafunc_GameLib_Math_Vector3_normalize00);
     tolua_function(tolua_S,"length",tolua_luafunc_GameLib_Math_Vector3_length00);
     tolua_function(tolua_S,"squareLength",tolua_luafunc_GameLib_Math_Vector3_squareLength00);
     tolua_function(tolua_S,"min",tolua_luafunc_GameLib_Math_Vector3_min00);
     tolua_function(tolua_S,"max",tolua_luafunc_GameLib_Math_Vector3_max00);
     tolua_function(tolua_S,"min",tolua_luafunc_GameLib_Math_Vector3_min01);
     tolua_function(tolua_S,"max",tolua_luafunc_GameLib_Math_Vector3_max01);
     tolua_variable(tolua_S,"x",tolua_get_GameLib__Math__Vector3_x,tolua_set_GameLib__Math__Vector3_x);
     tolua_variable(tolua_S,"y",tolua_get_GameLib__Math__Vector3_y,tolua_set_GameLib__Math__Vector3_y);
     tolua_variable(tolua_S,"z",tolua_get_GameLib__Math__Vector3_z,tolua_set_GameLib__Math__Vector3_z);
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"Vector2","GameLib::Math::Vector2","",NULL);
    tolua_beginmodule(tolua_S,"Vector2");
    tolua_endmodule(tolua_S);
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Matrix44","GameLib::Math::Matrix44","",tolua_collect_GameLib__Math__Matrix44);
    #else
    tolua_cclass(tolua_S,"Matrix44","GameLib::Math::Matrix44","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Matrix44");
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Matrix44_new00);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Matrix44_new00_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Matrix44_new00_local);
     tolua_function(tolua_S,"setIdentity",tolua_luafunc_GameLib_Math_Matrix44_setIdentity00);
     tolua_function(tolua_S,"setPerspectiveTransform",tolua_luafunc_GameLib_Math_Matrix44_setPerspectiveTransform00);
     tolua_function(tolua_S,"setOrthogonalTransform",tolua_luafunc_GameLib_Math_Matrix44_setOrthogonalTransform00);
     tolua_function(tolua_S,"multiplyViewTransform",tolua_luafunc_GameLib_Math_Matrix44_multiplyViewTransform00);
     tolua_function(tolua_S,"mul",tolua_luafunc_GameLib_Math_Matrix44_mul00);
     tolua_function(tolua_S,"setMul",tolua_luafunc_GameLib_Math_Matrix44_setMul00);
     tolua_function(tolua_S,".eq",tolua_luafunc_GameLib_Math_Matrix44__eq00);
     tolua_variable(tolua_S,"m00",tolua_get_GameLib__Math__Matrix44_m00,tolua_set_GameLib__Math__Matrix44_m00);
     tolua_variable(tolua_S,"m01",tolua_get_GameLib__Math__Matrix44_m01,tolua_set_GameLib__Math__Matrix44_m01);
     tolua_variable(tolua_S,"m02",tolua_get_GameLib__Math__Matrix44_m02,tolua_set_GameLib__Math__Matrix44_m02);
     tolua_variable(tolua_S,"m03",tolua_get_GameLib__Math__Matrix44_m03,tolua_set_GameLib__Math__Matrix44_m03);
     tolua_variable(tolua_S,"m10",tolua_get_GameLib__Math__Matrix44_m10,tolua_set_GameLib__Math__Matrix44_m10);
     tolua_variable(tolua_S,"m11",tolua_get_GameLib__Math__Matrix44_m11,tolua_set_GameLib__Math__Matrix44_m11);
     tolua_variable(tolua_S,"m12",tolua_get_GameLib__Math__Matrix44_m12,tolua_set_GameLib__Math__Matrix44_m12);
     tolua_variable(tolua_S,"m13",tolua_get_GameLib__Math__Matrix44_m13,tolua_set_GameLib__Math__Matrix44_m13);
     tolua_variable(tolua_S,"m20",tolua_get_GameLib__Math__Matrix44_m20,tolua_set_GameLib__Math__Matrix44_m20);
     tolua_variable(tolua_S,"m21",tolua_get_GameLib__Math__Matrix44_m21,tolua_set_GameLib__Math__Matrix44_m21);
     tolua_variable(tolua_S,"m22",tolua_get_GameLib__Math__Matrix44_m22,tolua_set_GameLib__Math__Matrix44_m22);
     tolua_variable(tolua_S,"m23",tolua_get_GameLib__Math__Matrix44_m23,tolua_set_GameLib__Math__Matrix44_m23);
     tolua_variable(tolua_S,"m30",tolua_get_GameLib__Math__Matrix44_m30,tolua_set_GameLib__Math__Matrix44_m30);
     tolua_variable(tolua_S,"m31",tolua_get_GameLib__Math__Matrix44_m31,tolua_set_GameLib__Math__Matrix44_m31);
     tolua_variable(tolua_S,"m32",tolua_get_GameLib__Math__Matrix44_m32,tolua_set_GameLib__Math__Matrix44_m32);
     tolua_variable(tolua_S,"m33",tolua_get_GameLib__Math__Matrix44_m33,tolua_set_GameLib__Math__Matrix44_m33);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Framework","GameLib::Framework","",tolua_collect_GameLib__Framework);
   #else
   tolua_cclass(tolua_S,"Framework","GameLib::Framework","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Framework");
    tolua_constant(tolua_S,"LOAD_ARCHIVE_FIRST",GameLib::Framework::LOAD_ARCHIVE_FIRST);
    tolua_constant(tolua_S,"LOAD_DIRECT_FIRST",GameLib::Framework::LOAD_DIRECT_FIRST);
    tolua_constant(tolua_S,"LOAD_ARCHIVE_ONLY",GameLib::Framework::LOAD_ARCHIVE_ONLY);
    tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Framework_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Framework_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Framework_new00_local);
    tolua_function(tolua_S,"instance",tolua_luafunc_GameLib_Framework_instance00);
    tolua_function(tolua_S,"configure",tolua_luafunc_GameLib_Framework_configure00);
    tolua_function(tolua_S,"update",tolua_luafunc_GameLib_Framework_update00);
    tolua_function(tolua_S,"enableFullScreen",tolua_luafunc_GameLib_Framework_enableFullScreen00);
    tolua_function(tolua_S,"width",tolua_luafunc_GameLib_Framework_width00);
    tolua_function(tolua_S,"height",tolua_luafunc_GameLib_Framework_height00);
    tolua_function(tolua_S,"title",tolua_luafunc_GameLib_Framework_title00);
    tolua_function(tolua_S,"isFullScreen",tolua_luafunc_GameLib_Framework_isFullScreen00);
    tolua_function(tolua_S,"isFullScreenForbidden",tolua_luafunc_GameLib_Framework_isFullScreenForbidden00);
    tolua_function(tolua_S,"isDragAndDropEnabled",tolua_luafunc_GameLib_Framework_isDragAndDropEnabled00);
    tolua_function(tolua_S,"requestEnd",tolua_luafunc_GameLib_Framework_requestEnd00);
    tolua_function(tolua_S,"isEndRequested",tolua_luafunc_GameLib_Framework_isEndRequested00);
    tolua_function(tolua_S,"time",tolua_luafunc_GameLib_Framework_time00);
    tolua_function(tolua_S,"frameRate",tolua_luafunc_GameLib_Framework_frameRate00);
    tolua_function(tolua_S,"setFrameRate",tolua_luafunc_GameLib_Framework_setFrameRate00);
    tolua_function(tolua_S,"previousFrameInterval",tolua_luafunc_GameLib_Framework_previousFrameInterval00);
    tolua_function(tolua_S,"isClipCursorEnabled",tolua_luafunc_GameLib_Framework_isClipCursorEnabled00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"Graphics",0);
   tolua_beginmodule(tolua_S,"Graphics");
    tolua_constant(tolua_S,"BLEND_OPAQUE",GameLib::Graphics::BLEND_OPAQUE);
    tolua_constant(tolua_S,"BLEND_LINEAR",GameLib::Graphics::BLEND_LINEAR);
    tolua_constant(tolua_S,"BLEND_ADDITIVE",GameLib::Graphics::BLEND_ADDITIVE);
    tolua_constant(tolua_S,"BLEND_MAX",GameLib::Graphics::BLEND_MAX);
    tolua_constant(tolua_S,"CULL_NONE",GameLib::Graphics::CULL_NONE);
    tolua_constant(tolua_S,"CULL_FRONT",GameLib::Graphics::CULL_FRONT);
    tolua_constant(tolua_S,"CULL_BACK",GameLib::Graphics::CULL_BACK);
    tolua_constant(tolua_S,"CULL_MAX",GameLib::Graphics::CULL_MAX);
    tolua_constant(tolua_S,"PRIMITIVE_TRIANGLE",GameLib::Graphics::PRIMITIVE_TRIANGLE);
    tolua_constant(tolua_S,"PRIMITIVE_LINE",GameLib::Graphics::PRIMITIVE_LINE);
    tolua_constant(tolua_S,"PRIMITIVE_POINT",GameLib::Graphics::PRIMITIVE_POINT);
    tolua_constant(tolua_S,"TEXTURE_FILTER_POINT",GameLib::Graphics::TEXTURE_FILTER_POINT);
    tolua_constant(tolua_S,"TEXTURE_FILTER_LINEAR",GameLib::Graphics::TEXTURE_FILTER_LINEAR);
    tolua_constant(tolua_S,"LIGHTING_NONE",GameLib::Graphics::LIGHTING_NONE);
    tolua_constant(tolua_S,"LIGHTING_PER_VERTEX",GameLib::Graphics::LIGHTING_PER_VERTEX);
    tolua_constant(tolua_S,"LIGHTING_PER_PIXEL",GameLib::Graphics::LIGHTING_PER_PIXEL);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"IDirect3DDevice9","IDirect3DDevice9","",NULL);
  tolua_beginmodule(tolua_S,"IDirect3DDevice9");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"Graphics",0);
   tolua_beginmodule(tolua_S,"Graphics");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Manager","GameLib::Graphics::Manager","",tolua_collect_GameLib__Graphics__Manager);
    #else
    tolua_cclass(tolua_S,"Manager","GameLib::Graphics::Manager","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Manager");
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Graphics_Manager_new00);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Graphics_Manager_new00_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Graphics_Manager_new00_local);
     tolua_function(tolua_S,"instance",tolua_luafunc_GameLib_Graphics_Manager_instance00);
     tolua_function(tolua_S,"setVertexBuffer",tolua_luafunc_GameLib_Graphics_Manager_setVertexBuffer00);
     tolua_function(tolua_S,"setIndexBuffer",tolua_luafunc_GameLib_Graphics_Manager_setIndexBuffer00);
     tolua_function(tolua_S,"setAnimatedVertexBoneBuffer",tolua_luafunc_GameLib_Graphics_Manager_setAnimatedVertexBoneBuffer00);
     tolua_function(tolua_S,"setTexture",tolua_luafunc_GameLib_Graphics_Manager_setTexture00);
     tolua_function(tolua_S,"enableDepthTest",tolua_luafunc_GameLib_Graphics_Manager_enableDepthTest00);
     tolua_function(tolua_S,"enableDepthWrite",tolua_luafunc_GameLib_Graphics_Manager_enableDepthWrite00);
     tolua_function(tolua_S,"setBlendMode",tolua_luafunc_GameLib_Graphics_Manager_setBlendMode00);
     tolua_function(tolua_S,"setCullMode",tolua_luafunc_GameLib_Graphics_Manager_setCullMode00);
     tolua_function(tolua_S,"setTextureFilter",tolua_luafunc_GameLib_Graphics_Manager_setTextureFilter00);
     tolua_function(tolua_S,"setProjectionViewMatrix",tolua_luafunc_GameLib_Graphics_Manager_setProjectionViewMatrix00);
     tolua_function(tolua_S,"setWorldMatrix",tolua_luafunc_GameLib_Graphics_Manager_setWorldMatrix00);
     tolua_function(tolua_S,"getProjectionViewMatrix",tolua_luafunc_GameLib_Graphics_Manager_getProjectionViewMatrix00);
     tolua_function(tolua_S,"getWorldMatrix",tolua_luafunc_GameLib_Graphics_Manager_getWorldMatrix00);
     tolua_function(tolua_S,"setViewport",tolua_luafunc_GameLib_Graphics_Manager_setViewport00);
     tolua_function(tolua_S,"getViewport",tolua_luafunc_GameLib_Graphics_Manager_getViewport00);
     tolua_function(tolua_S,"drawIndexed",tolua_luafunc_GameLib_Graphics_Manager_drawIndexed00);
     tolua_function(tolua_S,"draw",tolua_luafunc_GameLib_Graphics_Manager_draw00);
     tolua_function(tolua_S,"blendToScreen",tolua_luafunc_GameLib_Graphics_Manager_blendToScreen00);
     tolua_function(tolua_S,"enableFullScreen",tolua_luafunc_GameLib_Graphics_Manager_enableFullScreen00);
     tolua_function(tolua_S,"width",tolua_luafunc_GameLib_Graphics_Manager_width00);
     tolua_function(tolua_S,"height",tolua_luafunc_GameLib_Graphics_Manager_height00);
     tolua_function(tolua_S,"fullScreenWindowWidth",tolua_luafunc_GameLib_Graphics_Manager_fullScreenWindowWidth00);
     tolua_function(tolua_S,"fullScreenWindowHeight",tolua_luafunc_GameLib_Graphics_Manager_fullScreenWindowHeight00);
     tolua_function(tolua_S,"frameId",tolua_luafunc_GameLib_Graphics_Manager_frameId00);
     tolua_function(tolua_S,"captureScreen",tolua_luafunc_GameLib_Graphics_Manager_captureScreen00);
     tolua_function(tolua_S,"setLightingMode",tolua_luafunc_GameLib_Graphics_Manager_setLightingMode00);
     tolua_function(tolua_S,"setLightPosition",tolua_luafunc_GameLib_Graphics_Manager_setLightPosition00);
     tolua_function(tolua_S,"setLightIntensity",tolua_luafunc_GameLib_Graphics_Manager_setLightIntensity00);
     tolua_function(tolua_S,"setLightColor",tolua_luafunc_GameLib_Graphics_Manager_setLightColor00);
     tolua_function(tolua_S,"setEyePosition",tolua_luafunc_GameLib_Graphics_Manager_setEyePosition00);
     tolua_function(tolua_S,"setDiffuseColor",tolua_luafunc_GameLib_Graphics_Manager_setDiffuseColor00);
     tolua_function(tolua_S,"setSpecularColor",tolua_luafunc_GameLib_Graphics_Manager_setSpecularColor00);
     tolua_function(tolua_S,"setEmissionColor",tolua_luafunc_GameLib_Graphics_Manager_setEmissionColor00);
     tolua_function(tolua_S,"setAmbientColor",tolua_luafunc_GameLib_Graphics_Manager_setAmbientColor00);
     tolua_function(tolua_S,"setTransparency",tolua_luafunc_GameLib_Graphics_Manager_setTransparency00);
     tolua_function(tolua_S,"setSpecularSharpness",tolua_luafunc_GameLib_Graphics_Manager_setSpecularSharpness00);
     tolua_function(tolua_S,"dxDevice",tolua_luafunc_GameLib_Graphics_Manager_dxDevice00);
     tolua_function(tolua_S,"getLightingMode",tolua_luafunc_GameLib_Graphics_Manager_getLightingMode00);
     tolua_function(tolua_S,"sendWorldMatrixArray",tolua_luafunc_GameLib_Graphics_Manager_sendWorldMatrixArray00);
     tolua_function(tolua_S,"enableVertexBlend",tolua_luafunc_GameLib_Graphics_Manager_enableVertexBlend00);
     tolua_function(tolua_S,"enableMME",tolua_luafunc_GameLib_Graphics_Manager_enableMME00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"PseudoXml",0);
   tolua_beginmodule(tolua_S,"PseudoXml");
    tolua_cclass(tolua_S,"ConstElement","GameLib::PseudoXml::ConstElement","",NULL);
    tolua_beginmodule(tolua_S,"ConstElement");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"Graphics",0);
   tolua_beginmodule(tolua_S,"Graphics");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"Math",0);
   tolua_beginmodule(tolua_S,"Math");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Vector4","GameLib::Math::Vector4","",tolua_collect_GameLib__Math__Vector4);
    #else
    tolua_cclass(tolua_S,"Vector4","GameLib::Math::Vector4","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Vector4");
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector4_new00);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector4_new00_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector4_new00_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector4_new01);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector4_new01_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector4_new01_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector4_new02);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector4_new02_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector4_new02_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector4_new03);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector4_new03_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector4_new03_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector4_new04);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector4_new04_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector4_new04_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector4_new05);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector4_new05_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector4_new05_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector4_new06);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector4_new06_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector4_new06_local);
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Vector4_new07);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Vector4_new07_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Vector4_new07_local);
     tolua_function(tolua_S,"set",tolua_luafunc_GameLib_Math_Vector4_set00);
     tolua_function(tolua_S,".seti",tolua_luafunc_GameLib_Math_Vector4__seti00);
     tolua_function(tolua_S,".geti",tolua_luafunc_GameLib_Math_Vector4__geti00);
     tolua_function(tolua_S,".geti",tolua_luafunc_GameLib_Math_Vector4__geti01);
     tolua_variable(tolua_S,"x",tolua_get_GameLib__Math__Vector4_x,tolua_set_GameLib__Math__Vector4_x);
     tolua_variable(tolua_S,"y",tolua_get_GameLib__Math__Vector4_y,tolua_set_GameLib__Math__Vector4_y);
     tolua_variable(tolua_S,"z",tolua_get_GameLib__Math__Vector4_z,tolua_set_GameLib__Math__Vector4_z);
     tolua_variable(tolua_S,"w",tolua_get_GameLib__Math__Vector4_w,tolua_set_GameLib__Math__Vector4_w);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"Math",0);
   tolua_beginmodule(tolua_S,"Math");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"Math",0);
   tolua_beginmodule(tolua_S,"Math");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"Math",0);
   tolua_beginmodule(tolua_S,"Math");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Matrix34","GameLib::Math::Matrix34","",tolua_collect_GameLib__Math__Matrix34);
    #else
    tolua_cclass(tolua_S,"Matrix34","GameLib::Math::Matrix34","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Matrix34");
     tolua_function(tolua_S,"new",tolua_luafunc_GameLib_Math_Matrix34_new00);
     tolua_function(tolua_S,"new_local",tolua_luafunc_GameLib_Math_Matrix34_new00_local);
     tolua_function(tolua_S,".call",tolua_luafunc_GameLib_Math_Matrix34_new00_local);
     tolua_function(tolua_S,"setIdentity",tolua_luafunc_GameLib_Math_Matrix34_setIdentity00);
     tolua_function(tolua_S,"setTranslation",tolua_luafunc_GameLib_Math_Matrix34_setTranslation00);
     tolua_function(tolua_S,"setTranslation",tolua_luafunc_GameLib_Math_Matrix34_setTranslation01);
     tolua_function(tolua_S,"setRotationX",tolua_luafunc_GameLib_Math_Matrix34_setRotationX00);
     tolua_function(tolua_S,"setRotationY",tolua_luafunc_GameLib_Math_Matrix34_setRotationY00);
     tolua_function(tolua_S,"setRotationZ",tolua_luafunc_GameLib_Math_Matrix34_setRotationZ00);
     tolua_function(tolua_S,"setScaling",tolua_luafunc_GameLib_Math_Matrix34_setScaling00);
     tolua_function(tolua_S,"setScaling",tolua_luafunc_GameLib_Math_Matrix34_setScaling01);
     tolua_function(tolua_S,"setScaling",tolua_luafunc_GameLib_Math_Matrix34_setScaling02);
     tolua_function(tolua_S,"setViewTransform",tolua_luafunc_GameLib_Math_Matrix34_setViewTransform00);
     tolua_function(tolua_S,"setViewTransformRH",tolua_luafunc_GameLib_Math_Matrix34_setViewTransformRH00);
     tolua_function(tolua_S,"setViewTransformLH",tolua_luafunc_GameLib_Math_Matrix34_setViewTransformLH00);
     tolua_function(tolua_S,"translate",tolua_luafunc_GameLib_Math_Matrix34_translate00);
     tolua_function(tolua_S,"translate",tolua_luafunc_GameLib_Math_Matrix34_translate01);
     tolua_function(tolua_S,"rotateX",tolua_luafunc_GameLib_Math_Matrix34_rotateX00);
     tolua_function(tolua_S,"rotateY",tolua_luafunc_GameLib_Math_Matrix34_rotateY00);
     tolua_function(tolua_S,"rotateZ",tolua_luafunc_GameLib_Math_Matrix34_rotateZ00);
     tolua_function(tolua_S,"scale",tolua_luafunc_GameLib_Math_Matrix34_scale00);
     tolua_function(tolua_S,"scale",tolua_luafunc_GameLib_Math_Matrix34_scale01);
     tolua_function(tolua_S,"scale",tolua_luafunc_GameLib_Math_Matrix34_scale02);
     tolua_function(tolua_S,"mul",tolua_luafunc_GameLib_Math_Matrix34_mul00);
     tolua_function(tolua_S,"mul33",tolua_luafunc_GameLib_Math_Matrix34_mul3300);
     tolua_function(tolua_S,"setMul",tolua_luafunc_GameLib_Math_Matrix34_setMul00);
     tolua_function(tolua_S,"setMul",tolua_luafunc_GameLib_Math_Matrix34_setMul01);
     tolua_function(tolua_S,".eq",tolua_luafunc_GameLib_Math_Matrix34__eq00);
     tolua_function(tolua_S,"transpose33",tolua_luafunc_GameLib_Math_Matrix34_transpose3300);
     tolua_function(tolua_S,"setTransposed33",tolua_luafunc_GameLib_Math_Matrix34_setTransposed3300);
     tolua_function(tolua_S,"invert",tolua_luafunc_GameLib_Math_Matrix34_invert00);
     tolua_function(tolua_S,"setInverse",tolua_luafunc_GameLib_Math_Matrix34_setInverse00);
     tolua_variable(tolua_S,"m00",tolua_get_GameLib__Math__Matrix34_m00,tolua_set_GameLib__Math__Matrix34_m00);
     tolua_variable(tolua_S,"m01",tolua_get_GameLib__Math__Matrix34_m01,tolua_set_GameLib__Math__Matrix34_m01);
     tolua_variable(tolua_S,"m02",tolua_get_GameLib__Math__Matrix34_m02,tolua_set_GameLib__Math__Matrix34_m02);
     tolua_variable(tolua_S,"m03",tolua_get_GameLib__Math__Matrix34_m03,tolua_set_GameLib__Math__Matrix34_m03);
     tolua_variable(tolua_S,"m10",tolua_get_GameLib__Math__Matrix34_m10,tolua_set_GameLib__Math__Matrix34_m10);
     tolua_variable(tolua_S,"m11",tolua_get_GameLib__Math__Matrix34_m11,tolua_set_GameLib__Math__Matrix34_m11);
     tolua_variable(tolua_S,"m12",tolua_get_GameLib__Math__Matrix34_m12,tolua_set_GameLib__Math__Matrix34_m12);
     tolua_variable(tolua_S,"m13",tolua_get_GameLib__Math__Matrix34_m13,tolua_set_GameLib__Math__Matrix34_m13);
     tolua_variable(tolua_S,"m20",tolua_get_GameLib__Math__Matrix34_m20,tolua_set_GameLib__Math__Matrix34_m20);
     tolua_variable(tolua_S,"m21",tolua_get_GameLib__Math__Matrix34_m21,tolua_set_GameLib__Math__Matrix34_m21);
     tolua_variable(tolua_S,"m22",tolua_get_GameLib__Math__Matrix34_m22,tolua_set_GameLib__Math__Matrix34_m22);
     tolua_variable(tolua_S,"m23",tolua_get_GameLib__Math__Matrix34_m23,tolua_set_GameLib__Math__Matrix34_m23);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"XmlLoader",0);
  tolua_beginmodule(tolua_S,"XmlLoader");
   tolua_module(tolua_S,"MME",0);
   tolua_beginmodule(tolua_S,"MME");
    tolua_module(tolua_S,"Object",0);
    tolua_beginmodule(tolua_S,"Object");
     #ifdef __cplusplus
     tolua_cclass(tolua_S,"ModelKai","XmlLoader::MME::Object::ModelKai","",tolua_collect_XmlLoader__MME__Object__ModelKai);
     #else
     tolua_cclass(tolua_S,"ModelKai","XmlLoader::MME::Object::ModelKai","",NULL);
     #endif
     tolua_beginmodule(tolua_S,"ModelKai");
      tolua_function(tolua_S,"new",tolua_luafunc_XmlLoader_MME_Object_ModelKai_new00);
      tolua_function(tolua_S,"new_local",tolua_luafunc_XmlLoader_MME_Object_ModelKai_new00_local);
      tolua_function(tolua_S,".call",tolua_luafunc_XmlLoader_MME_Object_ModelKai_new00_local);
      tolua_function(tolua_S,"delete",tolua_luafunc_XmlLoader_MME_Object_ModelKai_delete00);
      tolua_function(tolua_S,"loadStart",tolua_luafunc_XmlLoader_MME_Object_ModelKai_loadStart00);
      tolua_function(tolua_S,"isReady",tolua_luafunc_XmlLoader_MME_Object_ModelKai_isReady00);
      tolua_function(tolua_S,"instance",tolua_luafunc_XmlLoader_MME_Object_ModelKai_instance00);
     tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"btCollisionObject","btCollisionObject","",NULL);
  tolua_beginmodule(tolua_S,"btCollisionObject");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"PseudoXml",0);
   tolua_beginmodule(tolua_S,"PseudoXml");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObject",0);
  tolua_beginmodule(tolua_S,"GameObject");
   tolua_cclass(tolua_S,"Accessory","GameObject::Accessory","",NULL);
   tolua_beginmodule(tolua_S,"Accessory");
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"AccessoryUtils",0);
   tolua_beginmodule(tolua_S,"AccessoryUtils");
    tolua_module(tolua_S,"MME",0);
    tolua_beginmodule(tolua_S,"MME");
     tolua_cclass(tolua_S,"TemplateModel","GameObject::AccessoryUtils::MME::TemplateModel","",NULL);
     tolua_beginmodule(tolua_S,"TemplateModel");
     tolua_endmodule(tolua_S);
     tolua_cclass(tolua_S,"Model","GameObject::AccessoryUtils::MME::Model","",NULL);
     tolua_beginmodule(tolua_S,"Model");
     tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObjectData",0);
  tolua_beginmodule(tolua_S,"GameObjectData");
   tolua_cclass(tolua_S,"Status","GameObjectData::Status","",NULL);
   tolua_beginmodule(tolua_S,"Status");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"XmlLoader",0);
  tolua_beginmodule(tolua_S,"XmlLoader");
   tolua_cclass(tolua_S,"Shape","XmlLoader::Shape","",NULL);
   tolua_beginmodule(tolua_S,"Shape");
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"GameObject",0);
   tolua_beginmodule(tolua_S,"GameObject");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Accessory","XmlLoader::GameObject::Accessory","",tolua_collect_XmlLoader__GameObject__Accessory);
    #else
    tolua_cclass(tolua_S,"Accessory","XmlLoader::GameObject::Accessory","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Accessory");
     tolua_function(tolua_S,"new",tolua_luafunc_XmlLoader_GameObject_Accessory_new00);
     tolua_function(tolua_S,"new_local",tolua_luafunc_XmlLoader_GameObject_Accessory_new00_local);
     tolua_function(tolua_S,".call",tolua_luafunc_XmlLoader_GameObject_Accessory_new00_local);
     tolua_function(tolua_S,"delete",tolua_luafunc_XmlLoader_GameObject_Accessory_delete00);
     tolua_function(tolua_S,"isReady",tolua_luafunc_XmlLoader_GameObject_Accessory_isReady00);
     tolua_function(tolua_S,"instance",tolua_luafunc_XmlLoader_GameObject_Accessory_instance00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"FileIO",0);
   tolua_beginmodule(tolua_S,"FileIO");
    tolua_cclass(tolua_S,"InFile","GameLib::FileIO::InFile","",NULL);
    tolua_beginmodule(tolua_S,"InFile");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObject",0);
  tolua_beginmodule(tolua_S,"GameObject");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Player","GameObject::Player","BaseObject",tolua_collect_GameObject__Player);
   #else
   tolua_cclass(tolua_S,"Player","GameObject::Player","BaseObject",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Player");
    tolua_function(tolua_S,"create",tolua_luafunc_GameObject_Player_create00);
    tolua_function(tolua_S,"create",tolua_luafunc_GameObject_Player_create01);
    tolua_function(tolua_S,"delete",tolua_luafunc_GameObject_Player_delete00);
    tolua_function(tolua_S,"release",tolua_luafunc_GameObject_Player_release00);
    tolua_function(tolua_S,"update",tolua_luafunc_GameObject_Player_update00);
    tolua_function(tolua_S,"preDraw",tolua_luafunc_GameObject_Player_preDraw00);
    tolua_function(tolua_S,"drawHUD",tolua_luafunc_GameObject_Player_drawHUD00);
    tolua_function(tolua_S,"getRTTI",tolua_luafunc_GameObject_Player_getRTTI00);
    tolua_variable(tolua_S,"rtti",tolua_get_GameObject__Player_rtti,NULL);
    tolua_function(tolua_S,"removeFromWorld",tolua_luafunc_GameObject_Player_removeFromWorld00);
    tolua_function(tolua_S,"addToWorld",tolua_luafunc_GameObject_Player_addToWorld00);
    tolua_function(tolua_S,"onCollisionEnter",tolua_luafunc_GameObject_Player_onCollisionEnter00);
    tolua_function(tolua_S,"onCollisionStay",tolua_luafunc_GameObject_Player_onCollisionStay00);
    tolua_function(tolua_S,"onCollisionExit",tolua_luafunc_GameObject_Player_onCollisionExit00);
    tolua_function(tolua_S,"getElapsedTime",tolua_luafunc_GameObject_Player_getElapsedTime00);
    tolua_function(tolua_S,"getMouse",tolua_luafunc_GameObject_Player_getMouse00);
    tolua_function(tolua_S,"getMousePos",tolua_luafunc_GameObject_Player_getMousePos00);
    tolua_function(tolua_S,"getModel",tolua_luafunc_GameObject_Player_getModel00);
    tolua_function(tolua_S,"getHeight",tolua_luafunc_GameObject_Player_getHeight00);
    tolua_function(tolua_S,"getStatus",tolua_luafunc_GameObject_Player_getStatus00);
    tolua_function(tolua_S,"getCharacter",tolua_luafunc_GameObject_Player_getCharacter00);
    tolua_function(tolua_S,"onGround",tolua_luafunc_GameObject_Player_onGround00);
    tolua_function(tolua_S,"addActions",tolua_luafunc_GameObject_Player_addActions00);
    tolua_function(tolua_S,"getBtCollisionObject",tolua_luafunc_GameObject_Player_getBtCollisionObject00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"ICollider","GameObject::ICollider","",NULL);
   tolua_beginmodule(tolua_S,"ICollider");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObjectData",0);
  tolua_beginmodule(tolua_S,"GameObjectData");
   tolua_cclass(tolua_S,"WeaponStatus","GameObjectData::WeaponStatus","",NULL);
   tolua_beginmodule(tolua_S,"WeaponStatus");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"XmlLoader",0);
  tolua_beginmodule(tolua_S,"XmlLoader");
   tolua_module(tolua_S,"MME",0);
   tolua_beginmodule(tolua_S,"MME");
    tolua_module(tolua_S,"Object",0);
    tolua_beginmodule(tolua_S,"Object");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"Camera",0);
   tolua_beginmodule(tolua_S,"Camera");
    tolua_cclass(tolua_S,"PlayerCamera","XmlLoader::Camera::PlayerCamera","",NULL);
    tolua_beginmodule(tolua_S,"PlayerCamera");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"GameObject",0);
   tolua_beginmodule(tolua_S,"GameObject");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Player","XmlLoader::GameObject::Player","",tolua_collect_XmlLoader__GameObject__Player);
    #else
    tolua_cclass(tolua_S,"Player","XmlLoader::GameObject::Player","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Player");
     tolua_function(tolua_S,"new",tolua_luafunc_XmlLoader_GameObject_Player_new00);
     tolua_function(tolua_S,"new_local",tolua_luafunc_XmlLoader_GameObject_Player_new00_local);
     tolua_function(tolua_S,".call",tolua_luafunc_XmlLoader_GameObject_Player_new00_local);
     tolua_function(tolua_S,"delete",tolua_luafunc_XmlLoader_GameObject_Player_delete00);
     tolua_function(tolua_S,"loadXml",tolua_luafunc_XmlLoader_GameObject_Player_loadXml00);
     tolua_function(tolua_S,"isReady",tolua_luafunc_XmlLoader_GameObject_Player_isReady00);
     tolua_function(tolua_S,"instance",tolua_luafunc_XmlLoader_GameObject_Player_instance00);
     tolua_function(tolua_S,"getName",tolua_luafunc_XmlLoader_GameObject_Player_getName00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"PseudoXml",0);
   tolua_beginmodule(tolua_S,"PseudoXml");
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"FileIO",0);
   tolua_beginmodule(tolua_S,"FileIO");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObject",0);
  tolua_beginmodule(tolua_S,"GameObject");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Enemy","GameObject::Enemy","BaseObject",tolua_collect_GameObject__Enemy);
   #else
   tolua_cclass(tolua_S,"Enemy","GameObject::Enemy","BaseObject",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Enemy");
    tolua_function(tolua_S,"create",tolua_luafunc_GameObject_Enemy_create00);
    tolua_function(tolua_S,"delete",tolua_luafunc_GameObject_Enemy_delete00);
    tolua_function(tolua_S,"getRTTI",tolua_luafunc_GameObject_Enemy_getRTTI00);
    tolua_variable(tolua_S,"rtti",tolua_get_GameObject__Enemy_rtti,NULL);
    tolua_function(tolua_S,"postdraw",tolua_luafunc_GameObject_Enemy_postdraw00);
    tolua_function(tolua_S,"update",tolua_luafunc_GameObject_Enemy_update00);
    tolua_function(tolua_S,"removeFromWorld",tolua_luafunc_GameObject_Enemy_removeFromWorld00);
    tolua_function(tolua_S,"addToWorld",tolua_luafunc_GameObject_Enemy_addToWorld00);
    tolua_function(tolua_S,"onCollisionEnter",tolua_luafunc_GameObject_Enemy_onCollisionEnter00);
    tolua_function(tolua_S,"isDied",tolua_luafunc_GameObject_Enemy_isDied00);
    tolua_function(tolua_S,"updateWhenDied",tolua_luafunc_GameObject_Enemy_updateWhenDied00);
    tolua_function(tolua_S,"getBtCollisionObject",tolua_luafunc_GameObject_Enemy_getBtCollisionObject00);
    tolua_function(tolua_S,"getConstBtCollisionObject",tolua_luafunc_GameObject_Enemy_getConstBtCollisionObject00);
    tolua_function(tolua_S,"getWorldTransform",tolua_luafunc_GameObject_Enemy_getWorldTransform00);
    tolua_function(tolua_S,"getWorldTransform",tolua_luafunc_GameObject_Enemy_getWorldTransform01);
    tolua_function(tolua_S,"isInWorld",tolua_luafunc_GameObject_Enemy_isInWorld00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObjectData",0);
  tolua_beginmodule(tolua_S,"GameObjectData");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"XmlLoader",0);
  tolua_beginmodule(tolua_S,"XmlLoader");
   tolua_module(tolua_S,"MME",0);
   tolua_beginmodule(tolua_S,"MME");
    tolua_module(tolua_S,"Object",0);
    tolua_beginmodule(tolua_S,"Object");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"GameObject",0);
   tolua_beginmodule(tolua_S,"GameObject");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Enemy","XmlLoader::GameObject::Enemy","",tolua_collect_XmlLoader__GameObject__Enemy);
    #else
    tolua_cclass(tolua_S,"Enemy","XmlLoader::GameObject::Enemy","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Enemy");
     tolua_function(tolua_S,"new",tolua_luafunc_XmlLoader_GameObject_Enemy_new00);
     tolua_function(tolua_S,"new_local",tolua_luafunc_XmlLoader_GameObject_Enemy_new00_local);
     tolua_function(tolua_S,".call",tolua_luafunc_XmlLoader_GameObject_Enemy_new00_local);
     tolua_function(tolua_S,"delete",tolua_luafunc_XmlLoader_GameObject_Enemy_delete00);
     tolua_function(tolua_S,"createSP",tolua_luafunc_XmlLoader_GameObject_Enemy_createSP00);
     tolua_function(tolua_S,"loadXml",tolua_luafunc_XmlLoader_GameObject_Enemy_loadXml00);
     tolua_function(tolua_S,"isReady",tolua_luafunc_XmlLoader_GameObject_Enemy_isReady00);
     tolua_function(tolua_S,"instance",tolua_luafunc_XmlLoader_GameObject_Enemy_instance00);
     tolua_function(tolua_S,"getName",tolua_luafunc_XmlLoader_GameObject_Enemy_getName00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"std",0);
  tolua_beginmodule(tolua_S,"std");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"shared_ptr_XmlLoader__GameObject__Enemy_","std::shared_ptr<XmlLoader::GameObject::Enemy>","",tolua_collect_std__shared_ptr_XmlLoader__GameObject__Enemy_);
   #else
   tolua_cclass(tolua_S,"shared_ptr_XmlLoader__GameObject__Enemy_","std::shared_ptr<XmlLoader::GameObject::Enemy>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"shared_ptr_XmlLoader__GameObject__Enemy_");
    tolua_function(tolua_S,"new",tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__delete00);
    tolua_function(tolua_S,"reset",tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__reset00);
    tolua_function(tolua_S,"get",tolua_luafunc_std_shared_ptr_XmlLoader__GameObject__Enemy__get00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MME",0);
  tolua_beginmodule(tolua_S,"MME");
   tolua_cclass(tolua_S,"Manager","MME::Manager","",NULL);
   tolua_beginmodule(tolua_S,"Manager");
    tolua_function(tolua_S,"instance",tolua_luafunc_MME_Manager_instance00);
    tolua_function(tolua_S,"destroy",tolua_luafunc_MME_Manager_destroy00);
    tolua_function(tolua_S,"isReady",tolua_luafunc_MME_Manager_isReady00);
    tolua_function(tolua_S,"drawAll",tolua_luafunc_MME_Manager_drawAll00);
    tolua_function(tolua_S,"drawIndexed",tolua_luafunc_MME_Manager_drawIndexed00);
    tolua_function(tolua_S,"draw",tolua_luafunc_MME_Manager_draw00);
    tolua_function(tolua_S,"setVertexBuffer",tolua_luafunc_MME_Manager_setVertexBuffer00);
    tolua_function(tolua_S,"setIndexBuffer",tolua_luafunc_MME_Manager_setIndexBuffer00);
    tolua_function(tolua_S,"setAnimatedVertexBoneBuffer",tolua_luafunc_MME_Manager_setAnimatedVertexBoneBuffer00);
    tolua_function(tolua_S,"setTexture",tolua_luafunc_MME_Manager_setTexture00);
    tolua_function(tolua_S,"setToonTexture",tolua_luafunc_MME_Manager_setToonTexture00);
    tolua_function(tolua_S,"setSphereTexture",tolua_luafunc_MME_Manager_setSphereTexture00);
    tolua_function(tolua_S,"setSphereTextureAdditive",tolua_luafunc_MME_Manager_setSphereTextureAdditive00);
    tolua_function(tolua_S,"setViewMatrix",tolua_luafunc_MME_Manager_setViewMatrix00);
    tolua_function(tolua_S,"setProjectionMatrix",tolua_luafunc_MME_Manager_setProjectionMatrix00);
    tolua_function(tolua_S,"setWorldMatrix",tolua_luafunc_MME_Manager_setWorldMatrix00);
    tolua_function(tolua_S,"Manager__getViewMatrix",tolua_luafunc_MME_Manager_Manager__getViewMatrix00);
    tolua_function(tolua_S,"Manager__getProjectionMatrix",tolua_luafunc_MME_Manager_Manager__getProjectionMatrix00);
    tolua_function(tolua_S,"Manager__getWorldMatrix",tolua_luafunc_MME_Manager_Manager__getWorldMatrix00);
    tolua_function(tolua_S,"setLightViewMatrix",tolua_luafunc_MME_Manager_setLightViewMatrix00);
    tolua_function(tolua_S,"setLightProjectionMatrix",tolua_luafunc_MME_Manager_setLightProjectionMatrix00);
    tolua_function(tolua_S,"setLightWorldMatrix",tolua_luafunc_MME_Manager_setLightWorldMatrix00);
    tolua_function(tolua_S,"setLightPosition",tolua_luafunc_MME_Manager_setLightPosition00);
    tolua_function(tolua_S,"setLightDirection",tolua_luafunc_MME_Manager_setLightDirection00);
    tolua_function(tolua_S,"setLightColor",tolua_luafunc_MME_Manager_setLightColor00);
    tolua_function(tolua_S,"setLightDiffuse",tolua_luafunc_MME_Manager_setLightDiffuse00);
    tolua_function(tolua_S,"setLightAmbient",tolua_luafunc_MME_Manager_setLightAmbient00);
    tolua_function(tolua_S,"setLightSpecular",tolua_luafunc_MME_Manager_setLightSpecular00);
    tolua_function(tolua_S,"setEyePosition",tolua_luafunc_MME_Manager_setEyePosition00);
    tolua_function(tolua_S,"setEyeDirection",tolua_luafunc_MME_Manager_setEyeDirection00);
    tolua_function(tolua_S,"setDiffuseColor",tolua_luafunc_MME_Manager_setDiffuseColor00);
    tolua_function(tolua_S,"setSpecularColor",tolua_luafunc_MME_Manager_setSpecularColor00);
    tolua_function(tolua_S,"setEmissionColor",tolua_luafunc_MME_Manager_setEmissionColor00);
    tolua_function(tolua_S,"setAmbientColor",tolua_luafunc_MME_Manager_setAmbientColor00);
    tolua_function(tolua_S,"setEdgeColor",tolua_luafunc_MME_Manager_setEdgeColor00);
    tolua_function(tolua_S,"setZNear",tolua_luafunc_MME_Manager_setZNear00);
    tolua_function(tolua_S,"setZFar",tolua_luafunc_MME_Manager_setZFar00);
    tolua_function(tolua_S,"setToonColor",tolua_luafunc_MME_Manager_setToonColor00);
    tolua_function(tolua_S,"setSpecularSharpness",tolua_luafunc_MME_Manager_setSpecularSharpness00);
    tolua_function(tolua_S,"sendWorldMatrixArray",tolua_luafunc_MME_Manager_sendWorldMatrixArray00);
    tolua_function(tolua_S,"enableVertexBlend",tolua_luafunc_MME_Manager_enableVertexBlend00);
    tolua_function(tolua_S,"getLightDirection",tolua_luafunc_MME_Manager_getLightDirection00);
    tolua_function(tolua_S,"sendParamsToGameLibGraphicsManager",tolua_luafunc_MME_Manager_sendParamsToGameLibGraphicsManager00);
    tolua_function(tolua_S,"canDraw",tolua_luafunc_MME_Manager_canDraw00);
    tolua_function(tolua_S,"getCurrentPass",tolua_luafunc_MME_Manager_getCurrentPass00);
    tolua_function(tolua_S,"getCurrentPass",tolua_luafunc_MME_Manager_getCurrentPass01);
    tolua_function(tolua_S,"setCurrentEffect",tolua_luafunc_MME_Manager_setCurrentEffect00);
    tolua_function(tolua_S,"sendParams",tolua_luafunc_MME_Manager_sendParams00);
    tolua_function(tolua_S,"findStandardEffect",tolua_luafunc_MME_Manager_findStandardEffect00);
    tolua_function(tolua_S,"findPostEffect",tolua_luafunc_MME_Manager_findPostEffect00);
    tolua_function(tolua_S,"findStandardEffect",tolua_luafunc_MME_Manager_findStandardEffect01);
    tolua_function(tolua_S,"backup",tolua_luafunc_MME_Manager_backup00);
    tolua_function(tolua_S,"recover",tolua_luafunc_MME_Manager_recover00);
    tolua_function(tolua_S,"beginShadow",tolua_luafunc_MME_Manager_beginShadow00);
    tolua_function(tolua_S,"endShadow",tolua_luafunc_MME_Manager_endShadow00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MME",0);
  tolua_beginmodule(tolua_S,"MME");
   tolua_module(tolua_S,"Drawer",0);
   tolua_beginmodule(tolua_S,"Drawer");
    tolua_module(tolua_S,"CutScene",0);
    tolua_beginmodule(tolua_S,"CutScene");
     tolua_function(tolua_S,"destroy",tolua_luafunc_MME_Drawer_CutScene_destroy00);
     tolua_function(tolua_S,"isReady",tolua_luafunc_MME_Drawer_CutScene_isReady00);
     tolua_function(tolua_S,"draw",tolua_luafunc_MME_Drawer_CutScene_draw00);
     tolua_function(tolua_S,"add",tolua_luafunc_MME_Drawer_CutScene_add00);
     tolua_function(tolua_S,"add",tolua_luafunc_MME_Drawer_CutScene_add01);
     tolua_function(tolua_S,"add",tolua_luafunc_MME_Drawer_CutScene_add02);
     tolua_function(tolua_S,"add",tolua_luafunc_MME_Drawer_CutScene_add03);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"FileLoader","FileLoader","",NULL);
  tolua_beginmodule(tolua_S,"FileLoader");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObject",0);
  tolua_beginmodule(tolua_S,"GameObject");
   tolua_module(tolua_S,"AccessoryUtils",0);
   tolua_beginmodule(tolua_S,"AccessoryUtils");
    tolua_module(tolua_S,"MME",0);
    tolua_beginmodule(tolua_S,"MME");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MME",0);
  tolua_beginmodule(tolua_S,"MME");
   tolua_module(tolua_S,"Object",0);
   tolua_beginmodule(tolua_S,"Object");
    tolua_cclass(tolua_S,"IObject","MME::Object::IObject","",NULL);
    tolua_beginmodule(tolua_S,"IObject");
    tolua_endmodule(tolua_S);
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"ModelKai","MME::Object::ModelKai","MME::Object::IObject",tolua_collect_MME__Object__ModelKai);
    #else
    tolua_cclass(tolua_S,"ModelKai","MME::Object::ModelKai","MME::Object::IObject",NULL);
    #endif
    tolua_beginmodule(tolua_S,"ModelKai");
     tolua_function(tolua_S,"create",tolua_luafunc_MME_Object_ModelKai_create00);
     tolua_function(tolua_S,"delete",tolua_luafunc_MME_Object_ModelKai_delete00);
     tolua_function(tolua_S,"draw",tolua_luafunc_MME_Object_ModelKai_draw00);
     tolua_function(tolua_S,"getScale",tolua_luafunc_MME_Object_ModelKai_getScale00);
     tolua_function(tolua_S,"getFaceValue",tolua_luafunc_MME_Object_ModelKai_getFaceValue00);
     tolua_function(tolua_S,"getBoneMatrix",tolua_luafunc_MME_Object_ModelKai_getBoneMatrix00);
     tolua_function(tolua_S,"getModelFileName",tolua_luafunc_MME_Object_ModelKai_getModelFileName00);
     tolua_function(tolua_S,"update",tolua_luafunc_MME_Object_ModelKai_update00);
     tolua_function(tolua_S,"isReady",tolua_luafunc_MME_Object_ModelKai_isReady00);
     tolua_function(tolua_S,"init",tolua_luafunc_MME_Object_ModelKai_init00);
     tolua_function(tolua_S,"isAnimOver",tolua_luafunc_MME_Object_ModelKai_isAnimOver00);
     tolua_function(tolua_S,"changeAnimation",tolua_luafunc_MME_Object_ModelKai_changeAnimation00);
     tolua_function(tolua_S,"addAnimState",tolua_luafunc_MME_Object_ModelKai_addAnimState00);
     tolua_function(tolua_S,"getAccessory",tolua_luafunc_MME_Object_ModelKai_getAccessory00);
     tolua_function(tolua_S,"addAccessory",tolua_luafunc_MME_Object_ModelKai_addAccessory00);
     tolua_function(tolua_S,"getFrame",tolua_luafunc_MME_Object_ModelKai_getFrame00);
     tolua_function(tolua_S,"getBone",tolua_luafunc_MME_Object_ModelKai_getBone00);
     tolua_function(tolua_S,"getAnimationModel",tolua_luafunc_MME_Object_ModelKai_getAnimationModel00);
     tolua_function(tolua_S,"addToWorld",tolua_luafunc_MME_Object_ModelKai_addToWorld00);
     tolua_function(tolua_S,"removeFromWorld",tolua_luafunc_MME_Object_ModelKai_removeFromWorld00);
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"PointLight","MME::Object::PointLight","",NULL);
    tolua_beginmodule(tolua_S,"PointLight");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"Accessory","MME::Object::Accessory","",NULL);
    tolua_beginmodule(tolua_S,"Accessory");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"Batch",0);
   tolua_beginmodule(tolua_S,"Batch");
    tolua_cclass(tolua_S,"StandardEffectBatch","MME::Batch::StandardEffectBatch","",NULL);
    tolua_beginmodule(tolua_S,"StandardEffectBatch");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"PostEffectBatch","MME::Batch::PostEffectBatch","",NULL);
    tolua_beginmodule(tolua_S,"PostEffectBatch");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
   tolua_module(tolua_S,"Drawer",0);
   tolua_beginmodule(tolua_S,"Drawer");
    tolua_cclass(tolua_S,"GameDrawer","MME::Drawer::GameDrawer","",NULL);
    tolua_beginmodule(tolua_S,"GameDrawer");
     tolua_function(tolua_S,"instance",tolua_luafunc_MME_Drawer_GameDrawer_instance00);
     tolua_function(tolua_S,"destroy",tolua_luafunc_MME_Drawer_GameDrawer_destroy00);
     tolua_function(tolua_S,"isReady",tolua_luafunc_MME_Drawer_GameDrawer_isReady00);
     tolua_function(tolua_S,"draw",tolua_luafunc_MME_Drawer_GameDrawer_draw00);
     tolua_function(tolua_S,"add",tolua_luafunc_MME_Drawer_GameDrawer_add00);
     tolua_function(tolua_S,"add",tolua_luafunc_MME_Drawer_GameDrawer_add01);
     tolua_function(tolua_S,"add",tolua_luafunc_MME_Drawer_GameDrawer_add02);
     tolua_function(tolua_S,"add",tolua_luafunc_MME_Drawer_GameDrawer_add03);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"std",0);
  tolua_beginmodule(tolua_S,"std");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"shared_ptr_MME__Object__ModelKai_","std::shared_ptr<MME::Object::ModelKai>","",tolua_collect_std__shared_ptr_MME__Object__ModelKai_);
   #else
   tolua_cclass(tolua_S,"shared_ptr_MME__Object__ModelKai_","std::shared_ptr<MME::Object::ModelKai>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"shared_ptr_MME__Object__ModelKai_");
    tolua_function(tolua_S,"new",tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__delete00);
    tolua_function(tolua_S,"reset",tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__reset00);
    tolua_function(tolua_S,"get",tolua_luafunc_std_shared_ptr_MME__Object__ModelKai__get00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MME",0);
  tolua_beginmodule(tolua_S,"MME");
   tolua_module(tolua_S,"Object",0);
   tolua_beginmodule(tolua_S,"Object");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MME",0);
  tolua_beginmodule(tolua_S,"MME");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"StandardEffect","MME::StandardEffect","BaseEffect",tolua_collect_MME__StandardEffect);
   #else
   tolua_cclass(tolua_S,"StandardEffect","MME::StandardEffect","BaseEffect",NULL);
   #endif
   tolua_beginmodule(tolua_S,"StandardEffect");
    tolua_function(tolua_S,"new",tolua_luafunc_MME_StandardEffect_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_MME_StandardEffect_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_MME_StandardEffect_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_MME_StandardEffect_delete00);
    tolua_function(tolua_S,"drawZPlot",tolua_luafunc_MME_StandardEffect_drawZPlot00);
    tolua_function(tolua_S,"drawObject",tolua_luafunc_MME_StandardEffect_drawObject00);
    tolua_function(tolua_S,"drawObjectSS",tolua_luafunc_MME_StandardEffect_drawObjectSS00);
    tolua_function(tolua_S,"drawEdge",tolua_luafunc_MME_StandardEffect_drawEdge00);
    tolua_function(tolua_S,"drawZPrePass",tolua_luafunc_MME_StandardEffect_drawZPrePass00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"std",0);
  tolua_beginmodule(tolua_S,"std");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"shared_ptr_MME__StandardEffect_","std::shared_ptr<MME::StandardEffect>","",tolua_collect_std__shared_ptr_MME__StandardEffect_);
   #else
   tolua_cclass(tolua_S,"shared_ptr_MME__StandardEffect_","std::shared_ptr<MME::StandardEffect>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"shared_ptr_MME__StandardEffect_");
    tolua_function(tolua_S,"new",tolua_luafunc_std_shared_ptr_MME__StandardEffect__new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_std_shared_ptr_MME__StandardEffect__new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_std_shared_ptr_MME__StandardEffect__new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_std_shared_ptr_MME__StandardEffect__delete00);
    tolua_function(tolua_S,"reset",tolua_luafunc_std_shared_ptr_MME__StandardEffect__reset00);
    tolua_function(tolua_S,"get",tolua_luafunc_std_shared_ptr_MME__StandardEffect__get00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MME",0);
  tolua_beginmodule(tolua_S,"MME");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"PostEffect","MME::PostEffect","BaseEffect",tolua_collect_MME__PostEffect);
   #else
   tolua_cclass(tolua_S,"PostEffect","MME::PostEffect","BaseEffect",NULL);
   #endif
   tolua_beginmodule(tolua_S,"PostEffect");
    tolua_function(tolua_S,"new",tolua_luafunc_MME_PostEffect_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_MME_PostEffect_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_MME_PostEffect_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_MME_PostEffect_delete00);
    tolua_function(tolua_S,"preDraw",tolua_luafunc_MME_PostEffect_preDraw00);
    tolua_function(tolua_S,"postDraw",tolua_luafunc_MME_PostEffect_postDraw00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"std",0);
  tolua_beginmodule(tolua_S,"std");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"shared_ptr_MME__PostEffect_","std::shared_ptr<MME::PostEffect>","",tolua_collect_std__shared_ptr_MME__PostEffect_);
   #else
   tolua_cclass(tolua_S,"shared_ptr_MME__PostEffect_","std::shared_ptr<MME::PostEffect>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"shared_ptr_MME__PostEffect_");
    tolua_function(tolua_S,"new",tolua_luafunc_std_shared_ptr_MME__PostEffect__new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_std_shared_ptr_MME__PostEffect__new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_std_shared_ptr_MME__PostEffect__new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_std_shared_ptr_MME__PostEffect__delete00);
    tolua_function(tolua_S,"reset",tolua_luafunc_std_shared_ptr_MME__PostEffect__reset00);
    tolua_function(tolua_S,"get",tolua_luafunc_std_shared_ptr_MME__PostEffect__get00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"D3DXMatrixIdentity",tolua_luafunc_D3DXMatrixIdentity00);
  tolua_function(tolua_S,"D3DXMatrixIsIdentity",tolua_luafunc_D3DXMatrixIsIdentity00);
  tolua_function(tolua_S,"D3DXMatrixLookAtLH",tolua_luafunc_D3DXMatrixLookAtLH00);
  tolua_function(tolua_S,"D3DXMatrixPerspectiveFovLH",tolua_luafunc_D3DXMatrixPerspectiveFovLH00);
  tolua_cclass(tolua_S,"btGhostPairCallback","btGhostPairCallback","",NULL);
  tolua_beginmodule(tolua_S,"btGhostPairCallback");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"btBroadphaseInterface","btBroadphaseInterface","",NULL);
  tolua_beginmodule(tolua_S,"btBroadphaseInterface");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"EventManager","EventManager","",NULL);
  tolua_beginmodule(tolua_S,"EventManager");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"BulletPhysics",0);
  tolua_beginmodule(tolua_S,"BulletPhysics");
   tolua_cclass(tolua_S,"FilterCallbackUsingGameObject","BulletPhysics::FilterCallbackUsingGameObject","",NULL);
   tolua_beginmodule(tolua_S,"FilterCallbackUsingGameObject");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CDxBulletDebugDrawer","BulletPhysics::CDxBulletDebugDrawer","",NULL);
   tolua_beginmodule(tolua_S,"CDxBulletDebugDrawer");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CDxBulletDebugDrawerEx","BulletPhysics::CDxBulletDebugDrawerEx","",NULL);
   tolua_beginmodule(tolua_S,"CDxBulletDebugDrawerEx");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CSegaBulletDebugDrawer","BulletPhysics::CSegaBulletDebugDrawer","",NULL);
   tolua_beginmodule(tolua_S,"CSegaBulletDebugDrawer");
   tolua_endmodule(tolua_S);
   tolua_constant(tolua_S,"GameWorldIndex",BulletPhysics::GameWorldIndex);
   tolua_constant(tolua_S,"CutSceneWorldIndex",BulletPhysics::CutSceneWorldIndex);
   tolua_constant(tolua_S,"DefaultFilter",BulletPhysics::DefaultFilter);
   tolua_constant(tolua_S,"StaticFilter",BulletPhysics::StaticFilter);
   tolua_constant(tolua_S,"KinematicFilter",BulletPhysics::KinematicFilter);
   tolua_constant(tolua_S,"DebrisFilter",BulletPhysics::DebrisFilter);
   tolua_constant(tolua_S,"SensorTrigger",BulletPhysics::SensorTrigger);
   tolua_constant(tolua_S,"CharacterFilter",BulletPhysics::CharacterFilter);
   tolua_constant(tolua_S,"MMDObjectFilter",BulletPhysics::MMDObjectFilter);
   tolua_constant(tolua_S,"PlayerFilter",BulletPhysics::PlayerFilter);
   tolua_constant(tolua_S,"EnemyFilter",BulletPhysics::EnemyFilter);
   tolua_constant(tolua_S,"BulletFilter",BulletPhysics::BulletFilter);
   tolua_constant(tolua_S,"AllFilter",BulletPhysics::AllFilter);
   tolua_constant(tolua_S,"AllFilterExceptMMDObject",BulletPhysics::AllFilterExceptMMDObject);
   tolua_constant(tolua_S,"DynamicFilter",BulletPhysics::DynamicFilter);
   tolua_cclass(tolua_S,"Manager","BulletPhysics::Manager","",NULL);
   tolua_beginmodule(tolua_S,"Manager");
    tolua_function(tolua_S,"instance",tolua_luafunc_BulletPhysics_Manager_instance00);
    tolua_function(tolua_S,"release",tolua_luafunc_BulletPhysics_Manager_release00);
    tolua_function(tolua_S,"addToWorld",tolua_luafunc_BulletPhysics_Manager_addToWorld00);
    tolua_function(tolua_S,"addToWorld",tolua_luafunc_BulletPhysics_Manager_addToWorld01);
    tolua_function(tolua_S,"addToWorld",tolua_luafunc_BulletPhysics_Manager_addToWorld02);
    tolua_function(tolua_S,"addToWorld",tolua_luafunc_BulletPhysics_Manager_addToWorld03);
    tolua_function(tolua_S,"addToWorld",tolua_luafunc_BulletPhysics_Manager_addToWorld04);
    tolua_function(tolua_S,"removeFromWorld",tolua_luafunc_BulletPhysics_Manager_removeFromWorld00);
    tolua_function(tolua_S,"removeFromWorld",tolua_luafunc_BulletPhysics_Manager_removeFromWorld01);
    tolua_function(tolua_S,"removeFromWorld",tolua_luafunc_BulletPhysics_Manager_removeFromWorld02);
    tolua_function(tolua_S,"update",tolua_luafunc_BulletPhysics_Manager_update00);
    tolua_function(tolua_S,"drawWorld",tolua_luafunc_BulletPhysics_Manager_drawWorld00);
    tolua_function(tolua_S,"drawObject",tolua_luafunc_BulletPhysics_Manager_drawObject00);
    tolua_function(tolua_S,"drawConstraint",tolua_luafunc_BulletPhysics_Manager_drawConstraint00);
    tolua_function(tolua_S,"clearForces",tolua_luafunc_BulletPhysics_Manager_clearForces00);
    tolua_function(tolua_S,"getWorldPtr",tolua_luafunc_BulletPhysics_Manager_getWorldPtr00);
    tolua_function(tolua_S,"getDebugDrawerPtr",tolua_luafunc_BulletPhysics_Manager_getDebugDrawerPtr00);
    tolua_function(tolua_S,"checkAllContactPoints",tolua_luafunc_BulletPhysics_Manager_checkAllContactPoints00);
    tolua_function(tolua_S,"getNumberCollisionObjects",tolua_luafunc_BulletPhysics_Manager_getNumberCollisionObjects00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MMD",0);
  tolua_beginmodule(tolua_S,"MMD");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"XmlLoader",0);
  tolua_beginmodule(tolua_S,"XmlLoader");
   tolua_module(tolua_S,"GameObject",0);
   tolua_beginmodule(tolua_S,"GameObject");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObject",0);
  tolua_beginmodule(tolua_S,"GameObject");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Sequence",0);
  tolua_beginmodule(tolua_S,"Sequence");
   tolua_module(tolua_S,"HatuneOfTheDead",0);
   tolua_beginmodule(tolua_S,"HatuneOfTheDead");
    tolua_module(tolua_S,"LuaImpl",0);
    tolua_beginmodule(tolua_S,"LuaImpl");
     tolua_cclass(tolua_S,"Resource","Sequence::HatuneOfTheDead::LuaImpl::Resource","",NULL);
     tolua_beginmodule(tolua_S,"Resource");
      tolua_function(tolua_S,"instance",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_instance00);
      tolua_function(tolua_S,"release",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_release00);
      tolua_function(tolua_S,"isReady",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_isReady00);
      tolua_function(tolua_S,"loadEnemy",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadEnemy00);
      tolua_function(tolua_S,"loadPlayer",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadPlayer00);
      tolua_function(tolua_S,"loadCameraAnimation",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadCameraAnimation00);
      tolua_function(tolua_S,"loadStage",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_loadStage00);
      tolua_function(tolua_S,"instancePlayer",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_instancePlayer00);
      tolua_function(tolua_S,"getStage",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_getStage00);
      tolua_function(tolua_S,"getEnemies",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_getEnemies00);
      tolua_function(tolua_S,"getCameraAnimation",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_Resource_getCameraAnimation00);
     tolua_endmodule(tolua_S);
     tolua_cclass(tolua_S,"State","Sequence::HatuneOfTheDead::LuaImpl::State","",NULL);
     tolua_beginmodule(tolua_S,"State");
      tolua_function(tolua_S,"instance",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_instance00);
      tolua_function(tolua_S,"release",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_release00);
      tolua_function(tolua_S,"isReady",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_isReady00);
      tolua_function(tolua_S,"isClear",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_isClear00);
      tolua_function(tolua_S,"update",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_update00);
      tolua_function(tolua_S,"draw",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_draw00);
      tolua_function(tolua_S,"reserveEnemySpawn",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_reserveEnemySpawn00);
      tolua_function(tolua_S,"build",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_build00);
      tolua_function(tolua_S,"getPlayer",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_getPlayer00);
      tolua_function(tolua_S,"setNextSequence",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_setNextSequence00);
      tolua_function(tolua_S,"getNextSequence",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_getNextSequence00);
      tolua_function(tolua_S,"needDrawCall",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_needDrawCall00);
      tolua_function(tolua_S,"setNeedDrawCall",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_setNeedDrawCall00);
      tolua_function(tolua_S,"resetAll",tolua_luafunc_Sequence_HatuneOfTheDead_LuaImpl_State_resetAll00);
     tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"HOD",0);
  tolua_beginmodule(tolua_S,"HOD");
   tolua_cclass(tolua_S,"EnemyManager","HOD::EnemyManager","",NULL);
   tolua_beginmodule(tolua_S,"EnemyManager");
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"EnemySpawner","HOD::EnemySpawner","",tolua_collect_HOD__EnemySpawner);
   #else
   tolua_cclass(tolua_S,"EnemySpawner","HOD::EnemySpawner","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"EnemySpawner");
    tolua_function(tolua_S,"new",tolua_luafunc_HOD_EnemySpawner_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_HOD_EnemySpawner_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_HOD_EnemySpawner_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_HOD_EnemySpawner_delete00);
    tolua_function(tolua_S,"update",tolua_luafunc_HOD_EnemySpawner_update00);
    tolua_function(tolua_S,"loadEnemy",tolua_luafunc_HOD_EnemySpawner_loadEnemy00);
    tolua_function(tolua_S,"isReady",tolua_luafunc_HOD_EnemySpawner_isReady00);
    tolua_function(tolua_S,"reserve",tolua_luafunc_HOD_EnemySpawner_reserve00);
    tolua_function(tolua_S,"registerEnemy",tolua_luafunc_HOD_EnemySpawner_registerEnemy00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MMD",0);
  tolua_beginmodule(tolua_S,"MMD");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"XmlLoader",0);
  tolua_beginmodule(tolua_S,"XmlLoader");
   tolua_module(tolua_S,"GameObject",0);
   tolua_beginmodule(tolua_S,"GameObject");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObject",0);
  tolua_beginmodule(tolua_S,"GameObject");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Stage","GameObject::Stage","GameObject::BaseObject",tolua_collect_GameObject__Stage);
   #else
   tolua_cclass(tolua_S,"Stage","GameObject::Stage","GameObject::BaseObject",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Stage");
    tolua_function(tolua_S,"create",tolua_luafunc_GameObject_Stage_create00);
    tolua_function(tolua_S,"delete",tolua_luafunc_GameObject_Stage_delete00);
    tolua_function(tolua_S,"drawUsingGameLib",tolua_luafunc_GameObject_Stage_drawUsingGameLib00);
    tolua_function(tolua_S,"createBvhTriangleMesh",tolua_luafunc_GameObject_Stage_createBvhTriangleMesh00);
    tolua_function(tolua_S,"getRTTI",tolua_luafunc_GameObject_Stage_getRTTI00);
    tolua_variable(tolua_S,"rtti",tolua_get_GameObject__Stage_rtti,NULL);
    tolua_function(tolua_S,"getBtCollisionObject",tolua_luafunc_GameObject_Stage_getBtCollisionObject00);
    tolua_function(tolua_S,"removeFromWorld",tolua_luafunc_GameObject_Stage_removeFromWorld00);
    tolua_function(tolua_S,"addToWorld",tolua_luafunc_GameObject_Stage_addToWorld00);
    tolua_function(tolua_S,"isClear",tolua_luafunc_GameObject_Stage_isClear00);
    tolua_function(tolua_S,"handleEventThatDefeatedAllEnemies",tolua_luafunc_GameObject_Stage_handleEventThatDefeatedAllEnemies00);
    tolua_function(tolua_S,"isReady",tolua_luafunc_GameObject_Stage_isReady00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Sequence",0);
  tolua_beginmodule(tolua_S,"Sequence");
   tolua_module(tolua_S,"HatuneOfTheDead",0);
   tolua_beginmodule(tolua_S,"HatuneOfTheDead");
    tolua_module(tolua_S,"LuaImpl",0);
    tolua_beginmodule(tolua_S,"LuaImpl");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Camera",0);
  tolua_beginmodule(tolua_S,"Camera");
   tolua_cclass(tolua_S,"ICamera","Camera::ICamera","",NULL);
   tolua_beginmodule(tolua_S,"ICamera");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"PlayerCamera","Camera::PlayerCamera","",NULL);
   tolua_beginmodule(tolua_S,"PlayerCamera");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Simple","Camera::Simple","",NULL);
   tolua_beginmodule(tolua_S,"Simple");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GUI",0);
  tolua_beginmodule(tolua_S,"GUI");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"XmlLoader",0);
  tolua_beginmodule(tolua_S,"XmlLoader");
   tolua_cclass(tolua_S,"Actions","XmlLoader::Actions","",NULL);
   tolua_beginmodule(tolua_S,"Actions");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObjectData",0);
  tolua_beginmodule(tolua_S,"GameObjectData");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"btRigidBody","btRigidBody","",NULL);
  tolua_beginmodule(tolua_S,"btRigidBody");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"btCollisionShape","btCollisionShape","",NULL);
  tolua_beginmodule(tolua_S,"btCollisionShape");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"btCylinderShape","btCylinderShape","",NULL);
  tolua_beginmodule(tolua_S,"btCylinderShape");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"btMotionState","btMotionState","",NULL);
  tolua_beginmodule(tolua_S,"btMotionState");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MME",0);
  tolua_beginmodule(tolua_S,"MME");
   tolua_module(tolua_S,"Object",0);
   tolua_beginmodule(tolua_S,"Object");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Component",0);
  tolua_beginmodule(tolua_S,"Component");
   tolua_cclass(tolua_S,"RigidBodyComponent","Component::RigidBodyComponent","",NULL);
   tolua_beginmodule(tolua_S,"RigidBodyComponent");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObject",0);
  tolua_beginmodule(tolua_S,"GameObject");
   tolua_module(tolua_S,"Utils",0);
   tolua_beginmodule(tolua_S,"Utils");
    tolua_cclass(tolua_S,"Character","GameObject::Utils::Character","",NULL);
    tolua_beginmodule(tolua_S,"Character");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"std",0);
  tolua_beginmodule(tolua_S,"std");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"shared_ptr_GameObject__Player_","std::shared_ptr<GameObject::Player>","",tolua_collect_std__shared_ptr_GameObject__Player_);
   #else
   tolua_cclass(tolua_S,"shared_ptr_GameObject__Player_","std::shared_ptr<GameObject::Player>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"shared_ptr_GameObject__Player_");
    tolua_function(tolua_S,"new",tolua_luafunc_std_shared_ptr_GameObject__Player__new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_std_shared_ptr_GameObject__Player__new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_std_shared_ptr_GameObject__Player__new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_std_shared_ptr_GameObject__Player__delete00);
    tolua_function(tolua_S,"reset",tolua_luafunc_std_shared_ptr_GameObject__Player__reset00);
    tolua_function(tolua_S,"get",tolua_luafunc_std_shared_ptr_GameObject__Player__get00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"btSphereShape","btSphereShape","",NULL);
  tolua_beginmodule(tolua_S,"btSphereShape");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"btBoxShape","btBoxShape","",NULL);
  tolua_beginmodule(tolua_S,"btBoxShape");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObjectData",0);
  tolua_beginmodule(tolua_S,"GameObjectData");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GUI",0);
  tolua_beginmodule(tolua_S,"GUI");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MMD",0);
  tolua_beginmodule(tolua_S,"MMD");
   tolua_cclass(tolua_S,"HumanModel","MMD::HumanModel","",NULL);
   tolua_beginmodule(tolua_S,"HumanModel");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MME",0);
  tolua_beginmodule(tolua_S,"MME");
   tolua_module(tolua_S,"Object",0);
   tolua_beginmodule(tolua_S,"Object");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Component",0);
  tolua_beginmodule(tolua_S,"Component");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObject",0);
  tolua_beginmodule(tolua_S,"GameObject");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"std",0);
  tolua_beginmodule(tolua_S,"std");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"shared_ptr_GameObject__Enemy_","std::shared_ptr<GameObject::Enemy>","",tolua_collect_std__shared_ptr_GameObject__Enemy_);
   #else
   tolua_cclass(tolua_S,"shared_ptr_GameObject__Enemy_","std::shared_ptr<GameObject::Enemy>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"shared_ptr_GameObject__Enemy_");
    tolua_function(tolua_S,"new",tolua_luafunc_std_shared_ptr_GameObject__Enemy__new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_std_shared_ptr_GameObject__Enemy__new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_std_shared_ptr_GameObject__Enemy__new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_std_shared_ptr_GameObject__Enemy__delete00);
    tolua_function(tolua_S,"reset",tolua_luafunc_std_shared_ptr_GameObject__Enemy__reset00);
    tolua_function(tolua_S,"get",tolua_luafunc_std_shared_ptr_GameObject__Enemy__get00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"MME",0);
  tolua_beginmodule(tolua_S,"MME");
   tolua_module(tolua_S,"Object",0);
   tolua_beginmodule(tolua_S,"Object");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameLib",0);
  tolua_beginmodule(tolua_S,"GameLib");
   tolua_module(tolua_S,"Math",0);
   tolua_beginmodule(tolua_S,"Math");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObject",0);
  tolua_beginmodule(tolua_S,"GameObject");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"std",0);
  tolua_beginmodule(tolua_S,"std");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"shared_ptr_GameObject__Stage_","std::shared_ptr<GameObject::Stage>","",tolua_collect_std__shared_ptr_GameObject__Stage_);
   #else
   tolua_cclass(tolua_S,"shared_ptr_GameObject__Stage_","std::shared_ptr<GameObject::Stage>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"shared_ptr_GameObject__Stage_");
    tolua_function(tolua_S,"new",tolua_luafunc_std_shared_ptr_GameObject__Stage__new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_std_shared_ptr_GameObject__Stage__new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_std_shared_ptr_GameObject__Stage__new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_std_shared_ptr_GameObject__Stage__delete00);
    tolua_function(tolua_S,"reset",tolua_luafunc_std_shared_ptr_GameObject__Stage__reset00);
    tolua_function(tolua_S,"get",tolua_luafunc_std_shared_ptr_GameObject__Stage__get00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Camera",0);
  tolua_beginmodule(tolua_S,"Camera");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"FixedCamera","Camera::FixedCamera","Camera::ICamera",tolua_collect_Camera__FixedCamera);
   #else
   tolua_cclass(tolua_S,"FixedCamera","Camera::FixedCamera","Camera::ICamera",NULL);
   #endif
   tolua_beginmodule(tolua_S,"FixedCamera");
    tolua_function(tolua_S,"new",tolua_luafunc_Camera_FixedCamera_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_Camera_FixedCamera_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_Camera_FixedCamera_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_Camera_FixedCamera_delete00);
    tolua_function(tolua_S,"update",tolua_luafunc_Camera_FixedCamera_update00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"GameObject",0);
  tolua_beginmodule(tolua_S,"GameObject");
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"XmlLoader",0);
  tolua_beginmodule(tolua_S,"XmlLoader");
   tolua_module(tolua_S,"GameObject",0);
   tolua_beginmodule(tolua_S,"GameObject");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"HOD",0);
  tolua_beginmodule(tolua_S,"HOD");
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_luafunc (lua_State* tolua_S) {
 return tolua_luafunc_open(tolua_S);
};
#endif

