#pragma once
#include"BaseTechnique.h"
#include<d3dx9.h>
namespace MME {

class PostTechnique : public BaseTechnique {
public:
	PostTechnique( ID3DXEffect *effect, D3DXHANDLE hTech, BaseEffect *mme );
	virtual ~PostTechnique();

	void preExec();
	void postExec();
private:
	std::vector<Script::IScript*> mPreScripts;
	std::vector<Script::IScript*> mPostScripts;
};
}