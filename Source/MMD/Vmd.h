#ifndef __VMD_H__
#define __VMD_H__

#include<Windows.h>

//最適化(パッティング)を防ぐ
#pragma pack( push, 1 )
namespace MMD{
class CVmd
{
public:
	//fileNameだったけど、データに変えた
	CVmd(const char* data);
	CVmd(const char* data, unsigned long size );
	~CVmd();
private:
	void sortMotion();
public:
	struct VMD_HEADER
	{
		char vmdHeader[30];
		char vmdModelName[20];
	};

	struct VMD_MOTION
	{
		char BoneName[15];
		DWORD flameNo;
		float Location[3];
		float Rotate[3];
		float w;
		char Interpolation1[16];
		char Interpolation2[16];
		char Interpolation3[16];
		char Interpolation4[16];
	};


	struct VMD_FACE
	{
		char FaceName[15];
		DWORD flameNo;
		float weight;
	};

	struct VMD_CAMERA
	{
		DWORD flameNo;
		float length;
		float position[3];
		float rotate[3];
		char interpolationX[4];
		char interpolationY[4];
		char interpolationZ[4];
		char interpolationQ[4];
		char interpolationL[4];
		char interpolationV[4];
		DWORD viewAngleDegree;
		BYTE parth;;
	};

	struct VMD_LIGHT
	{
		DWORD flameNo;
		DWORD RGB[3];
		DWORD Loc[3];
	};

	VMD_HEADER vmdHeader_;
	
	DWORD motionLength_;
	VMD_MOTION* pMotions_;

	DWORD faceLength_;
	VMD_FACE* pFaces_;

	DWORD cameraLength_;
	VMD_CAMERA* pCameras_;

	DWORD lightLength_;
	VMD_LIGHT* pLights_;
};
}// namespace MMD
#pragma pack( pop )

#endif