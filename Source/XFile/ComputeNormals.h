#pragma once
#include<GameLib/Graphics/VertexBuffer.h>
#include<GameLib/Graphics/IndexBuffer.h>
#include<GameLib/Graphics/Vertex.h>
#include<vector>
#include<GameLib/Math/Vector3.h>
//#include<assert.h>
//#include"helper/MyOutputDebugString.h"

namespace {
	//bool operator==( 
	//	const GameLib::Math::Vector3 &lhs,
	//	const GameLib::Math::Vector3 &rhs )
	//{
	//	return 
	//		lhs.x==rhs.x &&
	//		lhs.y==rhs.y &&
	//		lhs.z==rhs.z;
	//}
	//bool operator!=( 
	//	const GameLib::Math::Vector3 &lhs,
	//	const GameLib::Math::Vector3 &rhs )
	//{
	//	return !(lhs==rhs); 
	//		
	//}

	GameLib::Math::Vector3 computeNormal(
		GameLib::Math::Vector3 v0,
		GameLib::Math::Vector3 v1,
		GameLib::Math::Vector3 v2
	){
		v1-=v0;
		v2-=v0;
		
		GameLib::Math::Vector3 result;
		result.setCross( v1, v2 );
		if( result.squareLength() > 0.f ){
			result.normalize();
		}else{
			result.set( 0.f, 0.f, 0.f );
		}
		return result;
		
	}
}

namespace XFile {
static void computeNormals( 
	GameLib::Graphics::VertexBuffer *vb,
	const GameLib::Graphics::IndexBuffer &ib )
{
	using namespace GameLib::Math;
	
	
	struct FaceInfo{
		std::vector<Vector3> normals;
		Vector3 calcNormal()const{
			
			Vector3 sum( 0.f );
			for( int i=0, size=normals.size(); i<size; ++i ){
				sum += normals[i];
			}
			
			if( sum.squareLength() ){
				sum.normalize();
			} else{
				sum.set( 0.f, 1.f, 0.f );
			}

			return sum;
		}
	};

	FaceInfo *faceInfo = new FaceInfo [ vb->vertexNumber() ] ;

	//ŠÖ”‚Ìˆø”‚ğconstQÆ‚É‚·‚é‚±‚Æ‚ğ—Dæ‚µ‚½
	//‚»‚Á‚¿‚Ì‚Ù‚¤‚ªŠÖ”‚Ìg‚¢•û‚ª‚í‚©‚è‚â‚·‚¢‚¾‚ë‚¤
	unsigned short *indecies = const_cast<GameLib::Graphics::IndexBuffer*>(&ib)->lock();
	
	GameLib::Graphics::Vertex *v = vb->lock();

	for( int i=0, iMax=ib.indexNumber(); i<iMax; i+=3 ){
		unsigned short i0= indecies[i];
		unsigned short i1= indecies[i+1];
		unsigned short i2= indecies[i+2];

		Vector3 normal = computeNormal( v[i0].mPosition, v[i1].mPosition, v[i2].mPosition );


		faceInfo[i0].normals.push_back( normal );
		faceInfo[i1].normals.push_back( normal );
		faceInfo[i2].normals.push_back( normal );
	}

	for( int i=0, iMax=vb->vertexNumber(); i<iMax; ++i ){
		//assert( v[i].mNormal == faceInfo[i].average() );
		//Vector3 n0 = v[i].mNormal;
		//Vector3 n1 = faceInfo[i].calcNormal();

		//TRACE3( "( %f, %f, %f )\n", n0.x, n0.y, n0.z ); 
		//TRACE3( "( %f, %f, %f )\n", n1.x, n1.y, n1.z ); 
		
		v[i].mNormal = faceInfo[i].calcNormal();

	}

	vb->unlock( &v );
	const_cast<GameLib::Graphics::IndexBuffer*>(&ib)->unlock(&indecies);
	delete [] faceInfo;
}
}