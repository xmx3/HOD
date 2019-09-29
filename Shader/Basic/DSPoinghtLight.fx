

//#include "mmm.fx"
#define TEXTURE_FORMAT "D3DFMT_A16B16G16R16F"
// #define TEXTURE_FORMAT "D3DFMT_A8R8G8B8"

float4x4 WorldViewProjMatrix	: WORLDVIEWPROJECTION;
float4x4 ViewProjMatrix				: VIEWPROJECTION;
float3   CameraPos						: POSITION  < string Object = "Camera"; >;

float4 _LightColor = { 1,0,0,1};
float4 _LightPosition = { 0, 55, 0, 1 };
#define LRANGE 16.0
float4 _LightRange = { LRANGE, 1.0/LRANGE, 0, 0  }; // [0]: range, [1]: 1.0/range
static const float4 _ShadowParams = { 1.0, 10, 0, 0 }; // [0]: 0=disabled, [1]: steps


// MMD本来のsamplerを上書きしないための記述です。削除不可。
sampler MMDSamp0 : register(s0);
// sampler MMDSamp1 : register(s1);
// sampler MMDSamp2 : register(s2);


float Script : STANDARDSGLOBAL <
string ScriptOutput = "color";
string ScriptClass = "sceneorobject";
string ScriptOrder = "postprocess";
> = 0.8;

shared texture2D PositionTex : RENDERCOLORTARGET<
float2 ViewPortRatio = {1.0,1.0};
int MipLevels = 1;
string Format = TEXTURE_FORMAT ;
string DefaultEffect = "self = hide;";
>;

sampler2D PositionSampler = sampler_state
{
	texture = < PositionTex >;
};

shared texture ColorTex: RENDERCOLORTARGET<
float2 ViewPortRatio = {1.0,1.0};
string Format = TEXTURE_FORMAT ;
int MipLevels = 1;
string DefaultEffect = "self = hide;";
>;

sampler ColorSampler = sampler_state
{
	texture = < ColorTex >;
};

shared texture NormalTex: RENDERCOLORTARGET<
float2 ViewPortRatio = {1.0,1.0};
int MipLevels = 1;
string Format = TEXTURE_FORMAT ;
string DefaultEffect = "self = hide;";
>;

sampler NormalSampler = sampler_state
{
	texture = < NormalTex >;
};

float4 ClearColor = 0.0;
float ClearDepth  = 1.0;

float2 ViewportSize : VIEWPORTPIXELSIZE;
static const float2 PixelSize = (float2(1,1)/(ViewportSize));



struct VS_Out
{
	float4 vertex : POSITION;
	float4 screen_pos : TEXCOORD0;
	float4 lightpos_mvp : TEXCOORD1;
};


VS_Out drawPointLightVS( MMM_SKINNING_INPUT IN ) {
	VS_Out o = (VS_Out)0;
	// float4 pos = MMM_SkinnedPosition( IN.Pos, IN.BlendWeight, IN.BlendIndices, IN.SdefC, IN.SdefR0, IN.SdefR1 );
	float4 pos = IN.Pos;

	// カメラ視点のワールドビュー射影変換
	o.vertex = mul( float4( pos.xyz * (_LightRange.x*2.0), 1.0), WorldViewProjMatrix );
	o.screen_pos = o.vertex;
	o.lightpos_mvp = mul( _LightPosition, ViewProjMatrix );
	return o;
}

float4 drawPointLightPS(VS_Out i) : COLOR0
{
	float2 coord = (i.screen_pos.xy / i.screen_pos.w + 1.0) * 0.5;
	coord.y = 1.0-coord.y;

	float4 FragPos4		= tex2D(PositionSampler, coord);
	if(FragPos4.w==0.0) { discard; }
	float4 AS		= tex2D(ColorSampler, coord);
	float4 NS		= tex2D(NormalSampler, coord);

	float3 FragPos		= FragPos4.xyz;
	float3 LightColor	= _LightColor.rgb;
	float3 LightPos		= _LightPosition.xyz;
	float3 LightDiff	= _LightPosition.xyz - FragPos.xyz;
	float LightDistSq	= dot(LightDiff, LightDiff);
	float LightDist		= sqrt(LightDistSq);
	float3  LightDir	= LightDiff / LightDist;
	float4 LightPositionMVP = i.lightpos_mvp;
	float LightAttenuation	= max(_LightRange.x-LightDist, 0.0)*_LightRange.y;
	if(LightAttenuation==0.0) { discard; }

	// if(_ShadowParams[0]!=0.0f) {
	// 	float2 lcoord = (LightPositionMVP.xy/LightPositionMVP.w + 1.0) * 0.5;
	// 	lcoord.y = 1.0-lcoord.y;
	//	
	// 	const int Div = (int)_ShadowParams[1];
	// 	float2 D2 = (coord - lcoord) / Div;
	// 	float3 D3 = (FragPos - _LightPosition.xyz) / Div;
	// 	float attr = 1.0 / (Div*0.5);
	// 	for(int i=1; i<Div; ++i) {
	// 		float4 RayPos = mul( float4(_LightPosition.xyz + (D3*i), 1.0), ViewProjMatrix );
	// 		float RayZ = RayPos.z;
	// 		float4 RayFrag = tex2D(PositionSampler, lcoord + (D2*i));
	// 		if(RayFrag.w!=0.0 && RayZ > RayFrag.w) {
	// 			LightAttenuation -= attr;
	// 		}
	// 	}
	// }
	if(LightAttenuation<=0.0) { discard; }

	float3 Albedo	= AS.rgb;
	float Shininess	= AS.a;
	float Fresnel	= NS.a;
	float3 Normal	= NS.xyz;
	float3 EyePos	= CameraPos.xyz;
	float3 EyeDir	= normalize(EyePos - FragPos);

	float3 h		= normalize(EyeDir + LightDir);
	float nh		= max(dot(Normal, h), 0.0);
	float Specular	= pow(nh, Shininess);
	float Intensity	= max(dot(Normal, LightDir), 0.0);

	float4 Result	= float4(0.0, 0.0, 0.0, LightAttenuation );
	Result.rgb += LightColor * (Albedo * Intensity) * LightAttenuation;
	Result.rgb += LightColor * Specular * LightAttenuation;

	return Result;
}

struct VS_Out1
{
	float4 vertex : POSITION;
	float4 screen_pos : TEXCOORD0;
};


VS_Out1 drawSquadVS( float4 pos : POSITION ) {
	VS_Out1 o = (VS_Out1)0;
	o.vertex=pos;
	o.screen_pos = pos;
	return o;
}

float4 drawPS( float4 screen_pos : TEXCOORD0 ) : COLOR0
{
	float2 tex = (screen_pos.xy / screen_pos.w + 1.0) * 0.5;
	tex.y = 1.0-tex.y;
	float4 normal = tex2D( NormalSampler, tex );
	return normal;
	// float4 color = tex2D( ColorSampler, tex );
	// float4 position = tex2D( PositionSamp, tex );
	// float4 em = tex2D( EmittionSamp, tex );
	// return  color + em;
	// return color;
}

// オブジェクト描画用テクニック
technique MainTec  <
string MMDPass = "object";
string Script = 
"ScriptExternal=Color;"
"Pass=PointLight;"
// "Pass=Debug;"
;>
{
	pass PointLight< string Script= "Draw=Geometry;"; > {
		ZEnable = TRUE;
		ZFunc = GREATER;
		ZWriteEnable = FALSE;
		AlphaBlendEnable = TRUE;
		DESTBLEND=ONE;
		SRCBLEND=ONE;
		CullMode = CW;
		VertexShader = compile vs_3_0 drawPointLightVS();
		PixelShader  = compile ps_3_0 drawPointLightPS();
	}
	pass Debug< string Script= "Draw=Buffer;"; > {
		ZEnable = FALSE;
		ZWriteEnable = FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_3_0 drawSquadVS();
		PixelShader  = compile ps_3_0 drawPS();
	}

	
}

// vim: ft=fx
