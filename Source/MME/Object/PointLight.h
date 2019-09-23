#pragma once
#include"IObject.h"
#include"XFile/Model.h"
#include<memory>

namespace GameLib{ namespace FileIO{
	class InFile;
} }

namespace XFile{
	class Model;
}

namespace MME{
	class PostEffect;
	typedef std::shared_ptr<PostEffect> PostEffectSharedPtr;
	namespace Object{
		class PointLight;
		typedef std::shared_ptr<PointLight> PointLightSharedPtr;
class PointLight : public IObject{
public:
	//make_sharedがprivate　コンストラクタ呼ぶのに必要
	friend class std::_Ref_count_obj<PointLight>;
	static PointLightSharedPtr create(  const D3DXVECTOR3 &pos, float range, const D3DXVECTOR4 &color = D3DXVECTOR4( 1.f, 1.f, 1.f, 1.f ) );
	static bool isReady();
	static void destroy();

	~PointLight();

	void draw()const;

	float getFaceValue(const std::string &faceName )const;

	const D3DXMATRIX & getBoneMatrix( const std::string &boneName )const;

	float getScale()const;

	const std::string& getModelFileName()const;
private:
	// use create
	PointLight( const D3DXVECTOR3 &pos, float range, const D3DXVECTOR4 &color = D3DXVECTOR4( 1.f, 1.f, 1.f, 1.f ) );
	//disallow assign
	PointLight( const PointLight & );
	//disallow copy
	void operator=( const PointLight & );
	D3DXVECTOR4 mPos;
	D3DXVECTOR4 mRange;
	D3DXVECTOR4 mColor;
	D3DXVECTOR4 mShadowParam;



	static GameLib::FileIO::InFile *msFile;
	static std::unique_ptr<XFile::Model> msModel;
	static MME::PostEffectSharedPtr msEffect;
	static bool msIsReady;
	static D3DXHANDLE msLightColorHandle;
	static D3DXHANDLE msLightPositionHandle;
	static D3DXHANDLE msLightRangeHandle;
	static D3DXHANDLE msShadowParamsHandle;


};
}//end namespace Object
}// end namespace MME