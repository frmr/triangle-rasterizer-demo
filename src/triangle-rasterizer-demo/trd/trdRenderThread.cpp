#include "trdRenderThread.hpp"

trd::RenderThread::RenderThread(const Settings& settings, const tf::Vector<Model>& models, const size_t interlaceOffset, const size_t interlaceStep) :
	m_settings(settings),
	m_models(models),
	m_running(true),
	m_drawFrame(false),
	m_finished(true),
	m_thread(&RenderThread::threadLoop, this),
	m_camera(nullptr),
	m_colorBuffer(nullptr),
	m_depthBuffer(nullptr)
{
	m_rasterizer.setInterlace(interlaceOffset, interlaceStep);
	m_rasterizer.setCullFaceMode(tr::CullFaceMode::Back);
	m_rasterizer.setPrimitive(tr::Primitive::Triangles);
	m_rasterizer.setDepthTest(true);
}

trd::RenderThread::~RenderThread()
{
	if (m_running)
	{
		m_running = false;
		m_thread.join();
	}
}

void trd::RenderThread::drawFrame(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer)
{
	m_camera      = &camera;
	m_colorBuffer = &colorBuffer;
	m_depthBuffer = &depthBuffer;
	m_finished    = false;
	m_drawFrame   = true;
}

bool trd::RenderThread::isFinished() const
{
	return m_finished;
}

void trd::RenderThread::threadLoop()
{
	while (m_running)
	{
		if (m_drawFrame)
		{
			m_drawFrame = false;

			m_rasterizer.setTextureMode(m_settings.getTextureMode());
			m_shader.setRenderMode(m_settings.getRenderMode());

			for (const Model& model : m_models)
			{
				model.draw(*m_camera, m_rasterizer, m_shader, *m_colorBuffer, *m_depthBuffer);
			}

			m_finished = true;
		}
	}
}
