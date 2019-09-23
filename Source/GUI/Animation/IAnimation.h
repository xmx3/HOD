#pragma once

namespace GUI{
	class IComponent;
	namespace Animation {

class IAnimation{
public:
	IAnimation(){}
	virtual ~IAnimation(){}

	virtual void update( float dt, IComponent* )=0;
	virtual bool isOver()const=0;
private:
	IAnimation( const IAnimation & );
	void operator=( const IAnimation & );
};

	}// end namespace Animation
}// end namespace GUI