////////////////////////////////////////////////////////////////////////////////////////////////
//
//  basic.fx ver1.2
//  作成: 舞力介入P
//
////////////////////////////////////////////////////////////////////////////////////////////////
// パラメータ宣言

// 座法変換行列
float4x4 WorldViewProjMatrix      : WORLDVIEWPROJECTION;
float4x4 WorldMatrix              : WORLD;
float4x4 LightWorldViewProjMatrix : WORLDVIEWPROJECTION < string Object = "Light"; >;

float3   LightDirection    : DIRECTION < string Object = "Light"; >;
float3   CameraPosition    : POSITION  < string Object = "Camera"; >;

// マテリアル色
float4   MaterialDiffuse   : DIFFUSE  < string Object = "Geometry"; >;
float3   MaterialAmbient   : AMBIENT  < string Object = "Geometry"; >;
float3   MaterialEmmisive  : EMISSIVE < string Object = "Geometry"; >;
float3   MaterialSpecular  : SPECULAR < string Object = "Geometry"; >;
float    SpecularPower     : SPECULARPOWER < string Object = "Geometry"; >;
float3   MaterialToon      : TOONCOLOR;
// ライト色
float3   LightDiffuse      : DIFFUSE   < string Object = "Light"; >;
float3   LightAmbient      : AMBIENT   < string Object = "Light"; >;
float3   LightSpecular     : SPECULAR  < string Object = "Light"; >;
static float4 DiffuseColor  = MaterialDiffuse  * float4(LightDiffuse, 1.0f);
static float3 AmbientColor  = saturate(MaterialAmbient  * LightAmbient + MaterialEmmisive);
static float3 SpecularColor = MaterialSpecular * LightSpecular;

float4   EdgeColor         : EDGECOLOR;

static bool     parthf=true;   // パースペクティブフラグ
static bool     transp=false;   // 半透明フラグ
#define SKII1    1500
#define SKII2    8000
#define Toon     3

// オブジェクトのテクスチャ
texture ObjectTexture: MATERIALTEXTURE;
sampler ObjTexSampler = sampler_state
{
	texture = <ObjectTexture>;
	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
};

// MMD本来のsamplerを上書きしないための記述です。削除不可。
// sampler MMDSamp0 : register(s0);
// sampler MMDSamp1 : register(s1);
// sampler MMDSamp2 : register(s2);

// オブジェクト描画{{{

struct BufferShadow_OUTPUT {
	float4 Pos      : POSITION;     // 射影変換座標
	float4 ZCalcTex : TEXCOORD0;    // Z値
	float2 Tex      : TEXCOORD1;    // テクスチャ
	float3 Normal   : TEXCOORD2;    // 法線
	float3 Eye      : TEXCOORD3;    // カメラとの相対位置
	float2 SpTex    : TEXCOORD4;	 // スフィアマップテクスチャ座標
	float4 Color    : COLOR0;       // ディフューズ色
};


struct VS_OUTPUT
{
	float4 Vertex  : POSITION;    // 射影変換座標
	float4 ScreenPos  : TEXCOORD0;    // 射影変換座標
	float2 Tex        : TEXCOORD1;   // テクスチャ
	float3 Normal     : TEXCOORD2;   // 法線
	float4 WorldPos        : TEXCOORD3;
	float4 Color      : COLOR0;      // ディフューズ色
};

// 頂点シェーダ
VS_OUTPUT drawGBufferVS( MMM_SKINNING_INPUT IN, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	MMM_SKINNING_OUTPUT SkinOut = MMM_SkinnedPositionNormal( IN.Pos, IN.Normal, IN.BlendWeight, IN.BlendIndices, IN.SdefC, IN.SdefR0, IN.SdefR1 );

	Out.WorldPos = mul( SkinOut.Position, WorldMatrix );
	// カメラ視点のワールドビュー射影変換
	Out.Vertex = mul( SkinOut.Position, WorldViewProjMatrix );
	Out.ScreenPos = Out.Vertex;
	// 頂点法線
	Out.Normal = normalize( mul( SkinOut.Normal, (float3x3)WorldMatrix ) );

	// ディフューズ色＋アンビエント色 計算
	Out.Color.rgb = saturate( max(0,dot( Out.Normal, -LightDirection )) * DiffuseColor.rgb + AmbientColor );
	Out.Color.a = DiffuseColor.a;

	// テクスチャ座標
	Out.Tex = IN.Tex;

	return Out;
}
struct PS_INPUT{
	float4 ScreenPos  : TEXCOORD0;    // 射影変換座標
	float2 Tex        : TEXCOORD1;   // テクスチャ
	float3 Normal     : TEXCOORD2;   // 法線
	float3 WorldPos        : TEXCOORD3;
	float4 Color      : COLOR0;      // ディフューズ色
};

struct PS_OUTPUT
{
	float4 Color				: COLOR0;
	float4 Pos			: COLOR1;
	float4 Normal				: COLOR2;
};
// ピクセルシェーダ
PS_OUTPUT drawGBufferPS( PS_INPUT IN , uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon)
{
	PS_OUTPUT Out = (PS_OUTPUT)0;

	Out.Color = IN.Color;
	if ( useTexture ) {  //※このif文は非効率的
		// テクスチャ適用
		Out.Color *= tex2D( ObjTexSampler, IN.Tex );
	}
	Out.Normal = float4( IN.Normal, 1 );
	Out.Pos = float4( IN.WorldPos, IN.ScreenPos.z);
	// Out.Pos = float4( IN.WorldPos, IN.ScreenPos.z/IN.ScreenPos.w);

	return Out;
}

// // ピクセルシェーダ
float4 drawPS( VS_OUTPUT IN, uniform bool useTexture ) : COLOR0
{

	float4 Color = IN.Color;
	if ( useTexture ) {  //※このif文は非効率的
		// テクスチャ適用
		Color *= tex2D( ObjTexSampler, IN.Tex );
	}

	return Color;
}

// オブジェクト描画用テクニック（アクセサリ用）影ありも影なしもオッケ（独自拡張）{{{
// 不要なものは削除可
technique MainTec0 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = false; bool UseToon = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferVS(false, false, false);
		PixelShader  = compile ps_3_0 drawGBufferPS(false, false, false);
	}
}

technique MainTec1 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = false; bool UseToon = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferVS(true, false, false);
		PixelShader  = compile ps_3_0 drawGBufferPS(true, false, false);
	}
}

technique MainTec2 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = true; bool UseToon = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferVS(false, true, false);
		PixelShader  = compile ps_3_0 drawGBufferPS(false, true, false);
	}
}

technique MainTec3 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = true; bool UseToon = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;

		VertexShader = compile vs_3_0 drawGBufferVS(true, true, false);
		PixelShader  = compile ps_3_0 drawGBufferPS(true, true, false);
	}
}

// オブジェクト描画用テクニック（PMDモデル用）
technique MainTec4 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = false; bool UseToon = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;

		VertexShader = compile vs_3_0 drawGBufferVS(false, false, true);
		PixelShader  = compile ps_3_0 drawGBufferPS(false, false, true);
	}
}

technique MainTec5 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = false; bool UseToon = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;

		VertexShader = compile vs_3_0 drawGBufferVS(true, false, true);
		PixelShader  = compile ps_3_0 drawGBufferPS(true, false, true);
	}
}

technique MainTec6 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = true; bool UseToon = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferVS(false, true, true);
		PixelShader  = compile ps_3_0 drawGBufferPS(false, true, true);
	}
}

technique MainTec7 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = true; bool UseToon = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferVS(true, true, true);
		PixelShader  = compile ps_3_0 drawGBufferPS(true, true, true);
	}
}
//}}}


//}}}

// 輪郭描画{{{
// 頂点シェーダ
float4 ColorRender_VS(MMM_SKINNING_INPUT IN) : POSITION 
{
	MMM_SKINNING_OUTPUT SkinOut = MMM_SkinnedPositionNormal( IN.Pos, IN.Normal, IN.BlendWeight, IN.BlendIndices, IN.SdefC, IN.SdefR0, IN.SdefR1 );
	float4 Pos = mul( SkinOut.Position, WorldViewProjMatrix );


	// 法線方向にちょっとだけ膨らます
	float3 Normal = mul( SkinOut.Normal, (float3x3)WorldMatrix );
	float2 dir = normalize(Normal.xy);
	Pos.xy += dir/Pos.w;
	return Pos;
}

// ピクセルシェーダ
float4 ColorRender_PS() : COLOR
{
	// 輪郭色で塗りつぶし
	return EdgeColor;
}

// 輪郭描画用テクニック
technique EdgeTec < string MMDPass = "edge"; > {
	pass DrawEdge {
#ifdef ZPREPASS_ENABLE
		ZWriteEnable=FALSE;
		// ZFunc=Equal;
#endif
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		CULLMODE = CW;
		VertexShader = compile vs_2_0 ColorRender_VS();
		PixelShader  = compile ps_2_0 ColorRender_PS();
	}
}
//}}}

// セルフシャドウ用Z値プロット{{{

struct VS_ZValuePlot_OUTPUT {
	float4 Pos : POSITION;              // 射影変換座標
	float4 ShadowMapTex : TEXCOORD0;    // Zバッファテクスチャ
};

// 頂点シェーダ
VS_ZValuePlot_OUTPUT ZValuePlot_VS( MMM_SKINNING_INPUT IN )
{
	VS_ZValuePlot_OUTPUT Out = (VS_ZValuePlot_OUTPUT)0;

	float4 Pos =  MMM_SkinnedPosition(IN.Pos, IN.BlendWeight, IN.BlendIndices, IN.SdefC, IN.SdefR0, IN.SdefR1);
	// ライトの目線によるワールドビュー射影変換をする
	Out.Pos = mul( Pos, LightWorldViewProjMatrix );

	// テクスチャ座標を頂点に合わせる
	Out.ShadowMapTex = Out.Pos;

	return Out;
}

// ピクセルシェーダ
//分散シャドウマップ用
float4 VSM_ZValuePlot_PS( float4 ShadowMapTex : TEXCOORD0 ) : COLOR
{
	float depth = ShadowMapTex.z/ShadowMapTex.w;
	return float4( depth, depth*depth, 0.f, 0.f );
}

float4 ZValuePlot_PS( float4 ShadowMapTex : TEXCOORD0 ) : COLOR
{
	float depth = ShadowMapTex.z/ShadowMapTex.w;
	
	return float4( depth, 0.f, 0.f, 0.f );
}


// Z値プロット用テクニック
technique ZplotTec < 
string MMDPass = "zplot";
string Script = 
"Pass=ZValuePlot;";
> {
#ifdef ENABLE_VSM
	//分散シャドウマップの場合
	pass ZValuePlot {
		AlphaTestEnable  = FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_2_0 ZValuePlot_VS();
		PixelShader  = compile ps_2_0 VSM_ZValuePlot_PS();
	}
#else
	pass ZValuePlot {
		AlphaTestEnable  = FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_2_0 ZValuePlot_VS();
		PixelShader  = compile ps_2_0 ZValuePlot_PS();
	}
#endif


}

//}}}
// vim : ft=fx
