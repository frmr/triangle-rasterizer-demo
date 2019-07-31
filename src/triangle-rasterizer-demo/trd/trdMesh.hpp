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

		void                    draw(tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const;

	private:
		void                    loadObj(const tf::String& filename, const TextureMap& textureMap);

	private:
		std::vector<tr::Vertex> m_vertices;
		const tr::Texture*      m_texture;
	};
}