#include"BaseEffect.h"
#include<GameLib/GameLib.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/FileIO/InFile.h>
#include<GameLib/FileIO/Manager.h>
#include<assert.h>
#include<tchar.h>
#include<assert.h>
#include"Texture .h"
#include"RenderTarget.h"
#include"RenderDepthStencil.h"
#include"OffScreenRender.h"
#include"helper/ContainerHelper/findByName.h"
#include"helper/ContainerHelper/safeDeleteAll.h"
#include<algorithm>
#include"helper/MyOutputDebugString.h"
#include"BaseTechnique.h"
#include"StandardTechnique.h"
#include"helper/GetFolder.h"
#include"ControlObjectSelf.h"
#include"helper/ContainerHelper/findByName.h"
#include"MMMShader.h"
#include<stdlib.h>
#include<boost/unordered_map.hpp>
#include<boost/xpressive/xpressive.hpp>

namespace{
	//検証しながらかいたのでくそわかりにくいコードになっている
	//一応やりたいことは各セマンティック毎の型の形があっているかを検証している
	//わざわざenumで返す必要はあるのか？
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
		ZNEAR,
		ZFAR,
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
		const static int skSemanticsSize=UNKNOWN_MATRIX;
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
			if( _strcmpi(paramDesc.Semantic, semantic) == 0 ){
				D3DXHANDLE hObject = effect->GetAnnotationByName( hParam, "Object" );
				if(hObject){
					const char *object=NULL;
					effect->GetString( hObject, &object );
					if( _strcmpi( object, "camera") == 0 ){
						//TRACE2( "float4x4 %s : %s< string Object=\"Camera\">;\n", paramDesc.Name, paramDesc.Semantic );
						return static_cast<MATRIX_INDEX>(i);
					} else if( _strcmpi(object, "light") == 0 ){
						//assert( UNKNOWN_MATRIX > static_cast<MATRIX_INDEX>(i+skSemanticsSize) );
						//TRACE2( "float4x4 %s : %s< string Object=\"Light\">;\n", paramDesc.Name, paramDesc.Semantic );
						return UNKNOWN_MATRIX;
					} else{
						assert(false && "Matrix Annotation is wrong.");
						return UNKNOWN_MATRIX;
					}
				//anonotationない場合デフォルトのカメラ
				} else {
					//TRACE2( "float4x4 %s : %s;\n", paramDesc.Name, paramDesc.Semantic );
					assert(paramDesc.Annotations==0);
					return static_cast<MATRIX_INDEX>(i);
				}
			}
		}
		return UNKNOWN_MATRIX;
	}

	MATRIX_INDEX findLightMatrixIndex( ID3DXEffect *effect, D3DXHANDLE hParam ){
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
		const static int skSemanticsSize=UNKNOWN_MATRIX;
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
			if( _strcmpi(paramDesc.Semantic, semantic) == 0 ){
				D3DXHANDLE hObject = effect->GetAnnotationByName( hParam, "Object" );
				if(hObject){
					const char *object=NULL;
					effect->GetString( hObject, &object );
					if( _strcmpi(object, "light") == 0 ){
						//TRACE2( "float4x4 %s : %s< string Object=\"Light\">;\n", paramDesc.Name, paramDesc.Semantic );
						return static_cast<MATRIX_INDEX>(i);
					} else if( _strcmpi( object, "camera") == 0 ){
						//TRACE2( "float4x4 %s : %s< string Object=\"Camera\">;\n", paramDesc.Name, paramDesc.Semantic );
						assert(false && "Matrix Annotation is wrong.");
						return UNKNOWN_MATRIX;
					} else{
						assert(false && "Matrix Annotation is wrong.");
						return UNKNOWN_MATRIX;
					}
				//anonotationない場合デフォルトのカメラ
				} else {
					assert(false && "Matrix Annotation is wrong.");
					//TRACE2( "float4x4 %s : %s;\n", paramDesc.Name, paramDesc.Semantic );
					assert(paramDesc.Annotations==0);
					return UNKNOWN_MATRIX;
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
			if( _strcmpi(paramDesc.Semantic, semantic) == 0 ){
				D3DXHANDLE hObject = effect->GetAnnotationByName( hParam, "Object" );
				//アノテーションのObjectがあった場合
				if(hObject){
					const char *object=NULL;
					effect->GetString( hObject, &object );
					if( _strcmpi( object, "geometry") == 0 ){
						assert( !(i==DIRECTION || i==POSITION) && " Object of annotaition must be camera or light!" );						
						//TRACE3( "%s%s : %s< string Object=\"Geometry\">;\n", tType, paramDesc.Name, paramDesc.Semantic );
						return static_cast<FLOAT4INDEX>(i);
					} else if( _strcmpi(object, "light") == 0 ){
						if( UNKNOWN_FLOAT4 > static_cast<FLOAT4INDEX>(i+skSemanticsSize) ){
							//TRACE3( "%s%s : %s< string Object=\"Light\">;\n", tType, paramDesc.Name, paramDesc.Semantic );
							return static_cast<FLOAT4INDEX>(i+skSemanticsSize);
						}else {
							//TRACE3( "%s%s : %s< string Object=\"Light\">;\n", tType, paramDesc.Name, paramDesc.Semantic );							
							assert( false && "FLOAT4INDEX over! \"EDGECOLOR\", \"EMISSIVE\",\"TOONCOLOR\" cannot set light!" );
						}
						
					} else if( _strcmpi( object, "camera") == 0 ){
						assert( i==DIRECTION || i==POSITION && "Object of annotaition must be geometry or light!");
						//TRACE3( "%s%s : %s< string Object=\"Camera\">;\n", tType, paramDesc.Name, paramDesc.Semantic );
						return static_cast<FLOAT4INDEX>(i);
					} else{
						assert(false);
					}
				//annotationない場合
				//"EMISSIVE"および"TOONCOLOR"には、ライト色がないため、"Light"は指定できない。
				//EDGECOLORはannotationが存在しない
				} else if( 
					_strcmpi(paramDesc.Semantic, "EMISSIVE") == 0 ||
					_strcmpi(paramDesc.Semantic, "TOONCOLOR") == 0 ||
					_strcmpi(paramDesc.Semantic, "EDGECOLOR") == 0 )
				{
					
					//TRACE3( "%s%s : %s;\n", tType, paramDesc.Name, paramDesc.Semantic );
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
		if( _strcmpi(paramDesc.Semantic, "SPECULARPOWER" ) == 0 ){
			D3DXHANDLE hObject = effect->GetAnnotationByName( hParam, "Object" );
			//アノテーションのObjectがあった場合
			if(hObject){
				const char *object=NULL;
				effect->GetString( hObject, &object );
				if( _strcmpi( object, "geometry") == 0 ){
					//TRACE2( "float %s : %s< string Object=\"Geometry\">;\n", paramDesc.Name, paramDesc.Semantic );
					return SPECULARPOWER;
				} else{
					assert(false && "SPECULARPOWER's Object annotation must be only Geometry.");
				}
			//annotationない場合
			} else{
				//TRACE2( "float %s : %s;\n", paramDesc.Name, paramDesc.Semantic );
				return SPECULARPOWER;
			}
		} else if( _strcmpi(paramDesc.Semantic, "TIME" ) == 0 ){
			if(paramDesc.Annotations!=0){
				//assert(false);
				TRACE0(_T("SyncInEditMode is not implement.\n"));
			}
			//TRACE2( "float %s : %s;\n", paramDesc.Name, paramDesc.Semantic );
			return TIME;
		} else if( _strcmpi(paramDesc.Semantic, "ELAPSEDTIME" ) == 0 ){
			if(paramDesc.Annotations!=0){
				//assert(false);
				TRACE0(_T("SyncInEditMode is not implement.\n"));
			}
			//TRACE2( "float %s : %s;\n", paramDesc.Name, paramDesc.Semantic );
			return ELAPSEDTIME;
		} else if( _strcmpi(paramDesc.Semantic, "STANDARDSGLOBAL" ) == 0 ){
			float ver=0;
			HRESULT hr = effect->GetFloat( hParam, &ver );
			assert(SUCCEEDED(hr));
			assert( ver==0.8f );
			//TRACE2( "float %s : %s;\n", paramDesc.Name, paramDesc.Semantic );
			return STANDARDSGLOBAL;
		} else if(_strcmpi(paramDesc.Semantic, "ZNEAR" ) == 0 ){
			float znear=0;
			HRESULT hr = effect->GetFloat( hParam, &znear );
			assert(SUCCEEDED(hr));
			return ZNEAR;
		} else if(_strcmpi(paramDesc.Semantic, "ZFAR" ) == 0 ){
			float zfar=0;
			HRESULT hr = effect->GetFloat( hParam, &zfar );
			assert(SUCCEEDED(hr));
			return ZFAR;
		}

		//TRACE2( "float %s : %s is unknown float value.\n", paramDesc.Name, paramDesc.Semantic );

		return UNKNOWN_FLOAT;

	}

	void setIfNull( D3DXHANDLE &hLeft, const D3DXHANDLE &hRight ){
		if( hLeft==NULL ){
			hLeft = hRight;
		} else{
			assert( false && "There is a variable with the same meaning.");
		}		
	}

	MME::BaseEffect::ScriptOrder getScriptOrder( ID3DXEffect *effect, D3DXHANDLE hStandardGlobal){
		using namespace MME;
		if( hStandardGlobal ){
			HRESULT hr;
			D3DXHANDLE h = effect->GetAnnotationByName( hStandardGlobal, "ScriptOrder" );
			if( !h ){
				//ScriptOrderが省略された場合はStandard
				return BaseEffect::SO_STANDARD;
			}
			const char* strScriptOrder;
			hr = effect->GetString( h, &strScriptOrder );
			assert( SUCCEEDED(hr) );

			if(strcmpi( strScriptOrder, "standard" )==0){
				return BaseEffect::SO_STANDARD;
			} else if(strcmpi( strScriptOrder, "postprocess" )==0){
				return BaseEffect::SO_POST_PROCESS;			
			} else {
				assert( false  && "not impl or ScriptOrder value is wrong." );
				return BaseEffect::SO_STANDARD;
			}
		}
		else{
			//StandardsGlobalが省略された場合はStandard
			return BaseEffect::SO_STANDARD;
		}
	}


		
}// end unnamespace

namespace MME{
GameLib::Graphics::Texture BaseEffect::msWhiteTexture;

BaseEffect::BaseEffect( const std::string &fxFileName, GameLib::FileIO::InFile file , LPD3DXEFFECTPOOL pool ) 
	:mName(fxFileName),
	mEffect(0),
	mSpecularPowerHandle(0),
	mTimeHandle(0),
	mElapsedTimeHandle(0),
	mStandardGlobalHandle(0),
	mMaterialTextureHandle(0),
	mSphereMapTextureHandle(0),
	mDefaultBackBuffer(),
	mDefaultZBuffer(0),
	mIsError(false),
	mScriptOrder(SO_STANDARD),
	mDiffuse(0),      
	mAmbient(0),      
	mSpecular(0),      
	mPosition(0),
	mDirection(0),
	mEdgeColor(0),
	mEmissive(0),     
	mToonColor(0),    
	mLightDiffuse(0),  
	mLightAmbient(0),  
	mLightSpecular(0), 
	mLightPosition(0),
	mLightDirection(0),
	mWorldMatixArrayHandle(0),
	mViewPortPixelSize(0),
	mToonTextureHandle(0),
	mZNearHandle(0),
	mZFarHandle(0),
	mCurrentTech(0),
	mSpAddHandle(0),
	mParthfHandle(0),
	mTranspHandle(0),
	mUseTextureHandle(0),
	mUseSphereMapHandle(0),
	mUseToonHandle(0),
	mControlObjectSelf(0),
	mIsThereObject_SSInShader(false),
	mIsEnable(true),
	mObjects()
	//mVariables(0)
{
	TRACE1( "%s loading started!\n", mName.c_str() );

	if(!msWhiteTexture){
		msWhiteTexture = GameLib::Graphics::Texture::create( 1, 1, false );
		unsigned* textureData;
		int pitch;
		msWhiteTexture.lock( &textureData, &pitch, 0 );
		*textureData = 0xffffffff;
		msWhiteTexture.unlock( &textureData );
		textureData = 0;
	}

	assert(kMatrixHandlesSize==UNKNOWN_MATRIX);
	for( int i=0; i<UNKNOWN_MATRIX; ++i){
		mMatrixHandles[i]=0;
		mLightMatrixHandles[i]=0;
	}

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

	while(true){
		LPD3DXBUFFER pCompilationErrors;
	
		//MMM特有の関数と#define MIKUMIKUMOVINGを定義する
		//GameLib::FileIO::Manager fm;
		//fm.enableHaltOnError(false);
		while( !file.isFinished() ){}
		int size = file.size() + _countof(gMMMShader) -1;//\0が一つ余計なので 
		char *effectData = new char [size];
		memcpy( effectData, gMMMShader, _countof(gMMMShader ) );
		memcpy( effectData+_countof(gMMMShader)-1, file.data(), file.size() );//\0を上書きするためのー1
		const char *found = strstr( file.data(), "object_ss" );
		if( found ){
			mIsThereObject_SSInShader = true;
		}
		//OutputDebugStringA( effectData );
		//OutputDebugStringA( "\n" );
		

		hr=D3DXCreateEffect(
			pDevice,
			effectData,
			size,
			NULL,
			NULL,
			0,
			pool,
			&mEffect,
			&pCompilationErrors );

		delete effectData;
		effectData=0;
		//hr=D3DXCreateEffectFromFileA(
		//	pDevice,
		//	fxFileName.c_str(),
		//	NULL,
		//	NULL,
		//	0,
		//	NULL,
		//	&mEffect,
		//	&pCompilationErrors );
	
		if(pCompilationErrors){
			const char* p= (const char*)pCompilationErrors->GetBufferPointer();
			OutputDebugStringA( p );
			OutputDebugStringA( "error or warning by fxFileName: " );
			OutputDebugStringA( fxFileName.c_str() );
			OutputDebugStringA( "\n" );

			//OutputDebugString( p );
			if( FAILED(hr) ){
				MessageBoxA(NULL, p, fxFileName.c_str(), MB_OK);
			}
			pCompilationErrors->Release();
			
			assert( SUCCEEDED(hr) && "fx file compile error.");
		}

		if(SUCCEEDED(hr)){
			break;
		}else{
			assert(false && "shared keyword may wrong.");
		}
	}

	//mVariables = new boost::unordered_map< std::string, D3DXHANDLE >();

	std::string fullPath(fxFileName);
	int pos = fullPath.rfind('/');
	std::string path( fullPath, 0, pos+1 );
	
	D3DXEFFECT_DESC effectDesc;
	mEffect->GetDesc( &effectDesc );
	for( UINT iParam = 0; iParam < effectDesc.Parameters; iParam++ )
	{
		D3DXHANDLE hParam = mEffect->GetParameter ( NULL, iParam );
		
		//Matrix
		{
			MATRIX_INDEX midx =findMatrixIndex( mEffect, hParam );

			//TRACE1( "%s\n", TextMatrixIndex[mtype] );
			//見つかったならおしまい
			if(midx!=UNKNOWN_MATRIX){
				setIfNull(mMatrixHandles[midx], hParam);
				continue;
			}

			midx =findLightMatrixIndex( mEffect, hParam );
			if(midx!=UNKNOWN_MATRIX){
				setIfNull(mLightMatrixHandles[midx], hParam);
				continue;
			}
			
			D3DXPARAMETER_DESC paramDesc;
			mEffect->GetParameterDesc( hParam, &paramDesc );

			//bone計算で使用もっとわかりにくい名前のほうが良いと思う
			if( _strcmpi(paramDesc.Name, "WorldMatrixArray" ) == 0 ){
				setIfNull(mWorldMatixArrayHandle, hParam);
				continue;
			}
		}

		{
			FLOAT4INDEX cidx = findFloat4Index( mEffect, hParam );
			//見つかった?
			if(cidx!=UNKNOWN_FLOAT4){
				switch(cidx){
				case DIFFUSE :
					setIfNull( mDiffuse, hParam );
					break;
				case AMBIENT :
					setIfNull( mAmbient, hParam );
					break;
				case SPECULAR :
					setIfNull( mSpecular, hParam );
					break;
				case POSITION :
					setIfNull( mPosition, hParam );
					break;
				case DIRECTION :
					setIfNull( mDirection, hParam );
					break;
				case EDGECOLOR :
					setIfNull( mEdgeColor, hParam );
					break;
				case EMISSIVE :
					setIfNull( mEmissive, hParam );
					break;     
				case TOONCOLOR :
					setIfNull( mToonColor, hParam );
					break;    
				case L_DIFFUSE :
					setIfNull( mLightDiffuse, hParam );
					break;      
				case L_AMBIENT :
					setIfNull( mLightAmbient, hParam );
					break;      
				case L_SPECULAR :
					setIfNull( mLightSpecular, hParam );
					break;    
				case L_POSITION :
					setIfNull( mLightPosition, hParam );
					break;
				case L_DIRECTION :
					setIfNull( mLightDirection, hParam );
					break;
				default :
					assert( false );
					break;
				}
				continue;
			}
		}

		{
			FLOAT_INDEX fidx = findFloatIndex( mEffect, hParam );
			if(fidx==SPECULARPOWER){
				setIfNull(mSpecularPowerHandle, hParam);
				continue;
			} else if( fidx==TIME ){
				setIfNull(mTimeHandle, hParam );
				D3DXHANDLE hSync = mEffect->GetAnnotationByName( mTimeHandle, "SyncInEditMode" );
				if( hSync ){
					TRACE( "SyncInEditMode did not implimentied.\n" );
				}
				continue;
			} else if( fidx==ELAPSEDTIME ){
				setIfNull(mElapsedTimeHandle, hParam );
				D3DXHANDLE hSync = mEffect->GetAnnotationByName( mElapsedTimeHandle, "SyncInEditMode" );
				if( hSync ){
					TRACE( "SyncInEditMode did not implimentied.\n" );
				}
				continue;
			} else if( fidx==STANDARDSGLOBAL ){
				setIfNull( mStandardGlobalHandle, hParam );
				mScriptOrder = getScriptOrder( mEffect, mStandardGlobalHandle );
				continue;
			} else if( fidx==ZNEAR ){
				setIfNull( mZNearHandle, hParam );
			} else if( fidx==ZFAR ){
				setIfNull( mZFarHandle, hParam );			
			}else if( fidx==UNKNOWN_FLOAT ){
			} else {
				assert(false);
			}
		}

		//ViewportSize
		{
			D3DXPARAMETER_DESC pdesc;
			mEffect->GetParameterDesc( hParam, &pdesc );
			if( pdesc.Semantic ){
				if( _strcmpi( pdesc.Semantic, "VIEWPORTPIXELSIZE" ) == 0 ){
					assert( pdesc.Type == D3DXPT_FLOAT );
					assert( pdesc.Columns == 2 );
					setIfNull( mViewPortPixelSize, hParam );
					
					D3DVIEWPORT9 vp;
					hr=pDevice->GetViewport( &vp );
					assert(SUCCEEDED(hr));
					setViewportPixelSize(
						static_cast<float>(vp.Width),
						static_cast<float>(vp.Height) );
					continue;
				}
			}

		}

		//bool     parthf;   // パースペクティブフラグ
		//bool     transp;   // 半透明フラグ
		//bool	 spadd;    // スフィアマップ加算合成フラグ
		{
			D3DXPARAMETER_DESC pdesc;
			mEffect->GetParameterDesc( hParam, &pdesc );
			assert(pdesc.Name);
			if( pdesc.Type == D3DXPT_BOOL ){
				if( _strcmpi( pdesc.Name, "spadd" ) == 0 ){
					setIfNull( mSpAddHandle, hParam );
					continue;
				} else if( _strcmpi( pdesc.Name, "transp" ) == 0 ){
					setIfNull( mTranspHandle, hParam );
					continue;
				}else if( _strcmpi( pdesc.Name, "parthf" ) == 0 ){
					setIfNull( mParthfHandle, hParam );
					continue;
				}else if( _strcmpi( pdesc.Name, "use_texture" ) == 0 ){
					setIfNull( mUseTextureHandle, hParam );
					continue;
				}else if( _strcmpi( pdesc.Name, "use_spheremap" ) == 0 ){
					setIfNull( mUseSphereMapHandle, hParam );
					continue;
				}else if( _strcmpi( pdesc.Name, "use_toon" ) == 0 ){
					setIfNull( mUseToonHandle, hParam );
					continue;
				} 
			}
		}

		//Texture
		{
			D3DXPARAMETER_DESC texDesc;
			mEffect->GetParameterDesc( hParam, &texDesc );
			//TRACE1( "texDesc.Type %d\n", texDesc.Type );
			if(
				texDesc.Type ==  D3DXPT_TEXTURE ||
				texDesc.Type == D3DXPT_TEXTURE1D ||
				texDesc.Type == D3DXPT_TEXTURE2D ||
				texDesc.Type == D3DXPT_TEXTURE3D ||
				texDesc.Type == D3DXPT_TEXTURECUBE )
			{
				if( texDesc.Semantic ){

					if( _strcmpi( texDesc.Semantic, "RENDERCOLORTARGET" )==0 ){
						RenderTargetSharedPtr t = RenderTarget::create( mEffect, hParam );
						
						if( t->isError() ){
							t=NULL;
							assert(false && "mmeの初期化に失敗しました");
							mIsError=true;
							return;
						} else {
							mRenderTargets.push_back(t);
						}
					}
					else if( _strcmpi( texDesc.Semantic, "RENDERDEPTHSTENCILTARGET")==0 ){
						RenderDepthStencilSharedPtr t = RenderDepthStencil::create( mEffect, hParam );
						
						if( t->isError() ){
							t=NULL;
							assert(false && "mmeの初期化に失敗しました");
							mIsError=true;
							return;
						} else {
							mRenderDepthStencils.push_back(t);
						}
					}
					else if( _strcmpi( texDesc.Semantic, "ANIMATEDTEXTURE" )==0 ){
						assert(false && "ANIMATEDTEXTURE Have not implemented.");
					}
					else if( _strcmpi( texDesc.Semantic, "OFFSCREENRENDERTARGET" )==0 ){
						OffScreenRenderSharedPtr t = OffScreenRender::create( mEffect, hParam, getFolder(mName), pool );
					
						if( t->isError() ){
							t=NULL;
							assert(false && "mmeの初期化に失敗しました");
							mIsError=true;
							return;
						} else {
							mOffScreenRenders.push_back(t);
						}
					}
					else if( _strcmpi( texDesc.Semantic, "TEXTUREVALUE" )==0 ){
						assert(false && " TEXTUREVALUE Have not implemented.");
					}
					else if( _strcmpi( texDesc.Semantic, "MATERIALTEXTURE" )==0 ){
						setIfNull( mMaterialTextureHandle, hParam );
					}
					else if( _strcmpi( texDesc.Semantic, "MATERIALSPHEREMAP" )==0 ){
						setIfNull( mSphereMapTextureHandle, hParam );
					}
				} else {
					TextureSharedPtr t = Texture::create( mEffect, hParam, path );
					
					if(t->isError()){
						t=0;
						assert(false && "mmeの初期化に失敗しました");
						mIsError=true;
						return;
					}
					else{
						mTextures.push_back(t);
					}
				}
			}
			continue;
		}

		//D3DXPARAMETER_DESC paramDesc;
		//mEffect->GetParameterDesc( hParam, &paramDesc );

		//std::string name(paramDesc.Name);
		//boost::unordered_map< std::string, D3DXHANDLE >::iterator it = mVariables->find( name );
		//if( it == mVariables->end() ){
		//	(*mVariables)[name] = hParam;
		//} else {
		//	assert(false && "key is doubled!" );
		//}
		

	}// end iParam Loop

	//ControlObject
	//(self)のみ
	{
		mControlObjectSelf = NEW ControlObjectSelf( mEffect, "(self)" );
	}

	setTextures();

	mTextures.shrink_to_fit();
	mRenderDepthStencils.shrink_to_fit();
	mRenderTargets.shrink_to_fit();
	mOffScreenRenders.shrink_to_fit();
}
BaseEffect::~BaseEffect(){
	using namespace ContainerHelper;
	//SAFE_DELETE(mVariables);
	SAFE_RELEASE(mEffect);
	for( int i=0; i<kNumBackBuffers; ++i ){
		SAFE_RELEASE(mDefaultBackBuffer[i]);
	}
	SAFE_RELEASE(mDefaultZBuffer);
	SAFE_DELETE( mControlObjectSelf );
	//mTextures|safeDeleteAll();
	//mRenderDepthStencils|safeDeleteAll();
	//mRenderTargets|safeDeleteAll();
	//mOffScreenRenders|safeDeleteAll();
}





void BaseEffect::sendMatrices(
	const D3DXMATRIX &w,
	const D3DXMATRIX &v,
	const D3DXMATRIX &p
	){
		//WORLD系セマンティック
		{
			D3DXMATRIX iw;
			//逆行列が必要なら計算する
			if(mMatrixHandles[WORLDINVERSE] || mMatrixHandles[WORLDINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iw, 0, &w );
			}
			if(mMatrixHandles[WORLD]){
				mEffect->SetMatrix( mMatrixHandles[WORLD], &w );
			}
			if(mMatrixHandles[WORLDTRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[WORLDTRANSPOSE],&w );
			}
			if(mMatrixHandles[WORLDINVERSE]){
				mEffect->SetMatrix( mMatrixHandles[WORLDINVERSE], &iw );
			}
			if(mMatrixHandles[WORLDINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[WORLDINVERSETRANSPOSE], &iw );
			}
		}

		//VIEW系セマンティック
		{
			D3DXMATRIX iv;
			//逆行列が必要なら計算する
			if(mMatrixHandles[VIEWINVERSE] || mMatrixHandles[VIEWINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iv, 0, &v );
			}
			if(mMatrixHandles[VIEW]){
				mEffect->SetMatrix( mMatrixHandles[VIEW], &v );
			}
			if(mMatrixHandles[VIEWTRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[VIEWTRANSPOSE],&v );
			}
			if(mMatrixHandles[VIEWINVERSE]){
				mEffect->SetMatrix( mMatrixHandles[VIEWINVERSE], &iv );
			}
			if(mMatrixHandles[VIEWINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[VIEWINVERSETRANSPOSE], &iv );
			}
		}

		//PROJECTION系セマンティック
		{
			D3DXMATRIX ip;
			//逆行列が必要なら計算する
			if(mMatrixHandles[PROJECTIONINVERSE] || mMatrixHandles[PROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &ip, 0, &p );
			}
			if(mMatrixHandles[PROJECTION]){
				mEffect->SetMatrix( mMatrixHandles[PROJECTION], &p );
			}
			if(mMatrixHandles[PROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[PROJECTIONTRANSPOSE],&p );
			}
			if(mMatrixHandles[PROJECTIONINVERSE]){
				mEffect->SetMatrix( mMatrixHandles[PROJECTIONINVERSE], &ip );
			}
			if(mMatrixHandles[PROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[PROJECTIONINVERSETRANSPOSE], &ip );
			}
		}

		//WORLDVIEW系セマンティック
		if(
			mMatrixHandles[WORLDVIEW] ||
			mMatrixHandles[WORLDVIEWINVERSE] ||
			mMatrixHandles[WORLDVIEWTRANSPOSE] || 
			mMatrixHandles[WORLDVIEWINVERSETRANSPOSE])
		{
			D3DXMATRIX wv=w*v;

			D3DXMATRIX iwv;

			//逆行列が必要なら計算する
			if(mMatrixHandles[WORLDVIEWINVERSE] || mMatrixHandles[WORLDVIEWINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iwv, 0, &wv );
			}
			if(mMatrixHandles[WORLDVIEW]){
				mEffect->SetMatrix( mMatrixHandles[WORLDVIEW], &wv );
			}
			if(mMatrixHandles[WORLDVIEWTRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[WORLDVIEWTRANSPOSE],&wv );
			}
			if(mMatrixHandles[WORLDVIEWINVERSE]){
				mEffect->SetMatrix( mMatrixHandles[WORLDVIEWINVERSE], &iwv );
			}
			if(mMatrixHandles[WORLDVIEWINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[WORLDVIEWINVERSETRANSPOSE], &iwv );
			}
		}

		//VIEWPROJECTION系セマンティック
		if(
			mMatrixHandles[VIEWPROJECTION] ||
			mMatrixHandles[VIEWPROJECTIONINVERSE] ||
			mMatrixHandles[VIEWPROJECTIONTRANSPOSE] || 
			mMatrixHandles[VIEWPROJECTIONINVERSETRANSPOSE])
		{
			D3DXMATRIX vp=v*p;

			D3DXMATRIX ivp;

			//逆行列が必要なら計算する
			if(mMatrixHandles[VIEWPROJECTIONINVERSE] || mMatrixHandles[VIEWPROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &ivp, 0, &vp );
			}
			if(mMatrixHandles[VIEWPROJECTION]){
				mEffect->SetMatrix( mMatrixHandles[VIEWPROJECTION], &vp );
			}
			if(mMatrixHandles[VIEWPROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[VIEWPROJECTIONTRANSPOSE],&vp );
			}
			if(mMatrixHandles[VIEWPROJECTIONINVERSE]){
				mEffect->SetMatrix( mMatrixHandles[VIEWPROJECTIONINVERSE], &ivp );
			}
			if(mMatrixHandles[VIEWPROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[VIEWPROJECTIONINVERSETRANSPOSE], &ivp );
			}
		}

		//WORLDVIEWPROJECTION系セマンティック
		if(
			mMatrixHandles[WORLDVIEWPROJECTION] ||
			mMatrixHandles[WORLDVIEWPROJECTIONINVERSE] ||
			mMatrixHandles[WORLDVIEWPROJECTIONTRANSPOSE] || 
			mMatrixHandles[WORLDVIEWPROJECTIONINVERSETRANSPOSE])
		{
			D3DXMATRIX wvp=w*v*p;

			D3DXMATRIX iwvp;

			//逆行列が必要なら計算する
			if(mMatrixHandles[WORLDVIEWPROJECTIONINVERSE] || mMatrixHandles[WORLDVIEWPROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iwvp, 0, &wvp );
			}
			if(mMatrixHandles[WORLDVIEWPROJECTION]){
				mEffect->SetMatrix( mMatrixHandles[WORLDVIEWPROJECTION], &wvp );
			}
			if(mMatrixHandles[WORLDVIEWPROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[WORLDVIEWPROJECTIONTRANSPOSE],&wvp );
			}
			if(mMatrixHandles[WORLDVIEWPROJECTIONINVERSE]){
				mEffect->SetMatrix( mMatrixHandles[WORLDVIEWPROJECTIONINVERSE], &iwvp );
			}
			if(mMatrixHandles[WORLDVIEWPROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mMatrixHandles[WORLDVIEWPROJECTIONINVERSETRANSPOSE], &iwvp );
			}
		}
}

void BaseEffect::sendLightMatrices(
	const D3DXMATRIX &w,
	const D3DXMATRIX &v,
	const D3DXMATRIX &p
	){
		//L_WORLD系セマンティック
		{
			D3DXMATRIX iw;
			//逆行列が必要なら計算する
			if(mLightMatrixHandles[WORLDINVERSE] || mLightMatrixHandles[WORLDINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iw, 0, &w );
			}
			if(mLightMatrixHandles[WORLD]){
				mEffect->SetMatrix( mLightMatrixHandles[WORLD], &w );
			}
			if(mLightMatrixHandles[WORLDTRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[WORLDTRANSPOSE],&w );
			}
			if(mLightMatrixHandles[WORLDINVERSE]){
				mEffect->SetMatrix( mLightMatrixHandles[WORLDINVERSE], &iw );
			}
			if(mLightMatrixHandles[WORLDINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[WORLDINVERSETRANSPOSE], &iw );
			}
		}

		//L_VIEW系セマンティック
		{
			D3DXMATRIX iv;
			//逆行列が必要なら計算する
			if(mLightMatrixHandles[VIEWINVERSE] || mLightMatrixHandles[VIEWINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iv, 0, &v );
			}
			if(mLightMatrixHandles[VIEW]){
				mEffect->SetMatrix( mLightMatrixHandles[VIEW], &v );
			}
			if(mLightMatrixHandles[VIEWTRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[VIEWTRANSPOSE],&v );
			}
			if(mLightMatrixHandles[VIEWINVERSE]){
				mEffect->SetMatrix( mLightMatrixHandles[VIEWINVERSE], &iv );
			}
			if(mLightMatrixHandles[VIEWINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[VIEWINVERSETRANSPOSE], &iv );
			}
		}

		//L_PROJECTION系セマンティック
		{
			D3DXMATRIX ip;
			//逆行列が必要なら計算する
			if(mLightMatrixHandles[PROJECTIONINVERSE] || mLightMatrixHandles[PROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &ip, 0, &p );
			}
			if(mLightMatrixHandles[PROJECTION]){
				mEffect->SetMatrix( mLightMatrixHandles[PROJECTION], &p );
			}
			if(mLightMatrixHandles[PROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[PROJECTIONTRANSPOSE],&p );
			}
			if(mLightMatrixHandles[PROJECTIONINVERSE]){
				mEffect->SetMatrix( mLightMatrixHandles[PROJECTIONINVERSE], &ip );
			}
			if(mLightMatrixHandles[PROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[PROJECTIONINVERSETRANSPOSE], &ip );
			}
		}

		//L_WORLDVIEW系セマンティック
		if(
			mLightMatrixHandles[WORLDVIEW] ||
			mLightMatrixHandles[WORLDVIEWINVERSE] ||
			mLightMatrixHandles[WORLDVIEWTRANSPOSE] || 
			mLightMatrixHandles[WORLDVIEWINVERSETRANSPOSE])
		{
			D3DXMATRIX wv=w*v;

			D3DXMATRIX iwv;

			//逆行列が必要なら計算する
			if(mLightMatrixHandles[WORLDVIEWINVERSE] || mLightMatrixHandles[WORLDVIEWINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iwv, 0, &wv );
			}
			if(mLightMatrixHandles[WORLDVIEW]){
				mEffect->SetMatrix( mLightMatrixHandles[WORLDVIEW], &wv );
			}
			if(mLightMatrixHandles[WORLDVIEWTRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[WORLDVIEWTRANSPOSE],&wv );
			}
			if(mLightMatrixHandles[WORLDVIEWINVERSE]){
				mEffect->SetMatrix( mLightMatrixHandles[WORLDVIEWINVERSE], &iwv );
			}
			if(mLightMatrixHandles[WORLDVIEWINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[WORLDVIEWINVERSETRANSPOSE], &iwv );
			}
		}

		//L_VIEWPROJECTION系セマンティック
		if(
			mLightMatrixHandles[VIEWPROJECTION] ||
			mLightMatrixHandles[VIEWPROJECTIONINVERSE] ||
			mLightMatrixHandles[VIEWPROJECTIONTRANSPOSE] || 
			mLightMatrixHandles[VIEWPROJECTIONINVERSETRANSPOSE])
		{
			D3DXMATRIX vp=v*p;

			D3DXMATRIX ivp;

			//逆行列が必要なら計算する
			if(mLightMatrixHandles[VIEWPROJECTIONINVERSE] || mLightMatrixHandles[VIEWPROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &ivp, 0, &vp );
			}
			if(mLightMatrixHandles[VIEWPROJECTION]){
				mEffect->SetMatrix( mLightMatrixHandles[VIEWPROJECTION], &vp );
			}
			if(mLightMatrixHandles[VIEWPROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[VIEWPROJECTIONTRANSPOSE],&vp );
			}
			if(mLightMatrixHandles[VIEWPROJECTIONINVERSE]){
				mEffect->SetMatrix( mLightMatrixHandles[VIEWPROJECTIONINVERSE], &ivp );
			}
			if(mLightMatrixHandles[VIEWPROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[VIEWPROJECTIONINVERSETRANSPOSE], &ivp );
			}
		}

		//L_WORLDVIEWPROJECTION系セマンティック
		if(
			mLightMatrixHandles[WORLDVIEWPROJECTION] ||
			mLightMatrixHandles[WORLDVIEWPROJECTIONINVERSE] ||
			mLightMatrixHandles[WORLDVIEWPROJECTIONTRANSPOSE] || 
			mLightMatrixHandles[WORLDVIEWPROJECTIONINVERSETRANSPOSE])
		{
			D3DXMATRIX wvp=w*v*p;

			D3DXMATRIX iwvp;

			//逆行列が必要なら計算する
			if(mLightMatrixHandles[WORLDVIEWPROJECTIONINVERSE] || mLightMatrixHandles[WORLDVIEWPROJECTIONINVERSETRANSPOSE]){
				D3DXMatrixInverse( &iwvp, 0, &wvp );
			}
			if(mLightMatrixHandles[WORLDVIEWPROJECTION]){
				mEffect->SetMatrix( mLightMatrixHandles[WORLDVIEWPROJECTION], &wvp );
			}
			if(mLightMatrixHandles[WORLDVIEWPROJECTIONTRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[WORLDVIEWPROJECTIONTRANSPOSE],&wvp );
			}
			if(mLightMatrixHandles[WORLDVIEWPROJECTIONINVERSE]){
				mEffect->SetMatrix( mLightMatrixHandles[WORLDVIEWPROJECTIONINVERSE], &iwvp );
			}
			if(mLightMatrixHandles[WORLDVIEWPROJECTIONINVERSETRANSPOSE]){
				mEffect->SetMatrixTranspose( mLightMatrixHandles[WORLDVIEWPROJECTIONINVERSETRANSPOSE], &iwvp );
			}
		}
}

void BaseEffect::setRenderTarget( int renderTargetIndex, RenderTarget *texture ){
	if(texture){
		texture->setRenderTarget( renderTargetIndex, this );
	} else{
		HRESULT hr;
		IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();

		LPDIRECT3DSURFACE9 pSurf = mDefaultBackBuffer[renderTargetIndex];
		//レンダリングターゲットをテクスチャにセット
		hr=pDevice->SetRenderTarget( renderTargetIndex, pSurf );				
		assert(SUCCEEDED(hr));
		if( renderTargetIndex==0){
			assert( pSurf );
			D3DSURFACE_DESC desc;
			hr=pSurf->GetDesc( &desc );
			assert(SUCCEEDED(hr));

			//set viewport
			D3DVIEWPORT9 vp;
			vp.X = vp.Y = 0;
			vp.Width = desc.Width;
			vp.Height = desc.Height;
			vp.MinZ = 0.f;
			vp.MaxZ = 1.f;
			hr=pDevice->SetViewport( &vp );
			assert(SUCCEEDED(hr));

			//※この値は、MMDのスクリーンもしくはオフスクリーンレンダリングターゲットのサイズを指す。
			//Scriptsの"RenderColorTarget"コマンドで、レンダリングターゲットが変更しても、
			//この値は変化しない。
			//setViewportPixelSize( static_cast<float>(vp.Width), static_cast<float>(vp.Height) );
		}

	}

	
	
}

void BaseEffect::setRenderDepthStencil( RenderDepthStencil *rds ){
	
	if(rds){
		rds->setDepthStencilSurface();
	} else {
		HRESULT hr;
		IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();

		//レンダリングターゲットをテクスチャにセット
		LPDIRECT3DSURFACE9 pSurf = mDefaultZBuffer;
			
		hr=pDevice->SetDepthStencilSurface( pSurf );				
		assert(SUCCEEDED(hr));
		pSurf=0;
	}
}

void BaseEffect::clearRenderTarget( float r, float g, float b, float a ){
	HRESULT hr;
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	hr=pDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_COLORVALUE(r,g,b,a),
		0.f,
		0 );
	assert(SUCCEEDED(hr));
}
void BaseEffect::clearRenderDepthStencil( float z ){
	HRESULT hr;
	IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
	hr=pDevice->Clear(
		0,
		NULL,//rect
		D3DCLEAR_ZBUFFER ,
		0,//color
		z,//
		0 );//stencil 
	
	assert(SUCCEEDED(hr));
}

RenderTargetSharedPtr BaseEffect::findRenderTarget( const std::string &name ){
	using namespace ContainerHelper;
	std::vector<RenderTargetSharedPtr>::iterator it = mRenderTargets|findByName( name.c_str() );
	if(it==mRenderTargets.end()){
		return NULL;
	}
	return *it;
}


RenderDepthStencilSharedPtr BaseEffect::findRenderDepthStencil( const std::string &name ){
	using namespace ContainerHelper;

	std::vector<RenderDepthStencilSharedPtr>::iterator it = mRenderDepthStencils|findByName( name.c_str() );
	if(it==mRenderDepthStencils.end()){
		return NULL;
	}
	return *it;
}

void BaseEffect::setTexture( GameLib::Graphics::Texture tex ){
	HRESULT hr;
	if( tex.dxTeture() && mMaterialTextureHandle ){
		assert( tex.dxTeture() );
		hr = mEffect->SetTexture( mMaterialTextureHandle, tex.dxTeture() );
		assert( SUCCEEDED(hr) );
	} else if(mMaterialTextureHandle){
		hr = mEffect->SetTexture( mMaterialTextureHandle, msWhiteTexture.dxTeture() );
		assert( SUCCEEDED(hr) );
	}
}


void BaseEffect::setLightPosition(  const GameLib::Math::Vector4& position ){
	if( mLightPosition ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mLightPosition, &(position.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}
void BaseEffect::setLightDirection( const GameLib::Math::Vector4& dir ){
	if( mLightDirection ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mLightDirection, &(dir.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}

void BaseEffect::setLightDiffuse( const GameLib::Math::Vector4& diffuse ){
	if( mLightDiffuse ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mLightDiffuse, &(diffuse.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}
void BaseEffect::setLightAmbient( const GameLib::Math::Vector4& amb ){
	if( mLightAmbient ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mLightAmbient, &(amb.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}

void BaseEffect::setLightSpecular( const GameLib::Math::Vector4& sp ){
	if( mLightSpecular ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mLightSpecular, &(sp.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}

void BaseEffect::setEyePosition( const GameLib::Math::Vector4& position ){
	if( mPosition ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mPosition, &(position.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}
void BaseEffect::setEyeDirection( const GameLib::Math::Vector4& dir ){
	if( mDirection ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mDirection, &(dir.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}
void BaseEffect::setDiffuseColor( const GameLib::Math::Vector4& diffuse ){
	if( mDiffuse ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mDiffuse, &(diffuse.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}
void BaseEffect::setSpecularColor( const GameLib::Math::Vector4& sp ){
	if( mSpecular ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mSpecular, &(sp.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}
void BaseEffect::setEmissionColor( const GameLib::Math::Vector4& emmission ){
	if( mEmissive ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mEmissive, &(emmission.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}
void BaseEffect::setAmbientColor( const GameLib::Math::Vector4& amb ){
	if( mAmbient ){ 
		HRESULT hr;
		hr=mEffect->SetFloatArray( mAmbient, &(amb.x), 4 );
		assert( SUCCEEDED(hr) );
	}
}
void BaseEffect::setSpecularSharpness( float ss ){
	if( mSpecularPowerHandle ){ 
		HRESULT hr;
		hr=mEffect->SetFloat( mSpecularPowerHandle, ss );
		assert( SUCCEEDED(hr) );
	}
}

void BaseEffect::sendWorldMatrixArray( const D3DXMATRIX *worldMatrices, int size ){
	if( mWorldMatixArrayHandle ){
		HRESULT hr;
		hr=mEffect->SetMatrixArray( mWorldMatixArrayHandle, worldMatrices, size );
		assert( SUCCEEDED(hr) );
	} else{
		//assert(false);
		//TRACE2( "this shader can not draw vertex blend object.\n %s, line %d\n", __FILE__, __LINE__ );
	}

}

void BaseEffect::commitChanges(){
	HRESULT hr;
	hr=mEffect->CommitChanges();
	assert( SUCCEEDED(hr) );
}
//シェーダー内で使用する
//レンダリングターゲットを戻したりするときに参照する
//technique TShader <
//string Script = 
//"RenderColorTarget0 = RenderTarget;"
//"RenderDepthStencilTarget=DepthBuffer;"
//"ClearSetColor=ClearColor;"
//"ClearSetDepth=ClearDepth;"
//"Clear=Color;"
//"Clear = Depth;"
//"ScriptExternal=color;"
//"Pass=P0;" ;
//"RenderDepthStencilTarget=;"
//"RenderColorTarget0 = ;"

void BaseEffect::saveCurrentBackBuffers(){
	HRESULT hr;
	GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
	IDirect3DDevice9 *pDevice = m.dxDevice();

	for( int i=0; i<kNumBackBuffers; ++i ){
		hr=pDevice->GetRenderTarget(i, &(mDefaultBackBuffer[i]));
		assert( SUCCEEDED(hr) || !mDefaultBackBuffer[i]);
		
	}
	hr=pDevice->GetDepthStencilSurface(&mDefaultZBuffer);
	assert(SUCCEEDED(hr));
	
}

void BaseEffect::releaseCurrentBackBuffers(){

	assert(false && "この関数使わない予定" );
	for( int i=0; i<kNumBackBuffers; ++i ){
		SAFE_RELEASE( mDefaultBackBuffer[i] );	
	}
	SAFE_RELEASE( mDefaultZBuffer );	
}

void BaseEffect::setTextures(){
	for( int i=0, size=mTextures.size(); i<size; ++i )
	{
		mTextures[i]->send( mEffect );
	}

	for( int i=0, size=mRenderTargets.size(); i<size; ++i )
	{
		mRenderTargets[i]->send( mEffect );
	}

	for( int i=0, size=mRenderDepthStencils.size(); i<size; ++i ){
		mRenderDepthStencils[i]->send(mEffect );
	}


	for( int i=0, size=mOffScreenRenders.size(); i<size; ++i )
	{
		mOffScreenRenders[i]->send( mEffect );
	}
}

void BaseEffect::setViewportPixelSize( float x, float y ){
	if( mViewPortPixelSize ){
		float xy[2] = { x, y };
		HRESULT hr;
		hr=mEffect->SetFloatArray( mViewPortPixelSize, xy, 2 );
		assert(SUCCEEDED(hr));
	}
}


void BaseEffect::setToonTexture( GameLib::Graphics::Texture toonTexture ){
	if( mToonTextureHandle ){
		HRESULT hr;
		hr=mEffect->SetTexture( mToonTextureHandle, toonTexture.dxTeture() );
		assert(SUCCEEDED(hr));
	}
}
void BaseEffect::setToonColor( const GameLib::Math::Vector4& toon ){
	if( mToonColor ){
		HRESULT hr;
		hr=mEffect->SetFloatArray( mToonColor, &(toon.x), 4 );
		assert(SUCCEEDED(hr));
	}
}

void BaseEffect::setSphereTexture( GameLib::Graphics::Texture sphereTexture ){
	if( mSphereMapTextureHandle ){
		HRESULT hr;
		hr=mEffect->SetTexture( mSphereMapTextureHandle, sphereTexture.dxTeture() );
		assert(SUCCEEDED(hr));
	}
}

void BaseEffect::setSphereTextureAdditive( bool isAdditive ){
	if( mSpAddHandle ){
		HRESULT hr;
		hr=mEffect->SetBool( mSpAddHandle, isAdditive );
		assert(SUCCEEDED(hr));
	}
}


bool BaseEffect::canDraw(
	UseTexture useTexture,
	UseSphereMap useSphereMap,
	UseToon useToon,
	unsigned int materialIndex ) const
{
	return 
		(useTexture==mUseTexture) &&
		(useSphereMap == mUseSphereMap) &&
		(useToon == mUseToon) &&
		mCurrentTech->canDraw( materialIndex );
}

void BaseEffect::setUseFlag()const{
	HRESULT hr;
	
	if( mUseTextureHandle ){
		hr=mEffect->SetBool( mUseTextureHandle, mUseTexture );
		assert(SUCCEEDED(hr));
	}
	if( mUseSphereMapHandle ){
		hr=mEffect->SetBool( mUseSphereMapHandle, mUseSphereMap );
		assert(SUCCEEDED(hr));
	}
	if( mUseToonHandle ){
		hr=mEffect->SetBool( mUseToonHandle, mUseToon );
		assert(SUCCEEDED(hr));
	}
}

void BaseEffect::setTime( float time ){
	if(mTimeHandle){
		HRESULT hr=mEffect->SetFloat( mTimeHandle, time );
		assert(SUCCEEDED(hr));
	}

}
void BaseEffect::setElapsedTime( float elapsedTime ){
	if(mElapsedTimeHandle){
		HRESULT hr=mEffect->SetFloat( mElapsedTimeHandle, elapsedTime );
		assert(SUCCEEDED(hr));
	}
}

void BaseEffect::setEdgeColor( const GameLib::Math::Vector4& c ){
	if(mEdgeColor){
		HRESULT hr=mEffect->SetFloatArray( mEdgeColor, &(c.x), 4 );
		assert(SUCCEEDED(hr));
	}
}

void BaseEffect::setZNear( float znear ){
	if(mZNearHandle){
		HRESULT hr=mEffect->SetFloat( mZNearHandle, znear );
		assert(SUCCEEDED(hr));
	}
}

void BaseEffect::setZFar( float zfar ){
	if(mZFarHandle){
		HRESULT hr=mEffect->SetFloat( mZFarHandle, zfar );
		assert(SUCCEEDED(hr));
	}
}

void BaseEffect::drawOffScreen(){
	if( mIsEnable ){
		for( int i=0, size=mOffScreenRenders.size(); i<size; ++i ){
			mOffScreenRenders[i]->draw();
		}
	}
}

OffScreenRenderSharedPtr BaseEffect::findOffScreen(  const std::string &name ){
	using namespace ContainerHelper;
	std::vector<OffScreenRenderSharedPtr>::iterator it= mOffScreenRenders|findByName( name.c_str() );
	if( it==mOffScreenRenders.end() ) {
		return NULL;
	} else {
		return *it;
	}
}


void BaseEffect::backup(){
	HRESULT hr = mEffect->OnLostDevice();
	assert( SUCCEEDED(hr) );
	for( int i=0, size=mRenderTargets.size(); i<size; ++i )
	{
		mRenderTargets[i]->backup();
	}
	RenderTarget::clearCache();

	for( int i=0, size=mRenderDepthStencils.size(); i<size; ++i ){
		mRenderDepthStencils[i]->backup();
	}
	RenderDepthStencil::clearCache();

	
	for( int i=0, size=mOffScreenRenders.size(); i<size;++i ){
		mOffScreenRenders[i]->backup();
	}
	OffScreenRender::clearCache();

}

void BaseEffect::recover(){
	HRESULT hr=mEffect->OnResetDevice();
	assert( SUCCEEDED(hr) );

		for( int i=0, size=mRenderTargets.size(); i<size; ++i )
	{
		mRenderTargets[i]->backup();
	}
	RenderTarget::shrinkToFitCache();
	
	for( int i=0, size=mRenderDepthStencils.size(); i<size; ++i ){
		mRenderDepthStencils[i]->backup();
	}
	RenderDepthStencil::shrinkToFitCache();
	
	for( int i=0, size=mOffScreenRenders.size(); i<size;++i ){
		mOffScreenRenders[i]->backup();
	}
	OffScreenRender::shrinkToFitCache();

}


//void BaseEffect::setFloat( const std::string &name, float value ){
//	D3DXHANDLE h = (*mVariables)[name];
//	assert(h);
//	mEffect->SetFloat( h, value );
//}
//void BaseEffect::setFloatArray( const std::string &name, const float *pValue, unsigned int count ){
//	D3DXHANDLE h = (*mVariables)[name];
//	assert(h);
//	mEffect->SetFloatArray( h, pValue, count );
//}
//
//void BaseEffect::setInt( const std::string &name, int value ){
//	D3DXHANDLE h = (*mVariables)[name];
//	assert(h);
//	mEffect->SetInt( h, value );
//}
//void BaseEffect::setIntArray( const std::string &name, const int *pValue, unsigned int count ){
//	D3DXHANDLE h = (*mVariables)[name];
//	assert(h);
//	mEffect->SetIntArray( h, pValue, count );
//}

D3DXHANDLE BaseEffect::getHandle(const std::string &name )const{
	D3DXHANDLE h = mEffect->GetParameterByName( NULL, name.c_str() );
	assert(h);
	return h;
}

void BaseEffect::setFloat( D3DXHANDLE h, float value ){
	HRESULT hr = mEffect->SetFloat( h, value );
	assert(SUCCEEDED(hr));
}
void BaseEffect::setFloatArray( D3DXHANDLE h, const float *pValue, unsigned int count ){
	HRESULT hr = mEffect->SetFloatArray( h, pValue, count );
	assert(SUCCEEDED(hr));
}

void BaseEffect::setInt( D3DXHANDLE h, int value ){
	HRESULT hr = mEffect->SetInt( h, value );
	assert(SUCCEEDED(hr));
}

void BaseEffect::setIntArray( D3DXHANDLE h, const int *pValue, unsigned int count ){
	HRESULT hr = mEffect->SetIntArray( h, pValue, count );
	assert(SUCCEEDED(hr));
}

void BaseEffect::drawGeometry(){
	//boost::timer t;
	//t.restart();
	//TRACE1( "%s start!\n", mObjects[0]->getModelFileName().c_str() );
	assert( mObjects );
	for(
		DrawObjects::iterator it = mObjects->begin(), end = mObjects->end();
		it!=end;
		++it )
	{
		if( Object::IObjectSharedPtr p = it->lock() ){

			if( mControlObjectSelf ){
				mControlObjectSelf->send( mEffect, p );
			}
			p->draw();
		}
	}
	//TRACE2( "%s end!  %f sec\n", mObjects[0]->getModelFileName().c_str(), t.elapsed() );

}

//void BaseEffect:: matchByModelFileName(
//	std::vector<Object::IObjectSharedPtr> *out,
//	const boost::xpressive::sregex & filename  )const
//{
//	using namespace boost::xpressive;
//
//	for(
//		DrawObjects::const_iterator it = mObjects->begin(), end = mObjects->end();
//		it!=end;
//		++it )
//	{
//		if( Object::IObjectSharedPtr p = it->lock() ){
//			smatch what;
//			assert(false);
//			//putに同じオブジェクト入っていたら2重登録になるよ。
//			//バグだな
//			if (regex_match( p->getModelFileName(), what, filename)) {
//				out->push_back( p );
//			}
//		}
//	}
//}

unsigned int BaseEffect::getNumberOfOffScreens()const{
	return mOffScreenRenders.size();
}

OffScreenRenderSharedPtr BaseEffect::getOffScreenAt( unsigned int i){
	return mOffScreenRenders[i];
}

void BaseEffect::setObjectsPtr(const DrawObjectsSharedPtr & objects){
	mObjects=objects;
}
//
//void BaseEffect::add( const Object::IObjectSharedPtr &obj ){
//	mObjects->push_back( obj );
//	for( unsigned int i=0, size=mOffScreenRenders.size(); i<size; ++i ){
//		mOffScreenRenders[i]->add( obj );
//	}
//}
//
//void BaseEffect::removeRemovableObjects(){
//	
//	for(unsigned int i=0, size=mOffScreenRenders.size(); i<size; ++i ){		
//		mOffScreenRenders[i]->removeRemovableObjects();
//	}
//	
//	for(
//		DrawObjects::iterator it = mObjects->begin();
//		it!= mObjects->end(); )
//	{
//		if( Object::IObjectSharedPtr p = it->lock() ){
//			if( p->canRemove() ){
//				it = mObjects->erase(it);
//			} else {
//				++it;
//			}
//		} else{
//			it = mObjects->erase(it);
//		}
//	}
//}
//void BaseEffect::clearAllObjects(){
//	clearAllObjectsInOffScreen();
//	mObjects->clear();
//}
//void BaseEffect::clearAllObjectsInOffScreen(){
//	for( int i=0, size=mOffScreenRenders.size(); i<size;++i ){
//		mOffScreenRenders[i]->clearAllObjects();
//	}
//}



} //end namespace MME
