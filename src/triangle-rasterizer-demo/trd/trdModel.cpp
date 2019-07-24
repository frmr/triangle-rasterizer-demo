#include "trdModel.hpp"

trd::Model::Model(const tf::String& meshFilename, const MeshMap& meshMap, const Vector3& position, const Vector3& rotation, const bool fullBright) :
	m_mesh(meshMap.get(meshFilename)),
	m_matrix(),
	m_fullBright(fullBright)
{
}

void trd::Model::draw(const Camera& camera, tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const
{
	rasterizer.setProjectionViewMatrix(camera.getProjectionViewMatrix());
	rasterizer.setModelMatrix(m_matrix);

	const RenderMode originalRenderMode = shader.getRenderMode();

	if (originalRenderMode == RenderMode::Lit && m_fullBright)
	{
		shader.setRenderMode(RenderMode::FullBright);
	}

	m_mesh->draw(rasterizer, shader, colorBuffer, depthBuffer);

	shader.setRenderMode(originalRenderMode);
}

void trd::Model::translate(const Vector3& translation)
{
	m_position += translation;

	m_matrix.translate(translation);
}

void trd::Model::rotate(const Vector3& rotation)
{
	m_rotation += rotation;

	m_matrix.rotateX(rotation.x);
	m_matrix.rotateY(rotation.y);
	m_matrix.rotateZ(rotation.z);
}

void trd::Model::setPosition(const Vector3& position)
{
	m_matrix.identity();
	rotate(m_rotation);
	translate(position);
}

void trd::Model::setRotation(const Vector3& rotation)
{
	m_matrix.identity();
	rotate(rotation);
	translate(m_position);
}
