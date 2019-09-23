#ifndef __ANIMATIONPLAYER_H__
#define __ANIMATIONPLAYER_H__
#include "Animation.h"

namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}

class CAnimationPlayer {
public:
	CAnimationPlayer()
		:frame_(0.f),
		weight_(0.f)
	{}
	virtual ~CAnimationPlayer(){};

	bool load(const char *pFileName, CBone *pBones, unsigned short &boneSize ){
		return anim_.load( pFileName, pBones, boneSize );
	}
	
	bool load(const GameLib::FileIO::InFile &inFile, CBone *bones, unsigned short &boneSize ){
		return anim_.load( inFile, bones, boneSize );
	}



	const char* getName(){ return anim_.getName(); }
	bool isOver() const { return anim_.isOver(frame_); }
	void setFrame( const float &frame ){ frame_=frame; }
	float getFrame(){ return frame_; }
	//void resetTime();
	void stepFrame( const float &frame ){ frame_+=frame; }

	void setWeight( const float &weight ){ weight_=weight; }
	float getWeight(){ return weight_; }


	void resetRelativeBones(CBone *pBones){
		anim_.resetRelativeBones( pBones , frame_ , weight_ );
	}
	void updateBones(CBone *pBones){
		anim_.updateBones( pBones , frame_ , weight_ );
	}
	void updateFace( CFace *pFaces, const short &size){
		anim_.updateFace( pFaces , size, frame_ , weight_ );
	}
private:
	DISALLOW_COPY_AND_ASSIGN(CAnimationPlayer);

	CAnimation anim_;
	float frame_;//1frame 1/30second
	float weight_;
};

#endif//__ANIMATIONPLAYER_H__