#include"StartEnd.h"
#include"MMD/Model.h"
namespace MMD {
namespace AnimationState {

bool StartEnd::isOver( CModel *model ){
	return model->getFrame() > mEndFrame;
}



}
}