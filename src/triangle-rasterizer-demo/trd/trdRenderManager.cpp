#include "trdRenderManager.hpp"
#include <thread>

trd::RenderManager::RenderManager(const Settings& settings, const Scene& scene) :
	m_settings(settings),
	m_scene(scene)
{
}

trd::RenderManager::~RenderManager()
{
	killThreads();
}

void trd::RenderManager::draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer)
{
	colorBuffer.fill(tr::Color(0, 0, 0, 255));
	depthBuffer.fill(1.0f);

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
		m_threads.emplace_back(new RenderThread(i, m_settings, m_scene));
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
