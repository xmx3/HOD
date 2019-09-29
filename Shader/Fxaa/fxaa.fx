//http://www.geeks3d.com/20110405/fxaa-fast-approximate-anti-aliasing-demo-glsl-opengl-test-radeon-geforce/

float Script : STANDARDSGLOBAL <
    string ScriptOutput = "color";
    string ScriptClass = "sceneorobject";
    string ScriptOrder = "postprocess";
> = 0.8;


// スクリーンサイズ
float2 ViewportSize : VIEWPORTPIXELSIZE;
static float2 rcpFrame = (float2(1.0,1.0)/ViewportSize); // Constant {1.0/frameWidth, 1.0/frameHeight}.
static float2 ViewportOffset = (float2(0.5,0.5)/ViewportSize);

struct VS_Out
{
	float4 vertex : POSITION;
	float2 texcoord : TEXCOORD0;
};

VS_Out drawSquadVS( float4 pos : POSITION, float2 texcoord : TEXCOORD0 ) {
	VS_Out o = (VS_Out)0;
	o.vertex=pos;
	o.texcoord = texcoord + ViewportOffset;
	return o;
}

#define FXAA_SUBPIX_SHIFT 1.0/4.0;

// #define TEXTURE_FORMAT "D3DFMT_A16B16G16R16F"
#define TEXTURE_FORMAT "D3DFMT_A8R8G8B8"


texture2D RenderTarget : RENDERCOLORTARGET<
	float2 ViewPortRatio = {1.0,1.0};
	int MipLevels = 1;
	string Format = TEXTURE_FORMAT ;
	string DefaultEffect = "self = hide;";
>;


sampler2D tex0 = sampler_state
{
	texture = < RenderTarget >;
	// MipFilter = NONE;
	// MinFilter = LINEAR;
	// MagFilter = LINEAR;
	// AddressU = CLAMP;
	// AddressV = CLAMP;
	// sRGBTexture = FALSE;
};

static const float FXAA_SPAN_MAX = 8.0;
static const float FXAA_REDUCE_MUL = 1.0/8.0;

#define FxaaInt2 float2
#define FxaaFloat2 float2
#define FxaaFloat2 float2
#define FxaaTex sampler2D

float4 FxaaTexLod0(FxaaTex tex, float2 pos)
{
	return tex2Dlod(tex, float4(pos.xy, 0.0, 0.0)); 
}

float4 FxaaTexOff(FxaaTex tex, float2 pos, FxaaInt2 off, float2 rcpFrame)
{
	return tex2Dlod(tex, float4(pos.xy + (off * rcpFrame), 0, 0)); 
}

float3 FxaaPixelShader(
	FxaaTex tex,
	float2 posPos, // Output of FxaaVertexShader interpolated across screen.
	float2 rcpFrame) // Constant {1.0/frameWidth, 1.0/frameHeight}.
{   
	/*---------------------------------------------------------*/
	#define FXAA_REDUCE_MIN   (1.0/128.0)
	//#define FXAA_REDUCE_MUL   (1.0/8.0)
	//#define FXAA_SPAN_MAX     8.0
	/*---------------------------------------------------------*/
	float3 rgbNW = FxaaTexOff(tex, posPos.xy, FxaaInt2(-1,-1), rcpFrame).xyz;
	float3 rgbNE = FxaaTexOff(tex, posPos.xy, FxaaInt2( 1,-1), rcpFrame).xyz;
	float3 rgbSW = FxaaTexOff(tex, posPos.xy, FxaaInt2(-1, 1), rcpFrame).xyz;
	float3 rgbSE = FxaaTexOff(tex, posPos.xy, FxaaInt2( 1, 1), rcpFrame).xyz;

	float3 rgbM = FxaaTexOff(tex, posPos.xy, FxaaInt2( 0, 0), rcpFrame).xyz;
	/*---------------------------------------------------------*/
	
	float3 luma=float3(0.299, 0.587, 0.114);
	
	float lumaNW = dot(rgbNW, luma);
	float lumaNE = dot(rgbNE, luma);
	float lumaSW = dot(rgbSW, luma);
	float lumaSE = dot(rgbSE, luma);
	float lumaM  = dot(rgbM,  luma);
	/*---------------------------------------------------------*/
	float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
	float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));
	/*---------------------------------------------------------*/
	float2 dir; 
	dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
	dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
	/*---------------------------------------------------------*/
	float dirReduce = max(
			(lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * FXAA_REDUCE_MUL),
			FXAA_REDUCE_MIN);
	float rcpDirMin = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);
	dir = min(FxaaFloat2( FXAA_SPAN_MAX,  FXAA_SPAN_MAX), 
			max(FxaaFloat2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX), 
				dir * rcpDirMin)) * rcpFrame.xy;
	/*--------------------------------------------------------*/
	float3 rgbA = (1.0/2.0) * (
			FxaaTexLod0(tex, posPos.xy + dir * (1.0/3.0 - 0.5)).xyz +
			FxaaTexLod0(tex, posPos.xy + dir * (2.0/3.0 - 0.5)).xyz);
	float3 rgbB = rgbA * (1.0/2.0) + (1.0/4.0) * (
			FxaaTexLod0(tex, posPos.xy + dir * (0.0/3.0 - 0.5)).xyz +
			FxaaTexLod0(tex, posPos.xy + dir * (3.0/3.0 - 0.5)).xyz);
	float lumaB = dot(rgbB, luma);
	if((lumaB < lumaMin) || (lumaB > lumaMax)) return rgbA;
	return rgbB;
}

float4 drawPS( float2 texcoord : TEXCOORD0 ) : COLOR0 {
	float4 c;	
	c.rgb = FxaaPixelShader( tex0, texcoord, rcpFrame );
	c.a = 1.0;
	return c;
}

float4 ClearColor = {0,0,0,0};
float ClearDepth  = 1.0;


technique MainTec  <
string MMDPass = "object";
string Script = 
	//バッファクリア
	"ClearSetColor=ClearColor;"
	"ClearSetDepth=ClearDepth;"
	// "Clear=Color;"
	// "Clear=Depth;"
	"RenderColorTarget0=RenderTarget;"
	"Clear=Color;"
	
	"ScriptExternal=Color;"
	
	"RenderColorTarget0=;"
	// "RenderDepthStencilTarget=;"
	"Pass=FXAAPass;"
	"Clear=Depth;"
	;
> {

	pass FXAAPass< string Script= "Draw=Buffer;"; > {
		ZEnable = FALSE;
		ZWriteEnable = FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_3_0 drawSquadVS();
		PixelShader  = compile ps_3_0 drawPS();
	}
}
