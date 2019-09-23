#pragma once
#include<vector>
#include<memory>

namespace MME{ 
class OffScreenRender;
typedef std::shared_ptr<OffScreenRender> OffScreenRenderSharedPtr;
namespace Object{
	class IObject;
	typedef std::shared_ptr<IObject> IObjectSharedPtr;
}
namespace Batch {
class StandardEffectBatch;
class OffScreenBatch{
public:
	OffScreenBatch(const OffScreenRenderSharedPtr&);
	~OffScreenBatch();
	void add(const Object::IObjectSharedPtr &obj);
	void draw();
private:
	OffScreenRenderSharedPtr mOffScreen;
	std::vector<StandardEffectBatch*> mStandardBatchs;
};

} } //MME::Batch
