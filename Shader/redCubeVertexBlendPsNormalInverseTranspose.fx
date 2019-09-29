//ピクセルに情報をおくるだけのシェーダ
float4 gTransform[ 4 ] : register( c0 );
float4 gWorldMatrix[ 3 ] : register( c4 );
float4 gInvTransposedWorldMatrix[ 3 ] : register( c7 );
float4 gDiffuseColor : register( c10 );
static const int MAX_MATRICES = 2;
/*static const int MAX_MATRICES = 32;*/
bool gIsVertexBlend : register(c19);
float4 gWorldMatrixArray[MAX_MATRICES*3] : register( c20 );
float4 gNormalWorlds[MAX_MATRICES*3] : register( c26 );

struct ToPixel{
	float4 screenPosition : POSITION;
	float4 color : COLOR0; //頂点カラー
	float2 texCoord : TEXCOORD0; //テクスチャ座標
	float3 position : TEXCOORD1; //ローカル座標位置
	float3 normal : TEXCOORD2; //ローカル座標法線
};

struct VsInput{
	float4			pos             : POSITION;
	float4			blendWeights    : BLENDWEIGHT;
	int4				blendIndices    : BLENDINDICES;
	float3			normal          : NORMAL;
	float2			tex0            : TEXCOORD0;
	float4			color			: COLOR0;
};

ToPixel mainVS( VsInput i ){
	ToPixel o;
	float4 localPos;
	float4 world[3] = {
		{ 0.0, 0.0, 0.0, 0.0, },
		{ 0.0, 0.0, 0.0, 0.0, },
		{ 0.0, 0.0, 0.0, 0.0, } };
	float4 normalWorld[3] ={ 
		{ 0.0, 0.0, 0.0, 0.0, },
		{ 0.0, 0.0, 0.0, 0.0, },
		{ 0.0, 0.0, 0.0, 0.0, } };

	for (int iBone = 0; iBone<2; iBone++){
		world[0] += gWorldMatrixArray[i.blendIndices[iBone]*3+0]  * i.blendWeights[iBone];
		world[1] += gWorldMatrixArray[i.blendIndices[iBone]*3+1]  * i.blendWeights[iBone];
		world[2] += gWorldMatrixArray[i.blendIndices[iBone]*3+2]  * i.blendWeights[iBone];
	
		normalWorld[0] += gNormalWorlds[i.blendIndices[iBone]*3+0]  * i.blendWeights[iBone];
		normalWorld[1] += gNormalWorlds[i.blendIndices[iBone]*3+1]  * i.blendWeights[iBone];
		normalWorld[2] += gNormalWorlds[i.blendIndices[iBone]*3+2]  * i.blendWeights[iBone];
	}
	
	localPos.x = dot( world[ 0 ], i.pos );
	localPos.y = dot( world[ 1 ], i.pos );
	localPos.z = dot( world[ 2 ], i.pos );
	localPos.w = 1.0;
	
	//pvw変換
	o.screenPosition.x = dot( gTransform[ 0 ], localPos );
	o.screenPosition.y = dot( gTransform[ 1 ], localPos );
	o.screenPosition.z = dot( gTransform[ 2 ], localPos );
	o.screenPosition.w = dot( gTransform[ 3 ], localPos );
	
	//w変換
	o.position.x = dot( gWorldMatrix[ 0 ], localPos );
	o.position.y = dot( gWorldMatrix[ 1 ], localPos );
	o.position.z = dot( gWorldMatrix[ 2 ], localPos );
	
	float3 n;
	/*n.x = dot( world[ 0 ].xyz, i.normal );*/
	/*n.y = dot( world[ 1 ].xyz, i.normal );*/
	/*n.z = dot( world[ 2 ].xyz, i.normal );*/
	
	
	n.x = dot( normalWorld[ 0 ].xyz, i.normal );
	n.y = dot( normalWorld[ 1 ].xyz, i.normal );
	n.z = dot( normalWorld[ 2 ].xyz, i.normal );
	
	/*o.normal.x = dot( gWorldMatrix[ 0 ].xyz, o.normal );*/
	/*o.normal.y = dot( gWorldMatrix[ 1 ].xyz, o.normal );*/
	/*o.normal.z = dot( gWorldMatrix[ 2 ].xyz, o.normal );*/
	
	o.normal.x = dot( gInvTransposedWorldMatrix[ 0 ].xyz , n );
	o.normal.y = dot( gInvTransposedWorldMatrix[ 1 ].xyz , n );
	o.normal.z = dot( gInvTransposedWorldMatrix[ 2 ].xyz , n );
	
	/*o.normal.x = dot( gInvTransposedWorldMatrix[ 0 ].xyz , i.normal );*/
	/*o.normal.y = dot( gInvTransposedWorldMatrix[ 1 ].xyz , i.normal );*/
	/*o.normal.z = dot( gInvTransposedWorldMatrix[ 2 ].xyz , i.normal );*/

	
	o.normal = normalize(o.normal);

#ifdef LINEAR_ZBUFFER
	o.screenPosition.z *= o.screenPosition.w;
#endif
	o.color = i.color.zyxw * gDiffuseColor / 255.0;
	o.texCoord = i.tex0;
	return o;
}

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
	float3 position : TEXCOORD1;
	float3 normal : TEXCOORD2;
};

float4 mainPS( FromVertex input ) : COLOR {
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
}

technique main
{
	pass p0
	{
		VertexShader = compile vs_2_0 mainVS();
		PixelShader = compile ps_2_0 mainPS();
	}
}

