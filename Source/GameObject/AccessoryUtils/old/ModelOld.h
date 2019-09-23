#pragma once
#include<vector>
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/IndexBuffer.h>


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
namespace AccessoryUtils {

	struct Impl;

class Model {
public:
	explicit Model(const std::string &xFileName );
	~Model();

	void setScale( float s );
	float getScale() const;
	bool isFinished()const;
	bool isError()const;

	GameLib::Graphics::VertexBuffer getVertexBuffer();
	GameLib::Graphics::IndexBuffer getIndexBuffer();

	void draw( const GameLib::Math::Matrix34 &w34 ) const;
	void drawByMME( const D3DXMATRIX &world )const;
	const std::string& getFileName()const;
	
private:
	void operator=( const Model & );
	Model( const Model & );
	
	Impl *mImpl;
	float mScale;
};
}//end namespace AccessoryUtils
}//end namespace GameObject
