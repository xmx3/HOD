#include"PointLight.h"
#include<assert.h>
#include"MME/Manager.h"
#include<GameLib/FileIO/InFile.h>
#include"MME/PostEffect.h"

namespace MME{ namespace Object{ //MME::Object
static const char *shaderFile="ShaderTest/Basic/DSPoinghtLight.fx";
std::unique_ptr<XFile::Model> PointLight::msModel=NULL; 
PostEffectSharedPtr PointLight::msEffect=NULL;
bool PointLight::msIsReady=false;
D3DXHANDLE PointLight::msLightColorHandle		= NULL;
D3DXHANDLE PointLight::msLightPositionHandle	= NULL;
D3DXHANDLE PointLight::msLightRangeHandle		= NULL;
D3DXHANDLE PointLight::msShadowParamsHandle		= NULL;

PointLightSharedPtr PointLight::create( const D3DXVECTOR3 &pos, float range, const D3DXVECTOR4 &color){
	assert( isReady() );
	while(!isReady() ){}
	PointLightSharedPtr lp = std::make_shared<PointLight>( pos, range, color );
	return lp;
}

PointLight::PointLight( const D3DXVECTOR3 &pos, float range , const D3DXVECTOR4 &color )
	:mPos(pos,0.f),
	mRange(range, 1.0f/range, 0.f, 0.f),
	mColor(color),
	mShadowParam( 1.0f, 10.0f, 0.f, 0.f )
{
	mTransform._41 = pos.x;
	mTransform._42 = pos.y;
	mTransform._43 = pos.z;
}

PointLight::~PointLight(){


}

bool PointLight::isReady(){
	if(msIsReady){
		return msIsReady;
	} else {

		if( !msModel ){
			msModel.reset( new XFile::Model("Data/Model/Primitive/sphere.x") );
		}
		
		if( msModel->isFinished() ){
			MME::Manager *m=MME::Manager::instance();
			msEffect = m->findPostEffect( shaderFile );
			msLightColorHandle		= msEffect->getHandle("_LightColor");
			msLightPositionHandle	= msEffect->getHandle("_LightPosition");
			msLightRangeHandle		= msEffect->getHandle("_LightRange");
			//msShadowParamsHandle	= msEffect->getHandle("_ShadowParams");

			msIsReady=true;
			return msIsReady;
		}
		return msIsReady;
	}
}
	

void PointLight::draw()const{
	MME::Manager * m = ::MME::Manager::instance();
	MME::MMDPass pass;
	MME::UseTexture tex;
	MME::UseSphereMap sphere;
	MME::UseToon toon;
	MME::UseSelfShadow selfShadow;

	m->getCurrentPass( &pass, &tex, &sphere, &toon, &selfShadow );

	//posteFFECTなので全部falseのはず
	//けど使用かえるかもね、いやそれはないだろう　この機能のためにステート切り替え何回もするの馬鹿らしい
	//だったらここでコントロールするべき
	assert( !tex && !sphere && !toon && !selfShadow );
	assert( pass == MP_OBJECT );

	if( mCanDraw && mCanDrawMMDPass[pass] ) {
		msEffect->setFloatArray( msLightColorHandle		, mColor, 4 );
		msEffect->setFloatArray( msLightPositionHandle	, mPos, 4 );
		msEffect->setFloatArray( msLightRangeHandle		, mRange, 4 );
		//msEffect->setFloatArray( msShadowParamsHandle	, mShadowParam, 4 );

		msModel->drawByMME( mTransform );
	}
}

float PointLight::getFaceValue(const std::string &faceName )const
{
	return 0.0;
}

const D3DXMATRIX & PointLight::getBoneMatrix( const std::string &boneName )const
{
	static const  D3DXMATRIX matI( 
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
			);
	return matI;
}

float PointLight::getScale()const
{
	return 1.0;
}

const std::string& PointLight::getModelFileName()const
{
	return msModel->getFileName();
}

void PointLight::destroy(){
	msModel.reset();
	msEffect.reset();
	msIsReady = false;
	msLightColorHandle		= NULL;
	msLightPositionHandle	= NULL;
	msLightRangeHandle		= NULL;
	msShadowParamsHandle	= NULL;
}

}}// end namespace MME::Object