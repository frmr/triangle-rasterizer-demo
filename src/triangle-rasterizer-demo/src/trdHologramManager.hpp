#pragma once

#include "trdModel.hpp"
#include "trdLightComponent.hpp"
#include <vector>
#include <map>

namespace trd
{
	class HologramManager
	{
	public:
		                                HologramManager(MeshMap& meshMap);

		void                            queueHologram(const Vector3& cameraPosition, tr::Rasterizer<Shader>& rasterizer, Shader& shader) const;
		void                            update(const float frameTime);
		PointLight                      getLight() const;

	private:
		void                            loadModels(MeshMap& meshMap);
		void                            loadLightModels(MeshMap& meshMap);
		void                            loadHologramModels(MeshMap& meshMap);
		void                            updateHologram();

	private:
		std::vector<Model>              m_holograms;
		std::vector<Vector3>            m_lightColors;
		std::map<LightComponent, Model> m_lightModels;
		float                           m_time;
		size_t                          m_index;
		float                           m_interpolationRatio;
		float                           m_height;
		float                           m_scale;
		float                           m_alpha;
	};
}