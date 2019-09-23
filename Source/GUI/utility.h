#pragma once
#include<assert.h>
#include<memory>

//名前 helperのほうがよかったか？
//一箇所にまとめたかったので作った
//別に違う値、使うことも多々ある
namespace GUI{
namespace ButtonBasicSize{
	int width();
	int height();
};


namespace SaveLoadListTextPosSize{
	int x();
	int y();
	int width();
	int height();
};

class ListTexts;

std::shared_ptr<ListTexts> createSaveListText();
std::shared_ptr<ListTexts> createLoadListText();

void updateSaveListText( int index, std::shared_ptr<ListTexts> list );


}//end namespace GUI