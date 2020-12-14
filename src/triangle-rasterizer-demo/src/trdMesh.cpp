#include "trdMesh.hpp"
#include "trdExternalLibraryException.hpp"
#include "trdUnsupportedFileException.hpp"
#include "tiny_obj_loader.h"

trd::Mesh::Mesh(const tf::String& filename, TextureMap& textureMap)
{
	loadObj(filename, textureMap);
}

void trd::Mesh::loadObj(const tf::String& filename, TextureMap& textureMap)
{
	m_vertices.clear();
	m_faceMidPoints.clear();
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
			m_vertices.push_back({
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
					1.0f - attributes.texcoords[size_t(vertex.texcoord_index) * 2 + 1]
				)
			});
		}

		for (size_t vertexIndex = 0; vertexIndex < m_vertices.size(); vertexIndex += 3)
		{
			const Vector4& position0 = m_vertices[vertexIndex + 0].position;
			const Vector4& position1 = m_vertices[vertexIndex + 1].position;
			const Vector4& position2 = m_vertices[vertexIndex + 2].position;

			m_faceMidPoints.push_back(Vector4(
				(position0.x + position1.x + position2.x) / 3.0f,
				(position0.y + position1.y + position2.y) / 3.0f,
				(position0.z + position1.z + position2.z) / 3.0f,
				1.0f
			));
		}

		m_texture = textureMap.get(materials.front().diffuse_texname);
	}
}

void trd::Mesh::queueTriangles(const Vector3& cameraPosition, const bool sort, tr::Rasterizer<Shader>& rasterizer, Shader& shader) const
{
	shader.setTexture(m_texture);

	if (sort)
	{
		std::multimap<float, size_t> faceDistanceIndexMap;
		const Matrix4                modelMatrix = rasterizer.getModelMatrix();

		for (size_t i = 0; i < m_faceMidPoints.size(); ++i)
		{
			const Vector4 transformedMidPoint    = modelMatrix * m_faceMidPoints[i];
			const Vector3 cameraToMidPointVector = Vector3(transformedMidPoint.x, transformedMidPoint.y, transformedMidPoint.z) - cameraPosition;
			const Vector3 squaredVector          = cameraToMidPointVector * cameraToMidPointVector;
			const float   squaredDistance        = squaredVector.x + squaredVector.y + squaredVector.z;

			faceDistanceIndexMap.emplace(squaredDistance, i);
		}

		std::vector<tr::Vertex> sortedFaceVertices;

		sortedFaceVertices.reserve(m_vertices.size());

		for (auto it = faceDistanceIndexMap.rbegin(); it != faceDistanceIndexMap.rend(); it++)
		{
			const auto& distanceIndexPair    = *it;
			const size_t unsortedVertexIndex = distanceIndexPair.second * 3;

			sortedFaceVertices.push_back(m_vertices[unsortedVertexIndex + 0]);
			sortedFaceVertices.push_back(m_vertices[unsortedVertexIndex + 1]);
			sortedFaceVertices.push_back(m_vertices[unsortedVertexIndex + 2]);
		}

		rasterizer.queue(sortedFaceVertices, shader);
	}
	else
	{
		rasterizer.queue(m_vertices, shader);
	}
}