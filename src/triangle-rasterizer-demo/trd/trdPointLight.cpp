#include "trdPointLight.hpp"

trd::PointLight::PointLight(const Vector3& color, const Vector3& position, const float attenuation) :
	Light(color),
	m_position(position),
	m_attenuation(attenuation)
{
}

Vector3 trd::PointLight::getPosition() const
{
	return m_position;
}

float trd::PointLight::getAttenuation() const
{
	return m_attenuation;
}
