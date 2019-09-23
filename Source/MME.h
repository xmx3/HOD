#pragma once
#include<GameLib/Graphics/Manager.h>
#include<d3dx9.h>
#include<assert.h>
#include<tchar.h>
#include"ShaderTest.h"
#include"helper/MyOutputDebugString.h"
#include<assert.h>
#include<vector>

#include<GameLib/Math/Vector3.h>
#include"SegaTypeHelper.h"

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#endif//SAFE_RELEASE

namespace{
	struct TestModel{
		void draw(){}
	};

	enum MATRIX_INDEX{
		//camera
		WORLD=0,
		VIEW,
		PROJECTION,
		WORLDVIEW,
		VIEWPROJECTION,
		WORLDVIEWPROJECTION,

		WORLDTRANSPOSE,
		VIEWTRANSPOSE,
		PROJECTIONTRANSPOSE,
		WORLDVIEWTRANSPOSE,
		VIEWPROJECTIONTRANSPOSE,
		WORLDVIEWPROJECTIONTRANSPOSE,

		WORLDINVERSE,
		VIEWINVERSE,
		PROJECTIONINVERSE,
		WORLDVIEWINVERSE,
		VIEWPROJECTIONINVERSE,
		WORLDVIEWPROJECTIONINVERSE,

		WORLDINVERSETRANSPOSE,
		VIEWINVERSETRANSPOSE,
		PROJECTIONINVERSETRANSPOSE,
		WORLDVIEWINVERSETRANSPOSE,
		VIEWPROJECTIONINVERSETRANSPOSE,
		WORLDVIEWPROJECTIONINVERSETRANSPOSE,

		//light
		L_WORLD,
		L_VIEW,
		L_PROJECTION,
		L_WORLDVIEW,
		L_VIEWPROJECTION,
		L_WORLDVIEWPROJECTION,

		L_WORLDTRANSPOSE,
		L_VIEWTRANSPOSE,
		L_PROJECTIONTRANSPOSE,
		L_WORLDVIEWTRANSPOSE,
		L_VIEWPROJECTIONTRANSPOSE,
		L_WORLDVIEWPROJECTIONTRANSPOSE,
	
		L_WORLDINVERSE,
		L_VIEWINVERSE,
		L_PROJECTIONINVERSE,
		L_WORLDVIEWINVERSE,
		L_VIEWPROJECTIONINVERSE,
		L_WORLDVIEWPROJECTIONINVERSE,
		
		L_WORLDINVERSETRANSPOSE,
		L_VIEWINVERSETRANSPOSE,
		L_PROJECTIONINVERSETRANSPOSE,
		L_WORLDVIEWINVERSETRANSPOSE,
		L_VIEWPROJECTIONINVERSETRANSPOSE,
		L_WORLDVIEWPROJECTIONINVERSETRANSPOSE,
		
		UNKNOWN_MATRIX,
	};
	//debug用
	//const char *TextMatrixIndex[] = {
	//	//camera
	//	"WORLD",
	//	"VIEW",
	//	"PROJECTION",
	//	"WORLDVIEW",
	//	"VIEWPROJECTION",
	//	"WORLDVIEWPROJECTION",
	//	
	//	"WORLDTRANSPOSE",
	//	"VIEWTRANSPOSE",
	//	"PROJECTIONTRANSPOSE",
	//	"WORLDVIEWTRANSPOSE",
	//	"VIEWPROJECTIONTRANSPOSE",
	//	"WORLDVIEWPROJECTIONTRANSPOSE",
	//	
	//	"WORLDINVERSE",
	//	"VIEWINVERSE",
	//	"PROJECTIONINVERSE",
	//	"WORLDVIEWINVERSE",
	//	"VIEWPROJECTIONINVERSE",
	//	"WORLDVIEWPROJECTIONINVERSE",
	//	
	//	"WORLDINVERSETRANSPOSE",
	//	"VIEWINVERSETRANSPOSE",
	//	"PROJECTIONINVERSETRANSPOSE",
	//	"WORLDVIEWINVERSETRANSPOSE",
	//	"VIEWPROJECTIONINVERSETRANSPOSE",
	//	"WORLDVIEWPROJECTIONINVERSETRANSPOSE",
	//	
	//	//light
	//	"L_WORLD",
	//	"L_VIEW",
	//	"L_PROJECTION",
	//	"L_WORLDVIEW",
	//	"L_VIEWPROJECTION",
	//	"L_WORLDVIEWPROJECTION",
	//	
	//	"L_WORLDTRANSPOSE",
	//	"L_VIEWTRANSPOSE",
	//	"L_PROJECTIONTRANSPOSE",
	//	"L_WORLDVIEWTRANSPOSE",
	//	"L_VIEWPROJECTIONTRANSPOSE",
	//	"L_WORLDVIEWPROJECTIONTRANSPOSE",
	//	
	//	"L_WORLDINVERSE",
	//	"L_VIEWINVERSE",
	//	"L_PROJECTIONINVERSE",
	//	"L_WORLDVIEWINVERSE",
	//	"L_VIEWPROJECTIONINVERSE",
	//	"L_WORLDVIEWPROJECTIONINVERSE",
	//	
	//	"L_WORLDINVERSETRANSPOSE",
	//	"L_VIEWINVERSETRANSPOSE",
	//	"L_PROJECTIONINVERSETRANSPOSE",
	//	"L_WORLDVIEWINVERSETRANSPOSE",
	//	"L_VIEWPROJECTIONINVERSETRANSPOSE",
	//	"L_WORLDVIEWPROJECTIONINVERSETRANSPOSE",
	//	
	//	"UNKNOWN_MATRIX",
	//};

	enum FLOAT4INDEX{
		//geometory
		DIFFUSE=0,      
		AMBIENT,      
		SPECULAR,    
		POSITION,//camera
		DIRECTION,//camera
		EDGECOLOR,
		EMISSIVE,     
		TOONCOLOR,    

		//light
		L_DIFFUSE,      
		L_AMBIENT,      
		L_SPECULAR,    
		L_POSITION,
		L_DIRECTION,
		
		UNKNOWN_FLOAT4,
	};

	enum FLOAT_INDEX{
		SPECULARPOWER=0,
		TIME,
		ELAPSEDTIME,
		STANDARDSGLOBAL,
		UNKNOWN_FLOAT,
	};
	
	MATRIX_INDEX findMatrixIndex( ID3DXEffect *effect, D3DXHANDLE hParam ){
		D3DXPARAMETER_DESC paramDesc;
		effect->GetParameterDesc( hParam, &paramDesc );
		if( paramDesc.Semantic==NULL ){
			return UNKNOWN_MATRIX;
		}

		//行列じゃない場合
		if( !( paramDesc.Class == D3DXPC_MATRIX_ROWS || paramDesc.Class == D3DXPC_MATRIX_COLUMNS ) ){
			return UNKNOWN_MATRIX;
		}

		if(
			paramDesc.Type != D3DXPT_FLOAT &&
			paramDesc.Bytes != 4*16 )
		{
			return UNKNOWN_MATRIX;		
		}
		const static int skSemanticsSize=L_WORLD;
		const char *semantics[skSemanticsSize] = {
			//camera
			"WORLD",
			"VIEW",
			"PROJECTION",
			"WORLDVIEW",
			"VIEWPROJECTION",
			"WORLDVIEWPROJECTION",
			
			"WORLDTRANSPOSE",
			"VIEWTRANSPOSE",
			"PROJECTIONTRANSPOSE",
			"WORLDVIEWTRANSPOSE",
			"VIEWPROJECTIONTRANSPOSE",
			"WORLDVIEWPROJECTIONTRANSPOSE",
			
			"WORLDINVERSE",
			"VIEWINVERSE",
			"PROJECTIONINVERSE",
			"WORLDVIEWINVERSE",
			"VIEWPROJECTIONINVERSE",
			"WORLDVIEWPROJECTIONINVERSE",
			
			"WORLDINVERSETRANSPOSE",
			"VIEWINVERSETRANSPOSE",
			"PROJECTIONINVERSETRANSPOSE",
			"WORLDVIEWINVERSETRANSPOSE",
			"VIEWPROJECTIONINVERSETRANSPOSE",
			"WORLDVIEWPROJECTIONINVERSETRANSPOSE"
		};

		for( int i=0; i<skSemanticsSize; ++i ){
			const char *semantic = semantics[i];
			if( strcmpi(paramDesc.Semantic, semantic) == 0 ){
				D3DXHANDLE hObject = effect->GetAnnotationByName( hParam, "Object" );
				if(hObject){
					const char *object=NULL;
					effect->GetString( hObject, &object );
					if( strcmpi( object, "camera") == 0 ){
						TRACE2( "%s : %s< string Object=\"Camera\">;\n", paramDesc.Name, paramDesc.Semantic );
						return static_cast<MATRIX_INDEX>(i);
					} else if( strcmpi(object, "light") == 0 ){
						assert( UNKNOWN_MATRIX > static_cast<MATRIX_INDEX>(i+skSemanticsSize) );
						TRACE2( "%s : %s< string Object=\"Light\">;\n", paramDesc.Name, paramDesc.Semantic );
						return static_cast<MATRIX_INDEX>(i+skSemanticsSize);
					} else{
						assert(false);
					}
				//anonotationない場合デフォルトのカメラ
				} else {
					TRACE2( "%s : %s;\n", paramDesc.Name, paramDesc.Semantic );
					assert(paramDesc.Annotations==0);
					return static_cast<MATRIX_INDEX>(i);
				}
			}
		}
		return UNKNOWN_MATRIX;
	}

	FLOAT4INDEX findFloat4Index( ID3DXEffect *effect, D3DXHANDLE hParam ){
		D3DXPARAMETER_DESC paramDesc;
		effect->GetParameterDesc( hParam, &paramDesc );
		//セマンティックがない場合
		if( paramDesc.Semantic==NULL ){
			return UNKNOWN_FLOAT4;
		}

		//float3 or float4以外の場合
		//列ベクトル
		if(
			paramDesc.Class != D3DXPC_VECTOR ||
			paramDesc.Type != D3DXPT_FLOAT ||
			!(paramDesc.Bytes==4*3 || paramDesc.Bytes==4*4 ) ||
			!(paramDesc.Columns==3 || paramDesc.Columns==4 ) )
		{
			return UNKNOWN_FLOAT4;
		}
		
		const static int skSemanticsSize=L_DIFFUSE;		
		const char *semantics[skSemanticsSize]= {
			"DIFFUSE",      
			"AMBIENT",      
			"SPECULAR",    
			"POSITION",
			"DIRECTION",
			"EDGECOLOR",
			"EMISSIVE",     
			"TOONCOLOR"   
		};
#if _DEBUG
		const char* tType=NULL;
		const char *tFloat3="float3 ";
		const char *tFloat4="float4 ";
		if( paramDesc.Columns==3 ){
			tType = tFloat3;
			
		}
		else if( paramDesc.Columns==4 ){
			tType = tFloat4;
		}
#endif
		
		for( int i=0; i<skSemanticsSize; ++i ){
			const char *semantic = semantics[i];

			//セマンティックが一致した場合
			if( strcmpi(paramDesc.Semantic, semantic) == 0 ){
				D3DXHANDLE hObject = effect->GetAnnotationByName( hParam, "Object" );
				//アノテーションのObjectがあった場合
				if(hObject){
					const char *object=NULL;
					effect->GetString( hObject, &object );
					if( strcmpi( object, "geometry") == 0 ){
						assert( !(i==DIRECTION || i==POSITION) && " Object of annotaition must be camera or light!" );						
						TRACE3( "%s%s : %s< string Object=\"Geometry\">;\n", tType, paramDesc.Name, paramDesc.Semantic );
						return static_cast<FLOAT4INDEX>(i);
					} else if( strcmpi(object, "light") == 0 ){
						if( UNKNOWN_FLOAT4 > static_cast<FLOAT4INDEX>(i+skSemanticsSize) ){
							TRACE3( "%s%s : %s< string Object=\"Light\">;\n", tType, paramDesc.Name, paramDesc.Semantic );
							return static_cast<FLOAT4INDEX>(i+skSemanticsSize);
						}else {
							TRACE3( "%s%s : %s< string Object=\"Light\">;\n", tType, paramDesc.Name, paramDesc.Semantic );							
							assert( false && "FLOAT4INDEX over! \"EDGECOLOR\", \"EMISSIVE\",\"TOONCOLOR\" cannot set light!" );
						}
						
					} else if( strcmpi( object, "camera") == 0 ){
						assert( i==DIRECTION || i==POSITION && "Object of annotaition must be geometry or light!");
						TRACE3( "%s%s : %s< string Object=\"Camera\">;\n", tType, paramDesc.Name, paramDesc.Semantic );
						return static_cast<FLOAT4INDEX>(i);
					} else{
						assert(false);
					}
				//annotationない場合
				//"EMISSIVE"および"TOONCOLOR"には、ライト色がないため、"Light"は指定できない。
				//EDGECOLORはannotationが存在しない
				} else if( 
					strcmpi(paramDesc.Semantic, "EMISSIVE") == 0 ||
					strcmpi(paramDesc.Semantic, "TOONCOLOR") == 0 ||
					strcmpi(paramDesc.Semantic, "EDGECOLOR") == 0 )
				{
					
					TRACE2( "%s : %s;\n", paramDesc.Name, paramDesc.Semantic );
					assert(paramDesc.Annotations==0);
					return static_cast<FLOAT4INDEX>(i);
				} else {
					assert(false);
					return UNKNOWN_FLOAT4;
				}
			}
		}
		return UNKNOWN_FLOAT4;
	}

	FLOAT_INDEX findFloatIndex( ID3DXEffect *effect, D3DXHANDLE hParam ){
		D3DXPARAMETER_DESC paramDesc;
		effect->GetParameterDesc( hParam, &paramDesc );
		//セマンティックがない場合
		if( paramDesc.Semantic==NULL ){
			return UNKNOWN_FLOAT;
		}

		//float以外の場合
		if(
			paramDesc.Type != D3DXPT_FLOAT ||
			paramDesc.Bytes!=4 )
		{
			return UNKNOWN_FLOAT;
		}

		//セマンティックが一致した場合
		if( strcmpi(paramDesc.Semantic, "SPECULARPOWER" ) == 0 ){
			D3DXHANDLE hObject = effect->GetAnnotationByName( hParam, "Object" );
			//アノテーションのObjectがあった場合
			if(hObject){
				const char *object=NULL;
				effect->GetString( hObject, &object );
				if( strcmpi( object, "geometry") == 0 ){
					TRACE2( "%s : %s< string Object=\"Geometry\">;\n", paramDesc.Name, paramDesc.Semantic );
					return SPECULARPOWER;
				} else{
					assert(false && "SPECULARPOWER's Object annotation must be only Geometry.");
				}
			//annotationない場合
			} else{
				TRACE2( "%s : %s;\n", paramDesc.Name, paramDesc.Semantic );
				return SPECULARPOWER;
			}
		} else if( strcmpi(paramDesc.Semantic, "TIME" ) == 0 ){
			if(paramDesc.Annotations!=0){
				TRACE0(_T("SyncInEditMode is not implement."));
			}
			TRACE2( "%s : %s;\n", paramDesc.Name, paramDesc.Semantic );
			return TIME;
		} else if( strcmpi(paramDesc.Semantic, "ELAPSEDTIME" ) == 0 ){
			if(paramDesc.Annotations!=0){
				TRACE0(_T("SyncInEditMode is not implement."));
			}
			TRACE2( "%s : %s;\n", paramDesc.Name, paramDesc.Semantic );
			return ELAPSEDTIME;
		} else if( strcmpi(paramDesc.Semantic, "STANDARDSGLOBAL" ) == 0 ){
			float ver=0;
			HRESULT hr = effect->GetFloat( hParam, &ver );
			assert(SUCCEEDED(hr));
			assert( ver==0.8f );
			TRACE2( "%s : %s;\n", paramDesc.Name, paramDesc.Semantic );
			return STANDARDSGLOBAL;
		}

		return UNKNOWN_FLOAT;

	}

	void setIfNull( D3DXHANDLE &hLeft, const D3DXHANDLE &hRight ){
		if( hLeft==NULL ){
			hLeft = hRight;
		} else{
			assert( false && "There is a variable with the same meaning.");
		}		
	}
		
}


class MME {
public:
	MME()//LPCWSTR filename ) 
		: mEffect(0),
		mHandleSpecularPower(0),
		mHandleTime(0),
		mHandleElapsedTime(0)
	{
		for( int i=0; i<UNKNOWN_MATRIX; ++i){
			mHandlesMatrix[i]=0;
		}

		for( int i=0; i<UNKNOWN_FLOAT4; ++i){
			mHandlesFloat4[i]=0;
		}

		LPCWSTR filename = _T("shader/simple.fx");
		//LPCWSTR filename = _T("shader/MME/full.fx");
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();

		HRESULT hr;
		IDirect3DDevice9 *pDevice = m.dxDevice();

		//バージョンいくつに対応してるか
		D3DCAPS9 caps;
		pDevice->GetDeviceCaps(&caps);

		if ( ( caps.VertexShaderVersion < D3DVS_VERSION(3,0) ) ||
			( caps.PixelShaderVersion < D3DPS_VERSION(3,0)  ) ) {
				::MessageBox(NULL,_T("プログラマブルシェーダの機能に対応していません。"),_T(""),MB_OK);
		}

		LPD3DXBUFFER pCompilationErrors;
		hr=D3DXCreateEffectFromFile(
			pDevice,
			filename,
			NULL,
			NULL,
			0,
			NULL,
			&mEffect,
			&pCompilationErrors );
		if(pCompilationErrors){
			const char* p= (const char*)pCompilationErrors->GetBufferPointer();
			OutputDebugStringA( p );
			//OutputDebugString( p );
			pCompilationErrors->Release();
			assert(SUCCEEDED(hr));
			
			return;
		}

		// 座法変換行列
		//float4x4 WorldViewProjMatrix      : WORLDVIEWPROJECTION;
		//float4x4 WorldMatrix              : WORLD;
		//float4x4 ViewMatrix               : VIEW;
		//float4x4 LightWorldViewProjMatrix : WORLDVIEWPROJECTION < string Object = "Light"; >;
		
		D3DXEFFECT_DESC effectDesc;
		mEffect->GetDesc( &effectDesc );
		for( UINT iParam = 0; iParam < effectDesc.Parameters; iParam++ )
		{
		    D3DXHANDLE hParam = mEffect->GetParameter ( NULL, iParam );
			
			{
				MATRIX_INDEX midx =findMatrixIndex( mEffect, hParam );

				//TRACE1( "%s\n", TextMatrixIndex[mtype] );

				//見つかったならおしまい
				if(midx!=UNKNOWN_MATRIX){
					setIfNull(mHandlesMatrix[midx], hParam);
					continue;
				}
			}
			
			{
				FLOAT4INDEX cidx = findFloat4Index( mEffect, hParam );
				//見つかった?
				if(cidx!=UNKNOWN_FLOAT4){
					setIfNull(mHandlesFloat4[cidx], hParam);
					continue;
				}
			}

			{
				FLOAT_INDEX fidx = findFloatIndex( mEffect, hParam );
				if(fidx==SPECULARPOWER){
					setIfNull(mHandleSpecularPower, hParam);
					continue;
				} else if( fidx==TIME ){
					setIfNull(mHandleTime, hParam );
					continue;
				} else if( fidx==ELAPSEDTIME ){
					setIfNull(mHandleElapsedTime, hParam );
					continue;
				} else if( fidx==STANDARDSGLOBAL ){
					analyzeStandatdsGlobal(hParam);
					continue;
				} else if( fidx==UNKNOWN_FLOAT ){
				} else {
					assert(false);
				}
			}	
		}


		D3DXHANDLE hTech = mEffect->GetTechniqueByName("TShader");
		D3DXTECHNIQUE_DESC techDesc;
		mEffect->GetTechniqueDesc( hTech, &techDesc ); 
		D3DXHANDLE hScript = mEffect->GetAnnotationByName( hTech, "Script" );
		const char* scriptText=NULL;
		mEffect->GetString( hScript, &scriptText );
		TRACE1("%s\n", scriptText );

		if(false)
		for( UINT iTech=0; iTech < effectDesc.Techniques; ++iTech )
		{
			D3DXHANDLE hTech = mEffect->GetTechnique( iTech );
			D3DXTECHNIQUE_DESC techDesc;
			mEffect->GetTechniqueDesc( hTech, &techDesc ); 
			for( UINT iPass=0; iPass<techDesc.Passes; ++iPass ){
				D3DXHANDLE hPass = mEffect->GetPass( hTech, iPass );
				D3DXPASS_DESC passDesc;
				mEffect->GetPassDesc( hPass, &passDesc );
				//std::string name(passDesc.Name);
				
			}
		}
		
		//float3   LightDirection    : DIRECTION < string Object = "Light"; >;
		//float3   CameraPosition    : POSITION  < string Object = "Camera"; >;
		//
		//// マテリアル色
		//float4   MaterialDiffuse   : DIFFUSE  < string Object = "Geometry"; >;
		//float3   MaterialAmbient   : AMBIENT  < string Object = "Geometry"; >;
		//float3   MaterialEmmisive  : EMISSIVE < string Object = "Geometry"; >;
		//float3   MaterialSpecular  : SPECULAR < string Object = "Geometry"; >;
		//float    SpecularPower     : SPECULARPOWER < string Object = "Geometry"; >;
		//float3   MaterialToon      : TOONCOLOR;
		//float4   EdgeColor         : EDGECOLOR;
		//// ライト色
		//float3   LightDiffuse      : DIFFUSE   < string Object = "Light"; >;
		//float3   LightAmbient      : AMBIENT   < string Object = "Light"; >;
		//float3   LightSpecular     : SPECULAR  < string Object = "Light"; >;
		//static float4 DiffuseColor  = MaterialDiffuse  * float4(LightDiffuse, 1.0f);
		//static float3 AmbientColor  = saturate(MaterialAmbient  * LightAmbient + MaterialEmmisive);
		//static float3 SpecularColor = MaterialSpecular * LightSpecular;
		//
		//bool     parthf;   // パースペクティブフラグ
		//bool     transp;   // 半透明フラグ
		//bool	 spadd;    // スフィアマップ加算合成フラグ

	}
	~MME(){
		SAFE_RELEASE(mEffect);
	}

	void begin( int mmdPass, int useTexture, int useSphereMap, int useToon, int useSelfShadow ){
		int v81 = mmdPass%3;
		int v243 = mmdPass/3;
		
		
		int key = 243*v243 + 81*v81 + 27*useTexture + 9*useSphereMap + 3*useToon + useSelfShadow;
		D3DXHANDLE hTech = findTequnique( mmdPass, useTexture, useSphereMap, useToon, useSelfShadow );
		mEffect->SetTechnique( hTech );
		mEffect->Begin( 0, 0 );
		//script->exec();
	}

	D3DXHANDLE findTequnique( int mmdPass, int useTexture, int useSphereMap, int useToon, int useSelfShadow ){
		return 0;
	}

	void preScriptsExe(){
	}

	void scriptExe(){
	}

	void testDraw(){
		HRESULT hr;
		
		GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
		GameLib::Matrix44 mwpv = gm.getProjectionViewMatrix();

		//D3DXMATRIX m;
		//D3DXMatrixIdentity(&m);
		hr = mEffect->SetFloatArray("gTransform", (const float*)(&mwpv), 16);
		assert( SUCCEEDED(hr) );

		/*
		ISendAbleToEffect *h = mHandles[0];
		switch(h->type){
		case WORLDVIEWPROJECTION :
			h->send( mEffect, &mwpv );
		}
		*/
		
		float c0[1]={1};
		//for(int i=0; i<200; ++i ){
		//	assert(c0[i]==0);
		//}
		float* p=c0;
		//TRACE2( "%f, %f\n", *(p+1), *(p+2) );
		float c1[4]={1.f,1.f,1.f,1.f};
		float c2[4]={1.f,1.f,1.f,1.f};
		//LPDIRECT3DDEVICE9 d;
		//hr = mEffect->GetDevice(&d);

		//d->SetVertexShaderConstantF( 10, c, 1 );

		hr=mEffect->SetFloatArray("TestColor1", c1, 4 ); 
		assert( SUCCEEDED(hr) );
		hr=mEffect->SetFloatArray("TestColor2", c2, 4 ); 
		assert( SUCCEEDED(hr) );
		hr=mEffect->SetFloatArray("TestColor0", c0, 4 ); //NG変なデータ送ってる
		assert( SUCCEEDED(hr) );

		//GameLib::Math::Vector3 v(1.f,0,0);
		//gm.setDiffuseColor(v);
		

		mEffect->Begin(0, 0);
		mEffect->BeginPass( 0 );
		
		mCube.draw();

		mEffect->EndPass();
		mEffect->End();
	}

	void sendMatrices(
		const D3DXMATRIX &w,
		const D3DXMATRIX &v,
		const D3DXMATRIX &p
	){
		//WORLD系セマンティック
		{
			D3DXMATRIX iw;
			//逆行列が必要なら計算する
			if(mHandlesMatrix[WORLDINVERSE] || mHandlesMatrix[WORLDINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iw, 0, &w );
			}
			if(mHandlesMatrix[WORLD]){
				mEffect->SetMatrix( mHandlesMatrix[WORLD], &w );
			}
			if(mHandlesMatrix[WORLDTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[WORLDTRANSPOSE],&w );
			}
			if(mHandlesMatrix[WORLDINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[WORLDINVERSE], &iw );
			}
			if(mHandlesMatrix[WORLDINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[WORLDINVERSETRANSPOSE], &iw );
			}
		}

		//VIEW系セマンティック
		{
			D3DXMATRIX iv;
			//逆行列が必要なら計算する
			if(mHandlesMatrix[VIEWINVERSE] || mHandlesMatrix[VIEWINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iv, 0, &v );
			}
			if(mHandlesMatrix[VIEW]){
				mEffect->SetMatrix( mHandlesMatrix[VIEW], &v );
			}
			if(mHandlesMatrix[VIEWTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[VIEWTRANSPOSE],&v );
			}
			if(mHandlesMatrix[VIEWINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[VIEWINVERSE], &iv );
			}
			if(mHandlesMatrix[VIEWINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[VIEWINVERSETRANSPOSE], &iv );
			}
		}

		//PROJECTION系セマンティック
		{
			D3DXMATRIX ip;
			//逆行列が必要なら計算する
			if(mHandlesMatrix[PROJECTIONINVERSE] || mHandlesMatrix[PROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &ip, 0, &p );
			}
			if(mHandlesMatrix[PROJECTION]){
				mEffect->SetMatrix( mHandlesMatrix[PROJECTION], &p );
			}
			if(mHandlesMatrix[PROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[PROJECTIONTRANSPOSE],&p );
			}
			if(mHandlesMatrix[PROJECTIONINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[PROJECTIONINVERSE], &ip );
			}
			if(mHandlesMatrix[PROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[PROJECTIONINVERSETRANSPOSE], &ip );
			}
		}

		//WORLDVIEW系セマンティック
		if(
			mHandlesMatrix[WORLDVIEW] ||
			mHandlesMatrix[WORLDVIEWINVERSE] ||
			mHandlesMatrix[WORLDVIEWTRANSPOSE] || 
			mHandlesMatrix[WORLDVIEWINVERSETRANSPOSE])
		{
			D3DXMATRIX wv=w*v;
			
			D3DXMATRIX iwv;

			//逆行列が必要なら計算する
			if(mHandlesMatrix[WORLDVIEWINVERSE] || mHandlesMatrix[WORLDVIEWINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iwv, 0, &wv );
			}
			if(mHandlesMatrix[WORLDVIEW]){
				mEffect->SetMatrix( mHandlesMatrix[WORLDVIEW], &wv );
			}
			if(mHandlesMatrix[WORLDVIEWTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[WORLDVIEWTRANSPOSE],&wv );
			}
			if(mHandlesMatrix[WORLDVIEWINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[WORLDVIEWINVERSE], &iwv );
			}
			if(mHandlesMatrix[WORLDVIEWINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[WORLDVIEWINVERSETRANSPOSE], &iwv );
			}
		}

		//VIEWPROJECTION系セマンティック
		if(
			mHandlesMatrix[VIEWPROJECTION] ||
			mHandlesMatrix[VIEWPROJECTIONINVERSE] ||
			mHandlesMatrix[VIEWPROJECTIONTRANSPOSE] || 
			mHandlesMatrix[VIEWPROJECTIONINVERSETRANSPOSE])
		{
			D3DXMATRIX vp=v*p;
			
			D3DXMATRIX ivp;

			//逆行列が必要なら計算する
			if(mHandlesMatrix[VIEWPROJECTIONINVERSE] || mHandlesMatrix[VIEWPROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &ivp, 0, &vp );
			}
			if(mHandlesMatrix[VIEWPROJECTION]){
				mEffect->SetMatrix( mHandlesMatrix[VIEWPROJECTION], &vp );
			}
			if(mHandlesMatrix[VIEWPROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[VIEWPROJECTIONTRANSPOSE],&vp );
			}
			if(mHandlesMatrix[VIEWPROJECTIONINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[VIEWPROJECTIONINVERSE], &ivp );
			}
			if(mHandlesMatrix[VIEWPROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[VIEWPROJECTIONINVERSETRANSPOSE], &ivp );
			}
		}

		//WORLDVIEWPROJECTION系セマンティック
		if(
			mHandlesMatrix[WORLDVIEWPROJECTION] ||
			mHandlesMatrix[WORLDVIEWPROJECTIONINVERSE] ||
			mHandlesMatrix[WORLDVIEWPROJECTIONTRANSPOSE] || 
			mHandlesMatrix[WORLDVIEWPROJECTIONINVERSETRANSPOSE])
		{
			D3DXMATRIX wvp=w*v*p;
			
			D3DXMATRIX iwvp;

			//逆行列が必要なら計算する
			if(mHandlesMatrix[WORLDVIEWPROJECTIONINVERSE] || mHandlesMatrix[WORLDVIEWPROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iwvp, 0, &wvp );
			}
			if(mHandlesMatrix[WORLDVIEWPROJECTION]){
				mEffect->SetMatrix( mHandlesMatrix[WORLDVIEWPROJECTION], &wvp );
			}
			if(mHandlesMatrix[WORLDVIEWPROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[WORLDVIEWPROJECTIONTRANSPOSE],&wvp );
			}
			if(mHandlesMatrix[WORLDVIEWPROJECTIONINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[WORLDVIEWPROJECTIONINVERSE], &iwvp );
			}
			if(mHandlesMatrix[WORLDVIEWPROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[WORLDVIEWPROJECTIONINVERSETRANSPOSE], &iwvp );
			}
		}
	}

	void sendLightMatrices(
		const D3DXMATRIX &w,
		const D3DXMATRIX &v,
		const D3DXMATRIX &p
	){
		//L_WORLD系セマンティック
		{
			D3DXMATRIX iw;
			//逆行列が必要なら計算する
			if(mHandlesMatrix[L_WORLDINVERSE] || mHandlesMatrix[L_WORLDINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iw, 0, &w );
			}
			if(mHandlesMatrix[L_WORLD]){
				mEffect->SetMatrix( mHandlesMatrix[L_WORLD], &w );
			}
			if(mHandlesMatrix[L_WORLDTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_WORLDTRANSPOSE],&w );
			}
			if(mHandlesMatrix[L_WORLDINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[L_WORLDINVERSE], &iw );
			}
			if(mHandlesMatrix[L_WORLDINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_WORLDINVERSETRANSPOSE], &iw );
			}
		}

		//L_VIEW系セマンティック
		{
			D3DXMATRIX iv;
			//逆行列が必要なら計算する
			if(mHandlesMatrix[L_VIEWINVERSE] || mHandlesMatrix[L_VIEWINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iv, 0, &v );
			}
			if(mHandlesMatrix[L_VIEW]){
				mEffect->SetMatrix( mHandlesMatrix[L_VIEW], &v );
			}
			if(mHandlesMatrix[L_VIEWTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_VIEWTRANSPOSE],&v );
			}
			if(mHandlesMatrix[L_VIEWINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[L_VIEWINVERSE], &iv );
			}
			if(mHandlesMatrix[L_VIEWINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_VIEWINVERSETRANSPOSE], &iv );
			}
		}

		//L_PROJECTION系セマンティック
		{
			D3DXMATRIX ip;
			//逆行列が必要なら計算する
			if(mHandlesMatrix[L_PROJECTIONINVERSE] || mHandlesMatrix[L_PROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &ip, 0, &p );
			}
			if(mHandlesMatrix[L_PROJECTION]){
				mEffect->SetMatrix( mHandlesMatrix[L_PROJECTION], &p );
			}
			if(mHandlesMatrix[L_PROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_PROJECTIONTRANSPOSE],&p );
			}
			if(mHandlesMatrix[L_PROJECTIONINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[L_PROJECTIONINVERSE], &ip );
			}
			if(mHandlesMatrix[L_PROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_PROJECTIONINVERSETRANSPOSE], &ip );
			}
		}

		//L_WORLDVIEW系セマンティック
		if(
			mHandlesMatrix[L_WORLDVIEW] ||
			mHandlesMatrix[L_WORLDVIEWINVERSE] ||
			mHandlesMatrix[L_WORLDVIEWTRANSPOSE] || 
			mHandlesMatrix[L_WORLDVIEWINVERSETRANSPOSE])
		{
			D3DXMATRIX wv=w*v;
			
			D3DXMATRIX iwv;

			//逆行列が必要なら計算する
			if(mHandlesMatrix[L_WORLDVIEWINVERSE] || mHandlesMatrix[L_WORLDVIEWINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iwv, 0, &wv );
			}
			if(mHandlesMatrix[L_WORLDVIEW]){
				mEffect->SetMatrix( mHandlesMatrix[L_WORLDVIEW], &wv );
			}
			if(mHandlesMatrix[L_WORLDVIEWTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_WORLDVIEWTRANSPOSE],&wv );
			}
			if(mHandlesMatrix[L_WORLDVIEWINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[L_WORLDVIEWINVERSE], &iwv );
			}
			if(mHandlesMatrix[L_WORLDVIEWINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_WORLDVIEWINVERSETRANSPOSE], &iwv );
			}
		}

		//L_VIEWPROJECTION系セマンティック
		if(
			mHandlesMatrix[L_VIEWPROJECTION] ||
			mHandlesMatrix[L_VIEWPROJECTIONINVERSE] ||
			mHandlesMatrix[L_VIEWPROJECTIONTRANSPOSE] || 
			mHandlesMatrix[L_VIEWPROJECTIONINVERSETRANSPOSE])
		{
			D3DXMATRIX vp=v*p;
			
			D3DXMATRIX ivp;

			//逆行列が必要なら計算する
			if(mHandlesMatrix[L_VIEWPROJECTIONINVERSE] || mHandlesMatrix[L_VIEWPROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &ivp, 0, &vp );
			}
			if(mHandlesMatrix[L_VIEWPROJECTION]){
				mEffect->SetMatrix( mHandlesMatrix[L_VIEWPROJECTION], &vp );
			}
			if(mHandlesMatrix[L_VIEWPROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_VIEWPROJECTIONTRANSPOSE],&vp );
			}
			if(mHandlesMatrix[L_VIEWPROJECTIONINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[L_VIEWPROJECTIONINVERSE], &ivp );
			}
			if(mHandlesMatrix[L_VIEWPROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_VIEWPROJECTIONINVERSETRANSPOSE], &ivp );
			}
		}

		//L_WORLDVIEWPROJECTION系セマンティック
		if(
			mHandlesMatrix[L_WORLDVIEWPROJECTION] ||
			mHandlesMatrix[L_WORLDVIEWPROJECTIONINVERSE] ||
			mHandlesMatrix[L_WORLDVIEWPROJECTIONTRANSPOSE] || 
			mHandlesMatrix[L_WORLDVIEWPROJECTIONINVERSETRANSPOSE])
		{
			D3DXMATRIX wvp=w*v*p;
			
			D3DXMATRIX iwvp;

			//逆行列が必要なら計算する
			if(mHandlesMatrix[L_WORLDVIEWPROJECTIONINVERSE] || mHandlesMatrix[L_WORLDVIEWPROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iwvp, 0, &wvp );
			}
			if(mHandlesMatrix[L_WORLDVIEWPROJECTION]){
				mEffect->SetMatrix( mHandlesMatrix[L_WORLDVIEWPROJECTION], &wvp );
			}
			if(mHandlesMatrix[L_WORLDVIEWPROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_WORLDVIEWPROJECTIONTRANSPOSE],&wvp );
			}
			if(mHandlesMatrix[L_WORLDVIEWPROJECTIONINVERSE]){
				mEffect->SetMatrix( mHandlesMatrix[L_WORLDVIEWPROJECTIONINVERSE], &iwvp );
			}
			if(mHandlesMatrix[L_WORLDVIEWPROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mHandlesMatrix[L_WORLDVIEWPROJECTIONINVERSETRANSPOSE], &iwvp );
			}
		}
	}

private:
	void analyzeStandatdsGlobal(D3DXHANDLE hParam){
	}
	void otherHandelsCheck( D3DXHANDLE hParam ){
		D3DXPARAMETER_DESC paramDesc;
		mEffect->GetParameterDesc( hParam, &paramDesc );
		//セマンティックがない場合
		if( paramDesc.Semantic==NULL ){
		
		}

		

		//セマンティックが一致した場合
		if( strcmpi(paramDesc.Semantic, "SPECULARPOWER" ) == 0 ){
			D3DXHANDLE hObject = mEffect->GetAnnotationByName( hParam, "Object" );
		}
	}


	ID3DXEffect *mEffect;
	DxCube mCube;
	
	//最低限しか持たないことが可能
	//std::vector<ISendAbleToEffect*> mHandles;
	
	//D3DXHANDLE mHandles[UNKNOWN_MATRIX];
	//この実装だとw,v,p計算量が少なくなることが可能
	D3DXHANDLE mHandlesMatrix[UNKNOWN_MATRIX];
	D3DXHANDLE mHandlesFloat4[UNKNOWN_FLOAT4];
	D3DXHANDLE mHandleSpecularPower;
	D3DXHANDLE mHandleTime;
	D3DXHANDLE mHandleElapsedTime;

	TestModel mModel;
};


class ISendAbleToEffect {
public:
	unsigned int type;
	ISendAbleToEffect(){}
	virtual ~ISendAbleToEffect(){}
	virtual void send( ID3DXEffect *effect, const void *pData )=0;
};


template< int N >
class FloatXHandle : public ISendAbleToEffect {
public:
	virtual void send( ID3DXEffect *effect, const float *pData ){
		effect->SetFloatArray( mHandle, pData , N ); 
	}
	D3DXHANDLE mHandle;
};

template< int N >
class IntXHandle : public ISendAbleToEffect {
public:
	virtual void send( ID3DXEffect *effect, const int *pF ){
		effect->SetInttArray( mHandle, pData , N ); 
	}
	D3DXHANDLE mHandle;
};

class WorldHandle : public ISendAbleToEffect {
public:
	WorldHandle(){}
	virtual ~WorldHandle(){}
	virtual void send( ID3DXEffect *effect ){
		GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
		const GameLib::Matrix34 &mw = gm.getWorldMatrix();
		//列ベクトル用に転置
		D3DXMATRIX dxW = toDxMatrix(mw);
		effect->SetMatrix( mHandle, &dxW );
	}
	D3DXHANDLE mHandle;
};

class WVPHandle : public ISendAbleToEffect {
public:
	WVPHandle(){}
	virtual ~WVPHandle(){}
	virtual void send( ID3DXEffect *effect ){
		GameLib::Graphics::Manager gm = GameLib::Graphics::Manager::instance();
		const GameLib::Matrix34 &mw = gm.getWorldMatrix();
		const GameLib::Matrix44 &mpv = gm.getProjectionViewMatrix();
		GameLib::Matrix44 mpvw;
		mpvw.setMul( mpvw, mw );
		//列ベクトル用に転置
		effect->SetMatrixTranspose( mHandle, reinterpret_cast<const D3DXMATRIX *>(&mpvw) );
	}
	D3DXHANDLE mHandle;
};