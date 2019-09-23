#pragma once

#include"BaseBatch.h"
#include<memory>

namespace MME{
class PostEffect;
typedef std::shared_ptr<PostEffect> PostEffectSharedPtr;

namespace Batch {

class PostEffectBatch : public BaseBatch {
public:
	PostEffectBatch( const PostEffectSharedPtr& );
	~PostEffectBatch();
	void preDraw();
	void postDraw();
private:
	PostEffectSharedPtr mEffect;
};

} } //MME::Batch
