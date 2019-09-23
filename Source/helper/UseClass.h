#pragma once
#include<assert.h>

struct no{};
struct yes{};
struct either{};

class UseClass{
public:
	enum{
		either_t=2,
	};
	
	UseClass():mType(either_t){}
	
	UseClass( const no & )
		:mType(false){}
	UseClass( const yes & )
		:mType(true){}
	UseClass( const either & )
		:mType(either_t){}

	UseClass( bool yesOrNo )
		:mType(yesOrNo)
	{
		assert( mType < either_t+1 );
	}
	
	// bool operator<( const UseClass &leftHand ) const {
	// 	return mType < leftHand.mType;
	// }

	bool operator==( const UseClass &leftHand ) const {
		if( mType==either_t || leftHand.mType==either_t ){
			return true;
		} else {
			return mType==leftHand.mType;
		}
	}
	bool operator!=( const UseClass &leftHand ) const {
		return !operator==(leftHand );
	}

	void set( bool b){
		mType=static_cast<bool>(b);
	}
private:
	char mType;
};
//test
/*
#include<tuple>
#include<set>


int main(int argc, char const* argv[])
{
	std::tuple< UseClass, UseClass > tpl0;
	std::tuple< UseClass, UseClass > tpl1 = std::make_tuple< UseClass, UseClass >( yes(), no() );
	std::set< std::tuple< UseClass, UseClass > > types;
	types.insert( tpl0 );
		
	// assert( types.find( tpl1 )!=types.end() );
	
	assert( tpl0==tpl1 );
	
	assert( UseClass(either())==yes() );
	assert( UseClass(either())==true );
	assert( UseClass(either())==no() );
	assert( UseClass(yes())!=no() );
	
	// コンパイルエラー
	// yes()==yes();
	// yes == yes;
	
	assert(
			std::make_tuple( 3, UseClass(true), UseClass(either()), UseClass(either()), UseClass(either() ) ) ==
			std::make_tuple( 3, true, false, true, false ) );
	
	assert(
			std::make_tuple( 3, UseClass(true), UseClass(either()), UseClass(either()), UseClass(true)) !=
			std::make_tuple( 3, true, false, true, false ) );
	
	assert(
			std::make_tuple( 3, UseClass(true), UseClass(either()), UseClass(either()), UseClass(no())) ==
			std::make_tuple( 3, true, false, true, either() ) );
	
	assert(
			std::make_tuple( 3, UseClass(true), UseClass(either()), UseClass(either()), UseClass(either())) ==
			std::make_tuple( 3, true, false, true, false ) );
	
	assert(
			std::make_tuple( 0, UseClass(true), UseClass(either()), UseClass(either()), UseClass(either())) !=
			std::make_tuple( 3, true, false, true, false ) );
	
	// assert(
	// 		std::make_tuple( 3, either, UseClass(either), UseClass(either), UseClass(either)) ==
	// 		std::make_tuple( 3, true, false, true, false ) );
	
	//コンパイルエラーにしたい
	// assert(
	// 		std::make_tuple( 3, either(), UseClass(either()), UseClass(either()), UseClass(either())) ==
	// 		std::make_tuple( 3, 2, false, true, false ) );
	// 


	

	

	


	
	
	
	return 0;
}
*/
