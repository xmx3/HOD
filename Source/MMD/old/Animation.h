#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include<vector>
#include"MMDMacro.h"
#include"BezierCurve.h"

class CFaceKey;
class CFrameKey;
class CBone;
class CFace;
class CVmd;

namespace GameLib{
	namespace FileIO {
		class InFile;
	}
}

class CAnimation {
public:
	CAnimation();
	virtual ~CAnimation();
	
	bool load( const char *pFileName, CBone *pBones, const unsigned short &boneSize );
	bool load( const GameLib::FileIO::InFile &inFile, CBone* bones, const unsigned short &boneSize );

	const char* getName(){ return name_; }
	bool isOver(const float &frame ) const { return frame>=maxFrame_; }
	
	void resetRelativeBones( CBone *pBones, const float &frame, const float &weight );
	void updateBones( CBone *pBones, const float &frame, const float &weight );
	void updateFace( CFace *pFaces, const short &faceSize, const float &frame, const float &weight );
private:
	DISALLOW_COPY_AND_ASSIGN(CAnimation);
	bool load( const CVmd &vmd, CBone *pBones, const unsigned short &boneSize );
	char* name_;
	std::vector<CFrameKey*> frameKeys_;
	std::vector<CFaceKey*> faceKeys_;
	
	//‚±‚±‚Å‚½‚¹‚é‚×‚«‚¶‚á‚È‚¢BCFrameKey‚É‚½‚¹‚é‚×‚«
	//ƒoƒO‚¾‚¯‚ÇBoneKey‚Ì‚Ù‚¤‚ÅC³‚·‚é
	CBezierCurve interpolationX_;
	CBezierCurve interpolationY_;
	CBezierCurve interpolationZ_;
	CBezierCurve interpolationQ_;


	float maxFrame_;
};
#endif __ANIMATION_H__
