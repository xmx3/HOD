#pragma once
namespace MME {
	const char gMMMShader[] = 
"\
#define MIKUMIKUMOVING \n\
static const int MAX_MATRICES = 32;\
float4x4 WorldMatrixArray[MAX_MATRICES];\
\
struct MMM_SKINNING_INPUT{\
	float4 Pos                : POSITION;\
	float4 BlendWeight        : BLENDWEIGHT;\
	float4 BlendIndices        : BLENDINDICES;\
	float3 Normal            : NORMAL;\
	float2 Tex                : TEXCOORD0;\
	float4 AddUV1            : TEXCOORD1;\
	float4 AddUV2            : TEXCOORD2;\
	float4 AddUV3            : TEXCOORD3;\
	float4 AddUV4            : TEXCOORD4;\
	float4 SdefC            : TEXCOORD5;\
	float3 SdefR0            : TEXCOORD6;\
	float3 SdefR1            : TEXCOORD7;\
	float  EdgeWeight        : TEXCOORD8;\
	float  Index            : PSIZE15;\
};\
\
\
struct MMM_SKINNING_OUTPUT{\
	float4 Position;\
	float3 Normal;\
};\
\
MMM_SKINNING_OUTPUT MMM_SkinnedPositionNormal(\
	float4 pos,\
	float3 normal,\
	float4 blendWeights,\
	int4 blendIndices,\
	float4 sdefC,\
	float3 sdefR0,\
	float3 sdefR1\
){\
	\
	MMM_SKINNING_OUTPUT Out;\
	float4x4 world;\
\
	world = WorldMatrixArray[ blendIndices[0] ] * blendWeights[0];\
	for (int iBone = 1; iBone<2; ++iBone){\
		world += WorldMatrixArray[ blendIndices[iBone] ] * blendWeights[iBone];\
	}\
	Out.Position = mul( pos, world );\
	Out.Normal = mul( normal, (float3x3)world );\
	return Out;\
}\
\
\
float4 MMM_SkinnedPosition(\
	float4 pos,\
	float4 blendWeights,\
	int4 blendIndices,\
	float4 sdefC,\
	float3 sdefR0,\
	float3 sdefR1 )\
{\
	float4x4 world;\
\
	world = WorldMatrixArray[ blendIndices[0] ] * blendWeights[0];\
	for (int iBone = 1; iBone<2; ++iBone){\
		world += WorldMatrixArray[ blendIndices[iBone] ] * blendWeights[iBone];\
	}\
	return mul( pos, world );\
}\
";
}