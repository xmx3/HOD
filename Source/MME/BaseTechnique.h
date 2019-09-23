#pragma once
#include<d3dx9.h>
#include<vector>
#include"Enums.h"
#include<string>


class UseClass;

namespace MME{
	namespace Script{
		class IScript;
	}

	class DrawableMaterialNumberRange;
	class Pass;
	class BaseEffect;
class BaseTechnique{
public:
	BaseTechnique( ID3DXEffect *effect, D3DXHANDLE hTech, BaseEffect *mme );
	virtual ~BaseTechnique();
	
	bool canUse( MMDPass mmdPass, bool useTexture, bool useSphereMap, bool useToon, bool useSelfShadow )const;
	
	Pass* findPass( const std::string &name );
	bool isError() const{
		return mHandle==0;
	}

	bool canDraw( unsigned int materialIndex ) const;	
protected:
	D3DXHANDLE mHandle;
	ID3DXEffect *mEffect;
	DrawableMaterialNumberRange *mDrawableMaterials;
	MMDPass mMode;
	UseClass *mUseTexture;
	UseClass *mUseSelfShadow;
	UseClass *mUseSphereMap;
	UseClass *mUseToon;
	std::vector<Pass*> mPasses;
};

}//end namespace MME