#pragma once

namespace Camera {


class ICamera {
public:
	ICamera(){};
	virtual ~ICamera(){};

	virtual void update( float elapsedTime )=0;
};
} // end namespace Camera