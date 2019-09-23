#ifndef __MYOUTPUTDEBUGSTRING_H__
#define __MYOUTPUTDEBUGSTRING_H__

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include <windows.h>
#include <stdio.h>

#if defined(_DEBUG) || defined(DEBUG)
// Debugのとき
#define TRACE(x)   MyOutputDebugString0(x)
#define TRACE0(x)   MyOutputDebugString0(x)
#define TRACE1(x, a)            MyOutputDebugString(x, a)
#define TRACE2(x, a, b)         MyOutputDebugString(x, a, b)
#define TRACE3(x, a, b, c)      MyOutputDebugString(x, a, b, c)
#define TRACE4(x, a, b, c, d)   MyOutputDebugString(x, a, b, c, d)
#else
// Releaseのとき
#define TRACE(x)
#define TRACE0(x)
#define TRACE1(x, a)
#define TRACE2(x, a, b)
#define TRACE3(x, a, b, c)
#define TRACE4(x, a, b, c, d)
#endif

static void MyOutputDebugString0( LPCSTR text ){
	OutputDebugStringA( text );
}
static void MyOutputDebugString0( LPCWSTR text ){
	OutputDebugStringW( text );
}

//printfっぽいデバッグ出力
static void MyOutputDebugString( LPCSTR pszFormat, ...)
{
    va_list	argp;
    char pszBuf[ 256];
    va_start(argp, pszFormat);
    vsprintf( pszBuf, pszFormat, argp);
    va_end(argp);
    OutputDebugStringA( pszBuf );
    //OutputDebugString( reinterpret_cast<LPCWSTR>(pszBuf) );
}

static void printToBitArray( unsigned short value ){
	char bitArray[sizeof(unsigned short)*8+1];
	for(int i=0; i<sizeof(unsigned short)*8; ++i){
		unsigned short mask =0x8000;
		if( value & mask >> i ){
			//1
			bitArray[i]='1';
		}
		else{
			//0
			bitArray[i]='0';
		}
	}
	bitArray[sizeof(unsigned short)*8] = '\0';
	OutputDebugStringA( bitArray );
}


#endif