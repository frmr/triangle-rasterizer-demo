#pragma once

#include "trdModel.hpp"
#include <vector>

namespace trd
{
	class HologramManager
	{
	public:
		                     HologramManager(MeshMap& meshMap);

		void                 drawHologram(tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const;
		void                 update(const float frameTime);
		PointLight           getLight() const;

	private:
		void                 loadModels(MeshMap& meshMap);
		void                 updateHologram();

	private:
		std::vector<Model>   m_holograms;
		std::vector<Vector3> m_lightColors;
		float                m_time;
		size_t               m_index;
		float                m_height;
		float                m_scale;
	};
}