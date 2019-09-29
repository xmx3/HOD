
#define TEXTURE_FORMAT "D3DFMT_A16B16G16R16F"
// #define TEXTURE_FORMAT "D3DFMT_A8R8G8B8"

float3 gCameraPosition : POSITION  < string Object = "Camera"; >;
float4x4 ViewProjMatrix      : VIEWPROJECTION;

#define NUM_LIGHT 12
static float3 gLightPosition[NUM_LIGHT] = { 
	{10, 5, 0},
	{0, 25, 0},
	{-10, 5,0},
	{-10, 5,0},
	{-10, 5,0},
	{-10, 5,0},
	{-10, 5,0},
	{-10, 5,0},
	{-10, 5,0},
	{-10, 5,0},
	{-10, 5,0},
	{-10, 5,0},
};

static float3 gLightColor[NUM_LIGHT] = { 
	{ 1, 0, 0},
	{ 0, 1, 0},
	{ 0, 0, 1},
	{ 0, 0, 1},
	{ 0, 0, 1},
	{ 0, 0, 1},
	{ 0, 0, 1},
	{ 0, 0, 1},
	{ 0, 0, 1},
	{ 0, 0, 1},
	{ 0, 0, 1},
	{ 0, 0, 1},
};
//閾値
static const float depthThreshold = 0.005;

// MMD本来のsamplerを上書きしないための記述です。削除不可。
// sampler MMDSamp0 : register(s0);
// sampler MMDSamp1 : register(s1);
// sampler MMDSamp2 : register(s2);


float Script : STANDARDSGLOBAL <
    string ScriptOutput = "color";
    string ScriptClass = "sceneorobject";
    string ScriptOrder = "postprocess";
> = 0.8;

shared texture2D PositionTex:RENDERCOLORTARGET<
    float2 ViewPortRatio = {1.0,1.0};
    int MipLevels = 1;
    string Format = TEXTURE_FORMAT ;
    string DefaultEffect = "self = hide;";
>;

sampler2D PositionTexSampler = sampler_state
{
	texture = < PositionTex >;
};

shared texture ColorTex: RENDERCOLORTARGET<
    float2 ViewPortRatio = {1.0,1.0};
    string Format = TEXTURE_FORMAT ;
    int MipLevels = 1;
    string DefaultEffect = "self = hide;";
    
>;

sampler ColorTexSampler = sampler_state
{
	texture = < ColorTex >;
};


shared texture NormalTex: RENDERCOLORTARGET<
    float2 ViewPortRatio = {1.0,1.0};
    int MipLevels = 1;
    string Format = TEXTURE_FORMAT ;
    string DefaultEffect = "self = hide;";
    
>;

sampler NormalTexSampler = sampler_state
{
	texture = < NormalTex >;
};

// texture DepthTex: RENDERCOLORTARGET<
//     float2 ViewPortRatio = {1.0,1.0};
//     int MipLevels = 1;
//     string Format = "D3DFMT_R32F" ;
//     string DefaultEffect = "self = hide;";
//    
// >;
//
// sampler DepthTexSampler = sampler_state
// {
// 	texture = < DepthTex >;
// };
//
//
// texture DepthBuffer : RenderDepthStencilTarget <
//     float2 ViewPortRatio = {1.0,1.0};
//     string Format = "D24S8";
// >;

float4 ClearColor = 0.1;
float ClearDepth  = 1.0;

float2 ViewportSize : VIEWPORTPIXELSIZE;
static const float2 PixelSize = (float2(1,1)/(ViewportSize));



struct VS_Out
{
	float4 vertex : POSITION;
	float4 screen_pos : TEXCOORD0;
	float4 lightpos_mvp : TEXCOORD1;
};


VS_Out drawSquadVS( float4 pos : POSITION ) {
	VS_Out o = (VS_Out)0;
	o.vertex=pos;
	o.screen_pos = pos;
	return o;
}

float4 drawPS( float4 screen_pos : TEXCOORD0 ) : COLOR0
{
	float2 tex = (screen_pos.xy / screen_pos.w + 1.0) * 0.5;
	tex.y = 1.0-tex.y;
	// float4 normal = tex2D( NormalTexSampler, tex );
	float4 color = tex2D( ColorTexSampler, tex );
	// float4 position = tex2D( PositionTexSampler, tex );
	return color;
}


float4 drawLightPS(  float4 screen_pos: TEXCOORD0, float4 lightpos_mvp : TEXCOORD1 ) : COLOR0
{
	float2 tex = (screen_pos.xy / screen_pos.w + 1.0) * 0.5;
	tex.y = 1.0-tex.y;

	float4 positionAndDepth = tex2D( PositionTexSampler, tex );
	
	float3 position = positionAndDepth.xyz;
	
	float4 normal = tex2D( NormalTexSampler, tex );
	float4 diffuse = tex2D( ColorTexSampler, tex );
	float3 eyeDir   = normalize( gCameraPosition - position );
	
	float4 color = diffuse*0.5;
	
	for( int i=0; i<NUM_LIGHT; ++i )
	{
		float3 LightDir = gLightPosition[ i ].xyz - position;
		float3 L = normalize( LightDir );
		float  attenution = 1.0f / length( LightDir )*20;
		color.rgb +=  gLightColor[ i ] * diffuse.rgb * max( dot( L, normal ), 0 )*attenution;
	}
	//
	color.a   = 1.0f;
	return color;  
}


// オブジェクト描画用テクニック
technique MainTec  <
string MMDPass = "object";
string Script = 
	"ClearSetColor=ClearColor;"
	"ClearSetDepth=ClearDepth;"
	"Clear=Color;"
	"Clear=Depth;"
	"RenderColorTarget=NormalTex;"
	"Clear=Color;"
	"RenderColorTarget=PositionTex;"
	"Clear=Color;"
	"RenderColorTarget=ColorTex;"
	"Clear=Color;"
	// "RenderDepthStencilTarget=DepthBuffer;"
	// "Clear=Depth;"
	"RenderColorTarget0=ColorTex;"
	"RenderColorTarget1=PositionTex;"
	"RenderColorTarget2=NormalTex;"
	"ScriptExternal=Color;"
	"RenderColorTarget0=;"
	"RenderDepthStencilTarget=;"
	// "Pass=NoLighting;"; >
	"Pass=Lighting;"; >
{
	
	pass NoLighting< string Script= "Draw=Buffer;"; > {
		ZEnable = FALSE;
		ZWriteEnable = FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_3_0 drawSquadVS();
		PixelShader  = compile ps_3_0 drawPS();
	}
	pass Lighting< string Script= "Draw=Buffer;"; > {
		ZEnable =FALSE;
		ZWriteEnable =FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_3_0 drawSquadVS();
		PixelShader  = compile ps_3_0 drawLightPS();
	}
	
}

// vim: ft=fx
