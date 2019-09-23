#ifndef __FIREEFFECT_H__
#define __FIREEFFECT_H__
#include<d3dx9.h>
#include<GameLib/GameLib.h>
#include<GameLib/Graphics/Manager.h>
#include<GameLib/Graphics/Texture.h>
#include<assert.h>
#include<tchar.h>
#include<list>
#include<ctime>
#include<GameLib/Math/Random.h>

#include"MMD/MMDMacro.h"
#include"shader/convertXFileFormat.h"
#include<boost/smart_ptr.hpp>

#include<GameLib/FileIO/InFile.h>


using namespace GameLib::Math;
using namespace GameLib::Graphics;

//class EffectManager{};
//class IEffect{};
//class CFire : public IActor{
class CFire{
public:
	CFire(
			const D3DXVECTOR3 &pos,
			const D3DXVECTOR3 &scale
		):mPos(pos),
		mScale(scale),
		//mTime(time),
		mParticleSystemShape(1.f),
		mParticleSpread(20.f),
		mParticleSpeed(0.48f),
		mParticleSystemHeight(80.f),
		mParticleSize(7.8f),
		mIsEnable(true)
	{
		Random rand = Random::create( static_cast<int>(std::time(NULL)) );
		mTime = rand.getFloat( 0, 100 );
		mEndTime = mTime + rand.getFloat( 20.f, 50.f ); 
	}
	~CFire(){}
	void update( float elapsedTime ){
		mTime += elapsedTime;
		if( mTime > mEndTime ){
			mIsEnable=false;
		}
	}
	void setParam(
			ID3DXEffect *pEffect,			
			const D3DXMATRIX &view,
			const D3DXMATRIX &projection
			)
	{
		D3DXMATRIX world;
		D3DXMatrixTranslation( &world, mPos.x, mPos.y, mPos.z );
		world._11 = mScale.x;
		world._22 = mScale.y;
		world._33 = mScale.z;
		HRESULT hr;
		D3DXMATRIX temp = world*view;
		hr=pEffect->SetMatrixTranspose("world_view_trans_matrix", &temp );
		assert( SUCCEEDED( hr ) );
		temp *= projection;
		hr=pEffect->SetMatrix( "world_view_proj_matrix", &temp );
		assert( SUCCEEDED( hr ) );
		hr=pEffect->SetFloat( "time_0_X", mTime );
		assert( SUCCEEDED( hr ) );
		hr=pEffect->SetFloat( "particleSystemShape", mParticleSystemShape );
		assert( SUCCEEDED( hr ) );
		hr=pEffect->SetFloat( "particleSpread", mParticleSpread );
		assert( SUCCEEDED( hr ) );
		hr=pEffect->SetFloat( "particleSpeed", mParticleSpeed );
		assert( SUCCEEDED( hr ) );
		hr=pEffect->SetFloat( "particleSystemHeight", mParticleSystemHeight );
		assert( SUCCEEDED( hr ) );
		hr=pEffect->SetFloat( "particleSize", mParticleSize );
		assert( SUCCEEDED( hr ) );
	}
	void setEnable( bool b ){
		mIsEnable=b;
	}
	bool isEnable(){
		return mIsEnable;
	}
	bool hasRigidBody(){
		return false;
	}
	float particleSystemShape(){
		return mParticleSystemShape;
	}
	float particleSpread(){
		return mParticleSpread;
	}
	float particleSpeed(){
		return mParticleSpeed;
	}
	float particleSystemHeight(){
		return mParticleSystemHeight;
	}
	float particleSize(){
		return mParticleSize;
	}

	void setParticleSystemShape(float value){
		mParticleSystemShape=value;
	}
	void setParticleSpread(float value){
		mParticleSpread=value;
	}
	void setParticleSpeed(float value){
		mParticleSpeed=value;
	}
	void setParticleSystemHeight(float value){
		mParticleSystemHeight=value;
	}
	void setParticleSize(float value){
		mParticleSize=value;
	}
private:
	CFire();
	DISALLOW_COPY_AND_ASSIGN(CFire);
	//D3DXMATRIX mMat;
	D3DXVECTOR3 mPos;
	D3DXVECTOR3 mScale;
	//D3DXQUATERNION mQuat;
	float mTime;
	float mEndTime;
									//min-max defalutValue	
	float mParticleSystemShape;		//0-2 1.f
	float mParticleSpread;			//0-50 20
	float mParticleSpeed;			//0-2 0.48
	float mParticleSystemHeight;	//0-160 80
	float mParticleSize;			//0-20. 7.8
	bool mIsEnable;
	//btRigidBody* m_pRigidBody;
};

class CFireEffect {
public:
	static CFireEffect* instance(){
		if(!m_pThis)
		{
			m_pThis= new CFireEffect();
		}
		return m_pThis;

	}
	void update( float elapsedTime ){
		for( std::list<CFire*>::iterator it = mFires.begin(), end = mFires.end();
				 it != end;
				  )
		{
			CFire* pf = *it;
			if( pf->isEnable() ){
				pf->update(elapsedTime);
				++it;
			}else{
				SAFE_DELETE(pf);
				it=mFires.erase(it);
			}
		}
	}
	void release(){
		if(m_pThis){
			SAFE_RELEASE(m_pEffect);
			for( std::list<CFire*>::iterator it = mFires.begin(), end = mFires.end();
				 it != end;
				 ++it )
			{
				SAFE_DELETE(*it);
			}
			mFires.clear();
			SAFE_RELEASE(m_pAnim);
			mTexture=0;
			m_pFrame=NULL;
			SAFE_DELETE(m_pThis);
		}
	}
	void draw( 
			const D3DXMATRIX &view,
			const D3DXMATRIX &projection
		)
	{
		HRESULT hr;

		GameLib::Graphics::Manager::instance().setBlendMode( BLEND_LINEAR );
		DWORD size = m_pFrame->pFrameFirstChild->pMeshContainer->MeshData.pMesh->GetNumBytesPerVertex();
		LPDIRECT3DVERTEXBUFFER9 dxVertecies;
		hr=m_pFrame->pFrameFirstChild->pMeshContainer->MeshData.pMesh->GetVertexBuffer( &dxVertecies );
		assert( SUCCEEDED( hr ) );
		IDirect3DDevice9 *pDevice = GameLib::Graphics::Manager::instance().dxDevice();
		//VertexBufferセット
		hr = pDevice->SetStreamSource( 0, dxVertecies, 0, size );
		DWORD num = m_pFrame->pFrameFirstChild->pMeshContainer->MeshData.pMesh->GetNumVertices();

		for( std::list<CFire*>::iterator it = mFires.begin(), end = mFires.end();
				it != end;
				++it )
		{
			CFire* pf = *it;
			pf->setParam( m_pEffect, view, projection );
			UINT numPass;
			
			assert( SUCCEEDED( hr ) );
			hr=m_pEffect->Begin( &numPass, 0 );
			assert( SUCCEEDED( hr ) );
			hr=m_pEffect->BeginPass( 0 );
			assert( SUCCEEDED( hr ) );
			{	
					
				
				hr = pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, num/3 ); 
				assert( SUCCEEDED( hr ) );
			}
			hr=m_pEffect->EndPass();
			assert( SUCCEEDED( hr ) );
			hr=m_pEffect->End();
			assert( SUCCEEDED( hr ) );
		}
	}
	void add(CFire *pFire){
		mFires.push_back(pFire);
	}
	//deleteはしない？する？
	void remove(CFire *pFire);
private:
	CFireEffect()
	:m_pEffect(NULL),
	m_pFrame(NULL),
	m_pAnim(NULL)
	{
		GameLib::Graphics::Manager m = GameLib::Graphics::Manager::instance();
	
		HRESULT hr;
		IDirect3DDevice9 *pDevice = m.dxDevice();
		LPD3DXBUFFER pCompilationErrors;
		//hr=D3DXCreateEffect( m.dxDevice(), gSimpleFx, sizeof(gSimpleFx), NULL, NULL, 0, NULL, &g_pEffect, NULL);
		hr=D3DXCreateEffectFromFile(
			pDevice,
			_T("shader/FireParticleSystem.fx"),
			NULL,
			NULL,
			0,
			NULL,
			&m_pEffect,
			&pCompilationErrors
		);
		if(pCompilationErrors){
			const char* p= (const char*)pCompilationErrors->GetBufferPointer();
			OutputDebugStringA( p );
			//OutputDebugString( p );
			pCompilationErrors->Release();
			assert(false && "shader compile failed.");
			return;
		}
		D3DXHANDLE handle = m_pEffect->GetAnnotation( "Flame_Tex", 0 );
		const char *pName;

		hr=m_pEffect->GetString( handle, &pName );
		assert( SUCCEEDED( hr ) );
		
		//ファイルパスを作成する
		char filePathName[64];
		const char *pFireEffectDir = "Data/shader/FireEffectParticleSystem/";
		int dirLen = strlen(pFireEffectDir);
		int fileLen = strlen(pName);
		int len=dirLen+fileLen;
		assert( len < 64 && "filePath is too long." );

		for(int i=0; i<dirLen; ++i){
			filePathName[i] = pFireEffectDir[i];
		}
		for(int i=0 ; i<fileLen; ++i){
			filePathName[i+dirLen]=pName[i];
		}
		filePathName[len]='\0';

		mTexture = Texture::create( filePathName );
		while( !mTexture.isReady() ){}
		hr=m_pEffect->SetTexture( "Flame_Tex", mTexture.dxTeture() ); 
		assert( SUCCEEDED( hr ) );
		hr=m_pEffect->SetTechnique( "FireParticleSystem" );
		assert( SUCCEEDED( hr ) );

		//XFile作成
		//pathName初期化
		for(int i=dirLen ; i<64; ++i){
			filePathName[i]='\0';
		}
		const char *xfileName = "FireParticleSystem.x";
		int xfileLen = strlen( xfileName );
		len = dirLen+xfileLen;
		assert( len < 64 && "filePath is too long." );

		for(int i=0 ; i<xfileLen; ++i){
			filePathName[i+dirLen]=xfileName[i];
		}

		GameLib::FileIO::InFile in = GameLib::FileIO::InFile::create( filePathName );
		while( !in.isFinished() ){}
		assert( !in.isError() );
		const char *data = in.data();
		unsigned long size = strlen(data);
		//hr=D3DXLoadMeshHierarchyFromXInMemory( in.data(), size, D3DXMESH_MANAGED, pDevice, &mNah, NULL, &m_pFrame, &m_pAnim);
		hr=D3DXLoadMeshHierarchyFromX( _T("Data/shader/FireEffectParticleSystem/FireParticleSystem.x"), D3DXMESH_MANAGED, pDevice, &mNah, NULL, &m_pFrame, &m_pAnim);
		assert( SUCCEEDED( hr ) );
		
	}

	virtual ~CFireEffect(){}
	DISALLOW_COPY_AND_ASSIGN(CFireEffect);
	
	static CFireEffect* m_pThis;
	ID3DXEffect *m_pEffect;
	Dix::CNormalAllocHierarchy mNah;
	D3DXFRAME *m_pFrame;
	ID3DXAnimationController *m_pAnim;

	Texture mTexture;
	
	std::list<CFire*> mFires;
	
	//std::list< std::shared_ptr<CFire*> > mFires;
};

#endif//__FIREEFFECT_H__