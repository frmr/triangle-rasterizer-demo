#pragma once

#include "trdCamera.hpp"
#include "trdSettings.hpp"
#include "trColorBuffer.hpp"
#include "trDepthBuffer.hpp"
#include "trdTextureMap.hpp"
#include "trdModel.hpp"

namespace trd
{
	class RenderManager
	{
	public:
		                         RenderManager(const Settings& settings);

		void                     draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer);

	private:
		void                     renderThread(const size_t threadIndex, const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const;

	private:
		const Settings&          m_settings;
		TextureMap               m_textureMap;
		MeshMap                  m_meshMap;
		tf::Vector<Model>        m_models;
	};
}