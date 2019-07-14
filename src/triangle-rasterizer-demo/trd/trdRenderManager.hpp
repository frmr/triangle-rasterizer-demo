#pragma once

#include "trdRenderThread.hpp"

namespace trd
{
	class RenderManager
	{
	public:
		                         RenderManager(const Settings& settings);

		void                     draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer);

	private:
		void                     initThreads(const size_t numThreads);

	private:
		const Settings&          m_settings;
		TextureMap               m_textureMap;
		MeshMap                  m_meshMap;
		tf::Vector<Model>        m_models;
		std::list<RenderThread> m_threads;
	};
}