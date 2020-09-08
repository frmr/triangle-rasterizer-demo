#include "trdRenderManager.hpp"
#include <thread>

trd::RenderManager::RenderManager(const Settings& settings, const Scene& scene) :
	m_settings(settings),
	m_scene(scene)
{
}

void trd::RenderManager::draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer)
{
	depthBuffer.fill(1.0f);

	m_rasterizer.setCullFaceMode(tr::CullFaceMode::Front);
	m_rasterizer.setPrimitive(tr::Primitive::Triangles);
	m_rasterizer.setDepthTest(true);

	setTextureMode();
	m_shader.setRenderMode(m_settings.getRenderMode());
	m_shader.setBilinearFiltering(m_settings.getBilinearFiltering());

	m_scene.draw(camera, m_rasterizer, m_shader, colorBuffer, depthBuffer);
}

void trd::RenderManager::setTextureMode()
{
	if (m_settings.getTextureMode() == TextureMode::Off)
	{
		m_shader.setUseTexture(false);
	}
	else
	{
		m_shader.setUseTexture(true);
		m_rasterizer.setTextureMode(m_settings.getTextureMode() == TextureMode::Affine ? tr::TextureMode::Affine : tr::TextureMode::Perspective);
	}
}