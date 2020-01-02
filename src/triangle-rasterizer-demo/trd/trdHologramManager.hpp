#pragma once

#include "trdModel.hpp"
#include <vector>

namespace trd
{
	class HologramManager
	{
	public:
		                   HologramManager(MeshMap& meshMap);

		void               drawHologram(tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const;
		void               update(const float frameTime);

	private:
		void               loadModels(MeshMap& meshMap);

	private:
		std::vector<Model> m_holograms;
		float              m_time;
	};
}