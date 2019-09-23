//------------------------------------------------------------------------
// File : LSPSM.cpp
// Desc : Light Space Perspective Shadow Maps
// Date : May 30, 2010
// Author : Pocol
//------------------------------------------------------------------------

//
// Includes
//
#include"LSPSM.h"
#include<assert.h>
#include"helper/MyOutputDebugString.h"
#include<GameLib/DebugScreen.h>

// Defines
//
#define NEW_FORMULA 0

namespace {
	float GetCrossingAngle( D3DXVECTOR3 v1, D3DXVECTOR3 v2 ){
		assert( D3DXVec3LengthSq(&v1)!=0.f );
		assert( D3DXVec3LengthSq(&v2)!=0.f );

		D3DXVec3Normalize( &v1, &v1 );
		D3DXVec3Normalize( &v2, &v2 );

		float dot = D3DXVec3Dot( &v1, &v2 );
		return acosf(dot);
		
	}
}


//------------------------------------------------------------------------
// Name : TransformCoord()
// Desc : 行列で3次元ベクトルを変換する
//------------------------------------------------------------------------
D3DXVECTOR3 TransformCoord(const D3DXVECTOR3 &point, const D3DXMATRIX &matrix)
{
	float x = matrix._11 * point.x + matrix._21 * point.y + matrix._31 * point.z + matrix._41;
	float y = matrix._12 * point.x + matrix._22 * point.y + matrix._32 * point.z + matrix._42;
	float z = matrix._13 * point.x + matrix._23 * point.y + matrix._33 * point.z + matrix._43;
	float w = matrix._14 * point.x + matrix._24 * point.y + matrix._34 * point.z + matrix._44;

	x /= w;
	y /= w;
	z /= w;
	return D3DXVECTOR3( x, y, z );
}

//////////////////////////////////////////////////////////////////////////
// PointList Class
//////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------
// Name : PointList()
// Desc : コンストラクタ
//------------------------------------------------------------------------
PointList::PointList()
{
	//リストをクリア
	m_list.clear();
}

//------------------------------------------------------------------------
// Name : GetSize()
// Desc : サイズを返す
//------------------------------------------------------------------------
int PointList::GetSize()
{
	return (int)m_list.size();
}

//------------------------------------------------------------------------
// Name : Add()
// Desc : 座標を追加する
//------------------------------------------------------------------------
void PointList::Add(const D3DXVECTOR3& value)
{
	m_list.push_back( value );
}

//------------------------------------------------------------------------
// Name : Clear()
// Desc : リストをクリアする
//------------------------------------------------------------------------
void PointList::Clear()
{
	m_list.clear();
}

//------------------------------------------------------------------------
// Name : Transform()
// Desc : 指定した行列でリストを変換する
//------------------------------------------------------------------------
void PointList::Transform(const D3DXMATRIX &matrix)
{
	int size = (int)m_list.size();
	for( int i=0; i<size; i++ )
	{
		D3DXVECTOR3 point = m_list[i];
		m_list[i] = TransformCoord( point, matrix );
	}
}

//------------------------------------------------------------------------
// Name : ComputeBoundingBox()
// Desc : AABBを算出する
//------------------------------------------------------------------------
void PointList::ComputeBoundingBox(D3DXVECTOR3* min, D3DXVECTOR3* max)
{
	int size = (int)m_list.size();
	if( size > 0 )
	{
		*min = *max = m_list[0];
		for( int i=1; i<size; i++ )
		{
			D3DXVec3Minimize( min, min, &m_list[i] );
			D3DXVec3Maximize( max, max, &m_list[i] );
		}
	}
}

//------------------------------------------------------------------------
// operator =
//------------------------------------------------------------------------
PointList& PointList::operator = (const PointList &value)
{
	m_list.clear();
	int size = (int)value.m_list.size();
	for( int i=0; i<size; i++ )
	{
		m_list.push_back( value.m_list[i] );
	}
	return (*this);
}

//------------------------------------------------------------------------
// operator []
//------------------------------------------------------------------------
D3DXVECTOR3& PointList::operator[](int index)
{
	return m_list[index];
}


//////////////////////////////////////////////////////////////////////////
// LSPSMCalculator Class
//////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------
// Name : LSPSMCalculator()
// Desc : コンストラクタ
//------------------------------------------------------------------------
LSPSMCalculator::LSPSMCalculator()
{
	mNearClip = 0.1f;
	mUseLSPSM = false;
	mExtendLengthFromFrustum=200.f;
	mPointList.Clear();
}

//------------------------------------------------------------------------
// Name : ComputeUpVector()
// Desc : 視点・ライトベクトルからアップベクトルを計算する
//-------------------------------------------------------------------------
D3DXVECTOR3 LSPSMCalculator::ComputeUpVector(const D3DXVECTOR3 &viewDirection, const D3DXVECTOR3 &lightDirection)
{
	D3DXVECTOR3 left;
	D3DXVECTOR3 up;

	D3DXVec3Cross( &left, &lightDirection, &viewDirection );
	D3DXVec3Cross( &up, &left, &lightDirection );
	D3DXVec3Normalize( &up, &up );
	return up;
}

//------------------------------------------------------------------------
// Name : ComputeMatrix_USM()
// Desc : 通常のシャドウマップ行列を計算する
//------------------------------------------------------------------------
void LSPSMCalculator::ComputeMatrix_USM()
{
	D3DXVECTOR3 max, min;

	//ライトのビュー行列を求める
	D3DXMatrixLookAtLH( &mLightView, &mEyePosition, &(mEyePosition + mLightDirection), &mViewDirection );

	//ライト空間へ変換
	mPointList.Transform( mLightView );

	//AABBを算出
	mPointList.ComputeBoundingBox( &min, &max );

	//範囲を適正にする
	mLightProjection = GetUnitCubeClipMatrix( min, max );
}

//------------------------------------------------------------------------
// Name : ComputeMatrix_LSPSM()
// Desc : ライト空間透視シャドウマップ行列を計算
//------------------------------------------------------------------------
void LSPSMCalculator::ComputeMatrix_LSPSM()
{
	//コピペしただけだけどかなり怪しい
	D3DXVECTOR3 max, min;

	//視線ベクトルとライトベクトルのなす角度を求める
	//float angle = GetCrossingAngle(mViewDirection, mLightDirection);
	//assert( D3DXVec3LengthSq(&mViewDirection)==1.f );
	//assert( D3DXVec3LengthSq(&mLightDirection)!=1.f );

	float angle = acosf(abs(D3DXVec3Dot( &mViewDirection, &mLightDirection )));

	//TRACE1( "angle = %f度\n", angle*180.f/D3DX_PI );

	//カメラと光の方向が平行に近い場合(11)
	//if ( angle <= D3DX_PI/8.f )
	//{
	//	//ライトによる歪みがないので通常のシャドウマップを適用
	//	ComputeMatrix_USM();
	//	return;
	//}

	//リストをコピーしておく
	PointList listClone = mPointList;

	float sinGamma = sinf(angle);
	assert(sinGamma!=0.f);
	// アップベクトルを算出
	D3DXVECTOR3 up = ComputeUpVector( mViewDirection, mLightDirection );
	//D3DXVECTOR3 up = mViewDirection;

	//ライトのビュー行列を求める
	D3DXMatrixLookAtLH( &mLightView, &mEyePosition, &(mEyePosition + mLightDirection), &up );

	//ライトのビュー行列でリストを変換し、AABBを算出
	mPointList.Transform( mLightView );
	mPointList.ComputeBoundingBox( &min, &max );

	//新しい視錐台を求める
	const float factor = 1.0f / sinGamma;
	const float z_n = factor * mNearClip;
	const float d = abs( max.y - min.y );
#if NEW_FORMULA 
	// New Formula written in ShaderX4
	const float z0 = - z_n;
	const float z1 = - ( z_n + d * sinGamma );
	assert( z0!=0.f );
	assert( 0.f <= z1/z0 );
	const float n = d / ( sqrtf( z1 / z0 ) - 1.0f );
#else
 	// Old Formula written in papers
	const float z_f = z_n + d * sinGamma;
	const float n = ( z_n + sqrtf( z_f * z_n ) ) * factor;
#endif
	const float f = n + d;
	D3DXVECTOR3 pos = mEyePosition - up * ( n - mNearClip );

	//シャドウマップ生成用ライトのビュー行列
	D3DXMatrixLookAtLH( &mLightView, &pos, &(pos + mLightDirection), &up );

	//Y方向への射影行列を取得
	D3DXMATRIX proj = GetPerspective( n, f );

	//透視変換後の空間へ変換する
	mLightProjection = mLightView * proj;
	listClone.Transform( mLightProjection );

	//AABBを算出
	listClone.ComputeBoundingBox( &min, &max );

	//GameLib::DebugScreen ds;
	//ds.setPosition( 20, 0);
	//ds.precision( 5 );
	//ds << "camera_light_angle: " << (angle*180.f/D3DX_PI)  << GameLib::endl;
	//ds << "up_mLightDirection_dot: " << D3DXVec3Dot( &mLightDirection, &up ) << GameLib::endl;
	//ds << "n: " << n <<GameLib::endl;
	//ds << "f: " << f << GameLib::endl; 
	//ds << "f-n: " << f-n << GameLib::endl;
	//ds << "min : " << min.x << ", " << min.y << ", " << min.z << GameLib::endl;
	//ds << "max : " << max.x << ", " << max.y << ", " << max.z << GameLib::endl;


	//範囲を適正にする
	D3DXMATRIX clip = GetUnitCubeClipMatrix( min, max );

	//シャドウマップ生成用ライトの射影行列を求める
	mLightProjection = proj * clip;
	//mLightProjection = clip * proj;
}

//------------------------------------------------------------------------
// Name : UpdateShadowMatrix()
// Desc : ライトの行列を更新する
//------------------------------------------------------------------------
void LSPSMCalculator::UpdateShadowMatrix()
{
	D3DXMATRIX viewProj;
	viewProj =  mEyeView * mEyeProjection;

	//ビューボリュームを求める
	ComputeLightVolumePoints( viewProj );

	if( mUseLSPSM ){
		// Light Space Perspective Shadow Map
		ComputeMatrix_LSPSM();
	} else{
		ComputeMatrix_USM();
	}

	//左手座標系に変換
	//D3DXMATRIX scale = CreateScale( 1.0f, 1.0f, -1.0f );
	//Multiply( mLightProjection, scale, mLightProjection );

	//シャドウマップに使う最終的な行列を求める
	mLightViewProjection = mLightView * mLightProjection;
}

//-----------------------------------------------------------------------
// Name : ComputeLightVolumePoints()
// Desc : 凸体を求める
//-----------------------------------------------------------------------
void LSPSMCalculator::ComputeLightVolumePoints(const D3DXMATRIX &viewProj)
{
	//カメラの視錐台を求める
	ComputeViewFrustum( viewProj );

	//カメラの視錐台に影を投げるオブジェクトがあるか判定する
	// Check 1: 視錐台と交差しているか？
	/*** 視錐台を形成する平面とAABBとの交差判定を行う ***/
	///面倒なので未実装///

	// Check 2: オブジェクトの各頂点からライトベクトル方向に
	// レイを飛ばし交差するか？
	/*** 各頂点からライトベクトル方向にレイを飛ばし、視錐台を形成する平面との交差判定を行う ***/
	///面倒なので未実装///
	
	//凸体を正確に出すのがめんどくさいので
	//面倒なので光方向に視錐台を伸ばす
	for( int i=0; i<8; ++i ){
		D3DXVECTOR3 p = mPointList[i];
		p += -mExtendLengthFromFrustum*mLightDirection;
		
		mPointList.Add(p);
	}
}

//-----------------------------------------------------------------------
// Name : ComputeViewFrustum()
// Desc : カメラの視錐台を求める
//アイデア
//視錐台の中にあるかを求めるならば各種平面方程式求めたほうがよくないか
//まあ大して変わらないけど
//-----------------------------------------------------------------------
void LSPSMCalculator::ComputeViewFrustum( const D3DXMATRIX &viewProj )
{
	mPointList.Clear();

	//　立方体を作成
	D3DXVECTOR3 v[8];
	v[0] = D3DXVECTOR3( -1.0f, +1.0f, -1.0f );
	v[1] = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
	v[2] = D3DXVECTOR3( +1.0f, -1.0f, -1.0f );
	v[3] = D3DXVECTOR3( +1.0f, +1.0f, -1.0f );
	v[4] = D3DXVECTOR3( -1.0f, +1.0f, +1.0f );
	v[5] = D3DXVECTOR3( -1.0f, -1.0f, +1.0f );
	v[6] = D3DXVECTOR3( +1.0f, -1.0f, +1.0f );
	v[7] = D3DXVECTOR3( +1.0f, +1.0f, +1.0f );
	for( int i=0; i<8; i++ )
	{
		mPointList.Add( v[i] );
	}

	//　ビュー行列→射影行列の逆変換を行う行列を求める
	D3DXMATRIX invViewProj;
	D3DXMatrixInverse( &invViewProj, NULL, &viewProj );

	//　立方体に逆変換する行列をかけ、視錐台を求める
	mPointList.Transform( invViewProj );
}

//-----------------------------------------------------------------------
// Name : GetUnitCubeClipMatrix()
// Desc : 範囲を適正にする行列を取得する
//-----------------------------------------------------------------------
D3DXMATRIX LSPSMCalculator::GetUnitCubeClipMatrix(const D3DXVECTOR3 &min, const D3DXVECTOR3 &max)
{
	D3DXMATRIX result;

	result._11 = 2.0f / ( max.x - min.x );
	result._21 = 0.0f;
	result._31 = 0.0f;
	result._41 = -( max.x + min.x ) / ( max.x - min.x );

	result._12 = 0.0f;
	result._22 = 2.0f / ( max.y - min.y );
	result._32 = 0.0f;
	result._42 = -( max.y + min.y ) / ( max.y - min.y );

	result._13 = 0.0f;
	result._23 = 0.0f;
	result._33 = 1.0f / ( max.z - min.z );
	result._43 = - min.z / ( max.z - min.z );

	result._14 = 0.0f;
	result._24 = 0.0f;
	result._34 = 0.0f;
	result._44 = 1.0f;

	return result;
}

//-----------------------------------------------------------------------
// Name : GetPerspective()
// Desc : Y方向への射影行列を取得する
//-----------------------------------------------------------------------
D3DXMATRIX LSPSMCalculator::GetPerspective( float nearDist, float farDist )
{
	D3DXMATRIX result;
	D3DXMatrixIdentity(&result);
	result._22 = farDist /( farDist - nearDist );
	result._24 = 1.0f;
	result._42 = -farDist * nearDist /( farDist - nearDist );
	result._44 = 0.0f;
	return result;
}

//-----------------------------------------------------------------------
// Name : SetEyePos()
// Desc : カメラの位置を設定
//-----------------------------------------------------------------------
void LSPSMCalculator::SetEyePos( const D3DXVECTOR3 &value )
{
	mEyePosition = value;
}

//-----------------------------------------------------------------------
// Name : SetViewDir()
// Desc : カメラの視線ベクトルを設定
//-----------------------------------------------------------------------
void LSPSMCalculator::SetViewDir( const D3DXVECTOR3 &value )
{
	assert( D3DXVec3LengthSq(&value)!=0.f );
	D3DXVec3Normalize( &mViewDirection, &value );
	//mViewDirection = value;
}

//-----------------------------------------------------------------------
// Name : SetLightDir()
// Desc : ライトベクトルを設定
//-----------------------------------------------------------------------
void LSPSMCalculator::SetLightDir( const D3DXVECTOR3 &value )
{
	
	assert( D3DXVec3LengthSq(&value)!=0.f );
	D3DXVec3Normalize( &mLightDirection, &value );
	//mLightDirection = value;
}

//-----------------------------------------------------------------------
// Name : SetEyeView()
// Desc : カメラのビュー行列を設定
//-----------------------------------------------------------------------
void LSPSMCalculator::SetEyeView( const D3DXMATRIX &value )
{
	mEyeView = value; 
}

//-----------------------------------------------------------------------
// Name : SetEyeProjection()
// Desc : カメラの射影行列を設定
//-----------------------------------------------------------------------
void LSPSMCalculator::SetEyeProjection( const D3DXMATRIX &value )
{
	mEyeProjection = value;
}

//-----------------------------------------------------------------------
// Name : SetNearClip()
// Desc : ニア平面までの距離を設定する
//-----------------------------------------------------------------------
void LSPSMCalculator::SetNearClip( float value )
{
	mNearClip = value;
}

//-----------------------------------------------------------------------
// Name : SetUseLSPSM()
// Desc : フラグの設定
//-----------------------------------------------------------------------
void LSPSMCalculator::SetUseLSPSM( bool value )
{
	mUseLSPSM = value;
}

//-----------------------------------------------------------------------
// Name : GetLightView()
// Desc : ライトのビュー行列を取得する
//-----------------------------------------------------------------------
const D3DXMATRIX& LSPSMCalculator::GetLightView()const
{
	return mLightView; 
}

//-----------------------------------------------------------------------
// Name : GetLightProjection()
// Desc : ライトの射影行列を取得する
//-----------------------------------------------------------------------
const D3DXMATRIX& LSPSMCalculator::GetLightProjection()const
{
	return mLightProjection;
}

//-----------------------------------------------------------------------
// Name : GetLightViewProjection()
// Desc : ライトのビュー射影行列を取得する
//-----------------------------------------------------------------------
const D3DXMATRIX& LSPSMCalculator::GetLightViewProjection()const
{
	return mLightViewProjection;
}

