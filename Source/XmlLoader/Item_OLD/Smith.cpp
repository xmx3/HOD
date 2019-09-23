#include"Smith.h"
#include"DoubleSword.h"
#include<map>
#include"Item.h"
#include"helper/XmlHelperFuncs.h"
#include<sstream>


#include<boost/archive/xml_iarchive.hpp>

namespace Serialization{ namespace Item{

ItemSharedPtr Smith::get( const std::string & name ){
	return 0;
}

void Smith::init( const std::string &fileName ){
	using namespace boost::serialization;
	using namespace XmlHelperFuncs;
	std::istringstream iss;
	while( !iss.eof() ){
		std::string tag = advanceToNextTag( iss );
		if( tag=="DoubleSword"){
			boost::archive::xml_iarchive in_archive( iss, boost::archive::no_header );
			DoubleSword ds;
			in_archive >> make_nvp("DoubleSword",  ds );  
		} else {
			assert(false);
		}

	}
}

} }//end namespace Serialization::Item