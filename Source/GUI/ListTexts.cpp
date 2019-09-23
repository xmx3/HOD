#include"ListTexts.h"
#include<GameLib/GameLib.h>
#include<GameLib/Scene/Font.h>
#include"PushableLabel.h"
#include"VerticalScrollBar.h"
#include"Manager.h"
#include"Fonts.h"
#include<GameLib/Graphics/Texture.h>
#include<assert.h>
#include"helper/MyOutputDebugString.h"

namespace GUI {
	static const int skScrollBarWidth=5;
ListTexts::ListTexts(
	int x, int y,
	int sizeX, int sizeY
)
:BaseComponent( x, y, sizeX, sizeY ),
mScrollBar(NULL),
mSelectedIndex(-1),
mSelectedItemColor( 0x88000088 ),
mHoverItemColor( 0x11000088 ),
mItemColor( 0x00 )
{
	setFont( Fonts::getGothic() );

	mScrollBar = NEW VerticalScrollBar(
		x+sizeX-skScrollBarWidth, y,//pos
		skScrollBarWidth, sizeY,//width
		sizeY );
}
ListTexts::~ListTexts(){
	for( int i=0, size=mList.size(); i<size; ++i )
	{
		delete mList[i];
		mList[i]=0;
	}
	delete mScrollBar;
	mScrollBar=0;
}

void ListTexts::add( const char* text ){
	//elem : element
	//Len : Length of Y axis
	int elemLen = mFont.charHeight();
	
	PushableLabel *lbl = NEW PushableLabel(
		1, 1, //表示する際に正しい値にするので適当
		mSizeX-skScrollBarWidth, elemLen,
		0x770000ff );
	//lbl->setTexture(0);
	lbl->setFont(mFont);
	lbl->setText( text );
	mList.push_back( lbl );
	
	int numElem = mList.size();
	
	float numElemPerPage = static_cast<float>(mSizeY)/elemLen;

	if( numElem > floor(numElemPerPage) ){
		float pageLen = static_cast<float>(elemLen)*numElemPerPage;
		float totalLen = static_cast<float>(elemLen*numElem);
	
		int newLen = static_cast<int>(pageLen/totalLen*mSizeY);
		mScrollBar->setBarLength( newLen );
	}
	
}
//void ListTexts::remove( const std::string &text ){}
//
//const std::string& ListTexts::currentText()const{
//
//}


void ListTexts::setSelectedIndex( unsigned int index){
	assert( index < mList.size() );
	mSelectedIndex=index;

}
int ListTexts::getSelectedIndex()const{
	return mSelectedIndex;
}

//int ListTexts::count() const{}
//
void ListTexts::update(){
	mScrollBar->update();

	//elem : element
	//Len : Length of Y Axis
	int elemLen = mFont.charHeight();
	
	int numElemPerPage = mSizeY/elemLen;

	int drawStart = static_cast<int>(mScrollBar->getValue()*(mList.size()-numElemPerPage) );
	assert( drawStart>=0 );
	for( int i=0;
		i<numElemPerPage;
		++i )
	{
		unsigned int drawIdx=i+drawStart;
		if( drawIdx>=mList.size() ){
			break;
		} 

		mList[drawIdx]->setPos( mX, mY+i*elemLen );
		mList[drawIdx]->update();
		if( mList[drawIdx]->isPushed() ){
			mSelectedIndex = drawIdx;
		}
	}

}
void ListTexts::draw( Manager* mngr ){
	//elem : element
	//Len : Length of Y Axis
	int elemLen = mFont.charHeight();
	
	unsigned int numElemPerPage = mSizeY/elemLen;

	if( mList.size() > numElemPerPage  ){
		mScrollBar->draw(mngr);
	}

	int drawStart = static_cast<int>(mScrollBar->getValue()*(mList.size()-numElemPerPage) );
	assert( drawStart>=0 );
	for( int i=0;
		i<numElemPerPage;
		++i )
	{
		unsigned int drawIdx=i+drawStart;
		if( drawIdx>=mList.size() ){
			break;
		} 

		//色の設定
		if( drawIdx==mSelectedIndex ){
			mList[drawIdx]->setColor( mSelectedItemColor );
		}else if( mList[drawIdx]->isHover() )
		{
			mList[drawIdx]->setColor( mHoverItemColor );
		}
		else{
			mList[drawIdx]->setColor( mItemColor );
		}
		mList[drawIdx]->draw(mngr);
	}


}

void ListTexts::setFont( GameLib::Scene::Font f ){
	int elemLen = f.charHeight();
	if(mSizeY%elemLen!=0){
		//表示がきれいになる
		TRACE2( "%s : line %d sizeYはelemLenの倍数がお勧め\n", __FILE__, __LINE__ );
	}
	mFont=f;
}

bool ListTexts::isPushedSelectedElement()const{
	if(mSelectedIndex>=0){
		return mList[mSelectedIndex]->isPushed();
	}
	return false;
}

void ListTexts::setText( unsigned int index, const char* text ){
	assert( index>=0 && index<mList.size() );
	mList[index]->setText( text );
}

void ListTexts::setPushable( unsigned int index, bool enable ){
	assert( index>=0 && index<mList.size() );
	mList[index]->setPushable(enable);
}


}
