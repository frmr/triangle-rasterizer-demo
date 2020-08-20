#pragma once

#include "trdAmbientLight.hpp"
#include "trdDirectionalLight.hpp"
#include "trdPointLight.hpp"
#include <vector>

namespace trd
{
	class Lights
	{
	public:
		void                                 addLight(const AmbientLight& light);
		void                                 addLight(const DirectionalLight& light);
		void                                 addLight(const PointLight& light);

		const std::vector<AmbientLight>&     getAmbientLights() const;
		const std::vector<DirectionalLight>& getDirectionalLights() const;
		const std::vector<PointLight>&       getPointLights() const;

	private:
		std::vector<AmbientLight>            m_ambientLights;
		std::vector<DirectionalLight>        m_directionalLights;
		std::vector<PointLight>              m_pointLights;
	};
}