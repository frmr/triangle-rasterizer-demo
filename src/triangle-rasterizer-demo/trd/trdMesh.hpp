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
		                        Mesh(const tf::String& filename, trd::TextureMap& textureMap);

		void                    draw(const Vector3& cameraPosition, const bool sort, tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const;

	private:
		void                    loadObj(const tf::String& filename, TextureMap& textureMap);

	private:
		std::vector<tr::Vertex> m_vertices;
		std::vector<Vector4>    m_faceMidPoints;
		const tr::Texture*      m_texture;
	};
}