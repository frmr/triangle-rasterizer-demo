#include "trdModel.hpp"

trd::Model::Model(const tf::String& meshFilename, const MeshMap& meshMap, const Vector3& position, const Vector2& rotation) :
	m_mesh(meshMap.get(meshFilename)),
	m_matrix()
{
}

void trd::Model::draw(const Camera& camera, tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const
{
	rasterizer.setMatrix(camera.getProjectionViewMatrix() * m_matrix);

	m_mesh->draw(rasterizer, shader, colorBuffer, depthBuffer);
}
