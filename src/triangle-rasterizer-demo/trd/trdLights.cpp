#include "trdLights.hpp"

void trd::Lights::addLight(const AmbientLight& light)
{
	m_ambientLights.push_back(light);
}

void trd::Lights::addLight(const DirectionalLight& light)
{
	m_directionalLights.push_back(light);
}

void trd::Lights::addLight(const PointLight& light)
{
	m_pointLights.push_back(light);
}

const std::vector<trd::AmbientLight>& trd::Lights::getAmbientLights() const
{
	return m_ambientLights;
}

const std::vector<trd::DirectionalLight>& trd::Lights::getDirectionalLights() const
{
	return m_directionalLights;
}

const std::vector<trd::PointLight>& trd::Lights::getPointLights() const
{
	return m_pointLights;
}
