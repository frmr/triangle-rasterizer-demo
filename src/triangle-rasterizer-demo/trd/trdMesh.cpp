#include "trdMesh.hpp"
#include "trdExternalLibraryException.hpp"
#include "trdUnsupportedFileException.hpp"
#include "tiny_obj_loader.h"

trd::Mesh::Mesh(const tf::String& filename, const TextureMap& textureMap)
{
	if (m_texture->isInitialized())
		m_texture->getWidth();

	loadObj("data/meshes/test.obj", textureMap);
}

void trd::Mesh::loadObj(const tf::String& filename, const TextureMap& textureMap)
{
	m_vertices.clear();
	m_texture = nullptr;

	tinyobj::attrib_t                attributes;
	std::vector<tinyobj::shape_t>    shapes;
	std::vector<tinyobj::material_t> materials;

	std::string                      warning;
	std::string                      error;

	if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, filename.c_str()))
	{
		throw ExternalLibraryException("trd::Mesh::loadObj(): " + error);
	}

	if (!shapes.empty() && !materials.empty())
	{
		for (const unsigned char numFaceVertices : shapes.front().mesh.num_face_vertices)
		{
			if (numFaceVertices != 3)
			{
				throw UnsupportedFileException("trd::Mesh::loadObj(): Only triangular faces are support");
			}
		}

		for (const auto vertex : shapes.front().mesh.indices)
		{
			m_vertices.emplace_back(
				Vector4(
					attributes.vertices[size_t(vertex.vertex_index) * 3 + 0],
					attributes.vertices[size_t(vertex.vertex_index) * 3 + 1],
					attributes.vertices[size_t(vertex.vertex_index) * 3 + 2],
					1.0f
				),
				Vector3(
					attributes.normals[size_t(vertex.normal_index) * 3 + 0],
					attributes.normals[size_t(vertex.normal_index) * 3 + 1],
					attributes.normals[size_t(vertex.normal_index) * 3 + 2]
				),
				Vector2(
					attributes.texcoords[size_t(vertex.texcoord_index) * 2 + 0],
					attributes.texcoords[size_t(vertex.texcoord_index) * 2 + 1]
				)
			);
		}

		m_texture = textureMap.get(materials.front().diffuse_texname);
	}
}

void trd::Mesh::draw(tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const
{
	shader.setTexture(m_texture);
	rasterizer.draw(m_vertices, shader, colorBuffer, depthBuffer);
}