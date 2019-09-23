#include"MouseWrapper.h"



int		CMouseWrapper::sDoubleClickAbleTime[2] = { 0, 0 };
bool	CMouseWrapper::sIsOnDoubleClicked[2] = { false, false };
//bool	CMouseWrapper::sIsTriggeredDoubleClicked[2] = { false, false };

bool	CMouseWrapper::sIsOnRight=false;
bool	CMouseWrapper::sIsOnLeft=false;

const int	CMouseWrapper::skLeft=64;
const int	CMouseWrapper::skRight=640-64;

const int CMouseWrapper::DOUBLE_CLICK_ABLE_TIME=10;