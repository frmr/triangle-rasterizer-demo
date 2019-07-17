#include "trdLight.hpp"

trd::Light::Light(const Vector3& color) :
	m_color(color)
{
}

Vector3 trd::Light::getColor() const
{
	return m_color;
}
