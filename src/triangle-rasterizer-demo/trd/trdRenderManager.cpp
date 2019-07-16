#include "trdRenderManager.hpp"
#include <thread>

trd::RenderManager::RenderManager(const Settings& settings) :
	m_settings(settings),
	m_camera(nullptr),
	m_colorBuffer(nullptr),
	m_depthBuffer(nullptr)
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
	m_camera      = &camera;
	m_colorBuffer = &colorBuffer;
	m_depthBuffer = &depthBuffer;

	if (m_settings.getNumThreads() != m_threads.size())
	{
		initThreads(m_settings.getNumThreads());
	}

	for (auto& thread : m_threads)
	{
		thread->draw = true;
		thread->conditionVariable.notify_one();
	}

	for (auto& thread : m_threads)
	{
		std::unique_lock<std::mutex> lock(thread->mutex);

		thread->conditionVariable.wait(lock, [&]{ return thread->draw == false; });
	}
}

void trd::RenderManager::initThreads(const size_t numThreads)
{
	killThreads();

	for (size_t i = 0; i < numThreads; ++i)
	{
		m_threads.emplace_back(new RenderThread{ std::thread(&RenderManager::renderThreadFunction, this, i), std::condition_variable(), std::mutex(), false, false });
	}
}

void trd::RenderManager::killThreads()
{
	for (auto& thread : m_threads)
	{
		thread->quit = true;
		thread->conditionVariable.notify_one();

		thread->thread.join();
	}

	m_threads.clear();
}

void trd::RenderManager::renderThreadFunction(const size_t threadIndex)
{
	tr::Rasterizer<Shader> rasterizer;
	Shader                 shader;

	rasterizer.setInterlace(threadIndex, m_settings.getNumThreads());
	rasterizer.setCullFaceMode(tr::CullFaceMode::Back);
	rasterizer.setPrimitive(tr::Primitive::Triangles);
	rasterizer.setDepthTest(true);

	while (!m_threads[threadIndex]->quit)
	{
		std::unique_lock<std::mutex> lock(m_threads[threadIndex]->mutex);
		m_threads[threadIndex]->conditionVariable.wait(lock, [&]{ return m_threads[threadIndex]->draw || m_threads[threadIndex]->quit; });

		if (m_threads[threadIndex]->draw)
		{
			rasterizer.setTextureMode(m_settings.getTextureMode());
			shader.setRenderMode(m_settings.getRenderMode());

			for (const Model& model : m_models)
			{
				model.draw(*m_camera, rasterizer, shader, *m_colorBuffer, *m_depthBuffer);
			}

			m_threads[threadIndex]->draw = false;
			m_threads[threadIndex]->conditionVariable.notify_one();
		}
	}
}
