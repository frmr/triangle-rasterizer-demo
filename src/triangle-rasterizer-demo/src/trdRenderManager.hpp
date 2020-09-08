#pragma once

#include "trdTextureMap.hpp"
#include "trdModel.hpp"
#include "trdScene.hpp"
#include "trdSettings.hpp"
#include <memory>

namespace trd
{
	class RenderManager
	{
	public:
		                       RenderManager(const Settings& settings, const Scene& scene);

		void                   draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer);

	private:
		void                   setTextureMode();

	private:
		const Settings&        m_settings;
		const Scene&           m_scene;
		tr::Rasterizer<Shader> m_rasterizer;
		Shader                 m_shader;
	};
}