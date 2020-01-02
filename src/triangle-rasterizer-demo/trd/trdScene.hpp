#pragma once

#include "trRasterizer.hpp"
#include "trdShader.hpp"
#include "trdModel.hpp"
#include "trdMeshMap.hpp"
#include "trdLights.hpp"
#include "trdHologramManager.hpp"

namespace trd
{
	class Scene
	{
	public:
		                   Scene();

		void               draw(const Camera& camera, tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const;
		void               update(const Vector3& cameraPosition, const float frameTime, const float deltaTime);

	private:
		void               createScene();

	private:
		TextureMap         m_textureMap;
		MeshMap            m_meshMap;
		std::vector<Model> m_opaqueModels;
		std::vector<Model> m_translucentModels;
		HologramManager    m_hologramManager;
		Lights             m_lights;
	};
}