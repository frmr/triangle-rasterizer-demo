#include "trdScene.hpp"

trd::Scene::Scene() :
	m_textureMap(),
	m_meshMap(m_textureMap),
	m_hologramManager(m_meshMap)
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

	m_hologramManager.drawHologram(rasterizer, shader, colorBuffer, depthBuffer);
}

void trd::Scene::update(const Vector3& cameraPosition, const float frameTime, const float deltaTime)
{
	m_hologramManager.update(frameTime);
}

void trd::Scene::createScene()
{
	m_opaqueModels.emplace_back("data/dome/dome.obj",             m_meshMap, Vector3(), Vector3(), false);
	m_opaqueModels.emplace_back("data/ceiling/ceiling.obj",       m_meshMap, Vector3(), Vector3(), false);
	m_opaqueModels.emplace_back("data/trim/trim.obj",             m_meshMap, Vector3(), Vector3(), false);
	m_opaqueModels.emplace_back("data/wall/wall.obj",             m_meshMap, Vector3(), Vector3(), false);
	m_opaqueModels.emplace_back("data/step-top/step-top.obj",     m_meshMap, Vector3(), Vector3(), false);
	m_opaqueModels.emplace_back("data/step-front/step-front.obj", m_meshMap, Vector3(), Vector3(), false);
	m_opaqueModels.emplace_back("data/floor/floor.obj",           m_meshMap, Vector3(), Vector3(), false);
	m_opaqueModels.emplace_back("data/columns/columns.obj",       m_meshMap, Vector3(), Vector3(), false);
	
	m_lights.addLight(AmbientLight(Vector3(0.25f, 0.25f, 0.25f)));
	m_lights.addLight(DirectionalLight(Vector3(1.0f, 1.0f, 1.0f), Vector3(-2.0f, 0.0f, 0.0f)));
	m_lights.addLight(DirectionalLight(Vector3(0.25f, 0.25f, 0.25f), Vector3(1.0f, -7.0f, -0.5f)));
	m_lights.addLight(PointLight(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 2.0f, 0.0f), 0.5f));
}
