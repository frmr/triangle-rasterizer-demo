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
	rasterizer.setProjectionViewMatrix(camera.getProjectionViewMatrix());

	for (const Model& model : m_opaqueModels)
	{
		model.draw(rasterizer, shader, colorBuffer, depthBuffer);
	}

	for (const Model& model : m_translucentModels)
	{
		model.draw(rasterizer, shader, colorBuffer, depthBuffer);
	}

	m_earth.draw(rasterizer, shader, colorBuffer, depthBuffer);
}

void trd::Scene::update(const Vector3& cameraPosition, const float deltaTime)
{
	m_earth.setPosition(cameraPosition);
}

void trd::Scene::createScene()
{
	m_opaqueModels.emplace_back("data/meshes/sofa.obj",	        m_meshMap, Vector3(0.0f, 0.0f,  0.0f), Vector3(0.0f,   0.0f, 0.0f), false);
	m_opaqueModels.emplace_back("data/meshes/chair.obj",        m_meshMap, Vector3(1.6f, 0.0f,  1.8f), Vector3(0.0f,  90.0f, 0.0f), false);
	m_opaqueModels.emplace_back("data/meshes/chair.obj",        m_meshMap, Vector3(1.6f, 0.0f, -1.8f), Vector3(0.0f, 270.0f, 0.0f), false);
	m_opaqueModels.emplace_back("data/meshes/window.obj",       m_meshMap, Vector3(3.0f, 0.0f,  0.0f), Vector3(0.0f,   0.0f, 0.0f), false);
	m_opaqueModels.emplace_back("data/meshes/coffee-table.obj", m_meshMap, Vector3(1.6f, 0.0f,  0.0f), Vector3(0.0f,  90.0f, 0.0f), false);

	m_opaqueModels.emplace_back("data/meshes/sofa.obj",	        m_meshMap, Vector3(0.0f, 0.0f,  6.0f), Vector3(0.0f,   0.0f, 0.0f), false);
	m_opaqueModels.emplace_back("data/meshes/chair.obj",        m_meshMap, Vector3(1.6f, 0.0f,  7.8f), Vector3(0.0f,  90.0f, 0.0f), false);
	m_opaqueModels.emplace_back("data/meshes/chair.obj",        m_meshMap, Vector3(1.6f, 0.0f,  4.2f), Vector3(0.0f, 270.0f, 0.0f), false);
	m_opaqueModels.emplace_back("data/meshes/window.obj",       m_meshMap, Vector3(3.0f, 0.0f,  6.0f), Vector3(0.0f,   0.0f, 0.0f), false);
	m_opaqueModels.emplace_back("data/meshes/coffee-table.obj", m_meshMap, Vector3(1.6f, 0.0f,  6.0f), Vector3(0.0f,  90.0f, 0.0f), false);
	
	m_lights.addLight(AmbientLight(Vector3(0.25f, 0.25f, 0.25f)));
	m_lights.addLight(DirectionalLight(Vector3(1.0f, 1.0f, 1.0f), Vector3(-2.0f, 0.0f, 0.0f)));
	m_lights.addLight(DirectionalLight(Vector3(0.25f, 0.25f, 0.25f), Vector3(1.0f, -7.0f, -0.5f)));
	m_lights.addLight(PointLight(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 2.0f, 0.0f), 0.5f));
}
