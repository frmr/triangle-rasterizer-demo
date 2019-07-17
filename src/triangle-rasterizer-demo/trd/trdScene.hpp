#pragma once

#include "trRasterizer.hpp"
#include "trdShader.hpp"
#include "trdModel.hpp"
#include "trdMeshMap.hpp"
#include "trdLights.hpp"

namespace trd
{
	class Scene
	{
	public:
		                   Scene();

		void               draw(const Camera& camera, tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const;

	private:
		void               createScene();

	private:
		TextureMap         m_textureMap;
		MeshMap            m_meshMap;
		std::vector<Model> m_opaqueModels;
		std::vector<Model> m_translucentModels;
		Lights             m_lights;
	};
}