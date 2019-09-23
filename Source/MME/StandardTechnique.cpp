#include"StandardTechnique.h"
#include<assert.h>
#include"Script/Scripts.h"
#include<GameLib/GameLib.h>
#include"BaseEffect.h"
namespace MME {

StandardTechnique::StandardTechnique( ID3DXEffect *effect, D3DXHANDLE hTech, BaseEffect *mme )
	:BaseTechnique( effect, hTech, mme )
{
	HRESULT hr;
	D3DXHANDLE hScript = effect->GetAnnotationByName( hTech, "Script" );

	if(hScript){
		const char *scriptText = NULL;
		hr=effect->GetString( hScript, &scriptText );
		assert(SUCCEEDED(hr));

		const char *next=scriptText;
		assert(next!='\0');
		
		while( Script::isValid( next ) ){
			Script::IScript* s = Script::createScript(  next, &next, effect, mme, this );
			if( s==NULL && next!='\0' ){
				mHandle=NULL;
				return;
			}
			mScripts.push_back( s );
		}
	}
	//テクニックのスクリプトを省略した場合、単にテクニックのパスが順に実行される。
	else {
		for( int i=0, size=mPasses.size(); i<size; ++i ){
			Script::IScript *s = new Script::PassScript( mPasses[i] );
			mScripts.push_back(s);
		}
	}

	mScripts.shrink_to_fit();

}
StandardTechnique::~StandardTechnique(){
	for( int i=0, size=mScripts.size(); i<size; ++i ){
		SAFE_DELETE( mScripts[i] );
	}
	mScripts.clear();
	mScripts.shrink_to_fit();
}


void StandardTechnique::exec(){
	HRESULT hr;
	hr=mEffect->SetTechnique( mHandle );
	assert(SUCCEEDED(hr));

	hr=mEffect->Begin( 0, 0 );
	assert(SUCCEEDED(hr));

	for( int i=0, size=mScripts.size(); i<size; ++i ){
		mScripts[i]->exec();
	}

	//●空のテクニック

	//以下のように、テクニックを空にすると、そのテクニックでは一切描画が行われなくなる。
	//これを利用すると、オブジェクトの一部または全部の描画を抑止することができる。

	//　/*********************************************************/
	//     technique ShadowTech < string MMDPass = "shadow";  > {
	//        
	//     }
	//　/*********************************************************/

	hr=mEffect->End();
	assert(SUCCEEDED(hr));
}


}