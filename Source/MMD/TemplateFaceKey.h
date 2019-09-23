#ifndef __TEMPLATEFACE_KEY_H__
#define __TEMPLATEFACE_KEY_H__
#include <map>
#include <assert.h>
#include "MMDMacro.h"
#include<string>
#include<memory>
#include<map>
#include"helper/MyOutputDebugString.h"

namespace MMD {


	class TemplateFaceKey {
	public:
		typedef std::map< float, float > MapType;
		TemplateFaceKey()
		{
			map_.reset(new MapType);
		}
		//explicit TemplateFaceKey(const char *name)
		//	:name_(std::string(name))
		//{
		//	map_.reset( new MapType );
		//}
		//createFaceKey(Face* pFaces, unsigned long size );

		virtual ~TemplateFaceKey()
		{}

		void insert(const float &time, const float &weight) {
			//assert( map_->find(time) == map_->end() && "time must be unique." );
			bool b = map_->insert(std::make_pair(time, weight)).second;
			if (b == false) {
				//TRACE3( "cannot insert, because time is doubled. animation:%s, time:%f, weight:%f\n", name_.c_str(), time, weight);
			}
			//assert( b && "not unique" );
		}

		void setName(const std::string & name) {
			name_ = name;
		}
		void shrinkToFit()const {
			//map_->shrink_to_fit();
		}

		const char* getName()const { return name_.c_str(); }

		bool operator<(const TemplateFaceKey &right)const {
			return name_ < right.name_;
		}
		bool operator<(const std::string & right)const {
			return name_ < right;
		}

		std::shared_ptr< MapType > getMap()const {
			return map_;
		}
	private:
		DISALLOW_COPY_AND_ASSIGN(TemplateFaceKey);
	private:
		std::shared_ptr< MapType > map_;
		std::string name_;
	};
}
#endif//__TEMPLATEFACE_KEY_H__