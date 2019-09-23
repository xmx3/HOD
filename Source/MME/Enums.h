#pragma once
namespace MME {
	enum MMDPass{
		MP_OBJECT=0,   
		MP_ZPLOT,
		MP_OBJECT_SS,
		MP_SHADOW,   
		MP_EDGE,
		MP_ZPREPASS,
		MP_NUM,
	};

	enum ScriptClass{
		SC_OBJECT=0,
		SC_SCENE,
		SC_SCENEOROBJECT,
	};

	enum UseTexture{
		DISABLE_TEXTURE=0,
		ENABLE_TEXTURE=1,
	};

	enum UseToon{
		DISABLE_TOON=0,
		ENABLE_TOON=1,
	};

	enum UseSphereMap{
		DISABLE_SPHEREMAP=0,
		ENABLE_SPHEREMAP=1,
	};

	enum UseSelfShadow{
		DISABLE_SELFSHADOW=0,
		ENABLE_SELFSHADOW=1,
	};

}