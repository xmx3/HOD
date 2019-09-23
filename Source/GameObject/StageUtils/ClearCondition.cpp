#include"ClearCondition.h"
#include<GameLib/PseudoXml/Document.h>
#include<GameLib/PseudoXml/Element.h>
#include<GameLib/PseudoXml/Attribute.h>
#include<GameLib/Base/RefString.h>
#include<fstream>
#include<iostream>
#include<string>
#include<GameLib/GameLib.h>

namespace GameObject{
namespace StageUtils{


using ClearCondition::ICondition;
using ClearCondition::ConditionSharedPtr;

namespace ClearCondition {
static ConditionSharedPtr create( const GameLib::PseudoXml::ConstElement & e );
}

namespace{
class SimpleCondition : public ICondition {
public:
	static ConditionSharedPtr create( const GameLib::PseudoXml::ConstElement & e ){
		using namespace GameLib::PseudoXml;
		using GameLib::RefString;

		ASSERT( e.attributeNumber()==1 );
		ConstAttribute a = e.attribute(0);
		ASSERT( RefString(a.name())=="value" );
		RefString value( a.value() );
		if( value=="true" ){
			ConditionSharedPtr out( new SimpleCondition( true ) );
			return out;
		} else if( value=="false" ){
			ConditionSharedPtr out( new SimpleCondition( false ) );
			return out;
		} else{
			ASSERT( false && "true or false is wrong." );
			ConditionSharedPtr out;
			return out;
		}
	}
	
	virtual ~SimpleCondition(){
		// if(mBool){
		// 	std::cout << "~SimpleCondition()true" << std::endl;
		// } else {
		// 	std::cout << "~SimpleCondition()false" << std::endl;
		// }
	}

	virtual void debugPrint()const{
		if(mBool){
			std::cout << "true";
		} else {
			std::cout << "false";
		}
	}

	virtual bool is()const {
		return mBool;
	}
private:
	SimpleCondition( bool b )
	:mBool(b)
	{}
	bool mBool;
};

class AndPair : public ICondition {
public:
	static ConditionSharedPtr create( const GameLib::PseudoXml::ConstElement &parent );
	virtual ~AndPair(){
		// std::cout << "~AndPair()" << std::endl;
		mLeft.reset();
		mRight.reset();
	
	}
	
	virtual bool is()const {
		return mLeft->is() && mRight->is();
	}

	virtual void debugPrint()const{
		std::cout <<"(";
		mLeft->debugPrint();
		std::cout <<" and ";
		mRight->debugPrint();
		std::cout <<")";
	}
private:
		AndPair( ConditionSharedPtr left, ConditionSharedPtr right)
	:mLeft(left),
	mRight(right)
	{}

	ConditionSharedPtr mLeft;
	ConditionSharedPtr mRight;
};

class OrPair : public ICondition {
public:
	static ConditionSharedPtr create( const GameLib::PseudoXml::ConstElement &parent )
	{
		using namespace GameLib::PseudoXml;
		using GameLib::RefString;

		ConditionSharedPtr children[2];
		int n = parent.childNumber();
		ASSERT( n==2 && "child number must be 2.");
		for(int i=0; i<n; ++i ){
			ConstElement e = parent.child(i);
			children[i] = ClearCondition::create( e );
		}
		ConditionSharedPtr out( new OrPair( children[0], children[1] ) );
		return out;
	}

	virtual ~OrPair(){
		// std::cout << "~OrPair()" << std::endl;
		mLeft.reset();
		mRight.reset();
	
	}
	
	virtual bool is()const {
		return mLeft->is() || mRight->is();
	}

	virtual void debugPrint()const{
		std::cout <<"(";
		mLeft->debugPrint();
		std::cout <<" or ";
		mRight->debugPrint();
		std::cout <<")";
	}
private:
		OrPair( ConditionSharedPtr left, ConditionSharedPtr right)
	:mLeft(left),
	mRight(right)
	{}

	ConditionSharedPtr mLeft;
	ConditionSharedPtr mRight;
};

ConditionSharedPtr AndPair::create( const GameLib::PseudoXml::ConstElement &parent )
{
	using namespace GameLib::PseudoXml;
	using GameLib::RefString;

	ConditionSharedPtr children[2];
	int n = parent.childNumber();
	ASSERT( n==2 && "child number must be 2.");
	
	for(int i=0; i<n; ++i ){
		ConstElement e = parent.child(i);
		children[i] = ClearCondition::create( e );
	}
	ConditionSharedPtr out( new AndPair( children[0], children[1] ) );
	return out;
}


class DeathAllEnemiesCondition : public ICondition {
public:
	static ConditionSharedPtr create( const GameLib::PseudoXml::ConstElement & e ){
		//using namespace GameLib::PseudoXml;
		//using GameLib::RefString;
		ConditionSharedPtr out( new DeathAllEnemiesCondition() );
	}

	
	virtual ~DeathAllEnemiesCondition(){
		ASSERT( false );
	}

	virtual void debugPrint()const{
		ASSERT( false );

	}

	virtual bool is()const {
		ASSERT( false );
		//Enemy::Manager::instance()->areEnemiesDestroy();
	}
private:
	DeathAllEnemiesCondition()
	{}
};


}//end namespace

namespace ClearCondition{
static ConditionSharedPtr create( const GameLib::PseudoXml::Document &d ){
	if( d.isError() ){
		ASSERT(false && "document is error!" );
		return 0;
	}
	using namespace GameLib::PseudoXml;

	ConstElement e = d.child(0);
	ConditionSharedPtr root = create( e );
	return root;
}

static ConditionSharedPtr create(const GameLib::PseudoXml::ConstElement &e ){
	using namespace GameLib::PseudoXml;
	using GameLib::RefString;

	RefString name( e.name() );
	if(name=="AndPair"){
		return AndPair::create( e );
	}else if( name=="OrPair" ) {
		return OrPair::create( e );
	} else if( name=="SimpleCondition" ) {
		return SimpleCondition::create( e );
	} else {
		std::cout << e.name() ;
		ASSERT( false && "element name is wrong." );
		return NULL;
	}
}
}//end namespace ClearCondition
}//end namespace StageUtils
}//end namespace GameObject
