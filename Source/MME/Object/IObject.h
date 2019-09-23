#pragma once
#include<string>
#include<d3dx9.h>
#include<memory>
#include"MME/Enums.h"

namespace MME{
	namespace Object{

class IObject;
typedef std::shared_ptr<IObject> IObjectSharedPtr;
typedef std::weak_ptr<IObject> IObjectWeakPtr;
class IObject : public std::enable_shared_from_this<IObject>{
public:
	IObject();
	virtual ~IObject();

	virtual void draw()const=0;

	virtual float getFaceValue(const std::string &faceName )const=0;

	virtual const D3DXMATRIX & getBoneMatrix( const std::string &boneName )const=0;

	virtual float getScale()const=0;


	virtual const std::string& getModelFileName()const=0;

	//void registOffScreen( const char *effectFileName ,const char *offScreenName, const char *effectFileNameInOffScreen );
	
	bool canDraw()const;
	void setCanDraw( bool canDraw );
	void setCanDraw( MME::MMDPass pass, bool canDraw );
	
	float getSi()const;
	float getTr()const;

	const D3DXMATRIX & getWorldTransform() const;

	bool canRemove()const;

	void setCanRemove( bool canRemove );
protected:
	bool mCanDraw;
	bool mCanDrawMMDPass[MME::MP_NUM];//ZPlotÇñ≥éãÇµÇΩÇ¢ÇÃÇ™Ç†ÇÈÇÃÇ≈

	//standardeffectì‡ÇÃ
	//ï`âÊÉäÉXÉgÇ©ÇÁÇÕÇ∏Ç∑
	//canDrawÇæÇØÇ≈è\ï™Ç©
	//setCanDraw(true)ÇÃÇ∆Ç´í«â¡
	//setCanDraw(false)ÇÃÇ∆Ç´remove
	bool mCanRemove;

	float mTr;
	float mSi;
	D3DXMATRIX mTransform;
private:
	//disallow assign
	IObject( const IObject & )=delete;
	//disallow copy
	void operator=( const IObject & )=delete;
};
}//end namespace Object
}// end namespace MME