#pragma once
#include<d3dx9.h>
#include<string>
#include"Script/Scripts.h"
#include"helper/MyOutputDebugString.h"
#include<GameLib/Graphics/Manager.h>


namespace MME{
	class IScript;
	class Pass;
	class BaseEffect;
class Pass {
public:
	Pass( ID3DXEffect *effect, D3DXHANDLE hPass, int index, BaseEffect *mme )
		:mHandle(hPass), mIndex(index), mEffect(effect)
	{
		HRESULT hr;
		D3DXPASS_DESC passDesc;
		hr=effect->GetPassDesc( hPass, &passDesc );
		assert( SUCCEEDED(hr) );
		mName.assign(passDesc.Name);


		D3DXHANDLE hScript = effect->GetAnnotationByName( hPass, "Script" );

		if(hScript){
			const char *scriptText = NULL;
			hr=effect->GetString( hScript, &scriptText );
			assert(SUCCEEDED(hr));

			const char *next=scriptText;
			
			assert(next!='\0');

			while( Script::isValid( next ) ){
				Script::IScript* s = Script::createScript(  next, &next, effect, mme, NULL );
				if(s==NULL){
					mHandle=NULL;
					return;
				}
				mScripts.push_back( s );
			}
		}
		//また、パスのスクリプトを省略した場合、"Draw=Geometry"が実行される
		else {
			Script::IScript *s = new Script::DrawGeometry( mme );
			mScripts.push_back(s);
		}
		mScripts.shrink_to_fit();
	}
	~Pass(){
		for( int i=0, size=mScripts.size(); i<size; ++i ){
			delete mScripts[i];
			mScripts[i]=0;
		}
		mScripts.clear();
		mScripts.shrink_to_fit();
	}
	void exec(){
		HRESULT hr;
		//TRACE1( "begin pass %s.\n", mName.c_str() );
		hr=mEffect->BeginPass(mIndex);

		//GameLib::Graphics::Manager m;
		//LPDIRECT3DDEVICE9 pDevice = m.dxDevice();
		//DWORD flag;
		//pDevice->GetRenderState( D3DRS_ALPHABLENDENABLE, &flag );

		assert( SUCCEEDED(hr) );
		for( int i=0, size=mScripts.size(); i<size; ++i ){
			mScripts[i]->exec();
		}
		hr=mEffect->EndPass();
		assert( SUCCEEDED(hr) );

	}
	bool isError()const{
		return mHandle==NULL;
	}
	const std::string & getName()const{
		return mName;
	}
private:
	D3DXHANDLE mHandle;
	ID3DXEffect *mEffect;
	std::string mName;
	int mIndex;
	std::vector<Script::IScript*> mScripts;

};
}