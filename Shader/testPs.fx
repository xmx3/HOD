sampler2D gSampler : register( s0 );

struct FromVertex{
	float4 color : COLOR0; //í∏ì_ÉJÉâÅ[
	float2 texCoord : TEXCOORD0;
	float3 position : TEXCOORD1;
	float3 normal : TEXCOORD2;
};

float4 PS_main( FromVertex input ) : COLOR {
	float4 c = input.color * tex2D( gSampler, input.texCoord );
	return c;
}
