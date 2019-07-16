#include "trdRenderThread.hpp"
#include "trdShader.hpp"
#include "tr.hpp"

trd::RenderThread::RenderThread(const size_t threadIndex, const Settings& settings, const tf::Vector<Model>& models) :
	m_threadIndex(threadIndex),
	m_settings(settings),
	m_models(models),
	m_thread(&RenderThread::threadFunction, this),
	m_conditionVariable(),
	m_mutex(),
	m_quit(false),
	m_draw(false),
	m_camera(nullptr),
	m_colorBuffer(nullptr),
	m_depthBuffer(nullptr)
{
}

trd::RenderThread::~RenderThread()
{
	kill();
}

void trd::RenderThread::draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer)
{
	m_camera      = &camera;
	m_colorBuffer = &colorBuffer;
	m_depthBuffer = &depthBuffer;
	m_draw        = true;

	m_conditionVariable.notify_one();
}

void trd::RenderThread::wait()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_conditionVariable.wait(lock, [&]{ return !m_draw; });
}

void trd::RenderThread::kill()
{
	m_quit = true;
	m_conditionVariable.notify_one();

	try
	{
		m_thread.join();
	}
	catch (const std::system_error&)
	{
	}
}

void trd::RenderThread::threadFunction()
{
	tr::Rasterizer<Shader> rasterizer;
	Shader                 shader;

	rasterizer.setInterlace(m_threadIndex, m_settings.getNumThreads());
	rasterizer.setCullFaceMode(tr::CullFaceMode::Back);
	rasterizer.setPrimitive(tr::Primitive::Triangles);
	rasterizer.setDepthTest(true);

	while (!m_quit)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_conditionVariable.wait(lock, [&]{ return m_draw || m_quit; });

		if (m_draw)
		{
			rasterizer.setTextureMode(m_settings.getTextureMode());
			shader.setRenderMode(m_settings.getRenderMode());

			for (const Model& model : m_models)
			{
				model.draw(*m_camera, rasterizer, shader, *m_colorBuffer, *m_depthBuffer);
			}

			m_draw = false;
			m_conditionVariable.notify_one();
		}
	}
}
