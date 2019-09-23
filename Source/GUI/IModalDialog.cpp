#include"IModalDialog.h"
#include"Manager.h"
#include<GameLib/GameLib.h>
namespace GUI{

IModalDialog::IModalDialog(){}
IModalDialog::~IModalDialog(){
	hide();
}
	
void IModalDialog::show(){
	Manager *m=Manager::instance();
	STRONG_ASSERT( 
		m->mModalDialog==NULL || m->mModalDialog == this &&
		"use after hide!" );
	if( m->mModalDialog==NULL || m->mModalDialog == this ){
		m->mModalDialog = this;
	}
}
void IModalDialog::hide(){
	if( Manager::isInstance() ){
		Manager *m=Manager::instance();
		STRONG_ASSERT( 
			m->mModalDialog == this ||
			m->mModalDialog == NULL	&&
			"it can be only myself that sets mModalDialog NULL." );
		if( m->mModalDialog == this  ){
			m->mModalDialog = NULL;
		}
	}
}

}//end namespace GUI