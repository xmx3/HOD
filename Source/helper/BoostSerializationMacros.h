#pragma once

#pragma warning (push)
#pragma warning( disable : 4244 )

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#pragma warning (pop) 

#include<boost/archive/text_iarchive.hpp>
#include<boost/archive/text_oarchive.hpp>

#include<boost/archive/xml_iarchive.hpp>
#include<boost/archive/xml_oarchive.hpp>

#include<boost/serialization/serialization.hpp>

#include<boost/serialization/split_member.hpp>

//class_name::serialezeを明示的にインスタンス化する
#define EXPLICITY_INSTANTIATE_SERIALIZE_FUNCTION( class_name ) \
	template void class_name::serialize< boost::archive::binary_oarchive >(boost::archive::binary_oarchive &, const unsigned int );\
	template void class_name::serialize< boost::archive::binary_iarchive >(boost::archive::binary_iarchive &, const unsigned int );\
	template void class_name::serialize< boost::archive::text_oarchive >(boost::archive::text_oarchive &, const unsigned int );\
	template void class_name::serialize< boost::archive::text_iarchive >(boost::archive::text_iarchive &, const unsigned int );\
	template void class_name::serialize< boost::archive::xml_oarchive >(boost::archive::xml_oarchive &, const unsigned int );\
	template void class_name::serialize< boost::archive::xml_iarchive >(boost::archive::xml_iarchive &, const unsigned int );


#define SPLIT_SERIALIZE_IMPL( class_name ) \
template<class Archive>\
void class_name::serialize(Archive& ar, const unsigned int version){\
    boost::serialization::split_member(ar, *this, version);\
}

//型情報要らない
#include<boost/serialization/level.hpp>
//BOOST_CLASS_IMPLEMENTATION(Status, boost::serialization::object_serializable);

