#include "trdRenderThread.hpp"

trd::RenderThread::RenderThread(const size_t threadIndex, const Settings& settings, const Scene& scene) :
	m_threadIndex(threadIndex),
	m_settings(settings),
	m_scene(scene),
	m_quit(false),
	m_draw(false),
	m_camera(nullptr),
	m_colorBuffer(nullptr),
	m_depthBuffer(nullptr),
	m_continueConditionVariable(),
	m_waitConditionVariable(),
	m_mutex(),
	m_thread(&RenderThread::threadFunction, this)
{
}

trd::RenderThread::~RenderThread()
{
	kill();
}

void trd::RenderThread::draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_camera      = &camera;
	m_colorBuffer = &colorBuffer;
	m_depthBuffer = &depthBuffer;
	m_draw        = true;

	lock.unlock();

	m_continueConditionVariable.notify_one();
}

void trd::RenderThread::wait()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_waitConditionVariable.wait(lock, [&]{ return !m_draw; });
}

void trd::RenderThread::kill()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_quit = true;

	lock.unlock();

	m_continueConditionVariable.notify_one();

	if (m_thread.joinable())
	{
		m_thread.join();
	}
}

void trd::RenderThread::threadFunction()
{
	tr::Rasterizer<Shader> rasterizer;
	Shader                 shader;

	rasterizer.setInterlace(m_threadIndex, m_settings.getNumThreads());
	rasterizer.setCullFaceMode(tr::CullFaceMode::Front);
	rasterizer.setPrimitive(tr::Primitive::Triangles);
	rasterizer.setDepthTest(true);

	while (!m_quit)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_continueConditionVariable.wait(lock, [&]{ return m_draw || m_quit; });

		if (m_draw)
		{
			setTextureMode(rasterizer, shader);
			shader.setRenderMode(m_settings.getRenderMode());
			shader.setBilinearFiltering(m_settings.getBilinearFiltering());

			m_scene.draw(*m_camera, rasterizer, shader, *m_colorBuffer, *m_depthBuffer);

			m_draw = false;

			lock.unlock();
			m_waitConditionVariable.notify_one();
		}
	}
}

void trd::RenderThread::setTextureMode(tr::Rasterizer<Shader>& rasterizer, Shader& shader)
{
	if (m_settings.getTextureMode() == TextureMode::Off)
	{
		shader.setUseTexture(false);
	}
	else
	{
		shader.setUseTexture(true);
		rasterizer.setTextureMode(m_settings.getTextureMode() == TextureMode::Affine ? tr::TextureMode::Affine : tr::TextureMode::Perspective);
	}
}
