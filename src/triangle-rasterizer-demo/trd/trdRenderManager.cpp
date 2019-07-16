#include "trdRenderManager.hpp"
#include <thread>

trd::RenderManager::RenderManager(const Settings& settings) :
	m_settings(settings)
{
	m_textureMap.add("data/textures/test.png");
	m_meshMap.add("test.obj", m_textureMap);

	m_models.emplace_back("test.obj", m_meshMap, Vector3(), Vector2());
}

trd::RenderManager::~RenderManager()
{
	killThreads();
}

void trd::RenderManager::draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer)
{
	if (m_settings.getNumThreads() != m_threads.size())
	{
		initThreads(m_settings.getNumThreads());
	}

	for (auto& thread : m_threads)
	{
		thread->draw(camera, colorBuffer, depthBuffer);
	}

	for (auto& thread : m_threads)
	{
		thread->wait();
	}
}

void trd::RenderManager::initThreads(const size_t numThreads)
{
	killThreads();

	for (size_t i = 0; i < numThreads; ++i)
	{
		m_threads.emplace_back(new RenderThread(i, m_settings, m_models));
	}
}

void trd::RenderManager::killThreads()
{
	for (auto& thread : m_threads)
	{
		thread->kill();
	}

	m_threads.clear();
}
