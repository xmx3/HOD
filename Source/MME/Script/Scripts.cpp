#include"Scripts.h"
#include"MME/BaseEffect.h"
#include"MME/BaseTechnique.h"
#include"MME/PostTechnique.h"
#include"MME/RenderTarget.h"
#include"MME/RenderDepthStencil.h"
#include"MME/Pass.h"
#include"MME/Manager.h"
#include<assert.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/GameLib.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/Vertex.h>
#include"helper/parseEquals.h"

namespace MME {
	class BaseEffect;
namespace Script{


class SetRenderColorTarget : public IScript {
public:
	SetRenderColorTarget(
		ID3DXEffect *effect,
		BaseEffect *mme,
		const std::string &targetName,
		int targetIndex )
		:mTargetIndex(targetIndex),
		mRenderTarget(NULL),
		mEffect(mme)
	{
		if( !targetName.empty() ){
			mRenderTarget = mme->findRenderTarget( targetName );
			assert( mRenderTarget );
			if( mRenderTarget==0 ){
				mEffect=0;
			}
		}
	}
	virtual ~SetRenderColorTarget(){
		mRenderTarget=0;
		mEffect=0;
	}

	virtual void exec(){
		//mRenderTarget==NULL だと デフォルトに戻す
		mEffect->setRenderTarget( mTargetIndex, mRenderTarget.get() );
	}

	virtual bool isValid()const{
		return mEffect!=0;
	}
private:
	RenderTargetSharedPtr mRenderTarget;
	int mTargetIndex;
	BaseEffect *mEffect;
};

class SetRenderDepthStencilTarget : public IScript {
public:
	SetRenderDepthStencilTarget(
		ID3DXEffect *effect,
		BaseEffect *mme,
		const std::string &targetName )
		:mRenderDepthStencil(NULL),
		mEffect(mme)
	{
		if( !targetName.empty() ){
			mRenderDepthStencil = mme->findRenderDepthStencil( targetName );
			assert( mRenderDepthStencil );
			if( mRenderDepthStencil==0 ){
				mEffect=0;
			}
		}
	}
	virtual ~SetRenderDepthStencilTarget(){
		mRenderDepthStencil=0;
		mEffect=0;
	}

	virtual void exec(){
		//mRenderDepthStencil==NULL だと デフォルトに戻す
		mEffect->setRenderDepthStencil( mRenderDepthStencil.get() );
	}
	virtual bool isValid()const{
		return mEffect!=0;
	}
private:
	RenderDepthStencilSharedPtr mRenderDepthStencil;
	BaseEffect *mEffect;
};

class ClearColor : public IScript{
public:
	ClearColor(){}
	virtual ~ClearColor(){}
	virtual void exec(){
		HRESULT hr;
		IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
		hr=pDevice->Clear(
			0,
			NULL,
			D3DCLEAR_TARGET,
			msColor,
			1.f,
			0 );
		assert(SUCCEEDED(hr));
	}
	static void setColor( const DWORD &color ){
		msColor = color;
	}
private:
	static DWORD msColor;
};

DWORD ClearColor::msColor=0xffffffff;

class ClearDepth : public IScript {
public:
	ClearDepth()
	{}
	virtual ~ClearDepth(){}
	virtual void exec(){
		HRESULT hr;
		IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
		hr=pDevice->Clear(
			0,
			NULL,//rect
			D3DCLEAR_ZBUFFER ,
			0,//color
			msZ,//
			0 );//stencil 

		assert(SUCCEEDED(hr));
	}
	static void setDepth( const float depth ){
		msZ=depth;
	}
private:
	static float msZ;
};
float ClearDepth::msZ=1.f;


class ClearSetColor : public IScript {
public:
	ClearSetColor( ID3DXEffect *effect, const std::string &colorName )
		:mColor( 0xffffffff )
	{
		float clearColor[4]={1.f};
		HRESULT hr;
		D3DXHANDLE h=effect->GetParameterByName( 0, colorName.c_str() );
		assert(h);
		if(h){
			hr=effect->GetFloatArray( h, clearColor, 4 );
			assert( SUCCEEDED(hr) );
			mColor = D3DCOLOR_COLORVALUE( clearColor[0], clearColor[1], clearColor[2], clearColor[3] );
		}
	}
	virtual ~ClearSetColor(){}

	virtual void exec(){
		ClearColor::setColor(mColor);
	}
private:
	DWORD mColor;
};


class ClearSetDepth : public IScript {
public:
	ClearSetDepth( ID3DXEffect *effect, const std::string &depthName )
		:mZ( 1.f )
	{
		HRESULT hr;
		D3DXHANDLE h=effect->GetParameterByName( 0, depthName.c_str() );
		assert(h);
		if(h){
			hr=effect->GetFloat( h, &mZ );
			assert( SUCCEEDED(hr) );
		}
	}

	virtual ~ClearSetDepth(){}

	virtual void exec(){
		ClearDepth::setDepth(mZ);
	}
private:
	float mZ;
};

PassScript::PassScript( BaseTechnique *tech, const std::string &passName )
	:mPass(0)
{
	mPass = tech->findPass( passName );
	assert( mPass && "pass is not found." );
}

void PassScript::exec(){
	mPass->exec();
}



class LoopByCount;

class LoopGetIndex : public IScript {
public:
	LoopGetIndex( ID3DXEffect *effect, const std::string &indexName, LoopByCount *loop )
		:mLoop(loop),
		mIndex(0),
		mhIndex(0)
	{
		D3DXHANDLE h = effect->GetParameterByName( 0, indexName.c_str() );
		if(h){
			HRESULT hr;

			D3DXPARAMETER_DESC desc;
			hr=effect->GetParameterDesc( h, &desc );
			assert( SUCCEEDED(hr) );
			switch(desc.Type){
			case D3DXPT_BOOL :
				BOOL b;
				hr = effect->GetBool( h, &b );
				mIndex = static_cast<int>(b);
				assert( SUCCEEDED(hr) );
				assert( false );
				break;
			case D3DXPT_INT :
				hr = effect->GetInt( h, &mIndex );
				assert( SUCCEEDED(hr) );
				mhIndex = h;
				break;
			case D3DXPT_FLOAT :
				float f;
				hr = effect->GetFloat( h, &f );
				assert( SUCCEEDED(hr) );
				mIndex = static_cast<int>(f);
				assert( false );
				break;
			default :
				assert( false && "LoopGetIndex's variable type is wrong. can use float, bool, int. index was seted 0" );
				break;
			}
		} else{
			assert( false && "LoopGetIndex's variable is not found. seted 0" );
		}
	
	}
	virtual ~LoopGetIndex(){}
	//LoopByCountが必要なので下に定義してある
	virtual void exec();
	int getIndex()const{
		return mIndex;
	}
	D3DXHANDLE getHandle()const{
		return mhIndex;
	}
private:
	LoopByCount *mLoop;
	int mIndex;
	D3DXHANDLE mhIndex;

};

class LoopByCount : public IScript {
public:
	LoopByCount(
		const char *currentExpression,
		const char **ppNext,
		const std::string &loopCountName,
		ID3DXEffect *effect,
		BaseEffect *mme,
		BaseTechnique *technique )
		:mEffect(effect),
		mIsValid(false),
		mIndex(0),
		mEnd(0),
		mBegin(0),
		mhIndex(0)
	{
		D3DXHANDLE h = effect->GetParameterByName( 0, loopCountName.c_str() );
		if(h){
			HRESULT hr;

			D3DXPARAMETER_DESC desc;
			hr=effect->GetParameterDesc( h, &desc );
			assert( SUCCEEDED(hr) );
			switch(desc.Type){
			case D3DXPT_BOOL :
				BOOL b;
				hr = effect->GetBool( h, &b );
				mEnd = static_cast<int>(b);
				assert( SUCCEEDED(hr) );
				break;
			case D3DXPT_INT :
				hr = effect->GetInt( h, &mEnd );
				assert( SUCCEEDED(hr) );
				break;
			case D3DXPT_FLOAT :
				float f;
				hr = effect->GetFloat( h, &f );
				assert( SUCCEEDED(hr) );
				mEnd = static_cast<int>(f);
				break;
			default :
				assert( false && "LoopByCount's variable type is wrong. can use float, bool, int. loopcount was seted 0" );
				break;
			}
		}
		
		while( *ppNext!='\0'){
			IScript *s = createScript( ppNext, currentExpression, effect, mme, technique ); 
			if(s){
				if(LoopGetIndex *gi=dynamic_cast<LoopGetIndex*>(s) ){
					mBegin = gi->getIndex();
					mhIndex = gi->getHandle();
					delete s;
					s=0;
				} else{
					mScripts.push_back( s );
				}
				currentExpression = *ppNext;
			}
			else{
				assert( mIsValid && "loop didn't close;." );
				mScripts.shrink_to_fit();
				return;
			}
		}
		assert( mIsValid && "loop didn't close;." );
	}
	
	virtual ~LoopByCount(){
		for( int is=0, ssize=mScripts.size(); is<ssize; ++is ){
			SAFE_DELETE( mScripts[is] );
		}
		mScripts.clear();
		mScripts.shrink_to_fit();
	}
	
	void setIndex(int index){
		mIndex=index;
	}
	virtual void exec(){
		for( ; mIndex<mEnd; ++mIndex ){
			for( int is=0, ssize=mScripts.size(); is<ssize; ++is ){
				if( mhIndex ){
					HRESULT hr = mEffect->SetInt( mhIndex, mIndex );
					assert( SUCCEEDED(hr) );
				}
				mScripts[is]->exec();
			}
		}
		mIndex=mBegin;
	}
	virtual bool isValid()const{
		return mIsValid;
	}
private:
	IScript* createScript(
		const char **ppNextExpression,
		const char *pExpression,
		ID3DXEffect *effect,
		BaseEffect *mme,
		BaseTechnique *technique )
	{
		IScript* script = 
			MME::Script::createScript( pExpression, ppNextExpression, effect, mme, technique );
		if(script){
			return script;
		} else {
			std::string command, operand;
			*ppNextExpression = parseEquals( pExpression, &command, &operand );
			if( command=="LoopEnd" ){
				assert( operand.empty() );
				mIsValid=true;
				return NULL;
			} else if( command=="LoopGetIndex" ){
				script = NEW LoopGetIndex( effect, operand, this ); 
				return script;
			}else {
				assert(false && "there is unknown command. script be wrong!");
				return NULL;
			}
		}
	}
private:
	ID3DXEffect *mEffect;
	bool mIsValid;
	int mIndex;
	int mEnd;
	int mBegin;
	D3DXHANDLE mhIndex;
	std::vector<IScript*> mScripts; 
};

void LoopGetIndex::exec(){
	mLoop->setIndex( mIndex );
}

void DrawGeometry::exec(){
	mEffect->drawGeometry();
}

class DrawBuffer : public IScript{
public:
	DrawBuffer( BaseEffect *effect )
		:mEffect(effect)
	{
		if( !msVb ){
			msVb = GameLib::Graphics::VertexBuffer::create( 6 );
			GameLib::Graphics::Vertex *v;
			static const unsigned int c = 0;
			v = msVb.lock();
			v[0].mPosition.set( -1.f, 1.f, 0, 1.f);
			v[0].mUv.set( 0.f, 0.f );
			v[0].mColor = c;

			v[1].mPosition.set( 1.f, 1.f, 0, 1.f);
			v[1].mUv.set( 1.f, 0.f );
			v[1].mColor = c;

			v[2].mPosition.set( 1.f, -1.f, 0, 1.f);
			v[2].mUv.set( 1.f, 1.f );
			v[2].mColor = c;

			v[3].mPosition.set( -1.f, 1.f, 0, 1.f);
			v[3].mUv.set( 0.f, 0.f );
			v[3].mColor = c;

			v[4].mPosition.set( 1.0, -1.0, 0, 1.f);
			v[4].mUv.set( 1.f, 1.f );
			v[4].mColor = c;

			v[5].mPosition.set( -1.f, -1.f, 0, 1.f);
			v[5].mUv.set( 0.f, 1.f );
			v[5].mColor = c;
	
			msVb.unlock( &v );
		}
	}
	virtual ~DrawBuffer(){}
	virtual void exec(){

		Manager *m = Manager::instance();
		
		m->enableVertexBlend(false);
		m->setVertexBuffer( msVb );
		//mEffect->setTextures();

		m->draw( 0, 2 );
	}
private:
	BaseEffect *mEffect;
	static GameLib::Graphics::VertexBuffer msVb;
};
GameLib::Graphics::VertexBuffer DrawBuffer::msVb;

//スクリプトが間違っていたらNULLを返す
IScript* createScript(
	const char *pExpression,
	const char **ppNextExpression,
	ID3DXEffect *effect,
	BaseEffect *mme,
	BaseTechnique *technique )
{
	std::string command, operand;
	*ppNextExpression = parseEquals( pExpression, &command, &operand );

	if( command=="RenderColorTarget" ){
		SetRenderColorTarget *s = NEW SetRenderColorTarget( effect, mme, operand, 0 );
		if(s->isValid()){
			return s;
		} else {
			delete s;
			s=0;
			return NULL;
		}
	} else if( command=="RenderColorTarget0" ){
		SetRenderColorTarget *s = NEW SetRenderColorTarget( effect, mme, operand, 0 );
		if(s->isValid()){
			return s;
		} else {
			delete s;
			s=0;
			return NULL;
		}
	} else if( command=="RenderColorTarget1" ){
		SetRenderColorTarget *s = NEW SetRenderColorTarget( effect, mme, operand, 1 );
		if(s->isValid()){
			return s;
		} else {
			delete s;
			s=0;
			return NULL;
		}
	} else if( command=="RenderColorTarget2" ){
		SetRenderColorTarget *s = NEW SetRenderColorTarget( effect, mme, operand, 2 );
		if(s->isValid()){
			return s;
		} else {
			delete s;
			s=0;
			return NULL;
		}
	} else if( command=="RenderColorTarget3" ){
		SetRenderColorTarget *s = NEW SetRenderColorTarget( effect, mme, operand, 3 );
		if(s->isValid()){
			return s;
		} else {
			delete s;
			s=0;
			return NULL;
		}
	} else if( command=="RenderDepthStencilTarget" ){
		SetRenderDepthStencilTarget *s = NEW SetRenderDepthStencilTarget( effect, mme, operand );
		if(s->isValid()){
			return s;
		} else {
			delete s;
			s=0;
			return NULL;
		}
	} else if( command=="ClearSetColor" ){
		ClearSetColor *s = NEW ClearSetColor( effect, operand );
		return s;
	} else if( command=="ClearSetDepth" ){
		ClearSetDepth *s = NEW ClearSetDepth( effect, operand );
		return s;
	} else if( command=="Clear" ){
		if( operand=="Color" ){
			return NEW ClearColor();
		} else if( operand=="Depth" ) {
			return NEW ClearDepth();
		} else {
			assert( false && "Clear= is wrong" );
			return NULL;
		}
	} else if( command=="ScriptExternal" ){
		assert( technique && "このコマンドは、テクニックのスクリプト上でしか使用できない。" );
		
		if(technique==NULL){
			return NULL;
		}
		//このコマンドは、テクニックのスクリプト上でしか使用できない。
		//これは、ポストエフェクト（STANDARDSGLOBALパラメータのScriptOrderアノテーションに
		//　"postprocess"が指定されたエフェクトファイル）でのみ実行できる。
		PostTechnique *postTech = dynamic_cast<PostTechnique*>(technique);
		if(postTech){
			return NEW ScriptExternal();
		} else {
			assert(false &&
				"これは、ポストエフェクト（STANDARDSGLOBALパラメータのScriptOrderアノテーションに\
				\"postprocess\"が指定されたエフェクトファイル）でのみ実行できる。" );
			return NULL;
		}
	} else if( command=="Pass" ){
		assert( technique && "このコマンドは、テクニックのスクリプト上でしか使用できない。" );
		if(technique==NULL){
			return NULL;
		}
		PassScript *s = NEW PassScript( technique, operand );
		if(s->isValid()){
			return s;
		} else {
			delete s;
			s=0;
			return NULL;
		}
	} else if( command=="LoopByCount" ){
		LoopByCount *s = 
				NEW LoopByCount(
				*ppNextExpression,
				ppNextExpression,
				operand,
				effect,
				mme,
				technique );
		if(s->isValid()){
			return s;
		} else {
			delete s;
			s=0;
			return NULL;
		}
	} else if( command=="Draw" ){
		assert( !technique && "このコマンドは、パスのスクリプト上でしか使用できない。" );
		if(technique){
			return NULL;
		}

		if( operand=="Geometry" ){
			return NEW DrawGeometry( mme );
		} else if( operand == "Buffer") {
			return NEW DrawBuffer( mme );
		} else{
			assert( false && "unknown command(draw=)" );
			return NULL;
		}
	} else if( command == "LoopGetIndex"){
		return NULL;//LoopByCountにおまかせ
	} else if( command == "LoopEnd"){
		return NULL;//LoopByCountにおまかせ
	} else {
		assert( false && "unknown command" );
		return NULL;
	}
}

}//end namespace Script
}//end namespace MME
