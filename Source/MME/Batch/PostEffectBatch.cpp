#include "PostEffectBatch.h"
#include"MME/PostEffect.h"

namespace MME{ namespace Batch {

PostEffectBatch::PostEffectBatch( const PostEffectSharedPtr& effect)
	:BaseBatch(effect.get()),
	mEffect(effect)
{}

PostEffectBatch::~PostEffectBatch(){}

void PostEffectBatch::preDraw(){
	mEffect->setObjectsPtr( mObjects );
	mEffect->preDraw();
}

void PostEffectBatch::postDraw(){
	mEffect->setObjectsPtr( mObjects );
	mEffect->postDraw();
}


} } // namespace MME::Batch
