#pragma once

#include "tr.hpp"
#include "tfString.hpp"
#include "trdShader.hpp"
#include "trdTextureMap.hpp"
#include <vector>

namespace trd
{
	class Mesh
	{
	public:
		                               Mesh(const tf::String& filename, const trd::TextureMap& textureMap);

		void                           draw(tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const;

	private:
		static std::vector<tr::Vertex> defineVertices();

	private:
		const std::vector<tr::Vertex>  m_vertices;
		const tr::Texture* const       m_texture;
	};
}