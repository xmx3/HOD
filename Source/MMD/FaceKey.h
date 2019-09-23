#ifndef __FACE_KEY_H__
#define __FACE_KEY_H__
#include <map>
#include <assert.h>
#include "MMDMacro.h"
#include<string>
#include"Face.h"
#include"TemplateFaceKey.h"

namespace MMD {
	class Face;

	class FaceKey {
	public:
		typedef std::map< float, float > MapType;//sorderd_vector作るのめんどくさい

		FaceKey()
			:face_(NULL)
		{}
		virtual ~FaceKey()
		{}
		void init(Face *face, const TemplateFaceKey &tfk) {
			face_ = face;
			map_ = tfk.getMap();
		}

		void updateFace(const float &frame) {
			assert(!map_->empty());
			face_->weight_ = 0;
			MapType::iterator it = map_->lower_bound(frame);

			if (it == map_->begin()) {
				face_->weight_ += map_->begin()->second;
			}
			else if (it == map_->end()) {
				face_->weight_ += map_->rbegin()->second;
			}
			else {

				float time1, weight1;
				time1 = it->first;
				weight1 = it->second;
				--it;
				float time0, weight0;
				time0 = it->first;
				weight0 = it->second;
				assert(time0 < time1);
				assert(time0 <= frame && frame <= time1);

				// time0 < frame <time1の条件だけどソートしてあるのでこれで十分
				float r = (time1 - frame) / (time1 - time0);
				face_->weight_ += (weight0*r + weight1*(1 - r));
			}
		}
		const char* getName()const { return face_->getName(); }
		float maxFrame()const {
			if (map_->empty()) {
				return 0.f;
			}
			else {
				return map_->rbegin()->first;
			}
		}
	private:
		DISALLOW_COPY_AND_ASSIGN(FaceKey);
	private:
		std::shared_ptr< MapType > map_;
		Face *face_;
	};
}
#endif//__FACE_KEY_H__