#include "trdRenderManager.hpp"

trd::RenderManager::RenderManager(const Settings& settings) :
	m_settings(settings)
{
	m_textureMap.add("data/textures/test.png");
	m_meshMap.add("test.obj", m_textureMap);

	m_models.emplace_back("test.obj", m_meshMap, Vector3(), Vector2());

	initThreads(settings.getNumThreads());
}

void trd::RenderManager::draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer)
{
	if (size_t(m_settings.getNumThreads()) != m_threads.size())
	{
		initThreads(size_t(m_settings.getNumThreads()));
	}

	for (RenderThread& thread : m_threads)
	{
		thread.drawFrame(camera, colorBuffer, depthBuffer);
	}

	for (RenderThread& thread : m_threads)
	{
		while (!thread.isFinished())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
}

void trd::RenderManager::initThreads(const size_t numThreads)
{
	m_threads.clear();

	for (size_t i = 0; i < numThreads; ++i)
	{
		m_threads.emplace_back(m_settings, m_models, i, numThreads);
	}
}
