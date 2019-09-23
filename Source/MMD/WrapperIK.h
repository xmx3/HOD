#ifndef __WRAPPER_IK_H__
#define __WRAPPER_IK_H__

#include <vector>
#include "MMDMacro.h"

namespace MMD {

class Bone;

class IIK_Impl
{
public:
	virtual ~IIK_Impl(){};
	virtual const char* load( const char *pData )=0; 
	virtual void solve(Bone *pBones)=0;

	virtual void setEnable(bool enabled)=0;
	virtual bool isEnable()=0;
	virtual unsigned short getIndex()=0;
	virtual unsigned short getTopIndex()=0;
};


class WrapperIK
{
public:
	WrapperIK():pImpl_(0){}
	virtual ~WrapperIK(){SAFE_DELETE(pImpl_);};
	const char* load( const char *pData );		
	//boneによって実装を変えたい場合使う。現在は両方とも実装方法同じ
	const char* load( const char *pData, const Bone *bones, const short &boneSize );	
	void solve( Bone *pBones);
	void setEnable(bool enabled);
	bool isEnable();
	//参照ボーンのindexを返す　例:右足IK等の名前にIKがついてるインデックスを返す
	unsigned short getIndex();
	unsigned short getTopIndex();

private:
	IIK_Impl *pImpl_;
};
}// namespace MMD

#endif //__WRAPPER_IK_H__