#pragma once

#include "trdCamera.hpp"
#include "trdSettings.hpp"
#include "trColorBuffer.hpp"
#include "trDepthBuffer.hpp"
#include "trdTextureMap.hpp"
#include "trdModel.hpp"
#include "trdRenderThread.hpp"
#include <memory>

namespace trd
{
	class RenderManager
	{
	public:
		                                           RenderManager(const Settings& settings);
		                                           ~RenderManager();

		void                                       draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer);

	private:
		void                                       initThreads(const size_t numThreads);
		void                                       killThreads();
		void                                       renderThreadFunction(const size_t threadIndex);

	private:
		const Settings&                            m_settings;
		TextureMap                                 m_textureMap;
		MeshMap                                    m_meshMap;
		tf::Vector<Model>                          m_models;
		std::vector<std::unique_ptr<RenderThread>> m_threads;
		const Camera*                              m_camera;
		tr::ColorBuffer*                           m_colorBuffer;
		tr::DepthBuffer*                           m_depthBuffer;

	};
}