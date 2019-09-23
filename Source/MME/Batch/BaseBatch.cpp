#include"BaseBatch.h"
#include"MME/BaseEffect.h"
#include"OffScreenBatch.h"


namespace MME{ namespace Batch {
	
BaseBatch::BaseBatch(BaseEffect* b) 
:mBaseEffect(b)
{
	//buildOffScreenBatch
	unsigned int n = mBaseEffect->getNumberOfOffScreens();
	mOffScreens.reserve(n);
	for( unsigned int i=0; i<n; ++i ){
		mOffScreens.push_back( new OffScreenBatch( mBaseEffect->getOffScreenAt( i ) ) );
	}
}

BaseBatch::~BaseBatch(){
	for( unsigned int i=0; i<mOffScreens.size(); ++i ){
		delete mOffScreens[i];
		mOffScreens[i]=0;
	}

}


void BaseBatch::setObjectsPtr(const DrawObjectsSharedPtr &objects ){
	mObjects = objects;
}

void BaseBatch::add( const Object::IObjectSharedPtr &obj ){
	mObjects->push_back( obj );
	for( unsigned int i=0, size=mOffScreens.size(); i<size; ++i ){
		mOffScreens[i]->add( obj );
	}
}

void  BaseBatch::drawOffScreens(){
	for( unsigned int i=0, size=mOffScreens.size(); i<size; ++i ){
		mOffScreens[i]->draw();
	}
}

const std::string & BaseBatch::getName()const
{
	return mBaseEffect->getName();
}


} } // namespace MME::Batch
