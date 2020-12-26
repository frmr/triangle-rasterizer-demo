#pragma once

#include "trdLight.hpp"

namespace trd
{
	class PointLight : public Light
	{
	public:
		                     PointLight(const Vector3& color, const Vector3& position, const float attenuation);

		const tr::QuadVec3&  getPosition() const;
		const tr::QuadFloat& getAttenuation() const;

	private:
		tr::QuadVec3         m_position;
		tr::QuadFloat        m_attenuation;
	};
}