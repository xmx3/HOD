#pragma once
#include"Label.h"
#include<GameLib/Framework.h>
namespace GameLib{
	namespace Graphics{
		class Texture;
	}
}
using GameLib::Graphics::Texture;


namespace GUI{
class Manager;
//ドラッグドロップ検知
class DraggableLabel : public Label {
public:
	DraggableLabel(
		int x, int y,
		int sizeX, int sizeY,
		int minX=0, int maxX=GameLib::Framework::instance().width(),
		int minY=0, int maxY=GameLib::Framework::instance().height(),
		unsigned int color = 0xffffffff,
		unsigned int fontColor = 0xff000000,
		float u0=0.f, float v0=0.f,
		float u1=1.f, float v1=1.f );
	virtual ~DraggableLabel();
		
	virtual void update();
	virtual void draw( Manager* mngr );
	
	bool isDragging() const {
		return mIsDragging;
	}
	bool isDropped() const {
		return mIsDropped;		
	};
	
	void setMoveableArea( int left, int top, int right, int bottom ){
		mArea.left=left;
		mArea.top=top;
		mArea.right=right;
		mArea.bottom=bottom;
	}
	//位置をエリア内に修正する
	virtual void setPos( int x, int y );

	
	

private:
	//disallow copy
	DraggableLabel( const DraggableLabel& );	
	//disallow assin
	void operator=( const DraggableLabel& );
	
	//位置を修正するsetPosした場合呼び出す
	//void limitPosition();

private:
	int		mClickedX, mClickedY;
	int		mClickedOffsetX, mClickedOffsetY;
	bool	mIsDragging;
	bool	mIsDropped;
	struct Rect{
		Rect( int l, int t, int r, int b )
			:left(l), top(t), right(r), bottom(b)
		{}
		int left;
		int top;
		int right;
		int bottom;
	};
	Rect	mArea;
};


}//namespace GUI
