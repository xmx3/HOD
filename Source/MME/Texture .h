#pragma once
#include<d3dx9.h>
#include"formats.h"
#include<string>
#include<memory>
#include<vector>


namespace MME{
class Texture;
typedef std::shared_ptr<Texture> TextureSharedPtr;
class Texture {
public:
	static TextureSharedPtr create( ID3DXEffect *effect, D3DXHANDLE hTex, const std::string &path );
	static void clearCache();
	static void shrinkToFitCache();

	~Texture();

	bool isError()const;

	void send(ID3DXEffect *effect);
	const std::string & getName()const;
private:
	Texture( ID3DXEffect *effect, D3DXHANDLE hTex, const std::string &path );
	Texture( const Texture &src, ID3DXEffect *effect, D3DXHANDLE hTex, const std::string &path );

	std::string mName;
	D3DXHANDLE mHandle;
	std::shared_ptr<IDirect3DTexture9> mTexture;

	static std::vector< std::weak_ptr<Texture> > sCache;

};


} // end namespace
