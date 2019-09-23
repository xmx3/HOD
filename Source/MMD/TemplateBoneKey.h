#ifndef __TEMPLATEBONEKEY_H__
#define __TEMPLATEBONEKEY_H__
#include<d3dx9.h>
#include"MMDMacro.h"
#include<memory>
#include<string>
#include<map>
#include<boost/container/flat_set.hpp>

namespace MMD {

	class BezierCurve;
	struct OneFrameData;

	class TemplateBoneKey {
	public:
		TemplateBoneKey();

		virtual ~TemplateBoneKey();

		//名前はcopy、assignにするべきかな？
		//名前がセットだけだと味気ないか？
		void setName(const std::string &boneName);

		void insert(const OneFrameData & frame);

		void shrinkToFit()const;

		void reserve(unsigned int size)const;

		const char* getName() const;

		bool operator<(const TemplateBoneKey & right)const;

		bool operator<(const std::string & right)const;

		const std::shared_ptr< boost::container::flat_set<OneFrameData> >&
			getFrames()const;
	private:
		DISALLOW_COPY_AND_ASSIGN(TemplateBoneKey);

		std::string name_;
		std::shared_ptr< boost::container::flat_set<OneFrameData> > frames_;
	};
}
#endif//__TEMPLATEBONEKEY_H__
