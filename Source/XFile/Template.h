#ifndef INCLUDED_XFILE_TEMPLATE_H
#define INCLUDED_XFILE_TEMPLATE_H

#include <GameLib/Base/RefString.h>
#include <GameLib/Base/Array.h>
#include <GameLib/Base/AutoPtr.h>
#include "XFile/Parser.h"
#include <map>
#include <memory>

namespace XFile{

class Token;
class Element;
typedef std::shared_ptr<Element> ElementSharedPtr;
class TemplateLine;
using namespace GameLib;
using namespace std;

class CompositeElement;
class Template{
public:
	Template( RefString name, const RefString& uuid, int childNumber );
	void setChild( int i, TemplateLine** tl );
	~Template();

	int createElement( 
		ElementSharedPtr* elementOut, 
		const Array< Token >& t,
		int p,
		const Parser&,
		const RefString& name,
		map< RefString, ElementSharedPtr >* namedElements,
		int* level ) const;
	const RefString* getChildName( int index ) const;
	const RefString* getChildType( int index ) const;
	const RefString* getType() const;
private:
	void operator=( const Template& ); //‹ÖŽ~
	Template( const Template& ); //‹ÖŽ~

	int createArray(
		ElementSharedPtr* elementOut, 
		const TemplateLine& line,
		const Array< Token >& t,
		int p,
		const map< RefString, int >& arrayIndices,
		const Parser&,
		map< RefString, ElementSharedPtr >* namedElements,
		int* level ) const;
	int parseReference(
		ElementSharedPtr* elementOut,
		const Array< Token >& t,
		int p,
		map< RefString, ElementSharedPtr >* namedElements ) const;

	RefString mName;
	Array< AutoPtr< TemplateLine > > mChildren;
	const RefString mUuid;
};

} //namespace XFile

#endif
