#ifndef __EXPLOSION_GHOST_OBJECT__
#define __EXPLOSION_GHOST_OBJECT__
class btPairCachingGhostObject;
class btGhostObject;
class btSphereShape;
class btVector3;

class ExplosionGhostObject {
public:
	ExplosionGhostObject();
	~ExplosionGhostObject();
	void update( float elapsedTime );
	void draw() const;
	void setOwner( const void* owner ){
		mOwner=owner;
	}
	void setPos( const btVector3 &p );
	void setScale( const float &scale ){
		mScale = scale;
	}
	void setEnable( bool b ){
		if(b==mIsEnable){
			return;
		}
		mIsEnable=b;
		if( b ){
			add();
		}
		else {
			remove();
		}
	}
	bool isEnable() const{
		return mIsEnable;
	}

	
private:
	void add();
	void remove();
	btPairCachingGhostObject *mGhost;
	btSphereShape *mShape;
	const void    *mOwner;
	float mScale;
	float mPower;
	bool mIsEnable;

};
#endif//__EXPLOSION_GHOST_OBJECT__