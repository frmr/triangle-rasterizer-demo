#include "trdPointLight.hpp"

#include <cassert>

trd::PointLight::PointLight(const Vector3& color, const Vector3& position, const float attenuation) :
	Light(color),
	m_position(position),
	m_attenuation(attenuation)
{
	assert(attenuation > 0.0f);
}

const tr::QuadVec3& trd::PointLight::getPosition() const
{
	return m_position;
}

const tr::QuadFloat& trd::PointLight::getAttenuation() const
{
	return m_attenuation;
}
