#include"TemplateBoneKey.h"
#include<assert.h>
#include"OneFrameData.h"

namespace MMD {

	TemplateBoneKey::TemplateBoneKey()
	{
		frames_.reset(new boost::container::flat_set<OneFrameData>);
	}

	TemplateBoneKey::~TemplateBoneKey() {
	}

	//名前はcopy、assignにするべきかな？
	//名前がセットだけだと味気ないか？
	void TemplateBoneKey::setName(const std::string &boneName) {
		name_ = boneName;
	}

	void TemplateBoneKey::insert(const OneFrameData & frame)
	{
		auto ib = frames_->insert(frame);
		assert(ib.second);//2重に保存することはないはず
	}


	void TemplateBoneKey::shrinkToFit()const {
		assert(frames_->capacity() == frames_->size());
		//わざわざshrinkToFitしなくていいようにあらかじめメモリ確保しておけ
		frames_->shrink_to_fit();
	}

	void TemplateBoneKey::reserve(unsigned int size)const {
		frames_->reserve(size);
	}

	const char* TemplateBoneKey::getName() const {
		return name_.c_str();
	}

	bool TemplateBoneKey::operator<(const TemplateBoneKey & right)const {
		return name_ < right.name_;
	}
	bool TemplateBoneKey::operator<(const std::string & right)const {
		return name_ < right;
	}

	const std::shared_ptr< boost::container::flat_set<OneFrameData> >&
		TemplateBoneKey::getFrames()const {
		return frames_;
	}
}