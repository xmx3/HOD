#include"Vmd.h"
//#include<stdlib.h>
//#include <d3d9.h>
//#include<vector>
//#include<iostream>
#include<fstream>
//#include<iterator>
#include <algorithm>
#include <assert.h> 
#include"MMDMacro.h"
//#include <unistd.h>
#include <string.h>


namespace MMD {

static int motionComp( const void* pA, const void* pB)
{
	return (int)( reinterpret_cast<const CVmd::VMD_MOTION*>(pA)->flameNo - reinterpret_cast<const CVmd::VMD_MOTION*>(pB)->flameNo );
}

CVmd::CVmd(const char* data)
		:motionLength_(0),
		pMotions_(NULL),
		faceLength_(0),
		pFaces_(NULL),
		cameraLength_(0),
		pCameras_(NULL),
		lightLength_(0),
		pLights_(NULL)
{
	//各種データ読み込み
	memcpy( &vmdHeader_, data, sizeof(vmdHeader_) );
	data += sizeof(vmdHeader_);
	
	memcpy( &motionLength_, data, sizeof(motionLength_) );
	data += sizeof(motionLength_);
	
	pMotions_ = new VMD_MOTION[motionLength_];
	memcpy( pMotions_, data, sizeof(VMD_MOTION)*motionLength_ );
	data += sizeof(VMD_MOTION)*motionLength_;
	

	memcpy( &faceLength_, data, sizeof(faceLength_) );
	data += sizeof(faceLength_);

	pFaces_ = new VMD_FACE[faceLength_];
	memcpy( pFaces_, data, sizeof(VMD_FACE)*faceLength_ );
	data += sizeof(VMD_FACE)*faceLength_;

	memcpy( &cameraLength_, data,  sizeof(cameraLength_) );
	data += sizeof(cameraLength_);

	if(cameraLength_!=0){
		pCameras_ = new VMD_CAMERA[cameraLength_];
		memcpy( pCameras_, data, sizeof(VMD_CAMERA)*cameraLength_ );
		data += sizeof(VMD_CAMERA)*cameraLength_;
	}

	//変なところコピーしてる。
	//コピーした値使ったいないから致命傷になっていないけど
	//memcpy( &lightLength_, data, sizeof(lightLength_) );
	//data +=  sizeof(lightLength_);
	//if(lightLength_!=0){
	//	pLights_ = new VMD_LIGHT[lightLength_];
	//	memcpy( pLights_, data, sizeof(VMD_LIGHT)*lightLength_ );
	//	data += sizeof(VMD_LIGHT)*lightLength_;
	//}
	sortMotion();

	//デバッグ用
	//int time =-1;
	//for( unsigned int i=0 ; i<motionLength_ ; ++i){
	//	if( strcmp( pMotions_[i].BoneName,"センター" )==0 )
	//	{
	//		if((int)pMotions_[i].flameNo < time) assert(false);
	//		else time=pMotions_[i].flameNo;
	//	}
	//}
}

CVmd::CVmd(const char* data, unsigned long size )
		:motionLength_(0),
		pMotions_(NULL),
		faceLength_(0),
		pFaces_(NULL),
		cameraLength_(0),
		pCameras_(NULL),
		lightLength_(0),
		pLights_(NULL)
{
	const char* dataMax = data+size;
	//各種データ読み込み
	memcpy( &vmdHeader_, data, sizeof(vmdHeader_) );
	data += sizeof(vmdHeader_);
	
	memcpy( &motionLength_, data, sizeof(motionLength_) );
	data += sizeof(motionLength_);
	
	pMotions_ = new VMD_MOTION[motionLength_];
	memcpy( pMotions_, data, sizeof(VMD_MOTION)*motionLength_ );
	data += sizeof(VMD_MOTION)*motionLength_;
	

	memcpy( &faceLength_, data, sizeof(faceLength_) );
	data += sizeof(faceLength_);

	pFaces_ = new VMD_FACE[faceLength_];
	memcpy( pFaces_, data, sizeof(VMD_FACE)*faceLength_ );
	data += sizeof(VMD_FACE)*faceLength_;

	memcpy( &cameraLength_, data,  sizeof(cameraLength_) );
	data += sizeof(cameraLength_);

	if(cameraLength_!=0){
		pCameras_ = new VMD_CAMERA[cameraLength_];
		memcpy( pCameras_, data, sizeof(VMD_CAMERA)*cameraLength_ );
		data += sizeof(VMD_CAMERA)*cameraLength_;
	}
	assert( data<dataMax);
	
	memcpy( &lightLength_, data, sizeof(lightLength_) );
	data +=  sizeof(lightLength_);
	assert( data<=dataMax) ;

	if(lightLength_!=0){
		assert( data+(sizeof(VMD_LIGHT)*lightLength_)<dataMax );
		if( data+(sizeof(VMD_LIGHT)*lightLength_)<dataMax ){
			pLights_ = new VMD_LIGHT[lightLength_];
			const VMD_LIGHT* l=reinterpret_cast<const VMD_LIGHT*>(data);
			memcpy( pLights_, data, sizeof(VMD_LIGHT)*lightLength_ );
			data += sizeof(VMD_LIGHT)*lightLength_;
		}
	}
	sortMotion();

	//デバッグ用
	//int time =-1;
	//for( unsigned int i=0 ; i<motionLength_ ; ++i){
	//	if( strcmp( pMotions_[i].BoneName,"センター" )==0 )
	//	{
	//		if((int)pMotions_[i].flameNo < time) assert(false);
	//		else time=pMotions_[i].flameNo;
	//	}
	//}
}

CVmd::~CVmd()
{
	SAFE_DELETE_ARRAY( pMotions_ );
	SAFE_DELETE_ARRAY( pFaces_ );
	SAFE_DELETE_ARRAY( pCameras_ );
	SAFE_DELETE_ARRAY( pLights_ );
}

void CVmd::sortMotion()
{
	qsort(pMotions_,motionLength_,sizeof(VMD_MOTION),motionComp);
}

}// namespace MMD