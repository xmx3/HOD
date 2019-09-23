#pragma once
#include"BaseTechnique.h"
#include<d3dx9.h>
namespace MME {

class StandardTechnique : public BaseTechnique {
public:
	StandardTechnique( ID3DXEffect *effect, D3DXHANDLE hTech, BaseEffect *mme );
	virtual ~StandardTechnique();

	void exec();
private:
	std::vector<Script::IScript*> mScripts;


};
}