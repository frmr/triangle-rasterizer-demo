#pragma once

#include "trdLight.hpp"

namespace trd
{
	class AmbientLight : public Light
	{
	public:
		AmbientLight(const Vector3& color);
	};
}