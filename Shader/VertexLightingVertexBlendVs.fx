float4 gTransform[ 4 ] : register( c0 );
float4 gWorldMatrix[ 3 ] : register( c4 );
float4 gInvTransposedWorldMatrix[ 3 ] : register( c7 );
float4 gDiffuseColor : register( c10 );
float3 gAmbient : register( c11 );
float4 gLightPosX : register( c12 );
float4 gLightPosY : register( c13 );
float4 gLightPosZ : register( c14 );
float3 gLightColor0 : register( c15 );
float3 gLightColor1 : register( c16 );
float3 gLightColor2 : register( c17 );
float3 gLightColor3 : register( c18 );
static const int MAX_MATRICES = 32;
bool gIsVertexBlend : register(c19);
float4 gWorldMatrixArray[MAX_MATRICES*3] : register( c20 );

struct ToPixel{
	float4 screenPosition : POSITION;
	float4 color : COLOR0; //頂点カラー
	float2 texCoord : TEXCOORD0; //テクスチャ座標
};

struct VsInput{
	float4			pos             : POSITION;
	float4			blendWeights    : BLENDWEIGHT;
	int4				blendIndices    : BLENDINDICES;
	float3			normal          : NORMAL;
	float2			tex0            : TEXCOORD0;
	float4			color			: COLOR0;
};
ToPixel main( VsInput i ){
	ToPixel o;
	float4 worldPos;
	float4 world[3] = {
		{ 0.0, 0.0, 0.0, 0.0, },
		{ 0.0, 0.0, 0.0, 0.0, },
		{ 0.0, 0.0, 0.0, 0.0, } };
	//int imax = min(NumBones, 4);
	// calculate the pos/normal using the "normal" weights 
	//        and accumulate the weights to calculate the last weight
	for (int iBone = 0; iBone<2; iBone++){
		if( i.blendIndices[iBone]==255 ){
			break;
		}
		world[0] += gWorldMatrixArray[i.blendIndices[iBone]*3+0]  * i.blendWeights[iBone];
		world[1] += gWorldMatrixArray[i.blendIndices[iBone]*3+1]  * i.blendWeights[iBone];
		world[2] += gWorldMatrixArray[i.blendIndices[iBone]*3+2]  * i.blendWeights[iBone];
	}
	worldPos.x = dot( world[ 0 ], i.pos );
	worldPos.y = dot( world[ 1 ], i.pos );
	worldPos.z = dot( world[ 2 ], i.pos );
	worldPos.w = 1.0;
	
	o.screenPosition.x = dot( gTransform[ 0 ], worldPos );
	o.screenPosition.y = dot( gTransform[ 1 ], worldPos );
	o.screenPosition.z = dot( gTransform[ 2 ], worldPos );
	o.screenPosition.w = dot( gTransform[ 3 ], worldPos );

	float3 wp; //ワールド位置
	wp.x = worldPos.x;
	wp.y = worldPos.y;
	wp.z = worldPos.z;

	float3 wn; //ワールド法線
	wn.x = dot( world[ 0 ].xyz, i.normal );
	wn.y = dot( world[ 1 ].xyz, i.normal );
	wn.z = dot( world[ 2 ].xyz, i.normal );
#ifdef LINEAR_ZBUFFER
	o.screenPosition.z *= o.screenPosition.w;
#endif

	float4 lvX, lvY, lvZ;
	lvX = gLightPosX - wp.xxxx;
	lvY = gLightPosY - wp.yyyy;
	lvZ = gLightPosZ - wp.zzzz;
	float4 lvL;
	lvL = lvX * lvX;
	lvL += lvY * lvY;
	lvL += lvZ * lvZ;
	lvL += 0.00001; //0割り防止
	float4 d = lvX * wn.xxxx;
	d += lvY * wn.yyyy;
	d += lvZ * wn.zzzz;
	d /= lvL;
	d = max( ( float4 )0, d ); //マイナスは0。
	float3 c;
	c = gAmbient.xyz;
	c += gLightColor0 * d.x;
	c += gLightColor1 * d.y;
	c += gLightColor2 * d.z;
	c += gLightColor3 * d.w;
	i.color /= 255.0; //UBYTE4 -> UBYTE4N
	o.color.xyz = c * i.color.zyx * gDiffuseColor.xyz; //RGB入れ替え
	o.color.w = i.color.w * gDiffuseColor.w; //頂点アルファも乗算
	o.texCoord = i.tex0;
	return o;
}

