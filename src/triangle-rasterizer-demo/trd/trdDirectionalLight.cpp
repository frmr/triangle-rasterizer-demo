#include "trdDirectionalLight.hpp"

trd::DirectionalLight::DirectionalLight(const Vector3& color, Vector3 direction) :
	Light(color),
	m_direction(direction.normalize())
{
}

const Vector3& trd::DirectionalLight::getDirection() const
{
	return m_direction;
}
