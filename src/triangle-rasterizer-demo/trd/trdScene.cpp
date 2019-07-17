#include "trdScene.hpp"

trd::Scene::Scene() :
	m_textureMap(),
	m_meshMap(m_textureMap)
{
	createScene();
}

void trd::Scene::draw(const Camera& camera, tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const
{
	shader.setLights(m_lights);

	for (const Model& model : m_opaqueModels)
	{
		model.draw(camera, rasterizer, shader, colorBuffer, depthBuffer);
	}

	for (const Model& model : m_opaqueModels)
	{
		model.draw(camera, rasterizer, shader, colorBuffer, depthBuffer);
	}
}

void trd::Scene::createScene()
{
	m_opaqueModels.emplace_back("test.obj", m_meshMap, Vector3(), Vector3());

	m_lights.addLight(AmbientLight(Vector3(0.5f, 0.5f, 0.5f)));
}
