#include "trdScene.hpp"

trd::Scene::Scene() :
	m_textureMap(),
	m_meshMap(m_textureMap),
	m_earth("data/meshes/earth.obj", m_meshMap, Vector3(), Vector3(), true)
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

	for (const Model& model : m_translucentModels)
	{
		model.draw(camera, rasterizer, shader, colorBuffer, depthBuffer);
	}

	m_earth.draw(camera, rasterizer, shader, colorBuffer, depthBuffer);
}

void trd::Scene::update(const Vector3& cameraPosition, const float deltaTime)
{
	m_earth.setPosition(cameraPosition);
	m_opaqueModels.front().rotate(Vector3(0.0f, 0.1f * deltaTime, 0.0f));
}

void trd::Scene::createScene()
{
	m_opaqueModels.emplace_back("data/meshes/test.obj", m_meshMap, Vector3(), Vector3(), false);

	m_lights.addLight(AmbientLight(Vector3(0.1f, 0.1f, 0.1f)));
	m_lights.addLight(DirectionalLight(Vector3(0.5f, 0.5f, 0.5f), Vector3(-2.0f, 0.0f, 0.0f)));
	m_lights.addLight(PointLight(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 2.0f, 0.0f), 0.5f));
}
