#ifndef INCLUDED_XFILE_ELEMENT_H
#define INCLUDED_XFILE_ELEMENT_H

#include <GameLib/Base/RefString.h>
#include <GameLib/Base/Array.h>
#include <GameLib/Base/AutoPtr.h>
#include <GameLib/Base/OStringStream.h>
#include<memory>
#include<string>
#include<assert.h>
#include<boost/lexical_cast.hpp>

namespace XFile{

using namespace std;
using namespace GameLib;
class Template;
class Element;
typedef std::shared_ptr<Element> ElementSharedPtr;


//データ型
class Element{
public:
	Element();
	virtual ~Element();
	virtual void toString( OStringStream*, int indent, const RefString& name ) const = 0;
	
	virtual int childNumber() const{
		assert(false);
		return 0;
	}
	
	virtual Element* child( int i )
	{
		return 0;
	}
	
	virtual const RefString & type()=0;
	virtual const RefString & name()=0;
private:
	void operator=( const Element& ); //禁止
	Element( const Element& ); //禁止
};

class PrimitiveElement : public Element{
public:	
	PrimitiveElement(
		const RefString &data,
		const RefString &name,
		const RefString &type
	)
	:mData(data),
	mName(name),
	mType(type)
	{}

	virtual ~PrimitiveElement(){}

	virtual void toString( OStringStream*, int indent, const RefString& name ) const;

	const RefString & data(){
		return mData;
	}

	int size(){
		return mData.size();
	}

	virtual const RefString & type(){
		return mType;
	}
	virtual const RefString & name(){
		return mName;
	}

	template<class T>
	T getValue()const{
		//return boost::lexical_cast<T>( std::string(mData.get(), mData.size() ) );//boostをバージョンアップしたので
		return boost::lexical_cast<T>( mData.get(), mData.size() );
	}
	
	
private:
	void operator=( const PrimitiveElement & );
	PrimitiveElement( const PrimitiveElement & );

	RefString mData;
	RefString mName;
	RefString mType;
};

class CompositeElement : public Element{
public:
	CompositeElement( const Template* t, int childNumber, const RefString& name );
	~CompositeElement();
	void setChild( int i, const ElementSharedPtr& c );
	virtual Element* child( int i );
	void toString( OStringStream*, int indent, const RefString& name ) const;
	virtual int childNumber() const;
	virtual const RefString & type();
	virtual const RefString & name(){
		return mName;
	}
	const Template* getTemplate()const{
		return mTemplate;
	}
private:
	const Template* mTemplate;
	Array< ElementSharedPtr > mChildren;

	const RefString mName; //複合型には名前があることがある。
};

class CompositeArrayElement : public Element{
public:
	CompositeArrayElement( Array< int >& sizes, const RefString& type, const RefString& name );
	~CompositeArrayElement();
	void setElement( int i, ElementSharedPtr* e );

	void toString( OStringStream*, int indent, const RefString& name ) const;

	virtual int childNumber() const{
		return mElements.size();
	}
	virtual Element* child( int i ){
		return mElements[i].get();
	}
	virtual const RefString & type(){
		return mType;
	}
	virtual const RefString & name(){
		return mName;
	}

private:
	Array< int > mSizes;
	Array< ElementSharedPtr > mElements;
	const RefString mName;
	const RefString mType;
};

class PrimitiveArrayElement : public Element{
public:
	PrimitiveArrayElement( Array< int >& sizes, const RefString& typeName, const RefString& name );
	~PrimitiveArrayElement();
	void setElement( int i, const RefString& );

	void toString( OStringStream*, int indent, const RefString& name ) const;

	virtual int childNumber() const{
		return mChildren.size();
	}

	virtual Element* child( int i ){
		return mChildren[i].get();
	}

	virtual const RefString & type(){
		return mType;
	}
	virtual const RefString & name(){
		return mName;
	}
	//面の数
	int faceNumber( int i )const{
		return mSizes[i];
	}
private:
	Array< int > mSizes;
	Array< RefString > mElements; //配列がプリミティブ型ならこっちを使う。
	Array< std::shared_ptr<PrimitiveElement> > mChildren;
	const RefString mType;
	const RefString mName;
};

class ReferenceElement : public Element{
public:
	ReferenceElement( const RefString& name );
	~ReferenceElement();

	void toString( OStringStream*, int indent, const RefString& name ) const;
	virtual const RefString & name(){
		return mName;
	}
	virtual const RefString & type(){
		assert(false);
		static RefString nullString;
		return nullString;
	}
private:
	const RefString mName; //複合型には名前があることがある。
};



} //namespace XFile

#endif
