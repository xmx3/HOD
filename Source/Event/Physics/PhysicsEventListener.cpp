#include"PhysicsEventListener.h"
#include"PhysicsEventData.h"
#include<btBulletCollisionCommon.h>
#include"helper/MyOutputDebugString.h"
#include"GameObject/Accessory.h"
#include<assert.h>

bool PhysicsEventListener::handleEvent( IEventData const & ev ) {
	using Component::RigidBodyComponent;

	if( ev.getEventType().isExactly(OnCollisionEnterEventData::rtti) ){
		OnCollisionEnterEventData const *colEntrEv = dynamic_cast<OnCollisionEnterEventData const *>(&ev);
		
		RigidBodyComponent *gameObj0 = static_cast<RigidBodyComponent*>(colEntrEv->mObj0->getUserPointer());
		gameObj0->onCollisionEnter( colEntrEv->mManifold, colEntrEv->mObj0, colEntrEv->mObj1 );


		RigidBodyComponent *gameObj1 = static_cast<RigidBodyComponent*>(colEntrEv->mObj1->getUserPointer());
		gameObj1->onCollisionEnter( colEntrEv->mManifold, colEntrEv->mObj1, colEntrEv->mObj0 );
		
		//TRACE1("%s\n", gameObj0->getRTTI().getClassName().c_str());
		//TRACE1("%s\n", gameObj1->getRTTI().getClassName().c_str() );


		return true;
	}
	else if( ev.getEventType().isExactly( OnCollisionStayEventData::rtti ) ){	
		OnCollisionStayEventData const *colStyEv = dynamic_cast<OnCollisionStayEventData const *>(&ev);
		
		RigidBodyComponent *gameObj0 = static_cast<RigidBodyComponent*>(colStyEv->mObj0->getUserPointer());
		gameObj0->onCollisionStay( colStyEv->mManifold, colStyEv->mObj0, colStyEv->mObj1 );

		RigidBodyComponent *gameObj1 = static_cast<RigidBodyComponent*>(colStyEv->mObj1->getUserPointer());
		gameObj1->onCollisionStay( colStyEv->mManifold, colStyEv->mObj1, colStyEv->mObj0 );
		return true;
	}
	else if( ev.getEventType().isExactly( OnCollisionExitEventData::rtti ) ){

		OnCollisionExitEventData const *colExtEv = dynamic_cast<OnCollisionExitEventData const *>(&ev);
		
		RigidBodyComponent *gameObj0 = static_cast<RigidBodyComponent*>(colExtEv->mObj0->getUserPointer());
		gameObj0->onCollisionExit( colExtEv->mObj0, colExtEv->mObj1 );

		RigidBodyComponent *gameObj1 = static_cast<RigidBodyComponent*>(colExtEv->mObj1->getUserPointer());
		gameObj1->onCollisionExit( colExtEv->mObj1, colExtEv->mObj0 );
		return true;
	}
	return false;
}

bool PhysicsEventListener::validateEventType( EventType const &ev ) const {
	if( ev.isExactly( OnCollisionEnterEventData::rtti ) ||
		ev.isExactly( OnCollisionStayEventData::rtti ) ||	
		ev.isExactly( OnCollisionExitEventData::rtti ) ){
		return true;
	}
	return false;
}

