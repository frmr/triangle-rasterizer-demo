#pragma once

#include "trdLight.hpp"

namespace trd
{
	class DirectionalLight : public Light
	{
	public:
		        DirectionalLight(const Vector3& color, Vector3 direction);

		Vector3 getDirection() const;

	private:
		Vector3 m_direction;
	};
}