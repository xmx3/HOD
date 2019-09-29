////////////////////////////////////////////////////////////////////////////////////////////////
//
//  basic.fx ver1.2
//  作成: 舞力介入P
//
////////////////////////////////////////////////////////////////////////////////////////////////
// #define ENABLE_VSM
// #define DISABLE_SHADOW

// パラメータ宣言

// 座法変換行列
float4x4 WorldViewProjMatrix      : WORLDVIEWPROJECTION;
float4x4 WorldMatrix              : WORLD;
float4x4 ViewMatrix               : VIEW;
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
float znear : ZNEAR;
float zfar : ZFAR;

static bool     parthf=true;   // パースペクティブフラグ
static bool     transp=false;   // 半透明フラグ
bool	 spadd;    // スフィアマップ加算合成フラグ
#define SKII1    1500
#define SKII2    8000
#define Toon     3

#define SPECULAR_BASE 100
static bool IsEmittion = (SPECULAR_BASE <= SpecularPower) && (dot(MaterialSpecular, MaterialSpecular) < 0.01);
// static float EmittionPower0 = IsEmittion ? ((SpecularPower - SPECULAR_BASE) / 7.0) : 1;
// static float EmittionPower1 = EmittionPower0 * (LightUp * 2 + 1.0) * pow(400, LightUpE) * (1.0 - LightOff);






// オブジェクトのテクスチャ
texture ObjectTexture: MATERIALTEXTURE;
sampler ObjTexSampler = sampler_state
{
	texture = <ObjectTexture>;
	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
};

// スフィアマップのテクスチャ
texture ObjectSphereMap: MATERIALSPHEREMAP;
sampler ObjSphareSampler = sampler_state {
	texture = <ObjectSphereMap>;
	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
};



// MMD本来のsamplerを上書きしないための記述です。削除不可。
// sampler MMDSamp0 : register(s0);
// sampler MMDSamp1 : register(s1);
// sampler MMDSamp2 : register(s2);

// オブジェクト描画{{{

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
	float4 Color		: COLOR0;
	float4 Pos			: COLOR1;
	float4 Normal		: COLOR2;
	float4 Emittion	: COLOR3;
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

// オブジェクト描画用テクニック{{{
// 不要なものは削除可
technique MainTec0 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = false; bool UseToon = false; bool UseSelfShadow = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferVS(false, false, false);
		PixelShader  = compile ps_3_0 drawGBufferPS(false, false, false);
	}
}

technique MainTec1 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = false; bool UseToon = false; bool UseSelfShadow = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferVS(true, false, false);
		PixelShader  = compile ps_3_0 drawGBufferPS(true, false, false);
	}
}

technique MainTec2 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = true; bool UseToon = false; bool UseSelfShadow = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferVS(false, true, false);
		PixelShader  = compile ps_3_0 drawGBufferPS(false, true, false);
	}
}

technique MainTec3 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = true; bool UseToon = false; bool UseSelfShadow = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;

		VertexShader = compile vs_3_0 drawGBufferVS(true, true, false);
		PixelShader  = compile ps_3_0 drawGBufferPS(true, true, false);
	}
}

// オブジェクト描画用テクニック（PMDモデル用）
technique MainTec4 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = false; bool UseToon = true; bool UseSelfShadow = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;

		VertexShader = compile vs_3_0 drawGBufferVS(false, false, true);
		PixelShader  = compile ps_3_0 drawGBufferPS(false, false, true);
	}
}

technique MainTec5 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = false; bool UseToon = true; bool UseSelfShadow = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;

		VertexShader = compile vs_3_0 drawGBufferVS(true, false, true);
		PixelShader  = compile ps_3_0 drawGBufferPS(true, false, true);
	}
}

technique MainTec6 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = true; bool UseToon = true; bool UseSelfShadow = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferVS(false, true, true);
		PixelShader  = compile ps_3_0 drawGBufferPS(false, true, true);
	}
}

technique MainTec7 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = true; bool UseToon = true; bool UseSelfShadow = false; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferVS(true, true, true);
		PixelShader  = compile ps_3_0 drawGBufferPS(true, true, true);
	}
}
//}}}

//}}}

//オブジェクト描画(影つき) {{{ 
	
struct BufferShadow_OUTPUT {
	float4 Pos      : POSITION;     // 射影変換座標
	float4 ZCalcTex : TEXCOORD0;    // Z値
	float2 Tex      : TEXCOORD1;    // テクスチャ
	float3 Normal   : TEXCOORD2;    // 法線
	float3 Eye      : TEXCOORD3;    // カメラとの相対位置
	float2 SpTex    : TEXCOORD4;	 // スフィアマップテクスチャ座標
	float4 WorldPos : TEXCOORD5;
	float4 Color    : COLOR0;       // ディフューズ色
	float4 Emittion : COLOR1;
};

// シャドウバッファのサンプラ。"register(s0)"なのはMMDがs0を使っているから
sampler DefSampler : register(s0);


// 頂点シェーダ
BufferShadow_OUTPUT drawGBufferShadowVS( MMM_SKINNING_INPUT IN, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon)
{
	BufferShadow_OUTPUT Out = (BufferShadow_OUTPUT)0;


	MMM_SKINNING_OUTPUT SkinOut = MMM_SkinnedPositionNormal( IN.Pos, IN.Normal, IN.BlendWeight, IN.BlendIndices, IN.SdefC, IN.SdefR0, IN.SdefR1 );
	// カメラ視点のワールドビュー射影変換
	Out.Pos = mul( SkinOut.Position, WorldViewProjMatrix );
	Out.WorldPos = mul( SkinOut.Position, WorldMatrix );

	// カメラとの相対位置
	Out.Eye = CameraPosition - Out.WorldPos;
	// 頂点法線
	Out.Normal = normalize( mul( SkinOut.Normal, (float3x3)WorldMatrix ) );
	// ライト視点によるワールドビュー射影変換
	Out.ZCalcTex = mul( SkinOut.Position, LightWorldViewProjMatrix );

	// ディフューズ色＋アンビエント色 計算
	Out.Color.rgb = AmbientColor;
	if ( !useToon ) {
		Out.Color.rgb += max(0,dot( Out.Normal, -LightDirection )) * DiffuseColor.rgb;
	}
	Out.Color.a = DiffuseColor.a;
	Out.Color = saturate( Out.Color );

	// テクスチャ座標
	Out.Tex = IN.Tex;

	if ( useSphereMap ) {
		// スフィアマップテクスチャ座標
		float2 NormalWV = mul( Out.Normal, (float3x3)ViewMatrix );
		Out.SpTex.x = NormalWV.x * 0.5f + 0.5f;
		Out.SpTex.y = NormalWV.y * -0.5f + 0.5f;
	}
	
	//発光色
	if( IsEmittion ) {
		Out.Emittion = MaterialDiffuse;
		Out.Emittion.rgb += MaterialEmmisive * 0.5;
		Out.Emittion.rgb *= 0.5;
	}

	return Out;
}

// ピクセルシェーダ
PS_OUTPUT drawGBufferShadowPS(BufferShadow_OUTPUT IN, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon)
{
	PS_OUTPUT Out = (PS_OUTPUT)0;
	Out.Normal=float4( IN.Normal, 1.0 );
	Out.Pos = IN.WorldPos;
	Out.Emittion = IN.Emittion;
	// スペキュラ色計算
	float3 HalfVector = normalize( normalize(IN.Eye) + -LightDirection );
	float3 Specular = pow( max(0,dot( HalfVector, normalize(IN.Normal) )), SpecularPower ) * SpecularColor;

	float4 Color = IN.Color;
	float4 ShadowColor = float4(AmbientColor, Color.a);  // 影の色
	if ( useTexture ) {
		// テクスチャ適用
		float4 TexColor = tex2D( ObjTexSampler, IN.Tex );
		Color *= TexColor;
		ShadowColor *= TexColor;
	}
	if ( useSphereMap ) {
		// スフィアマップ適用
		float4 TexColor = tex2D(ObjSphareSampler,IN.SpTex);
		if(spadd) {
			Color.rgb += TexColor.rgb;
			ShadowColor.rgb += TexColor.rgb;
		} else {
			Color.rgb *= TexColor.rgb;
			ShadowColor.rgb *= TexColor.rgb;
		}
	}
	// スペキュラ適用
	Color.rgb += Specular;
#if defined( DISABLE_SHADOW )
	Out.Color = Color;
	return Out;
#endif

	// テクスチャ座標に変換
	IN.ZCalcTex /= IN.ZCalcTex.w;
	float2 TransTexCoord;
	TransTexCoord.x = (1.0f + IN.ZCalcTex.x)*0.5f;
	TransTexCoord.y = (1.0f - IN.ZCalcTex.y)*0.5f;


#if defined( ENABLE_VSM )
	// Variance Shadow Map 分散シャドウマップ
	if( any( saturate(TransTexCoord) != TransTexCoord ) ) {
		// シャドウバッファ外
		Out.Color=Color;
		return Out;
	} else {
		float2 shadow =  tex2D( DefSampler, TransTexCoord );
		shadow += 0.0001;

		float e_x2 = shadow.y;
		float ex_2 = shadow.x * shadow.x;
		float variance = e_x2 - ex_2;
		float md = shadow.x - IN.ZCalcTex.z;
		float p = variance / ( variance + (md * md) );
		p = saturate( max( p, IN.ZCalcTex.z < shadow.x ) );
		// トゥーン適用
		if ( useToon ) {
			p = min(saturate(dot(IN.Normal,-LightDirection)*Toon), p);
			ShadowColor.rgb *= MaterialToon;
		}

		Out.Color = lerp(ShadowColor, Color, p);
		return Out;
	}
// #else
// 	if( any( saturate(TransTexCoord) != TransTexCoord ) ) {
// 		// シャドウバッファ外
// 		Out.Color = Color;
// 		return Out;
// 	} else {
// 		float comp;
// 		if(parthf) {
// 			// セルフシャドウ mode2
// 			comp=1-saturate(max(IN.ZCalcTex.z-tex2D(DefSampler,TransTexCoord).r , 0.0f)*SKII2*TransTexCoord.y-0.3f);
// 		} else {
// 			// セルフシャドウ mode1
// 			comp=1-saturate(max(IN.ZCalcTex.z-tex2D(DefSampler,TransTexCoord).r , 0.0f)*SKII1-0.3f);
// 		}
// 		if ( useToon ) {
// 			// トゥーン適用
// 			comp = min(saturate(dot(IN.Normal,-LightDirection)*Toon),comp);
// 			ShadowColor.rgb *= MaterialToon;
// 		}
//
// 		float4 ans = lerp(ShadowColor, Color, comp);
// 		// if( transp ) ans.a = 0.5f;
// 		Out.Color = ans;
// 		return Out;
// 	}
#else
	if( any( saturate(TransTexCoord) != TransTexCoord ) ) {
		// シャドウバッファ外
		Out.Color=Color;
		return Out;
	} else {
		float2 shadow =  tex2D( DefSampler, TransTexCoord );
		// shadow.x += 0.0001;
		shadow.x += 0.005;
		
		//slop scaled biasもどき(微妙)
		// float sbias = 0.005*tan(acos( dot(IN.Normal, LightDirection) ) );
		// sbias = clamp(sbias, -0.005 , 0.005 );
		// shadow.x -= sbias;

		if( IN.ZCalcTex.z > shadow.x ){
			Out.Color = ShadowColor;
		} else {
			Out.Color = Color;
		}

		return Out;
	}

#endif
}

//テクニック{{{
technique MainTec8 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = false; bool UseToon = false; bool UseSelfShadow = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferShadowVS(false, false, false);
		PixelShader  = compile ps_3_0 drawGBufferShadowPS(false, false, false);
	}
}

technique MainTec9 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = false; bool UseToon = false; bool UseSelfShadow = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferShadowVS(true, false, false);
		PixelShader  = compile ps_3_0 drawGBufferShadowPS(true, false, false);
	}
}

technique MainTec10 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = true; bool UseToon = false; bool UseSelfShadow = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferShadowVS(false, true, false);
		PixelShader  = compile ps_3_0 drawGBufferShadowPS(false, true, false);
	}
}

technique MainTec11 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = true; bool UseToon = false; bool UseSelfShadow = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;

		VertexShader = compile vs_3_0 drawGBufferShadowVS(true, true, false);
		PixelShader  = compile ps_3_0 drawGBufferShadowPS(true, true, false);
	}
}

// オブジェクト描画用テクニック（PMDモデル用）
technique MainTec12 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = false; bool UseToon = true; bool UseSelfShadow = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;

		VertexShader = compile vs_3_0 drawGBufferShadowVS(false, false, true);
		PixelShader  = compile ps_3_0 drawGBufferShadowPS(false, false, true);
	}
}

technique MainTec13 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = false; bool UseToon = true; bool UseSelfShadow = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;

		VertexShader = compile vs_3_0 drawGBufferShadowVS(true, false, true);
		PixelShader  = compile ps_3_0 drawGBufferShadowPS(true, false, true);
	}
}

technique MainTec14 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = true; bool UseToon = true; bool UseSelfShadow = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferShadowVS(false, true, true);
		PixelShader  = compile ps_3_0 drawGBufferShadowPS(false, true, true);
	}
}

technique MainTec15 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = true; bool UseToon = true; bool UseSelfShadow = true; > {
	pass DrawGBuffer{
		AlphaBlendEnable = FALSE;
		AlphaTestEnable  = FALSE;
		VertexShader = compile vs_3_0 drawGBufferShadowVS(true, true, true);
		PixelShader  = compile ps_3_0 drawGBufferShadowPS(true, true, true);
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
	
	float z=Pos.w;
	float zn=znear;
	float zf=zfar;
	
	
	//横に1ドットは保障する
	{
		float w=640;
		float h=480;
	
		float3 n = mul( SkinOut.Normal, (float3x3)WorldViewProjMatrix );
		n=sign(n);//横の長さを1ドットにするため,xの方向が知りたい

		//エッジは1ドットなのでその分ずらす
		// Pos.x += n.x*( 2.f*z/w -2.f*zn/w );
		Pos.y += n.y*( 2.f/h*z -2.f*zn/h );//こっちも増やすとおかしい
	}
	
	
	//24bit
	//float da=5.96e-08;
	//float最小値 深度バッファの制度を変えた場合ここの値を変える事
	static const float da=1.175494351e-38F;
	// static const float da=0.0001;

	// <a href="http://marupeke296.com/DXG_No71_depthbuffer.html">その71 深度バッファの精度って？</a>
	//最短距離を求める
	float a =1.f/(1.f/z - da*(zf-zn)/(zf*zn)) - z;
	//一つの面で裏表のあるポリゴンが描画されてしまうのを防ぐため
	Pos.z += zf*a/(zf-zn);
	Pos.w += a;
	
	
	// (Pos.w-zn)/(zf-zn); 0-1の間
	
	// Pos.w -= (Pos.w-zn)/(zf-zn);
	


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
