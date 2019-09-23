#pragma once
#include"BaseEffect.h"
#include<vector>
#include<memory>

namespace MME{
	class PostTechnique;
	class PostEffect;
	typedef std::shared_ptr<PostEffect> PostEffectSharedPtr;
	
class PostEffect : public BaseEffect {
public:
	PostEffect( const std::string &fxFileName, GameLib::FileIO::InFile file, LPD3DXEFFECTPOOL pool );
	virtual ~PostEffect();

	void preDraw();
	void postDraw();

	//using BaseEffect::clearAllObjectsInOffScreen;

private:
	PostTechnique* findTequnique( MMDPass mmdPass, bool useTexture, bool useSphereMap, bool useToon, bool useSelfShadow );

	std::vector<PostTechnique*> mTechniques;
};

}