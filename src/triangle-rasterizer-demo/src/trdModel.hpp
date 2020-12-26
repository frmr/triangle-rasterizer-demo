#pragma once

#include "trRasterizer.hpp"
#include "trdCamera.hpp"
#include "trdMesh.hpp"
#include "trdMeshMap.hpp"
#include "trdTextureMap.hpp"
#include "Vectors.h"

namespace trd
{
	class Model
	{
	public:
		                  Model(const tf::String& meshFilename, MeshMap& meshMap, const Vector3& position, const Vector3& rotation, const bool fullBright);

		void              queueTriangles(const Vector3& cameraPosition, const bool sort, tr::Rasterizer<Shader>& rasterizer, Shader& shader) const;

		void              translate(const Vector3& translation);
		void              rotate(const Vector3& rotation);
		void              scale(const float scale);
		void              setPosition(const Vector3& position);
		void              setRotation(const Vector3& rotation);
		void              setScale(const float scale);

	private:
		void              recalculateMatrix();

	private:
		const Mesh* const m_mesh;
		Matrix4           m_matrix;
		Vector3           m_position;
		Vector3           m_rotation;
		float             m_scale;
		bool              m_fullBright;
	};
}