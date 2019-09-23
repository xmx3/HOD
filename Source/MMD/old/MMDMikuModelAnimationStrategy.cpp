//#include "MMDMikuModel.h"
//本当はここに定義したい
//コンパイル通るけどエラーがウザイので仕方なしに
/*
class CMMD_MikuModel::CWalkAnimation : public CBaseAnimationStrategy {
public:
	CWalkAnimation(){}
	virtual ~CWalkAnimation(){};

	void update( const D3DXMATRIX &world, float elapsedTime, CMMD_MikuModel *pMiku )
	{
		default_update( world, elapsedTime, pMiku );
	}
	IAnimationStrategy* changeState( IAnimationStrategy *pS, CMMD_MikuModel *pMiku )
	{
		default_changeState( pS, pMiku );
		return pS; 
	}
	AnimationState getType()
	{
		return ANIM_WALK;
	}
	bool isStand() {
		return true;
	}
	bool isChangeAble(IAnimationStrategy *pS)
	{
		AnimationState s=pS->getType();
		if(s==ANIM_WALK){
			return false;
		}
		if( pS->isStand() )
		{
			return true;
		}
		return false;
	}
protected:
	bool isOver( CMMD_MikuModel *pMiku ){
		return pMiku->mModel.getFrame( pMiku->mState ) > 32;
	}
};
*/