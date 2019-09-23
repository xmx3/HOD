#include "StandardEffectBatch.h"
#include "MME/StandardEffect.h"

namespace MME{ namespace Batch {

StandardEffectBatch::StandardEffectBatch( const StandardEffectSharedPtr& effect)
	:BaseBatch(effect.get()),
	mEffect(effect)
{}


StandardEffectBatch::~StandardEffectBatch(){}

void StandardEffectBatch::drawObject(){
	mEffect->setObjectsPtr( mObjects );
	mEffect->drawObject();
}

void StandardEffectBatch::drawObjectSS(){
	mEffect->setObjectsPtr( mObjects );
	mEffect->drawObjectSS();
}

void StandardEffectBatch::drawZPlot(){
	mEffect->setObjectsPtr( mObjects );
	mEffect->drawZPlot();
}

void StandardEffectBatch::drawZPrePass(){
	mEffect->setObjectsPtr( mObjects );
	mEffect->drawZPrePass();
}

void StandardEffectBatch::drawEdge(){
	mEffect->setObjectsPtr( mObjects );
	mEffect->drawEdge();
}


} } // namespace MME::Batch
