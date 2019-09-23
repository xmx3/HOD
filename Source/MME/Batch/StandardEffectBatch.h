#pragma once

#include"BaseBatch.h"
#include<memory>

namespace MME{
class StandardEffect;
typedef std::shared_ptr<StandardEffect> StandardEffectSharedPtr;

namespace Batch {

class StandardEffectBatch : public BaseBatch {
public:
	typedef BaseBatch BaseType;

	StandardEffectBatch( const StandardEffectSharedPtr& );
	~StandardEffectBatch();
	void drawObject();
	void drawObjectSS();
	void drawZPlot();
	void drawZPrePass();
	void drawEdge();
private:
	StandardEffectSharedPtr mEffect;
};

} } //MME::Batch
