#pragma once

#include "trdTextureMap.hpp"
#include "trdModel.hpp"
#include "trdRenderThread.hpp"
#include <memory>

namespace trd
{
	class RenderManager
	{
	public:
		                                          RenderManager(const Settings& settings, const Scene& scene);
		                                          ~RenderManager();

		void                                      draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer);

	private:
		void                                      initThreads(const size_t numThreads);
		void                                      killThreads();
		

	private:
		const Settings&                           m_settings;
		const Scene&                              m_scene;
		tf::Vector<std::unique_ptr<RenderThread>> m_threads;
	};
}