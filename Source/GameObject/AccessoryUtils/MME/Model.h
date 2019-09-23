#pragma once
#include<vector>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/IndexBuffer.h>
#include"MME/Object/IObject.h"
#include<memory>
#include<boost/flyweight/flyweight_fwd.hpp>
#include<boost/flyweight/key_value_fwd.hpp>
#include<string>

namespace XFile{
	class Model;
}

struct D3DXMATRIX;

namespace GameLib{
	namespace Scene {
		class Batch;
	}
	namespace Math {
		class Matrix34;
	}
}

class btTransform;

namespace GameObject {
	class Accessory;
namespace AccessoryUtils {

namespace MME {
class Model;
typedef std::shared_ptr<Model>  ModelSharedPtr;

//MMEで描画するためのモデル
class Model : public ::MME::Object::IObject {
public:
	typedef boost::flyweights::flyweight<
		boost::flyweights::key_value<std::string, XFile::Model >
	> FlyWeightModel;
	static ModelSharedPtr create( const FlyWeightModel &model, float scale );
	virtual ~Model();

	void setScale( float s );
	virtual float getScale()const;
	
	bool isFinished();
	bool isError()const;

	GameLib::Graphics::VertexBuffer getVertexBuffer();
	GameLib::Graphics::IndexBuffer getIndexBuffer();

	virtual void draw() const;
	void drawUsingGameLib()const;

	//描画姿勢をボーンに一致させる
	//controlObjectSelfで使うmTransformを更新
	//呼ぶタイミングがシビアなので気をつけること
	//物理更新後、ボーンを更新した後呼ぶこと
	//名前preDrawMME()のほうがいいか？
	void fitTransformToBone();

	virtual float getFaceValue(const std::string &faceName )const;

	virtual const D3DXMATRIX & getBoneMatrix( const std::string &boneName )const;

	virtual const std::string& getModelFileName()const;
	
	void setAccessory( Accessory* a ){
		mAccessory = a;
	}
private:
	
	//friendのみ作成できる
	explicit Model( const FlyWeightModel &model, float scale );
	//disallow
	void operator=( const Model & );
	//disallow
	Model( const Model & );

	Accessory *mAccessory;//姿勢がBone追従かそうでないかで異なってくる
	FlyWeightModel *mModel;
	float mScale;
};
}//end namespace MME
}//end namespace AccessoryUtils
}//end namespace GameObject
