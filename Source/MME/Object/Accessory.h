#pragma once
#include"IObject.h"
#include"MME/Manager.h"
#include"XFile/Model.h"
#include<GameLib/FileIO/Manager.h>
#include<GameLib/FileIO/InFile.h>
#include<GameLib/Math/Matrix34.h>
#include"SegaTypeHelper.h"
#include<memory>
#include <boost/filesystem.hpp>

namespace MME{
	namespace Object{
class Accessory;
typedef std::shared_ptr<Accessory> AccessorySharedPtr;
//テスト的なもの
class Accessory : public IObject {
public:
	friend class std::_Ref_count_obj<Accessory>;
	
	static AccessorySharedPtr create(){
		AccessorySharedPtr r = std::make_shared<Accessory>();
		return r;
	}

	void init( const char *fileName, float scale=1.f, const char *effectFullPath=NULL  )
	{
		mScale = scale;
		if(mModel){
			assert(false);
			return;
		}

		mModel =  std::make_shared<XFile::Model>( fileName );

		if(effectFullPath==NULL){
			//同じフォルダに "モデル名.fx" がないか探す
			//あった場合は、そのfxファイルを使用
			//なかった場合はデフォルトを使用
			const std::string& file = getModelFileName();

			int pos = file.rfind('.');
			assert( pos != std::string::npos && ". dosen't exsist!");

			std::string fxFileName( file, 0, pos+1 );
			fxFileName.append( "fx" );
			//file exist?
			namespace fs = boost::filesystem;
			const fs::path path(fxFileName);

			boost::system::error_code error;
			const bool result = fs::exists(path, error);
			//file dont exist.
			if (!result || error) {	
				return;
			}
			else{
				assert( false && "not impl" );
				//MME::Manager::instance()->addToStandardEfffect( shared_from_this(), fxFileName.c_str() );
				return;
			}
		} else {
			assert( false && "not impl" );
			//MME::Manager::instance()->addToStandardEfffect( shared_from_this(), effectFullPath );
		}

	}

	virtual ~Accessory(){}

	virtual float getFaceValue(const std::string &faceName )const
	{
		return 0.0;
	}
	virtual float getScale()const{
		return mScale;
	}


	virtual const D3DXMATRIX & getBoneMatrix( const std::string &boneName )const
	{
		static const D3DXMATRIX matI( 
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
			);
		return matI;
	}

	virtual const std::string& getModelFileName()const{
		return mModel->getFileName();
	}

	virtual void draw()const{
		MME::Manager * m = MME::Manager::instance();
		MMDPass pass;
		UseTexture tex;
		UseSphereMap sphere;
		UseToon toon;
		UseSelfShadow selfShadow;

		m->getCurrentPass( &pass, &tex, &sphere, &toon, &selfShadow );

		//XfileにはtoonとsphereMapはないので、無視
		if(  toon || sphere  ){
			return;
		}
		if( mCanDraw && mCanDrawMMDPass[pass] ) {
			D3DXMATRIX m = mTransform;
			m._11 *= mScale;
			m._22 *= mScale;
			m._33 *= mScale;
			mModel->drawByMME(m);
		}
	}

	void drawUsingGameLib()const{
		D3DXMATRIX m = mTransform;
		m._11 *= mScale;
		m._22 *= mScale;
		m._33 *= mScale;
		mModel->draw(toMatrix34(m));
	}


	void setTransform( const D3DXMATRIX & trans ){
		mTransform = trans;
	}

	bool isReady(){
		return mModel->isFinished();
	}

	GameLib::Graphics::VertexBuffer getVertexBuffer(){
		return mModel->getVertexBuffer();
	}

	GameLib::Graphics::IndexBuffer getIndexBuffer(){
		return mModel->getIndexBuffer();
	}

protected:
	std::shared_ptr<XFile::Model> mModel;
private:
	//shared_from_this()を使っているのでスマポ使わないとだめ
	Accessory()
		:mModel(NULL),
		mScale(1.f)
	{
		mCanDrawMMDPass[MME::MP_EDGE]=false;
	}
	//disallow assign
	Accessory(const Accessory& );
	//disallow copy
	void operator=(const Accessory& );
	float mScale;
};

}// end namespace Object
}// end namespace MME