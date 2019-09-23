#ifndef __CONTAINERHELPER_H__
#define __CONTAINERHELPER_H__

#include <vector>
#include <algorithm>
#include <iostream>

struct Deleter{
	template<typename T>
	void operator()(T*& ptr) const
	{
		if(ptr){
			delete ptr;
			ptr=NULL;
		}
	}
};

class name_is
{
public:
	name_is(const char* name):target_(name){}

	template<typename T>
	bool operator()(T *obj) const
	{
		return strcmp(obj->getName(), target_) == 0;
	}
	template<typename T>
	bool operator()(const T &obj) const
	{
		return strcmp(obj.getName(), target_) == 0;
	}

private:
	const char* target_;
};

class find_name
{	
public:
	find_name(const char* name):target_(name){}

	template <typename T>
	typename std::vector<T>::iterator operator()(std::vector<T> &source) const
	{
		return std::find_if(source.begin(), source.end(), name_is(target_));
	}

	//dynamic array用
	template <typename T>
	typename T* operator()( T* source, unsigned long size ) const
	{
		T* t = std::find_if( source, source+size, name_is(target_));
		if( t != source+size ){
			return t;
		} else {
			return NULL;
		}
	}

private:
	const char* target_;	
};

class shrink_to_fit
{
public:
	template <typename T>
	void operator()(std::vector<T> &v) const {
		std::vector<T>(v).swap(v);
	}
};

class destroy
{
public:
	template <typename T>
	void operator()(std::vector<T> &v) {
		std::for_each( v.begin(), v.end(), Deleter() );	
		v.clear();
		std::vector<T>(v).swap(v);
	}
};

//拡張メンバー関数
template <typename T>
typename std::vector<T>::iterator operator|(std::vector<T> &source, find_name f)
{
	return f(source);
}

//拡張メンバー関数
template <typename T>
void operator|(T &source, shrink_to_fit f)
{
	return f(source);
}

template <typename T>
void operator|(T &source, destroy f)
{
	return f(source);
}


//helper関数
template <typename T>
typename std::vector<T>::iterator findNameInVector(std::vector<T> &source, const char* pName )
{
	find_name func = find_name(pName);
	return func(source);
}

//helper関数
template <typename T>
typename T* findNameInArray( T* source, unsigned long size, const char* pName )
{
	find_name func = find_name(pName);
	return func( source, size );
}

//helper関数
template <typename T>
void shrinkVector(std::vector<T> &source)
{
  shrink_to_fit f;
	return f(source);
}
//helper関数
template <typename T>
void destroyVector(std::vector<T> &source)
{
	std::for_each( source.begin(), source.end(), Deleter() );
	source.clear();
	shrinkVector( source );
}


#endif