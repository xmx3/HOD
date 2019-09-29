// ユーザーパラメータ

// ぼかし範囲 (サンプリング数は固定のため、大きくしすぎると縞が出ます) 
// にじみ
float Extent_S
<
   string UIName = "Extent_S";
   string UIWidget = "Slider";
   bool UIVisible =  true;
   float UIMin = 0.00;
   float UIMax = 0.01;
> = float( 0.0025 );

// ガウス
float Extent_G
<
   string UIName = "Extent_G";
   string UIWidget = "Slider";
   bool UIVisible =  true;
   float UIMin = 0.00;
   float UIMax = 0.01;
> = float( 0.0025 );

//発光強度
float Strength_A
<
   string UIName = "Strength_A";
   string UIWidget = "Slider";
   bool UIVisible =  true;
   float UIMin = 0.0;
   float UIMax = 10.0;
> = float( 2.0 );

float Strength_B
<
   string UIName = "Strength_B";
   string UIWidget = "Slider";
   bool UIVisible =  true;
   float UIMin = 0.0;
   float UIMax = 10.0;
> = float( 3 );


//点滅周期、単位：フレーム、0で停止
int Interval
<
   string UIName = "Interval";
   string UIWidget = "Numeric";
   bool UIVisible =  true;
   int UIMin = 0;
   int UIMax = 300;
> = 0;


//編集中の点滅をフレーム数に同期
#define SYNC false




// ぼかし処理の重み係数：
//    ガウス関数 exp( -x^2/(2*d^2) ) を d=5, x=0～7 について計算したのち、
//    (WT_7 + WT_6 + … + WT_1 + WT_0 + WT_1 + … + WT_7) が 1 になるように正規化したもの
#define  WT_0  0.0920246
#define  WT_1  0.0902024
#define  WT_2  0.0849494
#define  WT_3  0.0768654
#define  WT_4  0.0668236
#define  WT_5  0.0558158
#define  WT_6  0.0447932
#define  WT_7  0.0345379

#define PI 3.14159

static const float4 Color_Black = {0,0,0,1};
static const float4 Color_White = {1,1,1,1};

// マテリアル色
float alpha1 : CONTROLOBJECT < string name = "(self)"; string item = "Tr"; >;
//スケール
float scaling0 : CONTROLOBJECT < string name = "(self)"; >;
static float scaling = scaling0 * 0.1;

//時間
float ftime : TIME <bool SyncInEditMode = SYNC;>;
static float timerate = Interval ? ((1 + cos(ftime * 2 * PI * 30 / (float)Interval)) * 0.4 + 0.2) : 1.0;

// スクリーンサイズ
float2 ViewportSize : VIEWPORTPIXELSIZE;

static float2 ViewportOffset = (float2(0.5,0.5)/ViewportSize);
static float2 OnePx = (float2(1,1)/ViewportSize);

static float2 SampStep = (float2(Extent_G,Extent_G)/ViewportSize*ViewportSize.y);
static float2 SampStep2 = (float2(Extent_S,Extent_S)/ViewportSize*ViewportSize.y);


// レンダリングターゲットのクリア値
float4 ClearColor = {0,0,0,1};
float4 ClearColorTr = {0,0,0,0};
float ClearDepth  = 1.0;


// ぼかし結果を記録するためのレンダーターゲット
texture2D ScnMap : RENDERCOLORTARGET <
    float2 ViewPortRatio = {0.5,0.5};
    int MipLevels = 1;
    string Format = "A8R8G8B8" ;
>;
sampler2D ScnSamp = sampler_state {
    texture = <ScnMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;
    AddressU  = CLAMP;
    AddressV = CLAMP;
};

// 白とび表現関数
float4 OverExposure(float4 color){
    float4 newcolor = color;
    
    //ある色が1を超えると、他の色にあふれる
    newcolor.gb += max(color.r - 1, 0) * float2(0.65, 0.6);
    newcolor.rb += max(color.g - 1, 0) * float2(0.5, 0.6);
    newcolor.rg += max(color.b - 1, 0) * float2(0.5, 0.6);
    
    return newcolor;
}


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

// MMD本来のsamplerを上書きしないための記述です。削除不可。
// sampler MMDSamp0 : register(s0);
// sampler MMDSamp1 : register(s1);
// sampler MMDSamp2 : register(s2);


float Script : STANDARDSGLOBAL <
    string ScriptOutput = "color";
    string ScriptClass = "sceneorobject";
    string ScriptOrder = "postprocess";
> = 0.8;


#define TEXTURE_FORMAT "D3DFMT_A16B16G16R16F"
// #define TEXTURE_FORMAT "D3DFMT_A8R8G8B8"

shared texture2D PositionTex:RENDERCOLORTARGET<
    float2 ViewPortRatio = {1.0,1.0};
    int MipLevels = 1;
    string Format = TEXTURE_FORMAT ;
    string DefaultEffect = "self = hide;";
>;

sampler2D PositionSamp = sampler_state
{
	texture = < PositionTex >;
};

shared texture ColorTex: RENDERCOLORTARGET<
    float2 ViewPortRatio = {1.0,1.0};
    string Format = TEXTURE_FORMAT ;
    int MipLevels = 1;
    string DefaultEffect = "self = hide;";
    
>;

sampler ColorSamp = sampler_state
{
	texture = < ColorTex >;
};


shared texture NormalTex: RENDERCOLORTARGET<
    float2 ViewPortRatio = {1.0,1.0};
    int MipLevels = 1;
    string Format = TEXTURE_FORMAT ;
    string DefaultEffect = "self = hide;";
    
>;
sampler NormalSamp = sampler_state
{
	texture = < NormalTex >;
};

//MRTなのでViewPortRatioは１．０(他のターゲットと同じ）じゃないとだめっぽい
shared texture EmittionTex: RENDERCOLORTARGET<
    float2 ViewPortRatio = {1.0,1.0};
    int MipLevels = 1;
    string Format = "A8R8G8B8" ;
>;

sampler EmittionSamp = sampler_state
{
	texture = < EmittionTex >;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU  = CLAMP;
	AddressV = CLAMP;
};

// texture DepthTex: RENDERCOLORTARGET<
//     float2 ViewPortRatio = {1.0,1.0};
//     int MipLevels = 1;
//     string Format = "D3DFMT_R32F" ;
//     string DefaultEffect = "self = hide;";
//    
// >;
//
// sampler DepthSamp = sampler_state
// {
// 	texture = < DepthTex >;
// };
//
//
texture DepthBuffer : RenderDepthStencilTarget <
    float2 ViewPortRatio = {1.0,1.0};
    string Format = "D24S8";
>;


struct VS_Out
{
	float4 vertex : POSITION;
	float4 screen_pos : TEXCOORD0;
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
	// float4 normal = tex2D( NormalSamp, tex );
	float4 color = tex2D( ColorSamp, tex );
	// float4 position = tex2D( PositionSamp, tex );
	float4 em = tex2D( EmittionSamp, tex );
	return  color + em;
	// return color;
}


float4 drawLightPS(  float4 screen_pos: TEXCOORD0 ) : COLOR0
{
	float2 tex = (screen_pos.xy / screen_pos.w + 1.0) * 0.5;
	tex.y = 1.0-tex.y;

	float4 positionAndDepth = tex2D( PositionSamp, tex );
	
	float3 position = positionAndDepth.xyz;
	
	float4 normal = tex2D( NormalSamp, tex );
	float4 diffuse = tex2D( ColorSamp, tex );
	float3 eyeDir   = normalize( gCameraPosition - position );
	
	float4 color = diffuse*0.5;
	
	for( int i=0; i<NUM_LIGHT; ++i )
	{
		float3 LightDir = gLightPosition[ i ].xyz - position;
		float3 L = normalize( LightDir );
		float  attenution = 1.0f / length( LightDir )*20;
		color.rgb +=  gLightColor[ i ] * diffuse.rgb * max( dot( L, normal.xyz ), 0 )*attenution;
	}
	//
	color.a   = 1.0f;
	return color;  
}


//共通頂点シェーダ
struct VS_OUTPUT {
    float4 Pos            : POSITION;
    float2 Tex            : TEXCOORD0;
};

VS_OUTPUT VS_passDraw( float4 Pos : POSITION, float2 Tex : TEXCOORD0 ) {
    VS_OUTPUT Out = (VS_OUTPUT)0; 
    
    Out.Pos = Pos;
    Out.Tex = Tex + float2(ViewportOffset.x, ViewportOffset.y);
    
    return Out;
}

VS_OUTPUT VS_passDraw2( float4 Pos : POSITION, float2 Tex : TEXCOORD0 ) {
    VS_OUTPUT Out = (VS_OUTPUT)0; 
    
    Out.Pos = Pos;
    Out.Tex = Tex + float2(ViewportOffset.x * 2, ViewportOffset.y * 2);
    
    return Out;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// デバッグ用テクスチャ見るパス

float4 PS_Emitter( float2 Tex: TEXCOORD0 ) : COLOR {
    float4 Color;
    
    Color = tex2D( EmittionSamp, Tex );
    
    return Color;
}
float4 PS_ScnSamp( float2 Tex: TEXCOORD0 ) : COLOR {
    float4 Color;
    
    Color = tex2D( ScnSamp, Tex );
    
    return Color;
}
////////////////////////////////////////////////////////////////////////////////////////////////
// ファーストパス

float4 PS_first( float2 Tex: TEXCOORD0 ) : COLOR {
    float4 Color;
    
    //オフスクリーンターゲットより読み込み、軽いぼかし
    Color = tex2D( EmittionSamp, Tex ) * 2;
    Color += tex2D( EmittionSamp, Tex + float2(0, OnePx.y) );
    Color += tex2D( EmittionSamp, Tex + float2(0, -OnePx.y) );
    Color += tex2D( EmittionSamp, Tex + float2(OnePx.x, 0) );
    Color += tex2D( EmittionSamp, Tex + float2(OnePx.x, OnePx.y) );
    Color += tex2D( EmittionSamp, Tex + float2(OnePx.x, -OnePx.y) );
    Color += tex2D( EmittionSamp, Tex + float2(-OnePx.x, 0) );
    Color += tex2D( EmittionSamp, Tex + float2(-OnePx.x, OnePx.y) );
    Color += tex2D( EmittionSamp, Tex + float2(-OnePx.x, -OnePx.y) );
    
    Color /= 10;
    
    return Color;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// X方向にじみ


float4 PS_passSX( float2 Tex: TEXCOORD0 ) : COLOR {   
    float4 Color;
    float step = SampStep2.x * alpha1 * timerate;
    
    Color = tex2D( ScnSamp, Tex );
    
    Color = max(Color, (7.0/8.0) * tex2D( ScnSamp, Tex+float2(step     ,0)));
    Color = max(Color, (6.0/8.0) * tex2D( ScnSamp, Tex+float2(step * 2 ,0)));
    Color = max(Color, (5.0/8.0) * tex2D( ScnSamp, Tex+float2(step * 3 ,0)));
    Color = max(Color, (4.0/8.0) * tex2D( ScnSamp, Tex+float2(step * 4 ,0)));
    Color = max(Color, (3.0/8.0) * tex2D( ScnSamp, Tex+float2(step * 5 ,0)));
    Color = max(Color, (2.0/8.0) * tex2D( ScnSamp, Tex+float2(step * 6 ,0)));
    Color = max(Color, (1.0/8.0) * tex2D( ScnSamp, Tex+float2(step * 7 ,0)));
    
    Color = max(Color, (7.0/8.0) * tex2D( ScnSamp, Tex-float2(step     ,0)));
    Color = max(Color, (6.0/8.0) * tex2D( ScnSamp, Tex-float2(step * 2 ,0)));
    Color = max(Color, (5.0/8.0) * tex2D( ScnSamp, Tex-float2(step * 3 ,0)));
    Color = max(Color, (4.0/8.0) * tex2D( ScnSamp, Tex-float2(step * 4 ,0)));
    Color = max(Color, (3.0/8.0) * tex2D( ScnSamp, Tex-float2(step * 5 ,0)));
    Color = max(Color, (2.0/8.0) * tex2D( ScnSamp, Tex-float2(step * 6 ,0)));
    Color = max(Color, (1.0/8.0) * tex2D( ScnSamp, Tex-float2(step * 7 ,0)));
    
    return Color;
}


////////////////////////////////////////////////////////////////////////////////////////////////
// Y方向にじみ

float4 PS_passSY(float2 Tex: TEXCOORD0) : COLOR
{   
    float4 Color;
    float step = SampStep2.y * alpha1 * timerate;
    
    Color = tex2D( EmittionSamp, Tex );
    
    Color = max(Color, (7.0/8.0) * tex2D( EmittionSamp, Tex+float2(0, step    )));
    Color = max(Color, (6.0/8.0) * tex2D( EmittionSamp, Tex+float2(0, step * 2)));
    Color = max(Color, (5.0/8.0) * tex2D( EmittionSamp, Tex+float2(0, step * 3)));
    Color = max(Color, (4.0/8.0) * tex2D( EmittionSamp, Tex+float2(0, step * 4)));
    Color = max(Color, (3.0/8.0) * tex2D( EmittionSamp, Tex+float2(0, step * 5)));
    Color = max(Color, (2.0/8.0) * tex2D( EmittionSamp, Tex+float2(0, step * 6)));
    Color = max(Color, (1.0/8.0) * tex2D( EmittionSamp, Tex+float2(0, step * 7)));
    
    Color = max(Color, (7.0/8.0) * tex2D( EmittionSamp, Tex-float2(0, step    )));
    Color = max(Color, (6.0/8.0) * tex2D( EmittionSamp, Tex-float2(0, step * 2)));
    Color = max(Color, (5.0/8.0) * tex2D( EmittionSamp, Tex-float2(0, step * 3)));
    Color = max(Color, (4.0/8.0) * tex2D( EmittionSamp, Tex-float2(0, step * 4)));
    Color = max(Color, (3.0/8.0) * tex2D( EmittionSamp, Tex-float2(0, step * 5)));
    Color = max(Color, (2.0/8.0) * tex2D( EmittionSamp, Tex-float2(0, step * 6)));
    Color = max(Color, (1.0/8.0) * tex2D( EmittionSamp, Tex-float2(0, step * 7)));
    
    return Color;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// X方向ぼかし

float4 PS_passX( float2 Tex: TEXCOORD0 ) : COLOR {   
    float4 Color;
    float step = SampStep.x * alpha1 * timerate;
    
    Color  = WT_0 *   tex2D( ScnSamp, Tex );
    Color.rgb *= Strength_A;
    Color = OverExposure(Color);
    
    Color += WT_1 * ( tex2D( ScnSamp, Tex+float2(step    ,0) ) + tex2D( ScnSamp, Tex-float2(step    ,0) ) );
    Color += WT_2 * ( tex2D( ScnSamp, Tex+float2(step * 2,0) ) + tex2D( ScnSamp, Tex-float2(step * 2,0) ) );
    Color += WT_3 * ( tex2D( ScnSamp, Tex+float2(step * 3,0) ) + tex2D( ScnSamp, Tex-float2(step * 3,0) ) );
    Color += WT_4 * ( tex2D( ScnSamp, Tex+float2(step * 4,0) ) + tex2D( ScnSamp, Tex-float2(step * 4,0) ) );
    Color += WT_5 * ( tex2D( ScnSamp, Tex+float2(step * 5,0) ) + tex2D( ScnSamp, Tex-float2(step * 5,0) ) );
    Color += WT_6 * ( tex2D( ScnSamp, Tex+float2(step * 6,0) ) + tex2D( ScnSamp, Tex-float2(step * 6,0) ) );
    Color += WT_7 * ( tex2D( ScnSamp, Tex+float2(step * 7,0) ) + tex2D( ScnSamp, Tex-float2(step * 7,0) ) );
    
    return Color;
}


////////////////////////////////////////////////////////////////////////////////////////////////
// Y方向ぼかし

float4 PS_passY(float2 Tex: TEXCOORD0) : COLOR
{   
    float4 Color;
    float4 MaskColor;
    float step = SampStep.y * alpha1 * timerate;
    
    Color  = WT_0 *   tex2D( EmittionSamp, Tex );
    Color += WT_1 * ( tex2D( EmittionSamp, Tex+float2(0,step    ) ) + tex2D( EmittionSamp, Tex-float2(0,step    ) ) );
    Color += WT_2 * ( tex2D( EmittionSamp, Tex+float2(0,step * 2) ) + tex2D( EmittionSamp, Tex-float2(0,step * 2) ) );
    Color += WT_3 * ( tex2D( EmittionSamp, Tex+float2(0,step * 3) ) + tex2D( EmittionSamp, Tex-float2(0,step * 3) ) );
    Color += WT_4 * ( tex2D( EmittionSamp, Tex+float2(0,step * 4) ) + tex2D( EmittionSamp, Tex-float2(0,step * 4) ) );
    Color += WT_5 * ( tex2D( EmittionSamp, Tex+float2(0,step * 5) ) + tex2D( EmittionSamp, Tex-float2(0,step * 5) ) );
    Color += WT_6 * ( tex2D( EmittionSamp, Tex+float2(0,step * 6) ) + tex2D( EmittionSamp, Tex-float2(0,step * 6) ) );
    Color += WT_7 * ( tex2D( EmittionSamp, Tex+float2(0,step * 7) ) + tex2D( EmittionSamp, Tex-float2(0,step * 7) ) );
    
    // Color.rgb *= (Strength_B * scaling * timerate);
    Color.rgb *= (Strength_B * timerate);
    Color = OverExposure(Color);
    Color += tex2D( ColorSamp, Tex );
		
    
    //ブロック領域の適用
    // MaskColor = tex2D( ColorSamp, Tex );
    // Color.rgb *= MaskColor.a;
    Color.a = 1;//MaskColor.a;
    
    return Color;
}



// オブジェクト描画用テクニック
technique MainTec  <
string MMDPass = "object";
string Script = 
	//バッファクリア
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
	"RenderColorTarget=EmittionTex;"
	"Clear=Color;"
	
	//MRTに設定し、GBufferに描画
	"RenderColorTarget0=ColorTex;"
	"RenderColorTarget1=PositionTex;"
	"RenderColorTarget2=NormalTex;"
	"RenderColorTarget3=EmittionTex;"
	"ScriptExternal=Color;"
	
	//debug
	// "RenderColorTarget0=;"
	// "RenderDepthStencilTarget=;"
	// // "Pass=NoLighting;"
	// "Pass=drawEmitter;"
	
	"RenderColorTarget1=;"
	"RenderColorTarget2=;"
	"RenderColorTarget3=;"

	
	"RenderColorTarget0=ScnMap;"
	"RenderDepthStencilTarget=DepthBuffer;"
	"ClearSetColor=ClearColor; ClearSetDepth=ClearDepth;"
	"Clear=Color; Clear=Depth;"
	"Pass=FirstPass;"
	
	// //debug
	// "RenderColorTarget0=;"
	// "RenderDepthStencilTarget=;"
	// "Pass=drawScnSamp;"//scnmapを見たい
	
	"RenderColorTarget0=EmittionTex;"
	"RenderDepthStencilTarget=DepthBuffer;"
	"ClearSetColor=ClearColor; ClearSetDepth=ClearDepth;"
	"Clear=Color; Clear=Depth;"
	"Pass=Spread_X;"
	
	//debug
	// "RenderColorTarget0=;"
	// "RenderDepthStencilTarget=;"
	// "Pass=drawEmitter;"
	
	
	"RenderColorTarget0=ScnMap;"
	"RenderDepthStencilTarget=DepthBuffer;"
	"ClearSetColor=ClearColor; ClearSetDepth=ClearDepth;"
	"Clear=Color; Clear=Depth;"
	"Pass=Spread_Y;"
	
	//debug
	// "RenderColorTarget0=;"
	// "RenderDepthStencilTarget=;"
	// "Pass=drawScnSamp;"//scnmapyを見たい
	
	
	"RenderColorTarget0=EmittionTex;"
	"RenderDepthStencilTarget=DepthBuffer;"
	"ClearSetColor=ClearColor; ClearSetDepth=ClearDepth;"
	"Clear=Color; Clear=Depth;"
	"Pass=Gaussian_X;"
	
	//debug
	// "RenderColorTarget0=;"
	// "RenderDepthStencilTarget=;"
	// "Pass=drawEmitter;"
	
	
	"RenderColorTarget0=;"
	"RenderDepthStencilTarget=;"
	"Pass=Mix;"

	// "RenderColorTarget0=;"
	// "RenderDepthStencilTarget=;"
	// "Pass=NoLighting;"; >
	// // "Pass=Lighting;"
	;
> {
	
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
	pass FirstPass < string Script= "Draw=Buffer;"; > {
		ZEnable =FALSE;
		ZWriteEnable =FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_3_0 VS_passDraw();
		PixelShader  = compile ps_3_0 PS_first();
	}
	pass Spread_X < string Script= "Draw=Buffer;"; > {
		ZEnable =FALSE;
		ZWriteEnable =FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_3_0 VS_passDraw2();
		PixelShader  = compile ps_3_0 PS_passSX();
	}
	pass Spread_Y < string Script= "Draw=Buffer;"; > {
		ZEnable =FALSE;
		ZWriteEnable =FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_3_0 VS_passDraw2();
		PixelShader  = compile ps_3_0 PS_passSY();
	}
	pass Gaussian_X < string Script= "Draw=Buffer;"; > {
		ZEnable =FALSE;
		ZWriteEnable =FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_3_0 VS_passDraw2();
		PixelShader  = compile ps_3_0 PS_passX();
	}
	pass Gaussian_Y < string Script= "Draw=Buffer;"; > {
		ZEnable =FALSE;
		ZWriteEnable =FALSE;
		AlphaBlendEnable = FALSE;
		VertexShader = compile vs_3_0 VS_passDraw2();
		PixelShader  = compile ps_3_0 PS_passY();
	}
	pass Mix < string Script= "Draw=Buffer;"; > {
		ZEnable =FALSE;
		ZWriteEnable =FALSE;
		// AlphaBlendEnable = FALSE;
		SRCBLEND = ONE;
		DESTBLEND = ONE;
		VertexShader = compile vs_3_0 VS_passDraw2();
		PixelShader  = compile ps_3_0 PS_passY();
	}
	pass drawEmitter< string Script= "Draw=Buffer;"; > {
		VertexShader = compile vs_3_0 VS_passDraw();
		PixelShader  = compile ps_3_0 PS_Emitter();
	}
	pass drawScnSamp< string Script= "Draw=Buffer;"; > {
		VertexShader = compile vs_3_0 VS_passDraw();
		PixelShader  = compile ps_3_0 PS_ScnSamp();
	}
}

// vim: ft=fx
