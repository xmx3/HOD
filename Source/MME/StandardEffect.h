#pragma once
#include"BaseEffect.h"
#include<memory>
#include<vector>

namespace MME{
	class StandardTechnique;
	class StandardEffect;
	typedef std::shared_ptr<StandardEffect> StandardEffectSharedPtr;

class StandardEffect : public BaseEffect {
public:
	StandardEffect( const std::string &fxFileName, GameLib::FileIO::InFile file, LPD3DXEFFECTPOOL pool );
	virtual ~StandardEffect();

	void drawZPlot();
	void drawObject();
	void drawObjectSS();
	void drawEdge();
	void drawZPrePass();

	//OffScreenRender findByName2‚ÅŽg—p
	typedef BaseEffect BaseType;
private:
	StandardTechnique* findTequnique( MMDPass mmdPass, bool useTexture, bool useSphereMap, bool useToon, bool useSelfShadow );
	void drawTech( MMDPass mmdPass, UseTexture useTexture, UseSphereMap useSphereMap, UseToon useToon, UseSelfShadow useSelfShadow  );
	
	std::vector<StandardTechnique*> mTechniques;
};
}