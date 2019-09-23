#ifndef __SEGATYPEHELPER_H__
#define __SEGATYPEHELPER_H__

#include <d3dx9.h>

#include "GameLib/Math/Vector3.h"
#include "GameLib/Math/Vector4.h"
#include "GameLib/Math/Matrix33.h"
#include "GameLib/Math/Matrix34.h"
#include "GameLib/Math/Matrix44.h"
#include <btBulletDynamicsCommon.h>

//Sege列ベクトル
//DirectXは行ベクトル

// sega→d3dx -----------------------------------------------------------
static inline D3DXMATRIX toDxMatrix(const GameLib::Math::Matrix44 &in)
{
	D3DXMATRIX o;
	o._11=in.m00;
	o._12=in.m10;
	o._13=in.m20;
	o._14=in.m30;

	o._21=in.m01;
	o._22=in.m11;
	o._23=in.m21;
	o._24=in.m31;

	o._31=in.m02;
	o._32=in.m12;
	o._33=in.m22;
	o._34=in.m32;

	o._41=in.m03;
	o._42=in.m13;
	o._43=in.m23;
	o._44=in.m33;

	return o;
}

static inline D3DXMATRIX toDxMatrix(const GameLib::Math::Matrix34 &in)
{
	D3DXMATRIX o;
	o._11=in.m00;
	o._12=in.m10;
	o._13=in.m20;
	o._14=0.f;

	o._21=in.m01;
	o._22=in.m11;
	o._23=in.m21;
	o._24=0.f;

	o._31=in.m02;
	o._32=in.m12;
	o._33=in.m22;
	o._34=0.f;

	o._41=in.m03;
	o._42=in.m13;
	o._43=in.m23;
	o._44=1.f;

	return o;
}

static inline D3DXVECTOR3 toDxVec3(const GameLib::Math::Vector3 &v) {
	return D3DXVECTOR3( v.x, v.y, v.z );
}

static inline D3DXVECTOR3 toDxVec3(const GameLib::Math::Vector4 &v) {
	return D3DXVECTOR3( v.x, v.y, v.z );
}

static inline D3DCOLORVALUE toDxColor( const GameLib::Math::Vector4 &c ){
	D3DCOLORVALUE result = { c.x, c.y, c.z, c.w };
	return result;
}

static inline D3DCOLORVALUE toDxColor( const GameLib::Math::Vector3 &c ){
	D3DCOLORVALUE result = { c.x, c.y, c.z, 1.f };
	return result;
}


// sega→d3dx End-----------------------------------------------------------


// directx→sega -------------------------------------------------
static inline GameLib::Math::Vector3 toVector3( const D3DXVECTOR3 &v ) {
	return GameLib::Math::Vector3(v.x, v.y, v.z);
}

static inline GameLib::Math::Vector3 toVector3( const D3DXVECTOR4 &v ) {
	return GameLib::Math::Vector3(v.x, v.y, v.z);
}

static inline GameLib::Math::Vector3 toVector3( const D3DXCOLOR &c ) {
	return GameLib::Math::Vector3(c.r, c.g, c.b);
}

static inline GameLib::Math::Vector4 toVector4( const D3DXVECTOR4 &v ) {
	return GameLib::Math::Vector4( v.x, v.y, v.z, v.w );
}

static inline GameLib::Math::Vector4 toVector4( const D3DXVECTOR3 &v, const float &w=1.0f ) {
	return GameLib::Math::Vector4( v.x, v.y, v.z, w );
}

static inline GameLib::Math::Matrix34 toMatrix34( const D3DXMATRIX &i ){
	GameLib::Math::Matrix34 out;
	out.m00 = i._11;	
	out.m01 = i._21;	
	out.m02 = i._31;	
	out.m03 = i._41;
	out.m10 = i._12;	
	out.m11 = i._22;	
	out.m12 = i._32;	
	out.m13 = i._42;
	out.m20 = i._13;	
	out.m21 = i._23;	
	out.m22 = i._33;	
	out.m23 = i._43;
	return out;
}

static inline GameLib::Math::Matrix44 toMatrix44( const D3DXMATRIX &i ){
	GameLib::Math::Matrix44 out;
	out.m00 = i._11;	
	out.m01 = i._21;	
	out.m02 = i._31;	
	out.m03 = i._41;
	out.m10 = i._12;	
	out.m11 = i._22;	
	out.m12 = i._32;	
	out.m13 = i._42;
	out.m20 = i._13;	
	out.m21 = i._23;	
	out.m22 = i._33;	
	out.m23 = i._43;
	out.m30 = i._14;	
	out.m31 = i._24;	
	out.m32 = i._34;	
	out.m33 = i._44;

	return out;
}

//directx→sega End-------------------------------------------------


// sega→bullet -----------------------------------------------------
static inline btVector3 toBtVector3( const GameLib::Math::Vector3 &vec3) {
	return btVector3( vec3.x, vec3.y, vec3.z );
}
//bullet→sega
static inline GameLib::Math::Matrix33 toMatrix33( const btMatrix3x3 &m33 ) {
	GameLib::Math::Matrix33 out;
	out.m00 = m33[0][0];
	out.m01 = m33[0][1];
	out.m02 = m33[0][2];

	out.m10 = m33[1][0];
	out.m11 = m33[1][1];
	out.m12 = m33[1][2];

	out.m20 = m33[2][0];
	out.m21 = m33[2][1];
	out.m22 = m33[2][2];

	return out;
}

static inline GameLib::Math::Matrix34 toMatrix34( const btTransform &t ) {
	GameLib::Math::Matrix34 out;
	btVector3 const &v3 = t.getOrigin();
	btMatrix3x3 const &m33 = t.getBasis();
	
	out.m00 = m33[0][0];
	out.m01 = m33[0][1];
	out.m02 = m33[0][2];
	out.m03 = v3.x();

	out.m10 = m33[1][0];
	out.m11 = m33[1][1];
	out.m12 = m33[1][2];
	out.m13 = v3.y();

	out.m20 = m33[2][0];
	out.m21 = m33[2][1];
	out.m22 = m33[2][2];
	out.m23 = v3.z();
	
	return out;
}

static inline GameLib::Math::Vector3 toVector3( const btVector3 &v ){
	return GameLib::Math::Vector3(v.x(), v.y(), v.z() );
}

#endif//__SEGATYPEHELPER_H__