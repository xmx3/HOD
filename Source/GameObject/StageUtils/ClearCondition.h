#ifndef __GAMEOBJECT_STAGE_CLEAR_CONDITION__
#define __GAMEOBJECT_STAGE_CLEAR_CONDITION__

#include<memory>

namespace GameLib{
	namespace PseudoXml{
		class Document;
	}
}

namespace GameObject{
namespace StageUtils{
namespace ClearCondition {

class ICondition{
public:
	virtual ~ICondition(){}
	virtual bool is()const=0;
	virtual void debugPrint()const=0;
};

typedef std::shared_ptr<ICondition> ConditionSharedPtr;

static ConditionSharedPtr create( const GameLib::PseudoXml::Document &d );

}//end namespace ClearCondition
}//end namespace StageUtils
}//end namespace GameObject


/*
int main(int argc, char const* argv[])
{
	using namespace GameLib::PseudoXml;
	using GameLib::RefString;

	std::ifstream ifs;
	ifs.open("test.xml");
	std::string txt;
	while( !ifs.eof() ){
		char line[64];
		ifs.getline( line, 64, '\n' );
		txt.append(line);
		txt.append("\n");
	}
	// std::cout << txt << std::endl;;
	
	Document d = Document::create( txt.c_str(), txt.size() );
	if( d.isError() ){
		std::cout << "error\n";
		return 0;
	}
	ConstElement e = d.child(0);
	RefString name( e.name() );

	ConditionSharedPtr root = Condition::create( e );
	
	if( root->is() ){
		std::cout << "true\n";
	} else {
		std::cout << "false\n";
	}
	root->debugPrint();
	return 0;
}
*/


#endif //__GAMEOBJECT_STAGE_CLEAR_CONDITION__