#pragma once
#include<algorithm>
namespace ContainerHelper{

struct safeDelete_func{
	template<typename T>
	void operator()(T*& ptr) const
	{
		if(ptr){
			delete ptr;
			ptr=NULL;
		}
	}
};
	
class safeDeleteAll
{
public:
	template <typename T>
	void operator()(std::vector<T> &v) {
		std::for_each( v.begin(), v.end(), safeDelete_func() );	
		v.clear();
		v.shrink_to_fit();;
	}
};


template <typename T>
void operator|(T &source, safeDeleteAll f)
{
	return f(source);
}

}