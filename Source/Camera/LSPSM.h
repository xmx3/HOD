//-----------------------------------------------------------------------
// File : LSPSM.h
// Desc : Light Space Perspective Shadow Maps
// Date : May 30, 2010
// Author : Pocol
//-----------------------------------------------------------------------

#ifndef __LSPSM_H__
#define __LSPSM_H__

//
// Includes
//
#include <iostream>
#include <vector>
#include <d3dx9.h>


/////////////////////////////////////////////////////////////////////////
// PointList Class
/////////////////////////////////////////////////////////////////////////
class PointList
{
private:
	std::vector<D3DXVECTOR3> m_list;

public:
	PointList();
	int GetSize();
	void Add( const D3DXVECTOR3& value );
	void Clear();
	void Transform( const D3DXMATRIX &matrix );
	void ComputeBoundingBox( D3DXVECTOR3* min, D3DXVECTOR3* max );
	
	PointList& operator= ( const PointList& value );
	D3DXVECTOR3& operator[] ( int index );
};

/////////////////////////////////////////////////////////////////////////
// LSPSMCalculator Class
/////////////////////////////////////////////////////////////////////////
class LSPSMCalculator
{
public:
	LSPSMCalculator();
	void SetEyePos( const D3DXVECTOR3 &value );
	void SetViewDir( const D3DXVECTOR3 &value );
	void SetLightDir( const D3DXVECTOR3 &value );
	void SetEyeView( const D3DXMATRIX &value );
	void SetEyeProjection( const D3DXMATRIX &value );
	void SetNearClip( float value );
	void UpdateShadowMatrix();
	void SetUseLSPSM( bool value );

	const D3DXMATRIX& GetLightView()const;
	const D3DXMATRIX& GetLightProjection()const;
	const D3DXMATRIX& GetLightViewProjection()const;

private:
	D3DXVECTOR3 mEyePosition;
	D3DXVECTOR3 mViewDirection;
	D3DXVECTOR3 mLightDirection;

	D3DXMATRIX mEyeView;
	D3DXMATRIX mEyeProjection;
	D3DXMATRIX mLightView;
	D3DXMATRIX mLightProjection;
	D3DXMATRIX mLightViewProjection;

	PointList mPointList;
	float mNearClip;
	bool mUseLSPSM;
	float mExtendLengthFromFrustum;//ì ëÃÇê≥ämÇ…èoÇ∑ÇÃÇ™ÇﬂÇÒÇ«Ç≠Ç≥Ç¢ÇÃÇ≈

	void ComputeMatrix_USM();
	void ComputeMatrix_LSPSM();
	void ComputeLightVolumePoints( const D3DXMATRIX &viewProj );
	void ComputeViewFrustum( const D3DXMATRIX &viewProj );
	D3DXVECTOR3 ComputeUpVector( const D3DXVECTOR3 &viewDir, const D3DXVECTOR3 &lightDir );
	D3DXMATRIX GetUnitCubeClipMatrix( const D3DXVECTOR3 &min, const D3DXVECTOR3 &max );
	D3DXMATRIX GetPerspective( float nearDist, float farDist );
};

#endif // __LSPSM_H__