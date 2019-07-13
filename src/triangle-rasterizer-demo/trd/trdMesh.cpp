#include "trdMesh.hpp"

trd::Mesh::Mesh(const tf::String& filename, const TextureMap& textureMap) :
	m_vertices(defineVertices()),
	m_texture(textureMap.get("data/textures/test.png"))
{
	if (m_texture->isInitialized())
		m_texture->getWidth();
}

std::vector<tr::Vertex> trd::Mesh::defineVertices()
{	
	return {

 		// Front
		tr::Vertex(Vector4( 2.0f,  2.0f,  2.0f, 1.0f), Vector3(0.0f, 0.0f,  1.0f), Vector2(2.0f, 0.0f)),
		tr::Vertex(Vector4( 2.0f, -2.0f,  2.0f, 1.0f), Vector3(0.0f, 0.0f,  1.0f), Vector2(2.0f, 2.0f)),
		tr::Vertex(Vector4(-2.0f, -2.0f,  2.0f, 1.0f), Vector3(0.0f, 0.0f,  1.0f), Vector2(0.0f, 2.0f)),

 		tr::Vertex(Vector4(-2.0f,  2.0f,  2.0f, 1.0f), Vector3(0.0f, 0.0f,  1.0f), Vector2(0.0f, 0.0f)),
		tr::Vertex(Vector4( 2.0f,  2.0f,  2.0f, 1.0f), Vector3(0.0f, 0.0f,  1.0f), Vector2(2.0f, 0.0f)),
		tr::Vertex(Vector4(-2.0f, -2.0f,  2.0f, 1.0f), Vector3(0.0f, 0.0f,  1.0f), Vector2(0.0f, 2.0f)),

 		// Top
		tr::Vertex(Vector4(-2.0f,  2.0f,  2.0f, 1.0f), Vector3(0.0f, 1.0f,  0.0f), Vector2(0.0f, 0.0f)),
		tr::Vertex(Vector4(-2.0f,  2.0f, -2.0f, 1.0f), Vector3(0.0f, 1.0f,  0.0f), Vector2(1.0f, 0.0f)),
		tr::Vertex(Vector4( 2.0f,  2.0f,  2.0f, 1.0f), Vector3(0.0f, 1.0f,  0.0f), Vector2(0.0f, 1.0f)),

 		tr::Vertex(Vector4(-2.0f,  2.0f, -2.0f, 1.0f), Vector3(0.0f, 1.0f,  0.0f), Vector2(1.0f, 0.0f)),
		tr::Vertex(Vector4( 2.0f,  2.0f, -2.0f, 1.0f), Vector3(0.0f, 1.0f,  0.0f), Vector2(1.0f, 1.0f)),
		tr::Vertex(Vector4( 2.0f,  2.0f,  2.0f, 1.0f), Vector3(0.0f, 1.0f,  0.0f), Vector2(0.0f, 1.0f)),

 		// Right	
		tr::Vertex(Vector4( 2.0f,  2.0f, -2.0f, 1.0f), Vector3(1.0f, 0.0f,  0.0f), Vector2(1.0f, 0.0f)),
		tr::Vertex(Vector4( 2.0f, -2.0f, -2.0f, 1.0f), Vector3(1.0f, 0.0f,  0.0f), Vector2(1.0f, 1.0f)),
		tr::Vertex(Vector4( 2.0f,  2.0f,  2.0f, 1.0f), Vector3(1.0f, 0.0f,  0.0f), Vector2(0.0f, 0.0f)),

 		tr::Vertex(Vector4( 2.0f,  2.0f,  2.0f, 1.0f), Vector3(1.0f, 0.0f,  0.0f), Vector2(0.0f, 0.0f)),
		tr::Vertex(Vector4( 2.0f, -2.0f, -2.0f, 1.0f), Vector3(1.0f, 0.0f,  0.0f), Vector2(1.0f, 1.0f)),
		tr::Vertex(Vector4( 2.0f, -2.0f,  2.0f, 1.0f), Vector3(1.0f, 0.0f,  0.0f), Vector2(0.0f, 1.0f)),

 		// Back	
		tr::Vertex(Vector4(-2.0f, -2.0f, -2.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 1.0f)),
		tr::Vertex(Vector4( 2.0f, -2.0f, -2.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 1.0f)),
		tr::Vertex(Vector4( 2.0f,  2.0f, -2.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 0.0f)),

 		tr::Vertex(Vector4(-2.0f, -2.0f, -2.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 1.0f)),
		tr::Vertex(Vector4( 2.0f,  2.0f, -2.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 0.0f)),
		tr::Vertex(Vector4(-2.0f,  2.0f, -2.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 0.0f)),
	};
}

void trd::Mesh::draw(tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const
{
	shader.setTexture(m_texture);
	rasterizer.draw(m_vertices, shader, colorBuffer, depthBuffer);
}