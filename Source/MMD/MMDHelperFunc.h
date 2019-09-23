#ifndef __MMDHELPERFUNC_H__
#define __MMDHELPERFUNC_H__
#include<math.h>
#include <d3dx9.h>
#include<assert.h>
#include<iostream>
#include<boost/lexical_cast.hpp>
#include<string>

const static float PI=static_cast<float>(3.14159265358979323846);

//たとえば－90度と270度とかどうするの?
//たぶん、バグある
//マトリックスを角度制限する。
static void MatrixRotationLimitYawPitchRoll(D3DXMATRIXA16* pMatOut , const D3DXMATRIXA16 &matIn ,
							  const float &maxYaw, const float &minYaw,
							  const float &maxPitch, const float &minPitch,
							  const float &maxRoll , const float &minRoll )
{
	float x=matIn._41;
	float y=matIn._42;
	float z=matIn._43;
	
	float pitch = asinf(-matIn._32);
	
	//ジンバルロック対策
	/*if(fabs(pitch) > PI/2*0.95f)
	{	
		pitch = (pitch<0)?-PI/2*0.95f:PI/2*0.95f;
	}*/
	float cosX=cosf(pitch);
	float yaw = asinf( matIn._31/cosX );
	float roll = asinf( matIn._12/cosX );

	
	if( yaw >= maxYaw ) yaw = maxYaw;
	if( roll >= maxRoll ) roll = maxRoll;
	if( pitch >= maxPitch) pitch = maxPitch;


	if( yaw < minYaw ) yaw = minYaw;
	if( roll < minRoll ) roll = minRoll;
	if( pitch < minPitch) pitch = minPitch;

	D3DXMatrixRotationYawPitchRoll(pMatOut,yaw,pitch,roll);
	pMatOut->_41=x;
	pMatOut->_42=y;
	pMatOut->_43=z;	
}

static void D3DXMatrixGetRollPitchYaw( float* roll, float* pitch, float* yaw, D3DXMATRIX const &matIn ) {

   // X軸回り
   float fSX = -matIn._32;    // sin(θx)
   float fX = (float)asin(fSX);   // X軸回り決定
   float fCX = (float)cos(fX);

   // Y軸回り
   float fSY = matIn._31 / fCX;
   float fCY = matIn._33 / fCX;
   float fY = (float)atan2(fSY, fCY);   // Y軸回り決定

   // Z軸回り
   float fSZ = matIn._12 / fCX;
   float fCZ = matIn._22 / fCX;
   float fZ = (float)atan2(fSZ, fCZ);

   *yaw = fY;		// ヨー
   *pitch = fX;		// ピッチ
   *roll = fZ;		// ロール
   return;
}


//http://blogs.msdn.com/b/mikepelton/archive/2004/10/29/249501.aspx
static void DecomposeRollPitchYawZXYMatrix( float *xPitch, float *yYaw, float *zRoll,const  D3DXMATRIX &mx) {

   *xPitch = asin(-mx._32);

   float threshold = 0.001f; // Hardcoded constant - burn him, he's a witch
   float test = cos(*xPitch);

   if(test > threshold) {
      *zRoll = atan2(mx._12, mx._22);
      *yYaw = atan2(mx._31, mx._33);
   } else {
      *zRoll = atan2(-mx._21, mx._11);
      *yYaw = 0.0;
   }
}
static float ConvertBetween0radAnd2PIrad(const float &rad ){
	if(rad<0){
		return rad+2*PI;
	} else {
		return rad;
	}
}

static void test(){
	float degree30=PI/6.f;
	float degree45=PI/4.f;
	float degree60=PI/3.f;
	float degree90=PI;
	float degree120=2*PI/3.f;
	D3DXMATRIX matR;
	float yaw,pitch, roll;

	std::cout << "start" << std::endl;

	yaw=pitch=roll=0;
	D3DXMatrixRotationYawPitchRoll(&matR, yaw, pitch, roll);
	//assert(yaw==pitch==roll==degree30);
	
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;
	
	D3DXMatrixGetRollPitchYaw( &roll, &pitch, &yaw ,matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;

	DecomposeRollPitchYawZXYMatrix( &pitch, &yaw, &roll, matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;
	
	std::cout << "start" << std::endl;

	yaw=pitch=roll=0;
	D3DXMatrixRotationYawPitchRoll(&matR, yaw, pitch, roll);
	//assert(yaw==pitch==roll==degree30);
	
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;
	
	D3DXMatrixGetRollPitchYaw( &roll, &pitch, &yaw ,matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;

	DecomposeRollPitchYawZXYMatrix( &pitch, &yaw, &roll, matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;

	std::cout << "start" << std::endl;

	yaw=pitch=roll=degree60;
	D3DXMatrixRotationYawPitchRoll(&matR, yaw, pitch, roll);
	//assert(yaw==pitch==roll==degree30);
	
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;
	
	D3DXMatrixGetRollPitchYaw( &roll, &pitch, &yaw ,matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;

	DecomposeRollPitchYawZXYMatrix( &pitch, &yaw, &roll, matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;

	std::cout << "start" << std::endl;

	yaw=pitch=roll=degree120;
	D3DXMatrixRotationYawPitchRoll(&matR, yaw, pitch, roll);
	//assert(yaw==pitch==roll==degree30);
	
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;
	
	D3DXMatrixGetRollPitchYaw( &roll, &pitch, &yaw ,matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;

	DecomposeRollPitchYawZXYMatrix( &pitch, &yaw, &roll, matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;

	std::cout << "start" << std::endl;

	yaw=pitch=roll=degree120*2.f;
	D3DXMatrixRotationYawPitchRoll(&matR, yaw, pitch, roll);
	//assert(yaw==pitch==roll==degree30);
	
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;
	
	D3DXMatrixGetRollPitchYaw( &roll, &pitch, &yaw ,matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;

	DecomposeRollPitchYawZXYMatrix( &pitch, &yaw, &roll, matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;
	
	std::cout << "start" << std::endl;

	yaw=pitch=roll=2*PI*3/4;
	D3DXMatrixRotationYawPitchRoll(&matR, yaw, pitch, roll);
	//assert(yaw==pitch==roll==degree30);
	
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;
	
	D3DXMatrixGetRollPitchYaw( &roll, &pitch, &yaw ,matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;

	DecomposeRollPitchYawZXYMatrix( &pitch, &yaw, &roll, matR );
	std::cout << "yaw=" << yaw << ", pitch=" << pitch << ", roll=" << roll << std::endl;

}
/*
static void DrawSphere( D3DXVECTOR3 const &pos,float const &r=0.f, float const &g=0.f, float const &b=0.f, float const &a=0.f ) {
	LPD3DXMESH pSphereMesh=NULL;
	D3DMATERIAL9* pSphereMeshMaterials=NULL;

	//スフィアメッシュのマテリアル　
	pSphereMeshMaterials = new D3DMATERIAL9;
	pSphereMeshMaterials->Diffuse.r=r;
	pSphereMeshMaterials->Diffuse.g=g;
	pSphereMeshMaterials->Diffuse.b=b;	
	pSphereMeshMaterials->Diffuse.a=a;
	pSphereMeshMaterials->Ambient=pSphereMeshMaterials->Diffuse;	
	pSphereMeshMaterials->Specular.r=1.0f;
	pSphereMeshMaterials->Specular.g=1.0f;
	pSphereMeshMaterials->Specular.b=1.0f;
	pSphereMeshMaterials->Emissive.r=0.1f;
	pSphereMeshMaterials->Emissive.g=0.1f;
	pSphereMeshMaterials->Emissive.b=0.1f;
	pSphereMeshMaterials->Power=120.0f;	

	//スフィアの作成
	D3DXCreateSphere(pDevice,1.f,12,12,&pSphereMesh,NULL);
		
	D3DXMATRIX matWorld;
	//ワールドトランスフォーム		
	D3DXMatrixTranslation(&matWorld, pos.x, pos.y, pos.z );
	//ワイヤーフレームだけ描画
	//pDevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_WIREFRAME );
	pDevice->SetMaterial(pSphereMeshMaterials);
	pDevice->SetTransform( D3DTS_WORLD, &matWorld );
	pSphereMesh->DrawSubset(0);
	//pDevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_SOLID );
	SAFE_RELEASE(pSphereMesh);
	SAFE_DELETE(pSphereMeshMaterials);
}
*/
//原点を中心にvec3Beforeをvec3AfterにするpMatOutを返す。
//vec3After = *pMatOut*vecBeforeとするpMatOutを返す。
static void MatrixTransformation(D3DXMATRIX *pMatOut,
	D3DXVECTOR3 const &vec3Before,
	D3DXVECTOR3 const &vec3After ) {
		if(vec3Before==vec3After) {
			D3DXMatrixIdentity( pMatOut );
			return;
		}
		D3DXVECTOR3 b,a;
		D3DXVec3Normalize(&b, &vec3Before);
		D3DXVec3Normalize(&a, &vec3After);
		float theata = acosf( D3DXVec3Dot(&b,&a) );
			
		D3DXVECTOR3 vec3Cross;
		D3DXVec3Cross( &vec3Cross, &vec3Before, &vec3After);
			
		D3DXMatrixRotationAxis( pMatOut, &vec3Cross, theata);
		return;

}

static void debugPrintQuaternion( const D3DXQUATERNION &q ) {
	D3DXMATRIX mat;
	D3DXMatrixRotationQuaternion( &mat, &q );
	float roll, yaw, pitch;
	D3DXMatrixGetRollPitchYaw( &roll, &pitch, &yaw, mat );
	float degreez = (roll/(2.f*3.14f))*360.f;
	float degreex = (pitch/(2.f*3.14f))*360.f;
	float degreey = (yaw/(2.f*3.14f))*360.f;
	using namespace boost;
	OutputDebugStringA("角度 x軸:");
	OutputDebugStringA( lexical_cast<std::string>(degreex).c_str() );
	OutputDebugStringA("\n角度 y軸:");
	OutputDebugStringA( lexical_cast<std::string>(degreey).c_str() );
	OutputDebugStringA("\n角度 z軸:");
	OutputDebugStringA( lexical_cast<std::string>(degreez).c_str() );
	OutputDebugStringA("\n");
}

/*
static void Error(const char* message) {
	MessageBox(NULL, message, "モデルの読み込みエラー", MB_OK);
	PostQuitMessage(0);
}*/
#endif //__MMDHELPERFUNC_H__
