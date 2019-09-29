////////////////////////////////////////////////////////////////////////////////////////////////
//
//  full.fx ver1.4
//  作成: 舞力介入P
//
////////////////////////////////////////////////////////////////////////////////////////////////
#define ENABLE_VSM
// #define ENABLE_SIMPLE_SM
// #define ENABLE_PCF

#define ZPREPASS_ENABLE

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
float4   EdgeColor         : EDGECOLOR;
// ライト色
float3   LightDiffuse      : DIFFUSE   < string Object = "Light"; >;
float3   LightAmbient      : AMBIENT   < string Object = "Light"; >;
float3   LightSpecular     : SPECULAR  < string Object = "Light"; >;
static float4 DiffuseColor  = MaterialDiffuse  * float4(LightDiffuse, 1.0f);
static float3 AmbientColor  = saturate(MaterialAmbient  * LightAmbient + MaterialEmmisive);
static float3 SpecularColor = MaterialSpecular * LightSpecular;

static bool parthf=false;   // パースペクティブフラグ
static bool transp=false;   // 半透明フラグ
bool spadd=false;;    // スフィアマップ加算合成フラグ
#define SKII1    1500
#define SKII2    8000
#define Toon     3

#define SHADOW_EPSILON 0.005

// スクリーンサイズ
float2 ViewportSize : VIEWPORTPIXELSIZE;

static float2 ViewportOffset = (float2(0.5,0.5)/ViewportSize);
static float2 ShadowMapSize = ViewportSize*3.f;


// オブジェクトのテクスチャ
texture ObjectTexture: MATERIALTEXTURE;
sampler ObjTexSampler = sampler_state {
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

////////////////////////////////////////////////////////////////////////////////////////////////
// 輪郭描画

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


///////////////////////////////////////////////////////////////////////////////////////////////
// 影（非セルフシャドウ）描画

// 頂点シェーダ
float4 Shadow_VS(float4 Pos : POSITION) : POSITION
{
    // カメラ視点のワールドビュー射影変換
    return mul( Pos, WorldViewProjMatrix );
}

// ピクセルシェーダ
float4 Shadow_PS() : COLOR
{
    // アンビエント色で塗りつぶし
    return float4(AmbientColor.rgb, 0.65f);
}

// 影描画用テクニック
technique ShadowTec < string MMDPass = "shadow"; > {
    pass DrawShadow {
        VertexShader = compile vs_2_0 Shadow_VS();
        PixelShader  = compile ps_2_0 Shadow_PS();
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
// オブジェクト描画（セルフシャドウOFF）

struct VS_OUTPUT {
    float4 Pos        : POSITION;    // 射影変換座標
    float2 Tex        : TEXCOORD1;   // テクスチャ
    float3 Normal     : TEXCOORD2;   // 法線
    float3 Eye        : TEXCOORD3;   // カメラとの相対位置
    float2 SpTex      : TEXCOORD4;	 // スフィアマップテクスチャ座標
    float4 Color      : COLOR0;      // ディフューズ色
};

// 頂点シェーダ
VS_OUTPUT Basic_VS(float4 Pos : POSITION, float3 Normal : NORMAL, float2 Tex : TEXCOORD0, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;
    
    // カメラ視点のワールドビュー射影変換
    Out.Pos = mul( Pos, WorldViewProjMatrix );
    
    // カメラとの相対位置
    Out.Eye = CameraPosition - mul( Pos, WorldMatrix );
    // 頂点法線
    Out.Normal = normalize( mul( Normal, (float3x3)WorldMatrix ) );
    
    // ディフューズ色＋アンビエント色 計算
    Out.Color.rgb = AmbientColor;
    if ( !useToon ) {
        Out.Color.rgb += max(0,dot( Out.Normal, -LightDirection )) * DiffuseColor.rgb;
    }
    Out.Color.a = DiffuseColor.a;
    Out.Color = saturate( Out.Color );
    
    // テクスチャ座標
    Out.Tex = Tex;
    
    if ( useSphereMap ) {
        // スフィアマップテクスチャ座標
        float2 NormalWV = mul( Out.Normal, (float3x3)ViewMatrix );
        Out.SpTex.x = NormalWV.x * 0.5f + 0.5f;
        Out.SpTex.y = NormalWV.y * -0.5f + 0.5f;
    }
    
    return Out;
}

// ピクセルシェーダ
float4 Basic_PS(VS_OUTPUT IN, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon) : COLOR0
{
    // スペキュラ色計算
    float3 HalfVector = normalize( normalize(IN.Eye) + -LightDirection );
    float3 Specular = pow( max(0,dot( HalfVector, normalize(IN.Normal) )), SpecularPower ) * SpecularColor;
    
    float4 Color = IN.Color;
    if ( useTexture ) {
        // テクスチャ適用
        Color *= tex2D( ObjTexSampler, IN.Tex );
    }
    if ( useSphereMap ) {
        // スフィアマップ適用
        if(spadd) Color.rgb += tex2D(ObjSphareSampler,IN.SpTex).rgb;
        else      Color.rgb *= tex2D(ObjSphareSampler,IN.SpTex).rgb;
    }
    
    if ( useToon ) {
        // トゥーン適用
        float LightNormal = dot( IN.Normal, -LightDirection );
        Color.rgb *= lerp(MaterialToon, float3(1,1,1), saturate(LightNormal * 16 + 0.5));
    }
    
    // スペキュラ適用
    Color.rgb += Specular;
    
    return Color;
}

// オブジェクト描画用テクニック（アクセサリ用）
// 不要なものは削除可
technique MainTec0 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = false; bool UseToon = false; > {
    pass DrawObject {
        VertexShader = compile vs_2_0 Basic_VS(false, false, false);
        PixelShader  = compile ps_2_0 Basic_PS(false, false, false);
    }
}

technique MainTec1 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = false; bool UseToon = false; > {
    pass DrawObject {
        VertexShader = compile vs_2_0 Basic_VS(true, false, false);
        PixelShader  = compile ps_2_0 Basic_PS(true, false, false);
    }
}

technique MainTec2 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = true; bool UseToon = false; > {
    pass DrawObject {
        VertexShader = compile vs_2_0 Basic_VS(false, true, false);
        PixelShader  = compile ps_2_0 Basic_PS(false, true, false);
    }
}

technique MainTec3 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = true; bool UseToon = false; > {
    pass DrawObject {
        VertexShader = compile vs_2_0 Basic_VS(true, true, false);
        PixelShader  = compile ps_2_0 Basic_PS(true, true, false);
    }
}

// オブジェクト描画用テクニック（PMDモデル用）
technique MainTec4 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = false; bool UseToon = true; > {
    pass DrawObject {
        VertexShader = compile vs_2_0 Basic_VS(false, false, true);
        PixelShader  = compile ps_2_0 Basic_PS(false, false, true);
    }
}

technique MainTec5 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = false; bool UseToon = true; > {
    pass DrawObject {
        VertexShader = compile vs_2_0 Basic_VS(true, false, true);
        PixelShader  = compile ps_2_0 Basic_PS(true, false, true);
    }
}

technique MainTec6 < string MMDPass = "object"; bool UseTexture = false; bool UseSphereMap = true; bool UseToon = true; > {
    pass DrawObject {
        VertexShader = compile vs_2_0 Basic_VS(false, true, true);
        PixelShader  = compile ps_2_0 Basic_PS(false, true, true);
    }
}

technique MainTec7 < string MMDPass = "object"; bool UseTexture = true; bool UseSphereMap = true; bool UseToon = true; > {
    pass DrawObject {
        VertexShader = compile vs_2_0 Basic_VS(true, true, true);
        PixelShader  = compile ps_2_0 Basic_PS(true, true, true);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
// セルフシャドウ用Z値プロット

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

	// float4 unpacked_depth = float4( 0.f, 65536.f, 0.f, 65536.f );
	// unpacked_depth.g *= modf( depth*65536.f, unpacked_depth.r);
	// unpacked_depth.a *= modf( depth*depth*65536.0f, unpacked_depth.b);

	// return unpacked_depth / 65536.f;  // 標準化
	
}

//バッファの精度を上げるのに使用
float4 ZValuePlot_PS( float4 ShadowMapTex : TEXCOORD0 ) : COLOR
{
	float depth = ShadowMapTex.z/ShadowMapTex.w;
	
	return float4( depth, 0.f, 0.f, 0.f );
	// float4 unpacked_depth = float4(0, 0, 256.0f, 256.0f);
	// unpacked_depth.g = modf( depth*256.0f, unpacked_depth.r);
	// unpacked_depth.b *= modf( unpacked_depth.g*256.0f, unpacked_depth.g );
	// // A成分を計算していませんが、
	// //それは冒頭に述べたようにfloat型の仮数部が23bitであるため、
	// //24bit以降の精度を求める意味がないためです。
	// return unpacked_depth / 256.0f;  // 標準化
}

float Convert_Color_To_Z( float4 color )
{
   return color.r + (color.g + color.b/256.0f) / 256.0f;
}

float2 Convert_Color_To_Z2( float4 color )
{
   return float2(color.r + color.g/65536.0f,  color.b+color.a/65536.0f );
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
        AlphaBlendEnable = FALSE;
        VertexShader = compile vs_2_0 ZValuePlot_VS();
        PixelShader  = compile ps_2_0 VSM_ZValuePlot_PS();
    }
#else
    pass ZValuePlot {
        AlphaBlendEnable = FALSE;
        VertexShader = compile vs_2_0 ZValuePlot_VS();
        PixelShader  = compile ps_2_0 ZValuePlot_PS();
    }
#endif

		
}


///////////////////////////////////////////////////////////////////////////////////////////////
// オブジェクト描画（セルフシャドウON）

// シャドウバッファのサンプラ。"register(s0)"なのはMMDがs0を使っているから
sampler DefSampler : register(s0);

struct BufferShadow_OUTPUT {
    float4 Pos      : POSITION;     // 射影変換座標
    float4 ZCalcTex : TEXCOORD0;    // Z値
    float2 Tex      : TEXCOORD1;    // テクスチャ
    float3 Normal   : TEXCOORD2;    // 法線
    float3 Eye      : TEXCOORD3;    // カメラとの相対位置
    float2 SpTex    : TEXCOORD4;	 // スフィアマップテクスチャ座標
    float4 Color    : COLOR0;       // ディフューズ色
};

// 頂点シェーダ
BufferShadow_OUTPUT BufferShadow_VS( MMM_SKINNING_INPUT IN, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon)
{
    BufferShadow_OUTPUT Out = (BufferShadow_OUTPUT)0;

		MMM_SKINNING_OUTPUT SkinOut = MMM_SkinnedPositionNormal( IN.Pos, IN.Normal, IN.BlendWeight, IN.BlendIndices, IN.SdefC, IN.SdefR0, IN.SdefR1 );
    // カメラ視点のワールドビュー射影変換
    Out.Pos = mul( SkinOut.Position, WorldViewProjMatrix );
    
    // カメラとの相対位置
    Out.Eye = CameraPosition - mul( SkinOut.Position, WorldMatrix );
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
    
    return Out;
}
struct PS_INPUT {
    float4 Pos      : VPOS;     // 射影変換座標
    float4 ZCalcTex : TEXCOORD0;    // Z値
    float2 Tex      : TEXCOORD1;    // テクスチャ
    float3 Normal   : TEXCOORD2;    // 法線
    float3 Eye      : TEXCOORD3;    // カメラとの相対位置
    float2 SpTex    : TEXCOORD4;	 // スフィアマップテクスチャ座標
    float4 Color    : COLOR0;       // ディフューズ色
};


struct PS_OUTPUT
{
	float4 Normal				: COLOR0;
	float4 Color				: COLOR1;
	// float4 Pos			: COLOR2;
};
// ピクセルシェーダ
float4 BufferShadow_PS(PS_INPUT IN, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon) : COLOR0
{
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
		
    // テクスチャ座標に変換
    IN.ZCalcTex /= IN.ZCalcTex.w;
    float2 TransTexCoord;
		
    TransTexCoord.x = (1.0f + IN.ZCalcTex.x)*0.5f;
    TransTexCoord.y = (1.0f - IN.ZCalcTex.y)*0.5f;
		
#if defined( ENABLE_VSM )
		// Variance Shadow Map 分散シャドウマップ
		if( any( saturate(TransTexCoord) != TransTexCoord ) ) {
		    // シャドウバッファ外
		    return Color;
		} else {
			// float2 shadow =  Convert_Color_To_Z2( tex2D( DefSampler, TransTexCoord ) );
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
			
			float4 ans = lerp(ShadowColor, Color, p);
			// if( transp ) ans.a = 0.5f;
			return ans;
		}
#elif defined( ENABLE_PCF )
		if( any( saturate(TransTexCoord) != TransTexCoord ) ) {
			// シャドウバッファ外
			return Color;
		} else {
			// Pixel is in lit area. Find out if it's
			// in shadow using 2x2 percentage closest filtering

			// transform to texel space
			float2 texelpos = ShadowMapSize * TransTexCoord;

			// Determine the lerp amounts           
			float2 lerps = frac( texelpos );

			//read in bilerp stamp, doing the shadow checks
			float sourcevals[4];
			sourcevals[0] = (tex2D( DefSampler, TransTexCoord ) +  SHADOW_EPSILON < IN.ZCalcTex.z)? 0.0f: 1.0f;  
			sourcevals[1] = (tex2D( DefSampler, TransTexCoord + float2(1.0/ShadowMapSize.x , 0) ) +  SHADOW_EPSILON < IN.ZCalcTex.z)? 0.0f: 1.0f;  
			sourcevals[2] = (tex2D( DefSampler, TransTexCoord + float2(0, 1.0/ShadowMapSize.y) ) + SHADOW_EPSILON < IN.ZCalcTex.z)? 0.0f: 1.0f;  
			sourcevals[3] = (tex2D( DefSampler, TransTexCoord + float2(1.0/ShadowMapSize.x, 1.0/ShadowMapSize.y) ) + SHADOW_EPSILON < IN.ZCalcTex.z)? 0.0f: 1.0f;  

			// lerp between the shadow values to calculate our light amount
			float LightAmount = lerp( lerp( sourcevals[0], sourcevals[1], lerps.x ),
					lerp( sourcevals[2], sourcevals[3], lerps.x ),
					lerps.y );
			// Light it
			return lerp(ShadowColor, Color, LightAmount);
		}

#elif defined( ENABLE_SIMPLE_SM )
		// シンプルなシャドウマップ
		if( any( saturate(TransTexCoord) != TransTexCoord ) ) {
			// シャドウバッファ外
			return Color;
		} else {
			// float SM_Z = Convert_Color_To_Z( tex2D( DefSampler, TransTexCoord ) );
			float SM_Z = tex2D( DefSampler, TransTexCoord ).x;

			// 算出点がシャドウマップのZ値よりも大きければ影と判断
			if( IN.ZCalcTex.z > SM_Z + 0.005){
				return ShadowColor;
			}
			return Color;
		}
#else
		// MMDのシャドウバッファ
		if( any( saturate(TransTexCoord) != TransTexCoord ) ) {
			// シャドウバッファ外
			return Color;
		} else {
			float comp;
			if(parthf) {
				// セルフシャドウ mode2
				// comp=1-saturate(max(IN.ZCalcTex.z-Convert_Color_To_Z( tex2D(DefSampler,TransTexCoord) ) , 0.0f)*SKII2*TransTexCoord.y-0.3f);
				comp=1-saturate(max(IN.ZCalcTex.z-tex2D(DefSampler,TransTexCoord).r, 0.0f)*SKII2*TransTexCoord.y-0.3f);
			} else {
				// セルフシャドウ mode1
				// comp=1-saturate(max(IN.ZCalcTex.z-Convert_Color_To_Z( tex2D(DefSampler,TransTexCoord) ) , 0.0f)*SKII1-0.3f);
				comp=1-saturate(max(IN.ZCalcTex.z-tex2D(DefSampler,TransTexCoord).r, 0.0f)*SKII1-0.3f);
			}
			if ( useToon ) {
				// トゥーン適用
				comp = min(saturate(dot(IN.Normal,-LightDirection)*Toon),comp);
				ShadowColor.rgb *= MaterialToon;
			}

			float4 ans = lerp(ShadowColor, Color, comp);
			if( transp ) ans.a = 0.5f;
			return ans;
		}
#endif
}


// オブジェクト描画用テクニック（アクセサリ用）
technique MainTecBS0  < string MMDPass = "object_ss"; bool UseTexture = false; bool UseSphereMap = false; bool UseToon = false; > {
	pass DrawObject {
#ifdef ZPREPASS_ENABLE
		ZWriteEnable=FALSE;
		ZFunc=Equal;
#endif
		VertexShader = compile vs_3_0 BufferShadow_VS(false, false, false);
		PixelShader  = compile ps_3_0 BufferShadow_PS(false, false, false);
	}
}

technique MainTecBS1  < string MMDPass = "object_ss"; bool UseTexture = true; bool UseSphereMap = false; bool UseToon = false; > {
	pass DrawObject {
#ifdef ZPREPASS_ENABLE
		ZWriteEnable=FALSE;
		ZFunc=Equal;
#endif
		VertexShader = compile vs_3_0 BufferShadow_VS(true, false, false);
		PixelShader  = compile ps_3_0 BufferShadow_PS(true, false, false);
	}
}

technique MainTecBS2  < string MMDPass = "object_ss"; bool UseTexture = false; bool UseSphereMap = true; bool UseToon = false; > {
	pass DrawObject {
#ifdef ZPREPASS_ENABLE
		ZWriteEnable=FALSE;
		ZFunc=Equal;
#endif
		VertexShader = compile vs_3_0 BufferShadow_VS(false, true, false);
		PixelShader  = compile ps_3_0 BufferShadow_PS(false, true, false);
	}
}

technique MainTecBS3  < string MMDPass = "object_ss"; bool UseTexture = true; bool UseSphereMap = true; bool UseToon = false; > {
	pass DrawObject {
#ifdef ZPREPASS_ENABLE
		ZWriteEnable=FALSE;
		ZFunc=Equal;
#endif
		VertexShader = compile vs_3_0 BufferShadow_VS(true, true, false);
		PixelShader  = compile ps_3_0 BufferShadow_PS(true, true, false);
	}
}

// オブジェクト描画用テクニック（PMDモデル用）
technique MainTecBS4  < string MMDPass = "object_ss"; bool UseTexture = false; bool UseSphereMap = false; bool UseToon = true; > {
	pass DrawObject {
#ifdef ZPREPASS_ENABLE
		ZWriteEnable=FALSE;
		ZFunc=Equal;
#endif
		VertexShader = compile vs_3_0 BufferShadow_VS(false, false, true);
		PixelShader  = compile ps_3_0 BufferShadow_PS(false, false, true);
	}
}

technique MainTecBS5  < string MMDPass = "object_ss"; bool UseTexture = true; bool UseSphereMap = false; bool UseToon = true; > {
	pass DrawObject {
#ifdef ZPREPASS_ENABLE
		ZWriteEnable=FALSE;
		ZFunc=Equal;
#endif
		VertexShader = compile vs_3_0 BufferShadow_VS(true, false, true);
		PixelShader  = compile ps_3_0 BufferShadow_PS(true, false, true);
	}
}

technique MainTecBS6  < string MMDPass = "object_ss"; bool UseTexture = false; bool UseSphereMap = true; bool UseToon = true; > {
	pass DrawObject {
#ifdef ZPREPASS_ENABLE
		ZWriteEnable=FALSE;
		ZFunc=Equal;
#endif
		VertexShader = compile vs_3_0 BufferShadow_VS(false, true, true);
		PixelShader  = compile ps_3_0 BufferShadow_PS(false, true, true);
	}
}

technique MainTecBS7  < string MMDPass = "object_ss"; bool UseTexture = true; bool UseSphereMap = true; bool UseToon = true; > {
	pass DrawObject {
#ifdef ZPREPASS_ENABLE
		ZWriteEnable=FALSE;
		ZFunc=Equal;
#endif
		VertexShader = compile vs_3_0 BufferShadow_VS(true, true, true);
		PixelShader  = compile ps_3_0 BufferShadow_PS(true, true, true);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////

//ZprePass {{{

#ifdef ZPREPASS_ENABLE
// 頂点シェーダ
float4 drawZPrePassVS( MMM_SKINNING_INPUT IN ) : POSITION0
{
	float4 pos = MMM_SkinnedPosition( IN.Pos, IN.BlendWeight, IN.BlendIndices, IN.SdefC, IN.SdefR0, IN.SdefR1 );

	// カメラ視点のワールドビュー射影変換
	return mul( pos, WorldViewProjMatrix );
}

// ピクセルシェーダ
float4 drawZPrePassPS() : COLOR0
{
	return float4(0,0,0,0);
}

technique ZPrePassTech  < string MMDPass = "zprepass"; > {
	pass ZPrePass {
		COLORWRITEENABLE=0;
		VertexShader = compile vs_3_0 drawZPrePassVS();
		PixelShader  = compile ps_3_0 drawZPrePassPS();
	}
}
#endif


//}}}
// vim: ft=fx
