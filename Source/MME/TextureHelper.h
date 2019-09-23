#pragma once
#include"formats.h"
#include<d3dx9.h>
#include"helper/ReplaceTxt.h"
#include"helper/MyOutputDebugString.h"
#include<assert.h>
#include<GameLib/Framework.h>


#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#endif//SAFE_RELEASE


namespace MME{

static D3DXHANDLE getWidth(  ID3DXEffect *effect, D3DXHANDLE hTex, int *width ){
	HRESULT hr;
	
	D3DXHANDLE hWidth=0;
	hWidth=effect->GetAnnotationByName( hTex, "Width" );
	if(hWidth){
		hr=effect->GetInt( hWidth, width );
		assert( SUCCEEDED(hr) );
	}
	return hWidth;
}

static D3DXHANDLE getHeight(  ID3DXEffect *effect, D3DXHANDLE hTex, int *height ){
	HRESULT hr;
	
	D3DXHANDLE h=0;
	h=effect->GetAnnotationByName( hTex, "Height" );
	if(h){
		hr=effect->GetInt( h, height );
		assert( SUCCEEDED(hr) );
	}
	return h;
}

static D3DXHANDLE getDepth(  ID3DXEffect *effect, D3DXHANDLE hTex, int *depth ){
	HRESULT hr;
	
	D3DXHANDLE h=0;
	h=effect->GetAnnotationByName( hTex, "Depth" );
	if(h){
		hr=effect->GetInt( h, depth );
		assert( SUCCEEDED(hr) );
	}
	return h;
}

static D3DXHANDLE getDimensions(
	ID3DXEffect *effect,
	D3DXHANDLE hTex,
	int *height, int *width, int *depth )
{
	HRESULT hr;

	D3DXHANDLE hDimensions=0;
	hDimensions = effect->GetAnnotationByName( hTex, "Dimensions" );
	if( hDimensions ){
		int dimensions[3] = {0};
		D3DXPARAMETER_DESC desc;
		hr=effect->GetParameterDesc( hDimensions, &desc );
		assert( SUCCEEDED(hr) );
		assert(false && "一回デバッグ中に配列数合ってるか確認 elements か　columns か自信ない");
		assert( desc.Elements == 2 || desc.Elements == 3 );
		hr=effect->GetIntArray( hDimensions, dimensions, desc.Elements );
		assert( SUCCEEDED(hr) );
		*width = dimensions[0];
		*height = dimensions[1];
		*depth = dimensions[2];
	}
	return hDimensions;
}

//static D3DXHANDLE getViewPortRatio(
//	ID3DXEffect *effect,
//	D3DXHANDLE hTex,
//	int *width, int *height )
//{
//	GameLib::Framework fw = GameLib::Framework::instance();
//	HRESULT hr;
//	D3DXHANDLE hViewPortRatio = 0;
//	hViewPortRatio = effect->GetAnnotationByName( hTex, "ViewPortRatio" );
//
//	if( hViewPortRatio ){
//		float viewportratio[2] = {1.f};
//		D3DXPARAMETER_DESC desc;
//		hr=effect->GetParameterDesc( hViewPortRatio, &desc );
//		assert( SUCCEEDED(hr) );
//		hr=effect->GetFloatArray( hViewPortRatio, viewportratio, 2 );
//		assert( SUCCEEDED(hr) );
//		*width = static_cast<int>(viewportratio[0]*fw.width() );
//		*height = static_cast<int>(viewportratio[1]*fw.height() );
//	}
//	return hViewPortRatio;
//}

static D3DXHANDLE getViewPortRatio(
	ID3DXEffect *effect,
	D3DXHANDLE hTex,
	float *xRate, float *yRate )
{
	HRESULT hr;
	D3DXHANDLE hViewPortRatio = 0;
	hViewPortRatio = effect->GetAnnotationByName( hTex, "ViewPortRatio" );

	if( hViewPortRatio ){
		float viewportratio[2] = {1.f};
		D3DXPARAMETER_DESC desc;
		hr=effect->GetParameterDesc( hViewPortRatio, &desc );
		assert( SUCCEEDED(hr) );
		hr=effect->GetFloatArray( hViewPortRatio, viewportratio, 2 );
		assert( SUCCEEDED(hr) );
		*xRate= viewportratio[0];
		*yRate = viewportratio[1];
	}
	return hViewPortRatio;
}

static D3DFORMAT getFormat( ID3DXEffect *effect, D3DXHANDLE hTex, D3DFORMAT DefalutFmt ){
	HRESULT hr;
	//・string Format
	//	テクスチャのフォーマットを指定する。
	//	ResourceNameが指定されているならば、画像ファイルからフォーマットが取得され、
	//	このアノテーションの設定は無視される。
	//	
	//	指定可能なフォーマットは、D3DFORMAT（http://msdn.microsoft.com/ja-jp/library/bb172558(v=VS.85).aspx）
	//	を参照。
	//	
	//	"A8R8G8B8"、"FMT_A8R8G8B8"、"D3DFMT_A8R8G8B8"のいずれの書式でも指定できる。
	D3DXHANDLE hFormat=0;
	D3DFORMAT format = DefalutFmt;
	hFormat=effect->GetAnnotationByName( hTex, "Format" );
	if(hFormat){
		const char* text = NULL;
		hr=effect->GetString( hFormat, &text );
		assert( SUCCEEDED(hr) );
		//見つからなかった場合がわかるように代入
		format = D3DFMT_UNKNOWN;

		std::string formatText = replaceText( text, "D3DFMT_", "" );
		formatText = replaceText( formatText, "FMT_", "" );

		for( int i=0; i<fmtInfoArraySize; ++i ){
			if( _strcmpi( formatText.c_str(), fmtInfoArray[i].strName)==0 ){
				format=fmtInfoArray[i].fmt;
				//TRACE1("texture format=%s\n", fmtInfoArray[i].strName );
				break;
			}
		}
		//見つからなかった
		if( format==D3DFMT_UNKNOWN ){
			assert( false && "format is not found! seted deflut format.");
			format = DefalutFmt;

		}
	}
	return format;
}

static D3DFORMAT getFormatRenderStencil( ID3DXEffect *effect, D3DXHANDLE hTex ){
	HRESULT hr;
	//・string Format
	//	テクスチャのフォーマットを指定する。
	//	ResourceNameが指定されているならば、画像ファイルからフォーマットが取得され、
	//	このアノテーションの設定は無視される。
	//	
	//	指定可能なフォーマットは、D3DFORMAT（http://msdn.microsoft.com/ja-jp/library/bb172558(v=VS.85).aspx）
	//	を参照。
	//　省略した場合、"D24S8"が使用される。

	static const D3DFORMAT DefalutFmt = D3DFMT_D24S8;

	D3DXHANDLE hFormat=0;
	D3DFORMAT format = DefalutFmt;
	hFormat=effect->GetAnnotationByName( hTex, "Format" );
	if(hFormat){
		const char* text = NULL;
		hr=effect->GetString( hFormat, &text );
		assert( SUCCEEDED(hr) );
		//見つからなかった場合がわかるように代入
		format = D3DFMT_UNKNOWN;

		std::string formatText = replaceText( text, "D3DFMT_", "" );
		formatText = replaceText( formatText, "FMT_", "" );

		for( int i=0; i<bufferFmtInfoArraySize; ++i ){
			if( _strcmpi( formatText.c_str(), bufferFmtInfoArray[i].strName)==0 ){
				format=bufferFmtInfoArray[i].fmt;
				//TRACE1("texture format=%s\n", bufferFmtInfoArray[i].strName );
				break;
			}
		}
		//見つからなかった
		if( format==D3DFMT_UNKNOWN ){
			assert( false && "format is not found! seted deflut format.");
			format = DefalutFmt;

		}
	}
	return format;
}

static int getMiplevel( ID3DXEffect *effect, D3DXHANDLE hTex, int defalutMipLevel ){
	HRESULT hr;
	D3DXHANDLE hMiplevels=0, hLevels=0;

	hMiplevels = effect->GetAnnotationByName( hTex, "Miplevels" );
	hLevels = effect->GetAnnotationByName( hTex, "Levels" );
	if(hLevels && hMiplevels){
		assert(false && "Miplevels, Levels is doubled! seted miplevels 0." );
	} else if( hLevels ){
		hr=effect->GetInt( hLevels, &defalutMipLevel );
		assert( SUCCEEDED(hr) );
	} else if( hMiplevels ){
		hr=effect->GetInt( hMiplevels, &defalutMipLevel );
		assert( SUCCEEDED(hr) );
	}
	return defalutMipLevel;
}

static void TextureReleaser(IDirect3DTexture9 *p){
	if(p != NULL) {
		(p)->Release();
		(p) = NULL;
	}
}

static void SurfaceReleaser(IDirect3DSurface9 *p){
	if(p != NULL) {
		(p)->Release();
		(p) = NULL;
	}
}

}//end namespace