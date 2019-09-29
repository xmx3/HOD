//
// Skinned Mesh Effect file 
// Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//

float4 lhtDir = {0.0f, 0.0f, -1.0f, 1.0f};    //light Direction 
float4 lightDiffuse = {0.6f, 0.6f, 0.6f, 1.0f}; // Light Diffuse
float4 MaterialAmbient : MATERIALAMBIENT = {0.1f, 0.1f, 0.1f, 1.0f};
float4 MaterialDiffuse : MATERIALDIFFUSE = {0.8f, 0.8f, 0.8f, 1.0f};

// Matrix Pallette
static const int MAX_MATRICES = 12;
float4x4    mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
int			mIndecesTable[MAX_MATRICES];
float4x4    mViewProj : VIEWPROJECTION;

///////////////////////////////////////////////////////
struct VS_INPUT
{
    float4			Pos             : POSITION;
    float4			BlendWeights    : BLENDWEIGHT;
    float4			BlendIndices    : BLENDINDICES;
    float3			Normal          : NORMAL;
    float3			Tex0            : TEXCOORD0;
	float4			Color			: COLOR0;
};

struct VS_OUTPUT
{
    float4  Pos     : POSITION;
    float4  Diffuse : COLOR0;
    float2  Tex0    : TEXCOORD0;
};


float3 Diffuse(float3 Normal)
{
    float CosTheta;
    
    // N.L Clamped
    CosTheta = max(0.0f, dot(Normal, lhtDir.xyz));
       
    // propogate scalar result to vector
    return (CosTheta);
}


VS_OUTPUT VShade(VS_INPUT i, uniform int NumBones)
{
    VS_OUTPUT   o;
    float3      Pos = 0.0f;
    float3      Normal = 0.0f;    

    o.Pos = mul(float4(i.Pos.xyz, 1.0f), mViewProj);
	o.Diffuse.x = 1.0f;
    o.Diffuse.y = 1.0f;
    o.Diffuse.z = 1.0f;
    o.Diffuse.w = 1.0f;


/*     
	// Compensate for lack of UBYTE4 on Geforce3
    int4 IndexVector = D3DCOLORtoUBYTE4(i.BlendIndices);


    // cast the vectors to arrays for use in the for loop below
    float BlendWeightsArray[4] = (float[4])i.BlendWeights;
    int   IndexArray[4]        = (int[4])IndexVector;
    
	int imax = min(NumBones, 4);
    // calculate the pos/normal using the "normal" weights 
    //        and accumulate the weights to calculate the last weight
    for (int iBone = 0; iBone < imax; iBone++)
    {
		float4x4 world;
		for (int j = 0; j < 12; j++){
			if( IndexArray[iBone]==mIndecesTable[j] ){
				world=mWorldMatrixArray[j];
				break;
			}
		}
		
		
//		if( IndexArray[iBone]==mIndecesTable[0] ){
//			world=mWorldMatrixArray[0];
//		} else if( IndexArray[iBone]==mIndecesTable[1] ){
//			world=mWorldMatrixArray[1];
//		} else if( IndexArray[iBone]==mIndecesTable[2] ){
//			world=mWorldMatrixArray[2];
//		} else if( IndexArray[iBone]==mIndecesTable[3] ){
//			world=mWorldMatrixArray[3];
//		} else if( IndexArray[iBone]==mIndecesTable[4] ){
//			world=mWorldMatrixArray[4];
//		} else if( IndexArray[iBone]==mIndecesTable[5] ){
//			world=mWorldMatrixArray[5];
//		} else if( IndexArray[iBone]==mIndecesTable[6] ){
//			world=mWorldMatrixArray[6];
//		} else if( IndexArray[iBone]==mIndecesTable[7] ){
//			world=mWorldMatrixArray[7];
//		} else if( IndexArray[iBone]==mIndecesTable[8] ){
//			world=mWorldMatrixArray[8];
//		} else if( IndexArray[iBone]==mIndecesTable[9] ){
//			world=mWorldMatrixArray[9];
//		} else if( IndexArray[iBone]==mIndecesTable[10] ){
//			world=mWorldMatrixArray[10];
//		} else if( IndexArray[iBone]==mIndecesTable[11] ){
//			world=mWorldMatrixArray[11];
//		}

    
        Pos += mul(i.Pos, world) * BlendWeightsArray[iBone];
        Normal += mul(i.Normal, world) * BlendWeightsArray[iBone];
    }
    
    // transform position from world space into view and then projection space
    o.Pos = mul(float4(Pos.xyz, 1.0f), mViewProj);

    // normalize normals
    Normal = normalize(Normal);

    // Shade (Ambient + etc.)
    //o.Diffuse.xyz = MaterialAmbient.xyz + Diffuse(Normal) * MaterialDiffuse.xyz;
    
*/
    // copy the input texture coordinate through
    o.Tex0  = i.Tex0.xy;

    return o;
}


///pixelShader
float3 gAmbient : register( c0 );
float4 gLightPosX : register( c1 );
float4 gLightPosY : register( c2 );
float4 gLightPosZ : register( c3 );
float3 gEyePosition : register( c4 );
float4 gSpecularColor : register( c5 );
float3 gLightColor0 : register( c6 );
float3 gLightColor1 : register( c7 );
float3 gLightColor2 : register( c8 );
float3 gLightColor3 : register( c9 );
float3 gEmissionColor : register( c10 );

sampler2D gSampler : register( s0 );

struct FromVertex{
	float4 color : COLOR0; //頂点カラー
	float2 texCoord : TEXCOORD0;
	float4 position : TEXCOORD1;
	float3 normal : TEXCOORD2;
};

float4 PS_main( FromVertex input ) : COLOR {
/*
	//反射ベクタの生成(ただし視線ベクタに対して)
	float3 ev = gEyePosition - input.position;
	float3 nv = normalize( input.normal );
	float3 rv = 2.0 * nv * dot( nv, ev ) - ev;
	//ライトベクタの生成
	float4 lvX, lvY, lvZ;
	lvX = gLightPosX - input.position.xxxx;
	lvY = gLightPosY - input.position.yyyy;
	lvZ = gLightPosZ - input.position.zzzz;
	//ライトベクタと反射ベクタの内積
	float4 s;
	s = lvX * rv.xxxx;
	s += lvY * rv.yyyy;
	s += lvZ * rv.zzzz;
	//指数関数を取る前に |L||R|で除す必要あり。
	float4 lvL2 = lvX * lvX; //ライトベクタ二乗長さ
	lvL2 += lvY * lvY;
	lvL2 += lvZ * lvZ;
	lvL2 += 0.0001; //0割り防止
	float4 rcpLvL = rsqrt( lvL2 ); //長さの逆数
	float4 rvL2 = dot( rv, rv );
	s *= rsqrt( lvL2 * rvL2 );
	s = max( 0, s );
	s = pow( s, gSpecularColor.w );
	//さらにライト距離で除す
	s *= rcpLvL;
	//ディフューズ項を計算する。
	float4 d = lvX * nv.xxxx;
	d += lvY * nv.yyyy;
	d += lvZ * nv.zzzz; 
	d *= rcpLvL * rcpLvL; //これを|L|^2で除する。
	d = max( 0, d );

	float3 dc = gAmbient;
	dc += gLightColor0 * d.x;
	dc += gLightColor1 * d.y;
	dc += gLightColor2 * d.z;
	dc += gLightColor3 * d.w;
	float3 sc = 0;
	sc += gLightColor0 * s.x;
	sc += gLightColor1 * s.y;
	sc += gLightColor2 * s.z;
	sc += gLightColor3 * s.w;

	float4 c = input.color * tex2D( gSampler, input.texCoord );
	c.xyz *= dc.xyz;
	c.xyz += sc * gSpecularColor.xyz;
	c.xyz += gEmissionColor.xyz;
	c.w = c.w;
	return c;
*/

	float4 c = input.color;
	return c;
}














int NumUsedBones = 2;
VertexShader vsArray[12] = {compile vs_3_0 VShade(1), 
                            compile vs_3_0 VShade(2),
                            compile vs_3_0 VShade(3),
                            compile vs_3_0 VShade(4),
                            compile vs_3_0 VShade(5),
                            compile vs_3_0 VShade(6),
                            compile vs_3_0 VShade(7),
                            compile vs_3_0 VShade(8),
                            compile vs_3_0 VShade(9),
                            compile vs_3_0 VShade(10),
                            compile vs_3_0 VShade(11),
                            compile vs_3_0 VShade(12)
                          };


//////////////////////////////////////
// Techniques specs follow
//////////////////////////////////////
technique t0
{
    pass p0
    {
        VertexShader = (vsArray[NumUsedBones]);
		PixelShader = compile ps_2_0 PS_main();
    }
}

