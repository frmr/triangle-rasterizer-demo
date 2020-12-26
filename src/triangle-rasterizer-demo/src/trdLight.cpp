#include "trdLight.hpp"

trd::Light::Light(const Vector3& color) :
	m_color(color.z, color.y, color.x)
{
}

const tr::QuadVec3& trd::Light::getColor() const
{
	return m_color;
}
