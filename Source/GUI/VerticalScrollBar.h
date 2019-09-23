#pragma once
#include"IComponent.h"

namespace GUI{
class Manager;
class DraggableLabel;
class Label;
class VerticalScrollBar : public BaseComponent {
public:
	VerticalScrollBar( 
		int x, int y,
		int sizeX, int sizeY,
		int barLength );
	virtual ~VerticalScrollBar();

	virtual void update();
	virtual void draw( Manager* mngr );

	//0.0-1.0‚ð•Ô‚·
	float getValue()const;

	void setBarPos( int x, int y );

	void setBarLength( int length );

	bool hasScrolled()const;
private:
	DraggableLabel *mBar;
	Label *mBackGround;
	int mOldBarPosX, mOldBarPosY;
};


}
