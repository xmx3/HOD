float4 gTransform[ 4 ] : register( c0 );
float4 gDiffuseColor : register( c10 );
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
ToPixel mainVS( VsInput i ){
	ToPixel o;
	o.screenPosition.x = dot( gTransform[ 0 ], i.pos );
	o.screenPosition.y = dot( gTransform[ 1 ], i.pos );
	o.screenPosition.z = dot( gTransform[ 2 ], i.pos );
	o.screenPosition.w = dot( gTransform[ 3 ], i.pos );
#ifdef LINEAR_ZBUFFER
	o.screenPosition.z *= o.screenPosition.w;
#endif
	o.color.xyzw = i.color.zyxw * gDiffuseColor / 255.0; //BGRAで来るので順番変更。加えてUBYTE4なので255で割って正規化
	o.texCoord = i.tex0;
	return o;
}

sampler2D gSampler : register( s0 );
float4 mainPS( ToPixel input ) : COLOR {
	float4 c = input.color * tex2D( gSampler, input.texCoord );
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

