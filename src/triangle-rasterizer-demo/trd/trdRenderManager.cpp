#include "trdRenderManager.hpp"
#include <thread>

trd::RenderManager::RenderManager(const Settings& settings) :
	m_settings(settings)
{
	m_textureMap.add("data/textures/test.png");
	m_meshMap.add("test.obj", m_textureMap);

	m_models.emplace_back("test.obj", m_meshMap, Vector3(), Vector2());
}

void trd::RenderManager::draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer)
{
	std::list<std::thread> threads;

	for (size_t i = 0; i < m_settings.getNumThreads(); ++i)
	{
		threads.emplace_back(&RenderManager::renderThread, this, i, std::ref(camera), std::ref(colorBuffer), std::ref(depthBuffer));
	}

	for (std::thread& thread : threads)
	{
		thread.join();
	}
}

void trd::RenderManager::renderThread(const size_t threadIndex, const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const
{
	tr::Rasterizer<Shader> rasterizer;
	Shader                 shader;

	rasterizer.setInterlace(threadIndex, m_settings.getNumThreads());
	rasterizer.setCullFaceMode(tr::CullFaceMode::Back);
	rasterizer.setPrimitive(tr::Primitive::Triangles);
	rasterizer.setDepthTest(true);
	rasterizer.setTextureMode(m_settings.getTextureMode());
	shader.setRenderMode(m_settings.getRenderMode());

	for (const Model& model : m_models)
	{
		model.draw(camera, rasterizer, shader, colorBuffer, depthBuffer);
	}
}
