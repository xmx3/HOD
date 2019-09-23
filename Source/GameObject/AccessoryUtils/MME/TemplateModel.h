#pragma once
#include<vector>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/IndexBuffer.h>
#include<memory>

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
//XFile::Model??だけ欲しいだけなんだが???!!!だろ
//XFile::Modelのラッパーなんだと思うがすごい気持ち悪い
//std::shared_ptr<XFile::Model>がほしいのでこのクラスを作成した
//XFile::Model*だと管理しにくいし、共有しにくいので
//XFile::Model + scale = GameObject::AccessoryUtils::MME::Model
class TemplateModel {
public:
	explicit TemplateModel(const std::string &xFileName );
	virtual ~TemplateModel();

	bool isFinished()const;
	bool isError()const;

	GameLib::Graphics::VertexBuffer getVertexBuffer()const;
	GameLib::Graphics::IndexBuffer getIndexBuffer()const;

	const std::string& getModelFileName()const;

	std::shared_ptr<Model> createModel(float scale)const;

private:
	void operator=( const TemplateModel & );
	TemplateModel( const TemplateModel & );
	std::shared_ptr<XFile::Model> mModel;
};
}//end namespace MME
}//end namespace AccessoryUtils
}//end namespace GameObject
