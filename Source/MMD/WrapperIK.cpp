#include"WrapperIK.h"
#include"Pmd.h"
#include"Bone.h"
#include<assert.h>
#include"IKImpl.h"

namespace MMD {

const char* WrapperIK::load( const char *pData ){
	const char* pNext;
	const PMD_IK *pIK = reinterpret_cast<const PMD_IK *>(pData);
	pImpl_=new IK_Impl();
	pNext=pImpl_->load(pData);
	
	return pNext;
}

const char* WrapperIK::load( const char *pData, const Bone *bones, const short &boneSize ){
	const char* pNext;
	const PMD_IK *pIK = reinterpret_cast<const PMD_IK *>(pData);
	const Bone *pBone = &(bones[pIK->index]); 
	if( strcmp( pBone->getName(), "‰E‘«‚h‚j" )==0  ||
		strcmp( pBone->getName(), "¶‘«‚h‚j" )==0 ) 
	{
		//pImpl_=new FootIK_Impl();
		//pNext=pImpl_->load(pData);
		//dynamic_cast<FootIK_Impl*>(pImpl_)->initLength(bones);
		pImpl_=new IK_Impl();
		pNext=pImpl_->load(pData);

	}else if( strcmp( pBone->getName(), "‰E‚Â‚Üæ‚h‚j" )==0  ||
		strcmp( pBone->getName(), "¶‚Â‚Üæ‚h‚j" )==0 ) 
	{
		pImpl_=new IK_Impl();
		//pImpl_=new AnkleIK_Impl();
		pNext=pImpl_->load(pData);
	} else{
		pImpl_=new IK_Impl();
		pNext=pImpl_->load(pData);
		pImpl_->setEnable(false);
	}
	
	return pNext;
}


void WrapperIK::solve(Bone *pBones) {
	pImpl_->solve(pBones);
}

bool WrapperIK::isEnable() {
	return pImpl_->isEnable();
}

void WrapperIK::setEnable( bool enabled) {
	pImpl_->setEnable(enabled);
}

unsigned short WrapperIK::getIndex() {
	return pImpl_->getIndex();
}

unsigned short WrapperIK::getTopIndex() {
	return pImpl_->getTopIndex();
}
}// namespace MMD