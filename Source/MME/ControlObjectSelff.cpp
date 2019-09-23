#include"ControlObjectSelf.h"
#include<d3dx9.h>
#include"BulletPhysics/BulletPhysicsHelper.h"
#include<assert.h>
namespace {
	//大文字小文字無視
	inline bool equal( const char*left, const char* right )
	{
		return _strcmpi( left, right ) == 0;
	}
	
	
	inline void setIfNull( D3DXHANDLE &hLeft, const D3DXHANDLE &hRight ){
		if( hLeft==NULL ){
			hLeft = hRight;
		} else{
			assert( false && "There is a variable with the same meaning.");
		}		
	}
	
	//http://blogs.msdn.com/b/mikepelton/archive/2004/10/29/249501.aspx
	static void decomposeRollPitchYawZXYMatrix( float *xPitch, float *yYaw, float *zRoll,const  D3DXMATRIX &mx) {

	   *xPitch = asin(-mx._32);

	   float threshold = 0.001f; // Hardcoded constant - burn him, he's a witch
	   float test = cos(*xPitch);

	   if(test > threshold) {
		  *zRoll = atan2(mx._12, mx._22);
		  *yYaw = atan2(mx._31, mx._33);
	   } else {
		  *zRoll = atan2(-mx._21, mx._11);
		  *yYaw = 0.0;
	   }
	}
}
namespace MME{
	

//@param aname( Aragument name ): CONTROLOBJECTのnameアノテーションの値
//現状selfのみ
ControlObjectSelf::ControlObjectSelf( ID3DXEffect *effect , const std::string &aname )
	:mName(aname),
	mhCanDraw(0),
	mhScale(0),
	mhOffset(0),
	mhTransform(0),
	mhX(0),		
	mhY(0),		
	mhZ(0),		
	mhXYZ(0),	
	mhRx(0),	
	mhRy(0),	
	mhRz(0),	
	mhRxyz(0),	
	mhSi(0),	
	mhTr(0)
{
	HRESULT hr;
	assert( aname=="(self)" );
	D3DXEFFECT_DESC effectDesc;
	hr = effect->GetDesc( &effectDesc );
	assert( SUCCEEDED(hr) );
	for( UINT iParam = 0; iParam < effectDesc.Parameters; iParam++ )
	{
		D3DXHANDLE hParam = effect->GetParameter ( NULL, iParam );
		D3DXPARAMETER_DESC prmdesc;
		hr=effect->GetParameterDesc( hParam, &prmdesc );
		assert( SUCCEEDED(hr) );
		if( prmdesc.Semantic &&
			equal("CONTROLOBJECT", prmdesc.Semantic) )
		{
			D3DXHANDLE hName = effect->GetAnnotationByName( hParam, "name" );
			assert( hName );//省略不可
			const char *name;
			hr=effect->GetString( hName, &name );
			assert( SUCCEEDED(hr) );
			
			if( equal( mName.c_str(), name ) ){
				D3DXHANDLE hItem;
				hItem = effect->GetAnnotationByName( hParam, "item" );

				if( hItem ){
					const char *item;
					hr=effect->GetString( hItem, &item );
					assert( SUCCEEDED(hr) );
					
					if( equal( item, "X" ) ){
						assert( prmdesc.Type == D3DXPT_FLOAT );
						assert( prmdesc.Class == D3DXPC_SCALAR );
						assert( false && "not impl" );
						setIfNull( mhX, hParam );
						continue;
					}else if( equal( item, "Y" ) ){
						assert( prmdesc.Type == D3DXPT_FLOAT );
						assert( prmdesc.Class == D3DXPC_SCALAR );
						assert( false && "not impl" );
						setIfNull( mhY, hParam );
						continue;
					}else if( equal( item, "Z" ) ){
						assert( prmdesc.Type == D3DXPT_FLOAT );
						assert( prmdesc.Class == D3DXPC_SCALAR );
						assert( false && "not impl" );
						setIfNull( mhZ, hParam );
						continue;
					}else if( equal( item, "XYZ" ) ){
						assert( prmdesc.Type == D3DXPT_FLOAT );
						assert( prmdesc.Class == D3DXPC_VECTOR );
						assert( false && "not impl" );
						setIfNull( mhXYZ, hParam );
						continue;
					}else if( equal( item, "Rx" ) ){
						assert( prmdesc.Type == D3DXPT_FLOAT );
						assert( prmdesc.Class == D3DXPC_SCALAR );
						assert( false && "not impl" );
						setIfNull( mhRx, hParam );
						continue;
					}else if( equal( item, "Ry" ) ){
						assert( prmdesc.Type == D3DXPT_FLOAT );
						assert( prmdesc.Class == D3DXPC_SCALAR );
						assert( false && "not impl" );
						setIfNull( mhRy, hParam );
						continue;
					}else if( equal( item, "Rz" ) ){
						assert( prmdesc.Type == D3DXPT_FLOAT );
						assert( prmdesc.Class == D3DXPC_SCALAR );
						setIfNull( mhRz, hParam );
						assert( false && "not impl" );
						continue;
					}else if( equal( item, "Rxyz" ) ){
						assert( prmdesc.Type == D3DXPT_FLOAT );
						assert( prmdesc.Class == D3DXPC_VECTOR );
						assert( false && "not impl" );
						setIfNull( mhRxyz, hParam );
						continue;
					}else if( equal( item, "Si" ) ){
						assert( prmdesc.Type == D3DXPT_FLOAT );
						assert( prmdesc.Class == D3DXPC_SCALAR );
						setIfNull( mhSi, hParam );
						continue;
					}else if( equal( item, "Tr" ) ){
						assert( prmdesc.Type == D3DXPT_FLOAT );
						assert( prmdesc.Class == D3DXPC_SCALAR );
						setIfNull( mhTr, hParam );
						continue;
					}else{
						//ボーン名 : PMDモデルの指定ボーンの座標またはワールド変換行列を取得する。
						//　　　　 　型はfloat3,float4,float4x4のうちいずれか。

						//表情名　 : PMDモデルの指定した表情の値を取得する。型はfloat。
						
						//とりあえず、指定したファイル名のオブジェクトが存在しない場合、以下の値が設定される。の値を入れておこう
						if( 
							prmdesc.Type == D3DXPT_FLOAT &&
							prmdesc.Class == D3DXPC_SCALAR )
						{
							mFloats.push_back( hParam );
							continue;
						}
						else if( 
							prmdesc.Type == D3DXPT_FLOAT &&
							prmdesc.Class == D3DXPC_VECTOR )
						{
							mFloat3s.push_back( hParam);
							continue;
						}
						else if( 
							prmdesc.Type == D3DXPT_FLOAT &&
							prmdesc.Class == D3DXPC_VECTOR &&
							prmdesc.Bytes==4*3 )
						{
							mFloat3s.push_back( hParam);
							continue;
						}
						else if( 
							prmdesc.Type == D3DXPT_FLOAT &&
							prmdesc.Class == D3DXPC_VECTOR &&
							prmdesc.Bytes==4*4 )
						{
							mFloat4s.push_back( hParam );
							continue;
						}
						else if( 
							prmdesc.Type == D3DXPT_FLOAT &&
							(prmdesc.Class == D3DXPC_MATRIX_COLUMNS || prmdesc.Class == D3DXPC_MATRIX_ROWS) &&
							prmdesc.Bytes==4*4*4 )
						{
							mMatricies.push_back( hParam );
							continue;
						}
						else{
							assert( false );
							continue;
						}
					}
				}
				else{
					//bool
					//　指定したオブジェクトが表示されているか 
					if(
						prmdesc.Type == D3DXPT_BOOL &&
						prmdesc.Class == D3DXPC_SCALAR)
					{
						setIfNull( mhCanDraw, hParam );
						continue;
					}
					//float
					//　指定したオブジェクトのスケーリング値
					else if(
						prmdesc.Type == D3DXPT_FLOAT &&
						prmdesc.Class == D3DXPC_SCALAR )
					{
						setIfNull( mhScale, hParam );
						continue;
					}
					//float3, float4
					//　指定したオブジェクトの座標（オフセット 
					else if(
						prmdesc.Type == D3DXPT_FLOAT &&
						prmdesc.Class == D3DXPC_VECTOR &&
						(prmdesc.Bytes==4*3 || prmdesc.Bytes==4*4 ) &&
						(prmdesc.Columns==3 || prmdesc.Columns==4 ) )
					{
						setIfNull( mhOffset, hParam );
						continue;
					}
					//float4x4
					//　指定したオブジェクトのワールド変換行列
					else if(
						prmdesc.Type == D3DXPT_FLOAT &&
						(prmdesc.Class == D3DXPC_MATRIX_ROWS || prmdesc.Class == D3DXPC_MATRIX_COLUMNS ) &&
						prmdesc.Bytes==4*4*4 )
					{
						setIfNull( mhTransform, hParam );
						continue;
					}
					else {
						assert(false);
					}
				}
			}

		}
	}
	
	mFloats.shrink_to_fit();
	mFloat3s.shrink_to_fit();
	mFloat4s.shrink_to_fit();
	mMatricies.shrink_to_fit();
}
ControlObjectSelf::~ControlObjectSelf(){

}

void ControlObjectSelf::send( ID3DXEffect *effect, Object::IObjectSharedPtr object ){
	//if( btCollisionObject *btobj = object->getBtCollisionObject() ){
		//btobj->getWorldTransform().getBasis().getEulerYPR( r[1], r[0], r[2] );
		//pos = object->getBtCollisionObject()->getWorldTransform().getOrigin();
	//}

	const D3DXMATRIX &world = object->getWorldTransform();
	btVector3 pos( world._41, world._42, world._43 );
	

	HRESULT hr;

	if(mhCanDraw){
		hr=effect->SetBool( mhCanDraw, object->canDraw() );
		assert( SUCCEEDED(hr) );
	}

	if( mhOffset ){
		hr=effect->SetFloatArray( mhOffset, pos, 4 );
		assert( SUCCEEDED(hr) );
	}

	if( mhScale ){
		hr=effect->SetFloat( mhScale, object->getScale() );
		assert( SUCCEEDED(hr) );
	}

	if( mhTransform ){
		hr=effect->SetMatrix( mhTransform, &world );
		assert( SUCCEEDED(hr) );
	}

	if( mhX ){
		hr=effect->SetFloat( mhX, pos.x() );
		assert( SUCCEEDED(hr) );
	}

	if( mhY ){
		hr=effect->SetFloat( mhY, pos.y() );
		assert( SUCCEEDED(hr) );

	}

	if( mhZ ){
		hr=effect->SetFloat( mhZ, pos.z() );
		assert( SUCCEEDED(hr) );

	}

	if( mhXYZ ){
		hr=effect->SetFloatArray( mhXYZ, pos, 3 );
		assert( SUCCEEDED(hr) );
	}

	if(
		mhRx ||
		mhRy ||
		mhRz ||
		mhRxyz )
	{
		float r[3] = {0.f, 0.f, 0.f};
		decomposeRollPitchYawZXYMatrix( &r[0], &r[1], &r[2], world );

		if( mhRx ){
			hr=effect->SetFloat( mhRx, r[0] );
			assert( SUCCEEDED(hr) );
		}

		if( mhRy ){
			hr=effect->SetFloat( mhRy, r[1] );
			assert( SUCCEEDED(hr) );
		}

		if( mhRz ){
			hr=effect->SetFloat( mhRz, r[2] );
			assert( SUCCEEDED(hr) );
		}

		if( mhRxyz ){
			hr=effect->SetFloatArray( mhRxyz, r, 3 );
			assert( SUCCEEDED(hr) );
		}
	}

	if( mhSi ){
		hr=effect->SetFloat( mhSi, object->getSi() );
		assert( SUCCEEDED(hr) );
	}

	if( mhTr ){
		hr=effect->SetFloat( mhTr, object->getTr() );
		assert( SUCCEEDED(hr) );
	}

	for( int i=0, size=mFloats.size(); i<size; ++i){
		hr=effect->SetFloat( mFloats[i], 0.0 );
	}

	float f4[4] = { 0.f, 0.f, 0.f, 1.f };
	for( int i=0, size=mFloat3s.size(); i<size; ++i){
		hr=effect->SetFloatArray( mFloat3s[i], f4, 3 );
	}

	for( int i=0, size=mFloat4s.size(); i<size; ++i){
		hr=effect->SetFloatArray( mFloat4s[i], f4, 4 );
	}

	D3DXMATRIX matI;
	D3DXMatrixIdentity( &matI );
	for( int i=0, size=mMatricies.size(); i<size; ++i){
		hr=effect->SetMatrix( mMatricies[i], &matI );
	}
}

}//end namespace