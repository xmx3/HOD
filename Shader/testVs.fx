float4 gTransform[ 4 ] : register( c0 );
float4 gWorldMatrix[ 3 ] : register( c4 );
float4 gInvTransposedWorldMatrix[ 3 ] : register( c7 );
float4 gDiffuseColor : register( c10 );
static const int MAX_MATRICES = 32;
bool gIsVertexBlend : register(c11);
float4    mWorldMatrixArray[MAX_MATRICES*3] : register( c12 );

int NumUsedBones = 2;

struct VS_INPUT
{
    float4			Pos             : POSITION;
    float4			BlendWeights    : BLENDWEIGHT;
    int4			BlendIndices    : BLENDINDICES;
    float3			Normal          : NORMAL;
    float2			Tex0            : TEXCOORD0;
	float4			Color			: COLOR0;
};

struct ToPixel{
	float4 screenPosition : POSITION;
	float4 color : COLOR0; //頂点カラー
	float2 texCoord : TEXCOORD0; //テクスチャ座標
	float3 position : TEXCOORD1; //ローカル座標位置
	float3 normal : TEXCOORD2; //ローカル座標法線
};


ToPixel VS_main( VS_INPUT i){
	ToPixel o;
	float3      Pos = 0.0f;
    float3      Normal = 0.0f;    

    
	
	// Compensate for lack of UBYTE4 on Geforce3
    //int4 IndexVector = D3DCOLORtoUBYTE4(i.BlendIndices);
    // cast the vectors to arrays for use in the for loop below
    //int BlendIndices[4] = (int[4])IndexVector;

	float4 world[3] = {
						{ 0.0, 0.0, 0.0, 0.0, },
						{ 0.0, 0.0, 0.0, 0.0, },
						{ 0.0, 0.0, 0.0, 0.0, } };
	//int imax = min(NumBones, 4);
    // calculate the pos/normal using the "normal" weights 
    //        and accumulate the weights to calculate the last weight
    for (int iBone = 0; iBone<4; iBone++)
    {
		if( i.BlendIndices[iBone]==255 ){
			break;
		}
		world[0] += mWorldMatrixArray[i.BlendIndices[iBone]*3+0]  * i.BlendWeights[iBone];
		world[1] += mWorldMatrixArray[i.BlendIndices[iBone]*3+1]  * i.BlendWeights[iBone];
		world[2] += mWorldMatrixArray[i.BlendIndices[iBone]*3+2]  * i.BlendWeights[iBone];
		
	}

	Pos.x = dot( world[0], i.Pos );
	Pos.y = dot( world[1], i.Pos );
	Pos.z = dot( world[2], i.Pos );
	
	Normal.x = dot( (float3)world[0], i.Normal );
	Normal.y = dot( (float3)world[1], i.Normal );
	Normal.z = dot( (float3)world[2], i.Normal ); 
	
	// normalize normals
	Normal = normalize(Normal);

	//o.screenPosition.x = dot( mViewProj[0], float4(Pos.xyz, 1.f) );
	//o.screenPosition.y = dot( mViewProj[1], float4(Pos.xyz, 1.f) );
	//o.screenPosition.z = dot( mViewProj[2], float4(Pos.xyz, 1.f) );
	//o.screenPosition.w = dot( mViewProj[3], float4(Pos.xyz, 1.f) );

	//o.screenPosition = mul( mViewProj, float4(Pos.xyz, 1.f) );
	//o.screenPosition = mul( float4(Pos.xyz, 1.f) , mViewProj );
	
	o.screenPosition.x = dot( gTransform[0], float4(Pos.xyz, 1.f) );
	o.screenPosition.y = dot( gTransform[1], float4(Pos.xyz, 1.f) );
	o.screenPosition.z = dot( gTransform[2], float4(Pos.xyz, 1.f) );
	o.screenPosition.w = dot( gTransform[3], float4(Pos.xyz, 1.f) );
	
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
