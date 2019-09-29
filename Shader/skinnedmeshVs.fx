
static const int MAX_MATRICES = 12;
float4x4    mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
int			mIndicesTable[12];
float4x4    mViewProj : VIEWPROJECTION;
int NumUsedBones = 2;

struct VS_INPUT
{
    float4			Pos             : POSITION;
    float4			BlendWeights    : BLENDWEIGHT;
    int4			BlendIndices    : BLENDINDICES;
    float3			Normal          : NORMAL;
    float3			Tex0            : TEXCOORD0;
	float4			Color			: COLOR0;
};


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


//ピクセルに情報をおくるだけのVertexシェーダ
ToPixel VS_main( VS_INPUT i){
	ToPixel o;
	float3      Pos = 0.0f;
    float3      Normal = 0.0f;    

    // cast the vectors to arrays for use in the for loop below
   // float BlendWeightsArray[4] = (float[4])i.BlendWeights;
    //int   IndexArray[4]        = (int[4])IndexVector;
    
	float4x4 world= {
						0.0, 0.0, 0.0, 0.0,
						0.0, 0.0, 0.0, 0.0,
						0.0, 0.0, 0.0, 0.0,
						0.0, 0.0, 0.0, 0.0  };
	//int imax = min(NumBones, 4);
    // calculate the pos/normal using the "normal" weights 
    //        and accumulate the weights to calculate the last weight
    for (int iBone = 0; iBone < 2; iBone++)
    {
		if( i.BlendIndices[iBone]==255 ){
			break;
		}
		//cpuで実装すべきか？
		for( int j = 0; j < 12; j++){
			if( i.BlendIndices[iBone]==mIndicesTable[j] ){
				world += mWorldMatrixArray[j]  * i.BlendWeights[iBone];
				break;
			}
		}
	}

	Pos = mul( i.Pos , world );
    Normal = mul( float4(i.Normal.xyz, 0.0), world );	
	
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