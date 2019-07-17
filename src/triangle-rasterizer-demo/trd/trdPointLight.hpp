#pragma once

#include "trdLight.hpp"

namespace trd
{
	class PointLight : public Light
	{
	public:
		        PointLight(const Vector3& color, const Vector3& position, const float attenuation);

		Vector3 getPosition() const;
		float   getAttenuation() const;

	private:
		Vector3 m_position;
		float   m_attenuation;
	};
}