// CodeZine MME連載サンプル
// ラインエフェクト
// 制作：ビームマンP

//複製回数
int CloneNum = 8;
int index;


//ターゲットオブジェクトから座標を取得
float TargetPos2 : CONTROLOBJECT < string name = "Target.x"; >;

//自分のSi値を取得
float Scale : CONTROLOBJECT < string name = "Line.x"; string item = "Si"; >;
//自分のTr値を取得
float Alpha : CONTROLOBJECT < string name = "Line.x"; string item = "Tr"; >;

//時間
float time : TIME;

//使用するテクスチャ
texture Line_Tex
<
   string ResourceName = "Tex.png";
>;
//テクスチャサンプラ
sampler LineTexSampler = sampler_state
{
   //使用するテクスチャ
   Texture = (Line_Tex);
   //テクスチャ範囲0.0～1.0をオーバーした際の処理
   //WRAP:ループ
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
   //テクスチャフィルター
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
   MIPFILTER = NONE;
};
#define RND_SIZE 128.0
//ランダムテクスチャ
texture2D RndTex <
    string ResourceName = "RndTex.bmp";
>;
//ランダムテクスチャサンプラ
sampler RndSampler = sampler_state {
    texture = <RndTex>;
};
// 座法変換行列
float4x4 ViewProjMatrix      : VIEWPROJECTION;
float4x4 WorldMatrix      : WORLD;

float3   CameraPosition    : POSITION  < string Object = "Camera"; >;

//エルミート補完関数
float3 HermiteLerp(float3 s,float3 e,float3 svec,float3 evec,float t)
{
	return (((t-1)*(t-1))*(2*t+1)*s) + ((t*t)*(3-2*t)*e) +((1-(t*t))*t*svec) + ((t-1)*(t*t)*evec);
}

struct VS_OUTPUT
{
    float4 Pos        : POSITION;    // 射影変換座標
    float2 Tex        : TEXCOORD1;   // テクスチャ
};
// 頂点シェーダ
VS_OUTPUT Line_VS(float4 Pos : POSITION, float2 Tex : TEXCOORD0)
{
	float3 TargetPos = TargetPos2;
	//インデックス番号を元に乱数テクスチャから色取得
	float4 RndCol_Start = (tex2Dlod(RndSampler,float4(index/RND_SIZE,0,0,0))-0.5)*2;
	float4 RndCol_End = (tex2Dlod(RndSampler,float4((index*2)/RND_SIZE,0,0,0))-0.5)*2;
	

	//エルミート曲線用始点ベクトル
	float3 StartVec = RndCol_Start.xyz * 16;
	//エルミート曲線用終点ベクトル
	float3 EndVec = RndCol_End.xyz * 32;
	
    VS_OUTPUT Out = (VS_OUTPUT)0;
    
    //出力用座標
    float4 LastPos = 1;
    
    //---現在の座標取得---//
    //ワールド行列の4行目からワールド座標を取得
	float3 ZeroPos = WorldMatrix[3].xyz;
	
    //原点と目標点の間を線形補間で座標を取得
    //補間用係数はモデルのZ座標
    //float3 NowPos = lerp(ZeroPos,TargetPos,Pos.z);
    float3 NowPos = HermiteLerp(ZeroPos,TargetPos,StartVec,EndVec,Pos.z);
    
    //出力用座標に保存
    LastPos.xyz = NowPos;
    
    
    //---ビルボード計算---//

    //現在座標から少しだけ先に進めた座標を取得
    //float3 NextPos = lerp(ZeroPos,TargetPos,Pos.z+0.01);
	float3 NextPos = HermiteLerp(ZeroPos,TargetPos,StartVec,EndVec,Pos.z+0.01);
	
    //カメラからの視線ベクトルを計算する
    float3 EyeVec = normalize(CameraPosition - NowPos);
    
    //現在の座標から先の座標から正面方向のベクトルを得る
    float3 FrontVec = normalize(NextPos - NowPos);
    
    //正面ベクトルと視線ベクトルの外積からサイドベクトルを得る
    float3 SideVec = cross(FrontVec,EyeVec);
    // float3 SideVec = cross(FrontVec,EyeVec) * Scale * 0.1;
    
    //現在処理している頂点を左右に割り振る
    //全ての頂点のX座標は0.5もしくは-0.5
    if(Pos.x > 0)
    {
    	LastPos.xyz += SideVec;
    }else{
    	LastPos.xyz += -SideVec;
    }
    
    
    // カメラ視点ビュー射影変換
    Out.Pos = mul( LastPos, ViewProjMatrix );
    
    // テクスチャ座標
    Tex.y += time; 
    Out.Tex = Tex;
    
    return Out;
}
// ピクセルシェーダ
float4 Line_PS( VS_OUTPUT IN ) : COLOR0
{
	//出力用カラー
	float4 Color;
	
	//テクスチャから色を取得
	Color = tex2D(LineTexSampler,IN.Tex);
    return Color;
}

// オブジェクト描画用テクニック
technique MainTec < string MMDPass = "object"; 
    string Script = 
		"LoopByCount=CloneNum;"
        "LoopGetIndex=index;"
	    "Pass=DrawObject;"
        "LoopEnd=;"
    ;
> {
    pass DrawObject
    {
		ZENABLE = TRUE;
		ZWRITEENABLE = FALSE;
		CULLMODE = NONE;
		ALPHABLENDENABLE = TRUE;
		SRCBLEND=SRCALPHA;
		DESTBLEND=ONE;
        VertexShader = compile vs_3_0 Line_VS();
        PixelShader  = compile ps_3_0 Line_PS();
    }
}
