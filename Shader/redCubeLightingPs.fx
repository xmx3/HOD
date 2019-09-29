//ピクセルに情報をおくるだけのシェーダ
float4 gTransform[ 4 ] : register( c0 );
float4 gWorldMatrix[ 3 ] : register( c4 );
float4 gInvTransposedWorldMatrix[ 3 ] : register( c7 );
float4 gDiffuseColor : register( c10 );

struct ToPixel{
	float4 screenPosition : POSITION;
	float4 color : COLOR0; //頂点カラー
	float2 texCoord : TEXCOORD0; //テクスチャ座標
	float3 position : TEXCOORD1; //ローカル座標位置
	float3 normal : TEXCOORD2; //ローカル座標法線
};

ToPixel mainVS( 
float4 aPosition : POSITION0,
float3 aNormal : NORMAL0,
float4 aColor : COLOR0,
float2 aTexCoord : TEXCOORD0 ){
	ToPixel o;
	o.screenPosition.x = dot( gTransform[ 0 ], aPosition );
	o.screenPosition.y = dot( gTransform[ 1 ], aPosition );
	o.screenPosition.z = dot( gTransform[ 2 ], aPosition );
	o.screenPosition.w = dot( gTransform[ 3 ], aPosition );
	float3 wp; //ワールド位置
	wp.x = dot( gWorldMatrix[ 0 ], aPosition );
	wp.y = dot( gWorldMatrix[ 1 ], aPosition );
	wp.z = dot( gWorldMatrix[ 2 ], aPosition );
	float3 wn; //ワールド法線
	wn.x = dot( gInvTransposedWorldMatrix[ 0 ].xyz, aNormal );
	wn.y = dot( gInvTransposedWorldMatrix[ 1 ].xyz, aNormal );
	wn.z = dot( gInvTransposedWorldMatrix[ 2 ].xyz, aNormal );
#ifdef LINEAR_ZBUFFER
	o.screenPosition.z *= o.screenPosition.w;
#endif
	o.color = aColor.zyxw * gDiffuseColor / 255.0;
	
	o.texCoord = aTexCoord;
	o.position = wp;
	o.normal = wn;
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

float4 gray(float4 c){
	return float4( c.xyz*0.5, c.w );
}

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
	return gray(c);
}

technique main
{
	pass p0
	{
		VertexShader = compile vs_2_0 mainVS();
		PixelShader = compile ps_2_0 mainPS();
	}
}
