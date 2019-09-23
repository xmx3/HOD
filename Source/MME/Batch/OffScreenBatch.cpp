#include"OffScreenBatch.h"
#include"StandardEffectBatch.h"
#include"MME/OffScreenRender.h"
#include"helper/ContainerHelper/findByName.h"


namespace MME{ namespace Batch {

OffScreenBatch::OffScreenBatch(const OffScreenRenderSharedPtr& off )
:mOffScreen(off)
{
	unsigned int n= mOffScreen->getNumberOfStandardEffects();
	mStandardBatchs.reserve(n);
	for( unsigned int i=0; i<n; ++i ){
		mStandardBatchs.push_back( new StandardEffectBatch( mOffScreen->getStandardEffectAt(i) ) );
	}
}

OffScreenBatch::~OffScreenBatch(){
	for( unsigned int i=0; i<mStandardBatchs.size(); ++i ){
		delete mStandardBatchs[i];
		mStandardBatchs[i]=0;
	}
	mStandardBatchs.clear();
}

void OffScreenBatch::add(const Object::IObjectSharedPtr &obj){
	std::string effectName;
	mOffScreen->findProperEffectName( &effectName, obj );
	if( !effectName.empty() ){
		using namespace ContainerHelper;
		StandardEffectBatch * batch = *(mStandardBatchs|findByName2( effectName.c_str() ));
		batch->add(obj);
	}
}

void OffScreenBatch::draw(){
	mOffScreen->begin();
	for(int i=0, size=mStandardBatchs.size(); i<size;){
		mStandardBatchs[i]->drawObjectSS();
	}
	mOffScreen->end();
}

} } //MME::Batch
