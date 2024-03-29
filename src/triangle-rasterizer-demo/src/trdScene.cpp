#include "trdScene.hpp"

trd::Scene::Scene() :
	m_textureMap(),
	m_meshMap(m_textureMap),
	m_hologramManager(m_meshMap)
{
	createScene();
}

void trd::Scene::draw(const size_t numThreads, const Camera& camera, tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const
{
	Lights lights = m_lights;

	lights.addLight(m_hologramManager.getLight());

	shader.setLights(lights);
	rasterizer.setProjectionMatrix(camera.getProjectionMatrix());
	rasterizer.setViewMatrix(camera.getViewMatrix());
	rasterizer.setCullFaceMode(tr::CullFaceMode::Front);
	shader.setAlpha(1.0f);

	for (const Model& model : m_models)
	{
		model.queueTriangles(camera.getPosition(), false, rasterizer, shader);
	}

	m_hologramManager.queueHologram(camera.getPosition(), rasterizer, shader);

	rasterizer.draw(numThreads, colorBuffer, depthBuffer);
	rasterizer.clear();
}

void trd::Scene::update(const bool pauseAnimation, const float frameTime)
{
	if (!pauseAnimation)
	{
		m_hologramManager.update(frameTime);
	}
}

void trd::Scene::createScene()
{
	m_models.emplace_back("data/dome/dome.obj",             m_meshMap, Vector3(), Vector3(), false);
	m_models.emplace_back("data/ceiling/ceiling.obj",       m_meshMap, Vector3(), Vector3(), false);
	m_models.emplace_back("data/trim/trim.obj",             m_meshMap, Vector3(), Vector3(), false);
	m_models.emplace_back("data/wall/wall.obj",             m_meshMap, Vector3(), Vector3(), false);
	m_models.emplace_back("data/step-top/step-top.obj",     m_meshMap, Vector3(), Vector3(), false);
	m_models.emplace_back("data/step-front/step-front.obj", m_meshMap, Vector3(), Vector3(), false);
	m_models.emplace_back("data/floor/floor.obj",           m_meshMap, Vector3(), Vector3(), false);
	m_models.emplace_back("data/columns/columns.obj",       m_meshMap, Vector3(), Vector3(), false);
	m_models.emplace_back("data/projector/projector.obj",   m_meshMap, Vector3(), Vector3(), false);
	
	m_lights.addLight(AmbientLight(Vector3(0.2f, 0.2f, 0.2f)));
}
