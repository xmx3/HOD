#include"Model.h"
#include"XFile/Model.h"

namespace GameObject {
namespace AccessoryUtils {


Model::Model( const std::string &xFileName )
	:mScale(1.0)
{
	mImpl=new Impl( xFileName );
}

Model::~Model(){
	delete mImpl;
	mImpl=0;
}

void Model::setScale( float s ){
	mScale = s;
}

float Model::getScale() const{
	return mScale;
}

bool Model::isFinished()const{
	return mImpl->isFinished();
}
bool Model::isError()const{
	return mImpl->isError();
}

GameLib::Graphics::VertexBuffer Model::getVertexBuffer(){
	return mImpl->getVertexBuffer();
}
GameLib::Graphics::IndexBuffer Model::getIndexBuffer(){
	return mImpl->getIndexBuffer();
}

void Model::draw( const GameLib::Math::Matrix34 &w34 ) const {
	mImpl->draw( w34 );
}
void Model::drawByMME( const D3DXMATRIX &world ) const {
	mImpl->drawByMME( world );
}

const std::string & Model::getFileName()const{
	return mImpl->getFileName();
}

}//end namespace AccessoryUtils
}//end namespace GameObject
