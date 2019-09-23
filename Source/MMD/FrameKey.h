#ifndef __FRAME_KEY_H__
#define __FRAME_KEY_H__
#include <d3dx9.h>
#include <vector>
#include <map>
#include <assert.h>

#include "MMDMacro.h"

namespace MMD {
	class Animation;
	//Frameをボーンにリネームしたからここもリネームするべき
	class FrameKey {
	public:
		typedef std::pair<D3DXVECTOR3, D3DXQUATERNION> Vec3AndQuat;
		typedef std::pair<float, Vec3AndQuat > MapPair;
		typedef std::map< float, Vec3AndQuat > Map;

		//FrameKey();
		FrameKey(const char *pBoneName, unsigned int index)
			:boneIndex_(index)
		{
			int strSize = strlen(pBoneName);
			name_ = new char[strSize + 1];
			strcpy(name_, pBoneName);


		}
		virtual ~FrameKey()
		{
			SAFE_DELETE_ARRAY(name_);
			map_.clear();
			map_.swap(map_);
		}

		void addFrameKey(const float &time,
			const D3DXVECTOR3 &pos,
			const D3DXQUATERNION &q)
		{
			assert(map_.find(time) == map_.end() && "time must be unique.");
			Vec3AndQuat vq(pos, q);

			map_.insert(MapPair(time, vq));
		}

		void getPosAndQuat(
			std::map< float, Vec3AndQuat >::iterator &it,
			D3DXVECTOR3 *pPos,
			D3DXQUATERNION *pQ)
		{
			*pPos = it->second.first;
			*pQ = it->second.second;
		}

		const char* getName() const { return name_; }

	private:
		DISALLOW_COPY_AND_ASSIGN(FrameKey);
	private:
		std::map< float, Vec3AndQuat > map_;
		char* name_;
		unsigned int boneIndex_;
		friend class Animation;
	};
}
#endif //__FRAME_KEY_H__
