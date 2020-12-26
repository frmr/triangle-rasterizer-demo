#pragma once

#include "trdLight.hpp"

namespace trd
{
	class DirectionalLight : public Light
	{
	public:
		                    DirectionalLight(const Vector3& color, Vector3 direction);

		const tr::QuadVec3& getDirection() const;

	private:
		tr::QuadVec3        m_direction;
	};
}