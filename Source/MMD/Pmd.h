#ifndef __PMD_H__
#define __PMD_H__
#include <d3dx9.h>

//最適化(パッティング)を防ぐ
#pragma pack( push, 1 )

namespace MMD {

	struct PMD_HEADER
	{
		char magic[3];//Pmd
		float version;
		char name[20]; // モデル名．0x00 終端，余白は 0xFD で埋める．
		char comment[256]; // コメント (著作権表示など)，0x00 終端，余白は 0xFD で埋める．
	};
	struct DIFFUSE { float r, g, b, a; };
	struct SPECULAR { float r, g, b; };
	struct AMBIENT { float r, g, b; };


	struct PMD_VERTEX
	{
		// 次の部分は MMD2 と同じ．Direct3D の D3DVERTEX 型．
		float x, y, z;// 座標
		float nx, ny, nz;// 単位法線ベクトル
		float u, v;// テクスチャ座標
		// 次の部分は PMD で追加された，ジオメトリ・ブレンディング用データ．
		// (MMD2 では *.osm 内にあった．)
		unsigned short bone[2];// ボーン番号
		unsigned char weight;// ブレンドの重み (0 ～ 100％)
		unsigned char	cbEdge;			// エッジフラグ
	};

	struct PMD_MATERIAL
	{
		DIFFUSE diffuse;
		float shininess;
		SPECULAR specular;
		AMBIENT ambient;
		unsigned char toonIndex;
		unsigned char edgeFlag;//輪郭、影
		unsigned long nEdges;// この材質に対応するエッジ数
		char textureFileName[20];// テクスチャファイル名 (MMD2 では 256 バイト)
	};

	struct PMD_BONE
	{
		char name[20]; // ボーン名 (0x00 終端，余白は 0xFD)
		short parent; // 親ボーン番号 (なければ -1)
		//std::vector<short> childrenIndexs;//子があれば子の配列番号
		unsigned short to;
		unsigned char kind;
		unsigned short ikTarget;
		float x, y, z;
	};

	struct PMD_IK
	{
		unsigned short index;
		unsigned short target;
		unsigned char effectBoneNum;
		unsigned short calcNum;
		float weight;
		unsigned short *pEffectBoneIndeces;
	};

	//表情の頂点データ
	struct PMD_FACE_VERTEX
	{
		unsigned long index;//影響する頂点インデックス
		float x, y, z;
	};

	struct PMD_FACE
	{
		char name[20];		// 表情名 (0x00 終端，余白は 0xFD)

		unsigned long nVertices;	// 表情頂点数
		unsigned char type;			// 分類

		PMD_FACE_VERTEX* pVertices;	// 表情頂点データ
	};
	// 剛体データ
	struct PMD_RigidBody
	{
		char			szName[20];		// 剛体名

		unsigned short	unBoneIndex;	// 関連ボーン番号
		unsigned char	cbColGroupIndex;// 衝突グループ
		unsigned short	unColGroupMask;	// 衝突グループマスク

		unsigned char	cbShapeType;	// 形状  0:球 1:箱 2:カプセル

		float			fWidth;			// 半径(幅)
		float			fHeight;		// 高さ
		float			fDepth;			// 奥行

		float			vec3Position[3];	// 位置(ボーン相対)
		float			vec3Rotation[3];	// 回転(radian)

		float			fMass;			// 質量
		float			fLinearDamping;	// 移動減
		float			fAngularDamping;// 回転減
		float			fRestitution;	// 反発力
		float			fFriction;		// 摩擦力

		unsigned char	cbRigidBodyType;// タイプ 0:Bone追従 1:物理演算 2:物理演算(Bone位置合せ)
	};

	// コンストレイント(ジョイント)データ
	struct PMD_Constraint
	{
		char			szName[20];		// コンストレイント名

		unsigned long	ulRigidA;		// 剛体A
		unsigned long	ulRigidB;		// 剛体B

		float			vec3Position[3];	// 位置(モデル原点中心)
		float			vec3Rotation[3];	// 回転(radian)

		float			vec3PosLimitL[3];	// 移動制限1
		float			vec3PosLimitU[3];	// 移動制限2

		float			vec3RotLimitL[3];	// 回転制限1
		float			vec3RotLimitU[3];	// 回転制限2

		float			vec3SpringPos[3];	// ばね移動
		float			vec3SpringRot[3];	// ばね回転
	};
}
#pragma pack( pop )

#endif