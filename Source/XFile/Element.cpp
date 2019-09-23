#include "XFile/Element.h"
#include "XFile/Template.h"
#include <GameLib/Base/RefString.h>
#include <GameLib/Base/Array.h>
#include <GameLib/Base/AutoPtr.h>
#include <GameLib/Base/OStringStream.h>
#include<assert.h>
#include"helper/MyOutputDebugString.h"

namespace XFile{

using namespace GameLib;

//Element
Element::Element(){
}

Element::~Element(){
}

//CompositeArrayElement
CompositeArrayElement::CompositeArrayElement( Array< int >& sizes, const RefString& type, const RefString& name ) :
mSizes( sizes.size() ),
mName( name ),
mType( type )
{
	int n = 1;
	for ( int i = 0; i < mSizes.size(); ++i ){
		mSizes[ i ] = sizes[ i ];
		n *= sizes[ i ];
	}
	mElements.setSize( n );
}

CompositeArrayElement::~CompositeArrayElement(){}

void CompositeArrayElement::setElement( int i, ElementSharedPtr* e ){ //この添え字は一次元化した添え字
	mElements[ i ] = *e;
	assert( (*e)->type()==mType );
	
	*e = 0;
}


void CompositeArrayElement::toString( OStringStream* o, int indent, const RefString& name ) const {
	//開始タグ
	for ( int i = 0; i < indent; ++i ){
		*o << '\t';
	}
	*o << "<Array";
	if ( name.size() > 0 ){
		assert( mName==name );
		*o << " name=\"";
		o->write( name.get(), name.size() );
		*o << "\"";
	}
	//配列サイズ出力
	*o << " size=\"";
	for ( int i = 0; i < mSizes.size(); ++i ){
		*o << mSizes[ i ];
		if ( i < mSizes.size() - 1 ){
			*o << ',';
		}
	}
	*o << "\">" << endl;
	//中身
	RefString nullString; //配列の各要素は名前を持たない
	for ( int i = 0; i < mElements.size(); ++i ){
		mElements[ i ]->toString( o, indent+1, nullString );
	}
	//終了タグ
	for ( int i = 0; i < indent; ++i ){
		*o << '\t';
	}
	*o << "</Array>" << endl;
}

PrimitiveArrayElement::PrimitiveArrayElement( Array< int >& sizes, const RefString& type, const RefString& name ) :
mSizes( sizes.size() ),
mType( type ),
mName( name )
{
	int n = 1;
	for ( int i = 0; i < mSizes.size(); ++i ){
		mSizes[ i ] = sizes[ i ];
		n *= sizes[ i ];
	}
	mElements.setSize( n );
	mChildren.setSize( n );
}

PrimitiveArrayElement::~PrimitiveArrayElement(){}

void PrimitiveArrayElement::setElement( int i, const RefString& e ){ //この添え字は一次元化した添え字
	mElements[ i ] = e;
	mChildren[ i ] = std::make_shared<PrimitiveElement>( e, mName, mType );
}

void PrimitiveArrayElement::toString( OStringStream* o, int indent, const RefString& name ) const {
	//開始タグ
	for ( int i = 0; i < indent; ++i ){
		*o << '\t';
	}
	*o << "<Array";
	if ( name.size() > 0 ){
		assert( name==mName );
		*o << " name=\"";
		o->write( mName.get(), mName.size() );
		*o << "\"";
	}
	//配列サイズ出力
	*o << " size=\"";
	for ( int i = 0; i < mSizes.size(); ++i ){
		*o << mSizes[ i ];
		if ( i < mSizes.size() - 1 ){
			*o << ',';
		}
	}
	*o << "\">" << endl;
	for ( int i = 0; i < mElements.size(); ++i ){
		for ( int j = 0; j < indent + 1; ++j ){
			*o << '\t';
		}
		*o << "<";
		o->write( mType.get(), mType.size() );
		*o << " value=\"";
		o->write( mElements[ i ].get(), mElements[ i ].size() );
		*o << "\"/>" << endl;
	}
	//終了タグ
	for ( int i = 0; i < indent; ++i ){
		*o << '\t';
	}
	*o << "</Array>" << endl;
}

//CompositeElement
CompositeElement::CompositeElement( const Template* t, int childNumber, const RefString& name ) : 
mTemplate( t ),
mChildren( childNumber ),
mName( name ){
}

CompositeElement::~CompositeElement(){
}

void CompositeElement::setChild( int i, const ElementSharedPtr &c ){ //所有権はこっちに移る
	mChildren[ i ] = c;
}

Element* CompositeElement::child( int i ){ 
	return mChildren[ i ].get(); 
}

int CompositeElement::childNumber() const {
	return mChildren.size();
}

void CompositeElement::toString( OStringStream* o, int indent, const RefString& name ) const {
	//開始タグ
	for ( int i = 0; i < indent; ++i ){
		*o << '\t';
	}
	*o << "<";
	const RefString& type = *mTemplate->getType();
	o->write( type.get(), type.size() );

	//if(mName!=name){
	//	TRACE1( "mName : %s\n", std::string( mName.get(), mName.size() ).c_str() );
	//	TRACE1( "name : %s\n", std::string( name.get(), name.size() ).c_str() );
	//}

	assert(mName==name);

	if ( mName.size() > 0 ){
		*o << " name=\"";
		o->write( mName.get(), mName.size() );
		*o << "\"";
	}else if ( name.size() > 0 ){
		assert(false);
		*o << " name=\"";
		o->write( name.get(), name.size() );
		*o << "\"";
	}
	*o << ">" << endl;
	//中身
	for ( int i = 0; i < mChildren.size(); ++i ){
		const ElementSharedPtr& child= mChildren[i];
		
		//古いバージョンと整合(assert)を取るために無駄だがやってる。
		RefString nullString;
		const RefString* name = mTemplate->getChildName( i );
		if ( !name ){ //拡張部分は無名なのでこの処置が必要
			name = &child->name();
		}
		
		assert( child->name() == *name );
		child->toString( o, indent+1, *name );
	}
	//終了タグ
	for ( int i = 0; i < indent; ++i ){
		*o << '\t';
	}
	*o << "</";
	o->write( type.get(), type.size() );
	*o << ">" << endl;
}

const RefString& CompositeElement::type()
{
	return  *(mTemplate->getType()); 
}

ReferenceElement::ReferenceElement( const RefString& name ) : mName( name ){
}

ReferenceElement::~ReferenceElement(){
}

void ReferenceElement::toString( OStringStream* o, int indent, const RefString& ) const {
	//開始タグ
	for ( int i = 0; i < indent; ++i ){
		*o << '\t';
	}
	*o << "<Reference name=\"";
	o->write( mName.get(), mName.size() );
	*o << "\"/>";
}


void PrimitiveElement::toString( OStringStream* o, int indent, const RefString& name ) const{
	for ( int j = 0; j < indent + 1; ++j ){
		*o << '\t';
	}
	*o << "<";
	o->write( mType.get(), mType.size() );
	
	*o << " name=\"";
	o->write( mName.get(), mName.size() );
	*o << "\"";

	*o << " value=\"";
	o->write( mData.get(), mData.size() );
	*o << "\"/>" << endl;
}

} //namespace XFile

