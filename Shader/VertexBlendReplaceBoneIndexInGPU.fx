float4 gTransform[ 4 ] : register( c0 );
float4 gWorldMatrix[ 3 ] : register( c4 );
float4 gInvTransposedWorldMatrix[ 3 ] : register( c7 );
float4 gDiffuseColor : register( c10 );
static const int MAX_MATRICES = 12;
int4	mIndicesTable[MAX_MATRICES/4] : register( c11 );
float4    mWorldMatrixArray[MAX_MATRICES*3] : register( c14 );
float4x4    mViewProj : VIEWPROJECTION;
int NumUsedBones = 2;

struct VS_INPUT
{
    float4			Pos             : POSITION;
    float4			BlendWeights    : BLENDWEIGHT;
    int4			BlendIndices    : BLENDINDICES;
    float3			Normal          : NORMAL;
    float3			Tex0            : TEXCOORD0;//float2?
	float4			Color			: COLOR0;
};

struct ToPixel{
	float4 screenPosition : POSITION;
	float4 color : COLOR0; //頂点カラー
	float2 texCoord : TEXCOORD0; //テクスチャ座標
	float3 position : TEXCOORD1; //ローカル座標位置
	float3 normal : TEXCOORD2; //ローカル座標法線
};


//ピクセルに情報をおくるだけのVertexシェーダ
ToPixel VS_main( VS_INPUT i){
	ToPixel o;
	float3      Pos = 0.0f;
    float3      Normal = 0.0f;    

    // cast the vectors to arrays for use in the for loop below
    int   indicesTable[MAX_MATRICES]        = (int[MAX_MATRICES])mIndicesTable;
    
	float4 world[3] = {
						{ 0.0, 0.0, 0.0, 0.0, },
						{ 0.0, 0.0, 0.0, 0.0, },
						{ 0.0, 0.0, 0.0, 0.0, } };
	//int imax = min(NumBones, 4);
    // calculate the pos/normal using the "normal" weights 
    //        and accumulate the weights to calculate the last weight
    for (int iBone = 0; iBone < 2; iBone++)
    {
		if( i.BlendIndices[iBone]==255 ){
			break;
		}
		//cpuで実装すべきか？
		//cpuで実装したら遅かったのでこのままで
		for( int j = 0; j < 12; j++){
			if( i.BlendIndices[iBone]==indicesTable[j] ){
				world[0] += mWorldMatrixArray[j*3+0]  * i.BlendWeights[iBone];
				world[1] += mWorldMatrixArray[j*3+1]  * i.BlendWeights[iBone];
				world[2] += mWorldMatrixArray[j*3+2]  * i.BlendWeights[iBone];
				break;
			}
		}
	}

	Pos.x = dot( world[0], i.Pos );
	Pos.y = dot( world[1], i.Pos );
	Pos.z = dot( world[2], i.Pos );

	Normal.x = dot( (float3)world[0], i.Normal );
	Normal.y = dot( (float3)world[1], i.Normal );
	Normal.z = dot( (float3)world[2], i.Normal ); 
	
	// normalize normals
	Normal = normalize(Normal);

	o.screenPosition = mul( float4(Pos.xyz, 1.f) , mViewProj );
	//o.screenPosition.x = dot( gTransform[0], float4(Pos.xyz, 1.f) );
	//o.screenPosition.y = dot( gTransform[1], float4(Pos.xyz, 1.f) );
	//o.screenPosition.z = dot( gTransform[2], float4(Pos.xyz, 1.f) );
	//o.screenPosition.w = dot( gTransform[3], float4(Pos.xyz, 1.f) );
	float3 wp=Pos.xyz; //ワールド位置
	//float3 wn; //ワールド法線
	//wn.x = dot( gInvTransposedWorldMatrix[ 0 ].xyz, Normal );
	//wn.y = dot( gInvTransposedWorldMatrix[ 1 ].xyz, Normal );
	//wn.z = dot( gInvTransposedWorldMatrix[ 2 ].xyz, Normal );
#ifdef LINEAR_ZBUFFER
	o.screenPosition.z *= o.screenPosition.w;
#endif
	o.color = i.Color.zyxw * gDiffuseColor / 255.0;
	o.texCoord = i.Tex0;
	o.position = wp;
	//o.normal = wn;
	o.normal = Normal;
	return o;
}

sampler2D gSampler : register( s0 );

struct FromVertex{
	float4 color : COLOR0; //頂点カラー
	float2 texCoord : TEXCOORD0;
	float3 position : TEXCOORD1;
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
	float4 c = input.color * tex2D( gSampler, input.texCoord );
	//c.xyz *= dc.xyz;
	//c.xyz += sc * gSpecularColor.xyz;
	//c.xyz += gEmissionColor.xyz;
	//c.w = c.w;
	return c;
}

//////////////////////////////////////
// Techniques specs follow
//////////////////////////////////////
technique t0
{


    pass p0
    {
        VertexShader = compile vs_3_0 VS_main();
        PixelShader = compile ps_3_0 PS_main();
    }
}

