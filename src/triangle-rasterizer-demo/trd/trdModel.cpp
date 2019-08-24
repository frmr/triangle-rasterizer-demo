#include "trdModel.hpp"

trd::Model::Model(const tf::String& meshFilename, MeshMap& meshMap, const Vector3& position, const Vector3& rotation, const bool fullBright) :
	m_mesh(meshMap.get(meshFilename)),
	m_matrix(),
	m_position(position),
	m_rotation(rotation),
	m_fullBright(fullBright)
{
	recalculateMatrix();
}

void trd::Model::draw(tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const
{
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
	recalculateMatrix();
}

void trd::Model::rotate(const Vector3& rotation)
{
	m_rotation += rotation;
	recalculateMatrix();
}

void trd::Model::setPosition(const Vector3& position)
{
	m_position = position;
	recalculateMatrix();
}

void trd::Model::setRotation(const Vector3& rotation)
{
	m_rotation = rotation;
	recalculateMatrix();
}

void trd::Model::recalculateMatrix()
{
	m_matrix.identity();
	m_matrix.rotateX(m_rotation.x);
	m_matrix.rotateY(m_rotation.y);
	m_matrix.rotateZ(m_rotation.z);
	m_matrix.translate(m_position);
}
